#include <iostream>
#include <math.h>
using namespace std;

char format1(const int &num)
{
    if (num >= 10)
        return num - 10 + 'A';
    return num + '0';
}
string decimalToBase(unsigned int num, const unsigned short base)
{
    string s = "";
    int value;
    while (num > 0)
    {
        value = num % base;
        s = format1(value) + s;
        num /= base;
    }
    if (s == "")
        s = '0';
    return s;
}

int format2(const char &c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return c - '0';
}

void processFlag(string &s, bool &flag, int &value, const unsigned short base)
{
    if (flag)
        ++value;
    flag = false;
    if (value >= base)
    {
        value -= base;
        flag = true;
    }
    s = format1(value) + s;
}

void processFlag2(string &s, bool &flag, int &value, const unsigned short base)
{
    if (flag)
        --value;
    flag = false;
    if (value < 0)
    {
        value += base;
        flag = true;
    }
    s = format1(value) + s;
}

string sum(const string &x, const string &y, const unsigned short base)
{
    string s = "";
    int value;
    bool flag = false;
    int i = x.length(), j = y.length();
    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0)
            value = format2(x[i - 1]) + format2(y[j - 1]);
        if (i > 0 && j <= 0)
            value = format2(x[i - 1]);
        if (i <= 0 && j > 0)
            value = format2(y[j - 1]);
        processFlag(s, flag, value, base);
        i--;
        j--;
    }
    if (flag)
        s = '1' + s;
    return s;
}

string difference(string x, string y, const unsigned short base)
{
    string s = "";
    int value;
    bool flag = false;
    bool soAm = false;
    int i = x.length(), j = y.length();
    if (j > i)
    {
        soAm = true;
    }
    else if (j == i)
    {
        int k = 0;
        while (k < i && x[k] == y[k])
        {
            k++;
        }
        if (k < i && x[k] < y[k])
        {
            soAm = true;
        }
    }
    if (soAm)
    {
        swap(x, y);
        swap(i, j);
    }
    while (i > 0)
    {
        if (j > 0)
            value = format2(x[i - 1]) - format2(y[j - 1]);
        else
            value = format2(x[i - 1]);
        if (flag)
        {
            value--;
            flag = false;
        }
        if (value < 0)
        {
            value += base;
            flag = true;
        }
        i--;
        j--;
        if (value || i)
            s = format1(value) + s;
    }
    if (soAm)
        s = '-' + s;
    if (s == "")
        s = '0';
    return s;
}

int main()
{
    // Can bo sung them mấy cach bieu dien so am
    unsigned int x, y;
    unsigned short base = 10;
    cin >> x >> y;
    cout << difference(decimalToBase(x, base), decimalToBase(y, base), base) << endl;
    return 0;
}