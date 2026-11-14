# Simulador de Reingreso Artemis — Cápsula Orion

## Integrantes
| Nombre | Legajo |
|---|---|
| Fleitas | 29759 |
| Zarate | 29841 |
| González | 28764 |
| Solís | 25598 |

**Comisión:** [completar]  
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
[Enlace al video de YouTube / Drive / Loom]

---

## Uso de Inteligencia Artificial
[Completado por Fleitas en Paso 19]
