#pragma once
#include <vector>

struct DrawHolder;

class GizmosDrawer
{
public:
    static void Draw();
    static void DrawCircle(Vector2f position, float size, float timeToDelete = 0);
    static void DrawRect(Rectf rect, float timeToDelete = 0);
    static void DrawLine(Vector2f startPos, Vector2f endPos, float timeToDelete = 0);
private:
    static std::vector<DrawHolder*> m_Drawings;

};
