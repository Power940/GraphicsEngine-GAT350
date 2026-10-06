#pragma once
#include <Math/Structs.h>
#include "Renderer.h"
#include "Texture.h"
#include <Resources/Resource.h>
#include <string>


namespace STR_FALL
{
	class TextureFrames : public Resource
	{
	public:
		bool Load(const std::string& filename, class Renderer& r);
		Rect2D GetFrameRect(unsigned int frame);

		unsigned int GetTotalFrames() const { return m_totalFrames; }
		res_t<Texture> GetTexture() const { return m_texture; }

	private:
		unsigned int m_columns = 0;
		unsigned int m_rows = 0;
		unsigned int m_startFrame = 0;
		unsigned int m_totalFrames = 0;

		Vector2 m_cellSize = Vector2();
		res_t<Texture> m_texture;
	};
}