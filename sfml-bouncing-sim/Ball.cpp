#include "Ball.h"

Ball::Ball(sf::Vector2f c, float r)
	:
	center(c),
	radius(r),
	shape(r)
{
	shape.setOrigin(sf::Vector2f(r, r)); // set origin to be the center
	shape.setPosition(c); // draw the ball at center c
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
	// moving from current center to new center requires the same vector transformation as
	// moving from old top left to new so this works
	shape.move(newPos-center); // move to new position
	center = shape.getPosition(); // set center to new center duh
}

bool Ball::isColliding(sf::Vector2f p) const
{
	sf::FloatRect boundingBox = shape.getGlobalBounds();
	return boundingBox.contains(p);
}
