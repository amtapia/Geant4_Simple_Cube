#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutrinoPhysics.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

// NOTE on forced-collision biasing (tried and reverted):
//
// The real nu_e weak-interaction cross sections (~1e-44 to 1e-39 cm^2) make
// an actual interaction in a 20 cm liquid argon cube statistically
// invisible even across thousands of events. G4BOptrForceCollision
// (G4GenericBiasingPhysics + G4BOptrForceCollision, attached to the
// ArgonCube) was tried to force an interaction every event, following the
// pattern from Geant4's GB02 example.
//
// It uncovered what looks like a bug in G4NeutrinoPhysics (new in Geant4
// 11.2): whichever interaction process actually fires (nuElectron or
// elNuNucleus) leaves nu_e at exactly Ekin = 0 afterwards, and something in
// the tracking/biasing bookkeeping then re-queries that process's cross
// section at that now-zero energy, which falls outside the cross-section
// table's valid range and raises a fatal G4Exception (had001,
// G4CrossSectionDataStore::GetIsoCrossSection). This reproduced regardless
// of which process was forced and regardless of the primary energy (tested
// 5, 50, 500 MeV) — i.e. it isn't a biasing setup mistake, it would
// eventually hit any run where one of these processes actually interacts,
// biased or not.
//
// So: this PhysicsList only sets up G4NeutrinoPhysics and confirms (via the
// diagnostic dump below) that its processes are correctly attached to
// nu_e. It doesn't try to force or otherwise make an interaction visible.

PhysicsList::PhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4NeutrinoPhysics());
}

void PhysicsList::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();

    // Diagnostic: confirm which processes G4NeutrinoPhysics attached to nu_e.
    auto particle = G4ParticleTable::GetParticleTable()->FindParticle("nu_e");
    auto processManager = particle ? particle->GetProcessManager() : nullptr;
    if (!processManager) {
        G4cout << "[PhysicsList] WARNING: no process manager found for nu_e" << G4endl;
        return;
    }

    G4ProcessVector* processes = processManager->GetProcessList();
    G4cout << "[PhysicsList] Processes attached to nu_e (" << processes->size() << "):" << G4endl;
    for (size_t i = 0; i < processes->size(); ++i) {
        G4cout << "  - " << (*processes)[i]->GetProcessName() << G4endl;
    }
}
