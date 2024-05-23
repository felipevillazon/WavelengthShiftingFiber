#ifndef FISTEPPING_HH
#define FISTEPPING_HH


#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "FiDetectorConstruction.hh"
#include "FiEventAction.hh"
#include "FiSurfaceFiber.hh"


class FiSteppingAction: public G4UserSteppingAction
{
public:
	FiSteppingAction(FiEventAction* eventAction);
	~FiSteppingAction();
	
	virtual void UserSteppingAction(const G4Step*);
	
private:
	FiEventAction * fEventAction;	

};

#endif                                               
