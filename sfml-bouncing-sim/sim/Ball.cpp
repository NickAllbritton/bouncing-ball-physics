#include "Ball.h"

Ball::Ball(sf::Vector2f c, float r)
	:
	center(c),
	radius(r),
	shape(r)
{
	shape.setPosition(c);
	shape.setFillColor(color);
}

Ball::Ball(int x, int y, int r) : Ball((float)x, (float)y, (float)r) {}

Ball::Ball(float x, float y, float r) : Ball(sf::Vector2f(x, y), r) {}

Ball& Ball::operator=(const Ball& rhs)
{
	this->center = rhs.center;
	this->radius = rhs.radius;
	return *this;
}

void Ball::draw(Window& w) const
{
	w.draw(shape);
}

void Ball::move(sf::Vector2f newPos)
{
	shape.setPosition(newPos); // move to new position
	center = shape.getPosition(); // set center to new center duh
}

bool Ball::isColliding(sf::Vector2f p) const
{
	sf::FloatRect boundingBox = shape.getGlobalBounds();
	return boundingBox.contains(p);
}
