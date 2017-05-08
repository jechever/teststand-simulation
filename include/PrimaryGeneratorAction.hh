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
/// \file electromagnetic/TestEm4/include/PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.hh 66241 2012-12-13 18:34:42Z gunter $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gun.
///
/// It defines (as default) a Cs-137 nucleus, at rest, from a point-like
/// source at (0,0,-6) cm. All parameters (particle type, energy, direction,
/// position) can be changed via the UI commands /gun/...
///

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    
private:
    
        G4ParticleGun*  fParticleGun;
    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
