#ifndef FIRUNACTION_HH
#define FIRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4RootAnalysisManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

class FiRunAction : public G4UserRunAction
{
public:
	FiRunAction();
	~FiRunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
};


#endif
