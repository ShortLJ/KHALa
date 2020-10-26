#ifndef LaBr3RunAction_h
#define LaBr3RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"
//#include "G4Accumulable.hh"
#include "globals.hh"

/// Run action class

class LaBr3RunAction : public G4UserRunAction{
	public:
		LaBr3RunAction();
		virtual ~LaBr3RunAction();

		virtual void BeginOfRunAction(const G4Run*);
		virtual void   EndOfRunAction(const G4Run*);

		//void CountEvent()           { fGoodEvents += 1; };
		//void SumDose(G4double dose) { fSumDose += dose; };  

	private:
		//G4Accumulable<G4int>    fGoodEvents;
		//G4Accumulable<G4double> fSumDose;  
};


#endif

