#include "FiDetectorConstruction.hh"

#include "G4VSolid.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Scintillation.hh"
#include "G4LossTableManager.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4UniformElectricField.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4OpWLS.hh"



FiDetectorConstruction::FiDetectorConstruction()
{
  DefineMaterials();
  DefineMaterialsProperties();
  DefinedOpticalPropertiesMaterials();
}



FiDetectorConstruction::~FiDetectorConstruction(){}

G4VPhysicalVolume* FiDetectorConstruction::Construct()
{        

//------------------------Option to switch on/off checking of volumes overlaps---------------------------------------------------------------------------------------
 
  G4bool checkOverlaps = true;        

//----------------------------------------------WORLD VOLUME-----------------------------------------------------------------------------------------------------------
  
  
  G4double world_sizeXY = 10.1*cm;
  G4double world_sizeZ  = 143*cm;
  	
  G4Box* solid_world = new G4Box("world", world_sizeXY, world_sizeXY, world_sizeZ);    
      
  G4LogicalVolume* logical_world = new G4LogicalVolume(solid_world, G4Material::GetMaterial("Vacuum"), "world");            
                                   
  G4VPhysicalVolume* physical_world = new G4PVPlacement(0, G4ThreeVector(), logical_world, "world", 0, false, 0, checkOverlaps);        


//--------------------------------------------------WALL VOLUME---------------------------------------------------------------------------------------------------

  G4double Steel_XY = 10*cm;
  G4double Steel_Z  = 141.5*cm;
	
  G4Box* solid_wall = new G4Box("wall" , Steel_XY, Steel_XY, Steel_Z);  
       
  logical_wall =  new G4LogicalVolume(solid_wall, G4Material::GetMaterial("SS304LSteel"), "wall");        
        
  G4VPhysicalVolume* physical_wall = new G4PVPlacement(0, G4ThreeVector(), logical_wall, "wall", logical_world, false, 0, checkOverlaps);
  
//---------------------------------------------LXe CONTAINING THE FIBER------------------------------------------------------------------------------------------------------------

  G4double lxe_XY = 9.9*cm;
  G4double lxe_Z  = 141.0*cm;
	
  G4Box* solid_lxe = new G4Box("lxe" , lxe_XY, lxe_XY, lxe_Z);  
       
  G4LogicalVolume* logical_lxe =  new G4LogicalVolume(solid_lxe, G4Material::GetMaterial("LXe"), "lxe");        
        
  G4VPhysicalVolume* physical_lxe = new G4PVPlacement(0, G4ThreeVector(), logical_lxe, "lxe", logical_wall, false, 0, checkOverlaps);   
        	
        
//---------------------------------------------FIBER CYLINDER---------------------------------------------------------------------------
       
       
  // Core

  G4double Fiber_rmin = 0.0 * cm;
  G4double Fiber_rmax = 0.1 * cm;
  G4double Fiber_z    = 130 * cm;
  G4double Fiber_sphi = 0.0 * deg;
  G4double Fiber_ephi = 360. * deg;
 	 
  G4Tubs* core_tube = new G4Tubs("Core", Fiber_rmin, Fiber_rmax, Fiber_z, Fiber_sphi, Fiber_ephi);   
  logical_core = new G4LogicalVolume(core_tube, G4Material::GetMaterial("Polystyrene"), "Core");     // LOGICAL VOLUME CORE FIBER
       
        
  // Cladding (first layer)

  G4double Clad1_rmin = 0. ;
  G4double Clad1_rmax = Fiber_rmax + 0.015 * Fiber_rmax;
  G4double Clad1_z    = Fiber_z;
  G4double Clad1_sphi = Fiber_sphi ;
  G4double Clad1_ephi = Fiber_ephi;
         
  G4Tubs* clad1_tube = new G4Tubs("Cladding1", Clad1_rmin, Clad1_rmax,  Clad1_z, Clad1_sphi, Clad1_ephi);
  logical_clad1 = new G4LogicalVolume(clad1_tube, G4Material::GetMaterial("PMMA") , "Cladding1");   // LOGICAL VOLUME CLADDING 1
   

  // Cladding (second layer)
         
  G4double Clad2_rmin = 0. ;
  G4double Clad2_rmax = Clad1_rmax + 0.015 * Fiber_rmax ;
  G4double Clad2_z    = Fiber_z ;
  G4double Clad2_sphi = Fiber_sphi ;
  G4double Clad2_ephi = Fiber_ephi ;
   
  G4Tubs* clad2_tube = new G4Tubs("Cladding2", Clad2_rmin, Clad2_rmax, Clad2_z, Clad2_sphi, Clad2_ephi);
  logical_clad2 = new G4LogicalVolume(clad2_tube, G4Material::GetMaterial("PVDF"), "Cladding2");   // LOGICAL VOLUME CLADDING 2  
         
  G4VPhysicalVolume* physical_core  = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logical_core , "Core"     , logical_clad1 ,   false, 0);
  G4VPhysicalVolume* physical_clad1 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logical_clad1, "Cladding1", logical_clad2, false, 0);
  G4VPhysicalVolume* physical_clad2 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logical_clad2, "Cladding2", logical_lxe   , false, 0);

