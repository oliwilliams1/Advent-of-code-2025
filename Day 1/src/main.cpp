#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>

class Factory
{
public:
    Factory() {};
    void Run(const std::string& str)
    {
        std::string iStr = "";
        for (auto c : str)
            if (c != str[0])
                iStr.push_back(c);

        int i = std::stoi(iStr.c_str());
        printf("%s: %d\n", str.c_str(), i);

        if (str[0] == 'R')
            c += i;
        if (str[0] == 'L')
            c -= i;

        FixAndCount();
    }

    void FixAndCount()
    {
        if (c > 99)
        {
            c -= 100;
            ctr++;
            FixAndCount();
            return;
        }
        if (c < 0)
        {
            c += 100;
            ctr++;
            FixAndCount();
            return;
        }
    }

    int c = 50;
    int ctr = 0;
};

int main(int argc, char* argv[])
{
    std::ifstream t("data.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string data = buffer.str();

    Factory factory;
    std::string temp;
    for (char c : data)
    {
        if (c == '\n') {
            factory.Run(temp);
            temp = "";
            continue;
        }
        temp.push_back(c);
    }


    printf("Result: %d", factory.ctr);
}