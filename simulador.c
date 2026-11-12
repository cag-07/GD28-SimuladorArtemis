#include "simulador.h"
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