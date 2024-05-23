/*#ifndef FIEVENTACTION_HH
#define FIEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "FiRunAction.hh"
#include "FiSurfaceFiber.hh"


class FiEventAction : public G4UserEventAction
{
public:
	FiEventAction(FiRunAction*);
	~FiEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	//void AddEdep(G4double edep) {fEdep += edep;}  // function that will add the energy 
	std::vector<G4double> incidenceAngleVec;
	std::vector<G4double> zposition;
	//G4int evt;
	
private:
	//G4double fEdep	;	// double definition of variable fEdep
	
};





#endif */


#ifndef FIEVENTACTION_HH
#define FIEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "FiRunAction.hh"
#include "FiSurfaceFiber.hh"


class FiEventAction : public G4UserEventAction
{
public:
	FiEventAction(FiRunAction*);
	~FiEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	//void AddEdep(G4double edep) {fEdep += edep;}  // function that will add the energy 
	std::vector<G4double> incidenceAngleVec;
	std::vector<G4double> incidenceAnglevec;
	std::vector<G4double> zposition;
	std::vector<G4double> xposition;
	std::vector<G4double> yposition;
	//G4int evt;
	
private:
	//G4double fEdep	;	// double definition of variable fEdep
	
};





#endif
