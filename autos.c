#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char marca[30];
    char modelo[30];
    char tipo;
    int año;
    float precio;
    bool disponible;
} Auto;

void agregarAuto(Auto autos[], int *numAutos) {
    if (*numAutos >= 100) {
        printf("No se pueden agregar más autos. Capacidad máxima alcanzada.\n");
        return;
    }

    Auto nuevoAuto;

    while (getchar() != '\n' && !feof(stdin));

    printf("Ingrese la marca del auto: ");
    scanf("%29s", nuevoAuto.marca);

    printf("Ingrese el modelo del auto: ");
    scanf("%29s", nuevoAuto.modelo);

    printf("Ingrese el tipo de auto (C, S, D): ");
    scanf(" %c", &nuevoAuto.tipo);

    printf("Ingrese el año del auto: ");
    scanf("%d", &nuevoAuto.año);

    printf("Ingrese el precio del auto: ");
    scanf("%f", &nuevoAuto.precio);

    int disponible;
    printf("¿Está disponible? (1 para sí, 0 para no): ");
    scanf("%d", &disponible);

    nuevoAuto.disponible = (disponible == 1);

    FILE *archivo = fopen("datos.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    } else {
        fprintf(archivo, "%s %s %c %d %.2f %d\n",
                nuevoAuto.marca,
                nuevoAuto.modelo,
                nuevoAuto.tipo,
                nuevoAuto.año,
                nuevoAuto.precio,
                nuevoAuto.disponible);

        fclose(archivo);
    }
    autos[*numAutos] = nuevoAuto;
    (*numAutos)++;

    printf("Auto agregado correctamente.\n");
}

void menu () {
    int opcion=1
    int i==1;
    while (i==1) {
        printf("=== Menú de Autos ===\n");
        printf("1. Agregar auto\n");
        printf("2. Salir\n");
scanf("%d", &opcion);
switch (opcion) {
    case 1:

        break;
    case 2:
        printf("Saliendo del programa.\n");
        break;
    default:
        printf("Opción inválida. Intente nuevamente.\n");
        break;
    }
}

int main(){

return 0;
}