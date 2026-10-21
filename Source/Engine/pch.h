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

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

#endif //PCH_H