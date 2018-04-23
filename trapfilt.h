#include <vector>
#include <deque>

std::vector<double>* FIRFilt(std::vector<double>* wave, 
int peakingTime, int gapTime) {
  const size_t len = wave->size();
  std::deque<double> leadingWindow;
  std::deque<double> trailingWindow;

  std::vector<double>* out = new std::vector<double>(len, 0);

  int leadIndex_leadWindow = 2 * peakingTime - gapTime;
  int leadIndex_trailingWindow = peakingTime;
  int terminationIndex = len- 2 * peakingTime - gapTime;

  for (int i = gapTime; i < gapTime + peakingTime; i++) leadingWindow.push_back(wave->at(i));
  for (int i = 0; i < peakingTime; i++) trailingWindow.push_back(wave->at(i));

  double leadingSum, trailingSum;
  for (int sumIdx = 0; sumIdx < peakingTime; sumIdx++) {
    leadingSum += (double)leadingWindow[sumIdx];
    trailingSum += (double)trailingWindow[sumIdx];
  }

  for (int idx = 0; idx < terminationIndex; idx++) {
    out->at(idx) = (double)(leadingSum - trailingSum);

    double newLeadingElement = wave->at(++leadIndex_leadWindow);
    double newTrailingElement = wave->at(++leadIndex_trailingWindow);

    leadingSum -= leadingWindow.front();
    leadingSum += newLeadingElement;
    leadingWindow.push_back(newLeadingElement);
    leadingWindow.pop_front();

    trailingSum -= trailingWindow.front();
    trailingSum += newTrailingElement;
    trailingWindow.push_back(newTrailingElement);
    trailingWindow.pop_front();
  }

  return out;
}
