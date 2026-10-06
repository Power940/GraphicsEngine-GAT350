#include "pch.h"
#include "TextureFrames.h"


namespace STR_FALL
{
    bool TextureFrames::Load(const std::string& filename, Renderer& r)
    {
        rapidjson::Document doc;

        if (!Json::Load(filename, doc))
        {
            std::cerr << "Could not load TextureFrames: " << filename << std::endl;
            return false;
        }

        std::string texture_name;
        JSON_READ(doc, texture_name);

        if (texture_name.empty())
        {
            return false;
        }

        m_texture = ResourceManager::ResManager().GetWithID<Texture>(texture_name.c_str(), texture_name.c_str(), r);

        if (!m_texture)
        {
            std::cerr << "Could not load TextureFrames texture: " << texture_name << std::endl;
            return false;
        }

        JSON_READ(doc, m_columns);
        JSON_READ(doc, m_rows);
        JSON_READ(doc, m_startFrame);
        JSON_READ(doc, m_totalFrames);

        if (m_columns == 0 || m_rows == 0)
        {
            std::cerr << "TextureFrames m_columns or m_rows can't be 0" << std::endl;
            return false;
        }

        m_cellSize = m_texture->m_size / Vector2(static_cast<float>(m_columns), static_cast<float>(m_rows));

        return true;
    }

    Rect2D TextureFrames::GetFrameRect(unsigned int frame)
    {
        if (frame >= m_totalFrames)
        {
            std::cerr << "TextureFrames frame: " << frame << " is out of bounds" << std::endl;
            frame = 0;
        }

        int currentFrame = m_startFrame + frame;
        int column = currentFrame % m_columns;
        int row = currentFrame / m_columns;
        float x = column * m_cellSize.m_x;
        float y = row * m_cellSize.m_y;

        return Rect2D(x, y, m_cellSize.m_x, m_cellSize.m_y);
    }
}