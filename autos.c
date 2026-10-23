#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char marca[30];
    char modelo[30];
    char tipo;
    int ano;
    float precio;
    bool disponible;
} Auto;

void convertirMayusculas(char texto[]) {
    int i = 0;

    while (texto[i] != '\0') {
        texto[i] = toupper(texto[i]);
        i++;
    }
}

int cargarautos(Auto autos[]) {
    FILE *archivo = fopen("datos.txt", "r");
    int numAutos = 0;
    int disponible;
    Auto autoLeido;

    if (archivo == NULL) {
        printf("No existe datos.txt o no se pudo abrir.\n");
        return 0;
    }

    while (numAutos < 100 &&
           fscanf(archivo, " %29[^;];%29[^;];%c;%d;%f;%d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        convertirMayusculas(autoLeido.marca);

        if ((autoLeido.tipo == 'C' ||
             autoLeido.tipo == 'S' ||
             autoLeido.tipo == 'D') &&
            autoLeido.ano >= 1886 &&
            autoLeido.ano <= 2026 &&
            autoLeido.precio > 0 &&
            autoLeido.precio <= 135000000 &&
            (disponible == 0 || disponible == 1)) {

            autoLeido.disponible = (disponible == 1);
            autos[numAutos] = autoLeido;
            numAutos++;

        } else {
            printf("Error: hay un auto con datos invalidos en datos.txt.\n");
        }
    }

    fclose(archivo);

    printf("Se cargaron %d autos validos desde datos.txt.\n", numAutos);

    return numAutos;
}



int agregarauto(Auto autos[], int numAutos) {
    if (numAutos >= 100) {
        printf("No se pueden agregar mas autos.\n");
        return numAutos;
    }

    Auto nuevoAuto;
    int i;
    int resultado;

    printf("Ingrese la marca: ");
    getchar();
    fgets(nuevoAuto.marca, 30, stdin);

    i = 0;
    while (nuevoAuto.marca[i] != '\0' && nuevoAuto.marca[i] != '\n') {
        nuevoAuto.marca[i] = toupper((unsigned char)nuevoAuto.marca[i]);
        i++;
    }

    if (nuevoAuto.marca[i] == '\n') {
        nuevoAuto.marca[i] = '\0';
    }

    printf("Ingrese el modelo: ");
    fgets(nuevoAuto.modelo, 30, stdin);

    i = 0;
    while (nuevoAuto.modelo[i] != '\0' && nuevoAuto.modelo[i] != '\n') {
        i++;
    }

    if (nuevoAuto.modelo[i] == '\n') {
        nuevoAuto.modelo[i] = '\0';
    }

    do {
        printf("\n-TIPOS DE AUTO-\n");
        printf("C - Coupe\n");
        printf("S - Sedan\n");
        printf("D - Deportivo\n");
        printf("Ingrese el tipo de auto (C, S o D): ");

        scanf(" %c", &nuevoAuto.tipo);
        nuevoAuto.tipo = toupper((unsigned char)nuevoAuto.tipo);

        if (nuevoAuto.tipo != 'C' &&
            nuevoAuto.tipo != 'S' &&
            nuevoAuto.tipo != 'D') {
            printf("Error: tipo invalido. Ingrese C, S o D.\n");
        }

    } while (nuevoAuto.tipo != 'C' &&
             nuevoAuto.tipo != 'S' &&
             nuevoAuto.tipo != 'D');

    do {
        printf("Ingrese el año (entre 1886 y 2026): ");
        resultado = scanf("%d", &nuevoAuto.ano);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero entero.\n");
            scanf("%*[^\n]");
            scanf("%*c");
            nuevoAuto.ano = 0;
        } else if (nuevoAuto.ano < 1886 || nuevoAuto.ano > 2026) {
            printf("Error: año invalido.\n");
        }

    } while (nuevoAuto.ano < 1886 || nuevoAuto.ano > 2026);

    do {
        printf("Ingrese el precio (mayor a 0 y hasta 135000000): ");
        resultado = scanf("%f", &nuevoAuto.precio);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero.\n");
            scanf("%*[^\n]");
            scanf("%*c");
            nuevoAuto.precio = 0;
        } else if (nuevoAuto.precio <= 0 ||
                   nuevoAuto.precio > 135000000) {
            printf("Error: precio invalido.\n");
        }

    } while (nuevoAuto.precio <= 0 ||
             nuevoAuto.precio > 135000000);

    int disponible;

    do {
        printf("Esta disponible? (1 = Si, 0 = No): ");
        resultado = scanf("%d", &disponible);

        if (resultado != 1) {
            printf("Error: debe ingresar 1 o 0.\n");
            scanf("%*[^\n]");
            scanf("%*c");
            disponible = -1;
        } else if (disponible != 1 && disponible != 0) {
            printf("Error: ingrese 1 para Si o 0 para No.\n");
        }

    } while (disponible != 1 && disponible != 0);

    nuevoAuto.disponible = (disponible == 1);

    FILE *archivo = fopen("datos.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return numAutos;
    }

    fprintf(archivo, "%s;%s;%c;%d;%.2f;%d\n",
            nuevoAuto.marca,
            nuevoAuto.modelo,
            nuevoAuto.tipo,
            nuevoAuto.ano,
            nuevoAuto.precio,
            disponible);

    fclose(archivo);

    autos[numAutos] = nuevoAuto;
    numAutos++;

    printf("Auto agregado correctamente.\n");

    return numAutos;
}





