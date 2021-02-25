#include "stdafx.h"
#include "linkedList.h"

extern cRenderClass graphics;

//Creates a new node
void linkedList::CreateNode()
{
	//Create a new node
	node *temp = new node;

	//Increase _count
	_count++;

	//set the next attribute of node to null on creation
	temp->next = NULL;

	//if head is null, the head is the current node, and the tail is also the current node
	if (head == NULL) {
		head = temp;
		tail = temp;
	}
	//if not null, the tail is set to the temp node
	else {
		tail->next = temp;
		tail = temp;
	}
}

//Runs through linked list
void linkedList::TraverseList()
{
	//Create a new node
	node * temp;

	//Set the new node to the head of the list
	temp = head;

	//MaxCount variable used to compare to _count, to start the explosion again
	_deadParticle = 0;

	//While the temp node isn't NULL (so not the end of the list), enter loop
	while (temp != NULL)
	{
		//If the particle is still alive, update the existence - fade, position, re-draw
		if (temp->particle.isAlive()) {
			temp->particle.updateExistence();
		}
		//If the particle is dead, increase the maxcount variable
		else {
			_deadParticle++;
		}
		//If the amount of dead particles is greater or equal to the count, we know all particles are
		//dead, so sets the list to empty
		if (_deadParticle >= _count)
		{
			SetEmpty();
		}
		//Moves along the linked list
		temp = temp->next;
	}
}

//Returns _count attribute
short int linkedList::GetCount()
{
	//Returns the _count variable, used for the memory management in the emitter
	return _count;
}

//Checks if list is full
bool linkedList::IsFull()
{
	//If the linked list is full, return true
	if (_full == true) {
		return true;
	}
	else {
		return false;
	}
}

//Sets list to full
void linkedList::SetFull()
{
	//Sets the linked list to full
	_full = true;
}

//Sets list to empty
void linkedList::SetEmpty()
{
	//Sets the linked list to empty
	_full = false;
}

//Frees up the memory from the list
void linkedList::EmptyList()
{
	node * temp;

	//While not at the end of the linked list, removes each node
	//starting from the beginning (head)
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

linkedList::linkedList()
	: head(NULL), tail(NULL), _count(0), _full(false)
{
}

linkedList::~linkedList()
{
}
