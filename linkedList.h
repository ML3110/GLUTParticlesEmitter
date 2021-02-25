#pragma once
#include "cParticle.h"

//emitter that points to a list of particles

struct node {
	cParticle particle;
	node * next;
};

class linkedList
{
	//Attributes
	node *head;
	node *tail;
	short int _count;
	short int _deadParticle;
	bool _full;
public:
	//Properties

	//Constructors
	linkedList();
	~linkedList();

	//Methods
	void CreateNode();
	void TraverseList();
	short int GetCount();
	bool IsFull();
	void SetFull();
	void SetEmpty();
	void EmptyList();
};

