#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <stdlib.h>

void CargarPeliculas(char peliculas[][4][40]){
    FILE *peliculastxt = fopen("TXT/Peliculas.txt","r");
    char linea[160];
    int i = 0;

    while (fgets(linea, sizeof(linea), peliculastxt) != NULL && i < 10) {
        char *token = strtok(linea, ",");
        int j = 0;
        
        while (token != NULL && j < 4) {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }
            strncpy(peliculas[i][j], token, 40);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(peliculastxt);
}

int CargarClientes(char clientes[][2][40], int control){
    FILE *clientesstxt = fopen("TXT/Clientes.txt","r");
    FILE *contadoretxt = fopen("TXT/Contadores.txt","r");
    char linea[160], lineacontador[160];
    int i = 0,k = 0,valor = 0,contadorclientes = 0;

    while (fgets(lineacontador, sizeof(lineacontador), contadoretxt) != NULL && k < 1) {
        char *token = strtok(lineacontador, ",");
        int j = 0;
        
        while (token != NULL && j < 2) {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }
            if(j == 0) { 
                contadorclientes = atoi(token);
            }
            else if(j == 1){
                valor = atoi(token);
            }
            token = strtok(NULL, ",");
            j++;
        }
        k++;
    }
    fclose(contadoretxt);
    if(control == 0){
        FILE *contadortxt = fopen("TXT/Contadores.txt","w");
        fclose(contadortxt);
        FILE *contadorestxt = fopen("TXT/Contadores.txt","a");
        fprintf(contadorestxt, "%d,%d\n",contadorclientes+1,valor);
        fclose(contadorestxt);
    }

    while (fgets(linea, sizeof(linea), clientesstxt) != NULL && i < contadorclientes) {
        char *token = strtok(linea, ",");
        int j = 0;
        
        while (token != NULL && j < 4) {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }
            strncpy(clientes[i][j], token, 40);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(clientesstxt);
    return contadorclientes;
}

int CargarReservas(int reserva[][4], int contadorreserva, int control){
    FILE *reservastxt = fopen("TXT/Reservas.txt","r");
    FILE *contadoretxt = fopen("TXT/Contadores.txt","r");
    char lineacontador[160];
    int k = 0, valor = 0;     

    while (fgets(lineacontador, sizeof(lineacontador), contadoretxt) != NULL && k < 1) {
        char *token = strtok(lineacontador, ",");
        int j = 0;
        
        while (token != NULL && j < 2) {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }
            if(j == 1) { 
                contadorreserva = atoi(token);
            }
            else if(j == 0){
                valor = atoi(token);
            }
            token = strtok(NULL, ",");
            j++;
        }
        k++;
    }
    
    fclose(contadoretxt);
        if (control == 1){
        FILE *contadortxt = fopen("TXT/Contadores.txt","w");
        fclose(contadortxt);
        FILE *contadorestxt = fopen("TXT/Contadores.txt","a");
        fprintf(contadorestxt, "%d,%d\n",valor,contadorreserva);
        fclose(contadorestxt);
    }
    char linea[160];
    int fila = 0;
    int i = 0;


    while (fgets(linea, sizeof(linea), reservastxt) != NULL && fila < contadorreserva) { 
        char *token = strtok(linea, ",");
        int columna = 0;

        while (token != NULL && columna < 4) {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }
            reserva[fila][columna] = atoi(token);
            token = strtok(NULL, ",");
            columna++;
        }
        fila++;
    }

    fclose(reservastxt);
    return contadorreserva;
}

void ingresarCliente(char clientes[][2][40]){
    FILE *clientestxt;
    char nombrecliente[60],cedulacliente[60];
    printf("Ingrese nombre del nuevo cliente: ");
    scanf("%s",nombrecliente);
    printf("Ingrese cedula del nuevo cliente: ");
    scanf("%s",cedulacliente);
    clientestxt = fopen("TXT/Clientes.txt", "a");
    fprintf(clientestxt, "%s,%s\n",nombrecliente,cedulacliente);
    fclose(clientestxt);
    imprimirClientes(clientes);
}

void imprimirClientes(char clientes[][2][40]){
    int control = 1;
    int k = CargarClientes(clientes,control);
    for (int i = 0; i < k; i++)
    {
        printf("%s\t\t%s\n",clientes[i][0],clientes[i][1]);
    }   
}

void listarPeliculas(char peliculas[][4][40]){
    for (int i = 0; i < 10; i++)
    {
        printf("%s\t%s\t%s\t%s\n",peliculas[i][0],peliculas[i][1],peliculas[i][2],peliculas[i][3]);
    }   
    printf("\n");
}

