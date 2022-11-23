#pragma once

class Point2
{
public:

	Point2(int x = 0, int y = 0);
	
		/// Arithmetic operators.
	Point2 operator+(const Point2& other);
	void operator+=(const Point2& other);

	Point2 operator-(const Point2& other);
	void operator-=(const Point2& other);

		/// Negate operator.
	Point2 operator-();



public:

	int x;
	int y;
};
