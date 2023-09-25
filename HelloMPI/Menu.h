#include "mpi.h"
#pragma once

class Menu
{
public:
	void Ring(char* arr, int count, int thread, int thread_size);
	void Broadcast(char* arr, int count, int thread, int thread_size);
	void Gather(char* arr, int count, int thread, int thread_size);
	void AllToAll(char* arr, int count, int thread, int thread_size);
	void showmenu();
};
