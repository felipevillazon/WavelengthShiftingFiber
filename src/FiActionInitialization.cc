#include "FiActionInitialization.hh"
#include "FiPrimaryGeneratorAction.hh"
#include "FiRunAction.hh"
#include "FiEventAction.hh"
#include "FiSteppingAction.hh"


FiActionInitialization::FiActionInitialization(){}
FiActionInitialization::~FiActionInitialization(){}

void FiActionInitialization::Build() const
{
  
  
  SetUserAction(new FiPrimaryGeneratorAction);
  
  FiRunAction *runAction = new FiRunAction();
  SetUserAction(runAction);
  
  FiEventAction *eventAction = new FiEventAction(runAction);
  SetUserAction(eventAction);
  
  FiSteppingAction *steppingAction = new FiSteppingAction(eventAction);
  SetUserAction(steppingAction);
 
}  

 
