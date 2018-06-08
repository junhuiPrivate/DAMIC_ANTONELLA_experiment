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
// $Id: EventAction.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4GeneralParticleSource.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
private:
    G4int fSDDHCID;

    G4int fBAR1HCID;
    G4int fBAR2HCID;
    G4int fBAR3HCID;
    G4int fBAR4HCID;
    G4int fBAR5HCID;
    G4int fBAR6HCID;
    G4int fBAR7HCID;
    G4int fBAR8HCID;
    G4int fBAR9HCID;
    G4int fBAR10HCID;
    G4int fBAR11HCID;
    G4int fBAR12HCID;
    G4int fBAR13HCID;
    G4int fBAR14HCID;
    G4int fBAR15HCID;
    G4int fBAR16HCID;
    G4int fBAR17HCID;
    G4int fBAR18HCID;
    G4int fBAR19HCID;
    G4int fBAR20HCID;
    G4int fBAR21HCID;
    G4int fBAR22HCID;

    G4int fCLMHCID;

    G4int fSHLDB1PXHCID;
    G4int fSHLDB1NXHCID;
    G4int fSHLDB2PXHCID;
    G4int fSHLDB2NXHCID;
    G4int fSHLDB3PXHCID;
    G4int fSHLDB3NXHCID;
    G4int fSHLDB4PXHCID;
    G4int fSHLDB4NXHCID;
    G4int fSHLDB5PXHCID;
    G4int fSHLDB5NXHCID;
    G4int fSHLDB6PXHCID;
    G4int fSHLDB6NXHCID;
    G4int fSHLDB7PXHCID;
    G4int fSHLDB7NXHCID;
    G4int fSHLDB8PXHCID;
    G4int fSHLDB8NXHCID;
    G4int fSHLDB9PXHCID;
    G4int fSHLDB9NXHCID;
    G4int fSHLDB10PXHCID;
    G4int fSHLDB10NXHCID;
    G4int fSHLDB11PXHCID;
    G4int fSHLDB11NXHCID;
    G4int fSHLDB12PXHCID;
    G4int fSHLDB12NXHCID;
    G4int fSHLDB13PXHCID;
    G4int fSHLDB13NXHCID;
    G4int fSHLDB14PXHCID;
    G4int fSHLDB14NXHCID;
    G4int fSHLDB15PXHCID;
    G4int fSHLDB15NXHCID;
    G4int fSHLDB16PXHCID;
    G4int fSHLDB16NXHCID;
    G4int fSHLDB17PXHCID;
    G4int fSHLDB17NXHCID;
    G4int fSHLDB18PXHCID;
    G4int fSHLDB18NXHCID;
    G4int fSHLDB19PXHCID;
    G4int fSHLDB19NXHCID;
    G4int fSHLDB20PXHCID;
    G4int fSHLDB20NXHCID;
    G4int fSHLDB21PXHCID;
    G4int fSHLDB21NXHCID;
    G4int fSHLDB22PXHCID;
    G4int fSHLDB22NXHCID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
