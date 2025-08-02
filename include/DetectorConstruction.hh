#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    virtual G4VPhysicalVolume* Construct();
};

#endif
