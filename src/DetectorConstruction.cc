//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file hadronic/Hadr03/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 70755 2013-06-05 12:17:48Z ihrivnac $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "globals.hh"
#include "G4NuclideTable.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fTargetMater(0), fLogicTarget(0),
 fDetectorMater(0), fLogicDetector(0), 
 fWorldMater(0), fPhysiWorld(0),
 fDetectorMessenger(0)
{
  fTargetLength      = 1*cm; 
  fTargetRadius      = 0.5*cm;
  fDetectorLength    = 5*cm; 
  fDetectorThickness = 2*cm;
  
    fWorldLength = 100*cm;//std::max(fTargetLength,fDetectorLength);
    fWorldRadius = 100*cm;//fTargetRadius + fDetectorThickness;
      
  DefineMaterials();
    
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{   /*//STARTING HERE NOT SURE HOW MUCH IS NECESSARY
    G4String name, symbol;             // a=mass of a mole;
    G4double density;
    //G4double a, z, density;            // z=mean number of protons;
    //G4int iz, n;                       // iz=nb of protons  in an isotope;
    // n=nb of nucleons in an isotope;
    G4int ncomponents, natoms;
    //G4double abundance, fractionmass;  //for ions
    G4double temperature; //pressure;
    
    G4UnitDefinition::BuildUnitsTable();
    ///
    
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
  //ENDS HERE
  */
    
  // build materials
  //
  fDetectorMater = 
  new G4Material("Germanium", 32, 72.61*g/mole, 5.323*g/cm3);
  

  G4Element* N  = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",   "O", 8, 16.00*g/mole);
  //
  G4int ncomponents; G4double fractionmass;      
  G4Material* Air20 = new G4Material("Air", 1.205*mg/cm3, ncomponents=2,
                      kStateGas, 293.*kelvin, 1.*atmosphere);
    Air20->AddElement(N, fractionmass=0.7);
    Air20->AddElement(O, fractionmass=0.3);
  //
  fWorldMater = Air20;
  
  // or use G4 materials data base
  //
  G4NistManager* man = G4NistManager::Instance();  
  //fTargetMater = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  //shape3_mat = man->FindOrBuildMaterial("G4_Al");
  //shape3_mat = man->FindOrBuildMaterial("G4_Al");
    shape3_mat = man->FindOrBuildMaterial("G4_Al");
    shape4_mat = man->FindOrBuildMaterial("G4_Al");
    shape5_mat = man->FindOrBuildMaterial("G4_Pyrex_Glass");
    shape6_mat = man->FindOrBuildMaterial("G4_Al");
    
    G4Element* C  = man->FindOrBuildElement("C");
    G4Element* H  = man->FindOrBuildElement("H");
    G4int natoms; //G4int ncomponents; G4double fractionmass;
    G4Material* EJ309 = new G4Material("EJ309", 0.959*g/cm3, ncomponents=2,
                                       kStateLiquid, 293.*kelvin, 1.*atmosphere);
    EJ309->AddElement(C, natoms=4);
    EJ309->AddElement(H, natoms=5);
    //
    G4Material* shape1_mat = EJ309;
    
    

    
 ///G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // World
  //
  // (re) compute World dimensions if necessary
  fWorldLength = 100*cm; //std::max(fTargetLength,fDetectorLength);
  fWorldRadius = 100*cm; //fTargetRadius + fDetectorThickness;
    
  G4Tubs*
  sWorld = new G4Tubs("World",                                 //name
                 0.,fWorldRadius, 0.5*fWorldLength, 0.,twopi); //dimensions  
    
    
    
  G4LogicalVolume*
  lWorld = new G4LogicalVolume(sWorld,                  //shape
                             fWorldMater,               //material
                             "World");                  //name

  fPhysiWorld = new G4PVPlacement(0,                    //no rotation
                            G4ThreeVector(),            //at (0,0,0)
                            lWorld,                     //logical volume
                            "World",                    //name
                            0,                          //mother volume
                            false,                      //no boolean operation
                            0);                         //copy number
                            
  // Target
  //
    G4ThreeVector pos3 = G4ThreeVector(0, 0, 0);
    
    // Hollow cylinder
    G4double shape3_pRMin = 6.35*cm, shape3_pSPhi = 0.*degree;
    G4double shape3_pRMax = 6.45*cm, shape3_pDPhi = 360*degree;
    G4double shape3_pDz  = 6.35*cm;

    
    G4Tubs*
    sTarget = new G4Tubs("Target",                      //its name
                         shape3_pRMin,
                         shape3_pRMax,
                         shape3_pDz,
                         shape3_pSPhi,
                         shape3_pDPhi);              //its size
    


    fLogicTarget = new G4LogicalVolume(sTarget,         //its solid
                                       shape3_mat,          //its material
                                       "Target");           //its name
    

    G4VisAttributes* visAttTarget = new G4VisAttributes( G4Color(1, 1, 1)); //Visualization attributes, here you set the parameters to view the detector
    visAttTarget->SetForceWireframe(true);
    fLogicTarget->SetVisAttributes(visAttTarget);

    
    new G4PVPlacement(0,                       //no rotation
                      pos3,                    //at position
                      fLogicTarget,             //its logical volume
                      "Target",                //its name
                      lWorld,                //its mother  volume
                      false,                   //no boolean operation
                      0);                       //copy number
                      //checkOverlaps);          //overlaps checking

    
    
    
  // Detector
  //
    
    /*
    G4double density = 0.959*g/cm3;
    G4double temperature = 295.*kelvin;
    G4Material* Hi = man->FindOrBuildMaterial("G4_H");
    G4Material* Ca = man->FindOrBuildMaterial("G4_C");
    
    G4Material* EJ309 = new G4Material(name="EJ309"  , density, ncomponents=2, kStateLiquid, temperature);
    //G4Material* PbWO4= new G4Material(name="PbWO4", density, ncomponents=3); //as in example
    EJ309->AddMaterial(Hi, G4int natoms1 = 5);
    EJ309->AddMaterial(Ca, G4int natoms2 = 4);
    G4Material* shape1_mat = man->FindOrBuildMaterial("EJ309"); //A PLACE HOLDER, NEED TO USE EJ309
    */
    
    
    //G4Element* C  = new G4Element("Nitrogen", "C", 7, 14.01*g/mole);
    //G4Element* H  = new G4Element("Oxygen",   "H", 8, 16.00*g/mole);

    
    G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
    
    // A solid cylinder containing EJ309
    G4double shape1_pRMin = 0.*cm, shape1_pSPhi = 0.*degree;
    G4double shape1_pRMax = 6.35*cm, shape1_pDPhi = 360*degree;
    G4double shape1_pDz  = 6.35*cm;
    
    G4Tubs*
    sDetector = new G4Tubs("Detector",                      //its name
                           shape1_pRMin,
                           shape1_pRMax,
                           shape1_pDz,
                           shape1_pSPhi,
                           shape1_pDPhi);              //its size
    


    fLogicDetector = new G4LogicalVolume(sDetector,         //its solid
                                         shape1_mat,          //its material
                                         "Detector");           //its name

    
    G4VisAttributes* visAttDetector = new G4VisAttributes( G4Color(0, 1, 0));
    fLogicDetector->SetVisAttributes(visAttDetector);
    
    
    new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(),             //at (0,0,0)
                           fLogicDetector,              //logical volume
                           "Detector",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number

    
    
    
    // SHAPE 4 -Aluminum Bottom
    //
    G4ThreeVector pos4 = G4ThreeVector(0, 0, -6.45*cm);
    
    // Solid cylinder
    G4double shape4_pRMin = 0.*cm, shape4_pSPhi = 0.*degree;
    G4double shape4_pRMax = 6.45*cm, shape4_pDPhi = 360*degree;
    G4double shape4_pDz  = 0.1*cm;
    G4Tubs* solidShape4 =
    new G4Tubs("Shape4",                      //its name
               shape4_pRMin,
               shape4_pRMax,
               shape4_pDz,
               shape4_pSPhi,
               shape4_pDPhi);              //its size
    
    G4LogicalVolume* logicShape4 =
    new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");           //its name
    
    G4VisAttributes* visAttShape4 = new G4VisAttributes( G4Color(1, 1, 1));
    visAttShape4->SetForceWireframe(true);
    logicShape4->SetVisAttributes(visAttShape4);
    
    new G4PVPlacement(0,                       //no rotation
                      pos4,                    //at position
                      logicShape4,             //its logical volume
                      "Shape4",                //its name
                      lWorld,                  //its mother  volume
                      false,                   //no boolean operation
                      0);                       //copy number
                      //checkOverlaps);          //overlaps checking
    
    // Set Shape4 as scoring volume
    //
    //fScoringVolume = logicShape4; //NOT sure what this does
    
    
    
    // SHAPE 5 -GLASS WINDOW
    //

    G4ThreeVector pos5 = G4ThreeVector(0, 0, 6.665*cm);
    
    // SOLID GLASS WINDOW
    G4double shape5_pRMin = 0.*cm, shape5_pSPhi = 0.*degree;
    G4double shape5_pRMax = 3.81*cm, shape5_pDPhi = 360*degree;
    G4double shape5_pDz  = 0.315*cm;
    G4Tubs* solidShape5 =
    new G4Tubs("Shape5",                      //its name
               shape5_pRMin,
               shape5_pRMax,
               shape5_pDz,
               shape5_pSPhi,
               shape5_pDPhi);              //its size
    
    G4LogicalVolume* logicShape5 =
    new G4LogicalVolume(solidShape5,         //its solid
                        shape5_mat,          //its material
                        "Shape5");           //its name
    
    new G4PVPlacement(0,                       //no rotation
                      pos5,                    //at position
                      logicShape5,             //its logical volume
                      "Shape5",                //its name
                      lWorld,                  //its mother  volume
                      false,                   //no boolean operation
                      0);                       //copy number
                      //checkOverlaps);          //overlaps checking
    
    // Set Shape5 as scoring volume
    //
    //fScoringVolume = logicShape5; //NOT sure what this does
    
    
    
    // SHAPE 6 -Al top cylinder
    //
    G4ThreeVector pos6 = G4ThreeVector(0, 0, 6.665*cm);
    
    // ALUMINUM TOP CYLINDER
    G4double shape6_pRMin = 3.81*cm, shape6_pSPhi = 0*degree;
    G4double shape6_pRMax = 7.62*cm, shape6_pDPhi = 360*degree;
    G4double shape6_pDz  = 0.315*cm;
    G4Tubs* solidShape6 =
    new G4Tubs("Shape6",                      //its name
               shape6_pRMin,
               shape6_pRMax,
               shape6_pDz,
               shape6_pSPhi,
               shape6_pDPhi);              //its size
    
    G4LogicalVolume* logicShape6 =
    new G4LogicalVolume(solidShape6,         //its solid
                        shape6_mat,          //its material
                        "Shape6");           //its name
    
    G4VisAttributes* visAttShape6 = new G4VisAttributes( G4Color(1, 1, 1));
    visAttShape6->SetForceWireframe(true);
    logicShape6->SetVisAttributes(visAttShape6);
    
    new G4PVPlacement(0,                       //no rotation
                      pos6,                    //at position
                      logicShape6,             //its logical volume
                      "Shape6",                //its name
                      lWorld,                  //its mother  volume
                      false,                   //no boolean operation
                      0);                       //copy number
                      //checkOverlaps);          //overlaps checking
    


  PrintParameters();
  
  //always return the root volume
  //
  return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void DetectorConstruction::PrintParameters()
{
  G4cout << "\n Target : Length = " << G4BestUnit(fTargetLength,"Length")
         << " Radius = " << G4BestUnit(fTargetRadius,"Length")  
         << " Material = " << fTargetMater->GetName();
  G4cout << "\n Detector : Length = " << G4BestUnit(fDetectorLength,"Length")
         << " Tickness = " << G4BestUnit(fDetectorThickness,"Length")  
         << " Material = " << fDetectorMater->GetName() << G4endl;          
  G4cout << "\n" << fTargetMater << "\n" << fDetectorMater << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  
  if (pttoMaterial) { 
    fTargetMater = pttoMaterial;
    if(fLogicTarget) { fLogicTarget->SetMaterial(fTargetMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetTargetMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fDetectorMater = pttoMaterial;
    if(fLogicDetector) { fLogicDetector->SetMaterial(fDetectorMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetDetectorMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetRadius(G4double value)
{
  fTargetRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetLength(G4double value)
{
  fTargetLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorThickness(G4double value)
{
  fDetectorThickness = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorLength(G4double value)
{
  fDetectorLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetTargetLength()
{
  return fTargetLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetTargetRadius()
{
  return fTargetRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetTargetMaterial()
{
  return fTargetMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicTarget()
{
  return fLogicTarget;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorLength()
{
  return fDetectorLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorThickness()
{
  return fDetectorThickness;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetDetectorMaterial()
{
  return fDetectorMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicDetector()
{
  return fLogicDetector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
