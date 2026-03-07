#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "CaloUnitVolume.hh"
#include "EcalUnitSD.hh"
#include "HcalUnitSD.hh"
#include "G4Cache.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4GlobalMagFieldMessenger;

namespace SimCalModule
{
    class DetectorMessenger;
    class CaloUnitVolume;

    enum MaterialIndex
    {
        Vacuum,
        Air,
        Al,
        Si,
        Fe,
        W,
        Cu,
        CuW,
        Steel,
        Quartz,
        Epoxy,
        FR4,
        ESR,
        PWO,
        BGO,
        PlasticSciHCAL,
        PlasticSciECAL,
        SciGlass,
        Graphite,
        Concrete,
        Teflon   // PTFE (polytetrafluoroethylene)
    };

    struct CaloUnitParameter
    {
        G4bool ifDoubleSidedReadout;
        G4double SensitiveLength;
        G4double SensitiveX;
        G4double SensitiveY;
        G4double PassiveSideThick;
        G4double PassiveCoverThick;
        G4double AttachThick;
        G4double Sensitive_dig_out_X;
        G4double Sensitive_dig_out_Y;
        G4double Sensitive_dig_out_Z;
        G4double House_X;
        G4double House_Y;
        G4double House_Z;
        MaterialIndex SensitiveMatIndex;
        MaterialIndex Sensitive_dig_out_MatIndex;
        MaterialIndex PassiveMatIndex;
        MaterialIndex AttachMatIndex;
    };

    class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction();
        ~DetectorConstruction() override;
        G4VPhysicalVolume *Construct() override;
        void ConstructSDandField() override;
        void SetDefaults();
        void ResetCaloLogical();
        void SetEcalCellNumberX(G4int);
        void SetEcalCellNumberY(G4int);
        void SetEcalLayerNumber(G4int);
        void SetHcalCellNumberX(G4int);
        void SetHcalCellNumberY(G4int);
        void SetHcalLayerNumber(G4int);
        void SetEcalSensitiveThick(G4double);
        void SetHcalSensitiveThick(G4double);
        void SetEcalPassiveThick(G4double);
        void SetHcalPassiveThick(G4double);
        void SetEcalAbsThick(G4double);
        void SetHcalAbsThick(G4double);
        void SetUpstreamObjThick(G4double);
        void SetIntermediateObjThick(G4double);
        void SetCaloLogicalVolume(G4LogicalVolume *&, G4LogicalVolume *);
        void SetEcalStepTimeLimit(G4double);
        void SetHcalStepTimeLimit(G4double);
        G4int GetEcalModuleType() const { return EcalModuleType; }
        G4int GetHcalModuleType() const { return HcalModuleType; }
        G4double GetEcalStepTimeLimit() const { return EcalStepTimeLimit; }
        G4double GetHcalStepTimeLimit() const { return HcalStepTimeLimit; }
        G4Material *GetCaloMaterial(MaterialIndex fIndex) const { return MaterialStore[fIndex]; }


        

    private:
        void DefineMaterials();
        DetectorMessenger *fDetectorMessenger;
        CaloUnitParameter EcalUnitParameter;
        CaloUnitParameter HcalUnitParameter;
        G4bool ifcheckOverlaps;
        G4ThreeVector Initial_pos;
        G4double EcalAbsorberThick;
        G4double HcalAbsorberThick;
        G4double EcalPCBThick;
        G4double HcaltriggerThick;
        G4double HcalgraphiteThick;
        G4double HcalPCBThick;
        G4double HcalPCB_Cu_Thick;
        G4double HcalPCB_Abs_gap;
        G4double UpstreamSizeX;
        G4double UpstreamSizeY;
        G4double UpstreamSizeZ;
        G4double IntermediateSizeX;
        G4double IntermediateSizeY;
        G4double IntermediateSizeZ;
        G4double EcalStepTimeLimit;
        G4double HcalStepTimeLimit;
        MaterialIndex HcaltriggerIndex;
        MaterialIndex HCALgraphiteIndex;
        MaterialIndex WorldMatIndex;
        MaterialIndex EcalAbsorberMatIndex;
        MaterialIndex HcalAbsorberMatIndex;
        MaterialIndex EcalPCBMatIndex;
        MaterialIndex HcalPCBMatIndex;
        MaterialIndex HcalPCB_Cu_MatIndex;
        MaterialIndex UpstreamMatIndex;
        MaterialIndex IntermediateMatIndex;
        G4int EcalModuleType;
        G4int HcalModuleType;
        G4int EcalCellNumberX;
        G4int EcalCellNumberY;
        G4int EcalLayerNumber;
        G4int HcalCellNumberX;
        G4int HcalCellNumberY;
        G4int HcalLayerNumber;
        G4int Hcaltriggernplane;
        G4double DownstreamSizeZ;
        G4int DownstreamNum;
        MaterialIndex DownstreamMatIndex;
        G4LogicalVolume *EcalUnitLogical;
        G4LogicalVolume *HcalUnitLogical;
        G4LogicalVolume *EcalSensitiveLogical;
        G4LogicalVolume *HcalSensitiveLogical;
        G4LogicalVolume *HcaltriggerLogical;
        CaloUnitVolume *EcalUnitVolume;
        CaloUnitVolume *HcalUnitVolume;
        std::vector<G4Material *> MaterialStore;
        G4Cache<EcalUnitSD *> fEcalUnitSD;
        G4Cache<HcalUnitSD *> fHcalUnitSD;
        G4Cache<G4GlobalMagFieldMessenger *> fFieldMessenger;
    };
}

#endif
