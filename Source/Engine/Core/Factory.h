#pragma once
#include "Singleton.h"
#include "StringUtils.h"
#include <Framework/Object.h>
#include <algorithm>
#include <concepts>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>


#define FACTORY_REG(classname)																		\
	class Register##classname																		\
	{																								\
	public:																							\
		Register##classname() { STR_FALL::Factory::Instance().Register<classname>(#classname); }	\
	};																								\
	static Register##classname regInst##classname;


namespace STR_FALL
{
	class ICreator
	{
	public:
		virtual ~ICreator() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};


	template <typename T> requires std::derived_from<T, Object>
	class Creator : public ICreator
	{
	public:
		std::unique_ptr<Object> Create() override { return std::make_unique<T>(); }
	};


	template <typename T> requires std::derived_from<T, Object>
	class PrototypeCreator : public ICreator
	{
	public:
		PrototypeCreator(std::unique_ptr<Object> prototype) : m_prototype(std::move(prototype)) {}
		std::unique_ptr<Object> Create() override { return m_prototype->Clone(); }

	private:
		std::unique_ptr<Object> m_prototype;
	};


	class Factory : public Singleton<Factory>
	{
	private:
		std::map<std::string, std::unique_ptr<ICreator>> m_registry;

	public:
		template <typename T> requires std::derived_from<T, Object>
		void Register(const std::string& name)
		{
			std::string lowerName = ToLower(name);

			if (m_registry.contains(lowerName))
			{
				std::cerr << "Object already registered: " << name << std::endl;
				return;
			}
			m_registry[lowerName] = std::make_unique<Creator<T>>();
		}

		template <typename T> requires std::derived_from<T, Object>
		void PrototypeRegister(const std::string& name, std::unique_ptr<Object> prototype)
		{
			std::string lowerName = ToLower(name);

			if (m_registry.contains(lowerName))
			{
				std::cerr << "Object already registered: " << name << std::endl;
				return;
			}
			m_registry[lowerName] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		}

		template <typename T = Object> requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name)
		{
			std::string lowerName = ToLower(name);

			if (!m_registry.contains(lowerName))
			{
				std::cerr << "Object isn't in registry: " << name << std::endl;
				return std::unique_ptr<T>();
			}

			auto object = m_registry[lowerName]->Create();

			T* derived = dynamic_cast<T*>(object.get());
			if (derived)
			{
				object.release();
				return std::unique_ptr<T>(derived);
			}
			else
			{
				std::cerr << "Object not derived | Name: " << name << " Type: " << typeid(T).name() << std::endl;
				return std::unique_ptr<T>();
			}
			return std::unique_ptr<T>();
		}
	};
}