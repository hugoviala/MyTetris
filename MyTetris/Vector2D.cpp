#include "Vector2D.h"


Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(m_x + v.getX(), m_x + v.getY());
}

Vector2D Vector2D::operator*(float scalar) const
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;

	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(m_x - v.getX(), m_y - v.getY());
}

Vector2D Vector2D::operator/(float scalar) const
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;

	return *this;
}


void Vector2D::normalize()
{
	float l = length();
	if (l > 0)
	{
		(*this) /= 1 / l;
	}
}


Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
	v1.setX(v1.getX() + v2.getX());
	v1.setY(v1.getY() + v2.getY());

	return v1;
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
	v1.setX(v1.getX() - v2.getX());
	v1.setY(v1.getY() - v2.getY());

	return v1;
}


