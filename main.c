// main.c
// Módulo Principal — Simulador de Reingreso Artemis
// Integrantes: Fleitas, Zarate, González, Solís
#include <stdio.h>
#include <math.h>
#include "simulador.h"
#include "validaciones.h"

void mostrarMenu(void) {
    printf("\n");
    printf("==========================================================\n");
    printf("     SIMULADOR DE REINGRESO ARTEMIS - CAPSULA ORION\n");
    printf("==========================================================\n");
    printf("  1. Configurar parametros de la mision\n");
    printf("  2. Simular reingreso completo\n");
    printf("  3. Calcular trabajo de rozamiento atmosferico\n");
    printf("  4. Calcular desaceleracion media\n");
    printf("  5. Calcular fuerza de amerizaje\n");
    printf("  6. Analizar angulo de reingreso\n");
    printf("  7. Ver reporte final de la mision\n");
    printf("  0. Salir del simulador\n");
    printf("==========================================================\n");
}
int main() {
    Capsula capsula;
    ResultadoSimulacion resultado;
    int opcion;
    int simulacionEjecutada = 0;
    inicializarCapsula(&capsula);
    printf("Bienvenido al Simulador de Reingreso Atmosferico Artemis\n");
    printf("Capsula Orion - Mision de retorno lunar\n");
    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion", 0, 7);
        switch (opcion) {
            case 1:
                configurarCapsula(&capsula);
                break;
            case 2:
                ejecutarSimulacionCompleta(&capsula, &resultado);
                simulacionEjecutada = resultado.reingresoSeguro;
                break;
            case 3: {
                double trabajo = calcularTrabajoRozamiento(
                    capsula.masa,
                    capsula.velocidadInicial,
                    capsula.velocidadFinal);

                printf("\nTrabajo de rozamiento: %.2e J\n", trabajo);
                printf("Energia disipada: %.2e J\n", fabs(trabajo));
                break;
            }
            case 4: {
                if (capsula.tiempoDesaceleracion <= 0) {
                    printf("Error: el tiempo debe ser mayor que cero.\n");
                    break;
                }

                double desaceleracion = calcularDesaceleracionMedia(
                    capsula.velocidadInicial,
                    capsula.velocidadFinal,
                    capsula.tiempoDesaceleracion);

                double fuerzasG = calcularFuerzasG(desaceleracion);

                printf("\nDesaceleracion media: %.2f m/s2\n", desaceleracion);
                printf("Fuerzas G: %.2f g\n", fuerzasG);

                if (fuerzasG > 10.0) {
                    printf("ALERTA: supera el limite de referencia de 10 g.\n");
                } else if (fuerzasG > 6.0) {
                    printf("ADVERTENCIA: fuerzas G elevadas.\n");
                } else {
                    printf("Dentro del limite de referencia del simulador.\n");
                }
                break;
            }
            case 5: {
                printf("\n--- CALCULO: FUERZA DE AMERIZAJE ---\n");
                printf("  Usando: masa=%.1f kg, Vimpacto=%.1f m/s, d=%.2f m\n",
                       capsula.masa, capsula.velocidadImpacto,
                       capsula.profundidadHundimiento);

                if (capsula.profundidadHundimiento <= 0) {
                    printf("  Error: la profundidad de hundimiento debe ser mayor a cero.\n");
                    break;
                }

                double fuerza = calcularFuerzaAmerizaje(
                    capsula.masa, capsula.velocidadImpacto,
                    capsula.profundidadHundimiento);
                double multiplo = calcularPesoMultiplo(fuerza, capsula.masa);

                printf("\n  Fuerza promedio del agua: %.2f N\n", fuerza);
                printf("  Equivale a %.2f veces el peso de la nave\n", multiplo);

                if (multiplo > 20.0) {
                    printf("  !! PELIGRO: Impacto estructuralmente peligroso !!\n");
                } else {
                    printf("  OK: Dentro de tolerancias estructurales.\n");
                }
                break;
            }
            case 6: {
                char mensaje[200];
                printf("\n--- ANALISIS: ANGULO DE REINGRESO ---\n");
                printf("  Angulo configurado: %.2f grados\n", capsula.anguloReingreso);
                printf("  Ventana segura: %.1f a %.1f grados\n", ANGULO_MIN, ANGULO_MAX);

                int seguro = analizarAnguloReingreso(capsula.anguloReingreso, mensaje);

                printf("\n  %s\n", mensaje);

                if (!seguro) {
                    printf("\n  >> La mision habria FRACASADO con este angulo.\n");
                } else {
                    printf("\n  >> La mision puede completarse exitosamente.\n");
                }
                break;
            }
            case 7:
                if (!simulacionEjecutada) {
                    printf("Debe ejecutar la simulacion primero (opcion 2).\n");
                } else {
                    mostrarReporte(&capsula, &resultado);
                }
                break;
            case 0:
                printf("\nMision finalizada. Hasta la proxima, astronauta.\n");
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
    return 0;
}
