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
// $Id: EventAction.cc 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "HodoscopeHit.hh"
#include "CollimatorHit.hh"
#include "PmtshieldHit.hh"
#include "SddHit.hh"
#include "Analysis.hh"
///#include "PrimaryGeneratorAction.hh"
#include "exGPSPrimaryGeneratorAction.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(), 

  fSDDHCID(-1),///Sdd

  fBAR1HCID(-1),///Bar1
  fBAR2HCID(-1),///Bar2
  fBAR3HCID(-1),///Bar3
  fBAR4HCID(-1),///Bar4
  fBAR5HCID(-1),///Bar5
  fBAR6HCID(-1),///Bar6
  fBAR7HCID(-1),///Bar7
  fBAR8HCID(-1),///Bar8
  fBAR9HCID(-1),///Bar9
  fBAR10HCID(-1),///Bar10
  fBAR11HCID(-1),///Bar11
  fBAR12HCID(-1),///Bar12
  fBAR13HCID(-1),///Bar13
  fBAR14HCID(-1),///Bar14
  fBAR15HCID(-1),///Bar15
  fBAR16HCID(-1),///Bar16
  fBAR17HCID(-1),///Bar17
  fBAR18HCID(-1),///Bar18
  fBAR19HCID(-1),///Bar19
  fBAR20HCID(-1),///Bar20
  fBAR21HCID(-1),///Bar21
  fBAR22HCID(-1),///Bar22

  fCLMHCID(-1),///Collimator Hit Collection ID

  fSHLDB1PXHCID(-1),///pmt shield, Bar 1, Positive X direction, Hit Collection ID.
  fSHLDB1NXHCID(-1),///pmt shield, Bar 1, negative X direction, Hit Collection ID.
  fSHLDB2PXHCID(-1),///pmt shield, Bar 2, Positive X direction, Hit Collection ID.
  fSHLDB2NXHCID(-1),///pmt shield, Bar 2, negative X direction, Hit Collection ID.
  fSHLDB3PXHCID(-1),///pmt shield, Bar 3, Positive X direction, Hit Collection ID.
  fSHLDB3NXHCID(-1),///pmt shield, Bar 3, negative X direction, Hit Collection ID.
  fSHLDB4PXHCID(-1), ///Bar4
  fSHLDB4NXHCID(-1), ///Bar4
  fSHLDB5PXHCID(-1), ///Bar5
  fSHLDB5NXHCID(-1), ///Bar5
  fSHLDB6PXHCID(-1), ///Bar6
  fSHLDB6NXHCID(-1), ///Bar6
  fSHLDB7PXHCID(-1), ///Bar7
  fSHLDB7NXHCID(-1), ///Bar7
  fSHLDB8PXHCID(-1), ///Bar8
  fSHLDB8NXHCID(-1), ///Bar8
  fSHLDB9PXHCID(-1), ///Bar9
  fSHLDB9NXHCID(-1), ///Bar9
  fSHLDB10PXHCID(-1), ///Bar10
  fSHLDB10NXHCID(-1), ///Bar10
  fSHLDB11PXHCID(-1), ///Bar11
  fSHLDB11NXHCID(-1), ///Bar11
  fSHLDB12PXHCID(-1), ///Bar12
  fSHLDB12NXHCID(-1), ///Bar12
  fSHLDB13PXHCID(-1), ///Bar13
  fSHLDB13NXHCID(-1), ///Bar13
  fSHLDB14PXHCID(-1), ///Bar14
  fSHLDB14NXHCID(-1), ///Bar14
  fSHLDB15PXHCID(-1), ///Bar15
  fSHLDB15NXHCID(-1), ///Bar15
  fSHLDB16PXHCID(-1), ///Bar16
  fSHLDB16NXHCID(-1), ///Bar16
  fSHLDB17PXHCID(-1), ///Bar17
  fSHLDB17NXHCID(-1), ///Bar17
  fSHLDB18PXHCID(-1), ///Bar18
  fSHLDB18NXHCID(-1), ///Bar18
  fSHLDB19PXHCID(-1), ///Bar19
  fSHLDB19NXHCID(-1), ///Bar19
  fSHLDB20PXHCID(-1), ///Bar20
  fSHLDB20NXHCID(-1), ///Bar20
  fSHLDB21PXHCID(-1), ///Bar21
  fSHLDB21NXHCID(-1), ///Bar21
  fSHLDB22PXHCID(-1), ///Bar22
  fSHLDB22NXHCID(-1)  ///Bar22

