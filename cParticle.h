#pragma once
class cParticle
{
	//Attributes
protected:
	bool _alive;
	float _gravity;
	short int _lifespan;
	short int _currLife;
	short int _tick;
	sRGBA _colour;
	sPos _position;
	sVect _vect;

public:
	//Properties
	void setup(void);
	void setLifespan(int max = 9000);
	void setPosition(int x = SCREEN_WIDTH / 2, int y = SCREEN_HEIGHT / 2);
	void setRGBA(float r = 1.00, float g = 0.00, float b = 0.00, float a = 1.00);
	void setVelocity(float x = -1.00, float y = 2.00);
	void setSpeed(float x = 1.00, float y = 1.20);
	void setGravity(float g = 2.00);
	void setTickCount(void);
	void setCurrLife(void);
	//void setSize(void); //enable this for a static particle effect, else it's more of a "sparkle"

	bool isAlive();
	int GetLife();
	int getCurrentLife();
	sRGBA getRGBA();
	sPos getPosition();

	//Constructors
	cParticle();
	~cParticle();

	//Methods
	float RNG(float, float);
	int RNG(int, int);
	void updateExistence();
	void updateCurrentLife();
	void updatePosition();
	void increaseGravity(float g = 0.08);
	void decreaseXVelocity();
	void fadeAlpha();
	void drawParticle();
	void killParticle();
};