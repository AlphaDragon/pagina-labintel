#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	int id,hilos=atoi(argv[1]);

	//Definimos numero de arreglos
	omp_set_num_threads(hilos);

	//Region paralela
	#pragma omp parallel private(id) shared()
	{
		//id del hilo
		id=omp_get_thread_num();

		printf("Hilo numero: %d\n",id);
		
	}

	return 0;
}