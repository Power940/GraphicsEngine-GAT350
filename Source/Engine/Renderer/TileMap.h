#pragma once
#include <Resources/ResourceManager.h>
#include <Math/Structs.h>
#include <vector>

namespace STR_FALL
{
	class TileMap : public Resource
	{
	public:
		struct Layer
		{
			int m_width = 0;
			int m_height = 0;
			bool m_hasCollision = false;
			std::vector<int> m_data;
			res_t<class Texture> texture;
		};

		int m_tileWidth = 0;
		int m_tileHeight = 0;
		std::vector<Layer> m_layers;

		Rect2D GetTileRect(const Layer& layer, int tileId);
		Vector2 GetTilePosition(const Layer& layer, int tileIndex);

		bool Load(const std::string& filename, class Renderer& r);
	};
}