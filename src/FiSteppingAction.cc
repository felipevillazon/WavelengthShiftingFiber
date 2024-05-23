#include "FiSteppingAction.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "FiSurfaceFiber.hh"
#include "FiDetectorConstruction.hh"

FiSteppingAction::FiSteppingAction(FiEventAction *eventAction)
{}

FiSteppingAction::~FiSteppingAction()
{}

void FiSteppingAction::UserSteppingAction(const G4Step *step)
{
	
        const G4StepPoint* endPoint = step->GetPostStepPoint();
        const G4VProcess* process = endPoint->GetProcessDefinedStep();
        G4String processName = process->GetProcessName();

	
        /*if (processName == "OpWLS") {
              
        G4AnalysisManager *man = G4AnalysisManager::Instance(); 
        G4StepPoint *pre = step->GetPostStepPoint();
        G4ThreeVector position = pre->GetPosition();
        
        G4cout << "The WLS happened at: " << position[1] << " [mm]" << G4endl;
        
        man->FillNtupleDColumn(2,0,position[0]);
        man->FillNtupleDColumn(2,1,position[1]);
        man->FillNtupleDColumn(2,2,position[2]);
        man->AddNtupleRow(2);
        }*/
                       
};	
