void muon_fit() {
    // ARCHIVO DE ENTRADA
    const char* filename = "vdelta_t.txt";

    // HISTOGRAMA
    TH1F* h = new TH1F("h", "Histograma de vida media del muon;#Delta t [#mu s];Eventos", 106, 0, 10);

    // LECTURA DEL ARCHIVO
    ifstream infile(filename);
    double dt;
    while (infile >> dt) {
        h->Fill(dt);
    }

    // DIBUJO DEL HISTOGRAMA
    TCanvas* c1 = new TCanvas("c1", "Muones", 800, 600);
    h->SetStats(0);
    h->Draw();

    // AJUSTE DE LA FUNCIÓN: y = A * exp(-x / tau) + C
    TF1* fitFunc = new TF1("fitFunc", "[0]*exp(-x/[1])+[2]", 0, 10);
    fitFunc->SetParameters(500, 2.0, 1); // A, tau, C
    h->Fit(fitFunc, "R");

    // IMPRIMIR PARÁMETROS AJUSTADOS
    double tau = fitFunc->GetParameter(1);
    double tauErr = fitFunc->GetParError(1);
    cout << "Vida media ajustada: " << tau << " ± " << tauErr << " µs" << endl;

    // IMPRIMIR chi^2/ndf
    double chi2 = fitFunc->GetChisquare();
    double ndf = fitFunc->GetNDF();
    cout << "Chi^2/NDF = " << chi2 << " / " << ndf << " = " << (chi2 / ndf) << endl;
}
