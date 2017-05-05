/*
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
 // $Id: B1PrimaryGeneratorAction.cc 94307 2015-11-11 13:42:46Z gcosmo $
 //
 /// \file B1PrimaryGeneratorAction.cc
 /// \brief Implementation of the B1PrimaryGeneratorAction class
 
 #include "B1PrimaryGeneratorAction.hh"
 
 #include "G4LogicalVolumeStore.hh"
 #include "G4LogicalVolume.hh"
 #include "G4Box.hh"
 #include "G4RunManager.hh"
 #include "G4ParticleGun.hh"
 #include "G4ParticleTable.hh"
 #include "G4ParticleDefinition.hh"
 #include "G4SystemOfUnits.hh"
 #include "Randomize.hh"
 #include "G4RandomDirection.hh"
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
 fParticleGun(0),
 fEnvelopeBox(0)
 {
 G4int n_particle = 1;
 fParticleGun  = new G4ParticleGun(n_particle);
 
 // default particle kinematic
 G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
 G4String particleName;
 G4ParticleDefinition* particle
 = particleTable->FindParticle(particleName="gamma");
 fParticleGun->SetParticleDefinition(particle);
 fParticleGun->SetParticleEnergy(1.2*MeV);
 }
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
 {
 delete fParticleGun;
 }
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
 {
 //this function is called at the begining of ecah event
 //
 
 // In order to avoid dependence of PrimaryGeneratorAction
 // on DetectorConstruction class we get Envelope volume
 // from G4LogicalVolumeStore.
 
 G4double envSizeXY = 0;
 G4double envSizeZ = 0;
 
 if (!fEnvelopeBox)
 {
 G4LogicalVolume* envLV
 = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
 if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
 }
 
 if ( fEnvelopeBox ) {
 envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
 envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
 }
 else  {
 G4ExceptionDescription msg;
 msg << "Envelope volume of box shape not found.\n";
 msg << "Perhaps you have changed geometry.\n";
 msg << "The gun will be place at the center.";
 G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
 "MyCode0002",JustWarning,msg);
 }
 
 G4double size = 0.8;
 G4double x0 = 0.;
 G4double y0 = 6.55*cm;
 G4double z0 = -6.35*cm;
 
 fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
 
 fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
 
 fParticleGun->GeneratePrimaryVertex(anEvent);
 }
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 */

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0)
{
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);
    fParticleGun->SetParticleEnergy(0*eV);
    //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,0.));
    G4double x0 = 0.;
    G4double y0 = 6.55*cm;
    G4double z0 = -6.35*cm;
    
    fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    
    //fParticleGun->GeneratePrimaryVertex(anEvent); //NOT SURE IF THIS IS NEEDED

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) //A Caesium source
{
    if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {
        G4int Z = 55, A = 137; //Cs-137, to change generators, change A and Z numbers
        G4double ionCharge   = 0.*eplus;
        G4double excitEnergy = 0.*keV;
        
        G4ParticleDefinition* ion
        = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(ionCharge);
    }
    //create vertex
    //
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

