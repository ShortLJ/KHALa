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

LaBr3EventAction::LaBr3EventAction(LaBr3RunAction *runAction):G4UserEventAction(),fEventEdep()
{ }


LaBr3EventAction::~LaBr3EventAction()
{ }


void LaBr3EventAction::BeginOfEventAction(const G4Event* /*evt*/){ 

	for(int i=0; i<12; i++){
		fEventEdep[i] = 0.;
	}
	fTime0 = -1.*s;
}

void LaBr3EventAction::Sumstep_EnergyDeposit(int i, G4double stepEdep, G4double time){

	// initialize t0
	if (fTime0 < 0.) fTime0 = time;

	// out of time window ?
	const G4double TimeWindow (400.*ns);
	if (std::fabs(time - fTime0) > TimeWindow) return;

	fEventEdep[i]+=stepEdep;

}

void LaBr3EventAction::EndOfEventAction(const G4Event* event){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	for(int i=0; i<12; i++){
		analysisManager->FillNtupleDColumn(1, i, fEventEdep[i]);
		if(fEventEdep[i]> 50*keV)	analysisManager->FillH1(0, fEventEdep[i]);
	}
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


