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
    virtual ~Entity() = default;
    Entity() = default;
    Entity(const Entity&) = default;
    Entity& operator=(const Entity& c) = default;

    virtual EntityType GetEntityType() const = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Draw() const = 0;
    
    
    // virtual void Draw() const = 0;
    // virtual bool CanPickUp(const Collider* collider) const = 0;
    // virtual bool IsPickedUp() const = 0;
    // virtual void Teleport(const Vector2f& position) = 0;
    // virtual void Throw(const Vector2f& velocity) = 0;
    // virtual void SetIsPickedUp(bool pickedUp) = 0;
    // virtual void Update(float elapsedTime) = 0;
};
