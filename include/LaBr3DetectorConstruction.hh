#ifndef LaBr3_DetectorConstruction_h
#define LaBr3_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class LaBr3DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		LaBr3DetectorConstruction();
		virtual ~LaBr3DetectorConstruction();

		virtual G4VPhysicalVolume* Construct();

	private:
		void DefineMaterials();
		G4VPhysicalVolume *DefineVolumes();

		G4bool fCheckOverlaps;

	protected:
		//G4LogicalVolume*  fScoringVolume;
};


#endif

