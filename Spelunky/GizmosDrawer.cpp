#include "pch.h"
#include "GizmosDrawer.h"

#include "Game.h"
#include "GlobalValues.h"

#include "Texture.h"
#include "utils.h"

std::vector<DrawHolder*> GizmosDrawer::m_Drawings;
Color4f GizmosDrawer::m_CurrentColor{1,1,1,1};
TTF_Font* GizmosDrawer::m_QTextFont{};

struct DrawHolder
{
    DrawHolder(const Color4f& color, const float timeDelete):
        timeToDelete(timeDelete),
        color(color)
    {
    }
    
    virtual ~DrawHolder() = default;
    virtual void Draw() = 0;
    
    float timeToDelete;
    Color4f color;
};

struct DrawCircleHolder final : public DrawHolder
{
    DrawCircleHolder(const Vector2f& pos, const float size, const Color4f& drawingColor, const float timeDelete):
        DrawHolder(drawingColor, timeDelete), pos(pos), size(size)
    {
    }
    Vector2f pos;
    float size;
    virtual void Draw() override
    {
        utils::DrawEllipse(pos, size, size);
    }
    
};

struct DrawRectHolder final : public DrawHolder
{
    Rectf rect;
    
    DrawRectHolder(const Rectf& rect, const Color4f& drawingColor, const float timeDelete):
        DrawHolder(drawingColor, timeDelete),
        rect(rect)
    {
    }

    virtual void Draw() override
    {
        utils::DrawRect(rect);
    }
};

struct DrawLineHolder final : public DrawHolder
{
    DrawLineHolder(const Vector2f& startPos, const Vector2f& endPos, const Color4f& drawingColor, const float timeDelete):
        DrawHolder(drawingColor, timeDelete), startPos(startPos), endPos(endPos)
    {
    }
    
    Vector2f startPos;
    Vector2f endPos;
    virtual void Draw() override
    {
        utils::DrawLine(startPos, endPos);
    }
};

struct DrawTextHolder final : public DrawHolder
{
    DrawTextHolder(const Vector2f& position, const std::string& text, TTF_Font* font, const Color4f& drawingColor, float timeToDelete):
        DrawHolder(drawingColor, timeToDelete), position(position), texture(new Texture(text, font, drawingColor))
    {
    }
    
    Vector2f position;
    Texture* texture;
    virtual ~DrawTextHolder() override
    {
        delete texture;
    }
    virtual void Draw() override
    {
        texture->Draw(position, Rectf{0,0, texture->GetWidth(), texture->GetHeight()});
    }
};

void GizmosDrawer::Draw()
{
    for (int i{}; i < int(m_Drawings.size()); ++i)
    {
        utils::SetColor(m_Drawings[i]->color);
        m_Drawings[i]->Draw();
    }
    
    for (int i{int(m_Drawings.size()) -1}; i >= 0; --i)
    {
        if(m_Drawings[i]->timeToDelete < Game::GetTime())
        {
            delete m_Drawings[i];
            m_Drawings.erase(std::next(m_Drawings.begin(), i));
        }
    }
}

void GizmosDrawer::SetColor(const Color4f& color)
{
    m_CurrentColor = color;
}

void GizmosDrawer::Shutdown()
{
    for (int i{}; i < m_Drawings.size(); ++i)
    {
        delete m_Drawings[i];
    }

    // if(m_QTextFont != nullptr)
        // delete m_QTextFont;
}

void GizmosDrawer::DrawCircle(const Vector2f& position, const float size, const float timeToDelete)
{
    m_Drawings.push_back(new DrawCircleHolder{position, size, m_CurrentColor, Game::GetTime() + timeToDelete});
}

void GizmosDrawer::DrawRect(const Rectf& rect, const float timeToDelete)
{
    m_Drawings.push_back(new DrawRectHolder{rect, m_CurrentColor, Game::GetTime() + timeToDelete});
}

void GizmosDrawer::DrawLine(const Vector2f& startPos, const Vector2f& endPos, const float timeToDelete)
{
    m_Drawings.push_back(new DrawLineHolder{startPos, endPos, m_CurrentColor, Game::GetTime() + timeToDelete});
}

void GizmosDrawer::DrawQText(const Vector2f& position, const std::string& text, float timeToDelete)
{
    if(m_QTextFont == nullptr) m_QTextFont = TTF_OpenFont( "arial.ttf", 16 );
    
    m_Drawings.push_back(new DrawTextHolder{position, text, m_QTextFont, m_CurrentColor, timeToDelete});
}


