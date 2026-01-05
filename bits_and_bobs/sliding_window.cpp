#include <chrono>
#include <iostream>
#include <ratio>
#include <vector>

class Timer
{
public:
  Timer() { m_StartTimepoint = std::chrono::high_resolution_clock::now(); };
  ~Timer() { Stop(); };
  void Stop()
  {
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(
                     m_StartTimepoint)
                     .time_since_epoch()
                     .count();

    auto end =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
            .time_since_epoch()
            .count();
    auto duration = end - start;
    double ms = duration * 0.001;
    std::cout << ms << "ms" << std::endl;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

std::vector<int> get_array(int size)
{
  std::vector<int> arr = {};
  for (int i = 0; i < size; i++)
  {
    arr.push_back(i + 1);
  };
  return arr;
}

// Brute force
int get_max_sum_three_values(std::vector<int> arr, int k)
{
  int n = arr.size();

  int maxSum = 0;
  for (int i = 0; i <= n - k; i++)
  {
    auto temp = 0;
    for (int j = i; j < i + k; j++)
    {
      temp += arr[j];
    }
    auto r = i + k;
    // std::cout << i << ',' << r << std::endl;
    // std::cout << '\t' << arr[i] << '+' << arr[i + 1] << '+' << arr[i + 2] << '=' << temp << std::endl;
    maxSum = std::max(temp, maxSum);
  }
  return maxSum;
};

// Sliding window
int get_max_sum_values(std::vector<int> arr, int k)
{
  int n = arr.size();
  int maxSum = 0;
  int windowSum = 0;
  // Calculate initial sum
  for (int i = 0; i < k; i++)
  {
    windowSum += arr[i];
  }
  maxSum = windowSum;

  for (int i = k; i < n; i++)
  {
    windowSum = windowSum - arr[i - k] + arr[i];
    maxSum = std::max(windowSum, maxSum);
  }
  return maxSum;
}

int main()
{
  auto k = 3;
  auto arr = get_array(10);
  {
    Timer timer;
    int maxSum = get_max_sum_values(arr, k);
    std::cout << maxSum << std::endl;
  }
  {
    Timer timer;
    int maxSum = get_max_sum_three_values(arr, k);
    std::cout << maxSum << std::endl;
  }

  return 0;
}
