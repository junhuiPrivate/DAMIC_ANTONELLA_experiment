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
// \file  Run.hh
// \brief Definition of Run class

#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"

class G4Event;

//=================================
// Exercise 1 Step 1:
// Create a user-defined Run class
// This class accumulates the energy
// in Hadronic and Em calorimeters for the
// entire run. Energy is taken from hits.
// Add two datamembers that will hold the accumulated energy
// As an optimization, instead of using the hits collection
// names to search them, let's use their ID. Add two integers
// that holds IDs.

class Run : public G4Run {
public:
    Run();
  virtual ~Run() {};

  virtual void RecordEvent(const G4Event*);
  ///virtual void Merge(const G4Run*);
    G4double GetSddEnergy() const { return sdd_ene; }
  ///
    G4double GetBar1Energy() const { return bar1_ene; }
    G4double GetBar2Energy() const { return bar2_ene; }
    G4double GetBar3Energy() const { return bar3_ene; }
    G4double GetBar4Energy() const { return bar4_ene; }
    G4double GetBar5Energy() const { return bar5_ene; }
    G4double GetBar6Energy() const { return bar6_ene; }
    G4double GetBar7Energy() const { return bar7_ene; }
    G4double GetBar8Energy() const { return bar8_ene; }
    G4double GetBar9Energy() const { return bar9_ene; }
    G4double GetBar10Energy() const { return bar10_ene; }
    G4double GetBar11Energy() const { return bar11_ene; }
    G4double GetBar12Energy() const { return bar12_ene; }
    G4double GetBar13Energy() const { return bar13_ene; }
    G4double GetBar14Energy() const { return bar14_ene; }
    G4double GetBar15Energy() const { return bar15_ene; }
    G4double GetBar16Energy() const { return bar16_ene; }
    G4double GetBar17Energy() const { return bar17_ene; }
    G4double GetBar18Energy() const { return bar18_ene; }
    G4double GetBar19Energy() const { return bar19_ene; }
    G4double GetBar20Energy() const { return bar20_ene; }
    G4double GetBar21Energy() const { return bar21_ene; }
    G4double GetBar22Energy() const { return bar22_ene; }

private:
    ///G4double em_ene;
    G4double sdd_ene; ///accumulated energy in sdd.
    G4double bar1_ene;///accumulated energy in bar1.
    G4double bar2_ene;///accumulated energy in bar2.
    G4double bar3_ene;///accumulated energy in bar3.
    G4double bar4_ene;
    G4double bar5_ene;
    G4double bar6_ene;
    G4double bar7_ene;
    G4double bar8_ene;
    G4double bar9_ene;
    G4double bar10_ene;
    G4double bar11_ene;
    G4double bar12_ene;
    G4double bar13_ene;
    G4double bar14_ene;
    G4double bar15_ene;
    G4double bar16_ene;
    G4double bar17_ene;
    G4double bar18_ene;
    G4double bar19_ene;
    G4double bar20_ene;
    G4double bar21_ene;
    G4double bar22_ene;
    //
    G4int SDDHCID; ///ID for sdd hits collection.
    //
    G4int BAR1HCID; ///ID for bar1 hits collection.
    G4int BAR2HCID; ///ID for bar2 hits collection.
    G4int BAR3HCID; ///ID for bar3 hits collection.
    G4int BAR4HCID; 
    G4int BAR5HCID; 
    G4int BAR6HCID; 
    G4int BAR7HCID; 
    G4int BAR8HCID; 
    G4int BAR9HCID; 
    G4int BAR10HCID; 
    G4int BAR11HCID; 
    G4int BAR12HCID; 
    G4int BAR13HCID; 
    G4int BAR14HCID; 
    G4int BAR15HCID; 
    G4int BAR16HCID; 
    G4int BAR17HCID; 
    G4int BAR18HCID; 
    G4int BAR19HCID; 
    G4int BAR20HCID; 
    G4int BAR21HCID; 
    G4int BAR22HCID; 
    //
    G4int CLMHCID;
    //
    G4int SHLDB1PXHCID;//Shiled bar1 Position X direction.
    G4int SHLDB1NXHCID;//Shiled bar1 Negative X direction.
    G4int SHLDB2PXHCID;//Shiled bar2 Position X direction.
    G4int SHLDB2NXHCID;//Shiled bar2 Negative X direction.
    G4int SHLDB3PXHCID;//Shiled bar3 Position X direction.
    G4int SHLDB3NXHCID;//Shiled bar3 Negative X direction.
    G4int SHLDB4PXHCID;
    G4int SHLDB4NXHCID;
    G4int SHLDB5PXHCID;
    G4int SHLDB5NXHCID;
    G4int SHLDB6PXHCID;
    G4int SHLDB6NXHCID;
    G4int SHLDB7PXHCID;
    G4int SHLDB7NXHCID;
    G4int SHLDB8PXHCID;
    G4int SHLDB8NXHCID;
    G4int SHLDB9PXHCID;
    G4int SHLDB9NXHCID;
    G4int SHLDB10PXHCID;
    G4int SHLDB10NXHCID;
    G4int SHLDB11PXHCID;
    G4int SHLDB11NXHCID;
    G4int SHLDB12PXHCID;
    G4int SHLDB12NXHCID;
    G4int SHLDB13PXHCID;
    G4int SHLDB13NXHCID;
    G4int SHLDB14PXHCID;
    G4int SHLDB14NXHCID;
    G4int SHLDB15PXHCID;
    G4int SHLDB15NXHCID;
    G4int SHLDB16PXHCID;
    G4int SHLDB16NXHCID;
    G4int SHLDB17PXHCID;
    G4int SHLDB17NXHCID;
    G4int SHLDB18PXHCID;
    G4int SHLDB18NXHCID;
    G4int SHLDB19PXHCID;
    G4int SHLDB19NXHCID;
    G4int SHLDB20PXHCID;
    G4int SHLDB20NXHCID;
    G4int SHLDB21PXHCID;
    G4int SHLDB21NXHCID;
    G4int SHLDB22PXHCID;
    G4int SHLDB22NXHCID;
};
#endif
