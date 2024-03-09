#include "pch.h"
#include "Vector2i.h"

#include <iomanip>
#include <ios>
#include <sstream>

//-----------------------------------------------------------------
// Vector2i Constructors
//-----------------------------------------------------------------
Vector2i::Vector2i( )
	:Vector2i{ 0, 0 }
{
}

Vector2i::Vector2i(const int x, const int y )
	: x{ x }
	, y{ y }
{
}
//
// Vector2i Vector2i::FromTo(const Vector2i& fromPoint, const Vector2i& toPoint)
// {
// 	return Vector2i{ toPoint.x - fromPoint.x, toPoint.y - fromPoint.y };
// }

// -------------------------
// Methods
// -------------------------

std::string Vector2i::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision( 2 );
	buffer << "Vector2i(" <<  x  << ", " <<  y  << ")";
	return buffer.str();
}

void Vector2i::Set(int newX, int newY)
{
	x = newX;
	y = newY;
}

// -------------------------
// Member operators
// -------------------------
Vector2i Vector2i::operator-( ) const
{
	return Vector2i{ -x, -y };
}
Vector2i Vector2i::operator+ ( ) const
{
	return Vector2i{ x, y };
}

Vector2i& Vector2i::operator*=(int rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2i& Vector2i::operator/=(int rhs)
{
	*this *= 1 / rhs;
	return *this;
}

Vector2i& Vector2i::operator+=(const Vector2i& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& rhs)
{
	*this += -rhs;
	return *this;
}

bool Vector2i::Equals(const Vector2i& other) const
{
	return (this->x == other.x && this->y == other.y);
}

// -------------------------
// Non-member operators
// -------------------------
Vector2i operator*( int lhs, Vector2i rhs )
{
	return rhs *= lhs;
}

Vector2i operator*( Vector2i lhs, int rhs )
{
	return lhs *= rhs;
}

Vector2i operator/( Vector2i lhs, int rhs )
{
	return lhs *= (1 / rhs);
}

Vector2i operator+( Vector2i lhs, const Vector2i& rhs )
{
	return lhs += rhs;
}

Vector2i operator-( Vector2i lhs, const Vector2i& rhs )
{
	return lhs += -rhs;
}

bool operator==( const Vector2i& lhs, const Vector2i& rhs )
{
	return ( lhs.Equals( rhs ) );
}

bool operator!=( const  Vector2i& lhs, const Vector2i& rhs )
{
	return !( lhs == rhs );
}

std::ostream& operator<< ( std::ostream& lhs, const Vector2i& rhs )
{
	lhs << rhs.ToString( );
	return lhs;
}