//-----------------------------SENSITIVE DETECTORS--------------------------------------------------------------------------------------------

  G4double sens_xy = 0.3 * cm;
  G4double sens_z = 0.1 * cm;
        
  G4Tubs* solid_sens = new G4Tubs("Sensitive", Clad2_rmin, Clad2_rmax, sens_z, Clad2_sphi, Clad2_ephi);    
  logicDetector = new G4LogicalVolume(solid_sens,G4Material::GetMaterial("SiSensitive"), "Sensitive");            
  
  G4double above = Fiber_z + sens_z;
  G4double below = -Fiber_z - sens_z;
	 
  G4VPhysicalVolume *PhysDetector1 = new G4PVPlacement(0, G4ThreeVector(0,0,above), logicDetector, "Sensitive1", logical_lxe, false, 1, checkOverlaps);          
  G4VPhysicalVolume *PhysDetector2 =  new G4PVPlacement(0, G4ThreeVector(0,0,below), logicDetector, "Sensitive2", logical_lxe, false, 2, checkOverlaps); 
                                   
      
  	
//-------------------ALWAYS RETURN PHYSICAL WORLD---------------------------------------------------------------------------------------------------------

  return physical_world;
  
}

//-----------------------------SENSITIVE DETECTORS (PMTs)-------------------------------------------------------------------------------------------------

void FiDetectorConstruction::ConstructSDandField()
{
  FiSurfaceFiber *SurfaceFiber = new FiSurfaceFiber("SurfaceFiber");
  logical_core->SetSensitiveDetector(SurfaceFiber);     
        
  FiSensitiveDetector *sensDet = new FiSensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
	 
}


