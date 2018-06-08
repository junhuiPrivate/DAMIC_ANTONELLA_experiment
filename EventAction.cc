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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(), 
  ///fHHC1ID(-1),
  ///fHHC2ID(-1),
  fBAR1HCID(-1),
  fBAR2HCID(-1),
  fHCLMID(-1)//collimator
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
    if (fBAR1HCID==-1) {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      fBAR1HCID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      fBAR2HCID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
      ///fHCLMID = sdManager->GetCollectionID("collimator/hodoscopeColl");
    }
}     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
    // =============================================
    // Exercise 3
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
    // corresponding to the two hodoscopes


    // Get hits collections 
    HodoscopeHitsCollection* hHC1 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR1HCID));
      
    HodoscopeHitsCollection* hHC2 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fBAR2HCID));
      
    HodoscopeHitsCollection* hHCLM 
      = static_cast<HodoscopeHitsCollection*>(hce->GetHC(fHCLMID));
      
    ///if ( (!hHC1) || (!hHC2)  )
    if ( (!hHC1) || (!hHC2) || (!hHCLM) )
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
 
    // Fill histograms
 
    ///G4int n_hit = dHC1->entries();
    G4int n_hit_1 = hHC1->entries();///n_hit_1 is the number of hits per incident particle in a bar.
    ///analysisManager->FillH1(0, n_hit_1);

    for (G4int i=0;i<n_hit_1;i++)
    {
       ///DriftChamberHit* hit = (*dHC1)[i];
       /// G4ThreeVector localPos = hit->GetLocalPos();
       ///analysisManager->FillH2(0, localPos.x(), localPos.y());
       HodoscopeHit* hit = (*hHC1)[i];
       G4ThreeVector Pos = hit->GetPos();
       ///analysisManager->FillH2(0, Pos.x()/cm, Pos.y()/cm);
    }
 
    ///n_hit = dHC2->entries();
    G4int n_hit_2 = hHC2->entries();
    ///analysisManager->FillH1(1, n_hit_2);

    for (G4int i=0;i<n_hit_2;i++)
    {
       ///DriftChamberHit* hit = (*dHC2)[i];
       ///G4ThreeVector localPos = hit->GetLocalPos();
       ///analysisManager->FillH2(1, localPos.x(), localPos.y());
       HodoscopeHit* hit = (*hHC2)[i];
       G4ThreeVector Pos = hit->GetPos();
       ///analysisManager->FillH2(1, Pos.x()/cm, Pos.y()/cm);
    }
    
        
    // Fill ntuple
    
    // Bar1Hits
    analysisManager->FillNtupleIColumn(0, hHC1->entries());
    // Bar2Hits
    analysisManager->FillNtupleIColumn(1, hHC2->entries());

    
    // Bar1 Energy
    G4int totalBar1Hit = 0;
    G4double totalBar1E = 0.;
    G4double E_1st_hit_Bar1 = 0.;
    G4double T_1st_hit_Bar1 = 0.;
    ///for (G4int i=0;i<25;i++)
    for (G4int i=0;i<n_hit_1;i++)
    {
        HodoscopeHit* hit = (*hHC1)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar1 = (*hHC1)[0]->GetTime();
        E_1st_hit_Bar1 = (*hHC1)[0]->GetEdep();
            totalBar1Hit++;
            totalBar1E += eDep;
          }
    }
    analysisManager->FillNtupleDColumn(2, totalBar1E/keV);


     //Bar2 Energy
    G4int totalBar2Hit = 0;
    G4double totalBar2E = 0.;
    G4double E_1st_hit_Bar2 = 0.;
    G4double T_1st_hit_Bar2 = 0.;
    for (G4int i=0;i<n_hit_2;i++)
    {
        HodoscopeHit* hit = (*hHC2)[i];
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
        T_1st_hit_Bar2 = (*hHC2)[0]->GetTime();
        E_1st_hit_Bar2 = (*hHC2)[0]->GetEdep();
            totalBar2Hit++;
            totalBar2E += eDep;
        }
    }
    analysisManager->FillNtupleDColumn(3, totalBar2E/keV);


    // Bar1, Energy deposited in 1st hit 
    analysisManager->FillNtupleDColumn(4,E_1st_hit_Bar1/keV);

    // Bar2, Energy deposited in 1st hit
    analysisManager->FillNtupleDColumn(5,E_1st_hit_Bar2/keV);

    // Time 1
    /*for (G4int i=0;i<hHC1->entries();i++)
    {
      ///analysisManager->FillNtupleDColumn(6,(*hHC1)[i]->GetTime()/ns);
    }*/
    ///G4cout << "The timing of T_1st_hit_bar1 is " << T_1st_hit_Bar1/ns << G4endl;

     if (T_1st_hit_Bar1 > 0. && T_1st_hit_Bar1 < 1000./ns){ 
     analysisManager->FillNtupleDColumn(6,T_1st_hit_Bar1/ns);
    // Reconstructed energy for bar 1
     analysisManager->FillNtupleDColumn(8, 1.3*1.0E+6 / (T_1st_hit_Bar1*T_1st_hit_Bar1));
    /// 1.3 probably is incorret, the correct one is 1.09. Default energy in G4 is Mev, time is ns. 
     }

    // Time 2
     if (T_1st_hit_Bar2 > 0. && T_1st_hit_Bar2 < 1000./ns){
     analysisManager->FillNtupleDColumn(7,T_1st_hit_Bar2/ns);
    // Reconstructed energy for bar 2
     analysisManager->FillNtupleDColumn(9, 2.7*1.0E+6 / (T_1st_hit_Bar2*T_1st_hit_Bar2));
    /// 2.7 probably is incorret, the correct one is 2.35. Default energy in G4 is Mev, time is ns. 

     }    

