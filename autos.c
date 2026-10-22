#include <stdio.h>
#include <stdbool.h>

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
        printf("No se pueden agregar mas autos.\n");
        return;
    }

    fflush(stdin);

    Auto nuevoAuto;

    printf("Ingrese la marca: ");
    scanf("%29s", nuevoAuto.marca);

    printf("Ingrese el modelo: ");
    scanf("%29s", nuevoAuto.modelo);

    printf("Ingrese el tipo (C, S, D): ");
    scanf(" %c", &nuevoAuto.tipo);

    do {
        printf("Ingrese el año (mayor a 1885): ");
        scanf("%d", &nuevoAuto.año);
        if (nuevoAuto.año <= 1885) {
            printf("Error: Año invalido. Ingrese un año posterior a 1885.\n");
        }
    } while (nuevoAuto.año <= 1885);

    do {
        printf("Ingrese el precio (mayor a 0): ");
        scanf("%f", &nuevoAuto.precio);
        if (nuevoAuto.precio <= 0) {
            printf("Error: El precio debe ser mayor a 0.\n");
        }
    } while (nuevoAuto.precio <= 0);

    int disponible;
    int i = 0;
    while(i < 10){
        printf("Esta disponible? (1 = Si, 0 = No): ");
        scanf("%d", &disponible);
        if(disponible == 1 || disponible == 0){
            i = 10;
        } else {
            printf("Ingrese un valor valido.\n");
        }
    }

    nuevoAuto.disponible = (disponible == 1);

    FILE *archivo = fopen("datos.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s %s %c %d %.2f %d\n",
            nuevoAuto.marca,
            nuevoAuto.modelo,
            nuevoAuto.tipo,
            nuevoAuto.año,
            nuevoAuto.precio,
            nuevoAuto.disponible);

    fclose(archivo);

    autos[*numAutos] = nuevoAuto;
    (*numAutos)++;

    printf("Auto agregado correctamente.\n");
}

void listarAutos() {
    FILE *archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
        return;
    }

    Auto autoLeido;
    int cantidad = 0;
    int disponible;

    while (fscanf(archivo, "%29s %29s %c %d %f %d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.año,
                  &autoLeido.precio,
                  &disponible) == 6) {

        autoLeido.disponible = (disponible == 1);

        printf("\nMarca: %s\n", autoLeido.marca);
        printf("Modelo: %s\n", autoLeido.modelo);
        printf("Tipo: %c\n", autoLeido.tipo);
        printf("Año: %d\n", autoLeido.año);
        printf("Precio: %.2f\n", autoLeido.precio);
        printf("Disponible: %s\n",
               autoLeido.disponible ? "Si" : "No");

        cantidad++;
    }

    if (cantidad == 0) {
        printf("No hay autos registrados.\n");
    }

    fclose(archivo);
}

int menu() {
    int opcion;
    printf("\nMENUUU\n");
    printf("1. Agregar auto\n");
    printf("2. Listar todos los autos\n");
    printf("3. Listar autos segun una condicion\n");
    printf("4. Buscar un auto\n");
    printf("5. Separar autos segun disponibilidad\n");
    printf("6. Salir\n");
    printf("Ingrese una opcion: ");

    scanf("%d", &opcion);
    return opcion;
}

int main() {
    Auto autos[100];
    int numAutos = 0;
    int opcion;
    
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                agregarAuto(autos, &numAutos);
                break;
            case 2:
                listarAutos();
                break;
            case 3:
            case 4:
            case 5:
                printf("Esta opcion todavia no esta programada.\n");
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion incorrecta.\n");
        }

    } while (opcion != 6);

    return 0;
}
