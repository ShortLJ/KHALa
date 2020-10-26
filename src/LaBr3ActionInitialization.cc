#include "LaBr3ActionInitialization.hh"
#include "LaBr3PrimaryGeneratorAction.hh"
#include "LaBr3RunAction.hh"
#include "LaBr3EventAction.hh"
#include "LaBr3SteppingAction.hh"
#include "LaBr3DetectorConstruction.hh"

//#include "LaBr3StackingAction.hh"


LaBr3ActionInitialization::LaBr3ActionInitialization(LaBr3DetectorConstruction *detConstruction):G4VUserActionInitialization(),fDetConstruction(detConstruction)
{ }


LaBr3ActionInitialization::~LaBr3ActionInitialization()
{ }


void LaBr3ActionInitialization::BuildForMaster() const
{
  LaBr3RunAction *runAction = new LaBr3RunAction;
  SetUserAction(runAction);
}


void LaBr3ActionInitialization::Build() const
{
  SetUserAction(new LaBr3PrimaryGeneratorAction);

  LaBr3RunAction *runAction = new LaBr3RunAction;
  SetUserAction(runAction);
  
  LaBr3EventAction *eventAction = new LaBr3EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new LaBr3SteppingAction(fDetConstruction, eventAction));
//  SetUserAction(new LaBr3StackingAction);
}  

