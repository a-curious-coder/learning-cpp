#include <chrono>
#include <iostream>
#include <vector>

class Timer {
public:
  Timer() : start(std::chrono::high_resolution_clock::now()) {};
  ~Timer() { Stop(); }
  void Stop() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << duration.count() << " milliseconds"
              << std::endl;
  }

private:
  std::chrono::high_resolution_clock::time_point start;
};

// O(n^2)
int maxSubArray(std::vector<int> arr) {
  int n = arr.size();
  int maxSum = 0;

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = i; j < n; j++) {
      sum += arr[j];
      maxSum = std::max(maxSum, sum);
    }
  }

  return maxSum;
};

int kadanes(std::vector<int> arr) {
  int n = arr.size();
  int maxSum = 0;
  int currentSum = 0;
  std::vector<int> currentSequence;
  std::vector<int> maxSequence;

  for (int i = 0; i < n; i++) {

    currentSum += arr[i];
    currentSequence.push_back(arr[i]);
    std::cout << "current sequence: ";
    for (int val : currentSequence) {
      std::cout << val << " + ";
    }
    std::cout << "= " << currentSum << '\n';

    if (currentSum > maxSum) {
      maxSum = currentSum;
      maxSequence = currentSequence;
    }

    if (currentSum < 0) {
      currentSum = 0;
      currentSequence = {};
      std::cout << "RESET" << std::endl;
    };
  }

  for (int i = 0; i < maxSequence.size(); i++) {
    if (i == maxSequence.size() - 1) {
      std::cout << maxSequence[i] << " = ";
      break;
    }
    std::cout << maxSequence[i] << ", ";
  }

  return maxSum;
};

int main() {
  //{
  //  Timer timer;
  //  // The subarray[4, -1, 2, 1] has the largest sum = 6.
  //  std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  //  std::cout << maxSubArray(arr) << std::endl;
  //}
  {
    Timer timer;
    // The subarray[4, -1, 2, 1] has the largest sum = 6.
    std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << kadanes(arr) << std::endl;
  }
  // Problem: Find max sum subarray in arr

  return 0;
}
