#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "mpi.h"
#include "Menu.h"

using namespace std;

void randomizeString(char* array, int size) {
	for (int i = 0; i < size; ++i) {
		array[i] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 36];

		if (i == size - 1) {
			array[i] = '\0';
		}
	}

	return;
}

int main(int* argc, char** argv) {
	char choice = 'q';
	const int count = 10;
	int err, thread, thread_size;
	char* arr = new char[10];
	Menu UserMenu;

	if ((err = MPI_Init(argc, &argv)) != MPI_SUCCESS) {
		fprintf(stderr, "Ошибка No %d в процедуре MPI_Init\n", err);
		MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);
	}	

	MPI_Comm_rank(MPI_COMM_WORLD, &thread);
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size);

	if (thread == 0) {
		UserMenu.showmenu();
		choice = getchar();
	}

	// Рассылаем выбор всем процессам
	MPI_Bcast(&choice, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

	randomizeString(arr, count);

	switch (choice)
	{
	case '1':
		UserMenu.Ring(arr, count, thread, thread_size);
		break;
	case '2':
		UserMenu.Broadcast(arr, count, thread, thread_size);
		break;
	case '3':
		UserMenu.Gather(arr, count, thread, thread_size);
		break;
	case '4':
		UserMenu.AllToAll(arr, count, thread, thread_size);
		break;
	case 'q':
		exit('0');
	default:
		printf("Wrong choise \n");
		break;
	}

	MPI_Finalize();

	return 0;
}
