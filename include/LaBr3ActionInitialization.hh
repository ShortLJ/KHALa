#ifndef LaBr3ActionInitialization_h
#define LaBr3ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class LaBr3DetectorConstruction;

class LaBr3ActionInitialization : public G4VUserActionInitialization{
	public:
		LaBr3ActionInitialization(LaBr3DetectorConstruction*);
		virtual ~LaBr3ActionInitialization();

		virtual void BuildForMaster() const;
		virtual void Build() const;

	private:
		LaBr3DetectorConstruction *fDetConstruction;

};



#endif

