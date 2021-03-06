#ifndef LaBr3EventAction_h
#define LaBr3EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"

class LaBr3RunAction;

/// Event action class
///
/// In EndOfEventAction() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for 
/// LaBr3RunAction::EndOfRunAction().

class LaBr3EventAction : public G4UserEventAction{
	public:
		LaBr3EventAction(LaBr3RunAction *runAction);
		virtual ~LaBr3EventAction();

		virtual void  BeginOfEventAction(const G4Event *event);
		virtual void    EndOfEventAction(const G4Event *event);

		void Sumstep_EnergyDeposit(int i, G4double stepEdep, G4double time);

	private:
		//LaBr3RunAction *fRunAction;
		G4double fEventEdep[12];
		G4double fTime0;
};





#endif


