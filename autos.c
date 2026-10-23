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
           fscanf(archivo, "%29s %29s %c %d %f %d",
                  autoLeido.marca,
                  autoLeido.modelo,
                  &autoLeido.tipo,
                  &autoLeido.ano,
                  &autoLeido.precio,
                  &disponible) == 6) {

        if (autoLeido.tipo == 'C' ||
            autoLeido.tipo == 'S' ||
            autoLeido.tipo == 'D') {

            if (autoLeido.ano > 1885) {

                if (autoLeido.precio > 0 &&
                    autoLeido.precio <= 135000000) {

                    if (disponible == 0 || disponible == 1) {
                        autoLeido.disponible = (disponible == 1);
                        autos[numAutos] = autoLeido;
                        numAutos++;
                    } else {
                        printf("Error: disponibilidad invalida en datos.txt.\n");
                    }

                } else {
                    printf("Error: precio invalido en datos.txt.\n");
                }

            } else {
                printf("Error: año invalido en datos.txt.\n");
            }

        } else {
            printf("Error: tipo invalido en datos.txt.\n");
        }
    }

    fclose(archivo);

    if (numAutos == 100) {
        printf("Se alcanzo el limite de 100 autos.\n");
    }

    printf("Se cargaron %d autos validos desde datos.txt.\n", numAutos);

    return numAutos;
}

int agregarauto(Auto autos[], int numAutos) {
    if (numAutos >= 100) {
        printf("No se pueden agregar mas autos.\n");
        return numAutos;
    }

    fflush(stdin);

    Auto nuevoAuto;

    printf("Ingrese la marca: ");
    scanf("%29s", nuevoAuto.marca);

    printf("Ingrese el modelo: ");
    scanf("%29s", nuevoAuto.modelo);

    do {
        printf("\n-TIPOS DE AUTO -\n");
        printf("C - Coupe: generalmente tiene dos puertas y un diseño deportivo.\n");
        printf("S - Sedan: suele tener cuatro puertas y un baul separado.\n");
        printf("D - Deportivo: prioriza el rendimiento y las prestaciones.\n");
        printf("Ingrese el tipo de auto (C, S o D): ");

        scanf(" %c", &nuevoAuto.tipo);

        if (nuevoAuto.tipo != 'C' &&
            nuevoAuto.tipo != 'S' &&
            nuevoAuto.tipo != 'D') {
            printf("Error: tipo invalido. Ingrese C, S o D.\n");
        }

    } while (nuevoAuto.tipo != 'C' &&
             nuevoAuto.tipo != 'S' &&
             nuevoAuto.tipo != 'D');

    int resultado;

    do {
        printf("Ingrese el año (mayor a 1885): ");
        resultado = scanf("%d", &nuevoAuto.ano);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero entero.\n");
            fflush(stdin);
            nuevoAuto.ano = 0;
        }  else if (nuevoAuto.ano <= 1885 || nuevoAuto.ano > 2026) {
    printf("Error: año invalido. Ingrese un año entre 1886 y 2026.\n");
}

    } while (nuevoAuto.ano <= 1885 || nuevoAuto.ano > 2026);

    do {
        printf("Ingrese el precio (mayor a 0 y hasta 135000000): ");
        resultado = scanf("%f", &nuevoAuto.precio);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero.\n");
            fflush(stdin);
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
            fflush(stdin);
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

    fprintf(archivo, "%s %s %c %d %.2f %d\n",
            nuevoAuto.marca,
            nuevoAuto.modelo,
            nuevoAuto.tipo,
            nuevoAuto.ano,
            nuevoAuto.precio,
            nuevoAuto.disponible);

    fclose(archivo);

    autos[numAutos] = nuevoAuto;
    numAutos++;

    printf("Auto agregado correctamente.\n");

    return numAutos;
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
                listarAutos();
                break;

            case 3:
                listarAutosSegunCondicion();
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

                default:
    printf("Opcion invalida. Ingrese una opcion del 1 al 6.\n");
    break;
        }
        

    } while (opcion != 6);

    return 0;
}