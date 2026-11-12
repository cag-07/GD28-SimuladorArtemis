#include "simulador.h"
#include <stdio.h>
#include <math.h>

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
}
