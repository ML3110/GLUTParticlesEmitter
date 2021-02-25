#include "stdafx.h"
#include "cParticle.h"
#include <random>
extern cRenderClass graphics;

//Constructor
cParticle::cParticle()
//Member initialiser list
	: _lifespan(0), _currLife(0), _alive(true), _tick(0), _gravity(0)/*, _size(0)*/
{
	setup();
}

//Destructor
cParticle::~cParticle()
{
}

//Main setup function for particle
void cParticle::setup()
{
	setLifespan(RNG((int)1000, 5000));
	setPosition();
	setVelocity();
	setSpeed();
	setTickCount();
	setCurrLife();
	setGravity();
	setRGBA();
	//setSize();
}

//Sets the lifespan of the particle in milliseconds. If arg is < 1000 or > 9000, sets to default
void cParticle::setLifespan(int max)
{
	/*max > 9000 || max < 1000 ? _lifespan = 9000 : _lifespan = max;*/
	_lifespan = max;
}

//Sets particle position on X and Y axis
void cParticle::setPosition(int x, int y)
{
	_position._px = x;
	_position._py = y;
}

//Sets the RGBA struct with args, defaults or RNG
void cParticle::setRGBA(float r, float g, float b, float a)
{
	r > 0 && r < 1 ? _colour._r = r : _colour._r = RNG((float)0.00, 1.00);
	g > 0 && g < 1 ? _colour._g = g : _colour._g = RNG((float)0.00, 1.00);
	b > 0 && b < 1 ? _colour._b = b : _colour._b = RNG((float)0.00, 1.00);
	a > 0 && a < 1 ? _colour._a = a : _colour._a = 1.00;
}

//Sets the velocity for both X and Y axis
void cParticle::setVelocity(float x, float y)
{
	x > -1.00 && x < 2.00 ? _vect._velX = x : _vect._velX = RNG((float)-1.00, 2.00);
	y > 1.00 && y < 2.00 ? _vect._velY = y : _vect._velY = RNG((float)1.00, 1.50);
}

//Sets the speed for both X and Y axis
void cParticle::setSpeed(float x, float y)
{
	x > -1.00 && x < 1.00 ? _vect._speedX = x : _vect._speedX = RNG((float)-1.00, 1.00);
	y > -1.00 && y < 1.20 ? _vect._speedY = y : _vect._speedY = RNG((float)-1.00, 1.20);
}

//Sets the gravity to be applied to the Y axis velocity
void cParticle::setGravity(float g)
{
	g > -1.00 && g < 3.00 ? _gravity = g : _gravity = 2.0;
}

//Sets the current tick count of the machine
void cParticle::setTickCount()
{
	_tick = GetTickCount();
}

//Sets the current life of the particle
void cParticle::setCurrLife()
{
	_currLife = GetTickCount() - _tick;
}

////Sets the particle size to a random size
//void cParticle::setSize(void)
//{
//	graphics.setPointSize(RNG(1, 3));
//}

//Check if particle is alive
bool cParticle::isAlive()
{
	if (_alive) {
		return true;
	}
	else {
		return false;
	}
}

//Returns the particles lifespan
int cParticle::GetLife()
{
	return _lifespan;
}

//Returns particles current life
int cParticle::getCurrentLife()
{
	return _currLife;
}

//Returns the RGBA struct
sRGBA cParticle::getRGBA()
{
	return _colour;
}

//Returns particle position struct
sPos cParticle::getPosition()
{
	return _position;
}

//RNG for float values
float cParticle::RNG(float startNum, float endNum)
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_real_distribution <float> uid(startNum, endNum);
	return uid(rng);
}

//RNG for integer values
int cParticle::RNG(int startNum, int endNum)
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution <int> uid(startNum, endNum);
	return uid(rng);
}

//Update the particle with all methods
void cParticle::updateExistence()
{
	updatePosition();
	increaseGravity(0.03);
	decreaseXVelocity();
	updateCurrentLife();
	fadeAlpha();
	drawParticle();
}

//Updates the current life, or living time of the particle
void cParticle::updateCurrentLife()
{
	//If the particle is off screen, set it to inactive, else update the current life
	if (_position._px < 0 || _position._px > SCREEN_WIDTH
		|| _position._py < 0 || _position._py > SCREEN_HEIGHT) {
		killParticle();
	}
	else {
		_currLife = GetTickCount() - _tick;
		if (_currLife >= _lifespan) {
			killParticle();
		}
	}
}

//Updates the position of the particle
void cParticle::updatePosition()
{
	_position._px += (_vect._velX * _vect._speedX);
	_position._py += (_vect._velY * _vect._speedY) + _gravity;
	//graphics.setPointSize(_size);
	graphics.setPointSize(RNG(1, 4));
}

//Increases the gravity applied to the particle
void cParticle::increaseGravity(float g)
{
	g > 0 && g < 1 ? _gravity -= g : _gravity -= 0.08;
}

//Decreases velocity on x axis
void cParticle::decreaseXVelocity()
{
	if (_vect._velX > 0) {
		_vect._velX -= 0.005;
	}
}

//Fade the alpha value of the RGBA struct
void cParticle::fadeAlpha()
{
	_colour._a -= (1.00 / (GetLife() / RNG(10,50)));
	//If the alpha is fully faded, kill particle
	if (_colour._a <= 0.00) {
		killParticle();
	}
}

//Draws the particle on the screen
void cParticle::drawParticle()
{
	graphics.setColour(getRGBA()._r, getRGBA()._g, getRGBA()._b, getRGBA()._a);
	graphics.drawPixel(getPosition()._px, getPosition()._py + 1);
	graphics.drawPixel(getPosition()._px, getPosition()._py - 1);
	graphics.drawPixel(getPosition()._px + 1, getPosition()._py);
	graphics.drawPixel(getPosition()._px - 1, getPosition()._py);
}

//Kills the particle
void cParticle::killParticle()
{
	setPosition(200, 200);
	_colour._a = 0.0;
	_lifespan = 0;
	_alive = false;
}