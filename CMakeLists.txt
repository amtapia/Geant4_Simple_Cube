cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(SimpleGeant4)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

add_executable(main main.cc
    src/DetectorConstruction.cc
    src/PrimaryGeneratorAction.cc
    src/ActionInitialization.cc
    src/PhysicsList.cc
    src/SteppingAction.cc
)

target_include_directories(main PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(main ${Geant4_LIBRARIES})
