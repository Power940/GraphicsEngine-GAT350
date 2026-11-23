#pragma once
#include "Component.h"


namespace STR_FALL
{
	class RendererComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& r) = 0;
	};
}