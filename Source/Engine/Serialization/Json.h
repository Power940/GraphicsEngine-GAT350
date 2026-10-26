#pragma once
#include <Math/Structs.h>
#include <rapidjson/document.h>
#include <string>
#include <unordered_set>
#include <vector>


#define JSON_READ_NAME(value, string, data) STR_FALL::Json::Read(value, string, data)
#define JSON_READ(value, data) STR_FALL::Json::Read(value, #data, data)
#define JSON_HAS(value, name) value.HasMember(name)
#define JSON_GET(value, name) value[name]

namespace STR_FALL::Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);
	bool Read(const rapidjson::Value& value, const std::string& name, unsigned int& data);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::unordered_set<std::string>& data);

	bool Read(const rapidjson::Value& value, const std::string& name, glm::vec2& data);
	bool Read(const rapidjson::Value& value, const std::string& name, glm::vec3& data);
	bool Read(const rapidjson::Value& value, const std::string& name, glm::vec4& data);

	//bool Read(const rapidjson::Value& value, const std::string& name, glm::mat2& data);
	//bool Read(const rapidjson::Value& value, const std::string& name, glm::mat3& data);


	/// <summary>
	/// <para>Index: 0, 1, 2 -> Position</para>
	/// <para>Index: 3, 4, 5 -> Scale</para>
	/// <para>Index: 6, 7, 8 -> Rotation</para>
	/// </summary>
	bool Read(const rapidjson::Value& value, const std::string& name, Transform3D& data);

	/// <summary>
	/// <para>Options:</para>
	/// <para>Int -> raw underlying 32 int</para>
	/// <para>4 unsigned bytes -> raw underlying 32 int | Left to Right -> Big to Small</para>
	/// <para>32 ones and zeros -> raw underlying 32 int | Left to Right -> Big to Small</para>
	/// </summary>
	bool Read(const rapidjson::Value& value, const std::string& name, BitMaskInt& data);
}
