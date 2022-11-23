#include "Widget.h"

#include "Manager/UI/UI.h"


Widget::Widget()
	: owner( 0 ), parent( 0 )
	, position(0, 0), size(100, 100)
{

}

void Widget::addChild(Widget* w)
{
	this->children.push_back(w);
	w->parent = this;
}

Point2 Widget::getPositionOnWindow() const
{
	Point2 pos = this->position;
	Widget* parent = this->parent;

	while (parent) {
		pos += parent->getPosition();
		parent = parent->getParent();
	}

	return pos;
}
