#ifndef LaBr3STEPPINGACTION_HH
#define LaBr3STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "g4root.hh"

class LaBr3DetectorConstruction;
class LaBr3EventAction;

class LaBr3SteppingAction : public G4UserSteppingAction
{
	public:
		LaBr3SteppingAction(const LaBr3DetectorConstruction *detectorConstruction, LaBr3EventAction *eventAction);
		virtual ~LaBr3SteppingAction();

		// method from the base class
		virtual void UserSteppingAction(const G4Step*);

	private:
		const LaBr3DetectorConstruction *fDetConstruction;
		LaBr3EventAction *fEventAction;

};

#endif
