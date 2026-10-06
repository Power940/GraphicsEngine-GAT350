#include "pch.h"
#include "GameObject.h"


namespace STR_FALL
{
	FACTORY_REG(GameObject);


	void GameObject::Start()
	{
		for (std::unique_ptr<Component>& component : m_components)
		{
			component->Start();
		}
	}

	void GameObject::Update(float dt)
	{
		for (std::unique_ptr<Component>& component : m_components)
		{
			if (component->m_active)
			{
				component->Update(dt);
			}
		}
	}

	void GameObject::OnDestroy()
	{
		for (std::unique_ptr<Component>& component : m_components)
		{
			component->OnDestroy();
		}
	}
}