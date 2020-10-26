#include "LaBr3PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4ParticleTable.hh"


LaBr3PrimaryGeneratorAction::LaBr3PrimaryGeneratorAction():G4VUserPrimaryGeneratorAction(),fParticleGun(0){
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);

	// default particle kinematic
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	fParticleGun->SetParticleEnergy(0*eV);    
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}


LaBr3PrimaryGeneratorAction::~LaBr3PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void LaBr3PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	if (particle == G4ChargedGeantino::ChargedGeantino()) {
		//G4int Z = 9, A = 18;    //Fluorine 
		//G4int Z = 62, A = 152;    //Samarium 
		G4int Z = 63, A = 152;    //Europium 
		//G4int Z = 11, A = 22;    //Sodium 
		G4double ionCharge   = 0.*eplus;
		G4double excitEnergy = 0.*keV;

		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(ionCharge);
	}

	// randomized position
	//
	G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;
	///G4double dx0 = 0*cm, dy0 = 0*cm, dz0 = 0*cm;   
	//G4double x0  = 1*cm, y0  = 1*cm, z0  = 1*cm;
	G4double dx0 = 0.1*cm, dy0 = 0.1*cm, dz0 = 0.1*cm; 
	x0 += dx0*(G4UniformRand()-0.5);
	y0 += dy0*(G4UniformRand()-0.5);
	z0 += dz0*(G4UniformRand()-0.5);
	fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

	//create vertex
	//
	fParticleGun->GeneratePrimaryVertex(anEvent);



}


