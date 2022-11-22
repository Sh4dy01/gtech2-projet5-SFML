#include "Point2.h"


Point2::Point2(int x, int y)
	: x(x), y(y)
{

}

Point2 Point2::operator+(const Point2& other)
{
	return Point2(this->x + other.x, this->y + other.y);
}

void Point2::operator+=(const Point2& other)
{
	this->x += other.x;
	this->y += other.y;
}
