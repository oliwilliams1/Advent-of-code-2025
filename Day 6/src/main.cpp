#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdint>

struct EquationBlock
{
    std::vector<std::string> lines;
    char operation;
    int expressionWidth;
};

static uint64_t Evaluate(const EquationBlock& block)
{
    std::vector<uint64_t> numbers;

    for (int i = block.expressionWidth - 1; i >= 0; i--)
    {
        std::string currentNumberStr;

        for (const auto& row : block.lines)
        {
            if (i < row.size())
            {
                char c = row[i];
                if (isdigit(c))
                {
                    currentNumberStr.push_back(c);
                }
            }
        }

        if (!currentNumberStr.empty())
        {
            numbers.push_back(std::stoull(currentNumberStr));
        }
    }

    if (block.operation == '+')
    {
        uint64_t sum = 0;
        for (uint64_t number : numbers) sum += number;
        return sum;
    }
    if (block.operation == '*')
    {
        uint64_t product = 1;
        for (uint64_t number : numbers) product *= number;
        return product;
    }
    return 0;
}

int main()
{
    std::ifstream t("data.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string data = buffer.str();

    std::vector<std::string> lines;
    std::string tempLine;

    for (const char& c : data)
	{
		if (c == '\n')
		{
			lines.push_back(tempLine);
			tempLine = "";
		}
		else
		{
			tempLine.push_back(c);
		}
	}
    lines.push_back(tempLine);

    std::vector<EquationBlock> equations;
    int width = 0;
    char lastOp = lines[lines.size() - 1][0];
    for (const char& c : lines[lines.size() - 1])
    {
        if (c != ' ' && width != 0)
        {
            EquationBlock equationBlock;
            equationBlock.operation = lastOp;
            equationBlock.expressionWidth = width - 1;
            width = 0;
			equations.push_back(equationBlock);
            lastOp = c;
        }
        width++;
    }

    EquationBlock equationBlock;
    equationBlock.operation = lastOp;
    equationBlock.expressionWidth = width + 1;
    equations.push_back(equationBlock);

    int accumWidth = 0;
    for (EquationBlock& block : equations)
	{
        for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++)
        {
            std::string expression = lines[lineIndex].substr(accumWidth, block.expressionWidth);
			block.lines.push_back(expression);
        }
        accumWidth += (block.expressionWidth + 1);
	}

    uint64_t sum = 0;
    for (const auto& e : equations)
    {
        sum += Evaluate(e);
    }

    std::cout << "Sum: " << sum << std::endl;

	return 0;
}