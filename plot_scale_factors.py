import ROOT
import numpy as np
import matplotlib.pyplot as plt
import json
import mplhep as hep

errorbar_style = {
    'linestyle': 'none',
    'marker': '.',      # display a dot for the datapoint
    'elinewidth': 2,    # width of the errorbar line
    'markersize': 10,   # size of the error marker
    'capsize': 0        # size of the caps on the errorbar (0: no cap fr)
    #'color': 'k',       # black 
}

WtagMP = {
    "16APV":0.845,
    "16":0.842,
    "17":0.810,
    "18":0.82
}

jet_labels = {
    "Hbb": {"tp3":"Top-merged","tp2":"bq-merged","tp1":"Non-merged"},
    "Wqq": {"tp3":"Top-merged","tp2":"W-merged","tp1":"Non-merged"}
}

xvals = {"tp3":[0.25,2.25,4.25],"tp2":[0.5,2.5,4.5],"tp1":[0.75,2.75,4.75]}
xvals_for_ticks = [0.5,2.5,4.5]
xlabels_for_ticks = ['[300,400)','[400,500)','[500,1500)']

lumi = {
  '16APV':'20',
  '16':'17',
  '17':'41',
  '18':'60'
  }

for year in ['16APV','16','17','18']:
    extraText = 'Work in Progress'
    lumiText = lumi[year]+r' fb$^{-1}$'+', 20'+year+' (13 TeV)'
    for tagger,wps in {'Hbb':[0.8,0.98]}.items(): #,'Wqq':[WtagMP[year]]}.items():
        for wp in wps:
            print(f"Making 20{year} plots for {tagger} tagger at working point {wp}")
            scale_factors = {"tp3":[],"tp2":[],"tp1":[]}
            uncertainties = {"tp3":[[],[]],"tp2":[[],[]],"tp1":[[],[]]}
            for pt_cat in [[300,400],[400,500],[500,1500]]:
                print(f"Grabbing histograms for pt cat {pt_cat}")
                ptmin = pt_cat[0]
                ptmax = pt_cat[1]
                with open(f'particlenetmd_sf/plots_postfit/impacts/impacts_particlenetmd_tt1l_{tagger}_{wp}to1._20{year}_pt{ptmin}to{ptmax}.json') as infile:
                    data = json.load(infile)
                    impacts = data["POIs"]
                    for jet_cat,idx in {"tp3":0,"tp2":1,"tp1":2}.items():
                        print(f"Grabbing plots for {jet_cat} jet category")
                        values = impacts[idx]["fit"]
                        sf_nom = values[1]
                        sf_up = values[2]
                        sf_down = values[0]
                        uncert_up = abs(sf_up-sf_nom)
                        uncert_down = abs(sf_down-sf_nom)
                        scale_factors[jet_cat].append(sf_nom)
                        uncertainties[jet_cat][0].append(uncert_down)
                        uncertainties[jet_cat][1].append(uncert_up)
            fig = plt.figure(figsize=(16, 14))
            print("Plotting...")
            plt.errorbar(xvals["tp3"],scale_factors["tp3"],yerr=uncertainties["tp3"],label=jet_labels[tagger]["tp3"], **errorbar_style)
            plt.errorbar(xvals["tp2"],scale_factors["tp2"],yerr=uncertainties["tp2"],label=jet_labels[tagger]["tp2"], **errorbar_style)
            plt.errorbar(xvals["tp1"],scale_factors["tp1"],yerr=uncertainties["tp1"],label=jet_labels[tagger]["tp1"], **errorbar_style)
            plt.legend(fontsize=20)
            plt.xlabel('AK8 $p_T$ (GeV)',size=30,loc='right')
            plt.xticks(xvals_for_ticks,xlabels_for_ticks,fontsize=20)
            plt.ylabel('Scale Factor',size=30,loc='top')
            plt.yticks(fontsize=20)
            plt.ylim(0,2)
            plt.grid(axis='y', linestyle=':')
            
            hep.cms.text(loc=0, text=extraText, fontsize=30)
            hep.cms.lumitext(lumiText, fontsize=30)

            plt.savefig(f'plots/scale_factors_{tagger}_wp_{wp}_20{year}.png',bbox_inches='tight')
            plt.close(fig)

