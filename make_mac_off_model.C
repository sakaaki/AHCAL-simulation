#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <vector>
int make_mac_off_model(){
    std::string model_light[3] = {"EPOSLHC","SIBYLL","QGSJET"};
    std::string model_charm[3] = {"central","max","min"};
    for (int j = 0; j<3;j++){
        for( int i =0 ; i<10 ;i++){
            std::ofstream ofs(Form("./mac/run_off_AHCAL0mmW_%s_%d.mac",model_charm[j].c_str(),i));
            ofs<<"/control/verbose 2"<<std::endl;
            ofs<<"/run/verbose 1"<<std::endl;
            ofs<<"/event/verbose 0"<<std::endl;
            ofs<<"/tracking/verbose 0"<<std::endl;
            ofs<<"/generator/inputFileName /eos/user/a/asakai/genie_data/faser_off_AHCAL0mmW_charm."<<model_charm[j]<<".1000ifb."<<i<<".gfaser.root"<<std::endl;
            ofs<<"/generator/FixedPrimaryVertexPosition false"<<std::endl;
            ofs<<"/run/initialize"<<std::endl;
            TFile * file = new TFile(Form("/eos/user/a/asakai/genie_data/faser_off_AHCAL0mmW_charm.%s.1000ifb.%d.gfaser.root",model_charm[j].c_str(),i),"READ");
            TTree * tree = (TTree*)file->Get("gFaser");
            int N = tree->GetEntriesFast();
            ofs<<"/run/beamOn "<<N<<std::endl;
        }
    }
    for (int j = 0; j<3;j++){
        for( int i =10 ; i<20 ;i++){
            std::ofstream ofs(Form("./mac/run_off_AHCAL0mmW_%s_%d.mac",model_light[j].c_str(),i));
            ofs<<"/control/verbose 2"<<std::endl;
            ofs<<"/run/verbose 1"<<std::endl;
            ofs<<"/event/verbose 0"<<std::endl;
            ofs<<"/tracking/verbose 0"<<std::endl;
            ofs<<"/generator/inputFileName /eos/user/a/asakai/genie_data/faser_off_AHCAL0mmW_light."<<model_light[j]<<".1000ifb."<<i<<".gfaser.root"<<std::endl;
            ofs<<"/generator/FixedPrimaryVertexPosition false"<<std::endl;
            ofs<<"/run/initialize"<<std::endl;
            TFile * file = new TFile(Form("/eos/user/a/asakai/genie_data/faser_off_AHCAL0mmW_light.%s.1000ifb.%d.gfaser.root",model_light[j].c_str(),i),"READ");
            TTree * tree = (TTree*)file->Get("gFaser");
            int N = tree->GetEntriesFast();
            ofs<<"/run/beamOn "<<N<<std::endl;
        }
    }
    return 0;
}