#pragma once
#include "Ball.h"

typedef sf::Keyboard kbd;
typedef sf::Mouse mouse;

class Game
{
public:
	Game(int w, int h);
	Game() = delete;
	~Game() = default;
	void run(Window& wnd);
	void events(Window& wnd); // event loop
	void update(Window& wnd); // game logic
	void draw(Window& wnd); // drawing
private:
	Ball ball;
	int height;
	int width;
	sf::Clock clock;
	float dt = 0;
	sf::Vector2f vi; // initial velocity
	sf::Vector2f ri = sf::Vector2f(100.f, 100.f); // initial position
	sf::Vector2f r = ri; // position vector
	sf::Vector2f v; // velocity vector
	sf::Vector2f a = sf::Vector2f(0.f, 98.1f); // acceleration vector
};