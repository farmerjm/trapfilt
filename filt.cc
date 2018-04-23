/*
* getFIRfilteredWaveform
* 
* perform FIR filtering (trapezoidal filtering) of waveform using an algorithm like that implemented on Struck digitizers
* 
* best to pre-allocate an array to hold the filtered waveform values and pass the pointer for that in as firArray
*/

#include <vector>
#include <string>
#include <iostream>
#include <deque>

#include "TCanvas.h"
#include "TH1.h"
#include "TRandom3.h"
#include "trapfilt.h" 

int main() {
  TRandom3 rand(time(NULL));

  std::vector<double>* test = new std::vector<double>();

  for (int i=0; i<4000;i++) {
    test->push_back(0);
    if (abs(2000-i)<150) {
      test->at(i)+=100*exp(-1*(1./2)*pow(double(i-2000)/20,2));
    }
  }

  for (int i=0; i<4000; i++) {
    test->at(i)+=rand.Gaus(0,70);  
  }

  std::vector<double>* filt = FIRFilt(test,100,20);

  TH1F* histData= new TH1F("dat", "dat", 4000, 0, 3999);
  TH1F* histFilt= new TH1F("filt", "filt", 4000, 0, 3999);

  for (int i=0;i<4000;i++) {
    histData->Fill(i, test->at(i));
    histFilt->Fill(i, filt->at(i));
  }

  TCanvas c1;
  c1.Divide(1,2);
  c1.cd(1);
  histData->Draw();
  c1.cd(2);
  histFilt->Draw();
  c1.SaveAs("test.png");
}
