#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

constexpr char START = 'S';
constexpr char SPLITTER = '^';

int main()
{
    std::vector<std::string> grid;

    std::ifstream file("data.txt");
    std::string line;

    while (std::getline(file, line))
    {
        grid.push_back(line);
    }

    if (grid.empty()) return 0;

    int height = grid.size();
    int width = grid[0].size();

    std::vector<std::vector<uint64_t>> timelineGrid;
    timelineGrid.resize(height);
    for (auto& row : timelineGrid)
    {
        row.resize(width);
    }

    for (int x = 0; x < width; x++)
    {
        if (grid[0][x] == START)
        {
            timelineGrid[0][x] = 1;
        }
    }

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width; x++)
        {
            uint64_t currentTimelines = timelineGrid[y][x];

            if (grid[y + 1][x] == SPLITTER)
            {
                if (x > 0)
                {
                    timelineGrid[y + 1][x - 1] += currentTimelines;
                }
                if (x < width - 1)
                {
                    timelineGrid[y + 1][x + 1] += currentTimelines;
                }
            }
            else
            {
                timelineGrid[y + 1][x] += currentTimelines;
            }
        }
    }

    uint64_t totalTimelines = 0;
    for (uint64_t count : timelineGrid[height - 1])
    {
        totalTimelines += count;
    }

    std::cout << "Num timelines: " << totalTimelines << std::endl;

    return 0;
}