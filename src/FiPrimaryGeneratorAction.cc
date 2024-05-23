
/*using namespace std;


#include "FiPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

#include "G4VisAttributes.hh"
#include "G4VisManager.hh"


FiPrimaryGeneratorAction::FiPrimaryGeneratorAction()
{

   fMessenger = new G4GenericMessenger(this, "/gun/", "Particle Gun");
   
   fMessenger->DeclareProperty("ftheta", ftheta, "Angle theta respect to z-axis");
   fMessenger->DeclareProperty("phi", phi, "Angle phi respect to xy plane from x-axis");
   fMessenger->DeclareProperty("z", z, "Shifting z position of the particle ");
   
   ftheta = 0 ;
   phi = 90 ; 
   z = 0 ; 


  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4double gammaEnergy = 7*eV; // set the energy of the gamma particle


  
  
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="opticalphoton");
  fParticleGun->SetParticleDefinition(particle);
  
 //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  fParticleGun->SetParticleEnergy(gammaEnergy);
  
  

}



FiPrimaryGeneratorAction::~FiPrimaryGeneratorAction()
{
  delete fParticleGun;
}



void FiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // --------------------
  // Pencile beam function:
  // --------------------
  
 
  G4double theta = 90 - ftheta;
  
  G4double x1 =   0.0*cm ;
  G4double y1 =   0.01* std::sin(theta * deg) * cm;
  G4double z1 =   (z + 0.01* std::cos(theta * deg )) * cm ;
  
  G4double norm = std::sqrt(x1**2 + y1**2 + z1**2);
  
  G4double x0 = x1/norm;
  G4double y0 = y1/norm;
  G4double z0 = z1/norm;
  
  G4double px1 = -1 * std::sin(theta * deg ) * std::cos(phi * deg);
  G4double py1 = -1 * std::sin(theta * deg) * std::sin(phi * deg);
  G4double pz1 = -1 * std::cos(theta * deg );
  
  G4double pnorm = std::sqrt(px1** + py1**2 + pz1**2);
  
   
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}





using namespace std;


#include "FiPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

#include "G4VisAttributes.hh"
#include "G4VisManager.hh"


FiPrimaryGeneratorAction::FiPrimaryGeneratorAction()
{

   fMessenger = new G4GenericMessenger(this, "/gun/", "Particle Gun");
   
   fMessenger->DeclareProperty("ftheta", ftheta, "Angle theta respect to z-axis");
   fMessenger->DeclareProperty("phi", phi, "Angle phi respect to xy plane from x-axis");
   fMessenger->DeclareProperty("x", x, "Shifting x position of the particle ");
   fMessenger->DeclareProperty("z", z, "Shifting z position of the particle ");
   
   
   ftheta = 90  ;
   phi = 90  ; 
   z = 0  ; 
   x = 0 ;


  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4double gammaEnergy = 7*eV; // set the energy of the gamma particle


  
  
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="opticalphoton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(gammaEnergy);
  
  

}



FiPrimaryGeneratorAction::~FiPrimaryGeneratorAction()
{
  delete fParticleGun;
}



void FiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // --------------------
  // Pencile beam function:
  // --------------------
  
  G4double theta = 90 - ftheta ;	
  
  G4double x0 =   (x + 0.0) * mm ;
  G4double y0 =   2* std::sin(theta * deg) * cm;
  G4double z0 =   (z + 2* std::cos(theta * deg )) * cm ;
  
  G4double px = -1 * std::sin(theta * deg ) * std::cos(phi * deg);
  G4double py = -1 * std::sin(theta * deg) * std::sin(phi * deg);
  G4double pz = -1 * std::cos(theta * deg );
   
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}*/




using namespace std;


#include "FiPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

#include "G4VisAttributes.hh"
#include "G4VisManager.hh"


FiPrimaryGeneratorAction::FiPrimaryGeneratorAction()
{

   fMessenger = new G4GenericMessenger(this, "/gun/", "Particle Gun");
   
   fMessenger->DeclareProperty("ftheta", ftheta, "Angle theta respect to z-axis");
   fMessenger->DeclareProperty("phi", phi, "Angle phi respect to xy plane from x-axis");
   fMessenger->DeclareProperty("x", x, "Shifting x position of the particle ");
   fMessenger->DeclareProperty("z", z, "Shifting z position of the particle ");
   
   
   ftheta = 0  ;
   phi = 0  ; 
   z = 0  ; 
   x = 0 * mm ;


  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4double gammaEnergy = 7*eV; // set the energy of the gamma particle


  
  
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="opticalphoton");
  fParticleGun->SetParticleDefinition(particle);
  
 //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  fParticleGun->SetParticleEnergy(gammaEnergy);
  
  

}



FiPrimaryGeneratorAction::~FiPrimaryGeneratorAction()
{
  delete fParticleGun;
}



void FiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // --------------------
  // Pencile beam function:
  // --------------------
  
 
  G4double yf = 1.03 * mm;
 
  
  
  // Define the center of the sphere
   G4ThreeVector pf(x, yf, z);

   // Define the desired values for phi and theta
   G4double phi_d = phi;   // Example azimuthal angle in radians
   G4double theta_d = ftheta; // Example polar angle (inclination) in radians
   
   
   G4double phi = phi_d * M_PI / 180.0;
   G4double theta = theta_d * M_PI / 180.0;
   
   

   // Calculate the Cartesian coordinates of the points using spherical coordinates
   G4double r = 3 * cm;;  // Radius of the sphere
   G4double z0 = pf.z() + r * sin(theta) * cos(phi);
   G4double x0 = pf.x() + r * sin(theta) * sin(phi);
   G4double y0 = pf.y() + r * cos(theta);

   // Create the 3D points
   G4ThreeVector p0(x0, y0, z0);
   G4ThreeVector p1f(x, yf, z);

   // Calculate the vector in Cartesian coordinates
   G4ThreeVector vectorCartesian = -p0 + p1f;

   // Print the resulting vector
    //G4cout << "Vector: " << vectorCartesian << G4endl;
  
  /*G4double theta = 90 - ftheta ;	
  
  G4double x0 =   (x + 0.0) * mm ;
  G4double y0 =   2* std::sin(theta * deg) * cm;
  G4double z0 =   (z + 2* std::cos(theta * deg )) * cm ;
  
  G4double px = -1 * std::sin(theta * deg ) * std::cos(phi * deg) ;
  G4double py = -1 * std::sin(theta * deg) * std::sin(phi * deg) ;
  G4double pz = -1 * std::cos(theta * deg ) ;*/
 
  fParticleGun->SetParticleMomentumDirection(vectorCartesian);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
  
  
  //G4cout << "ParticleGun Position: " << G4ThreeVector(x0,y0,z0) << " [mm]" << G4endl;
  //G4cout << "ParticleGun Direction: " << G4ThreeVector(px,py,pz) << G4endl;
  
  
}


