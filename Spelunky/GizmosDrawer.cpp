#include "pch.h"
#include "GizmosDrawer.h"

#include "Game.h"
#include "GlobalValues.h"
#include "utils.h"

std::vector<DrawHolder*> GizmosDrawer::m_Drawings;

struct DrawHolder
{
    virtual ~DrawHolder() = default;
    
    float timeToDelete;
    virtual void Draw() = 0;
};


struct DrawCircleHolder final : public DrawHolder
{
    DrawCircleHolder(const Vector2f pos, const float size, const float timeDelete)
    {
        this->pos = pos;
        this->size = size;
        this->timeToDelete = timeDelete;
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
    DrawRectHolder(const Rectf rect, const float timeDelete)
    {
        this->rect = rect;
        this->timeToDelete = timeDelete;
    }
    Rectf rect;
    virtual void Draw() override
    {
        utils::DrawRect(rect);
    }
};

struct DrawLineHolder final : public DrawHolder
{
    DrawLineHolder(const Vector2f startPos, const Vector2f endPos, const float timeDelete)
    {
        this->startPos = startPos;
        this->endPos = endPos;
    }
    Vector2f startPos;
    Vector2f endPos;
    virtual void Draw() override
    {
        utils::DrawLine(startPos, endPos);
    }
};

void GizmosDrawer::Draw()
{
    for (int i{}; i < m_Drawings.size(); ++i)
    {
        m_Drawings[i]->Draw();
        if(m_Drawings[i]->timeToDelete < Game::currentTime)
        {
            delete m_Drawings[i];
            m_Drawings.erase(std::next(m_Drawings.begin(), i));
        }
    }
}

void GizmosDrawer::DrawCircle(const Vector2f position, const float size, const float timeToDelete)
{
    m_Drawings.push_back(new DrawCircleHolder{position, size, Game::currentTime + timeToDelete});
}

void GizmosDrawer::DrawRect(const Rectf rect, const float timeToDelete)
{
    m_Drawings.push_back(new DrawRectHolder{rect, Game::currentTime + timeToDelete});
}

void GizmosDrawer::DrawLine(const Vector2f startPos, const Vector2f endPos, const float timeToDelete)
{
    m_Drawings.push_back(new DrawLineHolder{startPos, endPos, Game::currentTime + timeToDelete});
}
