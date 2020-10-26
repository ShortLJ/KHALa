#include "LaBr3SteppingAction.hh"
#include "LaBr3EventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

LaBr3SteppingAction::LaBr3SteppingAction(const LaBr3DetectorConstruction *detectorConstruction, LaBr3EventAction *eventAction)
	:G4UserSteppingAction(),
	fDetConstruction(detectorConstruction),
	fEventAction(eventAction)
{ }

LaBr3SteppingAction::~LaBr3SteppingAction()
{ }

void LaBr3SteppingAction::UserSteppingAction(const G4Step *step){

	//LaBr3EventAction *eventAction = (LaBr3EventAction *) G4EventManager::GetEventManager() -> GetUserEventAction();

	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	G4int volumeID = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
	G4double stepEdep = step->GetTotalEnergyDeposit();

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleIColumn(0, 0, eventID);
	analysisManager->FillNtupleIColumn(0, 1, volumeID);
	analysisManager->FillNtupleDColumn(0, 2, stepEdep);
	analysisManager->AddNtupleRow(0);

	if(volumeID==100) fEventAction->Sumstep_EnergyDeposit(stepEdep);


}
