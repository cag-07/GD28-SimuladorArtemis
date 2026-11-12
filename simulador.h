// simulador.h
// Módulo de Cabecera — Constantes, structs y prototipos
// Integrantes: Fleitas, Zarate, González, Solís
#ifndef SIMULADOR_H
#define SIMULADOR_H

// ═══ CONSTANTES FÍSICAS ═══
#define GRAVEDAD 9.81
#define MASA_DEFAULT 10400.0
#define VI_DEFAULT 11000.0
#define VF_PARACAIDAS 25.0
#define V_IMPACTO_DEFAULT 8.0
#define ALT_REINGRESO 120000.0
#define ALT_PARACAIDAS 2500.0
#define ANGULO_MIN 5.5
#define ANGULO_MAX 7.0
#define PROFUNDIDAD_DEFAULT 1.5

// ═══ STRUCTS ═══
typedef struct {
    double masa;
    double velocidadInicial;
    double velocidadFinal;
    double velocidadImpacto;
    double altitudReingreso;
    double altitudParacaidas;
    double anguloReingreso;
    double tiempoDesaceleracion;
    double profundidadHundimiento;
} Capsula;

typedef struct {
    double trabajoRozamiento;
    double desaceleracionMedia;
    double fuerzasG;
    double fuerzaAmerizaje;
    double pesoMultiplo;
    int reingresoSeguro;
    char mensajeAngulo[200];
} ResultadoSimulacion;

// ═══ PROTOTIPOS ═══
double calcularTrabajoRozamiento(double masa, double vi, double vf);
double calcularDesaceleracionMedia(double vi, double vf, double dt);
double calcularFuerzasG(double desaceleracion);
double calcularFuerzaAmerizaje(double masa, double vImpacto, double profundidad);
double calcularPesoMultiplo(double fuerzaAmerizaje, double masa);
int analizarAnguloReingreso(double angulo, char *mensajeSalida);
void inicializarCapsula(Capsula *cap);
void configurarCapsula(Capsula *cap);
void ejecutarSimulacionCompleta(Capsula *cap, ResultadoSimulacion *res);
void mostrarReporte(const Capsula *cap, const ResultadoSimulacion *res);

#endif
