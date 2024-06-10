#pragma once
#include <vector>
#include "SDL_ttf.h"
#include "structs.h"

struct DrawHolder;

class GizmosDrawer final
{
public:
    explicit GizmosDrawer() = delete;
    virtual ~GizmosDrawer() = delete;
    GizmosDrawer(const GizmosDrawer& other) = delete;
    GizmosDrawer& operator=(const GizmosDrawer& other) = delete;
    GizmosDrawer( GizmosDrawer&& other) = delete;
    GizmosDrawer& operator=(GizmosDrawer&& other) = delete;

    static void SetTimePointer(float* currentTime);
    static void Draw();
    static void DrawCircle(const Vector2f& position, float size, float timeToDelete = 0);
    static void DrawRect(const Rectf& rect, float timeToDelete = 0);
    static void DrawLine(const Vector2f& startPos, const Vector2f& endPos, float timeToDelete = 0);
    static void DrawQText(const Vector2f& position, const std::string& text, float timeToDelete = 0);
    static void SetColor(const Color4f& color);
    static void Shutdown();
private:
    static std::vector<DrawHolder*> m_Drawings;
    static Color4f m_CurrentColor;
    static TTF_Font* m_QTextFont;
    static float* m_CurrentTime;

};
