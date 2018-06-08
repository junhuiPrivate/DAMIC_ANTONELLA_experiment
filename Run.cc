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

#include "Run.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "HodoscopeHit.hh"
#include "HodoscopeSD.hh"
///#include "HadCalorimeterHit.hh"
///#include "EmCalorimeterHit.hh"


Run::Run() :
    G4Run(),
    ///em_ene(0);
    ///had_ene(0);
    bar1_ene(0),
    bar2_ene(0),
    ///shower_shape(0),
    ///ECHCID(-1);
    ///HCHCID(-1);    
    BAR1HCID(-1), ///Bar 1 Hit counter ID
    BAR2HCID(-1),
    HCLMID(-1)
{ }


//=================================
// Exercise 1 Step 2:
// Get the hits collection from the event
// For the EM and HAD calorimeter sensitive detectors
// Accumulate on them
// Do not forget to forward the call to the base class RecordEvent
// method

void Run::RecordEvent(const G4Event* evt)
{
    //Forward call to base class
    G4Run::RecordEvent(evt);

    if ( BAR1HCID == -1 || BAR2HCID == -1) {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      BAR1HCID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      BAR2HCID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
      HCLMID = sdManager->GetCollectionID("collimator/hodoscopeColl");
    }
    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;
  
    }


    ///const EmCalorimeterHitsCollection* emHC =
    ///    static_cast<const EmCalorimeterHitsCollection*>(hce->GetHC(BAR1HCID));
    ///const HadCalorimeterHitsCollection* hadHC =
    ///    static_cast<const HadCalorimeterHitsCollection*>(hce->GetHC(BAR2HCID));
    ///if ( !emHC || !hadHC )
    const HodoscopeHitsCollection* Bar1HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR1HCID));
    const HodoscopeHitsCollection* Bar2HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR2HCID));
    if ( !Bar1HC || !Bar2HC )
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;

    }
    ///G4double em = 0;
    ///G4double had = 0;
    G4double e_bar1 = 0;
    G4double e_bar2 = 0;
    for (size_t i=0;i<Bar1HC->GetSize();i++)
    {
        ///EmCalorimeterHit* hit = (*emHC)[i];
        HodoscopeHit* hit = (*Bar1HC)[i];
        e_bar1 += hit->GetEdep();
    }
    for (size_t i=0;i<Bar2HC->GetSize();i++)
    {
        ///HadCalorimeterHit* hit = (*hadHC)[i];
        HodoscopeHit* hit = (*Bar2HC)[i];
        e_bar2 += hit->GetEdep();
    }
    bar2_ene += e_bar2;
    bar1_ene += e_bar1; 

    ///if ( had+em > 0 )
        ///shower_shape += ( em/(had+em) );
}

//=================================
// Exercise 1 Step 3:
// Implement a Merge method.
// The meaning of this will become clear
// When Multi-threading is discussed.
// This method of a MASTER instance is called
// By all worker threads passing WORKER run as
// parameter. Get the energy from WORKER run and
// Accumulate in the MASTER
// Do not forget to forward the call to the base class
// method to accumulate the number of processed events!

/*
void Run::Merge(const G4Run* aRun)
{
    const Run* localRun = static_cast<const Run*>(aRun);
    bar1_ene += localRun->GetBar1Energy();
    bar2_ene += localRun->GetBar2Energy();
    ///shower_shape += localRun->GetShowerShape();
    //Forward call to base-class
    G4Run::Merge(localRun);
}
*/


