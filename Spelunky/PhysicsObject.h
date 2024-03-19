#pragma once

class PhysicsObject
{
public:
    explicit PhysicsObject(Vector2f position);
    virtual ~PhysicsObject();
    
protected:
    Vector2f m_Position;
    Vector2f m_Velocity;
    Vector2f m_PrevPosition;
    virtual void UpdatePhysics(float elapsedTime);
    
private:
    
};
