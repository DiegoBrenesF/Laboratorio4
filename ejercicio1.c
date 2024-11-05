#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  Funcion para reservar la matriz en memoria dinamica.

  Params
  -int*** matrix: Triple puntero para la matriz que sera creada.
  -int size: Tamano de la matriz (numero de filas y columnas)

  Retorno
  -No retorna un valor, reserva memoria para la matriz.
*/
void allocateMatrix (int*** matrix, int size){

     *matrix = (int**)malloc(size*sizeof(int*));
     //Pointer guard
     if (*matrix == NULL){
        printf ("Error: No se pudo asignar memoria para filas.\n");
        return;
     }

     for (int i=0; i < size; i++){
         *(*matrix+i) = (int*)malloc(size*sizeof(int));
         //Pointer guard
         if (*(*matrix+i) == NULL){
            printf ("Error: No se pudo asignar memoria para columnnas de la fila %d.", i);
            //Liberacion de memoria asiganada hasta el momento del error.
            for (int j=0; j < i; j++){
                free((*matrix)[j]);
            }
            free (*matrix);
            return;
         }
     }

}

/*
  Funcion para llenar la matriz con unos y ceros de forma aleatoria.

  Params
  -int** matrix: Puntero a la matriz a llenar.
  -int size: Tamano de la matriz (numero de filas y columnas)

  Retorno
  -No retorna un valor. Llena la matriz con valores (1s y 0s) aleatorios.
*/
void fillMatrix (int **matrix, int size){
     for (int i=0; i < size; i++){
         for (int j=0; j < size; j++){
             *(*(matrix+i)+j) = rand()%2;
         }
     }
}

/*
  Funcion para encontrar la longitud de la linea mas larga de unos en una matriz
  cuadrada de tamano size.

  Params
  -int** matrix: Puntero a la matriz  cuadrada de enteros.
  -int size: Tamano de la matriz (numero de filas y columnas)
  -int* result: Puntero donde se almacenara la longitud de la secuencia mas
                larga de unos.
  Retorno
  -No retorna un valor, pero modifica el valor en result.
*/
void findLargestLine (int** matrix, int size, int* result){
     int max=0;
     int sum=0;
     int ant=0;
     for (int i=0; i<size; i++){
         for (int j=0; j<size; j++){
             if (*(*(matrix+i)+j)==1 && ant==1){
                sum++;
             }
             if (*(*(matrix+i)+j)==0){
                if (sum>max){
                   max=sum;
                }
             sum=0;
             }
             ant= *(*(matrix+i)+j);
         }
     }
     max++;
     *result = max;
}

/*
  Funcion para imprimir la matriz.

  Params
  -int** matrix: Puntero a la matriz que se va imprimir.
  -int size: Tamano de la matriz (numero de filas y columnas)

  Retorno
  -No retorna un valor. Imprime la matriz en la salida estandar.
*/
void printMatrix (int** matrix, int size){
     printf ("Matrix (%dX%d)\n\n", size, size);
     for (int i=0; i < size; i++){
         for (int j=0; j < size; j++){
             printf ("%d", *(*(matrix+i)+j));
         }
         printf ("\n");
     }
}

/*
  Funcion para liberar la memoria asigna a la matriz.

  Params
  -int** matrix: Puntero a la matriz que se va a liberar.
  -int size: Tamano de la matriz (numero de filas y columnas)

  Retorno
  -No retorna un valor. Libera la memoria utilizada por la matriz.
*/
void freeMatrix (int** matrix, int size){
     for (int i=0; i<size; i++){
         free(matrix[i]);
     }
     free (matrix);
}


/*
  Funcion para mostrar menu principal.

  Params
  -No recibe parametros.

  Retorno
  -No retorna un valor. Muestrae el menu principal.
*/
void vistaPrincipal(){
     printf ("\nMenu\n\n");
     printf ("1 - Laboratorio #4\n");
     printf ("0 - Salir del programa\n");
     printf ("Ingrese una opcion: ");
}


/*
  Funcion para mostrar menu de la opcion 1.

  Params
  -No recibe parametros.

  Retorno
  -No retorna un valor. Muestrae el menu de la opcion 1.
*/
void vista1(){
     printf ("\nLaboratorio 4\n");
     printf ("Ejercicio 1\n\n");
     printf ("Ingrese el tamano de la matriz: ");
}


/*
  Funcion para calcular la matriz transpuesta y la secuencia mas larga de 1s de la transpuesta.

  Params
  -int** matrix: Puntero a la matriz a la que se le va calcular la transpuesta.
  -int size: Tamano de la matriz (numero de filas y columnas)

  Retorno
  -No retorna un valor. Imprime la matriz transpuesta y la secuencia mas larga de 1s que tiene.
*/
void puntoCuatro (int** matrix, int size){
     int **tempo = NULL;
     int* var = (int*)malloc(sizeof(int));
     allocateMatrix (&tempo, size);
     for (int i=0; i<size; i++){
         for (int j=0; j<size; j++){
             *(*(tempo+j)+i) = *(*(matrix+i)+j);
         }
     }
     printf ("\nMatriz transpuesta\n");
     printMatrix (tempo, size);
     findLargestLine (tempo, size, var);
     printf ("\nEl tamano de la secuencia de 1s mas larga de la matriz transpuesta es: %d.\n", *var);
     freeMatrix (tempo, size);
     free (var);
}

/*
  Funcion para manejar la logica de los menus (principal y opcion 1).

  Params
  -No recibe parametros.

  Retorno
  -No retorna un valor. Controla la logica del menu principal y de la opcion 1.
*/
void controlPrincipal(){

    char* opcion = (char*)malloc(sizeof(char));

    if (!opcion){
       printf ("Error de asignacion de memoria en la funcion controlPrincipal.\n");
    }

    do {
       vistaPrincipal();
       scanf ("%c", opcion);
       while (getchar() != '\n'); //Limpieza de buffer.
       switch (*opcion){
              case '1':
                       int* largestLine = (int*)malloc(sizeof(int));
                       int* size = (int*)malloc(sizeof(int));
                       int **matrix = NULL;
                       vista1();
                       scanf ("%d", size);
                       printf ("\nSolicitando memoria  dinamica para la matriz.\n");
                       allocateMatrix (&matrix,*size);
                       printf ("\nRellando aleatoriamente de 0s y 1s la matriz.\n\n");
                       fillMatrix (matrix, *size);
                       printMatrix (matrix, *size);
                       findLargestLine (matrix, *size, largestLine);
                       printf ("\nEl tamano de la secuencia de 1s mas larga es: %d.\n", *largestLine);
                       puntoCuatro (matrix, *size);
                       printf ("\nLiberando memoria dinamica utilizada en la opcion 1.\n");
                       freeMatrix (matrix, *size);
                       free (size);
                       free (largestLine);
                       while (getchar() != '\n');//Limpieza de buffer.
                       break;
              case '0':
                       break;
              default:
                      printf ("\nOpcion invalida. Solo se puede ingresar los numeros 0 o 1.\n");
       }

    } while(*opcion != '0');
    printf ("\nLiberando memoria  dinamica utilizada en la funcion controlPrincipal.\n");
    free (opcion);
    printf ("\nPrograma terminado.\n\n");
}

int main (){

    srand(time(0));//Semilla para generacion de numeros aleatorios.

    controlPrincipal();

}