void listarautos() {
    FILE *archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
        return;
    }

    Auto autoLeido;
    int disponible;
    int cantidad = 0;

    while (fscanf(archivo, " %29[^;];%29[^;];%c;%d;%f;%d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        printf("\nMarca: %s\n", autoLeido.marca);
        printf("Modelo: %s\n", autoLeido.modelo);
        printf("Tipo: %c\n", autoLeido.tipo);
        printf("Año: %d\n", autoLeido.ano);
        printf("Precio: %.2f\n", autoLeido.precio);
        printf("Disponible: %s\n", disponible == 1 ? "Si" : "No");

        cantidad++;
    }

    if (cantidad == 0) {
        printf("No hay autos registrados.\n");
    }

    fclose(archivo);
}




void listarautosseguncondicion() {
    int opcion = 0;

    do {
        printf("\n--- SELECCIONE UNA CONDICION ---\n");
        printf("1. Listar autos de una marca especifica\n");
        printf("2. Listar autos de 1886 a 1900\n");
        printf("3. Listar autos de 1901 a 2000\n");
        printf("4. Listar autos de 2001 a 2026\n");
        printf("5. Listar autos disponibles\n");
        printf("6. Volver al menu principal\n");
        printf("Ingrese una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Debe ingresar un numero.\n");
            scanf("%*[^\n]");
            scanf("%*c");
            opcion = 0;
            continue;
        }

        if (opcion < 1 || opcion > 6) {
            printf("Opcion incorrecta.\n");
        } else if (opcion <= 5) {
            FILE *archivo = fopen("datos.txt", "r");

            if (archivo == NULL) {
                printf("No se pudo abrir datos.txt.\n");
            } else {
                Auto autoLeido;
                int disponible;
                int cantidad = 0;
                char marcaBuscada[30];

                if (opcion == 1) {
                    int i = 0;

                    printf("Ingrese la marca a buscar: ");
                    getchar();
                    fgets(marcaBuscada, 30, stdin);

                    while (marcaBuscada[i] != '\0' &&
                           marcaBuscada[i] != '\n') {
                        marcaBuscada[i] = toupper((unsigned char)marcaBuscada[i]);
                        i++;
                    }

                    if (marcaBuscada[i] == '\n') {
                        marcaBuscada[i] = '\0';
                    }
                }

                while (fscanf(archivo, " %29[^;];%29[^;];%c;%d;%f;%d",
                              autoLeido.marca,
                              autoLeido.modelo,
                              &autoLeido.tipo,
                              &autoLeido.ano,
                              &autoLeido.precio,
                              &disponible) == 6) {

                    int coincide = 0;

                    if (opcion == 1 &&
                        strcmp(autoLeido.marca, marcaBuscada) == 0) {
                        coincide = 1;
                    } else if (opcion == 2 &&
                               autoLeido.ano >= 1886 &&
                               autoLeido.ano <= 1900) {
                        coincide = 1;
                    } else if (opcion == 3 &&
                               autoLeido.ano >= 1901 &&
                               autoLeido.ano <= 2000) {
                        coincide = 1;
                    } else if (opcion == 4 &&
                               autoLeido.ano >= 2001 &&
                               autoLeido.ano <= 2026) {
                        coincide = 1;
                    } else if (opcion == 5 && disponible == 1) {
                        coincide = 1;
                    }

                    if (coincide) {
                        printf("\nMarca: %s | Modelo: %s | Año: %d | Precio: %.2f | Disponible: %s\n",
                               autoLeido.marca,
                               autoLeido.modelo,
                               autoLeido.ano,
                               autoLeido.precio,
                               disponible == 1 ? "Si" : "No");

                        cantidad++;
                    }
                }

                if (cantidad == 0) {
                    printf("No se encontraron autos que cumplan con esa condicion.\n");
                }

                fclose(archivo);
            }
        }

    } while (opcion != 6);
}



