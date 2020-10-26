#include "LaBr3RunAction.hh"
#include "LaBr3PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4Event.hh"
//#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"



LaBr3RunAction::LaBr3RunAction():G4UserRunAction(){  

	G4RunManager::GetRunManager()->SetPrintProgress(1);

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	G4cout << "Using " << analysisManager->GetType() << G4endl;

	analysisManager->CreateH1("E","Edep", 1000, 0., 2000*keV);

	analysisManager->CreateNtuple("step", "step");
	analysisManager->CreateNtupleIColumn("EventID");
	analysisManager->CreateNtupleIColumn("VolumeID");
	analysisManager->CreateNtupleDColumn("StepEdep");
	analysisManager->FinishNtuple();

	analysisManager->CreateNtuple("Event", "Event");
	//for(int i=0; i<12; i++){
	//	G4String columnName = Form("EventEdep%2d",i);
	//	analysisManager->CreateNtupleDColumn(1, columnName);
		//analysisManager->CreateNtupleDColumn(1,G4String(Form("EventEdep%2d",i)));
		//analysisManager->CreateNtupleDColumn(1,Form("EventEdep%2d",i));
	//}
	analysisManager->CreateNtupleDColumn( 1,"EventEdep00");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep01");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep02");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep03");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep04");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep05");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep06");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep07");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep08");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep09");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep10");
	analysisManager->CreateNtupleDColumn( 1,"EventEdep11");
	analysisManager->FinishNtuple();



}

LaBr3RunAction::~LaBr3RunAction(){
	delete G4AnalysisManager::Instance();
}


void LaBr3RunAction::BeginOfRunAction(const G4Run *run){ 

	G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

	G4String filename = "LaBr3_geant4_test";
	analysisManager->OpenFile(filename);

}


void LaBr3RunAction::EndOfRunAction(const G4Run *run){
	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	if (analysisManager->GetH1(1)){
		G4cout << G4endl << " ----> print histograms statistic ";
		if(isMaster){
			G4cout << "for the entire run " << G4endl << G4endl; 
		}
		else{
			G4cout << "for the local thread " << G4endl << G4endl; 
		}

		G4cout << " EAbs : mean = " 
			<< G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
			<< " rms = " 
			<< G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
	}	

	analysisManager->Write();
	analysisManager->CloseFile();


}