{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    if (fSDDHCID==-1) {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      fSDDHCID = sdManager->GetCollectionID("sdd/sddColl");
      fBAR1HCID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      fBAR2HCID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
      fBAR3HCID = sdManager->GetCollectionID("hodoscope3/hodoscopeColl");
      fBAR4HCID = sdManager->GetCollectionID("hodoscope4/hodoscopeColl");
      fBAR5HCID = sdManager->GetCollectionID("hodoscope5/hodoscopeColl");
      fBAR6HCID = sdManager->GetCollectionID("hodoscope6/hodoscopeColl");
      fBAR7HCID = sdManager->GetCollectionID("hodoscope7/hodoscopeColl");
      fBAR8HCID = sdManager->GetCollectionID("hodoscope8/hodoscopeColl");
      fBAR9HCID = sdManager->GetCollectionID("hodoscope9/hodoscopeColl");
      fBAR10HCID = sdManager->GetCollectionID("hodoscope10/hodoscopeColl");
      fBAR11HCID = sdManager->GetCollectionID("hodoscope11/hodoscopeColl");
      fBAR12HCID = sdManager->GetCollectionID("hodoscope12/hodoscopeColl");
      fBAR13HCID = sdManager->GetCollectionID("hodoscope13/hodoscopeColl");
      fBAR14HCID = sdManager->GetCollectionID("hodoscope14/hodoscopeColl");
      fBAR15HCID = sdManager->GetCollectionID("hodoscope15/hodoscopeColl");
      fBAR16HCID = sdManager->GetCollectionID("hodoscope16/hodoscopeColl");
      fBAR17HCID = sdManager->GetCollectionID("hodoscope17/hodoscopeColl");
      fBAR18HCID = sdManager->GetCollectionID("hodoscope18/hodoscopeColl");
      fBAR19HCID = sdManager->GetCollectionID("hodoscope19/hodoscopeColl");
      fBAR20HCID = sdManager->GetCollectionID("hodoscope20/hodoscopeColl");
      fBAR21HCID = sdManager->GetCollectionID("hodoscope21/hodoscopeColl");
      fBAR22HCID = sdManager->GetCollectionID("hodoscope22/hodoscopeColl");

      fCLMHCID = sdManager->GetCollectionID("collimator/collimatorColl"); /// fCLMHCID = -1

      ///Shield in Bar1      
      fSHLDB1PXHCID = sdManager->GetCollectionID("pmtshieldb1px/pmtshieldColl"); 
      fSHLDB1NXHCID = sdManager->GetCollectionID("pmtshieldb1nx/pmtshieldColl"); 
      ///Shield in Bar2     
      fSHLDB2PXHCID = sdManager->GetCollectionID("pmtshieldb2px/pmtshieldColl"); 
      fSHLDB2NXHCID = sdManager->GetCollectionID("pmtshieldb2nx/pmtshieldColl"); 
      ///Shield in Bar3     
      fSHLDB3PXHCID = sdManager->GetCollectionID("pmtshieldb3px/pmtshieldColl"); 
      fSHLDB3NXHCID = sdManager->GetCollectionID("pmtshieldb3nx/pmtshieldColl"); 
      ///Shield in Bar4
      fSHLDB4PXHCID = sdManager->GetCollectionID("pmtshieldb4px/pmtshieldColl");
      fSHLDB4NXHCID = sdManager->GetCollectionID("pmtshieldb4nx/pmtshieldColl");
      ///Shield in Bar5
      fSHLDB5PXHCID = sdManager->GetCollectionID("pmtshieldb5px/pmtshieldColl");
      fSHLDB5NXHCID = sdManager->GetCollectionID("pmtshieldb5nx/pmtshieldColl");
      ///Shield in Bar6
      fSHLDB6PXHCID = sdManager->GetCollectionID("pmtshieldb6px/pmtshieldColl");
      fSHLDB6NXHCID = sdManager->GetCollectionID("pmtshieldb6nx/pmtshieldColl");
      ///Shield in Bar7
      fSHLDB7PXHCID = sdManager->GetCollectionID("pmtshieldb7px/pmtshieldColl");
      fSHLDB7NXHCID = sdManager->GetCollectionID("pmtshieldb7nx/pmtshieldColl");
      ///Shield in Bar8
      fSHLDB8PXHCID = sdManager->GetCollectionID("pmtshieldb8px/pmtshieldColl");
      fSHLDB8NXHCID = sdManager->GetCollectionID("pmtshieldb8nx/pmtshieldColl");
      ///Shield in Bar9
      fSHLDB9PXHCID = sdManager->GetCollectionID("pmtshieldb9px/pmtshieldColl");
      fSHLDB9NXHCID = sdManager->GetCollectionID("pmtshieldb9nx/pmtshieldColl");
      ///Shield in Bar10
      fSHLDB10PXHCID = sdManager->GetCollectionID("pmtshieldb10px/pmtshieldColl");
      fSHLDB10NXHCID = sdManager->GetCollectionID("pmtshieldb10nx/pmtshieldColl");
      ///Shield in Bar11
      fSHLDB11PXHCID = sdManager->GetCollectionID("pmtshieldb11px/pmtshieldColl");
      fSHLDB11NXHCID = sdManager->GetCollectionID("pmtshieldb11nx/pmtshieldColl");
      ///Shield in Bar12
      fSHLDB12PXHCID = sdManager->GetCollectionID("pmtshieldb12px/pmtshieldColl");
      fSHLDB12NXHCID = sdManager->GetCollectionID("pmtshieldb12nx/pmtshieldColl");
      ///Shield in Bar13
      fSHLDB13PXHCID = sdManager->GetCollectionID("pmtshieldb13px/pmtshieldColl");
      fSHLDB13NXHCID = sdManager->GetCollectionID("pmtshieldb13nx/pmtshieldColl");
      ///Shield in Bar14
      fSHLDB14PXHCID = sdManager->GetCollectionID("pmtshieldb14px/pmtshieldColl");
      fSHLDB14NXHCID = sdManager->GetCollectionID("pmtshieldb14nx/pmtshieldColl");
      ///Shield in Bar15
      fSHLDB15PXHCID = sdManager->GetCollectionID("pmtshieldb15px/pmtshieldColl");
      fSHLDB15NXHCID = sdManager->GetCollectionID("pmtshieldb15nx/pmtshieldColl");
      ///Shield in Bar16
      fSHLDB16PXHCID = sdManager->GetCollectionID("pmtshieldb16px/pmtshieldColl");
      fSHLDB16NXHCID = sdManager->GetCollectionID("pmtshieldb16nx/pmtshieldColl");
      ///Shield in Bar17
      fSHLDB17PXHCID = sdManager->GetCollectionID("pmtshieldb17px/pmtshieldColl");
      fSHLDB17NXHCID = sdManager->GetCollectionID("pmtshieldb17nx/pmtshieldColl");
      ///Shield in Bar18
      fSHLDB18PXHCID = sdManager->GetCollectionID("pmtshieldb18px/pmtshieldColl");
      fSHLDB18NXHCID = sdManager->GetCollectionID("pmtshieldb18nx/pmtshieldColl");
      ///Shield in Bar19
      fSHLDB19PXHCID = sdManager->GetCollectionID("pmtshieldb19px/pmtshieldColl");
      fSHLDB19NXHCID = sdManager->GetCollectionID("pmtshieldb19nx/pmtshieldColl");
      ///Shield in Bar20
      fSHLDB20PXHCID = sdManager->GetCollectionID("pmtshieldb20px/pmtshieldColl");
      fSHLDB20NXHCID = sdManager->GetCollectionID("pmtshieldb20nx/pmtshieldColl");
      ///Shield in Bar21
      fSHLDB21PXHCID = sdManager->GetCollectionID("pmtshieldb21px/pmtshieldColl");
      fSHLDB21NXHCID = sdManager->GetCollectionID("pmtshieldb21nx/pmtshieldColl");
      ///Shield in Bar22
      fSHLDB22PXHCID = sdManager->GetCollectionID("pmtshieldb22px/pmtshieldColl");
      fSHLDB22NXHCID = sdManager->GetCollectionID("pmtshieldb22nx/pmtshieldColl");

    }
}     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
    // Print on screen the hits of the hodoscope
    // Step 1: Get the hits collection of this event

    
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("EventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }   

    // Step 2: Using the memorised IDs get the collections
    // corresponding to the all sensitive detectors


    // Get hits collections 
    /// Bar1
    HodoscopeHitsCollection* hHC1 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR1HCID));
    /// Bar2
    HodoscopeHitsCollection* hHC2 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR2HCID));
    /// Bar3
    HodoscopeHitsCollection* hHC3 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR3HCID));
    ///Bar4
    HodoscopeHitsCollection* hHC4
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR4HCID));
    /// Bar5
    HodoscopeHitsCollection* hHC5
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR5HCID));
    /// Bar6
    HodoscopeHitsCollection* hHC6
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR6HCID));
    /// Bar7
    HodoscopeHitsCollection* hHC7
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR7HCID));
    /// Bar8
    HodoscopeHitsCollection* hHC8
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR8HCID));
    /// Bar9
    HodoscopeHitsCollection* hHC9
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR9HCID));
    /// Bar10
    HodoscopeHitsCollection* hHC10
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR10HCID));
    /// Bar11
    HodoscopeHitsCollection* hHC11
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR11HCID));
    /// Bar12
    HodoscopeHitsCollection* hHC12
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR12HCID));
    /// Bar13
    HodoscopeHitsCollection* hHC13
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR13HCID));
    /// Bar14
    HodoscopeHitsCollection* hHC14
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR14HCID));
    /// Bar15
    HodoscopeHitsCollection* hHC15
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR15HCID));
    /// Bar16
    HodoscopeHitsCollection* hHC16
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR16HCID));
    /// Bar17
    HodoscopeHitsCollection* hHC17
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR17HCID));
    /// Bar18
    HodoscopeHitsCollection* hHC18
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR18HCID));
    /// Bar19
    HodoscopeHitsCollection* hHC19
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR19HCID));
    /// Bar20
    HodoscopeHitsCollection* hHC20
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR20HCID));
    /// Bar21
    HodoscopeHitsCollection* hHC21
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR21HCID));
    /// Bar22
    HodoscopeHitsCollection* hHC22
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR22HCID));

      
    SddHitsCollection* sddHC 
      = static_cast<SddHitsCollection*>(hce->GetHC(fSDDHCID));
      
    CollimatorHitsCollection* hHCLM 
      = static_cast<CollimatorHitsCollection*>(hce->GetHC(fCLMHCID));

    ///Shield in Bar1
    PmtshieldHitsCollection* hSHLDB1PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB1PXHCID));
    PmtshieldHitsCollection* hSHLDB1NX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB1NXHCID));
    ///Shield in Bar2
    PmtshieldHitsCollection* hSHLDB2PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB2PXHCID));
    PmtshieldHitsCollection* hSHLDB2NX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB2NXHCID));
    ///Shield in Bar3
    PmtshieldHitsCollection* hSHLDB3PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB3PXHCID));
    PmtshieldHitsCollection* hSHLDB3NX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB3NXHCID));
    ///Shield in Bar4
    PmtshieldHitsCollection* hSHLDB4PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB4PXHCID));
    PmtshieldHitsCollection* hSHLDB4NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB4NXHCID));
    ///Shield in Bar5
    PmtshieldHitsCollection* hSHLDB5PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB5PXHCID));
    PmtshieldHitsCollection* hSHLDB5NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB5NXHCID));
    ///Shield in Bar6
    PmtshieldHitsCollection* hSHLDB6PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB6PXHCID));
    PmtshieldHitsCollection* hSHLDB6NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB6NXHCID));
    ///Shield in Bar7
    PmtshieldHitsCollection* hSHLDB7PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB7PXHCID));
    PmtshieldHitsCollection* hSHLDB7NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB7NXHCID));
    ///Shield in Bar8
    PmtshieldHitsCollection* hSHLDB8PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB8PXHCID));
    PmtshieldHitsCollection* hSHLDB8NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB8NXHCID));
    ///Shield in Bar9
    PmtshieldHitsCollection* hSHLDB9PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB9PXHCID));
    PmtshieldHitsCollection* hSHLDB9NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB9NXHCID));
    ///Shield in Bar10
    PmtshieldHitsCollection* hSHLDB10PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB10PXHCID));
    PmtshieldHitsCollection* hSHLDB10NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB10NXHCID));
    ///Shield in Bar11
    PmtshieldHitsCollection* hSHLDB11PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB11PXHCID));
    PmtshieldHitsCollection* hSHLDB11NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB11NXHCID));
    ///Shield in Bar12
    PmtshieldHitsCollection* hSHLDB12PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB12PXHCID));
    PmtshieldHitsCollection* hSHLDB12NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB12NXHCID));
    ///Shield in Bar13
    PmtshieldHitsCollection* hSHLDB13PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB13PXHCID));
    PmtshieldHitsCollection* hSHLDB13NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB13NXHCID));
    ///Shield in Bar14
    PmtshieldHitsCollection* hSHLDB14PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB14PXHCID));
    PmtshieldHitsCollection* hSHLDB14NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB14NXHCID));
    ///Shield in Bar15
    PmtshieldHitsCollection* hSHLDB15PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB15PXHCID));
    PmtshieldHitsCollection* hSHLDB15NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB15NXHCID));
    ///Shield in Bar16
    PmtshieldHitsCollection* hSHLDB16PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB16PXHCID));
    PmtshieldHitsCollection* hSHLDB16NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB16NXHCID));
    ///Shield in Bar17
    PmtshieldHitsCollection* hSHLDB17PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB17PXHCID));
    PmtshieldHitsCollection* hSHLDB17NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB17NXHCID));
    ///Shield in Bar18
    PmtshieldHitsCollection* hSHLDB18PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB18PXHCID));
    PmtshieldHitsCollection* hSHLDB18NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB18NXHCID));
    ///Shield in Bar19
    PmtshieldHitsCollection* hSHLDB19PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB19PXHCID));
    PmtshieldHitsCollection* hSHLDB19NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB19NXHCID));
    ///Shield in Bar20
    PmtshieldHitsCollection* hSHLDB20PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB20PXHCID));
    PmtshieldHitsCollection* hSHLDB20NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB20NXHCID));
    ///Shield in Bar21
    PmtshieldHitsCollection* hSHLDB21PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB21PXHCID));
    PmtshieldHitsCollection* hSHLDB21NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB21NXHCID));
    ///Shield in Bar22
    PmtshieldHitsCollection* hSHLDB22PX 
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB22PXHCID));
    PmtshieldHitsCollection* hSHLDB22NX
      = static_cast<PmtshieldHitsCollection*>(hce->GetHC(fSHLDB22NXHCID));

     
    if ( (!sddHC)  || (!hHCLM) || (!hHC1) || (!hHC2) || (!hHC3)|| (!hHC4) || (!hHC5) || (!hHC6)|| (!hHC7) || (!hHC8) || (!hHC9)|| (!hHC10) || (!hHC11) || (!hHC12)|| (!hHC13) || (!hHC14) || (!hHC15)|| (!hHC16) || (!hHC17) || (!hHC18)|| (!hHC19) || (!hHC20) || (!hHC21)|| (!hHC22) || (!hSHLDB1PX) || (!hSHLDB1NX)|| (!hSHLDB2PX) || (!hSHLDB2NX) || (!hSHLDB3PX) || (!hSHLDB3NX)|| (!hSHLDB4PX) || (!hSHLDB4NX)|| (!hSHLDB5PX) || (!hSHLDB5NX)|| (!hSHLDB6PX) || (!hSHLDB6NX)|| (!hSHLDB7PX) || (!hSHLDB7NX)|| (!hSHLDB8PX) || (!hSHLDB8NX)|| (!hSHLDB9PX) || (!hSHLDB9NX)|| (!hSHLDB10PX) || (!hSHLDB10NX)|| (!hSHLDB11PX) || (!hSHLDB11NX)|| (!hSHLDB12PX) || (!hSHLDB12NX)|| (!hSHLDB13PX) || (!hSHLDB13NX)|| (!hSHLDB14PX) || (!hSHLDB14NX)|| (!hSHLDB15PX) || (!hSHLDB15NX)|| (!hSHLDB16PX) || (!hSHLDB16NX)|| (!hSHLDB17PX) || (!hSHLDB17NX)|| (!hSHLDB18PX) || (!hSHLDB18NX)|| (!hSHLDB19PX) || (!hSHLDB19NX)|| (!hSHLDB20PX) || (!hSHLDB20NX)|| (!hSHLDB21PX) || (!hSHLDB21NX)|| (!hSHLDB22PX) || (!hSHLDB22NX)
       )
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n"; 
        G4Exception("EventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }



    //=================================
    // Fill histograms & ntuple
    
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Fill ntuple


     ///The energy of incident neutron.
     /// ~~~~~~~~~~~~~~~~~~~ Version of GPS. ~~~~~~~~~~~~~~~~~~
     G4RunManager* runManager = G4RunManager::GetRunManager();
     exGPSPrimaryGeneratorAction* generator = (exGPSPrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();
     G4double energy = generator->GetParticleSource()->GetParticleEnergy();

     /// ~~~~~~~~~~~~~~~~  Version of G4 particlegun. ~~~~~~~~~~~~~~~~~~
     ///PrimaryGeneratorAction* generator = (PrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();
     ///G4ParticleDefinition* particle = generator->GetParticleSource()->GetParticleDefinition();
     ///G4String Particle = particle->GetParticleName();
     ///G4double energy = generator->fParticleGun()->GetParticleEnergy();

     analysisManager->FillNtupleDColumn(0,energy/keV);





    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Collimator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Collimator # of Hits
    G4int n_hit_c = hHCLM->entries();///n_hit_c is the number of hits per incident particle in collimator.  
    analysisManager->FillNtupleIColumn(1, n_hit_c);

    G4double T_1st_hit_clm = 0.;
    for (G4int i=0;i<n_hit_c;i++)
    {
        CollimatorHit* hit = (*hHCLM)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_clm = (*hHCLM)[0]->GetTime();
        }
    }

    // Time recorded in Collimator
     if (T_1st_hit_clm > 0. && T_1st_hit_clm < 2000./ns){///Chaneged from 1000ns in Jan25,2015. After this change(only for collimator),Marco says the energy deposited is higher than before changing. 
     analysisManager->FillNtupleDColumn(2,T_1st_hit_clm/ns);
     }    




    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SDD ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
    G4int n_hit_sdd = sddHC->entries();///n_hit_sdd is the number of hits per incident particle in sdd.  

    for (G4int i=0;i<n_hit_sdd;i++)
    {
       SddHit* hit = (*sddHC)[i];
       G4ThreeVector Pos = hit->GetPos();
    }
    // # of Hits,Sdd
    analysisManager->FillNtupleIColumn(3, sddHC->entries());
    
    // Deposited energy, Sdd
    G4int totalSddHit = 0;
    G4double totalSddE = 0.;
    G4double E_1st_hit_Sdd = 0.;
    G4double T_1st_hit_Sdd = 0.;
    for (G4int i=0;i<n_hit_sdd;i++)
    {
        SddHit* hit = (*sddHC)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Sdd = (*sddHC)[0]->GetTime();
        E_1st_hit_Sdd = (*sddHC)[0]->GetEdep();
            totalSddHit++;
            totalSddE += eDep;
          }
    }
    analysisManager->FillNtupleDColumn(4, totalSddE/keV);
    analysisManager->FillNtupleDColumn(5,E_1st_hit_Sdd/keV);


    // Time 1
     if (T_1st_hit_Sdd > 0. && T_1st_hit_Sdd < 2000./ns){ 
     analysisManager->FillNtupleDColumn(6,T_1st_hit_Sdd/ns);
    // Reconstructed energy for bar 1
     analysisManager->FillNtupleDColumn(7, 1.3*1.0E+6 / (T_1st_hit_Sdd*T_1st_hit_Sdd));
     }

    // print on screen 
    for (G4int i=0;i<n_hit_sdd;i++)
    {
        SddHit* hit = (*sddHC)[i];
        hit->Print();
    }


    ///place_event_action
    ///# of Hits, Bar1
    G4int n_hit_1 = hHC1->entries();

    for (G4int i=0;i<n_hit_1;i++)
    {
       HodoscopeHit* hit = (*hHC1)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(8, hHC1->entries());


    ///Bar1 Energy
    G4int totalBar1Hit = 0;
    G4double totalBar1E = 0.;
    G4double E_1st_hit_Bar1 = 0.;
    G4double T_1st_hit_Bar1 = 0.;
    G4double X_1st_hit_Bar1 = 0.;
    G4double Y_1st_hit_Bar1 = 0.;
    G4double Z_1st_hit_Bar1 = 0.;

    for (G4int i=0;i<n_hit_1;i++)
    {
        HodoscopeHit* hit = (*hHC1)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar1 = (*hHC1)[0]->GetTime();
        E_1st_hit_Bar1 = (*hHC1)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar1 = worldPos.x();
        Y_1st_hit_Bar1 = worldPos.y();
        Z_1st_hit_Bar1 = worldPos.z();
        totalBar1Hit++;
        totalBar1E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(9, totalBar1E/keV);

    ///Bar1, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(10,E_1st_hit_Bar1/keV);

    ///Time 1
    if (T_1st_hit_Bar1 > 0. && T_1st_hit_Bar1 < 2000./ns){
    analysisManager->FillNtupleDColumn(11,T_1st_hit_Bar1/ns);

    ///Reconstructed energy for bar 1
     analysisManager->FillNtupleDColumn(12, 2.7*1.0E+6 / (T_1st_hit_Bar1*T_1st_hit_Bar1));
     }

    ///Bar1, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(13,X_1st_hit_Bar1/cm);
    analysisManager->FillNtupleDColumn(14,Y_1st_hit_Bar1/cm);
    analysisManager->FillNtupleDColumn(15,Z_1st_hit_Bar1/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_1;i++)
    {
        HodoscopeHit* hit = (*hHC1)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar1, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb1px = hSHLDB1PX->entries();///n_hit_sb1px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(16, n_hit_sb1px);

    G4double T_1st_hit_sb1px = 0.;
    for (G4int i=0;i<n_hit_sb1px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB1PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb1px = (*hSHLDB1PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb1px > 0. && T_1st_hit_sb1px < 2000./ns){
    analysisManager->FillNtupleDColumn(17,T_1st_hit_sb1px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar1, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb1nx = hSHLDB1NX->entries();///n_hit_sb1nx is the # of hits in the shield of bar1 in neg X.  
    analysisManager->FillNtupleIColumn(18, n_hit_sb1nx);

    G4double T_1st_hit_sb1nx = 0.;
    for (G4int i=0;i<n_hit_sb1nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB1NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb1nx = (*hSHLDB1NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb1nx > 0. && T_1st_hit_sb1nx < 2000./ns){
     analysisManager->FillNtupleDColumn(19,T_1st_hit_sb1nx/ns);
     }





    ///# of Hits, Bar2
    G4int n_hit_2 = hHC2->entries();

    for (G4int i=0;i<n_hit_2;i++)
    {
       HodoscopeHit* hit = (*hHC2)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(20, hHC2->entries());


    ///Bar2 Energy
    G4int totalBar2Hit = 0;
    G4double totalBar2E = 0.;
    G4double E_1st_hit_Bar2 = 0.;
    G4double T_1st_hit_Bar2 = 0.;
    G4double X_1st_hit_Bar2 = 0.;
    G4double Y_1st_hit_Bar2 = 0.;
    G4double Z_1st_hit_Bar2 = 0.;

    for (G4int i=0;i<n_hit_2;i++)
    {
        HodoscopeHit* hit = (*hHC2)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar2 = (*hHC2)[0]->GetTime();
        E_1st_hit_Bar2 = (*hHC2)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar2 = worldPos.x();
        Y_1st_hit_Bar2 = worldPos.y();
        Z_1st_hit_Bar2 = worldPos.z();
        totalBar2Hit++;
        totalBar2E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(21, totalBar2E/keV);

    ///Bar2, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(22,E_1st_hit_Bar2/keV);

    ///Time 2
    if (T_1st_hit_Bar2 > 0. && T_1st_hit_Bar2 < 2000./ns){
    analysisManager->FillNtupleDColumn(23,T_1st_hit_Bar2/ns);

    ///Reconstructed energy for bar 2
     analysisManager->FillNtupleDColumn(24, 2.7*1.0E+6 / (T_1st_hit_Bar2*T_1st_hit_Bar2));
     }

    ///Bar2, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(25,X_1st_hit_Bar2/cm);
    analysisManager->FillNtupleDColumn(26,Y_1st_hit_Bar2/cm);
    analysisManager->FillNtupleDColumn(27,Z_1st_hit_Bar2/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_2;i++)
    {
        HodoscopeHit* hit = (*hHC2)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar2, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb2px = hSHLDB2PX->entries();///n_hit_sb2px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(28, n_hit_sb2px);

    G4double T_1st_hit_sb2px = 0.;
    for (G4int i=0;i<n_hit_sb2px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB2PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb2px = (*hSHLDB2PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb2px > 0. && T_1st_hit_sb2px < 2000./ns){
    analysisManager->FillNtupleDColumn(29,T_1st_hit_sb2px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar2, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb2nx = hSHLDB2NX->entries();///n_hit_sb2nx is the # of hits in the shield of bar2 in neg X.  
    analysisManager->FillNtupleIColumn(30, n_hit_sb2nx);

    G4double T_1st_hit_sb2nx = 0.;
    for (G4int i=0;i<n_hit_sb2nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB2NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb2nx = (*hSHLDB2NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb2nx > 0. && T_1st_hit_sb2nx < 2000./ns){
     analysisManager->FillNtupleDColumn(31,T_1st_hit_sb2nx/ns);
     }





    ///# of Hits, Bar3
    G4int n_hit_3 = hHC3->entries();

    for (G4int i=0;i<n_hit_3;i++)
    {
       HodoscopeHit* hit = (*hHC3)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(32, hHC3->entries());


    ///Bar3 Energy
    G4int totalBar3Hit = 0;
    G4double totalBar3E = 0.;
    G4double E_1st_hit_Bar3 = 0.;
    G4double T_1st_hit_Bar3 = 0.;
    G4double X_1st_hit_Bar3 = 0.;
    G4double Y_1st_hit_Bar3 = 0.;
    G4double Z_1st_hit_Bar3 = 0.;

    for (G4int i=0;i<n_hit_3;i++)
    {
        HodoscopeHit* hit = (*hHC3)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar3 = (*hHC3)[0]->GetTime();
        E_1st_hit_Bar3 = (*hHC3)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        ///G4ThreeVector worldPos = (*hHC3)[0]->GetWorldPos();
        X_1st_hit_Bar3 = worldPos.x();
        Y_1st_hit_Bar3 = worldPos.y();
        Z_1st_hit_Bar3 = worldPos.z();
        totalBar3Hit++;
        totalBar3E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(33, totalBar3E/keV);

    ///Bar3, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(34,E_1st_hit_Bar3/keV);

    ///Time 3
    if (T_1st_hit_Bar3 > 0. && T_1st_hit_Bar3 < 2000./ns){
    analysisManager->FillNtupleDColumn(35,T_1st_hit_Bar3/ns);

    ///Reconstructed energy for bar 3
     analysisManager->FillNtupleDColumn(36, 2.7*1.0E+6 / (T_1st_hit_Bar3*T_1st_hit_Bar3));
     }

    ///Bar3, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(37,X_1st_hit_Bar3/cm);
    analysisManager->FillNtupleDColumn(38,Y_1st_hit_Bar3/cm);
    analysisManager->FillNtupleDColumn(39,Z_1st_hit_Bar3/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_3;i++)
    {
        HodoscopeHit* hit = (*hHC3)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar3, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb3px = hSHLDB3PX->entries();///n_hit_sb3px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(40, n_hit_sb3px);

    G4double T_1st_hit_sb3px = 0.;
    for (G4int i=0;i<n_hit_sb3px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB3PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb3px = (*hSHLDB3PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb3px > 0. && T_1st_hit_sb3px < 2000./ns){
    analysisManager->FillNtupleDColumn(41,T_1st_hit_sb3px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar3, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb3nx = hSHLDB3NX->entries();///n_hit_sb3nx is the # of hits in the shield of bar3 in neg X.  
    analysisManager->FillNtupleIColumn(42, n_hit_sb3nx);

    G4double T_1st_hit_sb3nx = 0.;
    for (G4int i=0;i<n_hit_sb3nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB3NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb3nx = (*hSHLDB3NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb3nx > 0. && T_1st_hit_sb3nx < 2000./ns){
     analysisManager->FillNtupleDColumn(43,T_1st_hit_sb3nx/ns);
     }





    ///# of Hits, Bar4
    G4int n_hit_4 = hHC4->entries();

    for (G4int i=0;i<n_hit_4;i++)
    {
       HodoscopeHit* hit = (*hHC4)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(44, hHC4->entries());


    ///Bar4 Energy
    G4int totalBar4Hit = 0;
    G4double totalBar4E = 0.;
    G4double E_1st_hit_Bar4 = 0.;
    G4double T_1st_hit_Bar4 = 0.;
    G4double X_1st_hit_Bar4 = 0.;
    G4double Y_1st_hit_Bar4 = 0.;
    G4double Z_1st_hit_Bar4 = 0.;

    for (G4int i=0;i<n_hit_4;i++)
    {
        HodoscopeHit* hit = (*hHC4)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar4 = (*hHC4)[0]->GetTime();
        E_1st_hit_Bar4 = (*hHC4)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar4 = worldPos.x();
        Y_1st_hit_Bar4 = worldPos.y();
        Z_1st_hit_Bar4 = worldPos.z();
        totalBar4Hit++;
        totalBar4E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(45, totalBar4E/keV);

    ///Bar4, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(46,E_1st_hit_Bar4/keV);

    ///Time 4
    if (T_1st_hit_Bar4 > 0. && T_1st_hit_Bar4 < 2000./ns){
    analysisManager->FillNtupleDColumn(47,T_1st_hit_Bar4/ns);

    ///Reconstructed energy for bar 4
     analysisManager->FillNtupleDColumn(48, 2.7*1.0E+6 / (T_1st_hit_Bar4*T_1st_hit_Bar4));
     }

    ///Bar4, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(49,X_1st_hit_Bar4/cm);
    analysisManager->FillNtupleDColumn(50,Y_1st_hit_Bar4/cm);
    analysisManager->FillNtupleDColumn(51,Z_1st_hit_Bar4/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_4;i++)
    {
        HodoscopeHit* hit = (*hHC4)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar4, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb4px = hSHLDB4PX->entries();///n_hit_sb4px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(52, n_hit_sb4px);

    G4double T_1st_hit_sb4px = 0.;
    for (G4int i=0;i<n_hit_sb4px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB4PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb4px = (*hSHLDB4PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb4px > 0. && T_1st_hit_sb4px < 2000./ns){
    analysisManager->FillNtupleDColumn(53,T_1st_hit_sb4px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar4, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb4nx = hSHLDB4NX->entries();///n_hit_sb4nx is the # of hits in the shield of bar4 in neg X.  
    analysisManager->FillNtupleIColumn(54, n_hit_sb4nx);

    G4double T_1st_hit_sb4nx = 0.;
    for (G4int i=0;i<n_hit_sb4nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB4NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb4nx = (*hSHLDB4NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb4nx > 0. && T_1st_hit_sb4nx < 2000./ns){
     analysisManager->FillNtupleDColumn(55,T_1st_hit_sb4nx/ns);
     }





    ///# of Hits, Bar5
    G4int n_hit_5 = hHC5->entries();

    for (G4int i=0;i<n_hit_5;i++)
    {
       HodoscopeHit* hit = (*hHC5)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(56, hHC5->entries());


    ///Bar5 Energy
    G4int totalBar5Hit = 0;
    G4double totalBar5E = 0.;
    G4double E_1st_hit_Bar5 = 0.;
    G4double T_1st_hit_Bar5 = 0.;
    G4double X_1st_hit_Bar5 = 0.;
    G4double Y_1st_hit_Bar5 = 0.;
    G4double Z_1st_hit_Bar5 = 0.;

    for (G4int i=0;i<n_hit_5;i++)
    {
        HodoscopeHit* hit = (*hHC5)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar5 = (*hHC5)[0]->GetTime();
        E_1st_hit_Bar5 = (*hHC5)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar5 = worldPos.x();
        Y_1st_hit_Bar5 = worldPos.y();
        Z_1st_hit_Bar5 = worldPos.z();
        totalBar5Hit++;
        totalBar5E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(57, totalBar5E/keV);

    ///Bar5, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(58,E_1st_hit_Bar5/keV);

    ///Time 5
    if (T_1st_hit_Bar5 > 0. && T_1st_hit_Bar5 < 2000./ns){
    analysisManager->FillNtupleDColumn(59,T_1st_hit_Bar5/ns);

    ///Reconstructed energy for bar 5
     analysisManager->FillNtupleDColumn(60, 2.7*1.0E+6 / (T_1st_hit_Bar5*T_1st_hit_Bar5));
     }

    ///Bar5, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(61,X_1st_hit_Bar5/cm);
    analysisManager->FillNtupleDColumn(62,Y_1st_hit_Bar5/cm);
    analysisManager->FillNtupleDColumn(63,Z_1st_hit_Bar5/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_5;i++)
    {
        HodoscopeHit* hit = (*hHC5)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar5, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb5px = hSHLDB5PX->entries();///n_hit_sb5px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(64, n_hit_sb5px);

    G4double T_1st_hit_sb5px = 0.;
    for (G4int i=0;i<n_hit_sb5px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB5PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb5px = (*hSHLDB5PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb5px > 0. && T_1st_hit_sb5px < 2000./ns){
    analysisManager->FillNtupleDColumn(65,T_1st_hit_sb5px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar5, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb5nx = hSHLDB5NX->entries();///n_hit_sb5nx is the # of hits in the shield of bar5 in neg X.  
    analysisManager->FillNtupleIColumn(66, n_hit_sb5nx);

    G4double T_1st_hit_sb5nx = 0.;
    for (G4int i=0;i<n_hit_sb5nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB5NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb5nx = (*hSHLDB5NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb5nx > 0. && T_1st_hit_sb5nx < 2000./ns){
     analysisManager->FillNtupleDColumn(67,T_1st_hit_sb5nx/ns);
     }





    ///# of Hits, Bar6
    G4int n_hit_6 = hHC6->entries();

    for (G4int i=0;i<n_hit_6;i++)
    {
       HodoscopeHit* hit = (*hHC6)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(68, hHC6->entries());


    ///Bar6 Energy
    G4int totalBar6Hit = 0;
    G4double totalBar6E = 0.;
    G4double E_1st_hit_Bar6 = 0.;
    G4double T_1st_hit_Bar6 = 0.;
    G4double X_1st_hit_Bar6 = 0.;
    G4double Y_1st_hit_Bar6 = 0.;
    G4double Z_1st_hit_Bar6 = 0.;

    for (G4int i=0;i<n_hit_6;i++)
    {
        HodoscopeHit* hit = (*hHC6)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar6 = (*hHC6)[0]->GetTime();
        E_1st_hit_Bar6 = (*hHC6)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar6 = worldPos.x();
        Y_1st_hit_Bar6 = worldPos.y();
        Z_1st_hit_Bar6 = worldPos.z();
        totalBar6Hit++;
        totalBar6E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(69, totalBar6E/keV);

    ///Bar6, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(70,E_1st_hit_Bar6/keV);

    ///Time 6
    if (T_1st_hit_Bar6 > 0. && T_1st_hit_Bar6 < 2000./ns){
    analysisManager->FillNtupleDColumn(71,T_1st_hit_Bar6/ns);

    ///Reconstructed energy for bar 6
     analysisManager->FillNtupleDColumn(72, 2.7*1.0E+6 / (T_1st_hit_Bar6*T_1st_hit_Bar6));
     }

    ///Bar6, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(73,X_1st_hit_Bar6/cm);
    analysisManager->FillNtupleDColumn(74,Y_1st_hit_Bar6/cm);
    analysisManager->FillNtupleDColumn(75,Z_1st_hit_Bar6/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_6;i++)
    {
        HodoscopeHit* hit = (*hHC6)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar6, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb6px = hSHLDB6PX->entries();///n_hit_sb6px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(76, n_hit_sb6px);

    G4double T_1st_hit_sb6px = 0.;
    for (G4int i=0;i<n_hit_sb6px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB6PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb6px = (*hSHLDB6PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb6px > 0. && T_1st_hit_sb6px < 2000./ns){
    analysisManager->FillNtupleDColumn(77,T_1st_hit_sb6px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar6, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb6nx = hSHLDB6NX->entries();///n_hit_sb6nx is the # of hits in the shield of bar6 in neg X.  
    analysisManager->FillNtupleIColumn(78, n_hit_sb6nx);

    G4double T_1st_hit_sb6nx = 0.;
    for (G4int i=0;i<n_hit_sb6nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB6NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb6nx = (*hSHLDB6NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb6nx > 0. && T_1st_hit_sb6nx < 2000./ns){
     analysisManager->FillNtupleDColumn(79,T_1st_hit_sb6nx/ns);
     }





    ///# of Hits, Bar7
    G4int n_hit_7 = hHC7->entries();

    for (G4int i=0;i<n_hit_7;i++)
    {
       HodoscopeHit* hit = (*hHC7)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(80, hHC7->entries());


    ///Bar7 Energy
    G4int totalBar7Hit = 0;
    G4double totalBar7E = 0.;
    G4double E_1st_hit_Bar7 = 0.;
    G4double T_1st_hit_Bar7 = 0.;
    G4double X_1st_hit_Bar7 = 0.;
    G4double Y_1st_hit_Bar7 = 0.;
    G4double Z_1st_hit_Bar7 = 0.;

    for (G4int i=0;i<n_hit_7;i++)
    {
        HodoscopeHit* hit = (*hHC7)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar7 = (*hHC7)[0]->GetTime();
        E_1st_hit_Bar7 = (*hHC7)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar7 = worldPos.x();
        Y_1st_hit_Bar7 = worldPos.y();
        Z_1st_hit_Bar7 = worldPos.z();
        totalBar7Hit++;
        totalBar7E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(81, totalBar7E/keV);

    ///Bar7, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(82,E_1st_hit_Bar7/keV);

    ///Time 7
    if (T_1st_hit_Bar7 > 0. && T_1st_hit_Bar7 < 2000./ns){
    analysisManager->FillNtupleDColumn(83,T_1st_hit_Bar7/ns);

    ///Reconstructed energy for bar 7
     analysisManager->FillNtupleDColumn(84, 2.7*1.0E+6 / (T_1st_hit_Bar7*T_1st_hit_Bar7));
     }

    ///Bar7, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(85,X_1st_hit_Bar7/cm);
    analysisManager->FillNtupleDColumn(86,Y_1st_hit_Bar7/cm);
    analysisManager->FillNtupleDColumn(87,Z_1st_hit_Bar7/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_7;i++)
    {
        HodoscopeHit* hit = (*hHC7)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar7, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb7px = hSHLDB7PX->entries();///n_hit_sb7px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(88, n_hit_sb7px);

    G4double T_1st_hit_sb7px = 0.;
    for (G4int i=0;i<n_hit_sb7px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB7PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb7px = (*hSHLDB7PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb7px > 0. && T_1st_hit_sb7px < 2000./ns){
    analysisManager->FillNtupleDColumn(89,T_1st_hit_sb7px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar7, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb7nx = hSHLDB7NX->entries();///n_hit_sb7nx is the # of hits in the shield of bar7 in neg X.  
    analysisManager->FillNtupleIColumn(90, n_hit_sb7nx);

    G4double T_1st_hit_sb7nx = 0.;
    for (G4int i=0;i<n_hit_sb7nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB7NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb7nx = (*hSHLDB7NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb7nx > 0. && T_1st_hit_sb7nx < 2000./ns){
     analysisManager->FillNtupleDColumn(91,T_1st_hit_sb7nx/ns);
     }





    ///# of Hits, Bar8
    G4int n_hit_8 = hHC8->entries();

    for (G4int i=0;i<n_hit_8;i++)
    {
       HodoscopeHit* hit = (*hHC8)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(92, hHC8->entries());


    ///Bar8 Energy
    G4int totalBar8Hit = 0;
    G4double totalBar8E = 0.;
    G4double E_1st_hit_Bar8 = 0.;
    G4double T_1st_hit_Bar8 = 0.;
    G4double X_1st_hit_Bar8 = 0.;
    G4double Y_1st_hit_Bar8 = 0.;
    G4double Z_1st_hit_Bar8 = 0.;

    for (G4int i=0;i<n_hit_8;i++)
    {
        HodoscopeHit* hit = (*hHC8)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar8 = (*hHC8)[0]->GetTime();
        E_1st_hit_Bar8 = (*hHC8)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar8 = worldPos.x();
        Y_1st_hit_Bar8 = worldPos.y();
        Z_1st_hit_Bar8 = worldPos.z();
        totalBar8Hit++;
        totalBar8E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(93, totalBar8E/keV);

    ///Bar8, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(94,E_1st_hit_Bar8/keV);

    ///Time 8
    if (T_1st_hit_Bar8 > 0. && T_1st_hit_Bar8 < 2000./ns){
    analysisManager->FillNtupleDColumn(95,T_1st_hit_Bar8/ns);

    ///Reconstructed energy for bar 8
     analysisManager->FillNtupleDColumn(96, 2.7*1.0E+6 / (T_1st_hit_Bar8*T_1st_hit_Bar8));
     }

    ///Bar8, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(97,X_1st_hit_Bar8/cm);
    analysisManager->FillNtupleDColumn(98,Y_1st_hit_Bar8/cm);
    analysisManager->FillNtupleDColumn(99,Z_1st_hit_Bar8/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_8;i++)
    {
        HodoscopeHit* hit = (*hHC8)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar8, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb8px = hSHLDB8PX->entries();///n_hit_sb8px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(100, n_hit_sb8px);

    G4double T_1st_hit_sb8px = 0.;
    for (G4int i=0;i<n_hit_sb8px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB8PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb8px = (*hSHLDB8PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb8px > 0. && T_1st_hit_sb8px < 2000./ns){
    analysisManager->FillNtupleDColumn(101,T_1st_hit_sb8px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar8, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb8nx = hSHLDB8NX->entries();///n_hit_sb8nx is the # of hits in the shield of bar8 in neg X.  
    analysisManager->FillNtupleIColumn(102, n_hit_sb8nx);

    G4double T_1st_hit_sb8nx = 0.;
    for (G4int i=0;i<n_hit_sb8nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB8NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb8nx = (*hSHLDB8NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb8nx > 0. && T_1st_hit_sb8nx < 2000./ns){
     analysisManager->FillNtupleDColumn(103,T_1st_hit_sb8nx/ns);
     }





    ///# of Hits, Bar9
    G4int n_hit_9 = hHC9->entries();

    for (G4int i=0;i<n_hit_9;i++)
    {
       HodoscopeHit* hit = (*hHC9)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(104, hHC9->entries());


    ///Bar9 Energy
    G4int totalBar9Hit = 0;
    G4double totalBar9E = 0.;
    G4double E_1st_hit_Bar9 = 0.;
    G4double T_1st_hit_Bar9 = 0.;
    G4double X_1st_hit_Bar9 = 0.;
    G4double Y_1st_hit_Bar9 = 0.;
    G4double Z_1st_hit_Bar9 = 0.;

    for (G4int i=0;i<n_hit_9;i++)
    {
        HodoscopeHit* hit = (*hHC9)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar9 = (*hHC9)[0]->GetTime();
        E_1st_hit_Bar9 = (*hHC9)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar9 = worldPos.x();
        Y_1st_hit_Bar9 = worldPos.y();
        Z_1st_hit_Bar9 = worldPos.z();
        totalBar9Hit++;
        totalBar9E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(105, totalBar9E/keV);

    ///Bar9, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(106,E_1st_hit_Bar9/keV);

    ///Time 9
    if (T_1st_hit_Bar9 > 0. && T_1st_hit_Bar9 < 2000./ns){
    analysisManager->FillNtupleDColumn(107,T_1st_hit_Bar9/ns);

    ///Reconstructed energy for bar 9
     analysisManager->FillNtupleDColumn(108, 2.7*1.0E+6 / (T_1st_hit_Bar9*T_1st_hit_Bar9));
     }

    ///Bar9, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(109,X_1st_hit_Bar9/cm);
    analysisManager->FillNtupleDColumn(110,Y_1st_hit_Bar9/cm);
    analysisManager->FillNtupleDColumn(111,Z_1st_hit_Bar9/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_9;i++)
    {
        HodoscopeHit* hit = (*hHC9)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar9, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb9px = hSHLDB9PX->entries();///n_hit_sb9px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(112, n_hit_sb9px);

    G4double T_1st_hit_sb9px = 0.;
    for (G4int i=0;i<n_hit_sb9px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB9PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb9px = (*hSHLDB9PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb9px > 0. && T_1st_hit_sb9px < 2000./ns){
    analysisManager->FillNtupleDColumn(113,T_1st_hit_sb9px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar9, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb9nx = hSHLDB9NX->entries();///n_hit_sb9nx is the # of hits in the shield of bar9 in neg X.  
    analysisManager->FillNtupleIColumn(114, n_hit_sb9nx);

    G4double T_1st_hit_sb9nx = 0.;
    for (G4int i=0;i<n_hit_sb9nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB9NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb9nx = (*hSHLDB9NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb9nx > 0. && T_1st_hit_sb9nx < 2000./ns){
     analysisManager->FillNtupleDColumn(115,T_1st_hit_sb9nx/ns);
     }





    ///# of Hits, Bar10
    G4int n_hit_10 = hHC10->entries();

    for (G4int i=0;i<n_hit_10;i++)
    {
       HodoscopeHit* hit = (*hHC10)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(116, hHC10->entries());


    ///Bar10 Energy
    G4int totalBar10Hit = 0;
    G4double totalBar10E = 0.;
    G4double E_1st_hit_Bar10 = 0.;
    G4double T_1st_hit_Bar10 = 0.;
    G4double X_1st_hit_Bar10 = 0.;
    G4double Y_1st_hit_Bar10 = 0.;
    G4double Z_1st_hit_Bar10 = 0.;

    for (G4int i=0;i<n_hit_10;i++)
    {
        HodoscopeHit* hit = (*hHC10)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar10 = (*hHC10)[0]->GetTime();
        E_1st_hit_Bar10 = (*hHC10)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar10 = worldPos.x();
        Y_1st_hit_Bar10 = worldPos.y();
        Z_1st_hit_Bar10 = worldPos.z();
        totalBar10Hit++;
        totalBar10E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(117, totalBar10E/keV);

    ///Bar10, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(118,E_1st_hit_Bar10/keV);

    ///Time 10
    if (T_1st_hit_Bar10 > 0. && T_1st_hit_Bar10 < 2000./ns){
    analysisManager->FillNtupleDColumn(119,T_1st_hit_Bar10/ns);

    ///Reconstructed energy for bar 10
     analysisManager->FillNtupleDColumn(120, 2.7*1.0E+6 / (T_1st_hit_Bar10*T_1st_hit_Bar10));
     }

    ///Bar10, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(121,X_1st_hit_Bar10/cm);
    analysisManager->FillNtupleDColumn(122,Y_1st_hit_Bar10/cm);
    analysisManager->FillNtupleDColumn(123,Z_1st_hit_Bar10/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_10;i++)
    {
        HodoscopeHit* hit = (*hHC10)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar10, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb10px = hSHLDB10PX->entries();///n_hit_sb10px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(124, n_hit_sb10px);

    G4double T_1st_hit_sb10px = 0.;
    for (G4int i=0;i<n_hit_sb10px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB10PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb10px = (*hSHLDB10PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb10px > 0. && T_1st_hit_sb10px < 2000./ns){
    analysisManager->FillNtupleDColumn(125,T_1st_hit_sb10px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar10, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb10nx = hSHLDB10NX->entries();///n_hit_sb10nx is the # of hits in the shield of bar10 in neg X.  
    analysisManager->FillNtupleIColumn(126, n_hit_sb10nx);

    G4double T_1st_hit_sb10nx = 0.;
    for (G4int i=0;i<n_hit_sb10nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB10NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb10nx = (*hSHLDB10NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb10nx > 0. && T_1st_hit_sb10nx < 2000./ns){
     analysisManager->FillNtupleDColumn(127,T_1st_hit_sb10nx/ns);
     }





    ///# of Hits, Bar11
    G4int n_hit_11 = hHC11->entries();

    for (G4int i=0;i<n_hit_11;i++)
    {
       HodoscopeHit* hit = (*hHC11)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(128, hHC11->entries());


    ///Bar11 Energy
    G4int totalBar11Hit = 0;
    G4double totalBar11E = 0.;
    G4double E_1st_hit_Bar11 = 0.;
    G4double T_1st_hit_Bar11 = 0.;
    G4double X_1st_hit_Bar11 = 0.;
    G4double Y_1st_hit_Bar11 = 0.;
    G4double Z_1st_hit_Bar11 = 0.;

    for (G4int i=0;i<n_hit_11;i++)
    {
        HodoscopeHit* hit = (*hHC11)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar11 = (*hHC11)[0]->GetTime();
        E_1st_hit_Bar11 = (*hHC11)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar11 = worldPos.x();
        Y_1st_hit_Bar11 = worldPos.y();
        Z_1st_hit_Bar11 = worldPos.z();
        totalBar11Hit++;
        totalBar11E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(129, totalBar11E/keV);

    ///Bar11, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(130,E_1st_hit_Bar11/keV);

    ///Time 11
    if (T_1st_hit_Bar11 > 0. && T_1st_hit_Bar11 < 2000./ns){
    analysisManager->FillNtupleDColumn(131,T_1st_hit_Bar11/ns);

    ///Reconstructed energy for bar 11
     analysisManager->FillNtupleDColumn(132, 2.7*1.0E+6 / (T_1st_hit_Bar11*T_1st_hit_Bar11));
     }

    ///Bar11, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(133,X_1st_hit_Bar11/cm);
    analysisManager->FillNtupleDColumn(134,Y_1st_hit_Bar11/cm);
    analysisManager->FillNtupleDColumn(135,Z_1st_hit_Bar11/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_11;i++)
    {
        HodoscopeHit* hit = (*hHC11)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar11, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb11px = hSHLDB11PX->entries();///n_hit_sb11px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(136, n_hit_sb11px);

    G4double T_1st_hit_sb11px = 0.;
    for (G4int i=0;i<n_hit_sb11px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB11PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb11px = (*hSHLDB11PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb11px > 0. && T_1st_hit_sb11px < 2000./ns){
    analysisManager->FillNtupleDColumn(137,T_1st_hit_sb11px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar11, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb11nx = hSHLDB11NX->entries();///n_hit_sb11nx is the # of hits in the shield of bar11 in neg X.  
    analysisManager->FillNtupleIColumn(138, n_hit_sb11nx);

    G4double T_1st_hit_sb11nx = 0.;
    for (G4int i=0;i<n_hit_sb11nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB11NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb11nx = (*hSHLDB11NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb11nx > 0. && T_1st_hit_sb11nx < 2000./ns){
     analysisManager->FillNtupleDColumn(139,T_1st_hit_sb11nx/ns);
     }





    ///# of Hits, Bar12
    G4int n_hit_12 = hHC12->entries();

    for (G4int i=0;i<n_hit_12;i++)
    {
       HodoscopeHit* hit = (*hHC12)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(140, hHC12->entries());


    ///Bar12 Energy
    G4int totalBar12Hit = 0;
    G4double totalBar12E = 0.;
    G4double E_1st_hit_Bar12 = 0.;
    G4double T_1st_hit_Bar12 = 0.;
    G4double X_1st_hit_Bar12 = 0.;
    G4double Y_1st_hit_Bar12 = 0.;
    G4double Z_1st_hit_Bar12 = 0.;

    for (G4int i=0;i<n_hit_12;i++)
    {
        HodoscopeHit* hit = (*hHC12)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar12 = (*hHC12)[0]->GetTime();
        E_1st_hit_Bar12 = (*hHC12)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar12 = worldPos.x();
        Y_1st_hit_Bar12 = worldPos.y();
        Z_1st_hit_Bar12 = worldPos.z();
        totalBar12Hit++;
        totalBar12E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(141, totalBar12E/keV);

    ///Bar12, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(142,E_1st_hit_Bar12/keV);

    ///Time 12
    if (T_1st_hit_Bar12 > 0. && T_1st_hit_Bar12 < 2000./ns){
    analysisManager->FillNtupleDColumn(143,T_1st_hit_Bar12/ns);

    ///Reconstructed energy for bar 12
     analysisManager->FillNtupleDColumn(144, 2.7*1.0E+6 / (T_1st_hit_Bar12*T_1st_hit_Bar12));
     }

    ///Bar12, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(145,X_1st_hit_Bar12/cm);
    analysisManager->FillNtupleDColumn(146,Y_1st_hit_Bar12/cm);
    analysisManager->FillNtupleDColumn(147,Z_1st_hit_Bar12/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_12;i++)
    {
        HodoscopeHit* hit = (*hHC12)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar12, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb12px = hSHLDB12PX->entries();///n_hit_sb12px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(148, n_hit_sb12px);

    G4double T_1st_hit_sb12px = 0.;
    for (G4int i=0;i<n_hit_sb12px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB12PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb12px = (*hSHLDB12PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb12px > 0. && T_1st_hit_sb12px < 2000./ns){
    analysisManager->FillNtupleDColumn(149,T_1st_hit_sb12px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar12, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb12nx = hSHLDB12NX->entries();///n_hit_sb12nx is the # of hits in the shield of bar12 in neg X.  
    analysisManager->FillNtupleIColumn(150, n_hit_sb12nx);

    G4double T_1st_hit_sb12nx = 0.;
    for (G4int i=0;i<n_hit_sb12nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB12NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb12nx = (*hSHLDB12NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb12nx > 0. && T_1st_hit_sb12nx < 2000./ns){
     analysisManager->FillNtupleDColumn(151,T_1st_hit_sb12nx/ns);
     }





    ///# of Hits, Bar13
    G4int n_hit_13 = hHC13->entries();

    for (G4int i=0;i<n_hit_13;i++)
    {
       HodoscopeHit* hit = (*hHC13)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(152, hHC13->entries());


    ///Bar13 Energy
    G4int totalBar13Hit = 0;
    G4double totalBar13E = 0.;
    G4double E_1st_hit_Bar13 = 0.;
    G4double T_1st_hit_Bar13 = 0.;
    G4double X_1st_hit_Bar13 = 0.;
    G4double Y_1st_hit_Bar13 = 0.;
    G4double Z_1st_hit_Bar13 = 0.;

    for (G4int i=0;i<n_hit_13;i++)
    {
        HodoscopeHit* hit = (*hHC13)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar13 = (*hHC13)[0]->GetTime();
        E_1st_hit_Bar13 = (*hHC13)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar13 = worldPos.x();
        Y_1st_hit_Bar13 = worldPos.y();
        Z_1st_hit_Bar13 = worldPos.z();
        totalBar13Hit++;
        totalBar13E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(153, totalBar13E/keV);

    ///Bar13, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(154,E_1st_hit_Bar13/keV);

    ///Time 13
    if (T_1st_hit_Bar13 > 0. && T_1st_hit_Bar13 < 2000./ns){
    analysisManager->FillNtupleDColumn(155,T_1st_hit_Bar13/ns);

    ///Reconstructed energy for bar 13
     analysisManager->FillNtupleDColumn(156, 2.7*1.0E+6 / (T_1st_hit_Bar13*T_1st_hit_Bar13));
     }

    ///Bar13, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(157,X_1st_hit_Bar13/cm);
    analysisManager->FillNtupleDColumn(158,Y_1st_hit_Bar13/cm);
    analysisManager->FillNtupleDColumn(159,Z_1st_hit_Bar13/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_13;i++)
    {
        HodoscopeHit* hit = (*hHC13)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar13, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb13px = hSHLDB13PX->entries();///n_hit_sb13px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(160, n_hit_sb13px);

    G4double T_1st_hit_sb13px = 0.;
    for (G4int i=0;i<n_hit_sb13px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB13PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb13px = (*hSHLDB13PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb13px > 0. && T_1st_hit_sb13px < 2000./ns){
    analysisManager->FillNtupleDColumn(161,T_1st_hit_sb13px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar13, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb13nx = hSHLDB13NX->entries();///n_hit_sb13nx is the # of hits in the shield of bar13 in neg X.  
    analysisManager->FillNtupleIColumn(162, n_hit_sb13nx);

    G4double T_1st_hit_sb13nx = 0.;
    for (G4int i=0;i<n_hit_sb13nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB13NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb13nx = (*hSHLDB13NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb13nx > 0. && T_1st_hit_sb13nx < 2000./ns){
     analysisManager->FillNtupleDColumn(163,T_1st_hit_sb13nx/ns);
     }





    ///# of Hits, Bar14
    G4int n_hit_14 = hHC14->entries();

    for (G4int i=0;i<n_hit_14;i++)
    {
       HodoscopeHit* hit = (*hHC14)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(164, hHC14->entries());


    ///Bar14 Energy
    G4int totalBar14Hit = 0;
    G4double totalBar14E = 0.;
    G4double E_1st_hit_Bar14 = 0.;
    G4double T_1st_hit_Bar14 = 0.;
    G4double X_1st_hit_Bar14 = 0.;
    G4double Y_1st_hit_Bar14 = 0.;
    G4double Z_1st_hit_Bar14 = 0.;

    for (G4int i=0;i<n_hit_14;i++)
    {
        HodoscopeHit* hit = (*hHC14)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar14 = (*hHC14)[0]->GetTime();
        E_1st_hit_Bar14 = (*hHC14)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar14 = worldPos.x();
        Y_1st_hit_Bar14 = worldPos.y();
        Z_1st_hit_Bar14 = worldPos.z();
        totalBar14Hit++;
        totalBar14E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(165, totalBar14E/keV);

    ///Bar14, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(166,E_1st_hit_Bar14/keV);

    ///Time 14
    if (T_1st_hit_Bar14 > 0. && T_1st_hit_Bar14 < 2000./ns){
    analysisManager->FillNtupleDColumn(167,T_1st_hit_Bar14/ns);

    ///Reconstructed energy for bar 14
     analysisManager->FillNtupleDColumn(168, 2.7*1.0E+6 / (T_1st_hit_Bar14*T_1st_hit_Bar14));
     }

    ///Bar14, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(169,X_1st_hit_Bar14/cm);
    analysisManager->FillNtupleDColumn(170,Y_1st_hit_Bar14/cm);
    analysisManager->FillNtupleDColumn(171,Z_1st_hit_Bar14/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_14;i++)
    {
        HodoscopeHit* hit = (*hHC14)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar14, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb14px = hSHLDB14PX->entries();///n_hit_sb14px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(172, n_hit_sb14px);

    G4double T_1st_hit_sb14px = 0.;
    for (G4int i=0;i<n_hit_sb14px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB14PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb14px = (*hSHLDB14PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb14px > 0. && T_1st_hit_sb14px < 2000./ns){
    analysisManager->FillNtupleDColumn(173,T_1st_hit_sb14px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar14, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb14nx = hSHLDB14NX->entries();///n_hit_sb14nx is the # of hits in the shield of bar14 in neg X.  
    analysisManager->FillNtupleIColumn(174, n_hit_sb14nx);

    G4double T_1st_hit_sb14nx = 0.;
    for (G4int i=0;i<n_hit_sb14nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB14NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb14nx = (*hSHLDB14NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb14nx > 0. && T_1st_hit_sb14nx < 2000./ns){
     analysisManager->FillNtupleDColumn(175,T_1st_hit_sb14nx/ns);
     }





    ///# of Hits, Bar15
    G4int n_hit_15 = hHC15->entries();

    for (G4int i=0;i<n_hit_15;i++)
    {
       HodoscopeHit* hit = (*hHC15)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(176, hHC15->entries());


    ///Bar15 Energy
    G4int totalBar15Hit = 0;
    G4double totalBar15E = 0.;
    G4double E_1st_hit_Bar15 = 0.;
    G4double T_1st_hit_Bar15 = 0.;
    G4double X_1st_hit_Bar15 = 0.;
    G4double Y_1st_hit_Bar15 = 0.;
    G4double Z_1st_hit_Bar15 = 0.;

    for (G4int i=0;i<n_hit_15;i++)
    {
        HodoscopeHit* hit = (*hHC15)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar15 = (*hHC15)[0]->GetTime();
        E_1st_hit_Bar15 = (*hHC15)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar15 = worldPos.x();
        Y_1st_hit_Bar15 = worldPos.y();
        Z_1st_hit_Bar15 = worldPos.z();
        totalBar15Hit++;
        totalBar15E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(177, totalBar15E/keV);

    ///Bar15, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(178,E_1st_hit_Bar15/keV);

    ///Time 15
    if (T_1st_hit_Bar15 > 0. && T_1st_hit_Bar15 < 2000./ns){
    analysisManager->FillNtupleDColumn(179,T_1st_hit_Bar15/ns);

    ///Reconstructed energy for bar 15
     analysisManager->FillNtupleDColumn(180, 2.7*1.0E+6 / (T_1st_hit_Bar15*T_1st_hit_Bar15));
     }

    ///Bar15, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(181,X_1st_hit_Bar15/cm);
    analysisManager->FillNtupleDColumn(182,Y_1st_hit_Bar15/cm);
    analysisManager->FillNtupleDColumn(183,Z_1st_hit_Bar15/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_15;i++)
    {
        HodoscopeHit* hit = (*hHC15)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar15, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb15px = hSHLDB15PX->entries();///n_hit_sb15px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(184, n_hit_sb15px);

    G4double T_1st_hit_sb15px = 0.;
    for (G4int i=0;i<n_hit_sb15px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB15PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb15px = (*hSHLDB15PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb15px > 0. && T_1st_hit_sb15px < 2000./ns){
    analysisManager->FillNtupleDColumn(185,T_1st_hit_sb15px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar15, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb15nx = hSHLDB15NX->entries();///n_hit_sb15nx is the # of hits in the shield of bar15 in neg X.  
    analysisManager->FillNtupleIColumn(186, n_hit_sb15nx);

    G4double T_1st_hit_sb15nx = 0.;
    for (G4int i=0;i<n_hit_sb15nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB15NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb15nx = (*hSHLDB15NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb15nx > 0. && T_1st_hit_sb15nx < 2000./ns){
     analysisManager->FillNtupleDColumn(187,T_1st_hit_sb15nx/ns);
     }





    ///# of Hits, Bar16
    G4int n_hit_16 = hHC16->entries();

    for (G4int i=0;i<n_hit_16;i++)
    {
       HodoscopeHit* hit = (*hHC16)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(188, hHC16->entries());


    ///Bar16 Energy
    G4int totalBar16Hit = 0;
    G4double totalBar16E = 0.;
    G4double E_1st_hit_Bar16 = 0.;
    G4double T_1st_hit_Bar16 = 0.;
    G4double X_1st_hit_Bar16 = 0.;
    G4double Y_1st_hit_Bar16 = 0.;
    G4double Z_1st_hit_Bar16 = 0.;

    for (G4int i=0;i<n_hit_16;i++)
    {
        HodoscopeHit* hit = (*hHC16)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar16 = (*hHC16)[0]->GetTime();
        E_1st_hit_Bar16 = (*hHC16)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar16 = worldPos.x();
        Y_1st_hit_Bar16 = worldPos.y();
        Z_1st_hit_Bar16 = worldPos.z();
        totalBar16Hit++;
        totalBar16E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(189, totalBar16E/keV);

    ///Bar16, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(190,E_1st_hit_Bar16/keV);

    ///Time 16
    if (T_1st_hit_Bar16 > 0. && T_1st_hit_Bar16 < 2000./ns){
    analysisManager->FillNtupleDColumn(191,T_1st_hit_Bar16/ns);

    ///Reconstructed energy for bar 16
     analysisManager->FillNtupleDColumn(192, 2.7*1.0E+6 / (T_1st_hit_Bar16*T_1st_hit_Bar16));
     }

    ///Bar16, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(193,X_1st_hit_Bar16/cm);
    analysisManager->FillNtupleDColumn(194,Y_1st_hit_Bar16/cm);
    analysisManager->FillNtupleDColumn(195,Z_1st_hit_Bar16/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_16;i++)
    {
        HodoscopeHit* hit = (*hHC16)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar16, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb16px = hSHLDB16PX->entries();///n_hit_sb16px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(196, n_hit_sb16px);

    G4double T_1st_hit_sb16px = 0.;
    for (G4int i=0;i<n_hit_sb16px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB16PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb16px = (*hSHLDB16PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb16px > 0. && T_1st_hit_sb16px < 2000./ns){
    analysisManager->FillNtupleDColumn(197,T_1st_hit_sb16px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar16, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb16nx = hSHLDB16NX->entries();///n_hit_sb16nx is the # of hits in the shield of bar16 in neg X.  
    analysisManager->FillNtupleIColumn(198, n_hit_sb16nx);

    G4double T_1st_hit_sb16nx = 0.;
    for (G4int i=0;i<n_hit_sb16nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB16NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb16nx = (*hSHLDB16NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb16nx > 0. && T_1st_hit_sb16nx < 2000./ns){
     analysisManager->FillNtupleDColumn(199,T_1st_hit_sb16nx/ns);
     }





    ///# of Hits, Bar17
    G4int n_hit_17 = hHC17->entries();

    for (G4int i=0;i<n_hit_17;i++)
    {
       HodoscopeHit* hit = (*hHC17)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(200, hHC17->entries());


    ///Bar17 Energy
    G4int totalBar17Hit = 0;
    G4double totalBar17E = 0.;
    G4double E_1st_hit_Bar17 = 0.;
    G4double T_1st_hit_Bar17 = 0.;
    G4double X_1st_hit_Bar17 = 0.;
    G4double Y_1st_hit_Bar17 = 0.;
    G4double Z_1st_hit_Bar17 = 0.;

    for (G4int i=0;i<n_hit_17;i++)
    {
        HodoscopeHit* hit = (*hHC17)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar17 = (*hHC17)[0]->GetTime();
        E_1st_hit_Bar17 = (*hHC17)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar17 = worldPos.x();
        Y_1st_hit_Bar17 = worldPos.y();
        Z_1st_hit_Bar17 = worldPos.z();
        totalBar17Hit++;
        totalBar17E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(201, totalBar17E/keV);

    ///Bar17, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(202,E_1st_hit_Bar17/keV);

    ///Time 17
    if (T_1st_hit_Bar17 > 0. && T_1st_hit_Bar17 < 2000./ns){
    analysisManager->FillNtupleDColumn(203,T_1st_hit_Bar17/ns);

    ///Reconstructed energy for bar 17
     analysisManager->FillNtupleDColumn(204, 2.7*1.0E+6 / (T_1st_hit_Bar17*T_1st_hit_Bar17));
     }

    ///Bar17, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(205,X_1st_hit_Bar17/cm);
    analysisManager->FillNtupleDColumn(206,Y_1st_hit_Bar17/cm);
    analysisManager->FillNtupleDColumn(207,Z_1st_hit_Bar17/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_17;i++)
    {
        HodoscopeHit* hit = (*hHC17)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar17, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb17px = hSHLDB17PX->entries();///n_hit_sb17px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(208, n_hit_sb17px);

    G4double T_1st_hit_sb17px = 0.;
    for (G4int i=0;i<n_hit_sb17px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB17PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb17px = (*hSHLDB17PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb17px > 0. && T_1st_hit_sb17px < 2000./ns){
    analysisManager->FillNtupleDColumn(209,T_1st_hit_sb17px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar17, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb17nx = hSHLDB17NX->entries();///n_hit_sb17nx is the # of hits in the shield of bar17 in neg X.  
    analysisManager->FillNtupleIColumn(210, n_hit_sb17nx);

    G4double T_1st_hit_sb17nx = 0.;
    for (G4int i=0;i<n_hit_sb17nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB17NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb17nx = (*hSHLDB17NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb17nx > 0. && T_1st_hit_sb17nx < 2000./ns){
     analysisManager->FillNtupleDColumn(211,T_1st_hit_sb17nx/ns);
     }





    ///# of Hits, Bar18
    G4int n_hit_18 = hHC18->entries();

    for (G4int i=0;i<n_hit_18;i++)
    {
       HodoscopeHit* hit = (*hHC18)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(212, hHC18->entries());


    ///Bar18 Energy
    G4int totalBar18Hit = 0;
    G4double totalBar18E = 0.;
    G4double E_1st_hit_Bar18 = 0.;
    G4double T_1st_hit_Bar18 = 0.;
    G4double X_1st_hit_Bar18 = 0.;
    G4double Y_1st_hit_Bar18 = 0.;
    G4double Z_1st_hit_Bar18 = 0.;

    for (G4int i=0;i<n_hit_18;i++)
    {
        HodoscopeHit* hit = (*hHC18)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar18 = (*hHC18)[0]->GetTime();
        E_1st_hit_Bar18 = (*hHC18)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar18 = worldPos.x();
        Y_1st_hit_Bar18 = worldPos.y();
        Z_1st_hit_Bar18 = worldPos.z();
        totalBar18Hit++;
        totalBar18E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(213, totalBar18E/keV);

    ///Bar18, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(214,E_1st_hit_Bar18/keV);

    ///Time 18
    if (T_1st_hit_Bar18 > 0. && T_1st_hit_Bar18 < 2000./ns){
    analysisManager->FillNtupleDColumn(215,T_1st_hit_Bar18/ns);

    ///Reconstructed energy for bar 18
     analysisManager->FillNtupleDColumn(216, 2.7*1.0E+6 / (T_1st_hit_Bar18*T_1st_hit_Bar18));
     }

    ///Bar18, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(217,X_1st_hit_Bar18/cm);
    analysisManager->FillNtupleDColumn(218,Y_1st_hit_Bar18/cm);
    analysisManager->FillNtupleDColumn(219,Z_1st_hit_Bar18/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_18;i++)
    {
        HodoscopeHit* hit = (*hHC18)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar18, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb18px = hSHLDB18PX->entries();///n_hit_sb18px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(220, n_hit_sb18px);

    G4double T_1st_hit_sb18px = 0.;
    for (G4int i=0;i<n_hit_sb18px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB18PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb18px = (*hSHLDB18PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb18px > 0. && T_1st_hit_sb18px < 2000./ns){
    analysisManager->FillNtupleDColumn(221,T_1st_hit_sb18px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar18, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb18nx = hSHLDB18NX->entries();///n_hit_sb18nx is the # of hits in the shield of bar18 in neg X.  
    analysisManager->FillNtupleIColumn(222, n_hit_sb18nx);

    G4double T_1st_hit_sb18nx = 0.;
    for (G4int i=0;i<n_hit_sb18nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB18NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb18nx = (*hSHLDB18NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb18nx > 0. && T_1st_hit_sb18nx < 2000./ns){
     analysisManager->FillNtupleDColumn(223,T_1st_hit_sb18nx/ns);
     }





    ///# of Hits, Bar19
    G4int n_hit_19 = hHC19->entries();

    for (G4int i=0;i<n_hit_19;i++)
    {
       HodoscopeHit* hit = (*hHC19)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(224, hHC19->entries());


    ///Bar19 Energy
    G4int totalBar19Hit = 0;
    G4double totalBar19E = 0.;
    G4double E_1st_hit_Bar19 = 0.;
    G4double T_1st_hit_Bar19 = 0.;
    G4double X_1st_hit_Bar19 = 0.;
    G4double Y_1st_hit_Bar19 = 0.;
    G4double Z_1st_hit_Bar19 = 0.;

    for (G4int i=0;i<n_hit_19;i++)
    {
        HodoscopeHit* hit = (*hHC19)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar19 = (*hHC19)[0]->GetTime();
        E_1st_hit_Bar19 = (*hHC19)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar19 = worldPos.x();
        Y_1st_hit_Bar19 = worldPos.y();
        Z_1st_hit_Bar19 = worldPos.z();
        totalBar19Hit++;
        totalBar19E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(225, totalBar19E/keV);

    ///Bar19, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(226,E_1st_hit_Bar19/keV);

    ///Time 19
    if (T_1st_hit_Bar19 > 0. && T_1st_hit_Bar19 < 2000./ns){
    analysisManager->FillNtupleDColumn(227,T_1st_hit_Bar19/ns);

    ///Reconstructed energy for bar 19
     analysisManager->FillNtupleDColumn(228, 2.7*1.0E+6 / (T_1st_hit_Bar19*T_1st_hit_Bar19));
     }

    ///Bar19, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(229,X_1st_hit_Bar19/cm);
    analysisManager->FillNtupleDColumn(230,Y_1st_hit_Bar19/cm);
    analysisManager->FillNtupleDColumn(231,Z_1st_hit_Bar19/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_19;i++)
    {
        HodoscopeHit* hit = (*hHC19)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar19, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb19px = hSHLDB19PX->entries();///n_hit_sb19px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(232, n_hit_sb19px);

    G4double T_1st_hit_sb19px = 0.;
    for (G4int i=0;i<n_hit_sb19px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB19PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb19px = (*hSHLDB19PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb19px > 0. && T_1st_hit_sb19px < 2000./ns){
    analysisManager->FillNtupleDColumn(233,T_1st_hit_sb19px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar19, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb19nx = hSHLDB19NX->entries();///n_hit_sb19nx is the # of hits in the shield of bar19 in neg X.  
    analysisManager->FillNtupleIColumn(234, n_hit_sb19nx);

    G4double T_1st_hit_sb19nx = 0.;
    for (G4int i=0;i<n_hit_sb19nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB19NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb19nx = (*hSHLDB19NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb19nx > 0. && T_1st_hit_sb19nx < 2000./ns){
     analysisManager->FillNtupleDColumn(235,T_1st_hit_sb19nx/ns);
     }





    ///# of Hits, Bar20
    G4int n_hit_20 = hHC20->entries();

    for (G4int i=0;i<n_hit_20;i++)
    {
       HodoscopeHit* hit = (*hHC20)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(236, hHC20->entries());


    ///Bar20 Energy
    G4int totalBar20Hit = 0;
    G4double totalBar20E = 0.;
    G4double E_1st_hit_Bar20 = 0.;
    G4double T_1st_hit_Bar20 = 0.;
    G4double X_1st_hit_Bar20 = 0.;
    G4double Y_1st_hit_Bar20 = 0.;
    G4double Z_1st_hit_Bar20 = 0.;

    for (G4int i=0;i<n_hit_20;i++)
    {
        HodoscopeHit* hit = (*hHC20)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar20 = (*hHC20)[0]->GetTime();
        E_1st_hit_Bar20 = (*hHC20)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar20 = worldPos.x();
        Y_1st_hit_Bar20 = worldPos.y();
        Z_1st_hit_Bar20 = worldPos.z();
        totalBar20Hit++;
        totalBar20E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(237, totalBar20E/keV);

    ///Bar20, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(238,E_1st_hit_Bar20/keV);

    ///Time 20
    if (T_1st_hit_Bar20 > 0. && T_1st_hit_Bar20 < 2000./ns){
    analysisManager->FillNtupleDColumn(239,T_1st_hit_Bar20/ns);

    ///Reconstructed energy for bar 20
     analysisManager->FillNtupleDColumn(240, 2.7*1.0E+6 / (T_1st_hit_Bar20*T_1st_hit_Bar20));
     }

    ///Bar20, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(241,X_1st_hit_Bar20/cm);
    analysisManager->FillNtupleDColumn(242,Y_1st_hit_Bar20/cm);
    analysisManager->FillNtupleDColumn(243,Z_1st_hit_Bar20/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_20;i++)
    {
        HodoscopeHit* hit = (*hHC20)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar20, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb20px = hSHLDB20PX->entries();///n_hit_sb20px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(244, n_hit_sb20px);

    G4double T_1st_hit_sb20px = 0.;
    for (G4int i=0;i<n_hit_sb20px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB20PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb20px = (*hSHLDB20PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb20px > 0. && T_1st_hit_sb20px < 2000./ns){
    analysisManager->FillNtupleDColumn(245,T_1st_hit_sb20px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar20, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb20nx = hSHLDB20NX->entries();///n_hit_sb20nx is the # of hits in the shield of bar20 in neg X.  
    analysisManager->FillNtupleIColumn(246, n_hit_sb20nx);

    G4double T_1st_hit_sb20nx = 0.;
    for (G4int i=0;i<n_hit_sb20nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB20NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb20nx = (*hSHLDB20NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb20nx > 0. && T_1st_hit_sb20nx < 2000./ns){
     analysisManager->FillNtupleDColumn(247,T_1st_hit_sb20nx/ns);
     }





    ///# of Hits, Bar21
    G4int n_hit_21 = hHC21->entries();

    for (G4int i=0;i<n_hit_21;i++)
    {
       HodoscopeHit* hit = (*hHC21)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(248, hHC21->entries());


    ///Bar21 Energy
    G4int totalBar21Hit = 0;
    G4double totalBar21E = 0.;
    G4double E_1st_hit_Bar21 = 0.;
    G4double T_1st_hit_Bar21 = 0.;
    G4double X_1st_hit_Bar21 = 0.;
    G4double Y_1st_hit_Bar21 = 0.;
    G4double Z_1st_hit_Bar21 = 0.;

    for (G4int i=0;i<n_hit_21;i++)
    {
        HodoscopeHit* hit = (*hHC21)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar21 = (*hHC21)[0]->GetTime();
        E_1st_hit_Bar21 = (*hHC21)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar21 = worldPos.x();
        Y_1st_hit_Bar21 = worldPos.y();
        Z_1st_hit_Bar21 = worldPos.z();
        totalBar21Hit++;
        totalBar21E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(249, totalBar21E/keV);

    ///Bar21, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(250,E_1st_hit_Bar21/keV);

    ///Time 21
    if (T_1st_hit_Bar21 > 0. && T_1st_hit_Bar21 < 2000./ns){
    analysisManager->FillNtupleDColumn(251,T_1st_hit_Bar21/ns);

    ///Reconstructed energy for bar 21
     analysisManager->FillNtupleDColumn(252, 2.7*1.0E+6 / (T_1st_hit_Bar21*T_1st_hit_Bar21));
     }

    ///Bar21, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(253,X_1st_hit_Bar21/cm);
    analysisManager->FillNtupleDColumn(254,Y_1st_hit_Bar21/cm);
    analysisManager->FillNtupleDColumn(255,Z_1st_hit_Bar21/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_21;i++)
    {
        HodoscopeHit* hit = (*hHC21)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar21, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb21px = hSHLDB21PX->entries();///n_hit_sb21px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(256, n_hit_sb21px);

    G4double T_1st_hit_sb21px = 0.;
    for (G4int i=0;i<n_hit_sb21px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB21PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb21px = (*hSHLDB21PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb21px > 0. && T_1st_hit_sb21px < 2000./ns){
    analysisManager->FillNtupleDColumn(257,T_1st_hit_sb21px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar21, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb21nx = hSHLDB21NX->entries();///n_hit_sb21nx is the # of hits in the shield of bar21 in neg X.  
    analysisManager->FillNtupleIColumn(258, n_hit_sb21nx);

    G4double T_1st_hit_sb21nx = 0.;
    for (G4int i=0;i<n_hit_sb21nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB21NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb21nx = (*hSHLDB21NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb21nx > 0. && T_1st_hit_sb21nx < 2000./ns){
     analysisManager->FillNtupleDColumn(259,T_1st_hit_sb21nx/ns);
     }





    ///# of Hits, Bar22
    G4int n_hit_22 = hHC22->entries();

    for (G4int i=0;i<n_hit_22;i++)
    {
       HodoscopeHit* hit = (*hHC22)[i];
       G4ThreeVector Pos = hit->GetPos();
    }

    analysisManager->FillNtupleIColumn(260, hHC22->entries());


    ///Bar22 Energy
    G4int totalBar22Hit = 0;
    G4double totalBar22E = 0.;
    G4double E_1st_hit_Bar22 = 0.;
    G4double T_1st_hit_Bar22 = 0.;
    G4double X_1st_hit_Bar22 = 0.;
    G4double Y_1st_hit_Bar22 = 0.;
    G4double Z_1st_hit_Bar22 = 0.;

    for (G4int i=0;i<n_hit_22;i++)
    {
        HodoscopeHit* hit = (*hHC22)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar22 = (*hHC22)[0]->GetTime();
        E_1st_hit_Bar22 = (*hHC22)[0]->GetEdep();
        G4ThreeVector worldPos = hit->GetWorldPos();
        X_1st_hit_Bar22 = worldPos.x();
        Y_1st_hit_Bar22 = worldPos.y();
        Z_1st_hit_Bar22 = worldPos.z();
        totalBar22Hit++;
        totalBar22E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(261, totalBar22E/keV);

    ///Bar22, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(262,E_1st_hit_Bar22/keV);

    ///Time 22
    if (T_1st_hit_Bar22 > 0. && T_1st_hit_Bar22 < 2000./ns){
    analysisManager->FillNtupleDColumn(263,T_1st_hit_Bar22/ns);

    ///Reconstructed energy for bar 22
     analysisManager->FillNtupleDColumn(264, 2.7*1.0E+6 / (T_1st_hit_Bar22*T_1st_hit_Bar22));
     }

    ///Bar22, Hit position X,Y,Z
    analysisManager->FillNtupleDColumn(265,X_1st_hit_Bar22/cm);
    analysisManager->FillNtupleDColumn(266,Y_1st_hit_Bar22/cm);
    analysisManager->FillNtupleDColumn(267,Z_1st_hit_Bar22/cm);


    ///Print on screen
    for (G4int i=0;i<n_hit_22;i++)
    {
        HodoscopeHit* hit = (*hHC22)[i];
        hit->Print();
    }


    /// ~~~~~~ Shield of PMT, Bar22, positive X direction. ~~~~~~
    ///# of hits,  
    G4int n_hit_sb22px = hSHLDB22PX->entries();///n_hit_sb22px is the # of hits per incident particle in shield.  
    analysisManager->FillNtupleIColumn(268, n_hit_sb22px);

    G4double T_1st_hit_sb22px = 0.;
    for (G4int i=0;i<n_hit_sb22px;i++)
    {
        PmtshieldHit* hit = (*hSHLDB22PX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb22px = (*hSHLDB22PX)[0]->GetTime();
        }
    }

    ///Time recorded in Shield of PMT
    if (T_1st_hit_sb22px > 0. && T_1st_hit_sb22px < 2000./ns){
    analysisManager->FillNtupleDColumn(269,T_1st_hit_sb22px/ns);
    }

    /// ~~~~~~ Shield of PMT, Bar22, negative X direction. ~~~~~~
    /// # of Hits 
    G4int n_hit_sb22nx = hSHLDB22NX->entries();///n_hit_sb22nx is the # of hits in the shield of bar22 in neg X.  
    analysisManager->FillNtupleIColumn(270, n_hit_sb22nx);

    G4double T_1st_hit_sb22nx = 0.;
    for (G4int i=0;i<n_hit_sb22nx;i++)
    {
        PmtshieldHit* hit = (*hSHLDB22NX)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_sb22nx = (*hSHLDB22NX)[0]->GetTime();
        }
    }

    /// Time recorded in Shield of PMT
     if (T_1st_hit_sb22nx > 0. && T_1st_hit_sb22nx < 2000./ns){
     analysisManager->FillNtupleDColumn(271,T_1st_hit_sb22nx/ns);
     }



    analysisManager->AddNtupleRow();

   
    // Print diagnostics
    
    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
    
    G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    
    G4cout << G4endl
           << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
           << primary->GetG4code()->GetParticleName()
           << " " << primary->GetMomentum() << G4endl;
      

}

