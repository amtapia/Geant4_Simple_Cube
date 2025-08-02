#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

int main(int argc, char** argv) {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserInitialization(new ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/execute init_vis.mac");

    ui->SessionStart();

    delete visManager;
    delete runManager;
    delete ui;
    return 0;
}
