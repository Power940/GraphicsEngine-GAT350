#include "pch.h"
#include "TileMapRendererComponent.h"
#include <Core/Factory.h>
#include "StarFallEngine.h"
#include <Renderer/TileMap.h>
#include "Resources/ResourceManager.h"
#include <Physics/PhysicsBody.h>
#include "RendererComponent.h"
#include <Math/Structs.h>
#include <Renderer/Renderer.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

namespace STR_FALL
{
	FACTORY_REG(TileMapRendererComponent)
	
	void TileMapRendererComponent::Start()
	{
		m_tileMap = ResourceManager::ResManager().GetWithID<TileMap>(m_tileMapName.c_str(), m_tileMapName.c_str(), STR_Engine::m_renderer);

		if (!m_tileMap)
		{
			std::cerr << "Could not load tilename " << m_tileMapName << std::endl;
			return;
		}

		// set tile transform current owner (actor) transform 
		Transform3D transform = m_owner->GetTransform();

		// define physics bodies 
		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;	// doesn't move (not dynamic) 
		bodyDef.owner = m_owner;	// set actor for collision 

		// iterate through layers 
		for (TileMap::Layer& layer : m_tileMap->m_layers)
		{
			// if layer doesn't have collision, skip physics body creation 
			if (!layer.m_hasCollision) continue;

			// get tilemap data (tile ids) 
			for (int i = 0; i < layer.m_data.size(); i++)
			{
				int tileId = layer.m_data[i];
				if (tileId == 0) continue;

				// set source rect from id 
				Rect2D sourceRect = m_tileMap->GetTileRect(layer, tileId);

				// set position from owner transform position + tile position * owner transform scale 
				transform.m_pos = m_owner->GetTransform().m_pos + (m_tileMap->GetTilePosition(layer, i) * transform.m_scale);

				// size of physics body is tehe source rect 
				Vector2 size{ sourceRect.m_w, sourceRect.m_h };
				
				// create physics body and add to physics bodies container 
				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, STR_Engine::m_phys);
				m_physicsBodies.push_back(std::move(physicsBody));

			}
		}
	}


	void TileMapRendererComponent::Draw(Renderer& r)
	{
		// iterate through layers 
		for (TileMap::Layer& layer : m_tileMap->m_layers)
		{
			// get layer data (array of tile ids) 
			for (int i = 0; i < layer.m_data.size(); i++)
			{
				int tileId = layer.m_data[i];
				if (tileId == 0) continue; // don't draw if tile ids = 0 

				// get source rect of tile id 
				Rect2D sourceRect = m_tileMap->GetTileRect(layer, tileId);

				// set position from owner (actor) transform position + tile position * transform scale 
				Transform3D transform = m_owner->GetTransform();
				Vector2 position = transform.m_pos + m_tileMap->GetTilePosition(layer, i) * transform.m_scale;

				// draw tile texture 
				r.RenderTexture(layer.texture.get(), sourceRect, position.m_x, position.m_y, transform.m_rotMat[0][0], transform.m_scale.m_x, transform.m_scale.m_y, false);
			}
		}
	}


	void TileMapRendererComponent::Read(const rapidjson::Value& value)
	{
		RendererComponent::Read(value);

		JSON_READ(value, m_tileMapName);
	}
}