#ifndef FiDetectorConstruction_h
#define FiDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "FiDetector.hh"
#include "FiSurfaceFiber.hh"


class FiDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
	FiDetectorConstruction();
	~FiDetectorConstruction();
	

	 	
	
  virtual G4VPhysicalVolume *Construct();
    
private:
	
	void DefineMaterials();
        void DefineMaterialsProperties();
        void DefinedOpticalPropertiesMaterials();
	
	virtual void ConstructSDandField();
	
	G4LogicalVolume *logicDetector;
	G4LogicalVolume *logical_clad2;
	G4LogicalVolume *logical_clad1;
	G4LogicalVolume *logical_core;
	G4LogicalVolume* logical_wall;
	
	
	G4Element* H;
	G4Element* C;
	G4Element* N;
	G4Element* O;
	G4Element* F;
	G4Element* Cr;
	G4Element* Mn;
	G4Element* Fe;
	G4Element* Ni;
	G4Element* Cu;
	G4Element* Si;
	G4Element* Xe;
	G4Element* Al;
	
	G4Material* Vacuum;
	G4Material* Pstyrene;
	G4Material* PMMA;
	G4Material* Pethylene1;
	G4Material* Pethylene2;
	G4Material* PVDF;
	G4Material* SS304LSteel;
	G4Material* LXe;
	G4Material* SiSensitive;
	
	
	
	
	

};


#endif

