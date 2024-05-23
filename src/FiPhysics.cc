#include "FiPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

FiPhysics::FiPhysics()
{
   RegisterPhysics (new G4EmStandardPhysics());
   RegisterPhysics (new G4OpticalPhysics());
   
//----------------PHYSICS FOR WAVELENGTH SHIFTING FIBERS-----------------------------------------------------------------------------------
   
   G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
   auto opticalParams               = G4OpticalParameters::Instance();

   opticalParams->SetBoundaryInvokeSD(true);
   opticalParams->SetWLSTimeProfile("delta");

   opticalParams->SetScintTrackSecondariesFirst(true);

   opticalParams->SetCerenkovMaxPhotonsPerStep(100);
   opticalParams->SetCerenkovMaxBetaChange(10.0);
   opticalParams->SetCerenkovTrackSecondariesFirst(true);

   RegisterPhysics (opticalPhysics);


   //RegisterPhysics (new G4DecayPhysics());
   //RegisterPhysics (new G4RadioactiveDecayPhysics());
   //RegisterPhysics( new G4IonElasticPhysics());
   //RegisterPhysics( new G4IonPhysics());
   //RegisterPhysics (new G4EmLivermorePhysics());
   //RegisterPhysics (new G4EmPenelopePhysics());
}

FiPhysics::~FiPhysics()
{}


