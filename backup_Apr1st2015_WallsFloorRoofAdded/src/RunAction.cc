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
// $Id: RunAction.cc 74204 2013-10-01 07:04:43Z ihrivnac $
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "Analysis.hh"
#include "Run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{
    
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("ScintillatorRun");

  // Book histograms, ntuple
  //

/*
  
  // Creating 1D histograms
  analysisManager
    ->CreateH1("ScintillatorBar1","Scintillator bar 1 # Hits", 50, 0., 15); // h1 Id = 0
  analysisManager
    ->CreateH1("ScintillatorBar2","Scintillator bar 2 # Hits", 50, 0., 15); // h1 Id = 1
  
  analysisManager
    ->CreateH1("E of First hit in Bar1","Deposited energy of first hit in bar 1", 50, 0.,2000); // h1 Id = 2
  analysisManager
    ->CreateH1("E of First hit in Bar2","Deposited energy of first hit in bar 2 ", 50, 0.,2000); // h1 Id = 3
  
  analysisManager
    ->CreateH1("Total E for all hits in Bar1","Deposited energy of all hits in bar 1", 50, 0.,5000); // h1 Id = 4
  analysisManager
    ->CreateH1("Total E of all hits in Bar2","Deposited energy of all hits in bar 2", 50, 0.,5000); // h1 Id = 5
  
  analysisManager
    ->CreateH1("Time of First hit in Bar1","Timing of first hit in bar 1", 1000, 0.,5000); // h1 Id = 6
  analysisManager
    ->CreateH1("Time of First hit in Bar2","Timing of first hit in bar 2 ", 1000, 0.,5000); // h1 Id = 7
  
  analysisManager
    ->CreateH1("Reconstructed E in Bar1","Reconstructed energy in bar 1", 100, 0.,50); // h1 Id = 8
  analysisManager
    ->CreateH1("Reconstructed E in Bar2","Reconstructed energy in bar 2 ", 100, 0.,50); // h1 Id = 9
  
  // Creating 2D histograms
  analysisManager                                                
    ->CreateH2("ScintillatorBar1 XY","Scintillator bar 1 X vs Y",           // h2 Id = 0
               50, -1000., 1000, 50, -300., 300.); 
  analysisManager                                                
    ->CreateH2("ScintillatorBar2 XY","Scintillator bar 2 X vs Y",           // h2 Id = 1
               50, -1500., 1500, 50, -300., 300.);


*/

  // Creating ntuple
  

  analysisManager->CreateNtuple("ScintillatorRun", "Hits");
  //~~~~~~
  analysisManager->CreateNtupleDColumn("Incident_Neutron_spectrum");  // column Id = 0
  //
  analysisManager->CreateNtupleIColumn("Collimator_N_of_Hits");       // column Id = 1
  analysisManager->CreateNtupleDColumn("Collimator_Time_1stHit");     // column Id = 2
  //
  analysisManager->CreateNtupleIColumn("Sdd_N_of_Hits");              // column Id = 3
  analysisManager->CreateNtupleDColumn("Sdd_Energy");                 // column Id = 4
  analysisManager->CreateNtupleDColumn("Sdd_Energy_1stHit");          // column Id = 5
  analysisManager->CreateNtupleDColumn("Sdd_Time_1stHit");            // column Id = 6
  analysisManager->CreateNtupleDColumn("Sdd_Reconstructed_E");        // column Id = 7
  /// place_run_action
  //Bar1
  analysisManager->CreateNtupleIColumn("Bar1_N_of_Hits");             // column Id = 8
  analysisManager->CreateNtupleDColumn("Bar1_Energy");                // column Id = 9
  analysisManager->CreateNtupleDColumn("Bar1_Energy_1stHit");         // column Id = 10
  analysisManager->CreateNtupleDColumn("Bar1_Time_1stHit");           // column Id = 11
  analysisManager->CreateNtupleDColumn("Bar1_Reconstructed_E");       // column Id = 12
  analysisManager->CreateNtupleDColumn("Bar1_HitPosition_X");         // column Id = 13
  analysisManager->CreateNtupleDColumn("Bar1_HitPosition_Y");         // column Id = 14
  analysisManager->CreateNtupleDColumn("Bar1_HitPosition_Z");         // column Id = 15
  analysisManager->CreateNtupleIColumn("ShieldB1PX_N_of_Hits");       // column Id = 16
  analysisManager->CreateNtupleDColumn("ShieldB1PX_Time_1stHit");     // column Id = 17
  analysisManager->CreateNtupleIColumn("ShieldB1NX_N_of_Hits");       // column Id = 18
  analysisManager->CreateNtupleDColumn("ShieldB1NX_Time_1stHit");     // column Id = 19

  //Bar2
  analysisManager->CreateNtupleIColumn("Bar2_N_of_Hits");             // column Id = 20
  analysisManager->CreateNtupleDColumn("Bar2_Energy");                // column Id = 21
  analysisManager->CreateNtupleDColumn("Bar2_Energy_1stHit");         // column Id = 22
  analysisManager->CreateNtupleDColumn("Bar2_Time_1stHit");           // column Id = 23
  analysisManager->CreateNtupleDColumn("Bar2_Reconstructed_E");       // column Id = 24
  analysisManager->CreateNtupleDColumn("Bar2_HitPosition_X");         // column Id = 25
  analysisManager->CreateNtupleDColumn("Bar2_HitPosition_Y");         // column Id = 26
  analysisManager->CreateNtupleDColumn("Bar2_HitPosition_Z");         // column Id = 27
  analysisManager->CreateNtupleIColumn("ShieldB2PX_N_of_Hits");       // column Id = 28
  analysisManager->CreateNtupleDColumn("ShieldB2PX_Time_1stHit");     // column Id = 29
  analysisManager->CreateNtupleIColumn("ShieldB2NX_N_of_Hits");       // column Id = 30
  analysisManager->CreateNtupleDColumn("ShieldB2NX_Time_1stHit");     // column Id = 31

  //Bar3
  analysisManager->CreateNtupleIColumn("Bar3_N_of_Hits");             // column Id = 32
  analysisManager->CreateNtupleDColumn("Bar3_Energy");                // column Id = 33
  analysisManager->CreateNtupleDColumn("Bar3_Energy_1stHit");         // column Id = 34
  analysisManager->CreateNtupleDColumn("Bar3_Time_1stHit");           // column Id = 35
  analysisManager->CreateNtupleDColumn("Bar3_Reconstructed_E");       // column Id = 36
  analysisManager->CreateNtupleDColumn("Bar3_HitPosition_X");         // column Id = 37
  analysisManager->CreateNtupleDColumn("Bar3_HitPosition_Y");         // column Id = 38
  analysisManager->CreateNtupleDColumn("Bar3_HitPosition_Z");         // column Id = 39
  analysisManager->CreateNtupleIColumn("ShieldB3PX_N_of_Hits");       // column Id = 40
  analysisManager->CreateNtupleDColumn("ShieldB3PX_Time_1stHit");     // column Id = 41
  analysisManager->CreateNtupleIColumn("ShieldB3NX_N_of_Hits");       // column Id = 42
  analysisManager->CreateNtupleDColumn("ShieldB3NX_Time_1stHit");     // column Id = 43

  //Bar4
  analysisManager->CreateNtupleIColumn("Bar4_N_of_Hits");             // column Id = 44
  analysisManager->CreateNtupleDColumn("Bar4_Energy");                // column Id = 45
  analysisManager->CreateNtupleDColumn("Bar4_Energy_1stHit");         // column Id = 46
  analysisManager->CreateNtupleDColumn("Bar4_Time_1stHit");           // column Id = 47
  analysisManager->CreateNtupleDColumn("Bar4_Reconstructed_E");       // column Id = 48
  analysisManager->CreateNtupleDColumn("Bar4_HitPosition_X");         // column Id = 49
  analysisManager->CreateNtupleDColumn("Bar4_HitPosition_Y");         // column Id = 50
  analysisManager->CreateNtupleDColumn("Bar4_HitPosition_Z");         // column Id = 51
  analysisManager->CreateNtupleIColumn("ShieldB4PX_N_of_Hits");       // column Id = 52
  analysisManager->CreateNtupleDColumn("ShieldB4PX_Time_1stHit");     // column Id = 53
  analysisManager->CreateNtupleIColumn("ShieldB4NX_N_of_Hits");       // column Id = 54
  analysisManager->CreateNtupleDColumn("ShieldB4NX_Time_1stHit");     // column Id = 55

  //Bar5
  analysisManager->CreateNtupleIColumn("Bar5_N_of_Hits");             // column Id = 56
  analysisManager->CreateNtupleDColumn("Bar5_Energy");                // column Id = 57
  analysisManager->CreateNtupleDColumn("Bar5_Energy_1stHit");         // column Id = 58
  analysisManager->CreateNtupleDColumn("Bar5_Time_1stHit");           // column Id = 59
  analysisManager->CreateNtupleDColumn("Bar5_Reconstructed_E");       // column Id = 60
  analysisManager->CreateNtupleDColumn("Bar5_HitPosition_X");         // column Id = 61
  analysisManager->CreateNtupleDColumn("Bar5_HitPosition_Y");         // column Id = 62
  analysisManager->CreateNtupleDColumn("Bar5_HitPosition_Z");         // column Id = 63
  analysisManager->CreateNtupleIColumn("ShieldB5PX_N_of_Hits");       // column Id = 64
  analysisManager->CreateNtupleDColumn("ShieldB5PX_Time_1stHit");     // column Id = 65
  analysisManager->CreateNtupleIColumn("ShieldB5NX_N_of_Hits");       // column Id = 66
  analysisManager->CreateNtupleDColumn("ShieldB5NX_Time_1stHit");     // column Id = 67

  //Bar6
  analysisManager->CreateNtupleIColumn("Bar6_N_of_Hits");             // column Id = 68
  analysisManager->CreateNtupleDColumn("Bar6_Energy");                // column Id = 69
  analysisManager->CreateNtupleDColumn("Bar6_Energy_1stHit");         // column Id = 70
  analysisManager->CreateNtupleDColumn("Bar6_Time_1stHit");           // column Id = 71
  analysisManager->CreateNtupleDColumn("Bar6_Reconstructed_E");       // column Id = 72
  analysisManager->CreateNtupleDColumn("Bar6_HitPosition_X");         // column Id = 73
  analysisManager->CreateNtupleDColumn("Bar6_HitPosition_Y");         // column Id = 74
  analysisManager->CreateNtupleDColumn("Bar6_HitPosition_Z");         // column Id = 75
  analysisManager->CreateNtupleIColumn("ShieldB6PX_N_of_Hits");       // column Id = 76
  analysisManager->CreateNtupleDColumn("ShieldB6PX_Time_1stHit");     // column Id = 77
  analysisManager->CreateNtupleIColumn("ShieldB6NX_N_of_Hits");       // column Id = 78
  analysisManager->CreateNtupleDColumn("ShieldB6NX_Time_1stHit");     // column Id = 79

  //Bar7
  analysisManager->CreateNtupleIColumn("Bar7_N_of_Hits");             // column Id = 80
  analysisManager->CreateNtupleDColumn("Bar7_Energy");                // column Id = 81
  analysisManager->CreateNtupleDColumn("Bar7_Energy_1stHit");         // column Id = 82
  analysisManager->CreateNtupleDColumn("Bar7_Time_1stHit");           // column Id = 83
  analysisManager->CreateNtupleDColumn("Bar7_Reconstructed_E");       // column Id = 84
  analysisManager->CreateNtupleDColumn("Bar7_HitPosition_X");         // column Id = 85
  analysisManager->CreateNtupleDColumn("Bar7_HitPosition_Y");         // column Id = 86
  analysisManager->CreateNtupleDColumn("Bar7_HitPosition_Z");         // column Id = 87
  analysisManager->CreateNtupleIColumn("ShieldB7PX_N_of_Hits");       // column Id = 88
  analysisManager->CreateNtupleDColumn("ShieldB7PX_Time_1stHit");     // column Id = 89
  analysisManager->CreateNtupleIColumn("ShieldB7NX_N_of_Hits");       // column Id = 90
  analysisManager->CreateNtupleDColumn("ShieldB7NX_Time_1stHit");     // column Id = 91

  //Bar8
  analysisManager->CreateNtupleIColumn("Bar8_N_of_Hits");             // column Id = 92
  analysisManager->CreateNtupleDColumn("Bar8_Energy");                // column Id = 93
  analysisManager->CreateNtupleDColumn("Bar8_Energy_1stHit");         // column Id = 94
  analysisManager->CreateNtupleDColumn("Bar8_Time_1stHit");           // column Id = 95
  analysisManager->CreateNtupleDColumn("Bar8_Reconstructed_E");       // column Id = 96
  analysisManager->CreateNtupleDColumn("Bar8_HitPosition_X");         // column Id = 97
  analysisManager->CreateNtupleDColumn("Bar8_HitPosition_Y");         // column Id = 98
  analysisManager->CreateNtupleDColumn("Bar8_HitPosition_Z");         // column Id = 99
  analysisManager->CreateNtupleIColumn("ShieldB8PX_N_of_Hits");       // column Id = 100
  analysisManager->CreateNtupleDColumn("ShieldB8PX_Time_1stHit");     // column Id = 101
  analysisManager->CreateNtupleIColumn("ShieldB8NX_N_of_Hits");       // column Id = 102
  analysisManager->CreateNtupleDColumn("ShieldB8NX_Time_1stHit");     // column Id = 103

  //Bar9
  analysisManager->CreateNtupleIColumn("Bar9_N_of_Hits");             // column Id = 104
  analysisManager->CreateNtupleDColumn("Bar9_Energy");                // column Id = 105
  analysisManager->CreateNtupleDColumn("Bar9_Energy_1stHit");         // column Id = 106
  analysisManager->CreateNtupleDColumn("Bar9_Time_1stHit");           // column Id = 107
  analysisManager->CreateNtupleDColumn("Bar9_Reconstructed_E");       // column Id = 108
  analysisManager->CreateNtupleDColumn("Bar9_HitPosition_X");         // column Id = 109
  analysisManager->CreateNtupleDColumn("Bar9_HitPosition_Y");         // column Id = 110
  analysisManager->CreateNtupleDColumn("Bar9_HitPosition_Z");         // column Id = 111
  analysisManager->CreateNtupleIColumn("ShieldB9PX_N_of_Hits");       // column Id = 112
  analysisManager->CreateNtupleDColumn("ShieldB9PX_Time_1stHit");     // column Id = 113
  analysisManager->CreateNtupleIColumn("ShieldB9NX_N_of_Hits");       // column Id = 114
  analysisManager->CreateNtupleDColumn("ShieldB9NX_Time_1stHit");     // column Id = 115

  //Bar10
  analysisManager->CreateNtupleIColumn("Bar10_N_of_Hits");             // column Id = 116
  analysisManager->CreateNtupleDColumn("Bar10_Energy");                // column Id = 117
  analysisManager->CreateNtupleDColumn("Bar10_Energy_1stHit");         // column Id = 118
  analysisManager->CreateNtupleDColumn("Bar10_Time_1stHit");           // column Id = 119
  analysisManager->CreateNtupleDColumn("Bar10_Reconstructed_E");       // column Id = 120
  analysisManager->CreateNtupleDColumn("Bar10_HitPosition_X");         // column Id = 121
  analysisManager->CreateNtupleDColumn("Bar10_HitPosition_Y");         // column Id = 122
  analysisManager->CreateNtupleDColumn("Bar10_HitPosition_Z");         // column Id = 123
  analysisManager->CreateNtupleIColumn("ShieldB10PX_N_of_Hits");       // column Id = 124
  analysisManager->CreateNtupleDColumn("ShieldB10PX_Time_1stHit");     // column Id = 125
  analysisManager->CreateNtupleIColumn("ShieldB10NX_N_of_Hits");       // column Id = 126
  analysisManager->CreateNtupleDColumn("ShieldB10NX_Time_1stHit");     // column Id = 127

  //Bar11
  analysisManager->CreateNtupleIColumn("Bar11_N_of_Hits");             // column Id = 128
  analysisManager->CreateNtupleDColumn("Bar11_Energy");                // column Id = 129
  analysisManager->CreateNtupleDColumn("Bar11_Energy_1stHit");         // column Id = 130
  analysisManager->CreateNtupleDColumn("Bar11_Time_1stHit");           // column Id = 131
  analysisManager->CreateNtupleDColumn("Bar11_Reconstructed_E");       // column Id = 132
  analysisManager->CreateNtupleDColumn("Bar11_HitPosition_X");         // column Id = 133
  analysisManager->CreateNtupleDColumn("Bar11_HitPosition_Y");         // column Id = 134
  analysisManager->CreateNtupleDColumn("Bar11_HitPosition_Z");         // column Id = 135
  analysisManager->CreateNtupleIColumn("ShieldB11PX_N_of_Hits");       // column Id = 136
  analysisManager->CreateNtupleDColumn("ShieldB11PX_Time_1stHit");     // column Id = 137
  analysisManager->CreateNtupleIColumn("ShieldB11NX_N_of_Hits");       // column Id = 138
  analysisManager->CreateNtupleDColumn("ShieldB11NX_Time_1stHit");     // column Id = 139

  //Bar12
  analysisManager->CreateNtupleIColumn("Bar12_N_of_Hits");             // column Id = 140
  analysisManager->CreateNtupleDColumn("Bar12_Energy");                // column Id = 141
  analysisManager->CreateNtupleDColumn("Bar12_Energy_1stHit");         // column Id = 142
  analysisManager->CreateNtupleDColumn("Bar12_Time_1stHit");           // column Id = 143
  analysisManager->CreateNtupleDColumn("Bar12_Reconstructed_E");       // column Id = 144
  analysisManager->CreateNtupleDColumn("Bar12_HitPosition_X");         // column Id = 145
  analysisManager->CreateNtupleDColumn("Bar12_HitPosition_Y");         // column Id = 146
  analysisManager->CreateNtupleDColumn("Bar12_HitPosition_Z");         // column Id = 147
  analysisManager->CreateNtupleIColumn("ShieldB12PX_N_of_Hits");       // column Id = 148
  analysisManager->CreateNtupleDColumn("ShieldB12PX_Time_1stHit");     // column Id = 149
  analysisManager->CreateNtupleIColumn("ShieldB12NX_N_of_Hits");       // column Id = 150
  analysisManager->CreateNtupleDColumn("ShieldB12NX_Time_1stHit");     // column Id = 151

  //Bar13
  analysisManager->CreateNtupleIColumn("Bar13_N_of_Hits");             // column Id = 152
  analysisManager->CreateNtupleDColumn("Bar13_Energy");                // column Id = 153
  analysisManager->CreateNtupleDColumn("Bar13_Energy_1stHit");         // column Id = 154
  analysisManager->CreateNtupleDColumn("Bar13_Time_1stHit");           // column Id = 155
  analysisManager->CreateNtupleDColumn("Bar13_Reconstructed_E");       // column Id = 156
  analysisManager->CreateNtupleDColumn("Bar13_HitPosition_X");         // column Id = 157
  analysisManager->CreateNtupleDColumn("Bar13_HitPosition_Y");         // column Id = 158
  analysisManager->CreateNtupleDColumn("Bar13_HitPosition_Z");         // column Id = 159
  analysisManager->CreateNtupleIColumn("ShieldB13PX_N_of_Hits");       // column Id = 160
  analysisManager->CreateNtupleDColumn("ShieldB13PX_Time_1stHit");     // column Id = 161
  analysisManager->CreateNtupleIColumn("ShieldB13NX_N_of_Hits");       // column Id = 162
  analysisManager->CreateNtupleDColumn("ShieldB13NX_Time_1stHit");     // column Id = 163

  //Bar14
  analysisManager->CreateNtupleIColumn("Bar14_N_of_Hits");             // column Id = 164
  analysisManager->CreateNtupleDColumn("Bar14_Energy");                // column Id = 165
  analysisManager->CreateNtupleDColumn("Bar14_Energy_1stHit");         // column Id = 166
  analysisManager->CreateNtupleDColumn("Bar14_Time_1stHit");           // column Id = 167
  analysisManager->CreateNtupleDColumn("Bar14_Reconstructed_E");       // column Id = 168
  analysisManager->CreateNtupleDColumn("Bar14_HitPosition_X");         // column Id = 169
  analysisManager->CreateNtupleDColumn("Bar14_HitPosition_Y");         // column Id = 170
  analysisManager->CreateNtupleDColumn("Bar14_HitPosition_Z");         // column Id = 171
  analysisManager->CreateNtupleIColumn("ShieldB14PX_N_of_Hits");       // column Id = 172
  analysisManager->CreateNtupleDColumn("ShieldB14PX_Time_1stHit");     // column Id = 173
  analysisManager->CreateNtupleIColumn("ShieldB14NX_N_of_Hits");       // column Id = 174
  analysisManager->CreateNtupleDColumn("ShieldB14NX_Time_1stHit");     // column Id = 175

  //Bar15
  analysisManager->CreateNtupleIColumn("Bar15_N_of_Hits");             // column Id = 176
  analysisManager->CreateNtupleDColumn("Bar15_Energy");                // column Id = 177
  analysisManager->CreateNtupleDColumn("Bar15_Energy_1stHit");         // column Id = 178
  analysisManager->CreateNtupleDColumn("Bar15_Time_1stHit");           // column Id = 179
  analysisManager->CreateNtupleDColumn("Bar15_Reconstructed_E");       // column Id = 180
  analysisManager->CreateNtupleDColumn("Bar15_HitPosition_X");         // column Id = 181
  analysisManager->CreateNtupleDColumn("Bar15_HitPosition_Y");         // column Id = 182
  analysisManager->CreateNtupleDColumn("Bar15_HitPosition_Z");         // column Id = 183
  analysisManager->CreateNtupleIColumn("ShieldB15PX_N_of_Hits");       // column Id = 184
  analysisManager->CreateNtupleDColumn("ShieldB15PX_Time_1stHit");     // column Id = 185
  analysisManager->CreateNtupleIColumn("ShieldB15NX_N_of_Hits");       // column Id = 186
  analysisManager->CreateNtupleDColumn("ShieldB15NX_Time_1stHit");     // column Id = 187

  //Bar16
  analysisManager->CreateNtupleIColumn("Bar16_N_of_Hits");             // column Id = 188
  analysisManager->CreateNtupleDColumn("Bar16_Energy");                // column Id = 189
  analysisManager->CreateNtupleDColumn("Bar16_Energy_1stHit");         // column Id = 190
  analysisManager->CreateNtupleDColumn("Bar16_Time_1stHit");           // column Id = 191
  analysisManager->CreateNtupleDColumn("Bar16_Reconstructed_E");       // column Id = 192
  analysisManager->CreateNtupleDColumn("Bar16_HitPosition_X");         // column Id = 193
  analysisManager->CreateNtupleDColumn("Bar16_HitPosition_Y");         // column Id = 194
  analysisManager->CreateNtupleDColumn("Bar16_HitPosition_Z");         // column Id = 195
  analysisManager->CreateNtupleIColumn("ShieldB16PX_N_of_Hits");       // column Id = 196
  analysisManager->CreateNtupleDColumn("ShieldB16PX_Time_1stHit");     // column Id = 197
  analysisManager->CreateNtupleIColumn("ShieldB16NX_N_of_Hits");       // column Id = 198
  analysisManager->CreateNtupleDColumn("ShieldB16NX_Time_1stHit");     // column Id = 199

  //Bar17
  analysisManager->CreateNtupleIColumn("Bar17_N_of_Hits");             // column Id = 200
  analysisManager->CreateNtupleDColumn("Bar17_Energy");                // column Id = 201
  analysisManager->CreateNtupleDColumn("Bar17_Energy_1stHit");         // column Id = 202
  analysisManager->CreateNtupleDColumn("Bar17_Time_1stHit");           // column Id = 203
  analysisManager->CreateNtupleDColumn("Bar17_Reconstructed_E");       // column Id = 204
  analysisManager->CreateNtupleDColumn("Bar17_HitPosition_X");         // column Id = 205
  analysisManager->CreateNtupleDColumn("Bar17_HitPosition_Y");         // column Id = 206
  analysisManager->CreateNtupleDColumn("Bar17_HitPosition_Z");         // column Id = 207
  analysisManager->CreateNtupleIColumn("ShieldB17PX_N_of_Hits");       // column Id = 208
  analysisManager->CreateNtupleDColumn("ShieldB17PX_Time_1stHit");     // column Id = 209
  analysisManager->CreateNtupleIColumn("ShieldB17NX_N_of_Hits");       // column Id = 210
  analysisManager->CreateNtupleDColumn("ShieldB17NX_Time_1stHit");     // column Id = 211

  //Bar18
  analysisManager->CreateNtupleIColumn("Bar18_N_of_Hits");             // column Id = 212
  analysisManager->CreateNtupleDColumn("Bar18_Energy");                // column Id = 213
  analysisManager->CreateNtupleDColumn("Bar18_Energy_1stHit");         // column Id = 214
  analysisManager->CreateNtupleDColumn("Bar18_Time_1stHit");           // column Id = 215
  analysisManager->CreateNtupleDColumn("Bar18_Reconstructed_E");       // column Id = 216
  analysisManager->CreateNtupleDColumn("Bar18_HitPosition_X");         // column Id = 217
  analysisManager->CreateNtupleDColumn("Bar18_HitPosition_Y");         // column Id = 218
  analysisManager->CreateNtupleDColumn("Bar18_HitPosition_Z");         // column Id = 219
  analysisManager->CreateNtupleIColumn("ShieldB18PX_N_of_Hits");       // column Id = 220
  analysisManager->CreateNtupleDColumn("ShieldB18PX_Time_1stHit");     // column Id = 221
  analysisManager->CreateNtupleIColumn("ShieldB18NX_N_of_Hits");       // column Id = 222
  analysisManager->CreateNtupleDColumn("ShieldB18NX_Time_1stHit");     // column Id = 223

  //Bar19
  analysisManager->CreateNtupleIColumn("Bar19_N_of_Hits");             // column Id = 224
  analysisManager->CreateNtupleDColumn("Bar19_Energy");                // column Id = 225
  analysisManager->CreateNtupleDColumn("Bar19_Energy_1stHit");         // column Id = 226
  analysisManager->CreateNtupleDColumn("Bar19_Time_1stHit");           // column Id = 227
  analysisManager->CreateNtupleDColumn("Bar19_Reconstructed_E");       // column Id = 228
  analysisManager->CreateNtupleDColumn("Bar19_HitPosition_X");         // column Id = 229
  analysisManager->CreateNtupleDColumn("Bar19_HitPosition_Y");         // column Id = 230
  analysisManager->CreateNtupleDColumn("Bar19_HitPosition_Z");         // column Id = 231
  analysisManager->CreateNtupleIColumn("ShieldB19PX_N_of_Hits");       // column Id = 232
  analysisManager->CreateNtupleDColumn("ShieldB19PX_Time_1stHit");     // column Id = 233
  analysisManager->CreateNtupleIColumn("ShieldB19NX_N_of_Hits");       // column Id = 234
  analysisManager->CreateNtupleDColumn("ShieldB19NX_Time_1stHit");     // column Id = 235

  //Bar20
  analysisManager->CreateNtupleIColumn("Bar20_N_of_Hits");             // column Id = 236
  analysisManager->CreateNtupleDColumn("Bar20_Energy");                // column Id = 237
  analysisManager->CreateNtupleDColumn("Bar20_Energy_1stHit");         // column Id = 238
  analysisManager->CreateNtupleDColumn("Bar20_Time_1stHit");           // column Id = 239
  analysisManager->CreateNtupleDColumn("Bar20_Reconstructed_E");       // column Id = 240
  analysisManager->CreateNtupleDColumn("Bar20_HitPosition_X");         // column Id = 241
  analysisManager->CreateNtupleDColumn("Bar20_HitPosition_Y");         // column Id = 242
  analysisManager->CreateNtupleDColumn("Bar20_HitPosition_Z");         // column Id = 243
  analysisManager->CreateNtupleIColumn("ShieldB20PX_N_of_Hits");       // column Id = 244
  analysisManager->CreateNtupleDColumn("ShieldB20PX_Time_1stHit");     // column Id = 245
  analysisManager->CreateNtupleIColumn("ShieldB20NX_N_of_Hits");       // column Id = 246
  analysisManager->CreateNtupleDColumn("ShieldB20NX_Time_1stHit");     // column Id = 247

  //Bar21
  analysisManager->CreateNtupleIColumn("Bar21_N_of_Hits");             // column Id = 248
  analysisManager->CreateNtupleDColumn("Bar21_Energy");                // column Id = 249
  analysisManager->CreateNtupleDColumn("Bar21_Energy_1stHit");         // column Id = 250
  analysisManager->CreateNtupleDColumn("Bar21_Time_1stHit");           // column Id = 251
  analysisManager->CreateNtupleDColumn("Bar21_Reconstructed_E");       // column Id = 252
  analysisManager->CreateNtupleDColumn("Bar21_HitPosition_X");         // column Id = 253
  analysisManager->CreateNtupleDColumn("Bar21_HitPosition_Y");         // column Id = 254
  analysisManager->CreateNtupleDColumn("Bar21_HitPosition_Z");         // column Id = 255
  analysisManager->CreateNtupleIColumn("ShieldB21PX_N_of_Hits");       // column Id = 256
  analysisManager->CreateNtupleDColumn("ShieldB21PX_Time_1stHit");     // column Id = 257
  analysisManager->CreateNtupleIColumn("ShieldB21NX_N_of_Hits");       // column Id = 258
  analysisManager->CreateNtupleDColumn("ShieldB21NX_Time_1stHit");     // column Id = 259

  //Bar22
  analysisManager->CreateNtupleIColumn("Bar22_N_of_Hits");             // column Id = 260
  analysisManager->CreateNtupleDColumn("Bar22_Energy");                // column Id = 261
  analysisManager->CreateNtupleDColumn("Bar22_Energy_1stHit");         // column Id = 262
  analysisManager->CreateNtupleDColumn("Bar22_Time_1stHit");           // column Id = 263
  analysisManager->CreateNtupleDColumn("Bar22_Reconstructed_E");       // column Id = 264
  analysisManager->CreateNtupleDColumn("Bar22_HitPosition_X");         // column Id = 265
  analysisManager->CreateNtupleDColumn("Bar22_HitPosition_Y");         // column Id = 266
  analysisManager->CreateNtupleDColumn("Bar22_HitPosition_Z");         // column Id = 267
  analysisManager->CreateNtupleIColumn("ShieldB22PX_N_of_Hits");       // column Id = 268
  analysisManager->CreateNtupleDColumn("ShieldB22PX_Time_1stHit");     // column Id = 269
  analysisManager->CreateNtupleIColumn("ShieldB22NX_N_of_Hits");       // column Id = 270
  analysisManager->CreateNtupleDColumn("ShieldB22NX_Time_1stHit");     // column Id = 271


  //~~~~~~
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{

    
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  // Open an output file
  // The default file name is set in RunAction::RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Collect the energy accumulated in the local Run
// And dump on screen the needed physics quantities
// for this particular run.
void RunAction::EndOfRunAction(const G4Run* run)
{
    const Run* myrun = dynamic_cast<const Run*>(run);
    if ( myrun )
    {
        G4int nEvets = myrun->GetNumberOfEvent();
        if ( nEvets < 1 )
        {
            G4ExceptionDescription msg;
            msg << "Run consists of 0 events";
            G4Exception("RunAction::EndOfRunAction()",
                        "Code001", JustWarning, msg);
            nEvets=1;
        }
        ///G4double bar1_ene = myrun->GetBar1Energy();
        ///G4double bar2_ene = myrun->GetBar2Energy();
        /*
        G4cout<<"Run["<<myrun->GetRunID()<<"] With: "<<nEvets<<"Events\n"
        <<" <E_Bar1>="<<G4BestUnit(bar1_ene/nEvets,"Energy")<<"\n"
        <<" <E_Bar2>="<<G4BestUnit(bar2_ene/nEvets,"Energy")<<"\n" 
        << G4endl;
        */
    } else {
        G4ExceptionDescription msg;
        msg << "Run is not of correct type, skypping analysis via RunAction";
        G4Exception("RunAction::EndOfRunAction()",
                    "Code001", JustWarning, msg);
    }
    
    
  // save histograms & ntuple
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Implement this method,
// instead of creating a generic G4Run
// create a user-defined Run
G4Run* RunAction::GenerateRun() {
    return new Run;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
