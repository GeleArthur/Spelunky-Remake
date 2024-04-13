#pragma once
#include <vector>
#include "SDL_ttf.h"

struct DrawHolder;

class GizmosDrawer
{
public:
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

};
