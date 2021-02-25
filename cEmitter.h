#pragma once
#include "cParticle.h"
#include "linkedList.h"
class cEmitter : public cParticle
{
private:
	//Attributes
	linkedList list;
	MEMORYSTATUS MemStat;
	int _memoryAvailable;
public:

	//Constructors
	cEmitter();
	~cEmitter();

	//Properties

	//Methods
	void accelerate();
	void explode();
};

