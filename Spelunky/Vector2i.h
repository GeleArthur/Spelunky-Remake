#pragma once
#include <ostream>

struct Vector2i final
{
	// -------------------------
	// Constructors 
	// -------------------------
	Vector2i( );
	explicit Vector2i( int x, int y );
	explicit Vector2i(const Vector2f& vector);

	virtual ~Vector2i() = default;
	Vector2i(const Vector2i& other) = default;
	Vector2i& operator=(const Vector2i& other) = default;
	Vector2i(Vector2i && other) = default;
	Vector2i& operator=(Vector2i&& other) = default;

	// -------------------------
	// Member operators
	// -------------------------
	Vector2i operator-( ) const;
	Vector2i operator+( ) const;
	Vector2i& operator*=( int rhs);
	Vector2i& operator/=( int rhs);
	Vector2i& operator+=( const Vector2i& rhs);
	Vector2i& operator-=( const Vector2i& rhs);

	// Are two vectors equal within a threshold?				
	// u.Equals(v)
	bool Equals( const Vector2i& other ) const;

	// Convert to String 
	std::string	ToString( ) const;

	// Sets the values of x and y
	void Set( int newX, int newY );

	// -------------------------
	// Datamembers 
	// -------------------------
	int x;
	int y;
};
// -------------------------
// Non member operators
// -------------------------
Vector2i operator*( int lhs, Vector2i rhs );
Vector2i operator*( Vector2i lhs, int rhs );
Vector2i operator/( Vector2i lhs, int rhs );

Vector2i operator+( Vector2i lhs, const Vector2i& rhs );
Vector2i operator-( Vector2i lhs, const Vector2i& rhs );

bool operator==( const Vector2i& lhs, const Vector2i& rhs );
bool operator!=( const  Vector2i& lhs, const Vector2i& rhs );

std::ostream& operator<< ( std::ostream& lhs, const Vector2i& rhs );