void buscarporNombre(char peliculas[][4][40]){
    char nombrepelicula[30];
    int found = -1;
    printf("Ingrese en nombre de la pelicula\n>>");
    getchar();
    fgets(nombrepelicula,sizeof(nombrepelicula),stdin);

    size_t len = strlen(nombrepelicula);
    if (len > 0 && nombrepelicula[len - 1] == '\n') {
        nombrepelicula[len - 1] = '\0';
    }   

    for(int k = 0; k < 10;k++){
        if(strcmp(nombrepelicula,peliculas[k][1])==0){
            printf("Las funciones para la pelicula es:\n");
            printf("%s\t\t%s\t\t%s\n",peliculas[k][1],peliculas[k][2],peliculas[k][3]);
            found = 1;
        }
    }
    if(found == -1){
        printf("No tenenemos funciones en esta pelicula: %s\n",nombrepelicula);
    }
}

void buscarporGenero(char peliculas[][4][40]){
    char generobuscar[30];
    int found = -1;
    printf("Ingrese el genero de la pelicula\n>>");
    fgets(generobuscar,sizeof(generobuscar),stdin);
    scanf("%s",generobuscar);
    printf("Las funciones para la pelicula es:\n");
    for(int k = 0; k < 10;k++){
        if(strcmp(generobuscar,peliculas[k][3])==0){
            printf("%s\t\t%s\t\t%s\n",peliculas[k][1],peliculas[k][2],peliculas[k][3]);
            found = 1;
        }
    }
    if(found == -1){
        printf("No tenenemos funciones en este genero: %s\n",generobuscar);
    }
}

void comprarTicket(char peliculas[][4][40],double precio[], char clientes[][2][40],int reserva[][4]){

    char cedula[40];
    int found = -1,control;
    int h = CargarClientes(clientes,control=0);
    FILE *reservasrfile;
    for(int k = 0; k<10; k++){
 
        printf("Ingrese su cedula: ");
        scanf("%s", cedula);
        getchar();
        for (int i = 0; i < h; i++) {
            if (strcmp(clientes[i][1], cedula) == 0) {
                found = i;
                reserva[k][1] = i;
                break;
            }
        }

        if (found == -1) {
            printf("Cedula no encontrada.\n");
            return;
        }
            
        listarPeliculas(peliculas);
        printf("Ingrese el numero de la pelicula: ");
        scanf("%d", &reserva[k][0]);
        printf("El valor de peli es : %d\n", reserva[k][0]);

        printf("Tipos de entrada: \n 0  Normal ($7) \n 1  Ninos ($3.5) \n 2  Adulto mayor ($3)\n");
        printf("Ingrese el tipo de entrada: ");
        scanf("%d", &reserva[k][2]);
            
        printf("Ingrese la cantidad de entradas: ");
        scanf("%d", &reserva[k][3]);

        double total = reserva[k][3] * precio[reserva[k][2]];
        printf("Compra realizada exitosamente. Total: $%.2f\n", total);


        reservasrfile = fopen("TXT/Reservas.txt", "a");
        fprintf(reservasrfile, "%d,%d,%d,%d\n",found,reserva[k][0],reserva[k][2],reserva[k][3]);
        fclose(reservasrfile);
        int controles = 1,controreserva=0;
        CargarReservas(reserva,controreserva,controles);
        break;
    }
}

void verCompras(char peliculas[][4][40], double precio[], char clientes[][2][40], int reserva[][4], int contadorreserva) {
    char cedula[30];
    int control = 0;
    int indice = -1, found = -1;
    int contador = CargarReservas(reserva, contadorreserva, control);
    int clientesnumero = CargarClientes(clientes, control);

    printf("Ingrese la cedula para ver las compras\n");
    getchar();
    fgets(cedula, sizeof(cedula), stdin);

    size_t len = strlen(cedula);
    if (len > 0 && cedula[len - 1] == '\n') {
        cedula[len - 1] = '\0';
    }

    for (int y = 0; y < clientesnumero; y++) {
        if (strcmp(clientes[y][1], cedula) == 0) {
            indice = y;
            break;
        }
    }
    if (indice == -1) {
        printf("La cedula no fue encontrada\n");
        return;
    }

    for (int j = 0; j < contador; j++) {
        if((reserva[j][0]==indice)){
            printf("%s\t\t%s\t\t%.2f\t\t%d\n",peliculas[reserva[j][1]-1][1],clientes[reserva[j][0]][0],precio[reserva[j][2]],reserva[j][3]);
            found = 1;
        }
    }
    if (found == -1) {
        printf("El cliente no ha hecho alguna compra\n");
    }
}
