//{

//    if(Recompute) {
//        MPAFDisplay md;
 
//        bool * rtmp= const_cast<bool*> pr;
//        *rtmp = false;

//    }
//    else 
//    md.refresh();

MPAFDisplay md;

void susy3l_manual() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="template3L_skimmed"; //was treeName in LUNE susy_cut_lowpt
    string fileList="template3L_skimmed"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    string obs ="zpeak";    //njets, nbjets, met, ht, lep, zpeak, mt2, pt, mll
    string sigs = "none"; 

    //observables **********************
    //string obs[6]={"","","","","",""};
    //md.dp.setObservables("Zmass");
    //md.dp.setObservables("deltaR_elmu");
    //md.dp.setObservables("BR_NJets");
    //md.dp.setObservables("BR_NBJets");
    //md.dp.setObservables("BR_HT");
    //md.dp.setObservables("BR_MET");
    //md.dp.setObservables("SR_NJets");
    //md.dp.setObservables("SR_NBJets");
    //md.dp.setObservables("SR_HT");
    //md.dp.setObservables("SR_MET");


    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    //double rangeX[2]={0,7};
    int xDiv[3]={8,6,0};
    int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
    bool logYScale=false;
    bool overFlowBin=true;
    bool underFlowBin=false;
    bool showDMCRatio=true;
    bool showGrid=false;
    float markerSize=0.8;
    float lineWidth=2;

    bool summedSignal=false;
    bool stacking=true;

    bool cmsPrel=true;

    float xt=0.68;
    float yt=0.48;
    float st=0.039;
    string addText="";


    if(obs == "njets"){
        md.dp.setObservables("BR_NJets");
        int binning=1;
        double rangeX[2]={0,7};
    }
    if(obs == "nbjets"){
        md.dp.setObservables("BR_NBJets");
        int binning=1;
        double rangeX[2]={0,5};
    }
    if(obs == "met"){
        md.dp.setObservables("BR_MET");
        int binning=50;
        double rangeX[2]={0,500};
    }
    if(obs == "ht"){
        md.dp.setObservables("BR_HT");
        int binning=50;
        double rangeX[2]={0,800};
    }
    if(obs == "lep"){
        md.dp.setObservables("mu_multiplicity");
        md.dp.setObservables("el_multiplicity");
        md.dp.setObservables("tau_multiplicity");
        md.dp.setObservables("lep_multiplicity");
        int binning=1;
        double rangeX[2]={0,7};
        //bool logYScale=true;
    }
    if(obs == "zpeak"){
        md.dp.setObservables("Zmass");
        int binning=3;
        double rangeX[2]={0,200};
    }
    if(obs == "mt2"){
        md.dp.setObservables("MT2");
        int binning=10;
        double rangeX[2]={0,400};
        bool logYScale=true;
    }
    if(obs == "pt"){
        md.dp.setObservables("pt_1st_lepton");
        md.dp.setObservables("pt_2nd_lepton");
        md.dp.setObservables("pt_3rd_lepton");
        int binning=4;
        double rangeX[2]={0,200};
        bool logYScale=false;
    }
    if(obs == "mll"){
        md.dp.setObservables("lowMll");
        int binning=2;
        double rangeX[2]={0,400};
        bool logYScale=true;
    }



    //string autoBinFile="susybinninghigh";
    //md.dp.loadAutoBinning(autoBinFile);

    //Systematic uncertainties ********************************
    bool addSystematics=true;
  
    bool mcStatSyst=true;
    string systSources="";

    bool uncDet=false;

    string Norm="";
  
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=42; //pb-1 19470
    float energy=13; //TeV

    bool useXS=false;

    map<string,float> LumisXS;

    //cross sections   
    
    //Drell-Yan
    //LumisXS[ "DYJetsToLL_M-50_13TeV-madgraph-pythia8"                       ] = 2829164 / (6024             );
    LumisXS[ "DYJetsToLL_M50_HT100to200"                ] = 4054159 / ( 194.3   * 1.27  );
    LumisXS[ "DYJetsToLL_M50_HT200to400"                ] = 4666496 / (  52.24  * 1.27  );
    LumisXS[ "DYJetsToLL_M50_HT400to600"                ] = 4931372 / (   6.546 * 1.27  );
    LumisXS[ "DYJetsToLL_M50_HT600toInf"                ] = 4493574 / (   2.179 * 1.27  );

    //Higgs->ZZ
    LumisXS[ "GGHZZ4L"                                  ] =  204684 / (0.01212192       );  // cross-section: 43.92*2.76E-04
    LumisXS[ "TTH"                                      ] =  199700 / (0.5085           );
    
    //signal
    LumisXS[ "SMS_T1tttt_2J_mGl1200_mLSP800"            ] =  100322 / (0.0856418        * 20  );
    LumisXS[ "SMS_T1tttt_2J_mGl1500_mLSP100"            ] =  105679 / (0.0141903        * 20  );
    LumisXS[ "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"] =   52499 / (0.3254           * 20  );
    LumisXS[ "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep" ] =   19688 / (0.012135670848   * 20  );
    LumisXS[ "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep" ] =   19228 / (0.011385976896   * 20  );
    LumisXS[ "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"   ] =   24510 / (0.002830290206   * 20  );
    LumisXS[ "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"    ] =   23300 / (0.000468961034   * 20  );
    LumisXS[ "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep" ] =   40268 / (0.004081667072   * 20  );
    LumisXS[ "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep" ] =   39202 / (0.003795325632   * 20  );
    LumisXS[ "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"   ] =   47130 / (0.000891017287   * 20  );
    LumisXS[ "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"    ] =   45307 / (0.000147635881   * 20  );
   
    //top 
    LumisXS[ "TBarToLeptons_sch"                        ] =  250000 / (1.34784          );  // 4.16*0.108*3
    LumisXS[ "TBarToLeptons_tch"                        ] = 1999800 / (26.23428         );  // 80.97*0.108*3
    LumisXS[ "TBar_tWch"                                ] =  971800 / (35.6             ); 
    LumisXS[ "TTJets"                                   ] =25446993 / (809.1            );
    LumisXS[ "TToLeptons_sch"                           ] =  500000 / (2.3328           );  // 7.20*0.108*3
    LumisXS[ "TToLeptons_tch"                           ] = 3991000 / (44.0802          );  // 136.05*0.108*3
    LumisXS[ "T_tWch"                                   ] =  986100 / (35.6             );  // 35.6
   
    //TTV 
    LumisXS[ "TTWJets"                                  ] =  246521 / (0.6647           );
    LumisXS[ "TTZJets"                                  ] =  249275 / (0.8565           );
      
    //LumisXS[ "WJetsToLNu_13TeV-madgraph-pythia8-tauola"                    ] = 10017462 / (20508.9        ); 
    LumisXS[ "WJetsToLNu_HT100to200"                    ] = 5262265  / (1817.0   * 1.23 );
    LumisXS[ "WJetsToLNu_HT200to400"                    ] = 4936077  / ( 471.6   * 1.23 );
    LumisXS[ "WJetsToLNu_HT400to600"                    ] = 4640594  / (  55.61  * 1.23 );
    LumisXS[ "WJetsToLNu_HT600toInf"                    ] = 237484   / (  18.81  * 1.23 );

    //Diboson
    LumisXS[ "WZJetsTo3LNu"                             ] =   237484 / (2.29            );
    LumisXS[ "ZZTo4L"                                   ] =  1958600 / (0.3231          );  // cross-section 31.8*(3*0.0336)*(3*0.0336)
    


    //via XSect
  
    map<string,float> KFactors;
    // if( md.isInitStatus() )
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    //===============================================================
    // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
    //if( md.isInitStatus() ) {
    
    md.anConf.addSample( "WZJetsTo3LNu"                     ,  "WZ+ZZ"              , kGreen    );
    md.anConf.addSample( "ZZTo4L"                           ,  "WZ+ZZ"              , kGreen    );

    md.anConf.addSample( "TTZJets"                          ,  "t#bar{t}Z"          , kBlue     );

    md.anConf.addSample( "TTWJets"                          ,  "t#bar{t}W"          , kYellow   );

    md.anConf.addSample( "GGHZZ4L"                          ,  "rare SM"            , kCyan     );
    md.anConf.addSample( "TTH"                              ,  "rare SM"             , kCyan      );

  //Drell-Yan
    md.anConf.addSample( "DYJetsToLL_M50_HT100to200"        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_HT200to400"        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_HT400to600"        ,  "non-prompt e/#mu"    , kRed      );
   md.anConf.addSample( "DYJetsToLL_M50_HT600toInf"        ,  "non-prompt e/#mu"    , kRed      );

  //t production
    md.anConf.addSample( "TBarToLeptons_sch"                ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TBarToLeptons_tch"                ,  "non-prompt e/#mu"    , kRed      );
   md.anConf.addSample( "TBar_tWch"                        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TTJets"                           ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TToLeptons_sch"                   ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TToLeptons_tch"                   ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "T_tWch"                           ,  "non-prompt e/#mu"    , kRed      );

  //W+Jets
    md.anConf.addSample( "WJetsToLNu_HT100to200"            ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT200to400"            ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT400to600"            ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT600toInf"            ,  "non-prompt e/#mu"    , kRed      );

  //signal
    if(sigs=="t"){
    md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800"                ,  "T1t412 sig"     , kBlue-3 );
    md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100"                ,  "T1t415 sig"     , kBlue-7  );
    md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    }
    if(sigs=="q"){
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4WZ12 sig"   , kRed-6  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4WZ15 sig"   , kRed+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }





//    md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1000) * 20 sig" , kOrange-3 );
  //md.anConf.addSample( "T5ttttDeg_mGo1300_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1300) #cdot 20 sig" , kOrange+6 );
    // }
    //===============================================================

    //*********************************************************************²
    //Execution macro ******************************************************
 
    //Configuration ================
    //if( md.isInitStatus() ) {
  
    //md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
   
    // }

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
    md.dp.setNormalization( Norm );
    md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal,
             mcOnly,cmsPrel, uncDet);
    md.prepareDisplay();
    md.doPlot();
    //md.doStatisticsPlot();
    md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
 
}
