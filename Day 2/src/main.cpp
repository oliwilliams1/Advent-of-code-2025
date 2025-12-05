#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream>

struct range {
    std::string start;
    std::string end;
};

bool isDivisible(uint64_t n, uint64_t d)
{
	return n % d == 0;
}

static bool IsInvalid(const std::string& str)
{
    int numDigits = str.size();

    std::vector<int> pairsToCheck;
    for (int i = 1; i < numDigits; i++)
    {
        if (isDivisible(numDigits, i))
		{
			pairsToCheck.push_back(i);
		}
    }

    for (int pairLength : pairsToCheck)
    {
        std::vector<std::string> pairs;
        int pairCount = numDigits / pairLength;
        for (int i = 0; i < pairCount; i++)
        {
            pairs.push_back(str.substr(i * pairLength, pairLength));
        }
        std::string temp = pairs[0];
        bool invalid = true;
        for (const auto& p : pairs)
        {
            if (p != temp)
            {
                invalid = false;
                continue;
            }
        }
        if (invalid)
            return true;
    }
    return false;
}

int main()
{
    std::ifstream t("data.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string data = buffer.str();

    std::vector<std::string> sRanges;
    
    std::string temp;
    for (const char c : data)
    {
        if (c == ',')
        {
            sRanges.push_back(temp);
            temp="";
            continue;
        }
        temp.push_back(c);
    }

    sRanges.push_back(temp);
    
    std::vector<range> ranges;
    for (const std::string& sR : sRanges)
    {
        std::string tR;
        range r{};
        for (char c : sR)
        {
            if (c == '-')
            {
                r.start = tR;
                tR="";
                continue;
            }
            tR.push_back(c);
        }
        r.end = tR;
        ranges.push_back(r);
    }

    uint64_t ctr = 0;
    for (const auto& r : ranges)
    {
        for (uint64_t n = std::stoull(r.start); n <= std::stoull(r.end); n++)
        {
            if (IsInvalid(std::to_string(n)))
            {
                uint64_t t = ctr;
                ctr += n;
            }
        }
    }
    
    std::cout << "Sum of invalid: " << ctr << std::endl;
    return 0;        
}