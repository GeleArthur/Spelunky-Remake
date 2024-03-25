#pragma once
#include <vector>
#include "Collider.h"

class Tile;

class PhysicsObject
{
public:
    explicit PhysicsObject(const Vector2f& position, Collider* collider, const std::vector<std::vector<Tile>>* tiles);
    PhysicsObject(const PhysicsObject& other);
    virtual ~PhysicsObject();
    Collider* GetCollider() const;
    virtual void UpdatePhysics(float elapsedTime);

    Vector2f GetPosition() const;
    void Teleport(const Vector2f& newPosition);

    // PhysicsObject& operator=(const PhysicsObject& rhs) = delete;
    
private:
    Vector2f m_Position;
    Vector2f m_Velocity;

    Vector2f m_Gravity{0, 100};
    float m_Bounciness{0.9f};
    Collider* m_Collider;
    
    const std::vector<std::vector<Tile>>* m_WorldTiles;
    
};
