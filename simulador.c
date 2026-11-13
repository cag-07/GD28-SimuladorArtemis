#include "simulador.h"
#include <stdio.h>
#include <math.h>
#include "validaciones.h"
double calcularTrabajoRozamiento(double masa, double vi, double vf) {
    return 0.5 * masa * (vf * vf - vi * vi);
}

/* Requiere un tiempo mayor que cero. */
double calcularDesaceleracionMedia(double vi, double vf, double dt) {
    return (vf - vi) / dt;
}

double calcularFuerzasG(double desaceleracion) {
    return fabs(desaceleracion) / GRAVEDAD;
}

void inicializarCapsula(Capsula *cap) {
    cap->masa = MASA_DEFAULT;
    cap->velocidadInicial = VI_DEFAULT;
    cap->velocidadFinal = VF_PARACAIDAS;
    cap->velocidadImpacto = V_IMPACTO_DEFAULT;
    cap->altitudReingreso = ALT_REINGRESO;
    cap->altitudParacaidas = ALT_PARACAIDAS;
    cap->anguloReingreso = 6.25;
    cap->tiempoDesaceleracion = 400.0;
    cap->profundidadHundimiento = PROFUNDIDAD_DEFAULT;
}

// ═══ CÁLCULO 3: Fuerza promedio de amerizaje ═══
// Usa Teorema Trabajo-Energía: F·d = ½m·v²  →  F = ½m·v² / d
double calcularFuerzaAmerizaje(double masa, double vImpacto, double profundidad) {
    return (0.5 * masa * vImpacto * vImpacto) / profundidad;
}

// Calcula la fuerza como múltiplo del peso de la nave
double calcularPesoMultiplo(double fuerzaAmerizaje, double masa) {
    double peso = masa * GRAVEDAD;
    return fuerzaAmerizaje / peso;
}