void FiDetectorConstruction::DefineMaterials()
{
  G4double a; 
  G4double z;  
  G4double density;

  H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g / mole);
  O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  F = new G4Element("Fluorine", "F", z = 9., a = 18.998 *g / mole);
  Cr = new G4Element("Chromium", "Cr", 24., 51.996 * g / mole);
  Mn = new G4Element("Manganese", "Mn", 25., 54.938 * g / mole);
  Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);
  Ni = new G4Element("Nickel", "Ni", 28., 58.693 * g / mole);
  Cu = new G4Element("Copper", "Cu", 29., 63.546 * g / mole);
  Si = new G4Element("Silicon", "Si", 14., 28.086 * g / mole);	
  Xe = new G4Element("Xenon", "Xe", 54., 131.293 * g / mole);
  Al = new G4Element("Aluminium", "Al", 13., 26.982 * g / mole);
  
  
  Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
  Vacuum->AddElement(N, 0.755);
  Vacuum->AddElement(O, 0.245);
  
  Pstyrene = new G4Material("Polystyrene", density = 1.03 * g / cm3, 2);
  Pstyrene->AddElement(C, 8);
  Pstyrene->AddElement(H, 8);
  
  PMMA = new G4Material("PMMA", density = 1190. * kg / m3, 3);
  PMMA->AddElement(H, 8);
  PMMA->AddElement(C, 5);
  PMMA->AddElement(O, 2);
  
  Pethylene1 = new G4Material("Pethylene1", density = 1200. * kg / m3, 2);
  Pethylene1->AddElement(H, 8);
  Pethylene1->AddElement(C, 5);
  
  Pethylene2 = new G4Material("Pethylene2", density = 1400. * kg / m3, 2);
  Pethylene2->AddElement(H, 8);
  Pethylene2->AddElement(C, 8);
  
  PVDF = new G4Material("PVDF", density = 1780. * kg / m3, 3); 
  PVDF->AddElement(H, 2);
  PVDF->AddElement(C, 2);
  PVDF->AddElement(F, 2);
    
  SS304LSteel = new G4Material("SS304LSteel", 8.00 * g / cm3, 5, kStateSolid);
  SS304LSteel->AddElement(Fe, 0.65);
  SS304LSteel->AddElement(Cr, 0.20);
  SS304LSteel->AddElement(Ni, 0.12);
  SS304LSteel->AddElement(Mn, 0.02);
  SS304LSteel->AddElement(Si, 0.01);
  
  LXe = new G4Material("LXe", 2.85 * g / cm3, 1, kStateLiquid, 168.15 * kelvin, 1.5 * atmosphere);
  LXe->AddElement(Xe, 1);
  
  SiSensitive = new G4Material("SiSensitive", 8.00 * g / cm3, 1, kStateSolid);
  SiSensitive->AddElement(Si, 1);
  
}


