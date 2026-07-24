# Geant4 Simple Cube

Proyecto de ejemplo con [Geant4](https://geant4.web.cern.ch/) que simula el disparo de una partícula primaria contra un cubo de material dentro de un volumen de aire, con visualización 3D interactiva.

## Geometría

- **World**: caja de aire (`G4_AIR`) de 1×1×1 m.
- **ArgonCube**: cubo de 20×20×20 cm de argón líquido (`G4_lAr`), ubicado en el centro del `World`.

## Partícula primaria

`PrimaryGeneratorAction` dispara un neutrino electrónico (`nu_e`) de 10 MeV desde `(0, 0, -50 cm)` en dirección `+z`, hacia el `ArgonCube`.

## Física de neutrinos

`PhysicsList` (en vez de la lista estándar `QGSP_BERT`, que no incluye procesos de neutrinos) registra `G4EmStandardPhysics`, `G4DecayPhysics` y `G4NeutrinoPhysics` — este último disponible desde **Geant4 ≥ 11.2** — para que el `nu_e` tenga procesos de interacción débil reales dentro del `ArgonCube`. `G4NeutrinoPhysics` adjunta a `nu_e`:

- **`nuVacOscillation`**: oscilación de neutrinos en el vacío (cambio de sabor, no deposita energía).
- **`nuElectron`**: dispersión neutrino-electrón (corriente cargada y neutra).
- **`elNuNucleus`**: dispersión neutrino-núcleo cuasi-elástica/coherente (CEvNS, formalismo de Llewellyn-Smith).

Al iniciar, `PhysicsList::ConstructProcess()` imprime en consola la lista de procesos adjuntos a `nu_e`, confirmando que quedaron correctamente registrados.

En la práctica, con un `nu_e` de pocas decenas de MeV y un cubo de 20 cm de argón líquido, la probabilidad real de que ocurra una interacción es prácticamente nula (secciones eficaces del orden de 10⁻⁴⁴–10⁻³⁹ cm²), así que no es de esperar ver depósitos de energía (`SteppingAction`) en una corrida normal — es el comportamiento físico esperado, no un error. Se intentó forzar una interacción visible con biasing (`G4GenericBiasingPhysics` + `G4BOptrForceCollision`), lo cual expuso un bug de `G4NeutrinoPhysics` (detallado como comentario en `src/PhysicsList.cc`) y por eso no quedó incluido en el proyecto.

## Estructura del proyecto

```
.
├── main.cc                          # Punto de entrada
├── include/                         # Headers
│   ├── ActionInitialization.hh
│   ├── DetectorConstruction.hh
│   ├── PhysicsList.hh
│   ├── PrimaryGeneratorAction.hh
│   └── SteppingAction.hh
├── src/                              # Implementaciones
│   ├── ActionInitialization.cc
│   ├── DetectorConstruction.cc
│   ├── PhysicsList.cc
│   ├── PrimaryGeneratorAction.cc
│   └── SteppingAction.cc
├── init_vis.mac                     # Macro de visualización (OpenGL, 10 eventos)
├── CMakeLists.txt
└── build.sh                         # Script de compilación
```

## Requisitos

- [Geant4](https://geant4.web.cern.ch/) **≥ 11.2** (requerido por `G4NeutrinoPhysics`), compilado con soporte de UI y visualización (`ui_all vis_all`)
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
