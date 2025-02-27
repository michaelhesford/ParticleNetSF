#include <string>
#include "configuration.h"

void makeOneDatacard(TString inputname, TString category, TString wpmin, TString wpmax, std::string name_, TString sample, TString era);
void makeOneDatacardTop(TString inputname, TString category, TString wpmin, TString wpmax,TString name, TString sample, TString era);

void makeDatacards(TString era, TString sample, TString category, TString wpmin, TString wpmax) {
  conf::configuration(sample);

  std::vector<TString> name  = conf::name;
  if (sample=="tt1L" || sample=="ttbar1L" || (sample=="ttbar1l") || (sample=="tt1l") ) 
    {
      for (int i0=0; i0<name.size(); ++i0) 
	{
	  makeOneDatacardTop(conf::algo+"_sf",category,wpmin,wpmax,name[i0],sample,era);
	}
    }
}


void makeOneDatacardTop(TString inputname, TString category, TString wpmin, TString wpmax, TString name_, TString sample, TString era) {
  conf::configuration(sample);

  std::cout << "makeData card : " << name_ << "\n"; 

  TString label0;
  TString name = (TString)name_;
  TString inputname_ = (TString)inputname;
  if (inputname_.Contains("particlenetmd"))                                                      { label0 = "particlenetmd"; }
  if (inputname_.Contains("particlenet_"))                                                        { label0 = "particlenet"; }
  
  std::cout << label0 << "\n";
  
  const int dir_err = system("mkdir -p ./"+inputname_+"/fitdir/");
  if (-1 == dir_err) { printf("Error creating directory!n"); exit(1); }

  std::ofstream out("./"+inputname_+"/fitdir/datacard_"+label0+"_tt1l_"+category+"_"+wpmin+"to"+wpmax+"_"+era+"_"+name+".txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  
  // pass 
  TFile *f_p = TFile::Open((TString)inputname+"/"+label0+"_tt1l_"+category+"_"+wpmin+"to"+wpmax+"_"+era+"_"+name+"_templates_p.root","READONLY");
  TH1D  *h_obs_p    = (TH1D*)f_p->Get("data_obs"); 
  TH1D  *h_top_p1_p = (TH1D*)f_p->Get("tp1");
  TH1D  *h_top_p2_p = (TH1D*)f_p->Get("tp2");
  TH1D  *h_top_p3_p = (TH1D*)f_p->Get("tp3");
  TH1D  *h_other_p  = (TH1D*)f_p->Get("other");
  // fail
  TFile *f_f = TFile::Open((TString)inputname+"/"+label0+"_tt1l_"+category+"_"+wpmin+"to"+wpmax+"_"+era+"_"+name+"_templates_f.root","READONLY");
  TH1D  *h_obs_f    = (TH1D*)f_f->Get("data_obs");   
  TH1D  *h_top_p1_f = (TH1D*)f_f->Get("tp1");
  TH1D  *h_top_p2_f = (TH1D*)f_f->Get("tp2");
  TH1D  *h_top_p3_f = (TH1D*)f_f->Get("tp3");
  TH1D  *h_other_f  = (TH1D*)f_f->Get("other");
  
  std::cout << "imax 2  number of channels\n";
  std::cout << "jmax 3  number of processes -1\n";
  std::cout << "kmax *  number of nuisance parameters (sources of systematical uncertainties)\n";
  std::cout << "------------\n";

  std::cout << "shapes  *  pass  " << (TString)inputname << "/"+label0+"_tt1l_"+category+"_"+wpmin+"to"+wpmax+"_"+era+"_" << name << "_templates_p.root  $PROCESS $PROCESS_$SYSTEMATIC\n";
  std::cout << "shapes  *  fail  " << (TString)inputname << "/"+label0+"_tt1l_"+category+"_"+wpmin+"to"+wpmax+"_"+era+"_" << name << "_templates_f.root  $PROCESS $PROCESS_$SYSTEMATIC\n";
  std::cout << "------------\n";


  std::cout << "bin             pass fail    \n";
  std::cout << "observation      " << h_obs_p->Integral(1,h_obs_p->GetNbinsX()) << " " << h_obs_f->Integral(1,h_obs_f->GetNbinsX()) << "\n";
  std::cout << "------------\n";
  std::cout << "# now we list the expected events for signal and all backgrounds in that bin\n";
  std::cout << "# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n";
  std::cout << "# then we list the independent sources of uncertainties, and give their effect (syst. error)\n";
  std::cout << "# on each process and bin\n";
  std::cout << "bin             pass pass pass pass    fail fail fail fail \n";
  std::cout << "process         tp3  tp2  tp1 other     tp3  tp2  tp1 other \n";  
  std::cout << "process         4 3 6 -7      4 3 6 -7  \n";
  std::cout << "rate            -1 -1 -1 -1      -1 -1 -1 -1  \n"; 
  std::cout << "------------\n";


  std::cout << "lumi            lnN      1.012 1.012 1.012 1.012     1.012 1.012 1.012 1.012 \n";
  std::cout << "\n";
    
  std::cout << "tp3_xsec     lnN      1.05 - - -    1.05 - - - \n";
  std::cout << "tp2_xsec     lnN      - 1.05 - -    - 1.05 - - \n";
  std::cout << "tp1_xsec     lnN      - - 1.05 -    - - 1.05 - \n";
  std::cout << "other_xsec   lnN      - - - 2.00    - - - 2.00 \n";
  
  std::cout << "\n";

  std::cout << "tp3JMS         shape    1 - - -     1 - - - \n";
  std::cout << "tp2JMS         shape    - 1 - -     - 1 - - \n";
  std::cout << "tp1JMS         shape    - - 1 -     - - 1 - \n";
  std::cout << "otherJMS         shape    - - - 1     - - - 1 \n";
  
  std::cout << "tp3JMR         shape    1 - - -     1 - - - \n";
  std::cout << "tp2JMR         shape    - 1 - -     - 1 - - \n";
  std::cout << "tp1JMR         shape    - - 1 -     - - 1 - \n";
  std::cout << "otherJMR         shape    - - - 1     - - - 1 \n";
  
  std::cout << "L1PreFiringWeight         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "TptReweight         shape    1 1 1 -     1 1 1 - \n";
  std::cout << "Pdfweight         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "Pileup         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "JES         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "JER         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "UE         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "ISRunc_qcd         shape    1 1 1 -     1 1 1 - \n";
  std::cout << "FSRunc_qcd         shape    1 1 1 -     1 1 1 - \n";
  std::cout << "ISRunc_ewk         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "FSRunc_ewk         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "QCDscale_uncert_qcd         shape    1 1 1 -     1 1 1 - \n";
  std::cout << "QCDscale_uncert_ewk         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuonIDWeight_uncert_stat         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuonIDWeight_uncert_syst         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuonRecoWeight_uncert_stat         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuonRecoWeight_uncert_syst         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuoTrigSF_lowPt         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "MuoTrigSF_highPt         shape    1 1 1 1     1 1 1 1 \n";

  /*
  std::cout << "met         shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "lhescalemuf shape    1 1 1 1     1 1 1 1 \n";
  std::cout << "lhescalemur shape    1 1 1 1     1 1 1 1 \n";
  //std::cout << "lhepdf      shape    1 1 1 1     1 1 1 1 \n";
  
  //  std::cout << "herwig         shape    1 1 1 -     1 1 1 -\n";
  */

  std::cout << "norm_top    rateParam    pass    tp3      1   [0.,10.]\n";
  std::cout << "norm_top    rateParam    fail    tp3      1   [0.,10.]\n";
  std::cout << "norm_top    rateParam    pass    tp2      1   [0.,10.]\n";
  std::cout << "norm_top    rateParam    fail    tp2      1   [0.,10.]\n";
  std::cout << "norm_top    rateParam    pass    tp1      1   [0.,10.]\n";
  std::cout << "norm_top    rateParam    fail    tp1      1   [0.,10.]\n";
  /*
  std::cout << "norm_other    rateParam    pass    other      1   [0.,10.]\n";
  std::cout << "norm_other    rateParam    fail    other      1   [0.,10.]\n";
  std::cout << "norm_other    rateParam    pass    qcd      1   [0.,10.]\n";
  std::cout << "norm_other    rateParam    fail    qcd      1   [0.,10.]\n";
  */
  std::cout << "\n";

  std::cout << "*  autoMCStats  0\n";

}

