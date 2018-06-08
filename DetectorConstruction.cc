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
// $Id: DetectorConstruction.cc 77656 2013-11-27 08:52:57Z gcosmo $
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "CellParameterisation.hh"
#include "HodoscopeSD.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4AutoDelete.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

///G4ThreadLocal G4FieldManager* DetectorConstruction::fFieldMgr = 0;
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), 
  fMessenger(0),
  fHodoscope1Logical(0), fHodoscope2Logical(0),
  fCollimatorLogical(0),
  /*fCellLogical(0), fHadCalScintiLogical(0),*/
  fVisAttributes(),
  fArmAngle(0.*deg), fArmRotation(0), fSecondArmPhys(0)

{
    fArmRotation = new G4RotationMatrix();
    fArmRotation->rotateY(fArmAngle);
    
    // define commands for this class
    DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
    delete fArmRotation;
    delete fMessenger;
    
    for (G4int i=0; i<G4int(fVisAttributes.size()); ++i) 
    {
      delete fVisAttributes[i];
    }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Construct materials
    ConstructMaterials();
    ///G4Material* vacuum = G4Material::GetMaterial("G4_Galactic");
    G4Material* air = G4Material::GetMaterial("G4_AIR");
    //G4Material* argonGas = G4Material::GetMaterial("_Ar");
    ///G4Material* argonGas = G4Material::GetMaterial("G4_Ar");
    G4Material* scintillator 
      = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4Material* polyethylene = G4Material::GetMaterial("G4_POLYETHYLENE");
    ///G4Material* polyethylene = G4Material::GetMaterial("G4_Pb");
    ///G4Material* lead = G4Material::GetMaterial("G4_Pb");
    
    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    // geometries --------------------------------------------------------------
    // experimental hall (world volume)
    G4VSolid* worldSolid 
      = new G4Box("worldBox",10.*m,3.*m,10.*m);
    G4LogicalVolume* worldLogical
      = new G4LogicalVolume(worldSolid,air,"worldLogical");
    G4VPhysicalVolume* worldPhysical
      = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,
                          false,0,checkOverlaps);


    ///~~~~~~~~~~~~~~~~~~ first arm, Collimator, made of Polyethylene ~~~~~~~~~~~~~~~~~
    G4VSolid* firstArmSolid 
      = new G4Box("firstArmBox",15.*cm,15.*cm,20.*cm);
    G4LogicalVolume* firstArmLogical
      = new G4LogicalVolume(firstArmSolid,air,"firstArmLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,20.*cm),firstArmLogical,//23.2 is from target to the mid of collimator
                      "firstArmPhysical",worldLogical,
                      false,0,checkOverlaps);

   
    // Polyethylene collimator, in first  arm
    ///G4VSolid* hodoscope1Solid 
    G4VSolid* collimatorSolid 
      = new G4Tubs("collimatorSlice",0.5*cm,14.*cm,0.5*cm,0.,2.0*pi);
    fCollimatorLogical
     /// = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope1Logical");
      = new G4LogicalVolume(collimatorSolid,polyethylene,"collimatorLogical");
      ///= new G4LogicalVolume(collimatorSolid,scintillator,"collimatorLogical");
    for (G4int i=0;i<38;i++)
    {
        ///G4double z1 = (i-19)*1.*cm;
        G4double z1 = ( (i-20)*1. + 0.5 )*cm;
        new G4PVPlacement(0,G4ThreeVector(0.,0.,z1),fCollimatorLogical,
                          "collimatorPhysical",firstArmLogical,
                          false,i,checkOverlaps);
    }
    
    
    
    /// ~~~~~~~~~~~~~~~~~ second arm, scintillator bars array ~~~~~~~~~~~~~~~~~~~~~~
    G4VSolid* secondArmSolid 
      = new G4Box("secondArmBox",50.*cm,10.*cm,15.*cm);//x = 50 reserved for 2PMTs
    G4LogicalVolume* secondArmLogical
      = new G4LogicalVolume(secondArmSolid,air,"secondArmLogical");
    fSecondArmPhys
      = new G4PVPlacement(fArmRotation,G4ThreeVector(0.,0.,55.*cm),secondArmLogical,
                          "fSecondArmPhys",worldLogical,
                          false,0,checkOverlaps);
    
    // 1st scintillator bar in second  arm
    G4VSolid* hodoscope1Solid 
      = new G4Box("hodoscope1Box",0.5*cm,1.5*cm,1.5*cm);
    fHodoscope1Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope1Logical");
    for (G4int i=0;i<25;i++)
    {
        G4double x1 = (i-12)*1.*cm;
        new G4PVPlacement(0,G4ThreeVector(x1,0.,-9.3*cm),fHodoscope1Logical,///-9.3 = 38 + 7.7 - 55
                          "hodoscope1Physical",secondArmLogical,
                          false,i,checkOverlaps);
    }
    

    
    // 2nd scintillator bar in second arm
    G4VSolid* hodoscope2Solid 
      = new G4Box("hodoscope2Box",0.5*cm,1.5*cm,1.5*cm);
    fHodoscope2Logical
      = new G4LogicalVolume(hodoscope2Solid,scintillator,"hodoscope2Logical");
    for (G4int i=0;i<25;i++)
    {
        G4double x2 = (i-12)*1.*cm;
        new G4PVPlacement(0,G4ThreeVector(x2,6.5*cm,11.1*cm),fHodoscope2Logical,///11.1 - (-9.3) = 20.4
                          "hodoscope2Physical",secondArmLogical,
                          false,i,checkOverlaps);
    }

    //
    // visualization attributes ------------------------------------------------
    // Step 6: uncomment visualization attributes of the newly created volumes
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    visAttributes->SetVisibility(false);
    worldLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.9));   // LightGray
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    visAttributes->SetVisibility(false);
    firstArmLogical->SetVisAttributes(visAttributes);
    secondArmLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.8888,0.0,0.0));
    fHodoscope1Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0,0.5,0.9));
    fHodoscope2Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0,0.8888,0.0));
    visAttributes->SetVisibility(false);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.5888,0.8888,0.5));
    ///visAttributes->SetVisibility(false);
    fCollimatorLogical->SetVisAttributes(visAttributes);
    ///emCalorimeterLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0));
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));
    visAttributes->SetVisibility(false);
    fVisAttributes.push_back(visAttributes);
    
    // return the world physical volume ----------------------------------------
    
    return worldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
   
    // sensitive detectors -----------------------------------------------------
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String SDname;
    
    G4VSensitiveDetector* hodoscope1 
      = new HodoscopeSD(SDname="/hodoscope1");
    SDman->AddNewDetector(hodoscope1);
    fHodoscope1Logical->SetSensitiveDetector(hodoscope1);

    G4VSensitiveDetector* hodoscope2 
      = new HodoscopeSD(SDname="/hodoscope2");
    SDman->AddNewDetector(hodoscope2);
    fHodoscope2Logical->SetSensitiveDetector(hodoscope2);
    
    G4VSensitiveDetector* collimator 
      = new HodoscopeSD(SDname="/collimator");
    SDman->AddNewDetector(collimator);
    fCollimatorLogical->SetSensitiveDetector(collimator);
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    // Air 
    nistManager->FindOrBuildMaterial("G4_AIR");
  
    // Argon gas
    nistManager->FindOrBuildMaterial("G4_Ar");
    // With a density different from the one defined in NIST
    // G4double density = 1.782e-03*g/cm3; 
    // nistManager->BuildMaterialWithNewDensity("_Ar","G4_Ar",density);
    // !! cases segmentation fault

    // Scintillator
    // (PolyVinylToluene, C_9H_10)
    nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    
    // CsI
    nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    
    // Lead
    nistManager->FindOrBuildMaterial("G4_Pb");
    
    // polyethylene
    nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    
    /// Vacuum "Galactic"
    ///nistManager->FindOrBuildMaterial("G4_Galactic");

    // Vacuum "Air with low density"
    // G4Material* air = G4Material::GetMaterial("G4_AIR");
    // G4double density = 1.0e-5*air->GetDensity();
    // nistManager
    //   ->BuildMaterialWithNewDensity("Air_lowDensity", "G4_AIR", density);

    G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetArmAngle(G4double val)
{
    if (!fSecondArmPhys)
    {
        G4cerr << "Detector has not yet been constructed." << G4endl;
        return;
    }
    
    fArmAngle = val;
    *fArmRotation = G4RotationMatrix();  // make it unit vector
    fArmRotation->rotateY(fArmAngle);
    ///G4double x = -5.*m * std::sin(fArmAngle);
    ///G4double z = 5.*m * std::cos(fArmAngle);
    G4double x = -1.*m * std::sin(fArmAngle);
    G4double z = 1.*m * std::cos(fArmAngle);
    fSecondArmPhys->SetTranslation(G4ThreeVector(x,0.,z));
    
    // tell G4RunManager that we change the geometry
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineCommands()
{
    // Define //detector command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this, 
                                        "/tutorial/detector/",
                                        "Detector control");

    // armAngle command
    G4GenericMessenger::Command& armAngleCmd
      = fMessenger->DeclareMethodWithUnit("armAngle","deg",
                                  &DetectorConstruction::SetArmAngle, 
                                  "Set rotation angle of the second arm.");
    armAngleCmd.SetParameterName("angle", true);
    armAngleCmd.SetRange("angle>=0. && angle<180.");
    armAngleCmd.SetDefaultValue("30.");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
