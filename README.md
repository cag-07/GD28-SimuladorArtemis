# Simulador de Reingreso Artemis — Cápsula Orion

## Integrantes
| Nombre | Legajo |
|---|---|
| Fleitas | 29759 |
| Zarate | 29841 |
| González | 28764 |
| Solís | 25598 |

**Comisión:** K1.4-ISI "D"  
**Materia:** Algoritmos y Estructuras de Datos — UTN FRRe  

---

## Escenario Artemis Asignado
**Situación-Problema 4:** Reingreso Atmosférico, Frenado Aerodinámico y Amerizaje.

---

## Estructura del Proyecto
- `main.c`: Menú interactivo y flujo de control.
- `simulador.h`: Declaración de tipos, constantes físicas y prototipos.
- `simulador.c`: Funciones de cálculos físicos, simulación y reporte.
- `validaciones.h` / `validaciones.c`: Módulo de entrada blindada contra errores de usuario.
- `Makefile`: Script para compilación limpia con GCC.

---

## Compilación y Ejecución
En la carpeta donde se encuentran todos los archivos, abrir un terminal Powershell (Shift + Click derecho) y ejecutar el comando make:
```bash
make
./simulador
```
O compilación manual:
```bash
gcc -Wall -Wextra -o simulador main.c simulador.c validaciones.c -lm
./simulador
```

---

## Video de Presentación
https://www.youtube.com/playlist?list=PLV1gl3RQPZ-0

---

## Registro de uso de Inteligencia Artificial

Durante el desarrollo del proyecto utilizamos ChatGPT principalmente como una herramienta de consulta y organización.

Al principio, nos ayudó a elaborar un cronograma de trabajo para distribuir las tareas entre los integrantes, establecer qué debía hacer cada uno y organizar los avances del proyecto.

También lo utilizamos para aclarar algunas dudas sobre el lenguaje C, comprender mejor ciertas funciones y consultar posibles soluciones cuando aparecían errores.

En cuanto a la programación, intentamos desarrollar el código por nuestra cuenta, utilizando la IA como apoyo en momentos puntuales para revisar errores o entender mejor algunos procedimientos.

La organización, las decisiones sobre el funcionamiento del simulador, las pruebas y la integración de los módulos fueron realizadas por los integrantes del equipo.
