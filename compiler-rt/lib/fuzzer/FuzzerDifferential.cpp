#include "FuzzerDifferential.h"

namespace fuzzer {
  DTManager DTM;
}

extern "C" {
void LLVMFuzzerStartBatch(const uint8_t *Data, size_t Size) {
  fuzzer::DTM.startBatch(Data, Size);
}
void LLVMFuzzerEndBatch() { fuzzer::DTM.endBatch(); }
void LLVMFuzzerStartRun(int i) { fuzzer::DTM.startRun(i); }
void LLVMFuzzerEndRun(int i, int exit_code, const uint8_t *data, size_t size) {
  fuzzer::DTM.endRun(i, exit_code, data, size);
}
}

namespace fuzzer {
DTManager::DTManager() {
}

void DTManager::startBatch(const uint8_t *Data, size_t Size)
{
  this->TimesOfUnits.clear();
  this->counter = 0;
}

void DTManager::endBatch()
{
}

void DTManager::startRun(int i)
{
  this->startTime = std::chrono::system_clock::now();
}

void DTManager::endRun(int i, int exit_code, const uint8_t *data, size_t size)
{
  this->endTime = std::chrono::system_clock::now();
  std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(this->endTime - this->startTime);

  this->TimesOfUnits.push_back(delta);
  this->counter++;
}

std::vector<std::chrono::microseconds> DTManager::getTimesOfUnits() const
{
  return this->TimesOfUnits;
}
}
