#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int tamano;
int nivel;

void merge(int arreglo1[], int n1, int arreglo2[], int n2, int arreglo3[])
{
    int x1=0, x2=0, x3=0;
 
    while (x1<n1 && x2<n2) {
        if (arreglo1[x1]<arreglo2[x2]) {
            arreglo3[x3] = arreglo1[x1];
            x1++;
        } else {
            arreglo3[x3] = arreglo2[x2];
            x2++;
        }
        x3++;
    }
    while (x1<n1) {
        arreglo3[x3] = arreglo1[x1];
        x1++;
        x3++;
    }
    while (x2<n2) {
        arreglo3[x3] = arreglo2[x2];
        x2++;
        x3++;
    }
}
 
void mergesort_s(int *vector, int n)
{
    int *vector1, *vector2, n1, n2,x,y;
    if (n>1)
    {
        if (n%2 == 0)
            n1=n2=(int) n / 2;
        else
        {
            n1=(int) n / 2;
            n2=n1+1;
        }

        vector1=(int *) malloc(sizeof(int)*n1);
        vector2=(int *) malloc(sizeof(int)*n2);

        for(x=0;x<n1;x++)
            vector1[x]=vector[x];
        for(y=0;y<n2;x++,y++)
            vector2[y]=vector[x];

        mergesort_s(vector1, n1);
        mergesort_s(vector2, n2);

        merge(vector1, n1, vector2, n2, vector);

        free(vector1);
        free(vector2);
    }    
}


void mergesort_p(int *vector, int n)
{
    int *vector1, *vector2, n1, n2,x,y;
    if (n>1)
    {
        if (n%2 == 0)
            n1=n2=(int) n / 2;
        else
        {
            n1=(int) n / 2;
            n2=n1+1;
        }

        vector1=(int *) malloc(sizeof(int)*n1);
        vector2=(int *) malloc(sizeof(int)*n2);

        for(x=0;x<n1;x++)
            vector1[x]=vector[x];
        for(y=0;y<n2;x++,y++)
            vector2[y]=vector[x];

        
            #pragma omp parallel sections
            {
                #pragma omp section
                mergesort_s(vector1, n1);
                #pragma omp section
                mergesort_s(vector2, n2);
            }
        
        merge(vector1, n1, vector2, n2, vector);
        free(vector1);
        free(vector2);
    }    
}


 
int main(int argc, char *argv[]){
    int i,*vector_s,*vector_p,hilos;
    double start, stop;

    hilos=atoi(argv[2]);
    tamano=atoi(argv[1]);

    vector_s=(int *) malloc(sizeof(int)*tamano);
    vector_p=(int *) malloc(sizeof(int)*tamano);

    srand((unsigned int)time(0));

    omp_set_num_threads(hilos);

    for(i=0;i<tamano;i++){
        vector_p[i]=vector_s[i]=rand()%tamano;
        //printf("%i,", vector_p[i]);
    }
    
    start=omp_get_wtime();
    mergesort_s(vector_s,tamano);
    stop=omp_get_wtime();

    printf("\n");
 
    //for(i=0;i<tamano;i++)
     //   printf("%i,", vector_s[i]);

    printf("\nTiempo Serial: %f\n",stop - start);


    start=omp_get_wtime();
    mergesort_p(vector_p,tamano);
    stop=omp_get_wtime();

    //for(i=0;i<tamano;i++)
    //    printf("%i,", vector_p[i]);

    printf("\nTiempo Paralelo: %f\n",stop - start);

 
    return 0;
}