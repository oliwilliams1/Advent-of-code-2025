#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>

struct Range
{
    uint64_t start = 0;
    uint64_t end = 0;

    Range() = default;

    Range(const std::string& serialisedRange)
    {
        bool foundDash = false;
        std::string temp;
        for (const char& c : serialisedRange)
        {
            if (c == '-')
            {
                foundDash = true;
                start = std::stoull(temp);
                temp = "";
                continue;
            }
            temp += c;
        }
        end = std::stoull(temp);
    }

    bool isInRange(uint64_t value) const
	{
		return value >= start && value <= end;
	}

    bool overlaps(const Range& other) const
    {
		if (!valid || !other.valid) return false;
		return start <= other.end && end >= other.start;
    }

    uint64_t size() const
    {
        if (!valid) return 0;

        return end - start + 1;
    }

    bool valid = true;
};

static void FixOverlap(Range& r1, Range& r2)
{
    r1.start = std::min(r1.start, r2.start);
    r1.end = std::max(r1.end, r2.end);
    r2.valid = false;
}

static bool compareRanges(const Range& a, const Range& b) {
    return a.start < b.start;
}

int main()
{
    std::ifstream t("data.txt");
    std::string line;

    bool populatingRanges = true;
    std::vector<Range> ranges;
    std::vector<uint64_t> ingredientIDs;

    while (std::getline(t, line))
    {
        if (line == "")
        {
            populatingRanges = false;
            continue;
        }
        if (populatingRanges)
        {
			ranges.push_back(line);
        }
        else
        {
			ingredientIDs.push_back(std::stoull(line));
        }
    }

    uint64_t count = 0;
    for (const auto& id : ingredientIDs)
    {
        for (const auto& range : ranges)
		{
			if (range.isInRange(id))
			{
				count++;
				break;
			}
		}
    }

    std::cout << "Available ingredient IDs: " << count << std::endl;

    std::sort(ranges.begin(), ranges.end(), compareRanges);

    std::vector<Range> mergedRanges;
    mergedRanges.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); i++)
    {
        Range& lastMerged = mergedRanges.back();
        const Range& current = ranges[i];

        if (lastMerged.overlaps(current))
            lastMerged.end = std::max(lastMerged.end, current.end);
        else
            mergedRanges.push_back(current);
    }

    uint64_t totalNumValidIDs = 0;
    for (const auto& r : mergedRanges)
    {
        totalNumValidIDs += r.size();
    }

    std::cout << "Num valid ingredient IDs: " << totalNumValidIDs << std::endl;

    return 0;
}