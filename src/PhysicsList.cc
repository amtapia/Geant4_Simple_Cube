#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutrinoPhysics.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

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
