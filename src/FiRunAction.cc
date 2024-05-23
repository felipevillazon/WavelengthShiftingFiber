#include "FiRunAction.hh"

FiRunAction::FiRunAction(){}

FiRunAction::~FiRunAction(){}

void FiRunAction::BeginOfRunAction(const G4Run* run)
{
	 G4AnalysisManager *man = G4AnalysisManager::Instance();
	 
	 G4int runID = run->GetRunID();
	 
	 std::stringstream strRunID;
	 strRunID << runID;
	 
	 man->OpenFile("output.root");
	 
	 man->CreateNtuple("Hits", "Hits");
	 man->CreateNtupleIColumn("Event_number");
	 man->CreateNtupleDColumn("x-position");
	 man->CreateNtupleDColumn("y-position");
	 man->CreateNtupleDColumn("z-position");
	 man->CreateNtupleDColumn("Energy");
	 man->CreateNtupleDColumn("Time");
	 man->FinishNtuple(0);
	 
	 
	 man->CreateNtuple("Scored", "Scored");
	 man->CreateNtupleIColumn("Event_number");
	 man->CreateNtupleDColumn("x-position");
	 man->CreateNtupleDColumn("y-position");
	 man->CreateNtupleDColumn("z-position");
	 man->CreateNtupleDColumn("detector ID");
	 man->CreateNtupleDColumn("Energy");
	 man->CreateNtupleDColumn("Time");
	 man->FinishNtuple(1);
	 
	 
	 /*man->CreateNtuple("IncidentAngle", "IncidentAngle");
	 man->CreateNtupleDColumn("Event_number");
	 man->CreateNtupleDColumn("InAngle");
	 man->CreateNtupleDColumn("z-position");
	 man->CreateNtupleDColumn("x-position");
	 man->CreateNtupleDColumn("y-position");
	 man->FinishNtuple(1);
	
	 man->CreateNtuple("position", "position");
	 man->CreateNtupleDColumn("x_position");
	 man->CreateNtupleDColumn("y_position");
	 man->CreateNtupleDColumn("z_position");
	 man->FinishNtuple(2);*/
	
	 
}

void FiRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
