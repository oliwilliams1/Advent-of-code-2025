#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

constexpr char ROLL = '@';
constexpr char EMPTY = '.';
constexpr char FORKLIFT = 'x';

std::vector<std::string> batteries;
int height = 0;
int width = 0;

static inline char GetCell(int x, int y)
{
    return batteries[y][x];
}

struct QueueDef
{
    int x, y;
    char c;
};

class CellSetter
{
public:
    void AddToQueue(int x, int y, char c)
    {
		queue.push_back({ x, y, c });
    }

    void ExecuteQueue()
    {
        for (const auto& q : queue)
            SetCell(q.x, q.y, q.c);
        queue.clear();
    }

private:
    std::vector<QueueDef> queue;
    inline void SetCell(int x, int y, char c)
    {
	    batteries[y][x] = c;
    }
};

static int NumRollsInLineAdjacent(int x, int y)
{
    int minX = std::clamp(x - 1, 0, width);
    int maxX = std::clamp(x + 1, 0, width);
    int numRolls = 0;
    for (int i = minX; i <= maxX; i++)
    {
        if (GetCell(i, y) == ROLL)
            numRolls++;
    }

    return numRolls;
}

static bool IsForklift(int x, int y)
{
    int minY = std::clamp(y - 1, 0, height);
    int maxY = std::clamp(y + 1, 0, height);
    int numRolls = 0;
    for (int i = minY; i <= maxY; i++)
	{
		numRolls += NumRollsInLineAdjacent(x, i);
	}

    if (numRolls <= 4)
        return true;
    else
        return false;
}

int main()
{
    std::ifstream t("data.txt");
    std::string line;

    while (std::getline(t, line))
    {
        height++;
        if (width == 0)
            width = line.length();
        batteries.push_back(line);
    }

    int totalRollsRemoved = 0;
    while (true)
    {
        int removedRolls = 0;
        
        CellSetter setter;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (GetCell(x, y) == ROLL)
                {
                    if (IsForklift(x, y))
                    {
                        setter.AddToQueue(x, y, EMPTY);
                        removedRolls++;
                    }
                    else
                        std::cout << ROLL;
                }
                else
                {
                    std::cout << EMPTY;
                }
            }

            std::cout << std::endl;
        }
        setter.ExecuteQueue();

        std::cout << "Num rolls removed: " << removedRolls << std::endl;
        totalRollsRemoved += removedRolls;
        if (removedRolls == 0)
            break;
    }

    std::cout << "Total rolls removed: " << totalRollsRemoved << std::endl;
	return 0;
}