#include "mpi.h"
#pragma once

class Lab1
{
	int Ring();
	int Broadcast();
	int Gather();
	int AllToAll();

	public:	
		bool isvalid(char what);
		int chooseMenuLab1(char ch);
		void showmenu();
};

