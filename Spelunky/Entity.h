#pragma once
enum class EntityType
{
    player,
    
    rock,
    arrow,
    
    snake
};

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(const Entity&) = default;
    Entity& operator=(const Entity& c) = default;
    Entity(Entity&& other) = default;
    Entity& operator=(Entity&& c) = default;
    
    virtual EntityType GetEntityType() const = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Draw() const = 0;
};
