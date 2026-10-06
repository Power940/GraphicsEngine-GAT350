#pragma once
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

namespace STR_FALL
{
	class Audio
	{
	private:
		FMOD::System* m_audio = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
		FMOD::Sound* m_tempSound = nullptr;

		void* m_extraDriverData = nullptr;


		inline bool CheckFMODResult(FMOD_RESULT result)
		{
			if (result != FMOD_OK) { std::cerr << FMOD_ErrorString(result) << std::endl; return false; }
			return true;
		}

	public:
		bool Initialize();
		void ShutDown();

		inline void Update() { CheckFMODResult(m_audio->update()); };

		bool AddSound(const std::string& name, const std::string& fileName);
		bool SetSound(const std::string& name, const std::string& fileName);
		bool PlaySound(const std::string& name);
	};
}