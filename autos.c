#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char marca[30];
    char modelo[30];
    char tipo;
    int ano;
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
        printf("Ingrese el ano (mayor a 1885): ");
        scanf("%d", &nuevoAuto.ano);
        if (nuevoAuto.ano <= 1885) {
            printf("Error: Ano invalido. Ingrese un ano posterior a 1885.\n");
        }
    } while (nuevoAuto.ano <= 1885);

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
            nuevoAuto.ano,
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
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        autoLeido.disponible = (disponible == 1);

        printf("\nMarca: %s\n", autoLeido.marca);
        printf("Modelo: %s\n", autoLeido.modelo);
        printf("Tipo: %c\n", autoLeido.tipo);
        printf("Ano: %d\n", autoLeido.ano);
        printf("Precio: %.2f\n", autoLeido.precio);
        
        if (autoLeido.disponible) {
            printf("Disponible: Si\n");
        } else {
            printf("Disponible: No\n");
        }

        cantidad++;
    }

    if (cantidad == 0) {
        printf("No hay autos registrados.\n");
    }

    fclose(archivo);
}

void listarAutosSegunCondicion() {
    int opcion = 0;

    do {
        printf("\n--- SELECCIONE UNA CONDICION ---\n");
        printf("1. Listar autos de una marca especifica\n");
        printf("2. Listar autos de 1800 A 1900\n");
        printf("3. Listar autos de 1901 A 2000\n");
        printf("4. Listar autos de 2001 A 2026\n");
        printf("5. Listar autos disponibles\n");
        printf("6. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        if (opcion >= 1 && opcion <= 5) {
            FILE *archivo = fopen("datos.txt", "r");
            if (archivo == NULL) {
                printf("No se pudo abrir el archivo (puede que aun no haya registros).\n");
            } else {
                Auto autoLeido;
                int disponible;
                int cantidad = 0;

                switch (opcion) {
                    case 1: {
                        char marcaBuscada[30];
                        printf("Ingrese la marca a buscar: ");
                        scanf("%29s", marcaBuscada);

                        while (fscanf(archivo, "%29s %29s %c %d %f %d",
                                      autoLeido.marca, autoLeido.modelo,
                                      &autoLeido.tipo, &autoLeido.ano,
                                      &autoLeido.precio, &disponible) == 6) {
                            
                            if (strcmp(autoLeido.marca, marcaBuscada) == 0) {
                                printf("\n[Encontrado] Marca: %s | Modelo: %s | Ano: %d | Precio: %.2f\n",
                                       autoLeido.marca, autoLeido.modelo, autoLeido.ano, autoLeido.precio);
                                cantidad++;
                            }
                        }
                        break;
                    }
                    case 2: {
                        while (fscanf(archivo, "%29s %29s %c %d %f %d",
                                      autoLeido.marca, autoLeido.modelo,
                                      &autoLeido.tipo, &autoLeido.ano,
                                      &autoLeido.precio, &disponible) == 6) {
                            if (autoLeido.ano >= 1800 && autoLeido.ano <= 1900) {
                                printf("\n[1800-1900] Marca: %s | Modelo: %s | Ano: %d\n",
                                       autoLeido.marca, autoLeido.modelo, autoLeido.ano);
                                cantidad++;
                            }
                        }
                        break;
                    }
                    case 3: {
                        while (fscanf(archivo, "%29s %29s %c %d %f %d",
                                      autoLeido.marca, autoLeido.modelo,
                                      &autoLeido.tipo, &autoLeido.ano,
                                      &autoLeido.precio, &disponible) == 6) {
                            if (autoLeido.ano >= 1901 && autoLeido.ano <= 2000) {
                                printf("\n[1901-2000] Marca: %s | Modelo: %s | Ano: %d\n",
                                       autoLeido.marca, autoLeido.modelo, autoLeido.ano);
                                cantidad++;
                            }
                        }
                        break;
                    }
                    case 4: {
                        while (fscanf(archivo, "%29s %29s %c %d %f %d",
                                      autoLeido.marca, autoLeido.modelo,
                                      &autoLeido.tipo, &autoLeido.ano,
                                      &autoLeido.precio, &disponible) == 6) {
                            if (autoLeido.ano >= 2001 && autoLeido.ano <= 2026) {
                                printf("\n[2001-2026] Marca: %s | Modelo: %s | Ano: %d\n",
                                       autoLeido.marca, autoLeido.modelo, autoLeido.ano);
                                cantidad++;
                            }
                        }
                        break;
                    }
                    case 5: {
                        while (fscanf(archivo, "%29s %29s %c %d %f %d",
                                      autoLeido.marca, autoLeido.modelo,
                                      &autoLeido.tipo, &autoLeido.ano,
                                      &autoLeido.precio, &disponible) == 6) {
                            if (disponible == 1) {
                                printf("\n[Disponible] Marca: %s | Modelo: %s | Ano: %d\n",
                                       autoLeido.marca, autoLeido.modelo, autoLeido.ano);
                                cantidad++;
                            }
                        }
                        break;
                    }
                }

                if (cantidad == 0) {
                    printf("\nNo se encontraron autos que cumplan con esa condicion.\n");
                }

                fclose(archivo);
            }
        } else {
            if (opcion != 6) {
                printf("Opcion invalida.\n");
            }
        }

    } while (opcion != 6);
}
void autobuscar() {
    printf("Ingrese la marca del auto a buscar: ");
    char marcaBuscada[30];
    scanf("%29s", marcaBuscada);

    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
    } else {
        Auto autoLeido;
        int disponible;
        int cantidad = 0;

        while (fscanf(archivo, "%29s %29s %c %d %f %d",
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
                printf("Ano: %d\n", autoLeido.ano);
                printf("Precio: %.2f\n", autoLeido.precio);
                printf("Disponible: %s\n", disponible == 1 ? "Si" : "No");
                cantidad++;
            }
        }

        if (cantidad == 0) {
            printf("No se encontraron autos de la marca %s.\n", marcaBuscada);
        }

        fclose(archivo);
    }
}
void listardisponibilidad() {
    FILE *archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir datos.txt.\n");
    } else {
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
        } else {
            Auto autoLeido;
            int disponible;
            int cantidadDisponibles = 0;
            int cantidadNoDisponibles = 0;

            printf("\n--- AUTOS DISPONIBLES ---\n");

            // Procesar y guardar disponibles / no disponibles
            while (fscanf(archivo, "%29s %29s %c %d %f %d",
                        autoLeido.marca,
                        autoLeido.modelo,
                        &autoLeido.tipo,
                        &autoLeido.ano,
                        &autoLeido.precio,
                        &disponible) == 6) {

                if (disponible == 1) {
                    cantidadDisponibles++;

                    fprintf(disponibles, "%s %s %c %d %.2f %d\n",
                            autoLeido.marca,
                            autoLeido.modelo,
                            autoLeido.tipo,
                            autoLeido.ano,
                            autoLeido.precio,
                            disponible);

                    printf("Marca: %s | Modelo: %s | Tipo: %c | Ano: %d | Precio: %.2f | Disponible: Si\n",
                           autoLeido.marca,
                           autoLeido.modelo,
                           autoLeido.tipo,
                           autoLeido.ano,
                           autoLeido.precio);

                } else {
                    cantidadNoDisponibles++;

                    fprintf(noDisponibles, "%s %s %c %d %.2f %d\n",
                            autoLeido.marca,
                            autoLeido.modelo,
                            autoLeido.tipo,
                            autoLeido.ano,
                            autoLeido.precio,
                            disponible);
                }
            }

            fclose(archivo);

         
        }
    }
}
int menu() {
    int opcion;
    printf("\n--- MENU PRINCIPAL ---\n");
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
                listarAutosSegunCondicion();
                break;
            case 4:
            case 5:
                printf("Funcionalidad en desarrollo.\n");
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