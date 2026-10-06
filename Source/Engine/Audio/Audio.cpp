#include "pch.h"
#include "Audio.h"

namespace STR_FALL
{
	bool Audio::Initialize()
	{
		if (!CheckFMODResult(FMOD::System_Create(&m_audio))) { return false; }
		if (!CheckFMODResult(m_audio->init(32, FMOD_INIT_NORMAL, m_extraDriverData))) { return false; }
		return true;
		
	}
	void Audio::ShutDown()
	{
		CheckFMODResult(m_audio->release());
		delete m_extraDriverData; m_extraDriverData = nullptr;
		m_tempSound = nullptr;
		m_sounds.clear();
	}

	bool Audio::AddSound(const std::string& name, const std::string& fileName)
	{
		if (m_sounds.contains(name)) { std::cerr << "Audio System : name already exists " << name << std::endl; return false; }

		if (!CheckFMODResult(m_audio->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &m_tempSound))) { return false; }

		m_sounds[name] = m_tempSound;
		m_tempSound = nullptr;

		return true;
	}

	bool Audio::SetSound(const std::string& name, const std::string& fileName)
	{
		if (!CheckFMODResult(m_audio->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &m_tempSound))) { return false; }

		m_sounds[name] = m_tempSound;
		m_tempSound = nullptr;

		return true;
	}

	bool Audio::PlaySound(const std::string& name)
	{
		if (!m_sounds.contains(name)) { std::cerr << "Audio System : name doesn't exists " << name << std::endl; return false; }

		if (!CheckFMODResult(m_audio->playSound(m_sounds[name], 0, false, nullptr))) { return false; }

		return true;
	}
}