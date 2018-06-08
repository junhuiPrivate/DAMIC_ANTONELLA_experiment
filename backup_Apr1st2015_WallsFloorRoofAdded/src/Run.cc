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
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "HodoscopeHit.hh"
#include "HodoscopeSD.hh"
#include "CollimatorHit.hh"
#include "CollimatorSD.hh"
#include "PmtshieldHit.hh"
#include "PmtshieldSD.hh"
#include "SddHit.hh"
#include "SddSD.hh"
///#include "HadCalorimeterHit.hh"
///#include "EmCalorimeterHit.hh"


Run::Run() :
    G4Run(),
    sdd_ene(0),

    bar1_ene(0),
    bar2_ene(0),
    bar3_ene(0),
    bar4_ene(0),
    bar5_ene(0),
    bar6_ene(0),
    bar7_ene(0),
    bar8_ene(0),
    bar9_ene(0),
    bar10_ene(0),
    bar11_ene(0),
    bar12_ene(0),
    bar13_ene(0),
    bar14_ene(0),
    bar15_ene(0),
    bar16_ene(0),
    bar17_ene(0),
    bar18_ene(0),
    bar19_ene(0),
    bar20_ene(0),
    bar21_ene(0),
    bar22_ene(0),

    SDDHCID(-1), ///Sdd Hit counter ID

    BAR1HCID(-1),
    BAR2HCID(-1),
    BAR3HCID(-1),
    BAR4HCID(-1),
    BAR5HCID(-1),
    BAR6HCID(-1),
    BAR7HCID(-1),
    BAR8HCID(-1),
    BAR9HCID(-1),
    BAR10HCID(-1),
    BAR11HCID(-1),
    BAR12HCID(-1),
    BAR13HCID(-1),
    BAR14HCID(-1),
    BAR15HCID(-1),
    BAR16HCID(-1),
    BAR17HCID(-1),
    BAR18HCID(-1),
    BAR19HCID(-1),
    BAR20HCID(-1),
    BAR21HCID(-1),
    BAR22HCID(-1),


    CLMHCID(-1),

    SHLDB1PXHCID (-1), ///shield Bar_1 Positive X direction Hit counter ID
    SHLDB1NXHCID (-1), ///shield Bar_1 negative X direction Hit counter ID
    SHLDB2PXHCID (-1), ///shield Bar_2 Positive X direction Hit counter ID
    SHLDB2NXHCID (-1), ///shield Bar_2 negative X direction Hit counter ID
    SHLDB3PXHCID (-1), ///shield Bar_3 Positive X direction Hit counter ID
    SHLDB3NXHCID (-1), ///shield Bar_3 negative X direction Hit counter ID
    SHLDB4PXHCID (-1), 
    SHLDB4NXHCID (-1), 
    SHLDB5PXHCID (-1), 
    SHLDB5NXHCID (-1), 
    SHLDB6PXHCID (-1), 
    SHLDB6NXHCID (-1), 
    SHLDB7PXHCID (-1), 
    SHLDB7NXHCID (-1), 
    SHLDB8PXHCID (-1), 
    SHLDB8NXHCID (-1), 
    SHLDB9PXHCID (-1), 
    SHLDB9NXHCID (-1), 
    SHLDB10PXHCID (-1), 
    SHLDB10NXHCID (-1), 
    SHLDB11PXHCID (-1), 
    SHLDB11NXHCID (-1), 
    SHLDB12PXHCID (-1), 
    SHLDB12NXHCID (-1), 
    SHLDB13PXHCID (-1), 
    SHLDB13NXHCID (-1), 
    SHLDB14PXHCID (-1), 
    SHLDB14NXHCID (-1), 
    SHLDB15PXHCID (-1), 
    SHLDB15NXHCID (-1), 
    SHLDB16PXHCID (-1), 
    SHLDB16NXHCID (-1), 
    SHLDB17PXHCID (-1), 
    SHLDB17NXHCID (-1), 
    SHLDB18PXHCID (-1), 
    SHLDB18NXHCID (-1), 
    SHLDB19PXHCID (-1), 
    SHLDB19NXHCID (-1), 
    SHLDB20PXHCID (-1), 
    SHLDB20NXHCID (-1), 
    SHLDB21PXHCID (-1), 
    SHLDB21NXHCID (-1), 
    SHLDB22PXHCID (-1), 
    SHLDB22NXHCID (-1) 
{ }



