#pragma once
#include <memory>
#include <string>
#include <Serialization/Json.h>


#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this); }

namespace STR_FALL
{
	struct Object
	{
	public:
		bool m_active = true;
		std::string m_name;


		Object() = default;
		virtual ~Object() = default;
		CLASS_PROTOTYPE(Object)

		virtual void Read(const rapidjson::Value& value)
		{
			JSON_READ(value, m_name);
			JSON_READ(value, m_active);
		}
	};
}