void FiDetectorConstruction::DefineMaterialsProperties()
{
 
  //----LXe-----//
  
  std::vector<G4double> lxe_n_energy = {1.*eV        , 1.24137931*eV, 1.48275862*eV, 1.72413793*eV, 1.96551724*eV,2.20689655*eV, 2.44827586*eV, 2.68965517*eV, 2.93103448*eV, 3.17241379*eV,
                                        3.4137931*eV , 3.65517241*eV, 3.89655172*eV, 4.13793103*eV, 4.37931034*eV,4.62068966*eV, 4.86206897*eV, 5.10344828*eV, 5.34482759*eV, 5.5862069*eV ,
                                        5.82758621*eV, 6.06896552*eV, 6.31034483*eV, 6.55172414*eV, 6.79310345*eV,7.03448276*eV, 7.27586207*eV, 7.51724138*eV, 7.75862069*eV, 8.*eV};
  
  std::vector<G4double> lxe_n = {1.37640198, 1.3779425 , 1.3797101 , 1.38173828, 1.38406545,1.38673567, 1.38979952, 1.39331502, 1.39734877, 1.40197714,1.40728781, 1.41338135, 1.42037316, 1.42839567, 
                                 1.43760081, 1.44816292, 1.46028205, 1.47418771, 1.49014327, 1.50845091,1.52945736, 1.55356048, 1.58121674, 1.61294994, 1.64936108,1.69113975, 1.73907721, 1.79408135,    
                                 1.85719391, 1.92961018};                                      
  
  std::vector<G4double> lxe_energy = { 7.0 * eV, 7.07 * eV, 7.14 * eV };
  
  std::vector<G4double> lxe_scint = { 1.0, 0.1, 0.1 };
  
  std::vector<G4double> lxe_absl  = { 50. * m, 50. * m, 50. * m };
  	
  G4MaterialPropertiesTable *LXeTableProperties = new G4MaterialPropertiesTable();
  	
  LXeTableProperties->AddProperty("SCINTILLATIONCOMPONENT1", lxe_energy, lxe_scint);
  LXeTableProperties->AddProperty("SCINTILLATIONCOMPONENT2", lxe_energy, lxe_scint);
  LXeTableProperties->AddProperty("RINDEX", lxe_n_energy, lxe_n);
  LXeTableProperties->AddProperty("ABSLENGTH", lxe_energy, lxe_absl);
  LXeTableProperties->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
  LXeTableProperties->AddConstProperty("RESOLUTIONSCALE", 1.0);
  LXeTableProperties->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3. * ns);
  LXeTableProperties->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 27. * ns);
  LXeTableProperties->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  LXeTableProperties->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  
  LXe->SetMaterialPropertiesTable(LXeTableProperties);
  
  
  
  //---POLYSTYRENE---//
  
  std::vector<G4double> ps_n_energy = {1.*eV, 1.24137931*eV, 1.48275862*eV, 1.72413793*eV, 1.96551724*eV,2.20689655*eV, 2.44827586*eV, 2.68965517*eV, 2.93103448*eV, 3.17241379*eV,
                                       3.4137931*eV , 3.65517241*eV, 3.89655172*eV, 4.13793103*eV, 4.37931034*eV,4.62068966*eV, 4.86206897*eV, 5.10344828*eV, 5.34482759*eV, 5.5862069*eV ,
                                       5.82758621*eV, 6.06896552*eV, 6.31034483*eV, 6.55172414*eV, 6.79310345*eV,7.03448276*eV, 7.27586207*eV, 7.51724138*eV, 7.75862069*eV, 8. *eV};
  
  std::vector<G4double> ps_n = { 1.56886052, 1.57262149, 1.57695992, 1.5819645 , 1.58773749,1.59439688, 1.60207878, 1.61094019, 1.6211622 , 1.63295373,
                                 1.64655578, 1.66224633, 1.68034605, 1.70122487, 1.72530948,1.75309213, 1.78514062, 1.82210994, 1.86475565, 1.91394931,
                                 1.97069634, 2.03615649, 2.1116676 , 2.19877293, 2.29925271,2.41516047, 2.5488651 , 2.70309917, 2.88101484, 3.08624826};
  
  std::vector<G4double> ps_abs_energy = { 1 * eV, 2*eV, 3* eV, 3.5*eV };
  
  std::vector<G4double> ps_abs = { 4 * m, 4* m , 4* m, 4*m };
        
  std::vector<G4double> wls_abs_energy = {2.5*eV,3.0*eV,3.5*eV,4.14297299*eV,  4.34910719*eV,  4.62223305*eV,  4.87180152*eV,  5.19768254*eV,5.52626141*eV,  5.9116195*eV ,  6.34034404*eV,  6.73716986*eV,  
                                          7.31862896*eV, 7.80866709*eV,  8.47012392*eV,  8.90094832*eV,  9.28392842*eV,  9.80375918*eV,10.30881052*eV, 10.95336061*eV, 11.58665859*eV, 12.19063474*eV};
                                                
  std::vector<G4double> wls_abs = {4*m,4*m,4*m,0.0241464*mm, 0.0240253*mm,0.024035*mm , 0.0239147*mm, 0.0236714*mm, 0.0234321*mm, 0.0230785*mm,0.0227351*mm, 0.0220701*mm, 0.0214443*mm, 
                                   0.0208513*mm, 0.0199305*mm,0.0194159*mm, 0.0183841*mm, 0.0177327*mm, 0.0171913*mm, 0.0164377*mm,0.0155833*mm, 0.0148621*mm};
  
  std::vector<G4double> wls_emission_energy = {2.08230412*eV, 2.11850012*eV, 2.16363175*eV, 2.21877763*eV, 2.28964037*eV,2.36977778*eV, 2.44587156*eV, 2.5217854*eV , 2.59149453*eV, 2.63065063*eV,
                                               2.67100814*eV, 2.68868579*eV, 2.71262321*eV,  2.74315113*eV, 2.79986872*eV,2.83900166*eV, 2.87924401*eV, 2.9136612*eV , 2.97047354*eV, 2.97773124*eV,
                                               2.99971871*eV, 3.0220333*eV , 3.04468237*eV, 3.0676735*eV , 3.0831948*eV ,3.09887396*eV,3.09887396*eV, 3.15502959*eV, 3.19640315*eV, 3.30923196*eV,
                                               3.37334915*eV};
  
  std::vector<G4double> wls_emission = {0.00520833, 0.01041667, 0.015625  , 0.01041667, 0.046875  ,0.09895833, 0.16145833, 0.265625  , 0.35416667, 0.43229167,0.48958333, 0.546875  , 0.58333333, 
                                        0.63541667, 0.6875 ,0.74479167, 0.765625  , 0.75, 0.671875  , 0.61458333,0.57291667, 0.49479167, 0.390625  , 0.29166667, 0.203125  ,
                                        0.16666667, 0.11458333, 0.06770833, 0.00520833, 0.00520833,0.00520833};
  
  G4MaterialPropertiesTable* PSTableProperty   = new G4MaterialPropertiesTable();
                  
  PSTableProperty->AddProperty("RINDEX", ps_n_energy, ps_n);
  //PSTableProperty->AddProperty("ABSLENGTH", ps_abs_energy, ps_abs);
  PSTableProperty->AddProperty("WLSABSLENGTH", wls_abs_energy, wls_abs);
  PSTableProperty->AddProperty("WLSCOMPONENT", wls_emission_energy, wls_emission);
  PSTableProperty->AddConstProperty("WLSTIMECONSTANT", 0.5 * ns);
        
  Pstyrene->SetMaterialPropertiesTable(PSTableProperty);


       

  //---PMMA---//
  
  std::vector<G4double> pmma_abs = { 3.5 * m, 3.5 * m, 3.5 * m, 3.5 * m };
  
  std::vector<G4double> pmma_abs_energy = { 1 * eV, 2 * eV, 6 * eV, 10 * eV };

  std::vector<G4double> pmma_n_energy  = {1. *eV, 1.24137931*eV, 1.48275862*eV, 1.72413793*eV, 1.96551724*eV,2.20689655*eV, 2.44827586*eV, 2.68965517*eV, 2.93103448*eV, 3.17241379*eV,
                                          3.4137931 *eV, 3.65517241*eV, 3.89655172*eV, 4.13793103*eV, 4.37931034*eV,4.62068966*eV, 4.86206897*eV, 5.10344828*eV, 5.34482759*eV, 5.5862069 *eV,
                                          5.82758621*eV, 6.06896552*eV, 6.31034483*eV, 6.55172414*eV, 6.79310345*eV,7.03448276*eV, 7.27586207*eV, 7.51724138*eV, 7.75862069*eV, 8.  *eV };
        
  std::vector<G4double> pmma_n = {1.47962474, 1.4811668 , 1.4829135 , 1.48489202, 1.48713311,1.48967162, 1.49254703, 1.49580403, 1.49949329, 1.50367216,1.50840561, 1.51376726, 1.51984047, 1.52671967, 
                                  1.53451183,1.54333811, 1.55333575, 1.56466021, 1.57748757, 1.59201729,1.60847529, 1.62711748, 1.64823373, 1.67215238, 1.69924534,
                                  1.72993389, 1.76469521, 1.8040698 , 1.84866991, 1.89918904};
        
  G4MaterialPropertiesTable* PMMATableProperty = new G4MaterialPropertiesTable();
  PMMATableProperty->AddProperty("RINDEX", pmma_n_energy,pmma_n);
  PMMATableProperty->AddProperty("ABSLENGTH", pmma_abs_energy, pmma_abs);
        
  PMMA->SetMaterialPropertiesTable(PMMATableProperty);
  
  
  
  //---PVDF---//
  
  std::vector<G4double> pvdf_n_energy = {1.*eV, 1.24137931*eV, 1.48275862*eV, 1.72413793*eV, 1.96551724*eV,2.20689655*eV, 2.44827586*eV, 2.68965517*eV, 2.93103448*eV, 3.17241379*eV,
                                         3.4137931 *eV, 3.65517241*eV, 3.89655172*eV, 4.13793103*eV, 4.37931034*eV,4.62068966*eV, 4.86206897*eV, 5.10344828*eV, 5.34482759*eV, 5.5862069*eV ,
                                         5.82758621*eV, 6.06896552*eV, 6.31034483*eV, 6.55172414*eV, 6.79310345*eV,7.03448276*eV, 7.27586207*eV, 7.51724138*eV, 7.75862069*eV, 8.*eV    };
  
  std::vector<G4double> pvdf_n = {1.40602789, 1.40677367, 1.40768198, 1.40878824, 1.4101356 ,1.41177659, 1.41377522, 1.41620943, 1.41917413, 1.42278495,
                                  1.4271827 , 1.43253889, 1.43906237, 1.44700756, 1.4566843 ,1.46846995, 1.48282413, 1.5003066 , 1.52159913, 1.54753209,
                                  1.57911677, 1.61758491, 1.66443665, 1.72149909, 1.79099752,1.87564217, 1.97873397, 2.10429323, 2.25721641, 2.44346711};
       
  std::vector<G4double> pvdf_abs_energy = { 1 * eV, 4*eV, 7* eV, 10*eV };
  std::vector<G4double> pvdf_abs = { 2 * m, 2* m , 2* m, 2*m };
        
  G4MaterialPropertiesTable* PVDFTableProperty   = new G4MaterialPropertiesTable();
  PVDFTableProperty->AddProperty("RINDEX", pvdf_n_energy, pvdf_n);
  PVDFTableProperty->AddProperty("ABSLENGTH", pvdf_abs_energy, pvdf_abs);
        	
  PVDF->SetMaterialPropertiesTable(PVDFTableProperty);
  
  
  //---SiSensitive---//

  G4double si_energy[] = {1. * eV, 2. * eV, 2.5 * eV, 3.0 * eV, 3.5 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
  G4double si_n[] = {1.50, 1.50, 1.55, 1.60, 1.62};
  G4double si_absl[] = {1. * nm, 1 * nm, 1. * nm, 1. * nm, 1. * nm};
    
  G4MaterialPropertiesTable *SiPropertiesTable = new G4MaterialPropertiesTable();

  SiPropertiesTable->AddProperty( "RINDEX", si_energy, si_n, 5);
  SiPropertiesTable->AddProperty("ABSLENGTH", si_energy, si_absl,5);
  SiSensitive->SetMaterialPropertiesTable(SiPropertiesTable);
    
  
  
}

void FiDetectorConstruction::DefinedOpticalPropertiesMaterials()
{
  std::vector<G4double> ephoton = {1*eV,2*eV,5*eV, 7.0 * eV, 7.14 * eV };
  std::vector<G4double> steel_Reflectivity =  {0.,0.,0.,0.,0.};
  std::vector<G4double> steel_Efficiency   = { 0.0,0.0,0.0,0.0, 0.0 };
  G4MaterialPropertiesTable* STEEL = new G4MaterialPropertiesTable();
  STEEL->AddProperty("REFLECTIVITY", ephoton, steel_Reflectivity);
  STEEL->AddProperty("EFFICIENCY", ephoton, steel_Efficiency);
    	 
  G4OpticalSurface* OpSteelSurface = new G4OpticalSurface("SteelSurface", unified, polished, dielectric_metal);
  OpSteelSurface->SetMaterialPropertiesTable(STEEL);
  new G4LogicalSkinSurface("steel_surface", logical_wall , OpSteelSurface);

}
	
