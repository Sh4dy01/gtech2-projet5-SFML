#pragma once

class Point2
{
public:

	Point2(int x = 0, int y = 0);

	Point2 operator+(const Point2& other);
	void operator+=(const Point2& other);

public:

	int x;
	int y;
};
