#include "Game.h"

Game::Game(int w, int h)
	:
	vi(sf::Vector2f(0.f, 0.f)),
    v(vi),
    ball(ri, 20),
	width(w),
	height(h)
{
}

void Game::run(Window& wnd)
{
    events(wnd);
    // game loop
	wnd.clear();
	update(wnd);
	draw(wnd);
	wnd.display();
}

void Game::events(Window& wnd)
{
    sf::Event event;
    while (wnd.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::EventType::Closed:
            wnd.close();
            break;
        }
    }
}


// 10 pixels = 1 m
// g = 98.1 pixels/s^2
// dy = v0*dt - 1/2 * 196.2*dt^2
// dt is in seconds
void Game::update(Window& wnd)
{
    dt = clock.restart().asSeconds(); // change in time
    /*if (kbd::isKeyPressed(kbd::Space))
    {
        a.y = 98.1f; // acceleration in y is 98.1 pixels/s^2 once space is pressed
        // ball starts to fall
    }*/

    // kinematics
    r = ri + (vi * dt) + ((1 / 2.f) * (a * (dt * dt))); // xf = xi + vi*t + 1/2at^2
    v = vi + (a * dt); // vf = vi + at


    // if the ball is colliding with the walls
    // for now just reverse its velocity
    if (ball.isColliding(sf::Vector2f(r.x, height - 1)))
    {
        // bottom
        v.y = -v.y;
    }
    else if (ball.isColliding(sf::Vector2f(r.x, 0)))
    {
        // top
        v.y = -v.y;
    }
    else if (ball.isColliding(sf::Vector2f(width - 1, r.y)))
    {
        // right
        v.x = -v.x;
    }
    else if(ball.isColliding(sf::Vector2f(0,r.y)))
    {
        // left
        v.x = -v.x;
    }
    ball.move(r); // move the ball to new position r
}

void Game::draw(Window& wnd)
{
	ball.draw(wnd);
}

