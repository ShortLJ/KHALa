void histogram(){
	TFile *file_Eres = new TFile("/home/samba.old/LaBr3_set1_Eres.root", "read");
	TF1 *ftn_Eres = (TF1*) file_Eres->Get("fftn_Eres");
	//TFitResult *fitresult_Eres = (TFitResult*) file_Eres->Get("TFitResult--fftn_Eres");
	//ftn_Eres->SetFitResult(*fitresult_Eres);
	ftn_Eres->SetParameters(1.13576e-02, 7.86098e-01, 3.79676e+00);
	gRandom->SetSeed(time(NULL));
	//ftn_Eres->Draw();

	int num_node=100;

	TH1D *h1 = new TH1D("Energy","Energy; keV; count/keV", 1500, 0, 1500);
	for(int i=0; i<num_node; i++){
		TFile *file = new TFile(Form("LaBr3_geant4_test_%02d.root",i),"read");
		TTree *tree = (TTree*)file->Get("Event");
		int Entries = tree->GetEntries();
		printf("%d entries in file %d of %d \n", Entries, i, num_node);

		double Energy[12]; double sigma, Energytofill;
		tree->SetBranchAddress("EventEdep00",&Energy[0]);
		tree->SetBranchAddress("EventEdep01",&Energy[1]);
		tree->SetBranchAddress("EventEdep02",&Energy[2]);
		tree->SetBranchAddress("EventEdep03",&Energy[3]);
		tree->SetBranchAddress("EventEdep04",&Energy[4]);
		tree->SetBranchAddress("EventEdep05",&Energy[5]);
		tree->SetBranchAddress("EventEdep06",&Energy[6]);
		tree->SetBranchAddress("EventEdep07",&Energy[7]);
		tree->SetBranchAddress("EventEdep08",&Energy[8]);
		tree->SetBranchAddress("EventEdep09",&Energy[9]);
		tree->SetBranchAddress("EventEdep10",&Energy[10]);
		tree->SetBranchAddress("EventEdep11",&Energy[11]);


		for (int ient=0; ient<Entries; ient++){
			tree->GetEntry(ient);

			for(int i=0; i<12; i++){
				Energy[i]=1000.*Energy[i];
				if(Energy[i]<50) continue;
				//printf("ient %d ch %d Energy %.3f \n", ient, i, Energy[i]);

				//sigma=(ftn_Eres->Eval(Energy[i]))/2.35*Energy[i];
				Energytofill=gRandom->Gaus(Energy[i], (ftn_Eres->Eval(Energy[i]))/2.35*Energy[i]);
				//printf("energy %.2f to be fill as %.2f\n", Energy[i], Energytofill);

				h1->Fill(Energytofill);

			}

		}
	}
	h1->Draw();


}