// ═══ CÁLCULO 4: Análisis del ángulo de reingreso ═══
// Ventana segura: 5.5° ≤ γ ≤ 7.0°
int analizarAnguloReingreso(double angulo, char *mensajeSalida) {
    if (angulo < ANGULO_MIN) {
        sprintf(mensajeSalida,
            "PELIGRO - REBOTE ATMOSFERICO (angulo %.2f grados < %.1f grados)\n"
            "  La capsula no penetra suficiente en la atmosfera.\n"
            "  Rebota como una piedra en el agua y se pierde en el espacio.\n"
            "  La tripulacion no puede regresar a la Tierra.",
            angulo, ANGULO_MIN);
        return 0;
    } else if (angulo > ANGULO_MAX) {
        sprintf(mensajeSalida,
            "PELIGRO - DESACELERACION EXCESIVA (angulo %.2f grados > %.1f grados)\n"
            "  La capsula entra demasiado empinada en la atmosfera.\n"
            "  Las fuerzas G superan el limite humano (> 10g).\n"
            "  Riesgo de aplastamiento de la tripulacion y destruccion termica.",
            angulo, ANGULO_MAX);
        return 0;
    } else {
        sprintf(mensajeSalida,
            "REINGRESO SEGURO (angulo %.2f grados, dentro de %.1f - %.1f grados)\n"
            "  La capsula entra en el corredor de reingreso correcto.\n"
            "  El escudo termico puede disipar el calor de forma controlada.\n"
            "  Las fuerzas G se mantienen dentro de limites tolerables.",
            angulo, ANGULO_MIN, ANGULO_MAX);
        return 1;
    }
}void configurarCapsula(Capsula *cap) {
    char opcion;

    printf("\n--- CONFIGURACION DE PARAMETROS DE LA MISION ---\n\n");

    printf("Valores actuales:\n");
    printf("Masa: %.1f kg\n", cap->masa);
    printf("Velocidad de reingreso: %.1f m/s\n", cap->velocidadInicial);
    printf("Velocidad paracaidas: %.1f m/s\n", cap->velocidadFinal);
    printf("Velocidad de impacto: %.1f m/s\n", cap->velocidadImpacto);
    printf("Altitud de reingreso: %.1f m\n", cap->altitudReingreso);
    printf("Altitud paracaidas: %.1f m\n", cap->altitudParacaidas);
    printf("Angulo de reingreso: %.2f grados\n", cap->anguloReingreso);
    printf("Tiempo de desaceleracion: %.1f s\n", cap->tiempoDesaceleracion);
    printf("Profundidad de hundimiento: %.2f m\n", cap->profundidadHundimiento);

    opcion = leerCaracter("\nDesea modificar los parametros? (S/N)", "SsNn");

    if (opcion == 'S' || opcion == 's') {
        cap->masa = leerDoublePositivo("Masa de la capsula (kg)");
        cap->velocidadInicial = leerDoublePositivo("Velocidad de reingreso (m/s)");
        cap->velocidadFinal = leerDouble("Velocidad paracaidas (m/s)", 1.0, cap->velocidadInicial);
        cap->velocidadImpacto = leerDouble("Velocidad de impacto (m/s)", 1.0, cap->velocidadFinal);
        cap->altitudReingreso = leerDoublePositivo("Altitud de reingreso (m)");
        cap->altitudParacaidas = leerDouble("Altitud paracaidas (m)", 0.0, cap->altitudReingreso);
        cap->anguloReingreso = leerDouble("Angulo de reingreso (grados)", 0.1, 90.0);
        cap->tiempoDesaceleracion = leerDoublePositivo("Tiempo de desaceleracion (s)");
        cap->profundidadHundimiento = leerDoublePositivo("Profundidad de hundimiento (m)");

        printf("\nParametros actualizados correctamente.\n");
    } else {
        printf("\nSe mantienen los parametros actuales.\n");
    }
}
void ejecutarSimulacionCompleta(Capsula *cap, ResultadoSimulacion *res) {
    char mensaje[1024];

    /* Limpia resultados de una simulacion anterior. */
    *res = (ResultadoSimulacion){0};

    printf("\n=== SIMULACION COMPLETA DE REINGRESO ===\n");

    if (cap->masa <= 0 ||
        cap->tiempoDesaceleracion <= 0 ||
        cap->profundidadHundimiento <= 0) {
        printf("Error: masa, tiempo y profundidad deben ser positivos.\n");
        return;
    }

    printf("\nFASE 1: Verificacion del angulo\n");
    res->reingresoSeguro = analizarAnguloReingreso(
        cap->anguloReingreso, mensaje);

    snprintf(res->mensajeAngulo, sizeof res->mensajeAngulo,
             "Angulo %.2f grados: %s",
             cap->anguloReingreso,
             res->reingresoSeguro ? "seguro" : "fuera de rango");

    printf("%s\n", mensaje);

    if (!res->reingresoSeguro) {
        printf("SIMULACION ABORTADA: angulo fuera de rango seguro.\n");
        return;
    }

    printf("\nFASE 2: Reingreso atmosferico\n");
    printf("Altitud: %.0f m -> %.0f m\n",
           cap->altitudReingreso, cap->altitudParacaidas);
    printf("Velocidad: %.1f m/s -> %.1f m/s\n",
           cap->velocidadInicial, cap->velocidadFinal);

    res->trabajoRozamiento = calcularTrabajoRozamiento(
        cap->masa, cap->velocidadInicial, cap->velocidadFinal);

    printf("Trabajo de rozamiento: %.2e J\n", res->trabajoRozamiento);
    printf("Energia disipada: %.2e J\n", fabs(res->trabajoRozamiento));

    printf("\nFASE 3: Desaceleracion\n");
    res->desaceleracionMedia = calcularDesaceleracionMedia(
        cap->velocidadInicial,
        cap->velocidadFinal,
        cap->tiempoDesaceleracion);

    res->fuerzasG = calcularFuerzasG(res->desaceleracionMedia);

    printf("Desaceleracion media: %.2f m/s2\n", res->desaceleracionMedia);
    printf("Fuerzas G: %.2f g\n", res->fuerzasG);

    printf("\nFASE 4: Despliegue de paracaidas\n");
    printf("Velocidad: %.1f m/s -> %.1f m/s\n",
           cap->velocidadFinal, cap->velocidadImpacto);

    printf("\nFASE 5: Amerizaje\n");
    res->fuerzaAmerizaje = calcularFuerzaAmerizaje(
        cap->masa, cap->velocidadImpacto, cap->profundidadHundimiento);

    res->pesoMultiplo = calcularPesoMultiplo(
        res->fuerzaAmerizaje, cap->masa);

    printf("Fuerza promedio: %.2f N\n", res->fuerzaAmerizaje);
    printf("Equivale a %.2f veces el peso\n", res->pesoMultiplo);
    printf("\nSIMULACION COMPLETADA\n");
}

