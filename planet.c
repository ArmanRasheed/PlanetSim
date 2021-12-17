void planet() {
    const int n = 1000;
    const int N = 10;
    float dt = .001;
    float pi = TMath::Pi();
    float mass = 6 * pow(10, 24);
    int apogee = 0;
    int perigee = 0;
    int covert = 0;
    int covert2 = 0;
    float vhigh = 0.0;
    float vlow = 1000.0;
    float dist = 0.0;
    float t[n], x[n], y[n], r[n], vx[n], vy[n], v[n], E[n], k[n], p[n], m[n];
    float A[N];
    t[0] = 0;
    x[0] = 1;
    y[0] = 0;
    r[0] = sqrt(x[0]*x[0] + y[0]*y[0]);
    vx[0] = 0;
    vy[0] = 2 * pi;
    v[0] = sqrt(vx[0]*vx[0] + vy[0]*vy[0]);
    k[0] = .5 * mass * v[0]*v[0];
    p[0] = (-4 * pi * pi * mass) / (r[0]*r[0]);
    E[0] = k[0] + p[0];
    m[0] = mass * r[0] * v[0];

    for(int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + dt;
        vx[i + 1] = vx[i] - (((4 * pow(pi, 2)) * x[i]) / (pow(r[i], 3))) * dt;
        x[i + 1] = x[i] + vx[i + 1] * dt;
        vy[i + 1] = vy[i] - (((4 * pow(pi, 2)) * y[i]) / (pow(r[i], 3))) * dt;
        y[i + 1] = y[i] + vy[i + 1] * dt;
        r[i + 1] = sqrt(x[i + 1]*x[i + 1] + y[i + 1]*y[i + 1]);
        v[i + 1] = sqrt(vx[i + 1]*vx[i + 1] + vy[i + 1]*vy[i + 1]);
        k[i + 1] = .5 * mass * v[i + 1]*v[i + 1];
        p[i + 1] = (-4 * pi * pi * mass) / (r[i + 1]*r[i + 1]);
        E[i + 1] = k[i + 1] + p[i + 1];
        m[i + 1] = mass * r[i + 1] * v[i + 1];
        if(v[i + 1] > vhigh) {
            vhigh = v[i + 1];
            apogee = i + 1;
        }
        if(v[i + 1] < vlow) {
            vlow = v[i + 1];
            perigee = i + 1;
        }
        if(vy[i + 1] > -0.1 && vy[i + 1] < 0.1) {
            if(y[i + 1] > 0) {
                covert = i + 1;
            } else {
                covert2 = i + 1;
            }
        }
    }

    float nums[N];
    int count = 0;
    for(int j = 0; j < n - 100; j++) {
        dist = sqrt((x[j + 100] - x[j])*(x[j + 100] - x[j]) + (y[j + 100] - y[j])*(y[j + 100] - y[j]));
        if(count <= N) {
            nums[count] = count;
            A[count] = .5 * r[j] * r[j] * dist;
            count++;
        } else {
            break;
        }
    }

    cout << endl << x[apogee] << ", " << y[apogee] << endl;
    cout << x[perigee] << ", " << y[perigee] << endl;
    cout << x[covert] << ", " << y[covert] << endl;
    cout << x[covert2] << ", " << y[covert2] << endl << endl;

    float major = sqrt((x[apogee] - x[perigee])*(x[apogee] - x[perigee]) + (y[apogee] - y[perigee])*(y[apogee] - y[perigee])) / 2.0;
    cout << "Semi-major:: " << major << endl;
    float minor = sqrt((x[covert] - x[covert2])*(x[covert] - x[covert2]) + (y[covert] - y[covert2])*(y[covert] - y[covert2])) / 2.0;
    cout << "Semi-minor:: " << minor << endl;
    float ec = sqrt(1 - pow(minor, 2)/pow(major, 2));
    cout << "Eccentricity:: " << ec << endl;

    c = new TCanvas("c", "Planetary Motion", 10, 10, 1500, 1000);
    c -> Divide(2, 3);
    c -> Draw();
    c -> cd(1);
    xy = new TGraph(n, x, y);
    xy -> SetTitle("Planet Motion");
    xy -> GetXaxis()->SetTitle("x position");
    xy -> GetYaxis()->SetTitle("y position");
    xy -> Draw();
    p1 = new TMarker(x[apogee],y[apogee], 20);
    p1 -> SetMarkerColor(2);
    p1 -> Draw("same");
    p2 = new TMarker(x[perigee],y[perigee], 20);
    p2 -> SetMarkerColor(2);
    p2 -> Draw("same");
    p3 = new TMarker(x[covert],y[covert], 20);
    p3 -> SetMarkerColor(4);
    p3 -> Draw("same");
    p4 = new TMarker(x[covert2],y[covert2], 20);
    p4 -> SetMarkerColor(4);
    p4 -> Draw("same");
    c -> cd(2); 
    area = new TGraph(N, nums, A);
    area -> SetTitle("Ellipse Area per segment");
    area -> GetXaxis()->SetTitle("segment");
    area -> GetYaxis()->SetTitle("Area");
    area -> Draw();
    c -> cd(3);
    kE = new TGraph(n, t, k);
    kE -> SetTitle("Kinetic Energy");
    kE -> GetXaxis()->SetTitle("time, [s]");
    kE -> GetYaxis()->SetTitle("Energy");
    kE -> Draw();
    c -> cd(4);
    pE = new TGraph(n, t, p);
    pE -> SetTitle("Potential Energy");
    pE -> GetXaxis()->SetTitle("time, [s]");
    pE -> GetYaxis()->SetTitle("Energy");
    pE -> Draw();
    c -> cd(5);
    EE = new TGraph(n, t, E);
    EE -> SetTitle("Total Energy");
    EE -> GetXaxis()->SetTitle("time, [s]");
    EE -> GetYaxis()->SetTitle("Energy");
    EE -> Draw();
    c -> cd(6);
    EE = new TGraph(n, t, m);
    EE -> SetTitle("Angular Momentum");
    EE -> GetXaxis()->SetTitle("time, [s]");
    EE -> GetYaxis()->SetTitle("Angular Momentum");
    EE -> Draw();
}