void autobuscar() {
    char marcaBuscada[30];
    int i;

    printf("Ingrese la marca del auto a buscar: ");
    getchar();
    fgets(marcaBuscada, 30, stdin);

    i = 0;
    while (marcaBuscada[i] != '\0' && marcaBuscada[i] != '\n') {
        marcaBuscada[i] = toupper((unsigned char)marcaBuscada[i]);
        i++;
    }

    if (marcaBuscada[i] == '\n') {
        marcaBuscada[i] = '\0';
    }

    FILE *archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
        return;
    }

    Auto autoLeido;
    int cantidad = 0;
    int disponible;

    while (fscanf(archivo, " %29[^;];%29[^;];%c;%d;%f;%d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        if (strcmp(autoLeido.marca, marcaBuscada) == 0) {
            printf("\nMarca: %s\n", autoLeido.marca);
            printf("Modelo: %s\n", autoLeido.modelo);
            printf("Tipo: %c\n", autoLeido.tipo);
            printf("Año: %d\n", autoLeido.ano);
            printf("Precio: %.2f\n", autoLeido.precio);
            printf("Disponible: %s\n",
                   disponible == 1 ? "Si" : "No");

            cantidad++;
        }
    }

    if (cantidad == 0) {
        printf("No se encontraron autos de la marca %s.\n",
               marcaBuscada);
    }

    fclose(archivo);
}


void listardisponibilidad() {
    FILE *archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
        return;
    }

    FILE *disponibles = fopen("disponibles.txt", "w");
    FILE *noDisponibles = fopen("no-disponibles.txt", "w");

    if (disponibles == NULL || noDisponibles == NULL) {
        printf("No se pudieron crear los archivos de disponibilidad.\n");

        if (disponibles != NULL) {
            fclose(disponibles);
        }

        if (noDisponibles != NULL) {
            fclose(noDisponibles);
        }

        fclose(archivo);
        return;
    }

    Auto autoLeido;
    int disponible;
    int cantidadDisponibles = 0;
    int cantidadNoDisponibles = 0;

    while (fscanf(archivo, " %29[^;];%29[^;];%c;%d;%f;%d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        if (disponible == 1) {
            fprintf(disponibles, "%s;%s;%c;%d;%.2f;%d\n",
                    autoLeido.marca,
                    autoLeido.modelo,
                    autoLeido.tipo,
                    autoLeido.ano,
                    autoLeido.precio,
                    disponible);

            printf("Disponible: %s %s\n",
                   autoLeido.marca, autoLeido.modelo);

            cantidadDisponibles++;

        } else if (disponible == 0) {
            fprintf(noDisponibles, "%s;%s;%c;%d;%.2f;%d\n",
                    autoLeido.marca,
                    autoLeido.modelo,
                    autoLeido.tipo,
                    autoLeido.ano,
                    autoLeido.precio,
                    disponible);

            cantidadNoDisponibles++;
        }
    }

    fclose(archivo);
    fclose(disponibles);
    fclose(noDisponibles);

    printf("\nCantidad de autos disponibles: %d\n", cantidadDisponibles);
    printf("Cantidad de autos no disponibles: %d\n", cantidadNoDisponibles);
    printf("Se actualizaron disponibles.txt y no-disponibles.txt.\n");
}



int menu() {
    int opcion;
    int resultado;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Agregar auto\n");
        printf("2. Listar todos los autos\n");
        printf("3. Listar autos segun una condicion\n");
        printf("4. Buscar un auto\n");
        printf("5. Separar autos segun disponibilidad\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");

        resultado = scanf("%d", &opcion);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero.\n");
            fflush(stdin);
            opcion = 0;
        } else if (opcion < 1 || opcion > 6) {
            printf("Opcion incorrecta. Ingrese un numero del 1 al 6.\n");
        }

    } while (opcion < 1 || opcion > 6);

    return opcion;
}


int main() {
    Auto autos[100];
    int numAutos;
    int opcion;

    numAutos = cargarautos(autos);

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                numAutos = agregarauto(autos, numAutos);
                break;

            case 2:
                listarautos();
                break;

            case 3:
                listarautosseguncondicion();
                break;

            case 4:
                autobuscar();
                break;

            case 5:
                listardisponibilidad();
                break;

            case 6:
                printf("Saliendo del programa.\n");
                break;
        }

    } while (opcion != 6);

    return 0;
}

