#pragma once
#include <vector>
#include "Collider.h"

class Tile;

class PhysicsObject
{
public:
    explicit PhysicsObject(Vector2f position, const Collider& collider, const std::vector<std::vector<Tile>>* tiles);
    virtual ~PhysicsObject();
    
protected:
    Vector2f m_Velocity;
    Vector2f m_PrevPosition;

    Vector2f m_Gravity{0, 100};
    float m_Bounciness{0.9f};
    Collider m_Collider;
    
    const std::vector<std::vector<Tile>>* m_WorldTiles;
    virtual void UpdatePhysics(float elapsedTime);
    Collider& GetCollider();

    
private:
    
    
};
