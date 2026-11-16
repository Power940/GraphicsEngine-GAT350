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

	void GameObject::Draw(Renderer& r)
	{
		if (!m_active) { return; }

		for (std::unique_ptr<Component>& component : m_components)
		{
			if (!component->m_active) { continue; }

			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(r);
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