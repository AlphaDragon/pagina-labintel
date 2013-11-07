#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int tamano=100000000;

int main(int argc, char *argv[]){

	int *a,*b,*c_s,*c_p,hilos,i;
	double start,stop;

	hilos=atoi(argv[1]);

    a=(int *) malloc(sizeof(int)*tamano);
    b=(int *) malloc(sizeof(int)*tamano);
    c_s=(int *) malloc(sizeof(int)*tamano);
    c_p=(int *) malloc(sizeof(int)*tamano);

    for(i=0;i<tamano;i++){
    	a[i]=i;
    	b[i]=tamano-i;
    }

    start=omp_get_wtime();
    //serial
    for(i=0;i<tamano;i++){
    	c_s[i]=a[i]+b[i];
    	//printf("%d,",c_s[i]);
    }

    stop=omp_get_wtime();

    printf("Tiempo serial: %f\n",stop - start);

    omp_set_num_threads(hilos);

    start=omp_get_wtime();
    //paralelo
   	#pragma omp parallel for 
	   	for(i=0;i<tamano;i++){
	    	c_p[i]=a[i]+b[i];
	    	//printf("%d,",c_p[i]);
	    }

	stop=omp_get_wtime();


    printf("Tiempo paralelo: %f\n",stop - start);


	return 0;
}


//www.openmp.org