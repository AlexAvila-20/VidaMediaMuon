void muon_lifetime_fit() {
    // Archivo de entrada
    const char* filename = "vdelta_t.txt";

    // Crear histograma
    TH1F* h = new TH1F("h", "Histograma de vida media del muon;#Delta t [#mu s];Eventos", 106, 0, 10);

    // Leer archivo
    ifstream infile(filename);
    double dt;
    while (infile >> dt) {
        h->Fill(dt);
    }

    // Dibujar histograma
    TCanvas* c1 = new TCanvas("c1", "Muones", 800, 600);
    h->SetStats(0);
    h->Draw();

    // Ajustar función: y = A * exp(-x / tau) + C
    TF1* fitFunc = new TF1("fitFunc", "[0]*exp(-x/[1])+[2]", 0, 10);
    fitFunc->SetParameters(500, 2.0, 1); // A, tau, C
    h->Fit(fitFunc, "R");

    // Mostrar parámetros ajustados
    double tau = fitFunc->GetParameter(1);
    double tauErr = fitFunc->GetParError(1);
    cout << "Vida media ajustada: " << tau << " ± " << tauErr << " µs" << endl;

    // Obtener y mostrar chi^2/ndf
    double chi2 = fitFunc->GetChisquare();
    double ndf = fitFunc->GetNDF();
    cout << "Chi^2/NDF = " << chi2 << " / " << ndf << " = " << (chi2 / ndf) << endl;
}
