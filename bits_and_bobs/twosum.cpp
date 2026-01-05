class Solution
{
public:
  vector<int> twoSum(vector<int> &nums, int target)
  {
    vector<int> indices;
    for (int i = 0; i < nums.size(); i++)
    {
      for (int j = 1; j < nums.size() - 1; i++)
      {
        if (target - (nums[i] + nums[j]) == 0)
        {
          indices.push_back(i);
          indices.push_back(j);
          if (indices.size() == 2)
          {
            break;
          }
        }
        if (indices.size() == 2)
        {
          break;
        }
      }
    }
    return indices;
  }
};

int main()
{

  return 0;
}