void Run::RecordEvent(const G4Event* evt)
{
    //Forward call to base class
    G4Run::RecordEvent(evt);

    if (SDDHCID == -1 || CLMHCID == -1 || BAR1HCID == -1 || BAR2HCID == -1 || BAR3HCID == -1 ||
        BAR4HCID == -1 || BAR5HCID == -1 || BAR6HCID == -1 || BAR7HCID == -1 || BAR8HCID == -1 || 
        BAR9HCID == -1 || BAR10HCID == -1 || BAR11HCID == -1 || BAR12HCID == -1 || BAR13HCID == -1 || 
        BAR14HCID == -1 || BAR15HCID == -1 || BAR16HCID == -1 || BAR17HCID == -1 || BAR18HCID == -1 || 
        BAR19HCID == -1 || BAR20HCID == -1 || BAR21HCID == -1 || BAR22HCID == -1 || 
        SHLDB1PXHCID == -1 ||SHLDB1NXHCID == -1 || SHLDB2PXHCID == -1 ||SHLDB2NXHCID == -1 ||
        SHLDB3PXHCID == -1 ||SHLDB3NXHCID == -1 || SHLDB4PXHCID == -1 ||SHLDB4NXHCID == -1 ||
        SHLDB5PXHCID == -1 ||SHLDB5NXHCID == -1 || SHLDB6PXHCID == -1 ||SHLDB6NXHCID == -1 ||
        SHLDB7PXHCID == -1 ||SHLDB7NXHCID == -1 || SHLDB8PXHCID == -1 ||SHLDB8NXHCID == -1 ||
        SHLDB9PXHCID == -1 ||SHLDB9NXHCID == -1 || SHLDB10PXHCID == -1 ||SHLDB10NXHCID == -1 ||
        SHLDB11PXHCID == -1 ||SHLDB11NXHCID == -1 || SHLDB12PXHCID == -1 ||SHLDB12NXHCID == -1 ||
        SHLDB13PXHCID == -1 ||SHLDB13NXHCID == -1 || SHLDB14PXHCID == -1 ||SHLDB14NXHCID == -1 ||
        SHLDB15PXHCID == -1 ||SHLDB15NXHCID == -1 || SHLDB16PXHCID == -1 ||SHLDB16NXHCID == -1 ||
        SHLDB17PXHCID == -1 ||SHLDB17NXHCID == -1 || SHLDB18PXHCID == -1 ||SHLDB18NXHCID == -1 ||
        SHLDB19PXHCID == -1 ||SHLDB19NXHCID == -1 || SHLDB20PXHCID == -1 ||SHLDB20NXHCID == -1 ||
        SHLDB21PXHCID == -1 ||SHLDB21NXHCID == -1 || SHLDB22PXHCID == -1 ||SHLDB22NXHCID == -1 
       ) {

      G4SDManager* sdManager = G4SDManager::GetSDMpointer();

      SDDHCID = sdManager->GetCollectionID("sdd/sddColl");
      CLMHCID = sdManager->GetCollectionID("collimator/collimatorColl");

      BAR1HCID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      BAR2HCID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
      BAR3HCID = sdManager->GetCollectionID("hodoscope3/hodoscopeColl");
      ///place_BARHCID
      BAR4HCID = sdManager->GetCollectionID("hodoscope4/hodoscopeColl");
      BAR5HCID = sdManager->GetCollectionID("hodoscope5/hodoscopeColl");
      BAR6HCID = sdManager->GetCollectionID("hodoscope6/hodoscopeColl");
      BAR7HCID = sdManager->GetCollectionID("hodoscope7/hodoscopeColl");
      BAR8HCID = sdManager->GetCollectionID("hodoscope8/hodoscopeColl");
      BAR9HCID = sdManager->GetCollectionID("hodoscope9/hodoscopeColl");
      BAR10HCID = sdManager->GetCollectionID("hodoscope10/hodoscopeColl");
      BAR11HCID = sdManager->GetCollectionID("hodoscope11/hodoscopeColl");
      BAR12HCID = sdManager->GetCollectionID("hodoscope12/hodoscopeColl");
      BAR13HCID = sdManager->GetCollectionID("hodoscope13/hodoscopeColl");
      BAR14HCID = sdManager->GetCollectionID("hodoscope14/hodoscopeColl");
      BAR15HCID = sdManager->GetCollectionID("hodoscope15/hodoscopeColl");
      BAR16HCID = sdManager->GetCollectionID("hodoscope16/hodoscopeColl");
      BAR17HCID = sdManager->GetCollectionID("hodoscope17/hodoscopeColl");
      BAR18HCID = sdManager->GetCollectionID("hodoscope18/hodoscopeColl");
      BAR19HCID = sdManager->GetCollectionID("hodoscope19/hodoscopeColl");
      BAR20HCID = sdManager->GetCollectionID("hodoscope20/hodoscopeColl");
      BAR21HCID = sdManager->GetCollectionID("hodoscope21/hodoscopeColl");
      BAR22HCID = sdManager->GetCollectionID("hodoscope22/hodoscopeColl");

    ///shield in bar_1
      SHLDB1PXHCID = sdManager->GetCollectionID("pmtshieldb1px/pmtshieldColl");
      SHLDB1NXHCID = sdManager->GetCollectionID("pmtshieldb1nx/pmtshieldColl");
    ///shield in bar_2
      SHLDB2PXHCID = sdManager->GetCollectionID("pmtshieldb2px/pmtshieldColl");
      SHLDB2NXHCID = sdManager->GetCollectionID("pmtshieldb2nx/pmtshieldColl");
    ///shield in bar_3
      SHLDB3PXHCID = sdManager->GetCollectionID("pmtshieldb3px/pmtshieldColl");
      SHLDB3NXHCID = sdManager->GetCollectionID("pmtshieldb3nx/pmtshieldColl");
      ///place_SHLDBHCID
    ///shield in bar_4
      SHLDB4PXHCID = sdManager->GetCollectionID("pmtshieldb4px/pmtshieldColl");
      SHLDB4NXHCID = sdManager->GetCollectionID("pmtshieldb4nx/pmtshieldColl");

    ///shield in bar_5
      SHLDB5PXHCID = sdManager->GetCollectionID("pmtshieldb5px/pmtshieldColl");
      SHLDB5NXHCID = sdManager->GetCollectionID("pmtshieldb5nx/pmtshieldColl");

    ///shield in bar_6
      SHLDB6PXHCID = sdManager->GetCollectionID("pmtshieldb6px/pmtshieldColl");
      SHLDB6NXHCID = sdManager->GetCollectionID("pmtshieldb6nx/pmtshieldColl");

    ///shield in bar_7
      SHLDB7PXHCID = sdManager->GetCollectionID("pmtshieldb7px/pmtshieldColl");
      SHLDB7NXHCID = sdManager->GetCollectionID("pmtshieldb7nx/pmtshieldColl");

    ///shield in bar_8
      SHLDB8PXHCID = sdManager->GetCollectionID("pmtshieldb8px/pmtshieldColl");
      SHLDB8NXHCID = sdManager->GetCollectionID("pmtshieldb8nx/pmtshieldColl");

    ///shield in bar_9
      SHLDB9PXHCID = sdManager->GetCollectionID("pmtshieldb9px/pmtshieldColl");
      SHLDB9NXHCID = sdManager->GetCollectionID("pmtshieldb9nx/pmtshieldColl");

    ///shield in bar_10
      SHLDB10PXHCID = sdManager->GetCollectionID("pmtshieldb10px/pmtshieldColl");
      SHLDB10NXHCID = sdManager->GetCollectionID("pmtshieldb10nx/pmtshieldColl");

    ///shield in bar_11
      SHLDB11PXHCID = sdManager->GetCollectionID("pmtshieldb11px/pmtshieldColl");
      SHLDB11NXHCID = sdManager->GetCollectionID("pmtshieldb11nx/pmtshieldColl");

    ///shield in bar_12
      SHLDB12PXHCID = sdManager->GetCollectionID("pmtshieldb12px/pmtshieldColl");
      SHLDB12NXHCID = sdManager->GetCollectionID("pmtshieldb12nx/pmtshieldColl");

    ///shield in bar_13
      SHLDB13PXHCID = sdManager->GetCollectionID("pmtshieldb13px/pmtshieldColl");
      SHLDB13NXHCID = sdManager->GetCollectionID("pmtshieldb13nx/pmtshieldColl");

    ///shield in bar_14
      SHLDB14PXHCID = sdManager->GetCollectionID("pmtshieldb14px/pmtshieldColl");
      SHLDB14NXHCID = sdManager->GetCollectionID("pmtshieldb14nx/pmtshieldColl");

    ///shield in bar_15
      SHLDB15PXHCID = sdManager->GetCollectionID("pmtshieldb15px/pmtshieldColl");
      SHLDB15NXHCID = sdManager->GetCollectionID("pmtshieldb15nx/pmtshieldColl");

    ///shield in bar_16
      SHLDB16PXHCID = sdManager->GetCollectionID("pmtshieldb16px/pmtshieldColl");
      SHLDB16NXHCID = sdManager->GetCollectionID("pmtshieldb16nx/pmtshieldColl");

    ///shield in bar_17
      SHLDB17PXHCID = sdManager->GetCollectionID("pmtshieldb17px/pmtshieldColl");
      SHLDB17NXHCID = sdManager->GetCollectionID("pmtshieldb17nx/pmtshieldColl");

    ///shield in bar_18
      SHLDB18PXHCID = sdManager->GetCollectionID("pmtshieldb18px/pmtshieldColl");
      SHLDB18NXHCID = sdManager->GetCollectionID("pmtshieldb18nx/pmtshieldColl");

    ///shield in bar_19
      SHLDB19PXHCID = sdManager->GetCollectionID("pmtshieldb19px/pmtshieldColl");
      SHLDB19NXHCID = sdManager->GetCollectionID("pmtshieldb19nx/pmtshieldColl");

    ///shield in bar_20
      SHLDB20PXHCID = sdManager->GetCollectionID("pmtshieldb20px/pmtshieldColl");
      SHLDB20NXHCID = sdManager->GetCollectionID("pmtshieldb20nx/pmtshieldColl");

    ///shield in bar_21
      SHLDB21PXHCID = sdManager->GetCollectionID("pmtshieldb21px/pmtshieldColl");
      SHLDB21NXHCID = sdManager->GetCollectionID("pmtshieldb21nx/pmtshieldColl");

    ///shield in bar_22
      SHLDB22PXHCID = sdManager->GetCollectionID("pmtshieldb22px/pmtshieldColl");
      SHLDB22NXHCID = sdManager->GetCollectionID("pmtshieldb22nx/pmtshieldColl");



    }
    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;
  
    }


    ///sdd
    const SddHitsCollection* SddHC =
        static_cast<const SddHitsCollection*>(hce->GetHC(SDDHCID));
    ///collimator
    const CollimatorHitsCollection* CHC =
        static_cast<const CollimatorHitsCollection*>(hce->GetHC(CLMHCID));
    ///bar_1
    const HodoscopeHitsCollection* Bar1HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR1HCID));
    ///bar_2
    const HodoscopeHitsCollection* Bar2HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR2HCID));
    ///bar_3
    const HodoscopeHitsCollection* Bar3HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR3HCID));
      ///place_BARHCNoID
    ///bar_4
    const HodoscopeHitsCollection* Bar4HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR4HCID));

    ///bar_5
    const HodoscopeHitsCollection* Bar5HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR5HCID));

    ///bar_6
    const HodoscopeHitsCollection* Bar6HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR6HCID));

    ///bar_7
    const HodoscopeHitsCollection* Bar7HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR7HCID));

    ///bar_8
    const HodoscopeHitsCollection* Bar8HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR8HCID));

    ///bar_9
    const HodoscopeHitsCollection* Bar9HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR9HCID));

    ///bar_10
    const HodoscopeHitsCollection* Bar10HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR10HCID));

    ///bar_11
    const HodoscopeHitsCollection* Bar11HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR11HCID));

    ///bar_12
    const HodoscopeHitsCollection* Bar12HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR12HCID));

    ///bar_13
    const HodoscopeHitsCollection* Bar13HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR13HCID));

    ///bar_14
    const HodoscopeHitsCollection* Bar14HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR14HCID));

    ///bar_15
    const HodoscopeHitsCollection* Bar15HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR15HCID));

    ///bar_16
    const HodoscopeHitsCollection* Bar16HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR16HCID));

    ///bar_17
    const HodoscopeHitsCollection* Bar17HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR17HCID));

    ///bar_18
    const HodoscopeHitsCollection* Bar18HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR18HCID));

    ///bar_19
    const HodoscopeHitsCollection* Bar19HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR19HCID));

    ///bar_20
    const HodoscopeHitsCollection* Bar20HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR20HCID));

    ///bar_21
    const HodoscopeHitsCollection* Bar21HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR21HCID));

    ///bar_22
    const HodoscopeHitsCollection* Bar22HC =
        static_cast<const HodoscopeHitsCollection*>(hce->GetHC(BAR22HCID));



    ///shield in bar_1
    const PmtshieldHitsCollection* SHLDB1PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB1PXHCID));
    const PmtshieldHitsCollection* SHLDB1NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB1NXHCID));
    ///shield in bar_2
    const PmtshieldHitsCollection* SHLDB2PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB2PXHCID));
    const PmtshieldHitsCollection* SHLDB2NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB2NXHCID));
    ///shield in bar_3
    const PmtshieldHitsCollection* SHLDB3PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB3PXHCID));
    const PmtshieldHitsCollection* SHLDB3NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB3NXHCID));
      ///place_SHLDBHCNoID
    ///shield in bar_4
    const PmtshieldHitsCollection* SHLDB4PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB4PXHCID));
    const PmtshieldHitsCollection* SHLDB4NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB4NXHCID));

    ///shield in bar_5
    const PmtshieldHitsCollection* SHLDB5PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB5PXHCID));
    const PmtshieldHitsCollection* SHLDB5NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB5NXHCID));

    ///shield in bar_6
    const PmtshieldHitsCollection* SHLDB6PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB6PXHCID));
    const PmtshieldHitsCollection* SHLDB6NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB6NXHCID));

    ///shield in bar_7
    const PmtshieldHitsCollection* SHLDB7PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB7PXHCID));
    const PmtshieldHitsCollection* SHLDB7NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB7NXHCID));

    ///shield in bar_8
    const PmtshieldHitsCollection* SHLDB8PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB8PXHCID));
    const PmtshieldHitsCollection* SHLDB8NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB8NXHCID));

    ///shield in bar_9
    const PmtshieldHitsCollection* SHLDB9PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB9PXHCID));
    const PmtshieldHitsCollection* SHLDB9NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB9NXHCID));

    ///shield in bar_10
    const PmtshieldHitsCollection* SHLDB10PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB10PXHCID));
    const PmtshieldHitsCollection* SHLDB10NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB10NXHCID));

    ///shield in bar_11
    const PmtshieldHitsCollection* SHLDB11PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB11PXHCID));
    const PmtshieldHitsCollection* SHLDB11NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB11NXHCID));

    ///shield in bar_12
    const PmtshieldHitsCollection* SHLDB12PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB12PXHCID));
    const PmtshieldHitsCollection* SHLDB12NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB12NXHCID));

    ///shield in bar_13
    const PmtshieldHitsCollection* SHLDB13PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB13PXHCID));
    const PmtshieldHitsCollection* SHLDB13NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB13NXHCID));

    ///shield in bar_14
    const PmtshieldHitsCollection* SHLDB14PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB14PXHCID));
    const PmtshieldHitsCollection* SHLDB14NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB14NXHCID));

    ///shield in bar_15
    const PmtshieldHitsCollection* SHLDB15PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB15PXHCID));
    const PmtshieldHitsCollection* SHLDB15NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB15NXHCID));

    ///shield in bar_16
    const PmtshieldHitsCollection* SHLDB16PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB16PXHCID));
    const PmtshieldHitsCollection* SHLDB16NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB16NXHCID));

    ///shield in bar_17
    const PmtshieldHitsCollection* SHLDB17PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB17PXHCID));
    const PmtshieldHitsCollection* SHLDB17NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB17NXHCID));

    ///shield in bar_18
    const PmtshieldHitsCollection* SHLDB18PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB18PXHCID));
    const PmtshieldHitsCollection* SHLDB18NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB18NXHCID));

    ///shield in bar_19
    const PmtshieldHitsCollection* SHLDB19PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB19PXHCID));
    const PmtshieldHitsCollection* SHLDB19NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB19NXHCID));

    ///shield in bar_20
    const PmtshieldHitsCollection* SHLDB20PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB20PXHCID));
    const PmtshieldHitsCollection* SHLDB20NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB20NXHCID));

    ///shield in bar_21
    const PmtshieldHitsCollection* SHLDB21PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB21PXHCID));
    const PmtshieldHitsCollection* SHLDB21NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB21NXHCID));

    ///shield in bar_22
    const PmtshieldHitsCollection* SHLDB22PXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB22PXHCID));
    const PmtshieldHitsCollection* SHLDB22NXHC =
        static_cast<const PmtshieldHitsCollection*>(hce->GetHC(SHLDB22NXHCID));




    if ( !SddHC || !Bar1HC || !Bar2HC || !Bar3HC || !Bar4HC || !Bar5HC || !Bar6HC || !Bar7HC || !Bar8HC|| !Bar9HC || !Bar10HC || !Bar11HC || !Bar12HC || !Bar13HC || !Bar14HC || !Bar15HC || !Bar16HC || !Bar17HC || !Bar18HC || !Bar19HC || !Bar20HC || !Bar21HC || !Bar22HC || !CHC || !SHLDB1PXHC || !SHLDB1NXHC || !SHLDB2PXHC || !SHLDB2NXHC || !SHLDB3PXHC || !SHLDB3NXHC || !SHLDB4PXHC || !SHLDB4NXHC || !SHLDB5PXHC || !SHLDB5NXHC || !SHLDB6PXHC || !SHLDB6NXHC || !SHLDB7PXHC || !SHLDB7NXHC || !SHLDB8PXHC || !SHLDB8NXHC || !SHLDB9PXHC || !SHLDB9NXHC || !SHLDB10PXHC || !SHLDB10NXHC || !SHLDB11PXHC || !SHLDB11NXHC || !SHLDB12PXHC || !SHLDB12NXHC || !SHLDB13PXHC || !SHLDB13NXHC || !SHLDB14PXHC || !SHLDB14NXHC || !SHLDB15PXHC || !SHLDB15NXHC || !SHLDB16PXHC || !SHLDB16NXHC || !SHLDB17PXHC || !SHLDB17NXHC || !SHLDB18PXHC || !SHLDB18NXHC || !SHLDB19PXHC || !SHLDB19NXHC || !SHLDB20PXHC || !SHLDB20NXHC || !SHLDB21PXHC || !SHLDB21NXHC || !SHLDB22PXHC || !SHLDB22NXHC
 )
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;

    }
    G4double e_sdd = 0;
    G4double e_bar1 = 0;
    G4double e_bar2 = 0;
    G4double e_bar3 = 0;
    G4double e_bar4 = 0;
    G4double e_bar5 = 0;
    G4double e_bar6 = 0;
    G4double e_bar7 = 0;
    G4double e_bar8 = 0;
    G4double e_bar9 = 0;
    G4double e_bar10 = 0;
    G4double e_bar11 = 0;
    G4double e_bar12 = 0;
    G4double e_bar13 = 0;
    G4double e_bar14 = 0;
    G4double e_bar15 = 0;
    G4double e_bar16 = 0;
    G4double e_bar17 = 0;
    G4double e_bar18 = 0;
    G4double e_bar19 = 0;
    G4double e_bar20 = 0;
    G4double e_bar21 = 0;
    G4double e_bar22 = 0;

    ///sdd
    for (size_t i=0;i<SddHC->GetSize();i++)
    {
        SddHit* hit = (*SddHC)[i];
        e_sdd += hit->GetEdep();
    }

    ///bar_1
    for (size_t i=0;i<Bar1HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar1HC)[i];
        e_bar1 += hit->GetEdep();
    }

    ///bar_2
    for (size_t i=0;i<Bar2HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar2HC)[i];
        e_bar2 += hit->GetEdep();
    }

    ///bar_3
    for (size_t i=0;i<Bar3HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar3HC)[i];
        e_bar3 += hit->GetEdep();
    }
      ///place_calculate_e_bar
    ///sdd_4
    for (size_t i=0;i<Bar4HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar4HC)[i];
        e_bar4 += hit->GetEdep();
    }


    ///sdd_5
    for (size_t i=0;i<Bar5HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar5HC)[i];
        e_bar5 += hit->GetEdep();
    }


    ///sdd_6
    for (size_t i=0;i<Bar6HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar6HC)[i];
        e_bar6 += hit->GetEdep();
    }


    ///sdd_7
    for (size_t i=0;i<Bar7HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar7HC)[i];
        e_bar7 += hit->GetEdep();
    }


    ///sdd_8
    for (size_t i=0;i<Bar8HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar8HC)[i];
        e_bar8 += hit->GetEdep();
    }


    ///sdd_9
    for (size_t i=0;i<Bar9HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar9HC)[i];
        e_bar9 += hit->GetEdep();
    }


    ///sdd_10
    for (size_t i=0;i<Bar10HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar10HC)[i];
        e_bar10 += hit->GetEdep();
    }


    ///sdd_11
    for (size_t i=0;i<Bar11HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar11HC)[i];
        e_bar11 += hit->GetEdep();
    }


    ///sdd_12
    for (size_t i=0;i<Bar12HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar12HC)[i];
        e_bar12 += hit->GetEdep();
    }


    ///sdd_13
    for (size_t i=0;i<Bar13HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar13HC)[i];
        e_bar13 += hit->GetEdep();
    }


    ///sdd_14
    for (size_t i=0;i<Bar14HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar14HC)[i];
        e_bar14 += hit->GetEdep();
    }


    ///sdd_15
    for (size_t i=0;i<Bar15HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar15HC)[i];
        e_bar15 += hit->GetEdep();
    }


    ///sdd_16
    for (size_t i=0;i<Bar16HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar16HC)[i];
        e_bar16 += hit->GetEdep();
    }


    ///sdd_17
    for (size_t i=0;i<Bar17HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar17HC)[i];
        e_bar17 += hit->GetEdep();
    }


    ///sdd_18
    for (size_t i=0;i<Bar18HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar18HC)[i];
        e_bar18 += hit->GetEdep();
    }


    ///sdd_19
    for (size_t i=0;i<Bar19HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar19HC)[i];
        e_bar19 += hit->GetEdep();
    }


    ///sdd_20
    for (size_t i=0;i<Bar20HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar20HC)[i];
        e_bar20 += hit->GetEdep();
    }


    ///sdd_21
    for (size_t i=0;i<Bar21HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar21HC)[i];
        e_bar21 += hit->GetEdep();
    }


    ///sdd_22
    for (size_t i=0;i<Bar22HC->GetSize();i++)
    {
        HodoscopeHit* hit = (*Bar22HC)[i];
        e_bar22 += hit->GetEdep();
    }





    sdd_ene += e_sdd; 
    bar1_ene += e_bar1;
    bar2_ene += e_bar2;
    bar3_ene += e_bar3;
    bar4_ene += e_bar4;
    bar5_ene += e_bar5;
    bar6_ene += e_bar6;
    bar7_ene += e_bar7;
    bar8_ene += e_bar8;
    bar9_ene += e_bar9;
    bar10_ene += e_bar10;
    bar11_ene += e_bar11;
    bar12_ene += e_bar12;
    bar13_ene += e_bar13;
    bar14_ene += e_bar14;
    bar15_ene += e_bar15;
    bar16_ene += e_bar16;
    bar17_ene += e_bar17;
    bar18_ene += e_bar18;
    bar19_ene += e_bar19;
    bar20_ene += e_bar20;
    bar21_ene += e_bar21;
    bar22_ene += e_bar22;

    ///if ( had+em > 0 )
        ///shower_shape += ( em/(had+em) );
}

///Multi-threads
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


