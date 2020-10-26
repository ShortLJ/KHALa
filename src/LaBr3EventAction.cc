#include "LaBr3EventAction.hh"
#include "LaBr3RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

//#include "G4SDManager.hh"
//#include "G4HCofThisEvent.hh"
//#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

LaBr3EventAction::LaBr3EventAction(LaBr3RunAction *runAction):G4UserEventAction(),fEventEdep(0.)
{ }


LaBr3EventAction::~LaBr3EventAction()
{ }


void LaBr3EventAction::BeginOfEventAction(const G4Event* /*evt*/){ 

	fEventEdep = 0.;

}


void LaBr3EventAction::EndOfEventAction(const G4Event* event){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	if(fEventEdep>100*keV)	analysisManager->FillH1(0, fEventEdep);
	analysisManager->FillNtupleDColumn(1, 0, fEventEdep);
	analysisManager->AddNtupleRow(1);


	//Hits collections
	//G4HCofThisEvent *HCE = evt->GetHCofThisEvent();
	//if(!HCE) return;

	// Get hits collections IDs
	//if(fCollID_cryst < 0){
	//	G4SDManager *SDMan = G4SDManager::GetSDMpointer();  
	//	fCollID_cryst   = SDMan->GetCollectionID("crystal/edep");
	//	fCollID_patient = SDMan->GetCollectionID("patient/dose");    
	//}
//20200817 durlRkwl
	//Energy in crystals : identify 'good events'
	//const G4double eThreshold = 10*keV;
	//G4int nbOfFired = 0;

	//G4THitsMap<G4double> *evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_cryst));

	//std::map<G4int,G4double*>::iterator itr;
	//for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
		///G4int copyNb  = (itr->first);
		//G4double edep = *(itr->second);
		//if (edep > eThreshold) nbOfFired++;
		///G4cout << "\n  cryst" << copyNb << ": " << edep/keV << " keV ";
	//}  
	//if (nbOfFired == 2) fRunAction->CountEvent();

	//Dose deposit in patient
	//
	//G4double dose = 0.;

	//evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_patient));

	//for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
		///G4int copyNb  = (itr->first);
		//dose = *(itr->second);
	//}
	//if (dose > 0.) fRunAction->SumDose(dose);
}  


