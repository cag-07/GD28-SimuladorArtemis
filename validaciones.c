// validaciones.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validaciones.h"

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leerEntero(const char *mensaje, int min, int max) {
    int valor;
    int resultado;

    do {
        printf("%s [%d - %d]: ", mensaje, min, max);
        resultado = scanf("%d", &valor);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero entero.\n");
            limpiarBuffer();
        } else if (valor < min || valor > max) {
            printf("Error: el valor debe estar entre %d y %d.\n", min, max);
        }

    } while (resultado != 1 || (resultado == 1 && (valor < min || valor > max)));

    limpiarBuffer();
    return valor;
}

double leerDouble(const char *mensaje, double min, double max) {
    double valor;
    int resultado;

    do {
        printf("%s [%.2f - %.2f]: ", mensaje, min, max);
        resultado = scanf("%lf", &valor);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero valido.\n");
            limpiarBuffer();
        } else if (valor < min || valor > max) {
            printf("Error: el valor debe estar entre %.2f y %.2f.\n", min, max);
        }

    } while (resultado != 1 || (resultado == 1 && (valor < min || valor > max)));

    limpiarBuffer();
    return valor;
}

double leerDoublePositivo(const char *mensaje) {
    double valor;
    int resultado;

    do {
        printf("%s (> 0): ", mensaje);
        resultado = scanf("%lf", &valor);

        if (resultado != 1) {
            printf("Error: debe ingresar un numero valido.\n");
            limpiarBuffer();
        } else if (valor <= 0) {
            printf("Error: el valor debe ser mayor a cero.\n");
        }

    } while (resultado != 1 || (resultado == 1 && valor <= 0));

    limpiarBuffer();
    return valor;
}

char leerCaracter(const char *mensaje, const char *opcionesValidas) {
    char valor;
    int resultado;
    int valido;

    do {
        printf("%s [%s]: ", mensaje, opcionesValidas);
        resultado = scanf(" %c", &valor);

        valido = (resultado == 1 &&
                  strchr(opcionesValidas, valor) != NULL);

        if (!valido) {
            printf("Error: opcion no valida.\n");
            if (resultado != 1) {
                limpiarBuffer();
            }
        }

    } while (!valido);

    limpiarBuffer();
    return valor;
}

void pausar(void) {
    printf("\nPresione Enter para continuar...");
    getchar();
}

void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


