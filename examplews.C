//https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part3/nonstandard/#rooparametrichist-gamman-for-shapes

void examplews(){
  // As usual, load the combine library to get access to the RooParametricHist
  gSystem->Load("libHiggsAnalysisCombinedLimit.so");

  // Output file and workspace
  TFile *fOut = new TFile("param_ws.root","RECREATE");
  RooWorkspace wspace("wspace","wspace");

  double nbins = 4;
  double xmin=200.;
  double xmax=1000.;

  RooRealVar met("met","E_{T}^{miss}",200,xmin,xmax);
  RooArgList vars(met);

  double xbins[5] = {200.,400.,600.,800.,1000.};

  // ---------------------------- CONTROL REGION 1 -------------------------------------------------------------------//
  TH1F data_th1("data_obs_CR1","Data observed in signal region",nbins,xbins);
  data_th1.SetBinContent(1,95);
  data_th1.SetBinContent(2,55);
  data_th1.SetBinContent(3,30);
  data_th1.SetBinContent(4,5);
  RooDataHist data_hist("data_obs_CR1","Data observed",vars,&data_th1);
  wspace.import(data_hist);

  RooRealVar bin1_CR1("bkg_CR1_bin1","Background yield in signal region, bin 1",95,0,500);
  RooRealVar bin2_CR1("bkg_CR1_bin2","Background yield in signal region, bin 2",55,0,500);
  RooRealVar bin3_CR1("bkg_CR1_bin3","Background yield in signal region, bin 3",30,0,500);
  RooRealVar bin4_CR1("bkg_CR1_bin4","Background yield in signal region, bin 4",5,0,500);
  RooArgList bkg_CR1_bins;
  bkg_CR1_bins.add(bin1_CR1);
  bkg_CR1_bins.add(bin2_CR1);
  bkg_CR1_bins.add(bin3_CR1);
  bkg_CR1_bins.add(bin4_CR1);

  RooParametricHist p_bkg("bkg_CR1", "Background PDF in signal region",met,bkg_CR1_bins,data_th1);
  RooAddition p_bkg_norm("bkg_CR1_norm","Total Number of events from background in signal region",bkg_CR1_bins);

  // ---------------------------- CONTROL REGION 2 -------------------------------------------------------------------//
  TH1F data_th1_2("data_obs_CR2","Data observed in signal region",nbins,xbins);
  data_th1_2.SetBinContent(1,99);
  data_th1_2.SetBinContent(2,51);
  data_th1_2.SetBinContent(3,26);
  data_th1_2.SetBinContent(4,9);
  RooDataHist data_hist_CR2("data_obs_CR2","Data observed",vars,&data_th1_2);
  wspace.import(data_hist_CR2);

  RooRealVar bin1_CR2("bkg_CR2_bin1","Background yield in signal region, bin 1",100,0,500);
  RooRealVar bin2_CR2("bkg_CR2_bin2","Background yield in signal region, bin 2",50,0,500);
  RooRealVar bin3_CR2("bkg_CR2_bin3","Background yield in signal region, bin 3",25,0,500);
  RooRealVar bin4_CR2("bkg_CR2_bin4","Background yield in signal region, bin 4",10,0,500);
  RooArgList bkg_CR2_bins;
  bkg_CR2_bins.add(bin1_CR2);
  bkg_CR2_bins.add(bin2_CR2);
  bkg_CR2_bins.add(bin3_CR2);
  bkg_CR2_bins.add(bin4_CR2);

  RooParametricHist p_bkg_CR2("bkg_CR2", "Background PDF in signal region",met,bkg_CR2_bins,data_th1_2);
  RooAddition p_bkg_CR2_norm("bkg_CR2_norm","Total Number of events from background in signal region",bkg_CR2_bins);

  // -------------------------------------------------------------------------------------------------------------//
  // ---------------------------- SIGNAL REGION -----------------------------------------------------------------//
  TH1F data_SRth1("data_obs_SR","Data observed in control region",nbins,xbins);

  data_SRth1.SetBinContent(1,200);
  data_SRth1.SetBinContent(2,100);
  data_SRth1.SetBinContent(3,50);
  data_SRth1.SetBinContent(4,20);

  RooDataHist data_SRhist("data_obs_SR","Data observed",vars,&data_SRth1);
  wspace.import(data_SRhist);

  RooRealVar TF("TF","Trasnfer factor",1.);

  // First RooParametricHisto from Control Region 1
  RooFormulaVar SRbin1("bkg_SR_bin1","Background yield in control region, bin 1","@0*@1",RooArgList(TF,bin1_CR1));
  RooFormulaVar SRbin2("bkg_SR_bin2","Background yield in control region, bin 2","@0*@1",RooArgList(TF,bin2_CR1));
  RooFormulaVar SRbin3("bkg_SR_bin3","Background yield in control region, bin 3","@0*@1",RooArgList(TF,bin3_CR1));
  RooFormulaVar SRbin4("bkg_SR_bin4","Background yield in control region, bin 4","@0*@1",RooArgList(TF,bin4_CR1));

  RooArgList bkg_SR_bins;
  bkg_SR_bins.add(SRbin1);
  bkg_SR_bins.add(SRbin2);
  bkg_SR_bins.add(SRbin3);
  bkg_SR_bins.add(SRbin4);
  RooParametricHist p_SRbkg("bkg_SR", "Background PDF in control region",met,bkg_SR_bins,data_th1);
  RooAddition p_SRbkg_norm("bkg_SR_norm","Total Number of events from background in control region",bkg_SR_bins);

  // Second RooParametricHisto from Control Region 2
  RooFormulaVar SR2bin1("bkg_SR2_bin1","Background yield in control region, bin 1","@0*@1",RooArgList(TF,bin1_CR2));
  RooFormulaVar SR2bin2("bkg_SR2_bin2","Background yield in control region, bin 2","@0*@1",RooArgList(TF,bin2_CR2));
  RooFormulaVar SR2bin3("bkg_SR2_bin3","Background yield in control region, bin 3","@0*@1",RooArgList(TF,bin3_CR2));
  RooFormulaVar SR2bin4("bkg_SR2_bin4","Background yield in control region, bin 4","@0*@1",RooArgList(TF,bin4_CR2));

  RooArgList bkg_SR2_bins;
  bkg_SR2_bins.add(SR2bin1);
  bkg_SR2_bins.add(SR2bin2);
  bkg_SR2_bins.add(SR2bin3);
  bkg_SR2_bins.add(SR2bin4);
  RooParametricHist p_SR2bkg("bkg_SR2", "Background PDF in control region",met,bkg_SR2_bins,data_th1);
  RooAddition p_SR2bkg_norm("bkg_SR2_norm","Total Number of events from background in control region",bkg_SR2_bins);

  // SIGNAL of the signal region
  TH1F signal_th1("signal_SR2","Signal expected in signal region",nbins,xbins);

  signal_th1.SetBinContent(1,1);
  signal_th1.SetBinContent(2,2);
  signal_th1.SetBinContent(3,3);
  signal_th1.SetBinContent(4,8);
  RooDataHist signal_hist("signal","Data observed",vars,&signal_th1);
  wspace.import(signal_hist);
  // -------------------------------------------------------------------------------------------------------------//

  // -------------------------------------------------------------------------------------------------------------//
  // ---------------------------- MultiPdf -----------------------------------------------------------------------//
  RooCategory cat("pdf_index","Index of Pdf which is active");
  RooArgList mypdfs;
  mypdfs.add(p_SRbkg);
  mypdfs.add(p_SR2bkg);
  RooMultiPdf multipdf("roomultipdf","RooMultiPdf in the signal region", cat, mypdfs);
  RooFormulaVar norm("roomultipdf_norm","Number of background events","(1-@0)*@1 + @0*@2",RooArgList(cat, p_SRbkg_norm, p_SR2bkg_norm));

  // import the pdfs
  wspace.import(cat);
  wspace.import(multipdf);
  wspace.import(norm,RooFit::RecycleConflictNodes());
  wspace.import(p_bkg);
  wspace.import(p_bkg_norm,RooFit::RecycleConflictNodes());
  wspace.import(p_bkg_CR2);
  wspace.import(p_bkg_CR2_norm,RooFit::RecycleConflictNodes());
  fOut->cd();
  wspace.Write();
  
  // Clean up
  fOut->Close();
  fOut->Delete();
}
