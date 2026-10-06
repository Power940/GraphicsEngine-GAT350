#pragma once
#include <random>
#include <algorithm>
#include <utility>


namespace STR_FALL
{
	inline std::mt19937& Generator()
	{
		static std::random_device randomDevice;
		static std::mt19937 gen(randomDevice());
		return gen;
	}

	inline static void SeedRandom()
	{
		Generator().seed(static_cast<unsigned int>(time(nullptr)));
	}

	inline void SeedRandom(unsigned int seed)
	{
		Generator().seed(seed);
	}

	inline int RandomInt()
	{
		static std::uniform_int_distribution<> dist;
		return dist(Generator());
	}

	inline int RandomInt(int max)
	{
		std::uniform_int_distribution<> dist(0, max - 1);
		return dist(Generator());
	}

	inline int RandomInt(int max, int min)
	{
		if (min > max) { std::swap(min, max); }
		std::uniform_int_distribution<> dist(min, max - 1);
		return dist(Generator());
	}

	inline float RandomFloat()
	{
		static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(Generator());
	}

	inline float RandomFloat(float max)
	{
		std::uniform_real_distribution<float> dist(0.0f, max);
		return dist(Generator());
	}

	inline float RandomFloat(float max, float min)
	{
		if (min > max) { std::swap(min, max); }
		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}

	inline bool RandomBool()
	{
		static std::bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}

	inline bool RandomBoolInfluence(float leaning)
	{
		if (leaning < 0.0f || 1.0f < leaning) { leaning = std::clamp(leaning, 0.0f, 1.0f); }
		std::bernoulli_distribution dist(leaning);
		return dist(Generator());
	}
}