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
// $Id: DetectorConstruction.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"

#include <vector>

class MagneticField;

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

/// Detector construction

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetArmAngle(G4double val);
    G4double GetArmAngle() { return fArmAngle; }
    
    void ConstructMaterials();
    
private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;
    
    ///static G4ThreadLocal MagneticField* fMagneticField;
    ///static G4ThreadLocal G4FieldManager* fFieldMgr;
    
    G4LogicalVolume* fHodoscope1Logical;
    G4LogicalVolume* fHodoscope2Logical;
    G4LogicalVolume* fHodoscope3Logical;
    G4LogicalVolume* fHodoscope4Logical;
    G4LogicalVolume* fHodoscope5Logical;
    G4LogicalVolume* fHodoscope6Logical;
    G4LogicalVolume* fHodoscope7Logical;
    G4LogicalVolume* fHodoscope8Logical;
    G4LogicalVolume* fHodoscope9Logical;
    G4LogicalVolume* fHodoscope10Logical;
    G4LogicalVolume* fHodoscope11Logical;
    G4LogicalVolume* fHodoscope12Logical;
    G4LogicalVolume* fHodoscope13Logical;
    G4LogicalVolume* fHodoscope14Logical;
    G4LogicalVolume* fHodoscope15Logical;
    G4LogicalVolume* fHodoscope16Logical;
    G4LogicalVolume* fHodoscope17Logical;
    G4LogicalVolume* fHodoscope18Logical;
    G4LogicalVolume* fHodoscope19Logical;
    G4LogicalVolume* fHodoscope20Logical;
    G4LogicalVolume* fHodoscope21Logical;
    G4LogicalVolume* fHodoscope22Logical;
    
    G4LogicalVolume* fCollimatorLogical;
    
    G4LogicalVolume* BeWindowLogical;
    G4LogicalVolume* EndcapLogical;
    G4LogicalVolume* fCoverSddLogical;
    G4LogicalVolume* fMultilayerCollimatorLogical;
    G4LogicalVolume* fSiliconDetectorLayerLogical;
    G4LogicalVolume* fSubstrateLayerLogical;
    G4LogicalVolume* fThermoelectricColimatorLogical;
    G4LogicalVolume* fHeaderSddLogical;
    G4LogicalVolume* fSddWorldLogical;
    G4LogicalVolume* fExtenderSddLogical;
    G4LogicalVolume* fBoxSddLogical;

    
    G4LogicalVolume* TubeBar1PosXLogical;
    G4LogicalVolume* TubeBar1NegXLogical;
    G4LogicalVolume* TubeBar2PosXLogical;
    G4LogicalVolume* TubeBar2NegXLogical;

    G4LogicalVolume* fShieldBar1PosXLogical;
    G4LogicalVolume* fShieldBar1NegXLogical;
    G4LogicalVolume* fShieldBar2PosXLogical;
    G4LogicalVolume* fShieldBar2NegXLogical;
    G4LogicalVolume* fShieldBar3PosXLogical;
    G4LogicalVolume* fShieldBar3NegXLogical;
    G4LogicalVolume* fShieldBar4PosXLogical;
    G4LogicalVolume* fShieldBar4NegXLogical;
    G4LogicalVolume* fShieldBar5PosXLogical;
    G4LogicalVolume* fShieldBar5NegXLogical;
    G4LogicalVolume* fShieldBar6PosXLogical;
    G4LogicalVolume* fShieldBar6NegXLogical;
    G4LogicalVolume* fShieldBar7PosXLogical;
    G4LogicalVolume* fShieldBar7NegXLogical;
    G4LogicalVolume* fShieldBar8PosXLogical;
    G4LogicalVolume* fShieldBar8NegXLogical;
    G4LogicalVolume* fShieldBar9PosXLogical;
    G4LogicalVolume* fShieldBar9NegXLogical;
    G4LogicalVolume* fShieldBar10PosXLogical;
    G4LogicalVolume* fShieldBar10NegXLogical;
    G4LogicalVolume* fShieldBar11PosXLogical;
    G4LogicalVolume* fShieldBar11NegXLogical;
    G4LogicalVolume* fShieldBar12PosXLogical;
    G4LogicalVolume* fShieldBar12NegXLogical;
    G4LogicalVolume* fShieldBar13PosXLogical;
    G4LogicalVolume* fShieldBar13NegXLogical;
    G4LogicalVolume* fShieldBar14PosXLogical;
    G4LogicalVolume* fShieldBar14NegXLogical;
    G4LogicalVolume* fShieldBar15PosXLogical;
    G4LogicalVolume* fShieldBar15NegXLogical;
    G4LogicalVolume* fShieldBar16PosXLogical;
    G4LogicalVolume* fShieldBar16NegXLogical;
    G4LogicalVolume* fShieldBar17PosXLogical;
    G4LogicalVolume* fShieldBar17NegXLogical;
    G4LogicalVolume* fShieldBar18PosXLogical;
    G4LogicalVolume* fShieldBar18NegXLogical;
    G4LogicalVolume* fShieldBar19PosXLogical;
    G4LogicalVolume* fShieldBar19NegXLogical;
    G4LogicalVolume* fShieldBar20PosXLogical;
    G4LogicalVolume* fShieldBar20NegXLogical;
    G4LogicalVolume* fShieldBar21PosXLogical;
    G4LogicalVolume* fShieldBar21NegXLogical;
    G4LogicalVolume* fShieldBar22PosXLogical;
    G4LogicalVolume* fShieldBar22NegXLogical;
    
    G4LogicalVolume* BaseBar1PosXLogical;
    G4LogicalVolume* BaseBar1NegXLogical;
    G4LogicalVolume* BaseBar2PosXLogical;
    G4LogicalVolume* BaseBar2NegXLogical;
    
    G4LogicalVolume* StainlessSteelSide0Logical;
    G4LogicalVolume* StainlessSteelSide1Logical;
    G4LogicalVolume* StainlessSteelSide2Logical;
    G4LogicalVolume* StainlessSteelSide3Logical;
    
    G4LogicalVolume* supportiveFrameScintBarArrayLogical;
    G4LogicalVolume* SupportStripNegXLogical;
    G4LogicalVolume* SupportStripPosXLogical;
    
    std::vector<G4VisAttributes*> fVisAttributes;
    
    G4double fArmAngle;
    G4RotationMatrix* fArmRotation;
    G4VPhysicalVolume* fSecondArmPhys;
    ///G4VPhysicalVolume* fPMTPhys;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
