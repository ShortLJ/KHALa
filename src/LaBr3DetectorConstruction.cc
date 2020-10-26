#include "LaBr3DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"

static const G4double inch = 2.54*cm;

LaBr3DetectorConstruction::LaBr3DetectorConstruction():G4VUserDetectorConstruction(), fCheckOverlaps(true)
{ }

LaBr3DetectorConstruction::~LaBr3DetectorConstruction()
{ }

G4VPhysicalVolume *LaBr3DetectorConstruction::Construct(){
	DefineMaterials();

	return DefineVolumes();

}

void LaBr3DetectorConstruction::DefineMaterials(){

	G4NistManager *nist = G4NistManager::Instance();
	//G4Material *world_mat =
		 nist->FindOrBuildMaterial("G4_AIR");
	//G4Material *Detector_mat = nist->FindOrBuildMaterial("G4_WATER");

	//G4double a;  // mass of a mole;
	G4double z;  // z=mean number of protons;  
	G4double density;
	//G4bool iso;
	G4int nel;

	G4Element *elC = nist->FindOrBuildElement(z=6);
	G4Element *elH = nist->FindOrBuildElement(z=1);
	G4Element *elLa = nist->FindOrBuildElement(z=57);
	G4Element *elBr = nist->FindOrBuildElement(z=35);

	G4Material *Plastic = new G4Material("Plastic",density=2*g/cm3,nel=2, kStateSolid);
	Plastic->AddElement(elC,4);
	Plastic->AddElement(elH,12);

	G4Material *LaBr3 = new G4Material("LaBr3",density=5.29*g/cm3, nel=2, kStateSolid);
	LaBr3->AddElement(elLa,1);
	LaBr3->AddElement(elBr,3); 

	G4cout << *(G4Material::GetMaterialTable()) << G4endl;

}


G4VPhysicalVolume *LaBr3DetectorConstruction::DefineVolumes(){

	G4Material *world_mat = G4Material::GetMaterial("G4_AIR");
	G4Material *Detector_mat = G4Material::GetMaterial("LaBr3");
	G4Material *SD_mat = G4Material::GetMaterial("Plastic");
	
	///////////////world////////////////

	G4Box *solidWorld = 
		new G4Box(	"World_Box",
				100.*cm, 100.*cm, 60.*cm);
	G4LogicalVolume *logicWorld = 
		new G4LogicalVolume(	solidWorld,
					world_mat,
					"World_logic"	);
	G4VPhysicalVolume *physWorld = 
		new G4PVPlacement(	0,
					G4ThreeVector(),
					logicWorld,
					"World_phys",
					0,
					false,
					0,
					fCheckOverlaps	);

	///////////////SourceDisk////////////////

	//G4Box *solidSD = new G4Box("Source_Disk", 1.*cm, 1.*cm, 0.3*cm);
	G4Tubs *solidSD = new G4Tubs("Source_Disk", 0., 1.*cm, 0.3*cm, 0., twopi);
	G4LogicalVolume *logicSD = new G4LogicalVolume(solidSD, SD_mat, "SourceDisk_logic");
		new G4PVPlacement(0, G4ThreeVector(), logicSD, "SourceDisk_phys", logicWorld, false, 0, fCheckOverlaps);


	
	///////////////Detector////////////////
	
//	G4Box *solidDetector = 
//		new G4Box(	"Detector_Box",
//				0.5*1.5*inch, 0.5*1.5*inch, 0.5*1.5*inch);
	G4Tubs *solidDetector = new G4Tubs("Detector_tub", 0., 0.5*1.5*inch, 0.5*1.5*inch, 0., twopi);

	G4LogicalVolume *logicDetector = 
		new G4LogicalVolume(	solidDetector,
					Detector_mat,
					"Detector_logic"	);

	G4ThreeVector position0;
	G4RotationMatrix *yRot[12]; // Rotates X and Z axes only
	for(int i=0; i<12; i++){
		position0 = G4ThreeVector((10.*cm+0.5*1.5*inch), 0., 0.);
		yRot[i] = new G4RotationMatrix; // Rotates X and Z axes only
		yRot[i]->rotateY((M_PI/2.)*rad);  
		yRot[i]->rotateZ(((double)i*M_PI/6.)*rad);  
		//G4PhysicalVolume *physDetector =
			new G4PVPlacement(	G4Transform3D(*yRot[i], position0.rotateZ((double)i*M_PI/6.*rad)),
						logicDetector,
						"Detector_phys",
						logicWorld,
						false,
						100+i,
						fCheckOverlaps	);
	}

	logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
	//G4VisAttributes *VisAtt = new G4VisAttributes();
	//VisAtt->SetVisibility(true);

//	fScoringVolume = logicDetector;
	return physWorld;


}
