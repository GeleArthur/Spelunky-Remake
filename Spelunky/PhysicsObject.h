#pragma once
#include <vector>
#include "Collider.h"

// class Tile;

// TODO: Rework into collision physics components
// class PhysicsObject
// {
// public:
//     explicit PhysicsObject(Collider* collider, const std::vector<std::vector<Tile>>* tiles);
//     virtual ~PhysicsObject();
//     PhysicsObject(const PhysicsObject& other);
//     PhysicsObject& operator=(const PhysicsObject& other);
//     
//     Collider* GetCollider() const;
//     virtual void UpdatePhysics(float elapsedTime);
//
//     static bool pauseAllPhysicsDebug;
//
// protected:
//     Vector2f m_Velocity;
//     Vector2f m_Gravity{0, 4000};
//     
//     float m_Bounciness{0.9f};
//     Collider* m_Collider;
//     bool m_IsOnGround{};
//     
//     const std::vector<std::vector<Tile>>* m_WorldTiles;
// };
