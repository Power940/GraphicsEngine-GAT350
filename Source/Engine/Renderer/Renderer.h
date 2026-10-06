#pragma once
#include <Math/Structs.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <string>
#include <vector>


namespace STR_FALL
{
	class Renderer
	{
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
		Color* m_lastSetColor = nullptr;
		Camera3D* m_cam = &(Camera3D::Empty);

		int m_WINDOW_WIDTH = -1;
		int m_WINDOW_HEIGHT = -1;

	public:
		bool m_useCamera2D = true;

        bool Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT, Camera3D* cam = &(Camera3D::Empty));
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void SetColor(Color c);
		void SetColorF(float r, float g, float b, float a = 1.0f);
		Color GetColor();
		void SetCamera(Camera3D* cam) { m_cam = cam; }
		Camera3D* GetCamera() { return m_cam; }
		void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
		void Clear(Color c);
		void ClearF(float r = 0, float g = 0, float b = 0, float a = 1.0f);
        void Present();
		void ShutDown();

		inline int GetSreenWidth() const { return m_WINDOW_WIDTH; }
		inline int GetSreenHeight() const { return m_WINDOW_HEIGHT; }

		void RenderDebugText(const std::string& text, const Vector2& point) const;
		void RenderTexture(const class Texture* texture, float x, float y, float angleDeg = 0.0f, float xScale = 1.0f, float yScale = 1.0f, bool flipH = false, const Vector2& origin = Vector2(0.5f, 0.5f));
		void RenderTexture(const class Texture* texture, const struct Rect2D& source, float x, float y, float angleDeg = 0.0f, float xScale = 1.0f, float yScale = 1.0f, bool flipH = false, const Vector2& origin = Vector2(0.5f, 0.5f));

		void RenderPoint(const Vector2& point) const;
		void RenderPoints(const std::vector<Vector2>& points) const;
		void RenderLine(const Line2D& line) const;
		void RenderLines(const std::vector<Line2D>& lines) const;
		void RenderFillTriangle(const Triangle2D& tri) const;
		void RenderOutlineTriangle(const Triangle2D& tri) const;
		void RenderCustomFilled(const std::vector<Vector2>& points, const std::vector<int>& indices) const;
		void RenderCustomOutline(const std::vector<Vector2>& points) const;

		void RenderPointColor(const Vector2C& point) const;
		void RenderPointsColor(const std::vector<Vector2C>& points) const;
		void RenderLineColor(const Line2DC& line) const;
		void RenderLinesColor(const std::vector<Line2DC>& lines) const;
		void RenderFillTriangleColor(const Triangle2DC& tri) const;
		void RenderOutlineTriangleColor(const Triangle2DC& tri) const;
		void RenderCustomFilledColor(const std::vector<Vector2C>& points, const std::vector<int>& indices) const;
		void RenderCustomOutlineColor(const std::vector<Vector2C>& points) const;

		void CameraProjection(const std::vector<VertexUV3D>* vertices, const std::vector<int>* indices, std::vector<VertexUV2D>* drawVertices, std::vector<int>* drawIndices) const;

		void Render3DCustomOutline(const std::vector<VertexUV3D>& points, const std::vector<int>& indices) const;
		void Render3DCustomTexture(const std::vector<VertexUV3D>& points, const std::vector<int>& indices, const class Texture* texture) const;

		friend struct Text;
		friend class Texture;
	};
}