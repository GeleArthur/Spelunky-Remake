#pragma once
#include <vector>

class Tile;

class PhysicsObject
{
public:
    explicit PhysicsObject(Vector2f position, const std::vector<std::vector<Tile>>& tiles);
    virtual ~PhysicsObject();
    
protected:
    Vector2f m_Position;
    Vector2f m_Velocity;
    Vector2f m_PrevPosition;

    Vector2f m_Gravity{0, 100};
    float m_Bounciness{0.9};
    
    const std::vector<std::vector<Tile>>& m_WorldTiles;
    
    virtual void UpdatePhysics(float elapsedTime);
    
private:
    
    
};
