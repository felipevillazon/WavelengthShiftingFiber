#ifndef SURFACEFIBER_HH
#define SURFACEFIBER_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include "G4TouchableHistory.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "FiEventAction.hh"

class FiSurfaceFiber : public G4VSensitiveDetector
{
public:
	FiSurfaceFiber(G4String);
	~FiSurfaceFiber();
	virtual void Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
private:
  G4int collectionID;
	
};

#endif
