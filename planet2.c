void planet2() {
    const int n = 15000;
    float dt = .001;
    float pi = TMath::Pi();
    float mars = 6.6 * pow(10, 23);
    float jupe = 1.9 * pow(10, 30);
    float sun = 2 * pow(10, 30);
    float t[n], x[n], y[n], r[n], vx[n], vy[n], x2[n], y2[n], r2[n], vx2[n], vy2[n], r12[n];
    t[0] = 0;
    x[0] = 1.66136;
    y[0] = 0;
    r[0] = sqrt(x[0]*x[0] + y[0]*y[0]);
    vx[0] = 0;
    vy[0] = 4.6425;
    x2[0] = 5.4496;
    y2[0] = 0;
    r2[0] = sqrt(x2[0]*x2[0] + y2[0]*y2[0]);
    vx2[0] = 0;
    vy2[0] = 2.626;
    r12[0] = sqrt((x[0] - x2[0])*(x[0] - x2[0]) + (y[0] - y2[0])*(y[0] - y2[0]));
    
    for(int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + dt;
        vx[i + 1] = vx[i] - ((((4 * pow(pi, 2)) * x[i]) / (pow(r[i], 3))) * dt) - (((4 * pow(pi, 2) * (jupe / sun))/(pow(r12[i], 3))) * dt);
        vy[i + 1] = vy[i] - ((((4 * pow(pi, 2)) * y[i]) / (pow(r[i], 3))) * dt) - (((4 * pow(pi, 2) * (jupe / sun))/(pow(r12[i], 3))) * dt);
        vx2[i + 1] = vx2[i] - ((((4 * pow(pi, 2)) * x2[i]) / (pow(r2[i], 3))) * dt) - (((4 * pow(pi, 2) * (mars / sun))/(pow(r12[i], 3))) * dt);
        vy2[i + 1] = vy2[i] - ((((4 * pow(pi, 2)) * y2[i]) / (pow(r2[i], 3))) * dt) - (((4 * pow(pi, 2) * (mars / sun))/(pow(r12[i], 3))) * dt);
        x[i + 1] = x[i] + vx[i + 1] * dt;
        y[i + 1] = y[i] + vy[i + 1] * dt;
        x2[i + 1] = x2[i] + vx2[i + 1] * dt;
        y2[i + 1] = y2[i] + vy2[i + 1] * dt;
        r[i + 1] = sqrt(x[i + 1]*x[i + 1] + y[i + 1]*y[i + 1]);
        r2[i + 1] = sqrt(x2[i + 1]*x2[i + 1] + y2[i + 1]*y2[i + 1]);
        r12[i + 1] = sqrt((x[i + 1] - x2[i + 1])*(x[i + 1] - x2[i + 1]) + (y[i + 1] - y2[i + 1])*(y[i + 1] - y2[i + 1]));
    }

    c = new TCanvas("c", "Planetary Motion", 10, 10, 900, 600);
    c -> Draw();
    xy2 = new TGraph(n, x2, y2);
    xy2 -> SetTitle("Three Body Sim. w/ Mars & Jupiter");
    xy2 -> GetXaxis()->SetTitle("x position");
    xy2 -> GetYaxis()->SetTitle("y position");
    xy2 -> Draw();
    xy = new TGraph(n, x, y);
    xy -> SetLineColor(2);
    xy -> Draw("same");
}