#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* argonMat = nist->FindOrBuildMaterial("G4_lAr");

    G4Box* worldBox = new G4Box("World", 1*m, 1*m, 1*m);
    G4LogicalVolume* worldLogic = new G4LogicalVolume(
                                                    worldBox, // its solid 
                                                    worldMat, // its material
                                                    "World"); // its name

    G4VPhysicalVolume* worldPhys = new G4PVPlacement(
                                                    0,                  // no rotation
                                                    G4ThreeVector(),    // at (0,0,0)
                                                    worldLogic,         // its logical volume
                                                    "World",            // its name
                                                    0,                  // its mother  volume
                                                    false,              // no boolean operation
                                                    0);                 // copy number

    G4Box* cube = new G4Box("ArgonCube", 10*cm, 10*cm, 10*cm);
    G4LogicalVolume* cubeLogic = new G4LogicalVolume(
                                                    cube,          // its solid
                                                    argonMat,      // its material
                                                    "ArgonCube");  // its name

    new G4PVPlacement(
                     0,                     // no rotation
                     G4ThreeVector(0,0,0),  // at (0,0,0)
                     cubeLogic,             // its logical volume
                     "ArgonCube",           // its name
                     worldLogic,            // its mother  volume
                     false,                 // no boolean operation
                     0);                    // copy number


    return worldPhys;
}
