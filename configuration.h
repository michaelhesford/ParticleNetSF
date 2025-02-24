#ifndef CONFIGURATION_INCLUDE
#define CONFIGURATION_INCLUDE

#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include "TString.h"

namespace conf {

  struct process {
    
    TString name;
    TString legend_name;
    int     color;
    
  } qcd, tp2, tp3, tp1, other;
  
  TString brX; int binsX; float minX, maxX;
  TString brY; int binsY; float minY, maxY;
  TString algo;
  TString score_def; 
  TString category;
  
  std::vector<TString> name; 
  std::vector<double>  ptmin; 
  std::vector<double>  ptmax;
  std::vector<TString> processes;
  std::vector<TString> process_names;
  std::vector<TString> syst;
  std::vector<TString> processes_in;

  double zmin;
  double zmax;

  TString path_2016;
  TString path_2017;
  TString path_2018;

  TString jetCone;

  void configuration(TString sample) {

    TString jet_prefix;

    // =================== area to modify - tune ===================== //
   
    if ( (sample == "tt1L") || (sample=="ttbar1L") || (sample=="ttbar1l") || (sample == "tt1l") || (sample == "tt1lw") ) {
      path_2016 = "/eos/uscms/store/user/pakontax/ParticleNET_UL_NanoV9_For_Copy/2016/from_Huilin/20211212_NanoAODv9_ak8_muon_2015/";
      //path_2016 = "/eos/uscms/store/user/pakontax/ParticleNET_UL_NanoV9_For_Copy/2016/from_Huilin/20211212_NanoAODv9_ak8_muon_2016/";
      path_2017 = "/eos/uscms/store/user/pakontax/ParticleNET_UL_NanoV9_For_Copy/2017/from_Huilin/20211212_NanoAODv9_ak8_muon_2017/";
      path_2018 = "/eos/uscms/store/user/pakontax/ParticleNET_UL_NanoV9_For_Copy/2018/from_Huilin/20211212_NanoAODv9_ak8_muon_2018/";
      
      jetCone    = "ak8";
      jet_prefix = "fj_1_";
      
      brX = jet_prefix+"sdmass"; 
      brY = jet_prefix+"pt";
      //category = "Wqq"; //W-Tagger
      category = "Hbb"; //H-Tagger
 
     // for make2DTemplates
      processes.push_back("ttbar-powheg"); process_names.push_back("tt"); 
      processes.push_back("singletop");    process_names.push_back("st");
      processes.push_back("w");            process_names.push_back("wj");
      processes.push_back("z");            process_names.push_back("zj");
      processes.push_back("drell-yan");    process_names.push_back("dy");
      processes.push_back("qcd-mg");       process_names.push_back("qcd");

      //processes.push_back("ttv");          process_names.push_back("ttv");
      //processes.push_back("diboson");      process_names.push_back("vv");

      // keep this format - pretify later - need to keep this order
      processes_in.push_back("tt_p3"); processes_in.push_back("st_p3"); processes_in.push_back("ttv_p3");
      processes_in.push_back("tt_p2"); processes_in.push_back("st_p2"); processes_in.push_back("ttv_p2"); 
      processes_in.push_back("tt_p1"); processes_in.push_back("st_p1"); processes_in.push_back("ttv_p1");
      processes_in.push_back("wj"); processes_in.push_back("zj"); processes_in.push_back("dy"); processes_in.push_back("db"); //processes_in.push_back("ttv"); processes_in.push_back("tth"); processes_in.push_back("db");
      processes_in.push_back("qcd"); 

      // list of systematic uncertainties
      syst.push_back("_"); syst.push_back("Pileup"); syst.push_back("TptReweight");
      syst.push_back("Pdfweight"); syst.push_back("JES"); syst.push_back("JER"); syst.push_back("JMS"); syst.push_back("JMR");
      syst.push_back("ISRunc_qcd"); syst.push_back("FSRunc_qcd"); syst.push_back("ISRunc_ewk"); syst.push_back("FSRunc_ewk");
      syst.push_back("ElectronIDWeight"); syst.push_back("ElectronRecoWeight"); syst.push_back("QCDscale_uncert_qcd"); syst.push_back("QCDscale_uncert_ewk");
      syst.push_back("MuonIDWeight_uncert_stat"); syst.push_back("MuonIDWeight_uncert_syst");
      syst.push_back("MuonRecoWeight_uncert_stat"); syst.push_back("MuonRecoWeight_uncert_syst"); 
      syst.push_back("UE"); syst.push_back("MuoTrigSF_lowPt"); syst.push_back("MuoTrigSF_highPt");
      //syst.push_back("L1PreFiringWeight"); //remove for 2018
    }


    //algo      = "particlenet"; //Nominal
    algo      = "particlenetmd";  //MD
    //score_def = jet_prefix+"ParticleNet_TvsQCD"; 
    //score_def = jet_prefix+"ParticleNet_WvsQCD"; //W-Nominal
    score_def = "(fj_1_ParticleNetMD_Xcc+fj_1_ParticleNetMD_Xqq)/(fj_1_ParticleNetMD_Xcc+fj_1_ParticleNetMD_Xqq+fj_1_ParticleNetMD_QCD)"; //W-MD
    binsX = 20; minX = 50;  maxX = 250.;
    //binsY = 40; minY = 200; maxY = 1200.; //Top-Tagger
    binsY = 24; minY = 300; maxY = 1500.; //W,H-Taggers
       
    // Hbb
    //zmin = 0.2; zmax = 1;
    //name.push_back("pt300to400"); ptmin.push_back(300.); ptmax.push_back(400.);
    //name.push_back("pt400to600"); ptmin.push_back(400.); ptmax.push_back(600.);
    //name.push_back("pt600to1500"); ptmin.push_back(600.); ptmax.push_back(1500.);    
 
    //W
    zmin = 0; zmax = 1;
    name.push_back("pt300to400"); ptmin.push_back(300.); ptmax.push_back(400.);
    name.push_back("pt400to500"); ptmin.push_back(400.); ptmax.push_back(500.);
    name.push_back("pt500to1500"); ptmin.push_back(500.); ptmax.push_back(1500.);  
    
    //name.push_back("pt300to1500"); ptmin.push_back(300.); ptmax.push_back(1500.);
 
    // =================== end of area to modify - tune ===================== //

    qcd.name        = "qcd";
    qcd.legend_name = "QCD Multijet";
    qcd.color       = kOrange-3;
   
    tp3.name        = "tp3";
    tp3.legend_name = "Top-merged";
    tp3.color       = kAzure+5;
 
    tp2.name        = "tp2";
    tp2.legend_name = "bq-merged";
    tp2.color       = 590;
    
    tp1.name        = "tp1";
    tp1.legend_name = "Non-merged";
    tp1.color       = 595;
    
    other.name        = "other";
    other.legend_name = "Other SM";
    other.color       = kGreen-2;
 
  }   

  TString convertFloatToTString(float input) {
    ostringstream tmpInputStr;
    tmpInputStr << input;
    TString inputStr = tmpInputStr.str();
    return inputStr;
  }

  std::string convertTStringToString(TString input) {
    std::string output;
    output = (string)input;
    return output;
  }

} 

#endif
