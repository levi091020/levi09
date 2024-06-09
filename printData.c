#include <iostream>
#include <fstream>
#include <vector>

void printData() {
    TChain *tIn = new TChain("TofHitsTree");
    tIn->Add("/home/lecamvi/Documents/TOF_thesis/output/run16505_outputTree.root");

    std::vector<Double_t> *SignalPosition = nullptr;
    std::vector<Double_t> *SignalPlane = nullptr;
    std::vector<Double_t> *SignalTime = nullptr;
    std::vector<Double_t> *SignalBar = nullptr;
    std::vector<Double_t> *SignalX = nullptr;
    std::vector<Double_t> *SignalY = nullptr;
    std::vector<Double_t> *SignalZ = nullptr;

    tIn->SetBranchAddress("SignalPosition", &SignalPosition);
    tIn->SetBranchAddress("SignalPlane", &SignalPlane);
    tIn->SetBranchAddress("SignalTime", &SignalTime);
    tIn->SetBranchAddress("SignalBar", &SignalBar);
    tIn->SetBranchAddress("SignalX", &SignalX);
    tIn->SetBranchAddress("SignalY", &SignalY);
    tIn->SetBranchAddress("SignalZ", &SignalZ);

    Long64_t nEntries = tIn->GetEntries();

    std::ofstream outfile("output16505.txt");

    for (Long64_t i = 0; i < nEntries; i++) {
        tIn->GetEntry(i);

        for (size_t j = 0; j < SignalPosition->size(); j++) {
            outfile << "Event " << i << ", Hit " << j << ":" << std::endl;
            if (SignalX && SignalY && SignalZ) {
                outfile << "x = " << (*SignalX)[j] << ", y = " << (*SignalY)[j] << ", z = " << (*SignalZ)[j] << std::endl;
            } else {
                outfile << "Coordinates not available" << std::endl;
            }
            if (SignalTime && SignalPosition) {
                outfile << "Time = " << (*SignalTime)[j] << ", Position = " << (*SignalPosition)[j] << std::endl;
            } else {
                outfile << "Time and Position not available" << std::endl;
            }
            if (SignalBar && SignalPlane) {
                outfile << "Bar = " << (*SignalBar)[j] << ", Plane = " << (*SignalPlane)[j] << std::endl;
            } else {
                outfile << "Bar and Plane not available" << std::endl;
            }
            outfile << std::endl;
        }
    }

    outfile.close();
}