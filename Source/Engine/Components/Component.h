#pragma once
#include <Framework/Object.h>


namespace STR_FALL
{
	class GameObject;

	class Component : public Object
	{
	public:
		GameObject* m_owner = nullptr;

		Component() = default;
		virtual ~Component() = default;

		CLASS_PROTOTYPE(Component)

		virtual void Start() {}
		virtual void Update(float dt) {}
		virtual void OnDestroy() {}

		virtual void Read(const rapidjson::Value& value) override
		{
			Object::Read(value);
		}
	};
}