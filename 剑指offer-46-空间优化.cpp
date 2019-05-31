#include <string>
#include <iostream>

using namespace std;

int GetTranslationCount(const string& number);

int GetTranslationCount(int number)
{
    if (number < 0)
        return 0;

    string numberInString = to_string(number);
    return GetTranslationCount(numberInString);
}

int GetTranslationCount(const string& number)
{
    int length = number.length();
    int nextcount, doublenext;
    int count = 0;

    for (int i = length - 1; i >= 0; --i)
    {
        count = 0;
        if (i < length - 1)
            count = nextcount;
        else
            count = 1;

        if (i < length - 1)
        {
            int digit1 = number[i] - '0';
            int digit2 = number[i + 1] - '0';
            int converted = digit1 * 10 + digit2;
            if (converted >= 10 && converted <= 25)
            {
                if (i < length - 2)
                    count += doublenext;
                else
                    count += 1;
            }
            doublenext = nextcount;
        }
        nextcount = count;
    }
    return count;
}

// ====================测试代码====================
void Test(const string& testName, int number, int expected)
{
    if (GetTranslationCount(number) == expected)
        cout << testName << " passed." << endl;
    else
        cout << testName << " FAILED." << endl;
}

void Test8()
{
    int number = 12258;
    int expected = 5;
    Test("Test8", number, expected);
}

void Test9()
{
    int number = 125;
    int expected = 3;
    Test("Test9", number, expected);
}

int main(int argc, char* argv[])
{
    Test8();
    Test9();

    return 0;
}