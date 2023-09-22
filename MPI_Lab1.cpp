#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include "Lab1.h"
#include "Lab2.h"

using namespace std;

int main(int argc, char* argv[])
{
    char choice;
    Lab1 Number1;

    MPI_Init(&argc, &argv);
    

    //Lab1
	for (;;) 
	{   
        do 
        {
            Number1.showmenu();
            cin >> choice;

        } while (!Number1.isvalid(choice));

        if (choice == 'q') break;
        cout << "\n";
        
        Number1.chooseMenuLab1(choice);
	}

    MPI_Finalize();

    return 0;
}
