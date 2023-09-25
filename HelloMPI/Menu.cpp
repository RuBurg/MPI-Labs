#include <iostream>
#include "Menu.h"
#include "mpi.h"

using namespace std;

void Menu::Ring(char* arr, int count, int thread, int thread_size)
{
	double cpu_time_start = 0.0, cpu_time_fini;
	char* res = new char[count];

	MPI_Request request;
	MPI_Isend(arr, count, MPI_CHAR, (thread - 1 + thread_size) % thread_size, 0, MPI_COMM_WORLD, &request);
	printf("Sended from process %d; Message: %s\n", thread, arr);
	cpu_time_start = MPI_Wtime();

	MPI_Irecv(res, count, MPI_CHAR, (thread + 1) % thread_size, 0, MPI_COMM_WORLD, &request);


	MPI_Status status;

	if (MPI_Wait(&request, &status) == MPI_SUCCESS) {
		printf("Received from process %d; With process: %d,  Message: %s\n", status.MPI_SOURCE, thread, res);
		cpu_time_fini = MPI_Wtime();
		printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start));
	}


	delete[] arr;
	delete[] res;
}

void Menu::Broadcast(char* arr, int count, int thread, int thread_size)
{
	int root = 0;
	double cpu_time_start = 0.0, cpu_time_fini;

	if (thread == root) {
		for (int to_thread = 1; to_thread < thread_size; to_thread++) {
			MPI_Send(arr, count, MPI_CHAR, to_thread, 0, MPI_COMM_WORLD);
		}
		printf("Sended from process %d; Message: %s\n", root, arr);
		cpu_time_start = MPI_Wtime();
	}
	else
	{
		MPI_Status status;
		MPI_Recv(arr, count, MPI_CHAR, root, 0, MPI_COMM_WORLD, &status);
		printf("Received from process %d; With process: %d,  Message: %s\n", status.MPI_SOURCE, thread, arr);

		cpu_time_fini = MPI_Wtime();
		printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start));
	}

	delete[] arr;
}

void Menu::Gather(char* arr, int count, int thread, int thread_size)
{
	int root = 0;
	double cpu_time_start = 0.0, cpu_time_fini;
	int extErr, sizeof_char;

	if (thread == root) {
		for (int i = 1; i < thread_size; i++) {
			MPI_Status status;
			MPI_Type_get_extent(MPI_CHAR, &sizeof_char, &extErr);
			MPI_Recv(((char*)arr) + (i * count * sizeof_char), count, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
			printf("Received from process %d; With process: %d,  Message: %s\n", status.MPI_SOURCE, thread, arr);

			cpu_time_fini = MPI_Wtime();
			printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start));
		}
	}
	else {
		MPI_Send(arr, count, MPI_CHAR, root, 0, MPI_COMM_WORLD);
		printf("Sended to process %d; Message: %s\n", thread, arr);
		cpu_time_start = MPI_Wtime();
	}

	delete[] arr;
}

void Menu::AllToAll(char* arr, int count, int thread, int thread_size)
{
	int extErr, sizeof_char;
	double cpu_time_start = 0.0, cpu_time_fini;
	char* res = new char[count];

	cpu_time_start = MPI_Wtime();
	MPI_Type_get_extent(MPI_CHAR, &sizeof_char, &extErr);

	for (int i = 0; i < thread_size; i++) {
		MPI_Request request;
		MPI_Isend(arr + i * count * sizeof_char, count, MPI_CHAR, i, 0, MPI_COMM_WORLD, &request);
		printf("Sended from process %d; Message: %s\n", thread, arr);

		MPI_Irecv(res + i * count * sizeof_char, count, MPI_CHAR, i, 0, MPI_COMM_WORLD, &request);

		MPI_Status status;

		if (MPI_Wait(&request, &status) == MPI_SUCCESS) {
			printf("Received from process %d; With process: %d,  Message: %s\n", status.MPI_SOURCE, i, res);
			cpu_time_fini = MPI_Wtime();
			printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start));
		}
	}

	delete[] arr;
	delete[] res;
}

void Menu::showmenu() {
	cout << "Spravka" << endl;
	cout << "	1. Ring\n" << endl;
	cout << "	2. Broadcast\n" << endl;
	cout << "	3. Gather\n" << endl;
	cout << "	4. All-to-all\n" << endl;
	cout << "Make your choice (q to exit): " << endl;
}