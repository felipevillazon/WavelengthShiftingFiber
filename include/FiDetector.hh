#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include "G4TouchableHistory.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"

class FiSensitiveDetector : public G4VSensitiveDetector
{
public:
	FiSensitiveDetector(G4String);
	~FiSensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
