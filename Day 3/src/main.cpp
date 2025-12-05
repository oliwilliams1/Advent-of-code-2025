#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>

struct Battery {
    std::string bank;
};

static int GetLargestDigitIndex(const std::string& str, int startIndex, int endIndex)
{
    int largestIndex = startIndex;
    for (int i = startIndex; i <= endIndex; i++)
    {
		if (str[i] > str[largestIndex])
		{
			largestIndex = i;
		}
    }

    return largestIndex;
}

static uint64_t GetMaxJoltageRating(const Battery& battery)
{
    std::array<int, 12> indexes = {};
    int lastIndex = -1;
    for (int i = 0; i < 12; i++)
    {
        int index = GetLargestDigitIndex(battery.bank, lastIndex + 1, battery.bank.length() - (12 - i));
        indexes[i] = index;
        lastIndex = index;
    }

    std::string digits;
    digits.resize(12);
    for (int i = 0; i < 12; i++)
    {
        digits[i] = battery.bank[indexes[i]];
    }
  
    return std::stoull(digits);
}

int main()
{
    std::vector<Battery> batteries;
    std::ifstream t("data.txt");
    std::string line;
    while (std::getline(t, line))
    {
        batteries.push_back({ line });
	}

    uint64_t sum = 0;
    for (const auto& battery : batteries)
    {
        sum += GetMaxJoltageRating(battery);
    }

    std::cout << "Total output joltage: " << sum << std::endl;

	return 0;
}