#pragma once

#include "Common/Point2.h"

#include <vector>

class UI;

namespace sf { class RenderWindow; class Drawable; }


class Widget
{
	friend class UI;

public:

	Widget();

	virtual void render(sf::RenderWindow& w) = 0;

		/// Add a child widget to this widget. Its coordinates will become relative to its parent.
	void addChild(Widget* w);

		/// Get the actual position on window of this widget, in pixels.
		/// This function walks the hierarchy and sums all positions.
	Point2 getPositionOnWindow() const;



	UI* getOwner() const { return owner; }
	Widget* getParent() const { return parent; }

	inline const Point2& getPosition() const { return position; }
	inline void setPosition(const Point2& p) { position = p; }

	inline const Point2& getSize() const { return size; }
	inline void setSize(const Point2& p) { size = p; }



private:

		/// Hierarchy-related data.
	UI* owner;
	Widget* parent;

	std::vector<Widget*> children;

protected:

		/// The position of this widget, relative to its parent.
		/// If the widget has no parent, the coordinates are relative to the window's top-left corner.
	Point2 position;

		/// The size of this widget in pixels.
	Point2 size;
};
