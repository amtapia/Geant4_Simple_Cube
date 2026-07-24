#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto volume = step->GetPreStepPoint()->GetPhysicalVolume();
    if (!volume || volume->GetName() != "ArgonCube") return;

    const G4Track* track = step->GetTrack();
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    G4double edep = step->GetTotalEnergyDeposit();

    // Log every step inside ArgonCube (not just ones with edep > 0) to see
    // whether nu_e crosses the cube in a single step (biasing not kicking
    // in) or is being split into shorter forced-collision steps, and
    // whether any secondaries are being produced at all.
    G4cout << "[ArgonCube] step: " << track->GetParticleDefinition()->GetParticleName()
           << " trackID=" << track->GetTrackID()
           << " Ekin=" << track->GetKineticEnergy() / MeV << " MeV"
           << " stepLen=" << step->GetStepLength() / cm << " cm"
           << " edep=" << edep / keV << " keV"
           << " weight=" << track->GetWeight()
           << " proc=" << (process ? process->GetProcessName() : "N/A")
           << G4endl;
}
