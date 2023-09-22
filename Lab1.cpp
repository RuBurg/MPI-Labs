#include <iostream>
#include "Lab1.h"
#include "mpi.h"

using namespace std;

int Lab1::Ring() 
{
	return 0;
}

int Lab1::Broadcast() 
{
	return 0;
}

int Lab1::Gather() 
{
	return 0;
}

int Lab1::AllToAll() 
{
	return 0;
}

int Lab1::chooseMenuLab1(char ch)
{
	switch (ch)
	{
	case '1':
		cout << "Ring" << endl;
		Ring();
		break;
	case '2':
		cout << "Broadcast" << endl;
		Broadcast();
		break;
	case '3':
		cout << "Gather" << endl;
		Gather();
		break;
	case '4':
		cout << "All-to-all" << endl;
		AllToAll();
		break;
	}
	cout << "\n" << endl;
	return 0; 
}

bool Lab1::isvalid(char ch) {
	if (ch < '1' || ch > '4' && ch != 'q') {
		return false;
	}
	else return true;
}

void Lab1::showmenu() {
	cout << "Spravka" << endl;
	cout << "	 1. Ring\n" << endl;
	cout << "	2. Broadcast\n" << endl;
	cout << "	3. Gather\n" << endl;
	cout << "	4. All-to-all\n" << endl;
	cout << "Make your choice (q to exit): " << endl;
}