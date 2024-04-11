#pragma once
#include <vector>

struct DrawHolder;

class GizmosDrawer
{
public:
    static void Draw();
    static void DrawCircle(const Vector2f& position, float size, float timeToDelete = 0);
    static void DrawRect(const Rectf& rect, float timeToDelete = 0);
    static void DrawLine(const Vector2f& startPos, const Vector2f& endPos, float timeToDelete = 0);
    static void SetColor(const Color4f& color);
private:
    static std::vector<DrawHolder*> m_Drawings;
    static Color4f m_CurrentColor;

};
