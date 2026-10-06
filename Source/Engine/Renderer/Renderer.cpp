#include "pch.h"
#include "Renderer.h"


namespace STR_FALL
{
    bool Renderer::Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT, Camera3D* cam)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        //SDL_SetDefaultTextureScaleMode(m_renderer, SDL_SCALEMODE_PIXELART);
        SDL_SetRenderVSync(m_renderer, 1);

        m_lastSetColor = new Color(1.0f, 1.0f, 1.0f);
        m_WINDOW_WIDTH = WINDOW_WIDTH;
        m_WINDOW_HEIGHT = WINDOW_HEIGHT;
        m_cam = cam;

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        m_lastSetColor->m_x = r / 255.0f;
        m_lastSetColor->m_y = g / 255.0f;
        m_lastSetColor->m_z = b / 255.0f;
        m_lastSetColor->m_w = a / 255.0f;
    }
    void Renderer::SetColor(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.m_x, c.m_y, c.m_z, c.m_w);
        m_lastSetColor->m_x = c.m_x;
        m_lastSetColor->m_y = c.m_y;
        m_lastSetColor->m_z = c.m_z;
        m_lastSetColor->m_w = c.m_w;
    }
    void Renderer::SetColorF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        m_lastSetColor->m_x = r;
        m_lastSetColor->m_y = g;
        m_lastSetColor->m_z = b;
        m_lastSetColor->m_w = a;
    }

    Color Renderer::GetColor() { return *m_lastSetColor; }

    void Renderer::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::Clear(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.m_x, c.m_y, c.m_z, c.m_w);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::ClearF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }
    void Renderer::ShutDown()
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        delete m_lastSetColor;
        m_lastSetColor = nullptr;
        SDL_Quit();
    }

    void Renderer::RenderDebugText(const std::string& text, const Vector2& point) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, 1.0f, 1.0f, 1.0f, 1.0f);
        SDL_RenderDebugText(m_renderer, point.m_x, point.m_y, text.c_str());
    }

    void Renderer::RenderTexture(const Texture* texture, float x, float y, float angleDeg, float xScale, float yScale, bool flipH, const Vector2& origin)
    {
        Vector2 size = texture->m_size;

        float cameraX = (m_useCamera2D) ? m_cam->m_transform.m_pos.m_x - (m_WINDOW_WIDTH * 0.5f) : 0.0f;
        float cameraY = (m_useCamera2D) ? m_cam->m_transform.m_pos.m_y - (m_WINDOW_HEIGHT * 0.5f) : 0.0f;

        SDL_FRect destRect;
        destRect.w = size.m_x * xScale;
        destRect.h = size.m_y * yScale;
        destRect.x = (x - cameraX) - (destRect.w * origin.m_x);
        destRect.y = (y - cameraY) - (destRect.h * origin.m_y);

        SDL_RenderTextureRotated(m_renderer, texture->m_texture, NULL, &destRect, angleDeg, NULL, flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    void Renderer::RenderTexture(const Texture* texture, const Rect2D& source, float x, float y, float angleDeg, float xScale, float yScale, bool flipH, const Vector2& origin)
    {
        Vector2 size = texture->m_size;

        float cameraX = (m_useCamera2D) ? m_cam->m_transform.m_pos.m_x - (m_WINDOW_WIDTH * 0.5f) : 0.0f;
        float cameraY = (m_useCamera2D) ? m_cam->m_transform.m_pos.m_y - (m_WINDOW_HEIGHT * 0.5f) : 0.0f;

        SDL_FRect srcRect;
        srcRect.x = source.m_x;
        srcRect.y = source.m_y;
        srcRect.w = source.m_w;
        srcRect.h = source.m_h;

        SDL_FRect destRect;
        destRect.w = source.m_w * xScale;
        destRect.h = source.m_h * yScale;
        destRect.x = (x - cameraX) - (destRect.w * origin.m_x);
        destRect.y = (y - cameraY) - (destRect.h * origin.m_y);
        SDL_RenderTextureRotated(m_renderer, texture->m_texture, &srcRect, &destRect, angleDeg, NULL, flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    void Renderer::RenderPoint(const Vector2& point) const { SDL_RenderPoint(m_renderer, point.m_x, point.m_y); }
    void Renderer::RenderPoints(const std::vector<Vector2>& points) const
    {
        for (const Vector2 point : points)
        {
            SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        }
    }
    void Renderer::RenderLine(const Line2D& line) const { SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y); }
    void Renderer::RenderLines(const std::vector<Line2D>& lines) const
    {
        for (const Line2D line : lines)
        {
            SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        }
    }
    void Renderer::RenderFillTriangle(const Triangle2D& tri) const {
        std::vector<SDL_Vertex> vertices;

        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[0].m_x, tri[0].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[1].m_x, tri[1].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[2].m_x, tri[2].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));

        SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), 3, nullptr, 0);
    }
    void Renderer::RenderOutlineTriangle(const Triangle2D& tri) const {

        SDL_RenderLine(m_renderer, tri[0].m_x, tri[0].m_y, tri[1].m_x, tri[1].m_y);
        SDL_RenderLine(m_renderer, tri[1].m_x, tri[1].m_y, tri[2].m_x, tri[2].m_y);
        SDL_RenderLine(m_renderer, tri[2].m_x, tri[2].m_y, tri[0].m_x, tri[0].m_y);
    }
    void Renderer::RenderCustomFilled(const std::vector<Vector2>& points, const std::vector<int>& indices) const
    {
        if (points.size() > 1)
        {
            std::vector<SDL_Vertex> vertices;

            for (const Vector2& point : points)
            {
                vertices.push_back(SDL_Vertex(
                    SDL_FPoint(point.m_x, point.m_y),
                    SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
                    SDL_FPoint(0, 0)
                ));
            }
            SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), indices.data(), static_cast<int>(indices.size()));
        }
    }
    void Renderer::RenderCustomOutline(const std::vector<Vector2>& points) const
    {
        unsigned int size = static_cast<unsigned int>(points.size());
        if (size > 1)
        {
            for (unsigned int index = 0; index < size; index++)
            {
                SDL_RenderLine(m_renderer,
                    points[index].m_x, points[index].m_y,
                    points[(index + 1) % size].m_x, points[(index + 1) % size].m_y
                );
            }
        }
    }

    void Renderer::RenderPointColor(const Vector2C& point) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w);
        SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderPointsColor(const std::vector<Vector2C>& points) const
    {
        for (const Vector2C& point : points)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w);
            SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderLineColor(const Line2DC& line) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, line.m_color.m_x, line.m_color.m_y, line.m_color.m_z, line.m_color.m_w);
        SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderLinesColor(const std::vector<Line2DC>& lines) const
    {
        for (const Line2DC& line : lines)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, line.m_color.m_x, line.m_color.m_y, line.m_color.m_z, line.m_color.m_w);
            SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderFillTriangleColor(const Triangle2DC& tri) const
    {
        std::vector<SDL_Vertex> vertices;

        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[0].m_x, tri[0].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[1].m_x, tri[1].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[2].m_x, tri[2].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));

        SDL_RenderGeometry(m_renderer, NULL, vertices.data(), 3, NULL, 0);
    }
    void Renderer::RenderOutlineTriangleColor(const Triangle2DC& tri) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w);
        SDL_RenderLine(m_renderer, tri[0].m_x, tri[0].m_y, tri[1].m_x, tri[1].m_y);
        SDL_RenderLine(m_renderer, tri[1].m_x, tri[1].m_y, tri[2].m_x, tri[2].m_y);
        SDL_RenderLine(m_renderer, tri[2].m_x, tri[2].m_y, tri[0].m_x, tri[0].m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderCustomFilledColor(const std::vector<Vector2C>& points, const std::vector<int>& indices) const
    {
        if (points.size() > 1)
        {
            std::vector<SDL_Vertex> vertices;

            for (const Vector2C& point : points)
            {
                vertices.push_back(SDL_Vertex(
                    SDL_FPoint(point.m_x, point.m_y),
                    SDL_FColor(point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w),
                    SDL_FPoint(0, 0)
                ));
            }
            SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), indices.data(), static_cast<int>(indices.size()));
        }
    }
    void Renderer::RenderCustomOutlineColor(const std::vector<Vector2C>& points) const
    {
        size_t size = points.size();
        if (size > 1)
        {
            for (size_t index = 0; index < size; index++)
            {
                SDL_SetRenderDrawColorFloat(m_renderer,
                    points[index].m_color.m_x, points[index].m_color.m_y, points[index].m_color.m_z, points[index].m_color.m_w
                );
                SDL_RenderLine(m_renderer,
                    points[index].m_x, points[index].m_y,
                    points[(index + 1) % size].m_x, points[(index + 1) % size].m_y
                );
            }
            SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
        }
    }

    void Renderer::CameraProjection(const std::vector<VertexUV3D>* vertices, const std::vector<int>* indices, std::vector<VertexUV2D>* drawVertices, std::vector<int>* drawIndices) const
    {
        std::vector<int> indicesConversion;
        int validIndex = 0;

        for (int index = 0; index < vertices->size(); index++)
        {
            const VertexUV3D& vertex = vertices->at(index);

            Vector3 pointVector = Vector3(m_cam->m_transform.m_pos, vertex.m_pos);

            float z = pointVector.Dot(m_cam->m_transform.m_rotMat.Forward());

            if (z < 0.00001f)
            {
                indicesConversion.push_back(-1);
                continue;
            }

            float x = pointVector.Dot(m_cam->m_transform.m_rotMat.Right());
            float y = pointVector.Dot(m_cam->m_transform.m_rotMat.Up());

            float px = x / z * m_cam->m_fovScaling / m_cam->m_aspect;
            float py = y / z * m_cam->m_fovScaling;

            Vector2 screenPos((px + 1) * 0.5f * m_cam->m_ScreenDim.m_x, (1 - py) * 0.5f * m_cam->m_ScreenDim.m_y);

            drawVertices->push_back(VertexUV2D(
                    screenPos.m_x, screenPos.m_y,
                    vertex.m_uv.m_x, vertex.m_uv.m_y
                ));

            indicesConversion.push_back(validIndex++);
        }

        for (int index = 0; index < indices->size(); index += 3)
        {
            int i0 = indices->at(index);
            int i1 = indices->at(index + 1);
            int i2 = indices->at(index + 2);

            if (indicesConversion[i0] == -1 || indicesConversion[i1] == -1 || indicesConversion[i2] == -1) { continue; }

            drawIndices->push_back(indicesConversion[i0]);
            drawIndices->push_back(indicesConversion[i1]);
            drawIndices->push_back(indicesConversion[i2]);
        }
    }

    void Renderer::Render3DCustomOutline(const std::vector<VertexUV3D>& points, const std::vector<int>& indices) const
    {
        std::vector<VertexUV2D> drawPoints;
        std::vector<int> drawIndices;

        CameraProjection(&points, &indices, &drawPoints, &drawIndices);

        for (int index = 0; index < drawIndices.size(); index += 3)
        {
            for (int i = 0; i < 3; i++)
            {
                int nextI = (i + 1) % 3;
                SDL_RenderLine(m_renderer,
                    drawPoints[drawIndices[index + i]].m_pos.m_x, drawPoints[drawIndices[index + i]].m_pos.m_y,
                    drawPoints[drawIndices[index + nextI]].m_pos.m_x, drawPoints[drawIndices[index + nextI]].m_pos.m_y
                );
            }
        }
    }
    void Renderer::Render3DCustomTexture(const std::vector<VertexUV3D>& points, const std::vector<int>& indices, const Texture* texture) const
    {
        std::vector<VertexUV2D> drawPoints;
        std::vector<int> drawIndices;

        CameraProjection(&points, &indices, &drawPoints, &drawIndices);

        std::vector<SDL_Vertex> vertices;

        for (int index = 0; index < drawPoints.size(); index++)
        {
            vertices.push_back(SDL_Vertex(
                SDL_FPoint(drawPoints[index].m_pos.m_x, drawPoints[index].m_pos.m_y),
                SDL_FColor(1.0f, 1.0f, 1.0f, 1.0f),
                SDL_FPoint(drawPoints[index].m_uv.m_x, drawPoints[index].m_uv.m_y)
            ));
        }

        SDL_RenderGeometry(
            m_renderer, texture->m_texture,
            vertices.data(), static_cast<int>(vertices.size()),
            drawIndices.data(), static_cast<int>(drawIndices.size())
        );
    }
}