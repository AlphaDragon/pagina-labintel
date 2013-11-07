#include <stdio.h>
#include <stdlib.h>

int tamano;
int nivel;
//Mezcla dos areglos ordenados en uno ordenado
void merge(int arreglo1[], int tam1, int arreglo2[], int tam2, int arreglo3[])
{
    
}

//ordenamiento recursivo serial 
void mergesort(int *vector, int n)
{
      
}



 
int main(int argc, char *argv[]){

    double vector;
    int i;

    vector=(int *) malloc(sizeof(int)*tamano);

    srand((unsigned int)time(0));

    //llenado de los arreglos

    for(i=0;i<tamano;i++){
        vector[i]=rand()%tamano;
        printf("%i,", vector[i]);
    }
    
    //llamada al metodo

    mergesort(vector,tamano);

    printf("\n");
 
    for(i=0;i<tamano;i++)
        printf("%i,", vector[i]);

    return 0;
}