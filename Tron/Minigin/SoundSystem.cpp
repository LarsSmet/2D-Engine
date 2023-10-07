#include "MiniginPCH.h"
#include "SoundSystem.h"
#include <mutex>

//got some help from Maxim Robeyst with the threading

int SDLSoundSystem::s_Head = 0;
int SDLSoundSystem::s_Tail;
const int SDLSoundSystem::s_MaxRequests = 20;
SoundRequest SDLSoundSystem::s_PendingSoundRequests[s_MaxRequests];



SDLSoundSystem::SDLSoundSystem() :  m_QueueIsRunning{ true }, //important that it gets initiliazed first, because otherwise thread would end instantly
m_SoundThread{ &SDLSoundSystem::ProcessEventQueue, this } //pas this pointer because a member func gets called, member func calls hidden this pointer (thread needs this pointer, to get member variable from ss)
{
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);



	s_Head = 0;
	s_Tail = 0;

	


}

SDLSoundSystem::~SDLSoundSystem()
{
	m_QueueIsRunning = false; //needs to be put to false, otherwise it will wait for other thread to end{
	m_ConditionVariable.notify_one(); //make sure thread ends



	m_SoundThread.join(); //set sound thread back on main thread
	SDL_Quit();
}

void SDLSoundSystem::PlaySoundRequest(SoundRequest request) 
{

	std::unique_lock lock{m_Mutex}; //lock soundthread so shared data is safe to change

	//add sounds to the queue
	s_PendingSoundRequests[s_Tail].path = request.path;
	s_PendingSoundRequests[s_Tail].volume = request.volume;

	s_Tail = (s_Tail + 1) % s_MaxRequests;

	m_ConditionVariable.notify_one(); //notify soundthread of change 

}


Mix_Chunk* SDLSoundSystem::LoadSound(SoundRequest request)  
{
	

	Mix_Chunk* tmpChunk = Mix_LoadWAV(request.path);

	if (tmpChunk != nullptr)
	{
		Mix_VolumeChunk(tmpChunk, int(request.volume));
		return tmpChunk;
	}

	return 0;

}





void SDLSoundSystem::ProcessEventQueue()
{
	while(m_QueueIsRunning)
	{

		if (s_Head == s_Tail) //if no sounds to load
		{
			//locks processeventqueue until we get a new sound to make sure we dont  loop
			std::unique_lock lock{ m_Mutex };
			m_ConditionVariable.wait(lock);



		}


		while (s_Head != s_Tail)
		{
			Mix_Chunk* tmpChunk = LoadSound(s_PendingSoundRequests[s_Head]);

			Mix_PlayChannel(-1, tmpChunk, 0);

			m_Mutex.lock(); //lock thread so shared data is safe to change
			s_Head = (s_Head + 1) % s_MaxRequests;
			m_Mutex.unlock();

		}

	

	}
}


void NullSoundSystem::PlaySoundRequest(SoundRequest request) 
{
	request; 
};

Mix_Chunk* NullSoundSystem::LoadSound(SoundRequest request)
{ 
	request; 
	return nullptr; 
};





NullSoundSystem ServiceLocator::s_DefaultInstance;
SoundSystem* ServiceLocator::s_Instance = &s_DefaultInstance;

void ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	s_Instance = soundSystem == nullptr ? &s_DefaultInstance : soundSystem;
}

SoundSystem& ServiceLocator::GetSoundSystem()
{

	return *s_Instance;


}

void ServiceLocator::DeleteSoundSystem()
{


	delete s_Instance;


	s_Instance = nullptr;



}

void LoggingSoundSystem::PlaySoundRequest(SoundRequest request)
{
	s_RealInstance->PlaySoundRequest(request);

	std::cout << "Playing from path: " << request.path << " at volume: " << request.volume << '\n';

}

 Mix_Chunk* LoggingSoundSystem::LoadSound(SoundRequest request) 
{
	 std::cout << "Loading sound " << request.path << " at volume: " << request.volume << '\n';
	return s_RealInstance->LoadSound(request);
	
}


