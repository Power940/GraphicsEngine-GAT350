#pragma once
#include <memory>
#include <Editor/Editor.h>


namespace STR_FALL
{
	class Resource : public IGUI
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		std::string m_name = "NAME_NOT_SET";
	};

	template <typename T = Resource>
	using res_t = std::shared_ptr<T>;
}