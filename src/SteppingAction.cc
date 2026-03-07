#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <G4RunManager.hh>
#include "G4EventManager.hh"
#include <fstream>

SteppingAction::SteppingAction() : G4UserSteppingAction() {
    fEventAction = nullptr;
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    // G4double zplane = 7382.2 * mm;
    fEventAction = const_cast<SimCalModule::EventAction*>(static_cast<const SimCalModule::EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));
    if (!fEventAction){
        G4cout<<"eventactioneeror"<<G4endl;
    }
    G4StepPoint* preStep = step->GetPreStepPoint();
    G4StepPoint* postStep = step->GetPostStepPoint();

    G4ThreeVector prePos = preStep->GetPosition();
    G4ThreeVector postPos = postStep->GetPosition();
    int numuCC = fEventAction->GetfNumuCClabel();
    int primary_trackid = fEventAction->GetPrimary_trackid();
    int D_id = fEventAction->GetfD_id();
    auto track = step->GetTrack();
    G4int trackID = track->GetTrackID();
    // if (numuCC > 0) {
    //     if (trackID == D_id) {
    //         if (track->GetTrackStatus() == fStopAndKill) { 
    //             G4cout << "D meson interaction at position: " 
    //                    << track->GetPosition() / mm << " mm" << G4endl;
    //             const G4VProcess* process = track->GetCreatorProcess();
    //             if (process) {
    //                 G4cout << "D meson disappeared due to: " << process->GetProcessName() << G4endl;
    //             }
    //             // 生成された二次粒子（崩壊 or 非弾性散乱の結果）を取得
    //             const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
    //             if (!secondaries->empty()) {
    //                 G4cout << "Outgoing particles from D meson reaction:" << G4endl;
    //                 for (const G4Track* secTrack : *secondaries) {
    //                     G4cout << " - " << secTrack->GetDefinition()->GetParticleName()
    //                            << " (Momentum: " << secTrack->GetMomentum().mag() / GeV << " GeV)"
    //                            << G4endl;
    //                 }
    //             }
    //         }
    //     }
    // }
    //G4double start_zplane = 6864.165 * mm;
    //G4double start_zplane = 6983.765 * mm; //100mmSteal20
    G4double start_zplane = 5575.1 * mm; //GS-HCAL
    G4double tau_plane = 5610.0 * mm;
    // 519.6
    //for (G4double zplane = start_zplane; zplane <= 9931.915 *mm; zplane +=519.6*mm){
    //for (G4double zplane = start_zplane; zplane <= 9176.365 *mm; zplane +=109.63*mm){    //100mmSteel
    for (G4double zplane = start_zplane; zplane <= 6880.7 *mm; zplane +=27.2*mm){    //GS-HCAL
    if (prePos.z() < zplane && postPos.z() > zplane && track->GetParticleDefinition()->GetPDGCharge() !=0 ) {
        int pdgID = track->GetParticleDefinition()->GetPDGEncoding();
        G4int parentID = track->GetParentID();
        G4double charge = track->GetParticleDefinition()->GetPDGCharge();
        G4double prepoint_time = preStep->GetGlobalTime();
        G4double postpoint_time = postStep->GetGlobalTime();
        G4double gTime = (prepoint_time *(postPos.z() - zplane) +
                      postpoint_time *(zplane - prePos.z())) / (postPos.z() - prePos.z());
        G4double energy = track->GetTotalEnergy() / GeV;
        G4double px = track->GetMomentum().x() / GeV;
        G4double py = track->GetMomentum().y() / GeV;
        G4double pz = track->GetMomentum().z() / GeV;
        G4double vx = prePos.x() + (postPos.x() - prePos.x()) * (zplane - prePos.z()) / (postPos.z() - prePos.z()) / mm;
        G4double vy = prePos.y() + (postPos.y() - prePos.y()) * (zplane - prePos.z()) / (postPos.z() - prePos.z()) / mm;
        G4double vz = zplane / mm;        
        int primary_Dmeson = 0;
        if (trackID == primary_trackid) {
            primary_Dmeson = 1;
        }
        if (numuCC > 0) {
            if (parentID == D_id) {
                primary_Dmeson = 2;
                G4cout<<"D meson decay to muon"<<G4endl;
            }
        }
        fEventAction->AddPlaneParticle(pdgID, charge, gTime, px, py, pz,energy,parentID,trackID, vx, vy, vz, primary_Dmeson);
    }
    }
    // if (prePos.z() <tau_plane && postPos.z() > tau_plane && track->GetParticleDefinition()->GetPDGCharge() !=0 ) {
    //     int pdgID = track->GetParticleDefinition()->GetPDGEncoding();
    //     G4int parentID = track->GetParentID();
    //     G4double charge = track->GetParticleDefinition()->GetPDGCharge();
    //     G4double prepoint_time = preStep->GetGlobalTime();
    //     G4double postpoint_time = postStep->GetGlobalTime();
    //     G4double gTime = (prepoint_time *(postPos.z() - tau_plane ) +
    //                   postpoint_time *(tau_plane  - prePos.z())) / (postPos.z() - prePos.z());
    //     G4double energy = track->GetTotalEnergy() / GeV;
    //     G4double px = track->GetMomentum().x() / GeV;
    //     G4double py = track->GetMomentum().y() / GeV;
    //     G4double pz = track->GetMomentum().z() / GeV;
    //     G4double vx = prePos.x() + (postPos.x() - prePos.x()) * (tau_plane  - prePos.z()) / (postPos.z() - prePos.z()) / mm;
    //     G4double vy = prePos.y() + (postPos.y() - prePos.y()) * (tau_plane  - prePos.z()) / (postPos.z() - prePos.z()) / mm;
    //     G4double vz = tau_plane  / mm;        
    //     int primary_Dmeson = 0;
    //     if (trackID == primary_trackid) {
    //         primary_Dmeson = 1;
    //     }
    //     if (numuCC > 0) {
    //         if (parentID == D_id) {
    //             primary_Dmeson = 2;
    //             G4cout<<"D meson decay to muon"<<G4endl;
    //         }
    //     }
    //     fEventAction->AddPlaneParticle(pdgID, charge, gTime, px, py, pz,energy,parentID,trackID, vx, vy, vz, primary_Dmeson);
    // }
}