void mostrarReporte(const Capsula *cap, const ResultadoSimulacion *res) {
    printf("\n");
    printf("==========================================================\n");
    printf("         REPORTE FINAL DE LA MISION ARTEMIS\n");
    printf("==========================================================\n");
    printf("\n");
    printf("  PARAMETROS DE LA MISION\n");
    printf("  --------------------------------------------------------\n");
    printf("  Masa de la capsula:           %12.1f kg\n", cap->masa);
    printf("  Velocidad de reingreso:       %12.1f m/s\n", cap->velocidadInicial);
    printf("  Velocidad paracaidas:         %12.1f m/s\n", cap->velocidadFinal);
    printf("  Velocidad de impacto:         %12.1f m/s\n", cap->velocidadImpacto);
    printf("  Altitud de reingreso:         %12.1f m\n", cap->altitudReingreso);
    printf("  Altitud paracaidas:           %12.1f m\n", cap->altitudParacaidas);
    printf("  Angulo de reingreso:          %12.2f grados\n", cap->anguloReingreso);
    printf("  Tiempo de desaceleracion:     %12.1f s\n", cap->tiempoDesaceleracion);
    printf("  Profundidad de hundimiento:   %12.2f m\n", cap->profundidadHundimiento);
    printf("\n");
    printf("  RESULTADOS DE LA SIMULACION\n");
    printf("  --------------------------------------------------------\n");
    printf("  Trabajo de rozamiento:        %15.2e J\n", res->trabajoRozamiento);
    printf("  Desaceleracion media:         %12.2f m/s2\n", res->desaceleracionMedia);
    printf("  Fuerzas G:                    %12.2f g\n", res->fuerzasG);
    printf("  Fuerza de amerizaje:          %12.2f N\n", res->fuerzaAmerizaje);
    printf("  Fuerza/Peso de la nave:       %12.2f veces\n", res->pesoMultiplo);
    printf("  Reingreso seguro:             %12s\n",
           res->reingresoSeguro ? "SI" : "NO");
    printf("\n");
    printf("  ESTADO FINAL DE LA MISION\n");
    printf("  --------------------------------------------------------\n");

    if (res->reingresoSeguro) {
        printf("  [OK] Angulo de reingreso dentro de ventana segura.\n");
    } else {
        printf("  [!!] Angulo de reingreso FUERA de ventana segura.\n");
    }

    if (res->fuerzasG <= 10.0) {
        printf("  [OK] Fuerzas G dentro de limites humanos.\n");
    } else {
        printf("  [!!] Fuerzas G EXCEDEN el limite humano.\n");
    }

    if (res->pesoMultiplo <= 20.0) {
        printf("  [OK] Fuerza de amerizaje dentro de tolerancia estructural.\n");
    } else {
        printf("  [!!] Fuerza de amerizaje EXCEDE tolerancia estructural.\n");
    }

    printf("\n==========================================================\n");
    if (res->reingresoSeguro && res->fuerzasG <= 10.0) {
        printf("  VEREDICTO: MISION EXITOSA - Tripulacion a salvo\n");
    } else {
        printf("  VEREDICTO: MISION FALLIDA - Revisar parametros\n");
    }
    printf("==========================================================\n");
}
