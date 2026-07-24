# Geant4 Simple Cube

Proyecto de ejemplo con [Geant4](https://geant4.web.cern.ch/) que simula el disparo de una partícula primaria contra un cubo de material dentro de un volumen de aire, con visualización 3D interactiva.

## Geometría

- **World**: caja de aire (`G4_AIR`) de 1×1×1 m.
- **ArgonCube**: cubo de 20×20×20 cm de argón líquido (`G4_lAr`), ubicado en el centro del `World`.

## Partícula primaria

`PrimaryGeneratorAction` dispara un neutrino electrónico (`nu_e`) de 10 MeV desde `(0, 0, -50 cm)` en dirección `+z`, hacia el `ArgonCube`.

## Estructura del proyecto

```
.
├── main.cc                          # Punto de entrada
├── include/                         # Headers
│   ├── ActionInitialization.hh
│   ├── DetectorConstruction.hh
│   └── PrimaryGeneratorAction.hh
├── src/                              # Implementaciones
│   ├── ActionInitialization.cc
│   ├── DetectorConstruction.cc
│   └── PrimaryGeneratorAction.cc
├── init_vis.mac                     # Macro de visualización (OpenGL, 10 eventos)
├── CMakeLists.txt
└── build.sh                         # Script de compilación
```

## Requisitos

- [Geant4](https://geant4.web.cern.ch/) compilado con soporte de UI y visualización (`ui_all vis_all`)
- CMake ≥ 3.16
- Compilador de C++ compatible con Geant4

`build.sh` está preparado para macOS, asumiendo Geant4 instalado en un entorno conda (`/opt/anaconda3/envs/G4/`) y zlib de Homebrew (`/opt/homebrew/opt/zlib`). Ajusta esas rutas en `build.sh` según tu instalación si es necesario.

## Compilar y ejecutar

```bash
./build.sh
cd build
./main
```

El script `build.sh` borra cualquier carpeta `build/` previa antes de recompilar, evitando cachés de CMake desactualizadas.

Al ejecutar `./main` se abre una ventana de visualización OpenGL y se corren 10 eventos (`/run/beamOn 10`, definido en `init_vis.mac`).
