#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define tam 100000000
#define n 5

int main(int argc, char *argv[]){

	int *a,*h_s,*h_p,i,hilos;
	double start,stop;

	hilos=atoi(argv[1]);

	a=(int *) malloc(sizeof(int)*tam);
	h_s=(int *) malloc(sizeof(int)*n);
	h_p=(int *) malloc(sizeof(int)*n);

	srand((unsigned int)time(0));

	for(i=0;i<tam;i++){
		a[i]=rand()%n;
	}

	for(i=0;i<n;i++){
		h_s[i]=0;
		h_p[i]=0;
	}


	start=omp_get_wtime();
	for(i=0;i<tam;i++){
		h_s[a[i]]++;
	}
	stop=omp_get_wtime();

	printf("Tiempo serial: %f\n",stop - start);

	omp_set_num_threads(hilos);

	/*
	start=omp_get_wtime();
	#pragma omp parallel for
	for(i=0;i<tam;i++){
		//#pragma omp critical
		h_p[a[i]]++;
	}
	stop=omp_get_wtime();
	printf("Tiempo paralelo: %f\n",stop - start);
	*/

	
	start=omp_get_wtime();
	#pragma omp parallel
	{ 
		int h_p_a[n];

		for(i=0;i<n;i++){
			h_p_a[i]=0;
		}

		#pragma omp for 
		for(i=0;i<tam;i++){
			h_p_a[a[i]]++;
		}

		#pragma omp critical
		for(i=0;i<n;i++){
			h_p[i]+=h_p_a[i];
		}

	}
	

	stop=omp_get_wtime();

	printf("Tiempo paralelo: %f\n",stop - start);


	for(i=0;i<n;i++)
		printf("%d.-%d ",i,h_s[i]);

	printf("\n");

	for(i=0;i<n;i++)
		printf("%d.-%d ",i,h_p[i]);

	return 0;
}