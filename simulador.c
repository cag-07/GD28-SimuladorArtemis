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
