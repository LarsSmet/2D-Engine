#pragma once
#include "SDL_mixer.h"
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <thread>
#include <mutex>

//i used this video to implement the SDL Mixer: https://www.youtube.com/watch?v=q06uSmkiqec
// and this for the event queue: https://gameprogrammingpatterns.com/event-queue.html


struct SoundRequest
{
	const char* path;
	int volume;
};

class SoundSystem
{
public:

	virtual ~SoundSystem() = default;

		
	
	virtual void PlaySoundRequest(SoundRequest request) = 0;
	

	virtual Mix_Chunk* LoadSound(SoundRequest request) = 0;






	

};



class SDLSoundSystem final : public SoundSystem
{

	static int s_Head;
	static int s_Tail;
	static const int s_MaxRequests;
	static SoundRequest s_PendingSoundRequests[];

	public:

		SDLSoundSystem(); 
	

		~SDLSoundSystem();
	

		void PlaySoundRequest(SoundRequest request) override;
	

		Mix_Chunk* LoadSound(SoundRequest request)  override;
	


	

		void ProcessEventQueue();
	


	private:

		
		std::mutex m_Mutex;

		bool m_QueueIsRunning;

		std::condition_variable  m_ConditionVariable;
	
		std::thread m_SoundThread;

};



class NullSoundSystem final : public SoundSystem
{


	virtual void PlaySoundRequest(SoundRequest request) override;


	virtual Mix_Chunk* LoadSound(SoundRequest request) override;


	



};

class ServiceLocator final
{
	static SoundSystem* s_Instance;
	static NullSoundSystem s_DefaultInstance;

	public:


		
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* soundSystem);

	static void DeleteSoundSystem();

};









class LoggingSoundSystem final : public  SoundSystem
{
	SoundSystem* s_RealInstance; //make ref? TODO:

	public:
	LoggingSoundSystem(SoundSystem* soundSystem) : s_RealInstance(soundSystem) {}
	~LoggingSoundSystem() { delete s_RealInstance; }

	

	virtual void PlaySoundRequest(SoundRequest request);


	virtual Mix_Chunk* LoadSound(SoundRequest request);


	


	

};





