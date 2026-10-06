#include "pch.h"
#include "TileMap.h"
#include "Texture.h"
#include "Renderer.h"
#include <Serialization/Json.h>
#include <Core/StringUtils.h>
#include <rapidjson/document.h>
#include <iostream>
#include <ostream>
#include <string>

namespace STR_FALL
{
	Rect2D TileMap::GetTileRect(const Layer& layer, int tileId)
	{
		if (tileId == 0) { return Rect2D(); }

		Vector2 textureSize = layer.texture->m_size;
		int tilesPerRow = static_cast<int>(textureSize.m_x) / m_tileWidth;

		int column = (tileId - 1) % tilesPerRow;
		int row = (tileId - 1) / tilesPerRow;

		return Rect2D(
			static_cast<float>(column * m_tileWidth),
			static_cast<float>(row * m_tileHeight),
			static_cast<float>(m_tileWidth),
			static_cast<float>(m_tileHeight)
			);
	}

	Vector2 TileMap::GetTilePosition(const Layer& layer, int tileIndex)
	{
		{
			int column = tileIndex % layer.m_width;
			int row = tileIndex / layer.m_width;
			return Vector2(static_cast<float>(column * m_tileWidth), static_cast<float>(row * m_tileHeight));
		}
	}

	bool TileMap::Load(const std::string& filename, Renderer& r)
	{
		rapidjson::Document doc;
		if (!Json::Load(filename, doc))
		{
			std::cerr << "Could not load Tilemap " << filename << std::endl;
			return false;
		}

		// read tilemap data
		JSON_READ_NAME(doc, "tilewidth", m_tileWidth);
		JSON_READ_NAME(doc, "tileheight", m_tileHeight);

		// read tilemap layers
		if (JSON_HAS(doc, "layers"))
		{
			for (auto& layerValue : JSON_GET(doc, "layers").GetArray())
			{
				Layer layer;

				JSON_READ_NAME(layerValue, "height", layer.m_height);
				JSON_READ_NAME(layerValue, "width", layer.m_width);
				JSON_READ_NAME(layerValue, "data", layer.m_data);

				// load texture from properties
				if (JSON_HAS(layerValue, "properties"))
				{
					for (auto& propertyValue : JSON_GET(layerValue, "properties").GetArray())
					{
						std::string name;
						JSON_READ(propertyValue, name);

						// check if property name is TextureName
						if (EqualsIgnoreCase(name, "m_textureName"))
						{
							// read texture name value (texture name)
							std::string value;
							JSON_READ(propertyValue, value);

							layer.texture = ResourceManager::ResManager().GetWithID<Texture>(value, value, r);
							if (!layer.texture)
							{
								std::cerr << "Could not read tilemap layer texure " << value << std::endl;
							}
						}
						else if (EqualsIgnoreCase(name, "m_hasCollision"))
						{
							JSON_READ_NAME(propertyValue, "value", layer.m_hasCollision);
						}
					}
				}

				m_layers.push_back(layer);
			}
		}
		return true;
	}
}