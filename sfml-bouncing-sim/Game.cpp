#include "Game.h"
#include <cmath>

float operator*(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Game::Game(float width, float height)
	:
    t(0), // t = 0
    m(100), // m = 100 kg doesn't really matter tbh
    ri(100.0f, 100.0f),
    r(ri),
	vi(200.0f, 0.0f), // vi_x = 2 m/s
    v(vi),
    a(0.0f, 0.f), // a_y = 0 m/s^2
    pi(m*vi),
    p(m*v),
    h(height-r.y),
    energy(m*g*h + .5f*m*(v*v)),
    ball(ri, 20.f),
	width(width),
	height(height)
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


// 100 pixels = 1 m
// g = 981 pixels/s^2
// t is in seconds
void Game::update(Window& wnd)
{
    t += clock.restart().asSeconds(); // increment time

    if (kbd::isKeyPressed(kbd::Key::Space))
    {
        vi = sf::Vector2f(200.0f, 0.0f);
        ri = sf::Vector2f(100.f, 100.f);
        pi = m * vi;
        v = vi;
        r = ri;
        p = pi;
        t = 0;
    }

    // all things that affect path of ball
    gravity(true);
    reflectFromWalls();

    // kinematics
    r = ri + (vi * t) + ((.5f) * (a * (t * t))); // xf = xi + vi*t + 1/2at^2
    v = vi + (a * t); // vf = vi + at
    h = height - r.y;

    ball.move(r); // move the ball to new position r
}

void Game::draw(Window& wnd)
{
	ball.draw(wnd);
}

float Game::restart()
{
    float dt = t;
    t = 0;
    ri = r;
    vi = v;
    return dt;
}

void Game::reflectFromWalls()
{
    // if the ball is colliding with the walls
    // for now just reverse its velocity and start time over w new initial velocity
    // change initial position too
    if (ball.isColliding(sf::Vector2f(r.x, height - 1.f)))
    {
        // bottom
        VfromE(-.36f * energy, 1); // lose 20 percent of kinetic energy in y direction
        v.y = -v.y;
        if (v.y >= 0.f) // if the ball is somehow going down
        {
            gravity(false); // turn off gravity so it doesn't keep falling
        }
        // so the ball is no longer hitting whatever it initially hit
        r.y -= 1.f;
        restart();
    }
    else if (ball.isColliding(sf::Vector2f(r.x, 0)))
    {
        // top
        VfromE(-.1f * energy, 1); // lose 20 percent of kinetic energy in y direction
        v.y = -v.y;
        // so the ball is no longer hitting whatever it initially hit
        r.y += 1.f;
        restart();
    }
    else if (ball.isColliding(sf::Vector2f(width - 1.f, r.y)))
    {
        // right
        //VfromE(-.1f * energy, -1); // lose 20 percent of kinetic energy in x direction
        v.x = -v.x;
        // so the ball is no longer hitting whatever it initially hit
        r.x -= 1.f;
        restart();
    }
    else if (ball.isColliding(sf::Vector2f(0, r.y)))
    {
        // left
        //VfromE(-.1f * energy, -1); // lose 20 percent of kinetic energy in x direction
        v.x = -v.x;
        // so the ball is no longer hitting whatever it initially hit
        r.x += 1.f;
        restart();
    }
}

void Game::gravity(bool isActive)
{
    if (isActive && a.y != g) a.y += g;
    else if (isActive && a.y == g) return;
    else a.y -= 0.f;
}

void Game::VfromE(float dE, int dir) // 1 = y direction, -1 = x direction, 0 = both
{
    energy += dE;
    if (dir == 1) // y direction loses velocity
    {
        // take total energy - KE in x direction then solve for v.y
        v.y = std::sqrtf(2 * ((energy - (.5f * m * (v.x * v.x))) / m - g * h));
    }
    else if (dir == -1) // x direction loses velocity
    {
        // take total energy - KE in y direction then solve for v.x
        v.x = std::sqrtf(2 * ((energy - (.5f * m * (v.y * v.y))) / m - g * h));
    }
    else if (dir == 0) // both directions slow
    {
        // take total energy and solve for v then apply change to both directions
        float speed = std::sqrtf(2 * (energy / m - g * h));
        float initialSpeed = std::sqrt(v * v);
        float dv = speed - initialSpeed; // how much speed decreases in either direction
        v.x -= dv;
        v.y -= dv;
    }
}
