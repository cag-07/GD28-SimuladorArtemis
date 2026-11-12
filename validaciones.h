// validaciones.h
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int leerEntero(const char *mensaje, int min, int max);
double leerDouble(const char *mensaje, double min, double max);
double leerDoublePositivo(const char *mensaje);
char leerCaracter(const char *mensaje, const char *opcionesValidas);
void limpiarBuffer(void);
void pausar(void);
void limpiarPantalla(void);

#endif
