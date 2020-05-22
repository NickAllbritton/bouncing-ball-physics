#pragma once
#include "Ball.h"

typedef sf::Keyboard kbd;
typedef sf::Mouse mouse;

class Game
{
public:
	Game(float w, float h);
	Game() = delete;
	~Game() = default;
	void run(Window& wnd);
	void events(Window& wnd); // event loop
	void update(Window& wnd); // game logic
	void draw(Window& wnd); // drawing
private:
	float restart(); // restart time and set initial conditions again
	// returns how much time has passed since last t = 0
	void reflectFromWalls();
	void gravity(bool isActive);
	void VfromE(float dE, int dir); // when energy is lost, velocity must be affected
private:
	float t;
	float m; // mass
	sf::Vector2f vi; // initial velocity
	sf::Vector2f ri; // initial position
	sf::Vector2f r; // position vector
	sf::Vector2f v; // velocity vector
	sf::Vector2f a; // acceleration vector
	sf::Vector2f pi; // initial momentum
	sf::Vector2f p; // momentum vector
	float h; // height of ball
	float energy;
	Ball ball;
	float height;
	float width;
	sf::Clock clock;
	static constexpr float g = 981.f;
};