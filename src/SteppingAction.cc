#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto volume = step->GetPreStepPoint()->GetPhysicalVolume();
    if (!volume || volume->GetName() != "ArgonCube") return;

    G4double edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.) return;

    const G4Track* track = step->GetTrack();
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();

    G4cout << "[ArgonCube] " << track->GetParticleDefinition()->GetParticleName()
           << " deposited " << edep / keV << " keV (weight " << track->GetWeight()
           << ") via process " << (process ? process->GetProcessName() : "N/A") << G4endl;
}
