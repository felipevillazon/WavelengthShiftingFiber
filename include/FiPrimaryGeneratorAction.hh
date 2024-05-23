/*
#ifndef FiPrimaryGeneratorAction_h
#define FiPrimaryGeneratorAction_h 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class FiPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    FiPrimaryGeneratorAction();    
    ~FiPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun {nullptr}; // pointer a to G4 gun class
    
    G4GenericMessenger *fMessenger;
    
    G4double phi;
    G4double ftheta;
    G4double z;
    
};





#endif*/





#ifndef FiPrimaryGeneratorAction_h
#define FiPrimaryGeneratorAction_h 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class FiPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    FiPrimaryGeneratorAction();    
    ~FiPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun {nullptr}; // pointer a to G4 gun class
    
    G4GenericMessenger *fMessenger;
    
    G4double phi;
    G4double ftheta;
    G4double z;
    G4double x;
    
};





#endif
