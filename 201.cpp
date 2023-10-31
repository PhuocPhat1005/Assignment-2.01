#include <iostream>
#include <math.h>
using namespace std;

string sum(const string &x, const string &y, const unsigned short base);
string difference(string x, string y, const unsigned short base);

char numToChar(const int &num)
{
    if (num >= 10)
        return num - 10 + 'A';
    return num + '0';
}

int charToNum(const char &c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return c - '0';
}

string form(string s, const unsigned short &base)
{
    if (base == 10)
        return s;
    if (base == 16 && s.length() % 2)
        s = '0' + s;
    else
        while (s.length() % 4 != 0)
            s = '0' + s;
    return s;
}

string decimalToBase(unsigned int num, const unsigned short &base)
{
    string s = "";
    int value;
    while (num > 0)
    {
        value = num % base;
        s = numToChar(value) + s;
        num /= base;
    }
    if (s == "")
        s = '0';
    return form(s, base);
}

string oneComplement(string x, const unsigned short &base)
{
    string res = "";
    for (int i = 0; i < x.length(); i++)
        res += numToChar(base - 1);
    return difference(res, x, base);
}

string twoComplement(string x, const unsigned short &base, bool soAm)
{
    return sum(oneComplement(x, base), "1", base);
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
            value = charToNum(x[i - 1]) + charToNum(y[j - 1]);
        if (i > 0 && j <= 0)
            value = charToNum(x[i - 1]);
        if (i <= 0 && j > 0)
            value = charToNum(y[j - 1]);
        if (flag)
            ++value;
        flag = false;
        if (value >= base)
        {
            value -= base;
            flag = true;
        }
        s = numToChar(value) + s;
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
            value = charToNum(x[i - 1]) - charToNum(y[j - 1]);
        else
            value = charToNum(x[i - 1]);
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
            s = numToChar(value) + s;
    }
    s = form(s, base);
    if (soAm)
    {
        if (base == 10)
            s = '-' + s;
        else
            s = twoComplement(s, base, 1);
    }
    if (s == "")
        s = '0';
    return s;
}

int main()
{
    unsigned int x, y;
    unsigned short base;
    while (true)
    {
        cout << "Nhap base, x, y: (Nhap base = 1 de thoat)" << endl;
        cin >> base >> x >> y;
        if (base == 1)
            break;
        cout << "Tong: " << sum(decimalToBase(x, base), decimalToBase(y, base), base) << "\nHieu: " << difference(decimalToBase(x, base), decimalToBase(y, base), base) << endl << endl;
    }
    return 0;
}