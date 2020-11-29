{
  ofstream submit_macro("submit.sh");

  for (auto i = 0; i <100; i++) 
  { 
    TString name = Form("labr3_%02d.sh",i);
    ofstream submit_file(name);
    
    submit_file << "# cpu 2" << endl;
    submit_file << "# mem 900" << endl;
    submit_file << "dir=`pwd`" << endl;
    submit_file << "idir=$dir/../" << endl;
    submit_file << Form("$idir/exampleLaBr3 $idir/runLJ.mac LaBr3_geant4_test_%02d %d", i, i) << endl;

    submit_file << "Requirements = (Machine != \"nuclear.korea.ac.kr\")" << endl;
    
    submit_macro << "csub " << name << endl;
  }
}
