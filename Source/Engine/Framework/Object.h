#pragma once
#include <memory>
#include <string>
#include <Serialization/Json.h>
#include <Editor/Editor.h>


#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this); } virtual const char* GetClassName() const { return #classname; }

namespace STR_FALL
{
	class Object : public IGUI
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

		void UpdateGui() override
		{
			ImGui::Text("%s", m_name.c_str());
		}
	};
}