/*
     /// The energy of incident neutron.
     G4RunManager* runManager = G4RunManager::GetRunManager();
    ///PrimaryGeneratorAction* generator = (PrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();
     exGPSPrimaryGeneratorAction* generator = (exGPSPrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();
     G4ParticleDefinition* particle = generator->GetParticleSource()->GetParticleDefinition();
     G4String Particle = particle->GetParticleName();
     G4double energy = generator->GetParticleSource()->GetParticleEnergy();

     analysisManager->FillNtupleDColumn(10,energy/keV);

*/


    analysisManager->AddNtupleRow();

   

    /// ~~~~~ Fill histograms ~~~~~~~~
    /// Be ware : running under "g4csv.sh" model, the lines related to histogram(fillH1, setXAxis etc) 
    /// should be commented. Otherwise warnning messages will display and slow down the speed of analysis. 
/*
    analysisManager->FillH1(2, E_1st_hit_Bar1/keV);
    analysisManager->FillH1(3, E_1st_hit_Bar2/keV);
    analysisManager->FillH1(4, totalBar1E/keV);
    analysisManager->FillH1(5, totalBar2E/keV);
    analysisManager->FillH1(6, T_1st_hit_Bar1/ns);
    analysisManager->FillH1(7, T_1st_hit_Bar2/ns);
    if (T_1st_hit_Bar1 > 0. && T_1st_hit_Bar1 < 1000./ns){ 
    analysisManager->FillH1(8, (1.3*1.0E+6/(T_1st_hit_Bar1*T_1st_hit_Bar1)));///Reconstruction of incident E via bar1
    }
    if (T_1st_hit_Bar2 > 0. && T_1st_hit_Bar2 < 1000./ns){ 
    analysisManager->FillH1(9, (2.7*1.0E+6/(T_1st_hit_Bar2*T_1st_hit_Bar2)));///Reconstruction of incident E via bar2
    }
*/   

    ///Set the title and unit of axis
    ///analysisManager->SetH1Title(2, "No of hits"); /// The title has been set in histogram definition.
/*
    analysisManager->SetH1XAxisTitle(2, "keV");
    analysisManager->SetH1XAxisTitle(3, "keV");
    analysisManager->SetH1XAxisTitle(4, "keV");
    analysisManager->SetH1XAxisTitle(5, "keV");
    analysisManager->SetH1XAxisTitle(6, "ns");
    analysisManager->SetH1XAxisTitle(7, "ns");
    analysisManager->SetH1XAxisTitle(8, "keV");
    analysisManager->SetH1XAxisTitle(9, "keV");
 
    analysisManager->SetH2XAxisTitle(0, "cm");
    analysisManager->SetH2YAxisTitle(0, "cm");
    analysisManager->SetH2XAxisTitle(1, "cm");
    analysisManager->SetH2YAxisTitle(1, "cm");
*/
    //
    // Print diagnostics
    // 
    
    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
    
    G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
    
    G4cout << G4endl
           << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
           << primary->GetG4code()->GetParticleName()
           << " " << primary->GetMomentum() << G4endl;
      
    // Step 3: Loop on the two collections and dump on screen hits
    // Hodoscope 1
    n_hit_1 = hHC1->entries();
    ///G4cout << "Hodoscope 1 has " << n_hit_1 << " hits." << G4endl;
    for (G4int i=0;i<n_hit_1;i++)
    {
        HodoscopeHit* hit = (*hHC1)[i];
        hit->Print();
    }

    // Hodoscope 2
    n_hit_2 = hHC2->entries();
    ///G4cout << "Hodoscope 2 has " << n_hit_2 << " hits." << G4endl;
    for (G4int i=0;i<n_hit_2;i++)
    {
        HodoscopeHit* hit = (*hHC2)[i];
        hit->Print();
    }

/*
     /// Print info on the monitor
    // Bar1 Energy
       G4cout << "Bar1 has " << totalBar1Hit << " hits. Total Edep is "
    << totalBar1E/keV << " (keV)" << ", 1st hit in bar1 : " << E_1st_hit_Bar1/keV << "(keV)" << G4endl;

    // Bar2 Energy
       G4cout << "Bar2 has " << totalBar2Hit << " hits. Total Edep is "
    << totalBar2E/keV << " (keV)" << ", 1st hit in bar2 : " << E_1st_hit_Bar2/keV << "(keV)" << G4endl;
*/ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
