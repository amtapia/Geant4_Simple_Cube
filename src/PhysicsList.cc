#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutrinoPhysics.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4BiasingProcessInterface.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

PhysicsList::PhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4NeutrinoPhysics());

    // Wrap nu_e processes so a biasing operator (see DetectorConstruction)
    // can force an interaction inside the ArgonCube: the real weak
    // interaction cross sections are far too small to see any interaction
    // in a run of a reasonable number of events otherwise.
    G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
    biasingPhysics->Bias("nu_e");
    RegisterPhysics(biasingPhysics);
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

    // Vacuum oscillation has by far the shortest interaction length of
    // nu_e's biased processes, so G4BOptrForceCollision always forces it
    // instead of the actual matter interactions (nuElectron / elNuNucleus)
    // we want to see. Oscillation carries no energy deposit anyway.
    // Deactivating it (G4ProcessManager::SetProcessActivation) had no
    // effect on the forced-collision selection, so remove it outright
    // instead. Collect the pointer during iteration and remove it only
    // after the loop, since RemoveProcess mutates the very G4ProcessVector
    // being iterated.
    G4ProcessVector* processes = processManager->GetProcessList();
    G4cout << "[PhysicsList] Processes attached to nu_e (" << processes->size() << "):" << G4endl;
    G4VProcess* oscillationProcess = nullptr;
    for (size_t i = 0; i < processes->size(); ++i) {
        G4VProcess* proc = (*processes)[i];
        G4bool isBiased = (dynamic_cast<G4BiasingProcessInterface*>(proc) != nullptr);
        G4bool isOscillation = (proc->GetProcessName().find("nuVacOscillation") != G4String::npos);
        if (isOscillation) {
            oscillationProcess = proc;
        }
        G4cout << "  - " << proc->GetProcessName()
               << (isBiased ? " [biasing-wrapped]" : "")
               << (isOscillation ? " [to be removed]" : "") << G4endl;
    }

    if (oscillationProcess) {
        processManager->RemoveProcess(oscillationProcess);
        G4cout << "[PhysicsList] Removed " << oscillationProcess->GetProcessName()
               << " from nu_e" << G4endl;
    }
}
