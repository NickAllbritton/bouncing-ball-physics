#pragma once
#include <utility>
#include <SFML/Graphics.hpp>

typedef sf::RenderWindow Window;

class Ball
{
public:
	Ball() = delete;
	Ball(sf::Vector2f c, float r);
	Ball(int x, int y, int r);
	Ball(float x, float y, float r);
	Ball& operator=(const Ball& rhs);
	~Ball() = default;
	void draw(Window&) const;
	void move(sf::Vector2f newPos);
	bool isColliding(sf::Vector2f p) const;
	const sf::Vector2f getCenter() const
	{
		return center;
	}
private:
	sf::Vector2f center;
	int radius;
	sf::CircleShape shape;
	sf::Color color = sf::Color::Blue;
};