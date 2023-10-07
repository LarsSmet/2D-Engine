#include "MiniginPCH.h"
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#pragma comment(lib, "xinput.lib")

namespace dae
{

   

    class dae::InputManager::Impl
    {



    public:



        XINPUT_STATE m_PreviousState[XUSER_MAX_COUNT]{};
        XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT]{};


        ControllerCommandsMap m_ConsoleCommands{};
        KeyBoardCommandsMap m_KeyBoardCommands{};

        int m_ButtonsPressedThisFrame[XUSER_MAX_COUNT]{};
        int m_ButtonsReleasedThisFrame[XUSER_MAX_COUNT]{};

        //used https://stackoverflow.com/questions/3741055/inputs-in-sdl-on-key-pressed
        bool m_KeysPressedThisFrame[322]; //// 322 is the number of events
        bool m_KeysPressedPreviousFrame[322]; //// 322 is the number of events

    };


    dae::InputManager::InputManager() : m_Impl{ std::make_unique<dae::InputManager::Impl>() }
    {
        for (int i = 0; i < 322; ++i)
        {
            m_Impl->m_KeysPressedThisFrame[i] = false;
            m_Impl->m_KeysPressedPreviousFrame[i] = false;
        }

    }

    dae::InputManager::~InputManager()
    {
    }




    bool dae::InputManager::ProcessInput() 
    {
      
        SDL_Event e;

       

        while (SDL_PollEvent(&e)) {

   
            switch (e.type) {
           
            case SDL_KEYDOWN:
               
                //first store old one, then update new one
                m_Impl->m_KeysPressedPreviousFrame[e.key.keysym.scancode] = m_Impl->m_KeysPressedThisFrame[e.key.keysym.scancode];

                m_Impl->m_KeysPressedThisFrame[e.key.keysym.scancode] = true;

                break;
            case SDL_KEYUP:
                //first store old one, then update new one
                m_Impl->m_KeysPressedPreviousFrame[e.key.keysym.scancode] = m_Impl->m_KeysPressedThisFrame[e.key.keysym.scancode];
                m_Impl->m_KeysPressedThisFrame[e.key.keysym.scancode] = false;
               
                break;

                
            case SDL_QUIT:
                return false;
                break;
            default:
                break;
            }
        }

        CopyMemory(&m_Impl->m_PreviousState, &m_Impl->m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
        ZeroMemory(&m_Impl->m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);

        for (int i = 0; i < XUSER_MAX_COUNT; ++i)
        {
           
           XInputGetState(i, &m_Impl->m_CurrentState[i]);

            auto buttonChanges = m_Impl->m_CurrentState[i].Gamepad.wButtons ^ m_Impl->m_PreviousState[i].Gamepad.wButtons;

            m_Impl->m_ButtonsPressedThisFrame[i] = buttonChanges & m_Impl->m_CurrentState[i].Gamepad.wButtons;
            m_Impl->m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_Impl->m_CurrentState[i].Gamepad.wButtons);

            HandleControllerInput(i);
        }

        HandleKeyBoardInput();


     
        return true;
    }


    void dae::InputManager::HandleControllerInput(int currentController)
    {

        for (auto command : m_Impl->m_ConsoleCommands) //go over all commands and do the one that matches the pressed button
        {
            if (command.first.controllerIndex != currentController)
            {
                continue;
            }

            switch (command.first.state)
            {
            case ActionState::Down:

                if (IsDownThisFrame(unsigned int(command.first.button), currentController))
                {
                    command.second->Execute();
                }



                break;
            case ActionState::Up:

                if (IsUpThisFrame(unsigned int(command.first.button), currentController))
                {
                    command.second->Execute();
                }

            

                break;
            case ActionState::Hold:

                if (IsHeld(unsigned int(command.first.button), currentController))
                {
                    command.second->Execute();
                }

                break;

            }

     
        }

        


    }

    void dae::InputManager::HandleKeyBoardInput()
    {
        for (auto command : m_Impl->m_KeyBoardCommands) //go over all commands and do the one that matches the pressed button
        {




            switch (command.first.state)
            {
            case ActionState::Down:

                if (IsDownThisFrame(command.first.key))
                {

                    command.second->Execute();
                }

                break;
            case ActionState::Up:

                if (IsUpThisFrame(command.first.key))
                {
                    command.second->Execute();
                }



                break;
            case ActionState::Hold:

                if (IsHeld(command.first.key))
                {
                    command.second->Execute();
                }

                break;

            }


        }
    }

    //controller
    void dae::InputManager::BindKey(ControllerAction key, std::shared_ptr<Command> command)
    {

        m_Impl->m_ConsoleCommands.insert({ key, command });
    }


    bool dae::InputManager::IsHeld(unsigned int button, int currentController) const
    {
        return m_Impl->m_CurrentState[currentController].Gamepad.wButtons & button;
    }

    bool dae::InputManager::IsUpThisFrame(unsigned int button, int currentController) const
    {
        return m_Impl->m_ButtonsReleasedThisFrame[currentController] & button;
    }

    bool dae::InputManager::IsDownThisFrame(unsigned int button, int currentController) const
    {
        return m_Impl->m_ButtonsPressedThisFrame[currentController] & button;
    }

    //keyboard
    void dae::InputManager::BindKey(KeyBoardAction key, std::shared_ptr<Command> command)
    {
        m_Impl->m_KeyBoardCommands.insert({ key, command });
    }

    bool dae::InputManager::IsUpThisFrame(SDL_Keycode key) const
    {
       return !m_Impl->m_KeysPressedThisFrame[key];

    }

    bool dae::InputManager::IsDownThisFrame(SDL_Keycode key) const
    {
        
        return m_Impl->m_KeysPressedThisFrame[key];
    }

    bool dae::InputManager::IsHeld(SDL_Keycode key) const
    {
       
        if (m_Impl->m_KeysPressedThisFrame[key] && m_Impl->m_KeysPressedPreviousFrame[key])
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    void dae::InputManager::ClearInputCommands()
    {

        m_Impl->m_KeyBoardCommands.clear();
        m_Impl->m_ConsoleCommands.clear();

    }

}