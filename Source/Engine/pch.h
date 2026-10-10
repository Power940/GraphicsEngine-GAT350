#ifndef PCH_H
#define PCH_H

// Standard Library Includes
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// Third Party Includes
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>

#include <box2d/box2d.h>
#include <box2d/id.h>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>

// Project Includes
#include "Core/StringUtils.h"
#include "Serialization/Json.h"
#include "Framework/GameObject.h"
#include "Framework/Object.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Core/File.h"
#include "Math/Structs.h"
#include "Input/Input.h"
#include "Core/StarTime.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

#endif //PCH_H