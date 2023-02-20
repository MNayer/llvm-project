#ifndef LLVM_FUZZER_DIFFERENTIAL_TIMER
#define LLVM_FUZZER_DIFFERENTIAL_TIMER

#include <cstdlib>
#include <vector>
#include <chrono>

namespace fuzzer {
class DTManager {
public:
    DTManager();
    DTManager(const DTManager&) = delete;

    void startBatch(const uint8_t *Data, size_t Size);
    void endBatch();
    void startRun(int i);
    void endRun(int i, int exit_code, const uint8_t *data, size_t size);

    std::vector<std::chrono::microseconds> getTimesOfUnits() const;

private:
    int counter = 0;
    std::vector<std::chrono::microseconds> TimesOfUnits;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
};
}

#endif