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
#include "CollimatorSD.hh"
#include "PmtshieldSD.hh"
#include "SddSD.hh"

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
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"
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
#include "G4GeneralParticleSource.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4PhysicalConstants.hh"

#include "G4AssemblyVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

///G4ThreadLocal G4FieldManager* DetectorConstruction::fFieldMgr = 0;
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), 
  ///Only Sensitive Detector's Logical volumes needed to be declared here, but all should be clared in its ".hh".
  fMessenger(0),
  fHodoscope1Logical(0), fHodoscope2Logical(0),fHodoscope3Logical(0),
  fHodoscope4Logical(0), fHodoscope5Logical(0),fHodoscope6Logical(0),
  fHodoscope7Logical(0), fHodoscope8Logical(0),fHodoscope9Logical(0),
  fHodoscope10Logical(0), fHodoscope11Logical(0),fHodoscope12Logical(0),
  fHodoscope13Logical(0), fHodoscope14Logical(0),fHodoscope15Logical(0),
  fHodoscope16Logical(0), fHodoscope17Logical(0),fHodoscope18Logical(0),
  fHodoscope19Logical(0), fHodoscope20Logical(0),fHodoscope21Logical(0),
  fCollimatorLogical(0), 
  fSiliconDetectorLayerLogical(0),
  fShieldBar1PosXLogical(0),fShieldBar1NegXLogical(0),
  fShieldBar2PosXLogical(0),fShieldBar2NegXLogical(0),
  fShieldBar3PosXLogical(0),fShieldBar3NegXLogical(0),
  fShieldBar4PosXLogical(0),fShieldBar4NegXLogical(0),
  fShieldBar5PosXLogical(0),fShieldBar5NegXLogical(0),
  fShieldBar6PosXLogical(0),fShieldBar6NegXLogical(0),
  fShieldBar7PosXLogical(0),fShieldBar7NegXLogical(0),
  fShieldBar8PosXLogical(0),fShieldBar8NegXLogical(0),
  fShieldBar9PosXLogical(0),fShieldBar9NegXLogical(0),
  fShieldBar10PosXLogical(0),fShieldBar10NegXLogical(0),
  fShieldBar11PosXLogical(0),fShieldBar11NegXLogical(0),
  fShieldBar12PosXLogical(0),fShieldBar12NegXLogical(0),
  fShieldBar13PosXLogical(0),fShieldBar13NegXLogical(0),
  fShieldBar14PosXLogical(0),fShieldBar14NegXLogical(0),
  fShieldBar15PosXLogical(0),fShieldBar15NegXLogical(0),
  fShieldBar16PosXLogical(0),fShieldBar16NegXLogical(0),
  fShieldBar17PosXLogical(0),fShieldBar17NegXLogical(0),
  fShieldBar18PosXLogical(0),fShieldBar18NegXLogical(0),
  fShieldBar19PosXLogical(0),fShieldBar19NegXLogical(0),
  fShieldBar20PosXLogical(0),fShieldBar20NegXLogical(0),
  fShieldBar21PosXLogical(0),fShieldBar21NegXLogical(0),
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
    G4Material* concrete = G4Material::GetMaterial("G4_CONCRETE");
    G4Material* scintillator 
      = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4Material* polyethylene = G4Material::GetMaterial("G4_POLYETHYLENE");
    G4Material* base_mat = G4Material::GetMaterial("G4_POLYCARBONATE");
    G4Material* quartz = G4Material::GetMaterial("quartz");
    G4Material* Tec = G4Material::GetMaterial("Tec");
    G4Material* Kovar = G4Material::GetMaterial("Kovar");
    /*G4Material* MAl = G4Material::GetMaterial("MAl");
    G4Material* MCr = G4Material::GetMaterial("MCr");
    G4Material* MTi = G4Material::GetMaterial("MTi");*/
    G4Material* Nickel = G4Material::GetMaterial("G4_Ni");
    G4Material* Silicon = G4Material::GetMaterial("G4_Si");
    G4Material* Tungsten = G4Material::GetMaterial("G4_W");
    G4Material* Beryllium = G4Material::GetMaterial("G4_Be");
    G4Material* Alumina = G4Material::GetMaterial("Alumina");
    G4Material* stainlessSteel = G4Material::GetMaterial("G4_STAINLESS-STEEL");
    G4Material* MuMetal = G4Material::GetMaterial("MuMetal");
  
    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    // geometries --------------------------------------------------------------
    // experimental hall (world volume)
    G4VSolid* worldSolid 
      = new G4Box("worldBox",10.*m,10.*m,10.*m);//B4, y = 3.0
    G4LogicalVolume* worldLogical
      = new G4LogicalVolume(worldSolid,air,"worldLogical");
    G4VPhysicalVolume* worldPhysical
      = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,
                          false,0,checkOverlaps);


    ///~~~~~~~~~~~~~~~~~~ Walls, floor and roof (10m,6m,10m)~~~~~~~~~~~~~~~~~

    ///~~~~~~~~ floor ~~~~~~~~~~
    G4VSolid* floorSolid 
      = new G4Box("floorBox",5.*m,.5*m,5.*m);
    G4LogicalVolume* floorLogical
      = new G4LogicalVolume(floorSolid,concrete,"floorLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,-2.3*m,0.5*m),floorLogical,///Original pt: entrance hole of CLM
                      "floorPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~ roof ~~~~~~~~~~
    G4VSolid* roofSolid 
      = new G4Box("roofBox",5.*m,.5*m,5.*m);
    G4LogicalVolume* roofLogical
      = new G4LogicalVolume(roofSolid,concrete,"roofLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,4.7*m,0.5*m),roofLogical,///Original pt: entrance hole of CLM
                      "roofPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~ wall 1( X +) ~~~~~~~~~~
    G4VSolid* wallPlusXSolid 
      = new G4Box("wallPlusXBox",.5*m,4.*m,5.*m);
    G4LogicalVolume* wallPlusXLogical
      = new G4LogicalVolume(wallPlusXSolid,concrete,"wallPlusXLogical");
    new G4PVPlacement(0,G4ThreeVector(5.5*m,1.2*m,0.5*m),wallPlusXLogical,///Original pt: entrance hole of CLM
                      "wallPlusXPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~ wall 1( X -) ~~~~~~~~~~
    G4VSolid* wallMinusXSolid 
      = new G4Box("wallMinusXBox",.5*m,4.*m,5.*m);
    G4LogicalVolume* wallMinusXLogical
      = new G4LogicalVolume(wallMinusXSolid,concrete,"wallMinusXLogical");
    new G4PVPlacement(0,G4ThreeVector(-5.5*m,1.2*m,0.5*m),wallMinusXLogical,///Original pt: entrance hole of CLM
                      "wallMinusXPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~ wall 1( Z +) ~~~~~~~~~~
    G4VSolid* wallPlusZSolid 
      = new G4Box("wallPlusZBox",5.*m,4.*m,.5*m);
    G4LogicalVolume* wallPlusZLogical
      = new G4LogicalVolume(wallPlusZSolid,concrete,"wallPlusZLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,1.2*m,6.0*m),wallPlusZLogical,///Original pt: entrance hole of CLM
                      "wallPlusZPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~ wall 2( Z -) ~~~~~~~~~~
    G4VSolid* wallMinusZSolid 
      = new G4Box("wallMinusZBox",5.*m,4.*m,.5*m);
    G4LogicalVolume* wallMinusZLogical
      = new G4LogicalVolume(wallMinusZSolid,concrete,"wallMinusZLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,1.2*m,-5.*m),wallMinusZLogical,///Original pt: entrance hole of CLM
                      "wallMinusZPhysical",worldLogical,
                      false,0,checkOverlaps);


    ///~~~~~~~~~~~~~~~~~~ first arm, Collimator, made of Polyethylene ~~~~~~~~~~~~~~~~~
    G4VSolid* firstArmSolid 
      = new G4Box("firstArmBox",25.*cm,25.*cm,20.*cm);
    G4LogicalVolume* firstArmLogical
      = new G4LogicalVolume(firstArmSolid,air,"firstArmLogical");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,20.*cm),firstArmLogical,///Original pt: entrance hole of CLM
                      "firstArmPhysical",worldLogical,
                      false,0,checkOverlaps);

   
    // Polyethylene collimator, in first  arm
    G4VSolid* collimatorSolid 
      = new G4Tubs("collimatorSlice",0.5*cm,21.5*cm,0.5*cm,0.,2.0*pi);
    fCollimatorLogical
      = new G4LogicalVolume(collimatorSolid,polyethylene,"collimatorLogical");
    for (G4int i=0;i<38;i++)
    {
        G4double z1 = ( (i-20)*1. + 0.5 )*cm;///
        new G4PVPlacement(0,G4ThreeVector(0.,0.,z1),fCollimatorLogical,
                          "collimatorPhysical",firstArmLogical,
                          false,i,checkOverlaps);
    }
    
    
    
    /// ~~~~~~~~~~~~~~~~~ second arm, scintillator bars and SDD ~~~~~~~~~~~~~~~~~~~~~~
    G4VSolid* secondArmSolid 
      ///= new G4Box("secondArmBox",50.*cm,65.*cm,15.*cm);//x = 50 reserved for 2PMTs,y=60 for 4 posts.
      = new G4Box("secondArmBox",50.*cm,105.*cm,81.*cm);
    G4LogicalVolume* secondArmLogical
      = new G4LogicalVolume(secondArmSolid,air,"secondArmLogical");
    fSecondArmPhys
      ///= new G4PVPlacement(fArmRotation,G4ThreeVector(0.,0.,55.*cm),secondArmLogical,
      = new G4PVPlacement(fArmRotation,G4ThreeVector(0.,0.,121.*cm),secondArmLogical,
                          "fSecondArmPhys",worldLogical,
                          false,0,checkOverlaps);
    /*
    G4double Bar1Y       = 10.5*cm;
    G4double Bar1Z       = -0.8*cm;///-0.8 = 38 + 3.4 + 12.8 - 55 (in the mother volume : secondArmLogical).
    */
    G4double Bar1Y       = 0.*cm;
    G4double Bar1Z       = 0.*cm;
    
    G4double SddWorldX   = 0.0*mm;/// in the mother volume : secondArmLogical .
    ///G4double SddWorldY   = -11.5*cm;/// in the mother volume : secondArmLogical .
    G4double SddWorldY   = -11.5*cm;/// in the mother volume : secondArmLogical .
    G4double SddWorldZ   = -70.6*cm;/// 70.6 = 81 - 10.4; in the mother volume : secondArmLogical.


    G4RotationMatrix* rotD0 = new G4RotationMatrix();
    rotD0->rotateY(0.*deg);

    G4RotationMatrix* rotD45 = new G4RotationMatrix();
    rotD45->rotateY(45.*deg);

    G4RotationMatrix* rotDX90 = new G4RotationMatrix();
    rotDX90->rotateX(90.*deg);

    G4RotationMatrix* rotDY75 = new G4RotationMatrix();
    rotDY75->rotateY(75.*deg);

    G4RotationMatrix* rotD90 = new G4RotationMatrix();
    rotD90->rotateY(90.*deg);

    G4RotationMatrix* rotDZ90 = new G4RotationMatrix();
    rotDZ90->rotateZ(90.*deg);

    G4RotationMatrix* rotD180 = new G4RotationMatrix();
    rotD180->rotateY(180.*deg);

    G4RotationMatrix* rotD270 = new G4RotationMatrix();
    rotD270->rotateY(270.*deg);

    G4RotationMatrix* rotDZ270 = new G4RotationMatrix();
    rotDZ270->rotateZ(270.*deg);


    ///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~  SDD ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// SDD world in the second arm
    G4VSolid* sddWorldSolid 
      = new G4Box("sddWorldBox",3.0*cm,12.0*cm,1.4*cm);///SDD world solid. The thickness of body is 2*1.4=2.8cm. 
    ///= new G4Box("sddWorldBox",12.0*cm,3.0*cm,1.4*cm);///SDD world solid. The thickness of body is 2*1.4=2.8cm. 
    fSddWorldLogical
      = new G4LogicalVolume(sddWorldSolid,air,"fSddWorldLogical");
        ///new G4PVPlacement(rotDZ90,G4ThreeVector(SddWorldX,SddWorldY,SddWorldZ),fSddWorldLogical,
        new G4PVPlacement(0,G4ThreeVector(SddWorldX,SddWorldY,SddWorldZ),fSddWorldLogical,
                          "sddWorldPhysical",secondArmLogical,
                          false,0,checkOverlaps);


    ///Be window .
    G4double BeWindowInnerRadius    = 0.*mm;
    G4double BeWindowOuterRadius    = 3.5*mm;
    G4double BeWindowHeight    = 0.026*mm;
    G4double BeWindowX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double BeWindowY       = 116.65*mm;/// 116.65 = 115.0+1.4+0.5/2 ; mother volume : fSddWorldLogical .
    G4double BeWindowZ       = 0.*mm;///-136.mm (mother volume : fSddWorldLogical ).

    G4Tubs*  BeWindow= new G4Tubs("BeWindow",BeWindowInnerRadius , BeWindowOuterRadius,
                                              0.5*BeWindowHeight,0.*deg, 360.*deg);

    BeWindowLogical  = new G4LogicalVolume(BeWindow, Beryllium, "BeWindowLogical");///Need to understand the layout of it.
    new G4PVPlacement(rotDX90,G4ThreeVector(BeWindowX,BeWindowY,BeWindowZ),BeWindowLogical,
                       "BeWindowPhys",  fSddWorldLogical, false, 0,checkOverlaps);



    /// Kovar endcap.
    G4double EndcapInnerRadius    = 3.5*mm;
    G4double EndcapOuterRadius    = 7.0*mm;
    G4double EndcapHeight    = 0.25*mm;
    ///G4double EndcapX       = -116.65*mm;/// -116.65 = -115.0-1.4-0.5/2 ; mother volume : fSddWorldLogical .
    ///G4double EndcapY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double EndcapX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double EndcapY       = 116.65*mm;/// 116.65 = 115.0+1.4+0.5/2 ; mother volume : fSddWorldLogical .
    G4double EndcapZ       = 0.*mm;///-136.mm (mother volume : fSddWorldLogical ).

    G4Tubs*  Endcap= new G4Tubs("Endcap",EndcapInnerRadius , EndcapOuterRadius,
                                              0.5*EndcapHeight,0.*deg, 360.*deg);

    EndcapLogical  = new G4LogicalVolume(Endcap, Kovar, "EndcapLogical");///Need to understand the layout of it.
    new G4PVPlacement(rotDX90,G4ThreeVector(EndcapX,EndcapY,EndcapZ),EndcapLogical,
                       "EndcapPhys",  fSddWorldLogical, false, 0,checkOverlaps);



    /// Cover of SDD 
    G4double CoverSddInnerRadius  = 6.75*mm;
    G4double CoverSddOuterRadius  = 7.0*mm;
    G4double CoverSddHeight  = 8.6*mm;
    ///G4double CoverSddX       = -112.1*mm;/// -112.1 = -115.-1.4+8.6/2 ; mother volume : fSddWorldLogical .
    ///G4double CoverSddY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double CoverSddX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double CoverSddY       = 112.1*mm;/// 112.35 = 115.+0.5/2+1.4-8.6/2 ; mother volume : fSddWorldLogical .
    G4double CoverSddZ       = 0.*mm;/// (mother volume : fSddWorldLogical ).
    G4Tubs* CoverSdd = new G4Tubs("CoverSdd", CoverSddInnerRadius, CoverSddOuterRadius, 
                                              0.5*CoverSddHeight,0.*deg, 360.*deg);
    fCoverSddLogical
      = new G4LogicalVolume(CoverSdd,Nickel,"fCoverSddLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(CoverSddX,CoverSddY,CoverSddZ),
                          fCoverSddLogical,"CoverSddPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);



    /// Multilayer Collimator in SDD 
    G4double MultilayerCollimatorRadius  = 2.33*mm;
    G4double MultilayerCollimatorHeight  = 0.225*mm;///The thickness of this layer is 500 micrometers.
    ///G4double MultilayerCollimatorX       = -115.4*mm;/// mother volume : fSddWorldLogical .
    ///G4double MultilayerCollimatorY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double MultilayerCollimatorX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double MultilayerCollimatorY       = 115.4*mm;/// mother volume : fSddWorldLogical .
    G4double MultilayerCollimatorZ       = 0.*mm;///-136.mm (mother volume : fSddWorldLogical ).
    G4Tubs* MultilayerCollimator = new G4Tubs("MultilayerCollimator", 0.*cm,  MultilayerCollimatorRadius, 
                                              0.5*MultilayerCollimatorHeight,0.*deg, 360.*deg);
    fMultilayerCollimatorLogical
      = new G4LogicalVolume(MultilayerCollimator,Tungsten,"fMultilayerCollimatorLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(MultilayerCollimatorX,MultilayerCollimatorY,MultilayerCollimatorZ),fMultilayerCollimatorLogical,"MultilayerCollimatorPhysical",fSddWorldLogical,false,0,checkOverlaps);



    /// Silicon detector layer in SDD 
    G4double SiliconDetectorLayerRadius  = 2.82*mm;
    G4double SiliconDetectorLayerHeight  = 0.5*mm;///The thickness of this layer is 500 micrometers.
    ///G4double SiliconDetectorLayerX       = -115.*mm;/// mother volume : fSddWorldLogical .
    ///G4double SiliconDetectorLayerY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double SiliconDetectorLayerX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double SiliconDetectorLayerY       = 115.0*mm;/// mother volume : fSddWorldLogical .
    G4double SiliconDetectorLayerZ       = 0.*mm;///mother volume : fSddWorldLogical .
    G4Tubs* SiliconDetectorLayer = new G4Tubs("SiliconDetectorLayer", 0.*cm,  SiliconDetectorLayerRadius, 
                                              0.5*SiliconDetectorLayerHeight,0.*deg, 360.*deg);
    fSiliconDetectorLayerLogical
      = new G4LogicalVolume(SiliconDetectorLayer,Silicon,"fSiliconDetectorLayerLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(SiliconDetectorLayerX,SiliconDetectorLayerY,SiliconDetectorLayerZ),fSiliconDetectorLayerLogical,"SiliconDetectorLayerPhysical",fSddWorldLogical,false,0,checkOverlaps);


    /// Substrate layer of SDD 
    G4double SubstrateLayerRadius  = 5.*mm;
    G4double SubstrateLayerHeight  = 0.65*mm;///The thickness of substrate layer is 650 micrometers.
    ///G4double SubstrateLayerX       = SiliconDetectorLayerX + 0.5*(SiliconDetectorLayerHeight+SubstrateLayerHeight) ;
    ///G4double SubstrateLayerY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double SubstrateLayerX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double SubstrateLayerY       = SiliconDetectorLayerY - 0.5*(SiliconDetectorLayerHeight+SubstrateLayerHeight) ;
    G4double SubstrateLayerZ       = 0.*mm;///mother volume : fSddWorldLogical .
    G4Tubs* SubstrateLayer = new G4Tubs("SubstrateLayer", 0.*cm,  SubstrateLayerRadius, 
                                              0.5*SubstrateLayerHeight,0.*deg, 360.*deg);
    fSubstrateLayerLogical
      = new G4LogicalVolume(SubstrateLayer,Alumina,"fSubstrateLayerLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(SubstrateLayerX,SubstrateLayerY,SubstrateLayerZ),
                          fSubstrateLayerLogical,"SubstrateLayerPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);


    /// Thermoelectric Collimator of SDD 
    G4double ThermoelectricColimatorLength      = 6.4*mm;
    G4double ThermoelectricColimatorWidth       = 6.4*mm;
    G4double ThermoelectricColimatorHeight      = 4.8*mm;
    ///G4double ThermoelectricColimatorX           = SubstrateLayerX + 0.5*(SubstrateLayerHeight+ThermoelectricColimatorHeight)                                                   + 0.8*mm;
    ///G4double ThermoelectricColimatorY           = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double ThermoelectricColimatorX           = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double ThermoelectricColimatorY           = SubstrateLayerY - 0.5*(SubstrateLayerHeight+ThermoelectricColimatorHeight) - 0.8*mm;
    G4double ThermoelectricColimatorZ           = 0.*mm;///mother volume : fSddWorldLogical .

    G4VSolid* ThermoelectricColimatorSolid 
      = new G4Box("ThermoelectricColimatorBox",0.5*ThermoelectricColimatorLength,0.5*ThermoelectricColimatorWidth,
                  0.5*ThermoelectricColimatorHeight); 
    fThermoelectricColimatorLogical
      = new G4LogicalVolume(ThermoelectricColimatorSolid,Tec,"fThermoelectricColimatorLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(ThermoelectricColimatorX,ThermoelectricColimatorY,
                          ThermoelectricColimatorZ),fThermoelectricColimatorLogical,
                          "ThermoelectricColimatorPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);


    /// Header of SDD 
    G4double HeaderSddRadius  = 7.*mm;
    G4double HeaderSddHeight  = 1.*mm;///The thickness of header is 1 mm(guess).
    ///G4double HeaderSddX  = ThermoelectricColimatorX + 0.5*(ThermoelectricColimatorHeight + HeaderSddHeight)+1.2*mm;
                            /// the "+1.2*mm" is to solve overlap warning.
    ///G4double HeaderSddY       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double HeaderSddX       = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double HeaderSddY  = ThermoelectricColimatorY - 0.5*(ThermoelectricColimatorHeight + HeaderSddHeight)-1.2*mm;
                            /// the "+1.2*mm" is to solve overlap warning.
    G4double HeaderSddZ       = 0.*mm;///mother volume : fSddWorldLogical .
    G4Tubs* HeaderSdd = new G4Tubs("HeaderSdd", 0.*cm,  HeaderSddRadius, 
                                              0.5*HeaderSddHeight,0.*deg, 360.*deg);
    fHeaderSddLogical
      = new G4LogicalVolume(HeaderSdd,Kovar,"fHeaderSddLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(HeaderSddX,HeaderSddY,HeaderSddZ),
                          fHeaderSddLogical,"HeaderSddPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);


    /// Extender of SDD 
    G4double ExtenderSddInnerRadius  = 3.0*mm;//This 3.0mm is an equivalent value, not an exact one.
    G4double ExtenderSddOuterRadius  = 8.9*mm;
    G4double ExtenderSddHeight       = 136.*mm;
    ///G4double ExtenderSddX            = HeaderSddX + 0.5*(HeaderSddHeight + ExtenderSddHeight);
    ///G4double ExtenderSddY            = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double ExtenderSddX            = 0.*mm;/// mother volume : fSddWorldLogical .
    G4double ExtenderSddY            = HeaderSddY - 0.5*(HeaderSddHeight + ExtenderSddHeight);
    G4double ExtenderSddZ            = 0.*mm;///mother volume : fSddWorldLogical .
    G4Tubs* ExtenderSdd = new G4Tubs("ExtenderSdd",ExtenderSddInnerRadius, ExtenderSddOuterRadius, 
                                      0.5*ExtenderSddHeight,0.*deg, 360.*deg);
    fExtenderSddLogical
      = new G4LogicalVolume(ExtenderSdd,stainlessSteel,"fExtenderSddLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(ExtenderSddX,ExtenderSddY,ExtenderSddZ),
                          fExtenderSddLogical,"ExtenderSddPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);


    /// Box of SDD, simplified to cylinder shape, with radiud = 1.4cm which equals to fSddWorldLogical.
    G4double BoxSddInnerRadius  = 12.*mm;//The thickness of body is 2.0mm.
    G4double BoxSddOuterRadius  = 14.0*mm;
    G4double BoxSddHeight       = 76.2*mm;
    ///G4double BoxSddX            = ExtenderSddX + 0.5*(ExtenderSddHeight + BoxSddHeight);
    ///G4double BoxSddY            = -16.0*mm;/// mother volume : fSddWorldLogical .
    G4double BoxSddX            = -16.0*mm;/// mother volume : fSddWorldLogical .
    G4double BoxSddY            = ExtenderSddY - 0.5*(ExtenderSddHeight + BoxSddHeight);
    G4double BoxSddZ            = 0.*mm;///mother volume : fSddWorldLogical .
    G4Tubs* BoxSdd = new G4Tubs("BoxSdd",BoxSddInnerRadius, BoxSddOuterRadius, 
                                      0.5*BoxSddHeight,0.*deg, 360.*deg);
    fBoxSddLogical
      = new G4LogicalVolume(BoxSdd,stainlessSteel,"fBoxSddLogical");
        new G4PVPlacement(rotDX90,G4ThreeVector(BoxSddX,BoxSddY,BoxSddZ),
                          fBoxSddLogical,"BoxSddPhysical",fSddWorldLogical,
                          false,0,checkOverlaps);



    ///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~  PMT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    G4double pmtInRadius     = 20.0*mm;
    G4double pmtOutRadius    = 25.0*mm;
    G4double pmtHeight       = 121.0*mm;
    G4double flangeRadius    = 25.0*mm;
    G4double flangeHeight    = 47.0*mm;
    G4double baseRadius      = 33.0*mm;
    G4double baseHeight      = 42.0*mm;
    G4double pmtShieldInR    = 28.5*mm;
    G4double pmtShieldOutR   = 29.5*mm;
    G4double pmtShieldHeight = 168.0*mm;

    G4double SupportStripInnerRadius    = 33.2*mm;
    G4double SupportStripOuterRadius    = 42.2*mm;
    G4double SupportStripHeight         = 30.0*mm;

    G4double baseVPosition    = 31.*cm; ///distance between PMT and Bar
    G4double tubeVPosition    = 18.6*cm;
    G4double shieldVPosition  = 20.5*cm;
    G4double supportStripVPosition    = 31.*cm; ///distance between PMT and Bar

    G4double flangeShiftBase  = 39.*mm;///flange is displaced with an offset to pmt base(tube?) along z axis.


    G4Tubs* pmt_tube = new G4Tubs("pmt_tube", pmtInRadius,  pmtOutRadius, 0.5*pmtHeight,
     0.*deg, 360.*deg);
    G4Tubs* pmt_base = new G4Tubs("pmt_base", 0.*cm,  baseRadius, 0.5*baseHeight,
     0.*deg, 360.*deg);
    G4Tubs* pmt_flange = new G4Tubs("pmt_flange", 0.*cm,  flangeRadius, 0.5*flangeHeight,
     0.*deg, 360.*deg);
    G4Tubs* pmt_shield = new G4Tubs("pmt_shield", pmtShieldInR,  pmtShieldOutR, 0.5*pmtShieldHeight,
     0.*deg, 360.*deg);
    G4Tubs*  SupportStrip= new G4Tubs("SupportStrip",SupportStripInnerRadius , SupportStripOuterRadius,
                                              0.5*SupportStripHeight,-90.*deg, 180.*deg);
    ///new G4PVPlacement(rotDY75,G4ThreeVector(SupportStripX,SupportStripY,SupportStripZ),SupportStripLogical,
    ///                   "SupportStripPhys", secondArmLogical, false, 0,checkOverlaps);
    


    /// ~~~~~~~~~~~~ The PMT on the positive X direction of bar1. ~~~~~~~~~~~~ 

    /// Tube of a PMT_pxb1, made of quartz.
    TubeBar1PosXLogical  = new G4LogicalVolume(pmt_tube, quartz, "TubeBar1PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(tubeVPosition,Bar1Y,Bar1Z),TubeBar1PosXLogical,
    ///                   "fTubeBar1PosXPhys", secondArmLogical, false, 0,checkOverlaps);

    /// Base and flange of a PMT_pxb1, made of glass.
    G4UnionSolid* pmt_sol_bar1_posX = new G4UnionSolid("pmt_sol_bar1_posX", pmt_base, pmt_flange,
                            G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,flangeShiftBase)));

    BaseBar1PosXLogical  = new G4LogicalVolume(pmt_sol_bar1_posX, base_mat, "BaseBar1PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(baseVPosition,Bar1Y,Bar1Z),BaseBar1PosXLogical,
    ///                   "fBaseBar1PosXPhys",  secondArmLogical, false, 0,checkOverlaps);

    /// Shield of a PMT_pxb1, made of mu-mental.
    fShieldBar1PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar1PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(shieldVPosition,Bar1Y,Bar1Z),fShieldBar1PosXLogical,
    ///                   "fShieldBar1PosXPhys", secondArmLogical, false, 0,checkOverlaps);

    SupportStripPosXLogical  = new G4LogicalVolume(SupportStrip, Alumina, "SupportStripPosXLogical");


    /// ~~~~~~~~~~~~ The PMT on the negative X direction of bar1. ~~~~~~~~~~~~ 
    /// Tube of a PMT_nxb1, made of quartz.
    TubeBar1NegXLogical  = new G4LogicalVolume(pmt_tube, quartz, "TubeBar1NegXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(-1.*tubeVPosition,Bar1Y,Bar1Z),TubeBar1NegXLogical,
    ///                   "fTubeBar1NegXPhys", secondArmLogical, false, 0,checkOverlaps);

    /// Base and flange of a PMT_pxb1, made of glass.
    G4UnionSolid* pmt_sol_bar1_negX = new G4UnionSolid("pmt_sol_bar1_negX", pmt_base, pmt_flange,
                            G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,-1.*flangeShiftBase)));

    BaseBar1NegXLogical  = new G4LogicalVolume(pmt_sol_bar1_negX, base_mat, "BaseBar1NegXLogical");
    /// new G4PVPlacement(rotD90,G4ThreeVector(-1.*baseVPosition,Bar1Y,Bar1Z),BaseBar1NegXLogical,
    ///                   "fBaseBar1NegXPhys",  secondArmLogical, false, 0,checkOverlaps);

    /// Shield of a PMT_nxb1, made of mu-mental.
    fShieldBar1NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar1NegXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(-1.*shieldVPosition,Bar1Y,Bar1Z),fShieldBar1NegXLogical,
    ///                   "fShieldBar1NegXPhys", secondArmLogical, false, 0,checkOverlaps);

    SupportStripNegXLogical  = new G4LogicalVolume(SupportStrip, Alumina, "SupportStripNegXLogical");


    ///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~  scintillator bar 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    G4VSolid* hodoscope1Solid 
      = new G4Box("hodoscope1Box",12.5*cm,1.5*cm,1.5*cm);
         
    /// scintillator_bar_1
    fHodoscope1Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope1Logical");

    /// scintillator_bar_2
    fHodoscope2Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope2Logical");
         
    /// scintillator_bar_3
    fHodoscope3Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope3Logical");


    ///place_scintillator_bar
    /// scintillator_bar_4
    fHodoscope4Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope4Logical");

    /// scintillator_bar_5
    fHodoscope5Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope5Logical");

    /// scintillator_bar_6
    fHodoscope6Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope6Logical");

    /// scintillator_bar_7
    fHodoscope7Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope7Logical");

    /// scintillator_bar_8
    fHodoscope8Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope8Logical");

    /// scintillator_bar_9
    fHodoscope9Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope9Logical");

    /// scintillator_bar_10
    fHodoscope10Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope10Logical");

    /// scintillator_bar_11
    fHodoscope11Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope11Logical");

    /// scintillator_bar_12
    fHodoscope12Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope12Logical");

    /// scintillator_bar_13
    fHodoscope13Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope13Logical");

    /// scintillator_bar_14
    fHodoscope14Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope14Logical");

    /// scintillator_bar_15
    fHodoscope15Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope15Logical");

    /// scintillator_bar_16
    fHodoscope16Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope16Logical");

    /// scintillator_bar_17
    fHodoscope17Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope17Logical");

    /// scintillator_bar_18
    fHodoscope18Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope18Logical");

    /// scintillator_bar_19
    fHodoscope19Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope19Logical");

    /// scintillator_bar_20
    fHodoscope20Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope20Logical");

    /// scintillator_bar_21
    fHodoscope21Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope21Logical");

    /// scintillator_bar_22
    fHodoscope22Logical
      = new G4LogicalVolume(hodoscope1Solid,scintillator,"hodoscope22Logical");




    /// ~~~~~~~~~~~~ Scintillator bar array. ~~~~~~~~~~~~ 

    G4ThreeVector TriVBar1(0,Bar1Y,Bar1Z);
    G4ThreeVector TriVTubeBar1PosX(tubeVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVBaseBar1PosX(baseVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVSupportStripPosX(supportStripVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVShieldBar1PosX(shieldVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVTubeBar1NegX(-1.*tubeVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVBaseBar1NegX(-1.*baseVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVSupportStripNegX(-1.*supportStripVPosition,Bar1Y,Bar1Z);
    G4ThreeVector TriVShieldBar1NegX(-1.*shieldVPosition,Bar1Y,Bar1Z);
  
    ///assembly, tube and base.  
    G4AssemblyVolume* assembly = new G4AssemblyVolume();
    assembly->AddPlacedVolume(TubeBar1PosXLogical, TriVTubeBar1PosX, rotD270);
    assembly->AddPlacedVolume(BaseBar1PosXLogical, TriVBaseBar1PosX, rotD270);
    assembly->AddPlacedVolume(SupportStripPosXLogical, TriVSupportStripPosX, rotD270);
    assembly->AddPlacedVolume(TubeBar1NegXLogical, TriVTubeBar1NegX, rotD270);
    assembly->AddPlacedVolume(SupportStripNegXLogical, TriVSupportStripNegX, rotD270);
    assembly->AddPlacedVolume(BaseBar1NegXLogical, TriVBaseBar1NegX, rotD270);
  
    ///assembly outer layer, tube and base.  
    G4AssemblyVolume* assemblyOuterLayer = new G4AssemblyVolume();
    assemblyOuterLayer->AddPlacedVolume(TubeBar1PosXLogical, TriVTubeBar1PosX, rotD270);
    assemblyOuterLayer->AddPlacedVolume(BaseBar1PosXLogical, TriVBaseBar1PosX, rotD270);
    assemblyOuterLayer->AddPlacedVolume(SupportStripPosXLogical, TriVSupportStripPosX, rotD90);
    assemblyOuterLayer->AddPlacedVolume(TubeBar1NegXLogical, TriVTubeBar1NegX, rotD270);
    assemblyOuterLayer->AddPlacedVolume(SupportStripNegXLogical, TriVSupportStripNegX, rotD90);
    assemblyOuterLayer->AddPlacedVolume(BaseBar1NegXLogical, TriVBaseBar1NegX, rotD270);

    ///assemblyBar1SD  
    G4AssemblyVolume* assemblyBar1SD = new G4AssemblyVolume();
    assemblyBar1SD->AddPlacedVolume(fShieldBar1PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar1SD->AddPlacedVolume(fHodoscope1Logical, TriVBar1, rotD0);
    assemblyBar1SD->AddPlacedVolume(fShieldBar1NegXLogical, TriVShieldBar1NegX, rotD270);
 
    ///assemblyBar2SD  
    G4AssemblyVolume* assemblyBar2SD = new G4AssemblyVolume();
    fShieldBar2PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar2PosXLogical");
    fShieldBar2NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar2NegXLogical");
    assemblyBar2SD->AddPlacedVolume(fShieldBar2PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar2SD->AddPlacedVolume(fHodoscope2Logical, TriVBar1, rotD0);
    assemblyBar2SD->AddPlacedVolume(fShieldBar2NegXLogical, TriVShieldBar1NegX, rotD270);
 
    ///assemblyBar3SD  
    G4AssemblyVolume* assemblyBar3SD = new G4AssemblyVolume();
    fShieldBar3PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar3PosXLogical");
    fShieldBar3NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar3NegXLogical");
    assemblyBar3SD->AddPlacedVolume(fShieldBar3PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar3SD->AddPlacedVolume(fHodoscope3Logical, TriVBar1, rotD0);
    assemblyBar3SD->AddPlacedVolume(fShieldBar3NegXLogical, TriVShieldBar1NegX, rotD270);
 
    ///place_assembly_bar
    ///assemblyBar4SD  
    G4AssemblyVolume* assemblyBar4SD = new G4AssemblyVolume();
    fShieldBar4PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar4PosXLogical");
    fShieldBar4NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar4NegXLogical");
    assemblyBar4SD->AddPlacedVolume(fShieldBar4PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar4SD->AddPlacedVolume(fHodoscope4Logical, TriVBar1, rotD0);
    assemblyBar4SD->AddPlacedVolume(fShieldBar4NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar5SD  
    G4AssemblyVolume* assemblyBar5SD = new G4AssemblyVolume();
    fShieldBar5PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar5PosXLogical");
    fShieldBar5NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar5NegXLogical");
    assemblyBar5SD->AddPlacedVolume(fShieldBar5PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar5SD->AddPlacedVolume(fHodoscope5Logical, TriVBar1, rotD0);
    assemblyBar5SD->AddPlacedVolume(fShieldBar5NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar6SD  
    G4AssemblyVolume* assemblyBar6SD = new G4AssemblyVolume();
    fShieldBar6PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar6PosXLogical");
    fShieldBar6NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar6NegXLogical");
    assemblyBar6SD->AddPlacedVolume(fShieldBar6PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar6SD->AddPlacedVolume(fHodoscope6Logical, TriVBar1, rotD0);
    assemblyBar6SD->AddPlacedVolume(fShieldBar6NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar7SD  
    G4AssemblyVolume* assemblyBar7SD = new G4AssemblyVolume();
    fShieldBar7PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar7PosXLogical");
    fShieldBar7NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar7NegXLogical");
    assemblyBar7SD->AddPlacedVolume(fShieldBar7PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar7SD->AddPlacedVolume(fHodoscope7Logical, TriVBar1, rotD0);
    assemblyBar7SD->AddPlacedVolume(fShieldBar7NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar8SD  
    G4AssemblyVolume* assemblyBar8SD = new G4AssemblyVolume();
    fShieldBar8PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar8PosXLogical");
    fShieldBar8NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar8NegXLogical");
    assemblyBar8SD->AddPlacedVolume(fShieldBar8PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar8SD->AddPlacedVolume(fHodoscope8Logical, TriVBar1, rotD0);
    assemblyBar8SD->AddPlacedVolume(fShieldBar8NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar9SD  
    G4AssemblyVolume* assemblyBar9SD = new G4AssemblyVolume();
    fShieldBar9PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar9PosXLogical");
    fShieldBar9NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar9NegXLogical");
    assemblyBar9SD->AddPlacedVolume(fShieldBar9PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar9SD->AddPlacedVolume(fHodoscope9Logical, TriVBar1, rotD0);
    assemblyBar9SD->AddPlacedVolume(fShieldBar9NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar10SD  
    G4AssemblyVolume* assemblyBar10SD = new G4AssemblyVolume();
    fShieldBar10PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar10PosXLogical");
    fShieldBar10NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar10NegXLogical");
    assemblyBar10SD->AddPlacedVolume(fShieldBar10PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar10SD->AddPlacedVolume(fHodoscope10Logical, TriVBar1, rotD0);
    assemblyBar10SD->AddPlacedVolume(fShieldBar10NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar11SD  
    G4AssemblyVolume* assemblyBar11SD = new G4AssemblyVolume();
    fShieldBar11PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar11PosXLogical");
    fShieldBar11NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar11NegXLogical");
    assemblyBar11SD->AddPlacedVolume(fShieldBar11PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar11SD->AddPlacedVolume(fHodoscope11Logical, TriVBar1, rotD0);
    assemblyBar11SD->AddPlacedVolume(fShieldBar11NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar12SD  
    G4AssemblyVolume* assemblyBar12SD = new G4AssemblyVolume();
    fShieldBar12PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar12PosXLogical");
    fShieldBar12NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar12NegXLogical");
    assemblyBar12SD->AddPlacedVolume(fShieldBar12PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar12SD->AddPlacedVolume(fHodoscope12Logical, TriVBar1, rotD0);
    assemblyBar12SD->AddPlacedVolume(fShieldBar12NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar13SD  
    G4AssemblyVolume* assemblyBar13SD = new G4AssemblyVolume();
    fShieldBar13PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar13PosXLogical");
    fShieldBar13NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar13NegXLogical");
    assemblyBar13SD->AddPlacedVolume(fShieldBar13PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar13SD->AddPlacedVolume(fHodoscope13Logical, TriVBar1, rotD0);
    assemblyBar13SD->AddPlacedVolume(fShieldBar13NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar14SD  
    G4AssemblyVolume* assemblyBar14SD = new G4AssemblyVolume();
    fShieldBar14PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar14PosXLogical");
    fShieldBar14NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar14NegXLogical");
    assemblyBar14SD->AddPlacedVolume(fShieldBar14PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar14SD->AddPlacedVolume(fHodoscope14Logical, TriVBar1, rotD0);
    assemblyBar14SD->AddPlacedVolume(fShieldBar14NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar15SD  
    G4AssemblyVolume* assemblyBar15SD = new G4AssemblyVolume();
    fShieldBar15PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar15PosXLogical");
    fShieldBar15NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar15NegXLogical");
    assemblyBar15SD->AddPlacedVolume(fShieldBar15PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar15SD->AddPlacedVolume(fHodoscope15Logical, TriVBar1, rotD0);
    assemblyBar15SD->AddPlacedVolume(fShieldBar15NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar16SD  
    G4AssemblyVolume* assemblyBar16SD = new G4AssemblyVolume();
    fShieldBar16PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar16PosXLogical");
    fShieldBar16NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar16NegXLogical");
    assemblyBar16SD->AddPlacedVolume(fShieldBar16PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar16SD->AddPlacedVolume(fHodoscope16Logical, TriVBar1, rotD0);
    assemblyBar16SD->AddPlacedVolume(fShieldBar16NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar17SD  
    G4AssemblyVolume* assemblyBar17SD = new G4AssemblyVolume();
    fShieldBar17PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar17PosXLogical");
    fShieldBar17NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar17NegXLogical");
    assemblyBar17SD->AddPlacedVolume(fShieldBar17PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar17SD->AddPlacedVolume(fHodoscope17Logical, TriVBar1, rotD0);
    assemblyBar17SD->AddPlacedVolume(fShieldBar17NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar18SD  
    G4AssemblyVolume* assemblyBar18SD = new G4AssemblyVolume();
    fShieldBar18PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar18PosXLogical");
    fShieldBar18NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar18NegXLogical");
    assemblyBar18SD->AddPlacedVolume(fShieldBar18PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar18SD->AddPlacedVolume(fHodoscope18Logical, TriVBar1, rotD0);
    assemblyBar18SD->AddPlacedVolume(fShieldBar18NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar19SD  
    G4AssemblyVolume* assemblyBar19SD = new G4AssemblyVolume();
    fShieldBar19PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar19PosXLogical");
    fShieldBar19NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar19NegXLogical");
    assemblyBar19SD->AddPlacedVolume(fShieldBar19PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar19SD->AddPlacedVolume(fHodoscope19Logical, TriVBar1, rotD0);
    assemblyBar19SD->AddPlacedVolume(fShieldBar19NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar20SD  
    G4AssemblyVolume* assemblyBar20SD = new G4AssemblyVolume();
    fShieldBar20PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar20PosXLogical");
    fShieldBar20NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar20NegXLogical");
    assemblyBar20SD->AddPlacedVolume(fShieldBar20PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar20SD->AddPlacedVolume(fHodoscope20Logical, TriVBar1, rotD0);
    assemblyBar20SD->AddPlacedVolume(fShieldBar20NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar21SD  
    G4AssemblyVolume* assemblyBar21SD = new G4AssemblyVolume();
    fShieldBar21PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar21PosXLogical");
    fShieldBar21NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar21NegXLogical");
    assemblyBar21SD->AddPlacedVolume(fShieldBar21PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar21SD->AddPlacedVolume(fHodoscope21Logical, TriVBar1, rotD0);
    assemblyBar21SD->AddPlacedVolume(fShieldBar21NegXLogical, TriVShieldBar1NegX, rotD270);


    ///assemblyBar22SD  
    G4AssemblyVolume* assemblyBar22SD = new G4AssemblyVolume();
    fShieldBar22PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar22PosXLogical");
    fShieldBar22NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar22NegXLogical");
    assemblyBar22SD->AddPlacedVolume(fShieldBar22PosXLogical, TriVShieldBar1PosX, rotD270);
    assemblyBar22SD->AddPlacedVolume(fHodoscope22Logical, TriVBar1, rotD0);
    assemblyBar22SD->AddPlacedVolume(fShieldBar22NegXLogical, TriVShieldBar1NegX, rotD270);

 
    /// 3 vectors of inner bar array
    G4ThreeVector TriVAssemblyBarInner1st(0.,23.2937*cm,16.3333*cm);
    G4ThreeVector TriVAssemblyBarInner2nd(0.,31.5187*cm,13.7005*cm);
    G4ThreeVector TriVAssemblyBarInner3rd(0.,39.4534*cm,10.2915*cm);
    G4ThreeVector TriVAssemblyBarInner4th(0.,47.0249*cm,6.13761*cm);
    G4ThreeVector TriVAssemblyBarInner5th(0.,54.1634*cm,1.2772*cm);
    G4ThreeVector TriVAssemblyBarInner6th(0.,60.8031*cm,-4.24504*cm);
    G4ThreeVector TriVAssemblyBarInner7th(0.,66.883*cm,-10.3782*cm);
    G4ThreeVector TriVAssemblyBarInner8th(0.,72.3471*cm,-17.0659*cm);
    G4ThreeVector TriVAssemblyBarInner9th(0.,77.1451*cm,-24.2466*cm);
    G4ThreeVector TriVAssemblyBarInner10th(0.,81.2327*cm,-31.854*cm);
    G4ThreeVector TriVAssemblyBarInner11th(0.,84.5723*cm,-39.8182*cm);


    ///place the tubes and bases of inner array  
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner1st, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner2nd, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner3rd, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner4th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner5th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner6th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner7th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner8th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner9th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner10th, rotD0, 0);
    assembly->MakeImprint(secondArmLogical, TriVAssemblyBarInner11th, rotD0, 0);

    G4RotationMatrix* rotBar1 = new G4RotationMatrix();
    rotBar1->rotateX(-15.*deg);
    G4RotationMatrix* rotBar2 = new G4RotationMatrix();
    rotBar2->rotateX(-20.5*deg);
    G4RotationMatrix* rotBar3 = new G4RotationMatrix();
    rotBar3->rotateX(-26.*deg);
    G4RotationMatrix* rotBar4 = new G4RotationMatrix();
    rotBar4->rotateX(-31.5*deg);
    G4RotationMatrix* rotBar5 = new G4RotationMatrix();
    rotBar5->rotateX(-37.*deg);
    G4RotationMatrix* rotBar6 = new G4RotationMatrix();
    rotBar6->rotateX(-42.5*deg);
    G4RotationMatrix* rotBar7 = new G4RotationMatrix();
    rotBar7->rotateX(-48.*deg);
    G4RotationMatrix* rotBar8 = new G4RotationMatrix();
    rotBar8->rotateX(-53.5*deg);
    G4RotationMatrix* rotBar9 = new G4RotationMatrix();
    rotBar9->rotateX(-59.*deg);
    G4RotationMatrix* rotBar10 = new G4RotationMatrix();
    rotBar10->rotateX(-64.5*deg);
    G4RotationMatrix* rotBar11 = new G4RotationMatrix();
    rotBar11->rotateX(-70.*deg);

    ///place BarSDs, inner array
    assemblyBar1SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner1st, rotBar1, 0);
    assemblyBar2SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner2nd, rotBar2, 0);
    assemblyBar3SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner3rd, rotBar3, 0);
    assemblyBar4SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner4th, rotBar4, 0);
    assemblyBar5SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner5th, rotBar5, 0);
    assemblyBar6SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner6th, rotBar6, 0);
    assemblyBar7SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner7th, rotBar7, 0);
    assemblyBar8SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner8th, rotBar8, 0);
    assemblyBar9SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner9th, rotBar9, 0);
    assemblyBar10SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner10th, rotBar10, 0);
    assemblyBar11SD->MakeImprint(secondArmLogical, TriVAssemblyBarInner11th, rotBar11, 0);

    /// 3 vectors of outer bar array 
    G4ThreeVector TriVAssemblyBarOuter1st(0.,29.3188*cm,22.3874*cm);
    G4ThreeVector TriVAssemblyBarOuter2nd(0.,38.0963*cm,19.1492*cm);
    G4ThreeVector TriVAssemblyBarOuter3rd(0.,46.523*cm,15.0847*cm);
    G4ThreeVector TriVAssemblyBarOuter4th(0.,54.5213*cm,10.2312*cm);
    G4ThreeVector TriVAssemblyBarOuter5th(0.,62.0176*cm,4.6334*cm);
    G4ThreeVector TriVAssemblyBarOuter6th(0.,68.9429*cm,-1.65709*cm);
    G4ThreeVector TriVAssemblyBarOuter7th(0.,75.2334*cm,-8.58237*cm);
    G4ThreeVector TriVAssemblyBarOuter8th(0.,80.8312*cm,-16.0787*cm);
    G4ThreeVector TriVAssemblyBarOuter9th(0.,85.6847*cm,-24.077*cm);
    G4ThreeVector TriVAssemblyBarOuter10th(0.,89.7492*cm,-32.5037*cm);
    G4ThreeVector TriVAssemblyBarOuter11th(0.,92.9874*cm,-41.2812*cm);

    ///place the tubes and bases of outer array  
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter1st, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter2nd, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter3rd, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter4th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter5th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter6th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter7th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter8th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter9th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter10th, rotD0, 0);
    assemblyOuterLayer->MakeImprint(secondArmLogical, TriVAssemblyBarOuter11th, rotD0, 0);


    G4RotationMatrix* rotOuterBar1 = new G4RotationMatrix();
    rotOuterBar1->rotateX(-17.5*deg);
    G4RotationMatrix* rotOuterBar2 = new G4RotationMatrix();
    rotOuterBar2->rotateX(-23.*deg);
    G4RotationMatrix* rotOuterBar3 = new G4RotationMatrix();
    rotOuterBar3->rotateX(-28.5*deg);
    G4RotationMatrix* rotOuterBar4 = new G4RotationMatrix();
    rotOuterBar4->rotateX(-34.*deg);
    G4RotationMatrix* rotOuterBar5 = new G4RotationMatrix();
    rotOuterBar5->rotateX(-39.5*deg);
    G4RotationMatrix* rotOuterBar6 = new G4RotationMatrix();
    rotOuterBar6->rotateX(-45.*deg);
    G4RotationMatrix* rotOuterBar7 = new G4RotationMatrix();
    rotOuterBar7->rotateX(-50.5*deg);
    G4RotationMatrix* rotOuterBar8 = new G4RotationMatrix();
    rotOuterBar8->rotateX(-56.*deg);
    G4RotationMatrix* rotOuterBar9 = new G4RotationMatrix();
    rotOuterBar9->rotateX(-61.5*deg);
    G4RotationMatrix* rotOuterBar10 = new G4RotationMatrix();
    rotOuterBar10->rotateX(-67.*deg);
    G4RotationMatrix* rotOuterBar11 = new G4RotationMatrix();
    rotOuterBar11->rotateX(-72.5*deg);

    ///place BarSDs, outer array
    assemblyBar12SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter1st, rotOuterBar1, 0);
    assemblyBar13SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter2nd, rotOuterBar2, 0);
    assemblyBar14SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter3rd, rotOuterBar3, 0);
    assemblyBar15SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter4th, rotOuterBar4, 0);
    assemblyBar16SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter5th, rotOuterBar5, 0);
    assemblyBar17SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter6th, rotOuterBar6, 0);
    assemblyBar18SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter7th, rotOuterBar7, 0);
    assemblyBar19SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter8th, rotOuterBar8, 0);
    assemblyBar20SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter9th, rotOuterBar9, 0);
    assemblyBar21SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter10th, rotOuterBar10, 0);
    assemblyBar22SD->MakeImprint(secondArmLogical, TriVAssemblyBarOuter11th, rotOuterBar11, 0);


    
    /// ~~~~~~~~~~~~ 2 supportive frames of scintillator bar array  ~~~~~~~~~~~~ 

    G4double supportiveFrame1X   =   32.*cm;
    ///G4double supportiveFrame1Y   =   3.0*cm;
    G4double supportiveFrame1Y   =   -4.0*cm;
    G4double supportiveFrame1Z   =   16.*cm;
    G4VSolid* supportiveFrameScintBarArraySolid
      = new G4Box("supportiveFrameScintBarArrayBox",1.*cm,23.0*cm,3.5*cm);
    supportiveFrameScintBarArrayLogical
      = new G4LogicalVolume(supportiveFrameScintBarArraySolid,Alumina,"supportiveFrameScintBarArrayLogical");
    new G4PVPlacement(0,G4ThreeVector(supportiveFrame1X,supportiveFrame1Y,supportiveFrame1Z),
                      supportiveFrameScintBarArrayLogical,"supportiveFrameScintBarArrayPhysical",secondArmLogical,
                      false,0.,checkOverlaps);
    
    

    G4double supportiveFrame2X   =   -32.*cm;
    G4double supportiveFrame2Y   =   -4.0*cm;
    G4double supportiveFrame2Z   =   16.*cm;
    new G4PVPlacement(0,G4ThreeVector(supportiveFrame2X,supportiveFrame2Y,supportiveFrame2Z),
                      supportiveFrameScintBarArrayLogical,"supportiveFrameScintBarArrayPhysical",secondArmLogical,
                      false,0.,checkOverlaps);
    





    /// ~~~~~~~~~~~~ The PMT on the positive X direction of bar2. ~~~~~~~~~~~~ 
    /// Tube of a PMT_pxb2, made of plastic.
    TubeBar2PosXLogical  = new G4LogicalVolume(pmt_tube, quartz, "TubeBar2PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(tubeVPosition,Bar2Y,Bar2Z),TubeBar2PosXLogical,
    ///                   "fTubeBar2PosXPhys", secondArmLogical, false, 0,checkOverlaps);

    /// Base and flange of a PMT_pxb2, made of glass.
    G4UnionSolid* pmt_sol_bar2_posX = new G4UnionSolid("pmt_sol_bar2_posX", pmt_base, pmt_flange,
                            G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,flangeShiftBase)));

    BaseBar2PosXLogical  = new G4LogicalVolume(pmt_sol_bar2_posX, base_mat, "BaseBar2PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(baseVPosition,Bar2Y,Bar2Z),BaseBar2PosXLogical,
    ///                   "fBaseBar2PosXPhys",  secondArmLogical, false, 0,checkOverlaps);

    /// Shield of a PMT_pxb2, made of mu-mental.
    ///fShieldBar2PosXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar2PosXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(shieldVPosition,Bar2Y,Bar2Z),fShieldBar2PosXLogical,
    ///                   "fShieldBar2PosXPhys", secondArmLogical, false, 0,checkOverlaps);


    /// ~~~~~~~~~~~~ The PMT on the positive X direction of bar2. ~~~~~~~~~~~~ 
    /// Tube of a PMT_nxb2, made of plastic.
    TubeBar2NegXLogical  = new G4LogicalVolume(pmt_tube, quartz, "TubeBar2NegXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(-1.*tubeVPosition,Bar2Y,Bar2Z),TubeBar2NegXLogical,
    ///                   "fTubeBar2NegXPhys", secondArmLogical, false, 0,checkOverlaps);

    /// Base and flange of a PMT_pxb2, made of glass.
    G4UnionSolid* pmt_sol_bar2_negX = new G4UnionSolid("pmt_sol_bar2_negX", pmt_base, pmt_flange,
                            G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,-1.*flangeShiftBase)));

    BaseBar2NegXLogical  = new G4LogicalVolume(pmt_sol_bar2_negX, base_mat, "BaseBar2NegXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(-1.*baseVPosition,Bar2Y,Bar2Z),BaseBar2NegXLogical,
    ///                   "fBaseBar2NegXPhys",  secondArmLogical, false, 0,checkOverlaps);

    /// Shield of a PMT_pxb2, made of mu-mental.
    ///fShieldBar2NegXLogical  = new G4LogicalVolume(pmt_shield, MuMetal, "fShieldBar2NegXLogical");
    ///new G4PVPlacement(rotD90,G4ThreeVector(-1.*shieldVPosition,Bar2Y,Bar2Z),fShieldBar2NegXLogical,
    ///                   "fShieldBar2NegXPhys", secondArmLogical, false, 0,checkOverlaps);



    ///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Rectangle stainless frame ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// Long side in the direction of negative X axis
    G4double side0X       = 40.*cm;
    G4double side0Y       = -30.*cm;
    G4double side0Z       = 0.*cm;
    G4VSolid* StainlessSteelLongSideSolid 
      = new G4Box("stainlesssteellongsideBox",1.5*cm,1.5*cm,80.0*cm);  
    StainlessSteelSide0Logical
      = new G4LogicalVolume(StainlessSteelLongSideSolid,stainlessSteel,"StainlessSteelSide0Logical");
        new G4PVPlacement(0,G4ThreeVector(side0X,side0Y,side0Z),StainlessSteelSide0Logical,
                          "StainlessSteelLongSidePhysical",secondArmLogical,
                          false,0,checkOverlaps);


    /// short side in the direction of positive Z axis
    G4VSolid* StainlessSteelShortSideSolid 
      = new G4Box("stainlesssteelshortsideBox",38.5*cm,1.5*cm,1.5*cm);  
    G4double side1X       = 0.*cm;
    G4double side1Y       = -30.*cm;
    G4double side1Z       = 15.0*cm;
    StainlessSteelSide1Logical
      = new G4LogicalVolume(StainlessSteelShortSideSolid,stainlessSteel,"StainlessSteelSide1Logical");
        new G4PVPlacement(0,G4ThreeVector(side1X,side1Y,side1Z),StainlessSteelSide1Logical,
                          "StainlessSteelSide1Physical",secondArmLogical,
                          false,0,checkOverlaps);


    /// Long side in the direction of positive X axis
    G4double side2X       = -40.*cm;
    G4double side2Y       = -30.*cm;
    G4double side2Z       = 0.*cm;
    StainlessSteelSide2Logical
      = new G4LogicalVolume(StainlessSteelLongSideSolid,stainlessSteel,"StainlessSteelSide2Logical");
        new G4PVPlacement(0,G4ThreeVector(side2X,side2Y,side2Z),StainlessSteelSide2Logical,
                          "StainlessSteelSide2Physical",secondArmLogical,
                          false,0,checkOverlaps);


    /// short side in the direction of negative Z axis
    G4double side3X       = 0.*cm;
    G4double side3Y       = -30.*cm;
    G4double side3Z       = -78.*cm;
    StainlessSteelSide3Logical
      = new G4LogicalVolume(StainlessSteelShortSideSolid,stainlessSteel,"StainlessSteelSide3Logical");
        new G4PVPlacement(0,G4ThreeVector(side3X,side3Y,side3Z),StainlessSteelSide3Logical,
                          "StainlessSteelSide3Physical",secondArmLogical,
                          false,0,checkOverlaps);


    //
    // visualization attributes ------------------------------------------------
    // Step 6: uncomment visualization attributes of the newly created volumes
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    visAttributes->SetVisibility(false);
    worldLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.3));   
    fThermoelectricColimatorLogical->SetVisAttributes(visAttributes);
    fExtenderSddLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.6,0.3));  
    fSubstrateLayerLogical->SetVisAttributes(visAttributes);
    fBoxSddLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    fSddWorldLogical->SetVisAttributes(visAttributes);
    visAttributes->SetVisibility(false);
    fCoverSddLogical->SetVisAttributes(visAttributes);
    firstArmLogical->SetVisAttributes(visAttributes);
    ///secondArmLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.8888,0.0,0.0));
    fMultilayerCollimatorLogical->SetVisAttributes(visAttributes);
    fSiliconDetectorLayerLogical->SetVisAttributes(visAttributes);
    ///fHodoscope1Logical->SetVisAttributes(visAttributes);
    BeWindowLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0,0.5,0.9));
    floorLogical->SetVisAttributes(visAttributes);
    roofLogical->SetVisAttributes(visAttributes);
    wallPlusXLogical->SetVisAttributes(visAttributes);
    wallMinusXLogical->SetVisAttributes(visAttributes);
    wallPlusZLogical->SetVisAttributes(visAttributes);
    wallMinusZLogical->SetVisAttributes(visAttributes);
    ///fHodoscope2Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0,0.8888,0.0));
    secondArmLogical->SetVisAttributes(visAttributes);
    EndcapLogical->SetVisAttributes(visAttributes);
    BaseBar1PosXLogical->SetVisAttributes(visAttributes);
    BaseBar1NegXLogical->SetVisAttributes(visAttributes);
    BaseBar2PosXLogical->SetVisAttributes(visAttributes);
    BaseBar2NegXLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.5888,0.8888,0.5));
    ///fHodoscope3Logical->SetVisAttributes(visAttributes);
    fCollimatorLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.6,0.3,0.9));
    supportiveFrameScintBarArrayLogical->SetVisAttributes(visAttributes);
    SupportStripNegXLogical->SetVisAttributes(visAttributes);
    SupportStripPosXLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));
    StainlessSteelSide0Logical->SetVisAttributes(visAttributes);
    StainlessSteelSide1Logical->SetVisAttributes(visAttributes);
    StainlessSteelSide2Logical->SetVisAttributes(visAttributes);
    StainlessSteelSide3Logical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.3, 0.0, 0.9));
    TubeBar1PosXLogical->SetVisAttributes(visAttributes);
    TubeBar1NegXLogical->SetVisAttributes(visAttributes);
    TubeBar2PosXLogical->SetVisAttributes(visAttributes);
    TubeBar2NegXLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.6, 0.3, 0.2));
    ///fCoverSddLogical->SetVisAttributes(visAttributes);
    fHeaderSddLogical->SetVisAttributes(visAttributes);
    fShieldBar1PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar1NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar2PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar2NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar3PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar3NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar4PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar4NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar5PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar5NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar6PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar6NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar7PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar7NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar8PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar8NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar9PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar9NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar10PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar10NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar11PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar11NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar12PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar12NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar13PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar13NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar14PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar14NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar15PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar15NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar16PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar16NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar17PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar17NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar18PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar18NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar19PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar19NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar20PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar20NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar21PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar21NegXLogical->SetVisAttributes(visAttributes);
    fShieldBar22PosXLogical->SetVisAttributes(visAttributes);
    fShieldBar22NegXLogical->SetVisAttributes(visAttributes);
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
    
    G4VSensitiveDetector* sdd 
      = new SddSD(SDname="/sdd");
    SDman->AddNewDetector(sdd);
    ///fSddWorldLogical->SetSensitiveDetector(sdd);
    fSiliconDetectorLayerLogical->SetSensitiveDetector(sdd);

    ///Bar1
    G4VSensitiveDetector* hodoscope1 
      = new HodoscopeSD(SDname="/hodoscope1");
    SDman->AddNewDetector(hodoscope1);
    fHodoscope1Logical->SetSensitiveDetector(hodoscope1);

    ///Bar2
    G4VSensitiveDetector* hodoscope2 
      = new HodoscopeSD(SDname="/hodoscope2");
    SDman->AddNewDetector(hodoscope2);
    fHodoscope2Logical->SetSensitiveDetector(hodoscope2);

    ///Bar3
    G4VSensitiveDetector* hodoscope3 
      = new HodoscopeSD(SDname="/hodoscope3");
    SDman->AddNewDetector(hodoscope3);
    fHodoscope3Logical->SetSensitiveDetector(hodoscope3);
    ///place_sdman
    ///Bar4
    G4VSensitiveDetector* hodoscope4
      = new HodoscopeSD(SDname="/hodoscope4");
    SDman->AddNewDetector(hodoscope4);
    fHodoscope4Logical->SetSensitiveDetector(hodoscope4);

    ///Bar5
    G4VSensitiveDetector* hodoscope5
      = new HodoscopeSD(SDname="/hodoscope5");
    SDman->AddNewDetector(hodoscope5);
    fHodoscope5Logical->SetSensitiveDetector(hodoscope5);

    ///Bar6
    G4VSensitiveDetector* hodoscope6
      = new HodoscopeSD(SDname="/hodoscope6");
    SDman->AddNewDetector(hodoscope6);
    fHodoscope6Logical->SetSensitiveDetector(hodoscope6);

    ///Bar7
    G4VSensitiveDetector* hodoscope7
      = new HodoscopeSD(SDname="/hodoscope7");
    SDman->AddNewDetector(hodoscope7);
    fHodoscope7Logical->SetSensitiveDetector(hodoscope7);

    ///Bar8
    G4VSensitiveDetector* hodoscope8
      = new HodoscopeSD(SDname="/hodoscope8");
    SDman->AddNewDetector(hodoscope8);
    fHodoscope8Logical->SetSensitiveDetector(hodoscope8);

    ///Bar9
    G4VSensitiveDetector* hodoscope9
      = new HodoscopeSD(SDname="/hodoscope9");
    SDman->AddNewDetector(hodoscope9);
    fHodoscope9Logical->SetSensitiveDetector(hodoscope9);

    ///Bar10
    G4VSensitiveDetector* hodoscope10
      = new HodoscopeSD(SDname="/hodoscope10");
    SDman->AddNewDetector(hodoscope10);
    fHodoscope10Logical->SetSensitiveDetector(hodoscope10);

    ///Bar11
    G4VSensitiveDetector* hodoscope11
      = new HodoscopeSD(SDname="/hodoscope11");
    SDman->AddNewDetector(hodoscope11);
    fHodoscope11Logical->SetSensitiveDetector(hodoscope11);

    ///Bar12
    G4VSensitiveDetector* hodoscope12
      = new HodoscopeSD(SDname="/hodoscope12");
    SDman->AddNewDetector(hodoscope12);
    fHodoscope12Logical->SetSensitiveDetector(hodoscope12);

    ///Bar13
    G4VSensitiveDetector* hodoscope13
      = new HodoscopeSD(SDname="/hodoscope13");
    SDman->AddNewDetector(hodoscope13);
    fHodoscope13Logical->SetSensitiveDetector(hodoscope13);

    ///Bar14
    G4VSensitiveDetector* hodoscope14
      = new HodoscopeSD(SDname="/hodoscope14");
    SDman->AddNewDetector(hodoscope14);
    fHodoscope14Logical->SetSensitiveDetector(hodoscope14);

    ///Bar15
    G4VSensitiveDetector* hodoscope15
      = new HodoscopeSD(SDname="/hodoscope15");
    SDman->AddNewDetector(hodoscope15);
    fHodoscope15Logical->SetSensitiveDetector(hodoscope15);

    ///Bar16
    G4VSensitiveDetector* hodoscope16
      = new HodoscopeSD(SDname="/hodoscope16");
    SDman->AddNewDetector(hodoscope16);
    fHodoscope16Logical->SetSensitiveDetector(hodoscope16);

    ///Bar17
    G4VSensitiveDetector* hodoscope17
      = new HodoscopeSD(SDname="/hodoscope17");
    SDman->AddNewDetector(hodoscope17);
    fHodoscope17Logical->SetSensitiveDetector(hodoscope17);

    ///Bar18
    G4VSensitiveDetector* hodoscope18
      = new HodoscopeSD(SDname="/hodoscope18");
    SDman->AddNewDetector(hodoscope18);
    fHodoscope18Logical->SetSensitiveDetector(hodoscope18);

    ///Bar19
    G4VSensitiveDetector* hodoscope19
      = new HodoscopeSD(SDname="/hodoscope19");
    SDman->AddNewDetector(hodoscope19);
    fHodoscope19Logical->SetSensitiveDetector(hodoscope19);

    ///Bar20
    G4VSensitiveDetector* hodoscope20
      = new HodoscopeSD(SDname="/hodoscope20");
    SDman->AddNewDetector(hodoscope20);
    fHodoscope20Logical->SetSensitiveDetector(hodoscope20);

    ///Bar21
    G4VSensitiveDetector* hodoscope21
      = new HodoscopeSD(SDname="/hodoscope21");
    SDman->AddNewDetector(hodoscope21);
    fHodoscope21Logical->SetSensitiveDetector(hodoscope21);

    ///Bar22
    G4VSensitiveDetector* hodoscope22
      = new HodoscopeSD(SDname="/hodoscope22");
    SDman->AddNewDetector(hodoscope22);
    fHodoscope22Logical->SetSensitiveDetector(hodoscope22);

    
    G4VSensitiveDetector* collimator 
      = new CollimatorSD(SDname="/collimator");///"CollimatorSD" typoed as "HodoscopeSD", wasted around one day.
    SDman->AddNewDetector(collimator);
    fCollimatorLogical->SetSensitiveDetector(collimator);

    G4VSensitiveDetector* pmtshieldb1px 
      = new PmtshieldSD(SDname="/pmtshieldb1px");
    SDman->AddNewDetector(pmtshieldb1px);
    fShieldBar1PosXLogical->SetSensitiveDetector(pmtshieldb1px);///This line actives an SD.

    G4VSensitiveDetector* pmtshieldb1nx 
      = new PmtshieldSD(SDname="/pmtshieldb1nx");
    SDman->AddNewDetector(pmtshieldb1nx);
    fShieldBar1NegXLogical->SetSensitiveDetector(pmtshieldb1nx);///This line actives an SD.

    G4VSensitiveDetector* pmtshieldb2px 
      = new PmtshieldSD(SDname="/pmtshieldb2px");
    SDman->AddNewDetector(pmtshieldb2px);
    fShieldBar2PosXLogical->SetSensitiveDetector(pmtshieldb2px);///This line actives an SD.

    G4VSensitiveDetector* pmtshieldb2nx 
      = new PmtshieldSD(SDname="/pmtshieldb2nx");
    SDman->AddNewDetector(pmtshieldb2nx);
    fShieldBar2NegXLogical->SetSensitiveDetector(pmtshieldb2nx);///This line actives an SD.

    G4VSensitiveDetector* pmtshieldb3px 
      = new PmtshieldSD(SDname="/pmtshieldb3px");
    SDman->AddNewDetector(pmtshieldb3px);
    fShieldBar3PosXLogical->SetSensitiveDetector(pmtshieldb3px);///This line actives an SD.

    G4VSensitiveDetector* pmtshieldb3nx 
      = new PmtshieldSD(SDname="/pmtshieldb3nx");
    SDman->AddNewDetector(pmtshieldb3nx);
    fShieldBar3NegXLogical->SetSensitiveDetector(pmtshieldb3nx);///This line actives an SD.

    ///place_define_shield_sd
    G4VSensitiveDetector* pmtshieldb4px
      = new PmtshieldSD(SDname="/pmtshieldb4px");
    SDman->AddNewDetector(pmtshieldb4px);
    fShieldBar4PosXLogical->SetSensitiveDetector(pmtshieldb4px);

    G4VSensitiveDetector* pmtshieldb4nx
      = new PmtshieldSD(SDname="/pmtshieldb4nx");
    SDman->AddNewDetector(pmtshieldb4nx);
    fShieldBar4NegXLogical->SetSensitiveDetector(pmtshieldb4nx);


    G4VSensitiveDetector* pmtshieldb5px
      = new PmtshieldSD(SDname="/pmtshieldb5px");
    SDman->AddNewDetector(pmtshieldb5px);
    fShieldBar5PosXLogical->SetSensitiveDetector(pmtshieldb5px);

    G4VSensitiveDetector* pmtshieldb5nx
      = new PmtshieldSD(SDname="/pmtshieldb5nx");
    SDman->AddNewDetector(pmtshieldb5nx);
    fShieldBar5NegXLogical->SetSensitiveDetector(pmtshieldb5nx);


    G4VSensitiveDetector* pmtshieldb6px
      = new PmtshieldSD(SDname="/pmtshieldb6px");
    SDman->AddNewDetector(pmtshieldb6px);
    fShieldBar6PosXLogical->SetSensitiveDetector(pmtshieldb6px);

    G4VSensitiveDetector* pmtshieldb6nx
      = new PmtshieldSD(SDname="/pmtshieldb6nx");
    SDman->AddNewDetector(pmtshieldb6nx);
    fShieldBar6NegXLogical->SetSensitiveDetector(pmtshieldb6nx);


    G4VSensitiveDetector* pmtshieldb7px
      = new PmtshieldSD(SDname="/pmtshieldb7px");
    SDman->AddNewDetector(pmtshieldb7px);
    fShieldBar7PosXLogical->SetSensitiveDetector(pmtshieldb7px);

    G4VSensitiveDetector* pmtshieldb7nx
      = new PmtshieldSD(SDname="/pmtshieldb7nx");
    SDman->AddNewDetector(pmtshieldb7nx);
    fShieldBar7NegXLogical->SetSensitiveDetector(pmtshieldb7nx);


    G4VSensitiveDetector* pmtshieldb8px
      = new PmtshieldSD(SDname="/pmtshieldb8px");
    SDman->AddNewDetector(pmtshieldb8px);
    fShieldBar8PosXLogical->SetSensitiveDetector(pmtshieldb8px);

    G4VSensitiveDetector* pmtshieldb8nx
      = new PmtshieldSD(SDname="/pmtshieldb8nx");
    SDman->AddNewDetector(pmtshieldb8nx);
    fShieldBar8NegXLogical->SetSensitiveDetector(pmtshieldb8nx);


    G4VSensitiveDetector* pmtshieldb9px
      = new PmtshieldSD(SDname="/pmtshieldb9px");
    SDman->AddNewDetector(pmtshieldb9px);
    fShieldBar9PosXLogical->SetSensitiveDetector(pmtshieldb9px);

    G4VSensitiveDetector* pmtshieldb9nx
      = new PmtshieldSD(SDname="/pmtshieldb9nx");
    SDman->AddNewDetector(pmtshieldb9nx);
    fShieldBar9NegXLogical->SetSensitiveDetector(pmtshieldb9nx);


    G4VSensitiveDetector* pmtshieldb10px
      = new PmtshieldSD(SDname="/pmtshieldb10px");
    SDman->AddNewDetector(pmtshieldb10px);
    fShieldBar10PosXLogical->SetSensitiveDetector(pmtshieldb10px);

    G4VSensitiveDetector* pmtshieldb10nx
      = new PmtshieldSD(SDname="/pmtshieldb10nx");
    SDman->AddNewDetector(pmtshieldb10nx);
    fShieldBar10NegXLogical->SetSensitiveDetector(pmtshieldb10nx);


    G4VSensitiveDetector* pmtshieldb11px
      = new PmtshieldSD(SDname="/pmtshieldb11px");
    SDman->AddNewDetector(pmtshieldb11px);
    fShieldBar11PosXLogical->SetSensitiveDetector(pmtshieldb11px);

    G4VSensitiveDetector* pmtshieldb11nx
      = new PmtshieldSD(SDname="/pmtshieldb11nx");
    SDman->AddNewDetector(pmtshieldb11nx);
    fShieldBar11NegXLogical->SetSensitiveDetector(pmtshieldb11nx);


    G4VSensitiveDetector* pmtshieldb12px
      = new PmtshieldSD(SDname="/pmtshieldb12px");
    SDman->AddNewDetector(pmtshieldb12px);
    fShieldBar12PosXLogical->SetSensitiveDetector(pmtshieldb12px);

    G4VSensitiveDetector* pmtshieldb12nx
      = new PmtshieldSD(SDname="/pmtshieldb12nx");
    SDman->AddNewDetector(pmtshieldb12nx);
    fShieldBar12NegXLogical->SetSensitiveDetector(pmtshieldb12nx);


    G4VSensitiveDetector* pmtshieldb13px
      = new PmtshieldSD(SDname="/pmtshieldb13px");
    SDman->AddNewDetector(pmtshieldb13px);
    fShieldBar13PosXLogical->SetSensitiveDetector(pmtshieldb13px);

    G4VSensitiveDetector* pmtshieldb13nx
      = new PmtshieldSD(SDname="/pmtshieldb13nx");
    SDman->AddNewDetector(pmtshieldb13nx);
    fShieldBar13NegXLogical->SetSensitiveDetector(pmtshieldb13nx);


    G4VSensitiveDetector* pmtshieldb14px
      = new PmtshieldSD(SDname="/pmtshieldb14px");
    SDman->AddNewDetector(pmtshieldb14px);
    fShieldBar14PosXLogical->SetSensitiveDetector(pmtshieldb14px);

    G4VSensitiveDetector* pmtshieldb14nx
      = new PmtshieldSD(SDname="/pmtshieldb14nx");
    SDman->AddNewDetector(pmtshieldb14nx);
    fShieldBar14NegXLogical->SetSensitiveDetector(pmtshieldb14nx);


    G4VSensitiveDetector* pmtshieldb15px
      = new PmtshieldSD(SDname="/pmtshieldb15px");
    SDman->AddNewDetector(pmtshieldb15px);
    fShieldBar15PosXLogical->SetSensitiveDetector(pmtshieldb15px);

    G4VSensitiveDetector* pmtshieldb15nx
      = new PmtshieldSD(SDname="/pmtshieldb15nx");
    SDman->AddNewDetector(pmtshieldb15nx);
    fShieldBar15NegXLogical->SetSensitiveDetector(pmtshieldb15nx);


    G4VSensitiveDetector* pmtshieldb16px
      = new PmtshieldSD(SDname="/pmtshieldb16px");
    SDman->AddNewDetector(pmtshieldb16px);
    fShieldBar16PosXLogical->SetSensitiveDetector(pmtshieldb16px);

    G4VSensitiveDetector* pmtshieldb16nx
      = new PmtshieldSD(SDname="/pmtshieldb16nx");
    SDman->AddNewDetector(pmtshieldb16nx);
    fShieldBar16NegXLogical->SetSensitiveDetector(pmtshieldb16nx);


    G4VSensitiveDetector* pmtshieldb17px
      = new PmtshieldSD(SDname="/pmtshieldb17px");
    SDman->AddNewDetector(pmtshieldb17px);
    fShieldBar17PosXLogical->SetSensitiveDetector(pmtshieldb17px);

    G4VSensitiveDetector* pmtshieldb17nx
      = new PmtshieldSD(SDname="/pmtshieldb17nx");
    SDman->AddNewDetector(pmtshieldb17nx);
    fShieldBar17NegXLogical->SetSensitiveDetector(pmtshieldb17nx);


    G4VSensitiveDetector* pmtshieldb18px
      = new PmtshieldSD(SDname="/pmtshieldb18px");
    SDman->AddNewDetector(pmtshieldb18px);
    fShieldBar18PosXLogical->SetSensitiveDetector(pmtshieldb18px);

    G4VSensitiveDetector* pmtshieldb18nx
      = new PmtshieldSD(SDname="/pmtshieldb18nx");
    SDman->AddNewDetector(pmtshieldb18nx);
    fShieldBar18NegXLogical->SetSensitiveDetector(pmtshieldb18nx);


    G4VSensitiveDetector* pmtshieldb19px
      = new PmtshieldSD(SDname="/pmtshieldb19px");
    SDman->AddNewDetector(pmtshieldb19px);
    fShieldBar19PosXLogical->SetSensitiveDetector(pmtshieldb19px);

    G4VSensitiveDetector* pmtshieldb19nx
      = new PmtshieldSD(SDname="/pmtshieldb19nx");
    SDman->AddNewDetector(pmtshieldb19nx);
    fShieldBar19NegXLogical->SetSensitiveDetector(pmtshieldb19nx);


    G4VSensitiveDetector* pmtshieldb20px
      = new PmtshieldSD(SDname="/pmtshieldb20px");
    SDman->AddNewDetector(pmtshieldb20px);
    fShieldBar20PosXLogical->SetSensitiveDetector(pmtshieldb20px);

    G4VSensitiveDetector* pmtshieldb20nx
      = new PmtshieldSD(SDname="/pmtshieldb20nx");
    SDman->AddNewDetector(pmtshieldb20nx);
    fShieldBar20NegXLogical->SetSensitiveDetector(pmtshieldb20nx);


    G4VSensitiveDetector* pmtshieldb21px
      = new PmtshieldSD(SDname="/pmtshieldb21px");
    SDman->AddNewDetector(pmtshieldb21px);
    fShieldBar21PosXLogical->SetSensitiveDetector(pmtshieldb21px);

    G4VSensitiveDetector* pmtshieldb21nx
      = new PmtshieldSD(SDname="/pmtshieldb21nx");
    SDman->AddNewDetector(pmtshieldb21nx);
    fShieldBar21NegXLogical->SetSensitiveDetector(pmtshieldb21nx);


    G4VSensitiveDetector* pmtshieldb22px
      = new PmtshieldSD(SDname="/pmtshieldb22px");
    SDman->AddNewDetector(pmtshieldb22px);
    fShieldBar22PosXLogical->SetSensitiveDetector(pmtshieldb22px);

    G4VSensitiveDetector* pmtshieldb22nx
      = new PmtshieldSD(SDname="/pmtshieldb22nx");
    SDman->AddNewDetector(pmtshieldb22nx);
    fShieldBar22NegXLogical->SetSensitiveDetector(pmtshieldb22nx);



}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    // Air 
    nistManager->FindOrBuildMaterial("G4_AIR");
  
    // Argon gas
    nistManager->FindOrBuildMaterial("G4_Ar");

    // Scintillator
    // (PolyVinylToluene, C_9H_10)
    nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    
    // CsI
    nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    
    // Concrete
    nistManager->FindOrBuildMaterial("G4_CONCRETE");
    
    // Lead
    nistManager->FindOrBuildMaterial("G4_Pb");
    
    // polyethylene
    nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    
    /// Vacuum "Galactic"
    nistManager->FindOrBuildMaterial("G4_Galactic");

    /// "Glass_plate"
    nistManager->FindOrBuildMaterial("G4_GLASS_PLATE");
    
    /// "Stainless_steel"
    nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    
    /// "base_mat"
    nistManager->FindOrBuildMaterial("G4_POLYCARBONATE");
    
    /// Nickel
    nistManager->FindOrBuildMaterial("G4_Ni");

    /// Silicon
    nistManager->FindOrBuildMaterial("G4_Si");

    /// Tungsten
    nistManager->FindOrBuildMaterial("G4_W");

    /// Beryllium
    nistManager->FindOrBuildMaterial("G4_Be");

   /// making material
    G4String name, symbol;
    G4double a,z,density,fractionmass;
    G4int ncomponents;
    
    /// quartz
    G4Element* O  = new G4Element(name="Oxygen" , symbol="O" , z= 8., a=16.00*g/mole);
    G4Element* Si = new G4Element(name="Silicon", symbol="Si" , z= 14., a=28.09*g/mole);
    G4Material* quartz = new G4Material(name="quartz", density=2.200*g/cm3, ncomponents=2);
    quartz->AddElement(Si, 1);
    quartz->AddElement(O , 2);
    
    /// Tec, thermoelectric cooler
    G4Element* Bi  = new G4Element(name="Bismuth" , symbol="Bi" , z= 83., a=208.98*g/mole);
    G4Element* Te = new G4Element(name="Tellurium", symbol="Te" , z= 52., a=127.60*g/mole);
    G4Material* Tec = new G4Material(name="Tec", density=7.642*g/cm3, ncomponents=2);
    Tec->AddElement(Bi, 2);
    Tec->AddElement(Te , 3);

    /// kovar, Fe,54%; Ni,29%; Co,17%.
    G4Element* Fe = new G4Element(name="Iron", symbol="Fe" , z= 26., a=55.85*g/mole);
    G4Element* Ni = new G4Element(name="Nickel" , symbol="Ni" , z= 28., a=58.69*g/mole);
    G4Element* Co = new G4Element(name="Cobalt" , symbol="Co" , z= 27., a=58.93*g/mole);
    G4Material* Kovar = new G4Material(name="Kovar", density=8.0*g/cm3, ncomponents=3);
    Kovar->AddElement(Fe, fractionmass = 54*perCent);
    Kovar->AddElement(Bi, fractionmass = 29*perCent);
    Kovar->AddElement(Co, fractionmass = 17*perCent);

    /// Alumina, substrate of SDD
    G4Element* Al  = new G4Element(name="Aluminium" , symbol="Al" , z= 13., a=26.98*g/mole);
    G4Material* Alumina = new G4Material(name="Alumina", density=3.95*g/cm3, ncomponents=2);
    Alumina->AddElement(Al, 2);
    Alumina->AddElement(O,  3);

    /// MuMetal, Ni,77%; Fe,16%; Cu,5%, Cr,2% .
    G4Element* Cu = new G4Element(name="Copper" , symbol="Cu" , z= 29., a=63.55*g/mole);
    G4Element* Cr = new G4Element(name="Chromium" , symbol="Cr" , z= 24., a=52.00*g/mole);
    G4Material* MuMetal = new G4Material(name="MuMetal", density=8.7*g/cm3, ncomponents=4);
    MuMetal->AddElement(Ni, fractionmass = 77*perCent);
    MuMetal->AddElement(Fe, fractionmass = 16*perCent);
    MuMetal->AddElement(Cu, fractionmass = 5*perCent);
    MuMetal->AddElement(Cr, fractionmass = 2*perCent);


    /// MAl, Material of Aluminium
  /*  G4Material* MAl  = new G4Material(name="MAl" , z= 13., a=26.98*g/mole,density=3.95*g/cm3);

    /// MCr, Material of Chromium
    G4Material* MCr  = new G4Material(name="MCr" , z= 24., a=52.00*g/mole,density=7.19*g/cm3);

    /// MTi, Material of Titanium
    G4Material* MTi  = new G4Material(name="MTi" , z= 22., a=47.87*g/mole, density=4.51*g/cm3);
    */

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
//
