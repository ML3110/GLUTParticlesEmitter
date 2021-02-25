#include "stdafx.h"
#include "cEmitter.h"
#include <Windows.h>
#include <mmsystem.h>

extern cRenderClass graphics;

cEmitter::cEmitter()
{
	//http://forums.codeguru.com/showthread.php?262506-Get-process-memory-size
	memset(&MemStat, 0, sizeof(MemStat));
	::GlobalMemoryStatus(&MemStat);

	//Gets the physical memory 
	_memoryAvailable = MemStat.dwAvailPhys/1024/*RNG(5000,8000)*/;

	//If there's not enough memory available, produce an error and exit.
	if (_memoryAvailable <= sizeof(node)) {
		printf_s("Error. Not enough memory");
		exit(0);
	}

	//If the free memory is greater than the maximum memory required, 
	//create up to the maximum memory amount.
	if (_memoryAvailable > MAX_MEMORY_ALLOCATION) {
		for (int i = 0; i < (MAX_MEMORY_ALLOCATION / sizeof(node)); i++) {
			list.CreateNode();
		}
	} 

	//If not, go up to the limit available
	else {
		for (int i = 0; i < (_memoryAvailable / sizeof(node)); i++) {
			list.CreateNode();
		}
	}

	//Set the list as full now
	list.SetFull();
	
	//Un-comment below code for output in cmd
	int maxNodesAvailabile = _memoryAvailable / sizeof(node);
	printf_s("Nodes created:\t%i\r\nMaximum memory allocation:\t%i\r\nPhys. memory available:\t%i\r\nMax nodes available:\t%i\r\n\r\n", list.GetCount(), MAX_MEMORY_ALLOCATION, _memoryAvailable, maxNodesAvailabile);
}

cEmitter::~cEmitter()
{
}

void cEmitter::accelerate()
{
	//Moves the emitter up the screen, as if to emulate a rocket firing up from the ground
	_position._py += _gravity;
}

void cEmitter::explode()
{
	//While the linked list is full, run through the list and re-render the scene
	while (list.IsFull()) {
		list.TraverseList();
		graphics.render();
	}
	//Once the list is empty, delete all nodes from list to free up memory
	list.EmptyList();
}