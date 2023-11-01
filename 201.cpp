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

string decimalToBase(unsigned long long num, const unsigned short &base)
{
    string s = "";
    unsigned short value; // Vi value = num % base, nen k can khai bao kieu int
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

unsigned long long baseToDecimal(string x, const unsigned short &base) {
    unsigned long long result = 0;
    unsigned long long power = 1;
    for (int i = x.size() - 1; i >= 0; i--) {
        unsigned digit;
        digit = charToNum(x[i]);
        result += digit * power;
        power *= base;
    }
    return result;
}

string oneComplement(string x, const unsigned short &base)
{
    string res = "";
    for (int i = 0; i < x.length(); i++)
        res += numToChar(base - 1);
    return difference(res, x, base);
}

string twoComplement(string x, const unsigned short &base)
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
        s = '-' + s;

    if (s == "")
        s = '0';
    return s;
}

int main()
{
    unsigned long long x, y;
    unsigned short base;
    int tmpX, tmpY, tmpBase;
    while (true)
    {
        cout << "Nhap he co so base (Nhap 1 de thoat): ";
        cin >> tmpBase;
        if (tmpBase == 1)
            break;
        cout << "Nhap x: ";
        cin >> tmpX;
        cout << "Nhap y: ";
        cin >> tmpY;
        if (tmpX < 0 || tmpY < 0 || tmpBase > 36 || tmpBase < 2)
        {
            cout << "Input khong dung voi yeu cau!\n";
            continue;
        }
        base = tmpBase;
        x = tmpX;
        y = tmpY;
        string SUM = sum(decimalToBase(x, base), decimalToBase(y, base), base);
        string DIFF = difference(decimalToBase(x, base), decimalToBase(y, base), base);
        cout << "\nTong: x + y = " << SUM;
        if (base != 10)
            cout << " (Decimal value: " << baseToDecimal(SUM, base) << " )\n";

        cout << "Hieu: x - y = " << DIFF;
        if (base != 10)
        {
            if (DIFF[0] == '-')
                cout << " (Decimal value: -" << baseToDecimal(DIFF.substr(1), base) << " || Two's complement: " << twoComplement(DIFF.substr(1), base) << " )";
            else
                cout << " (Decimal value: " << baseToDecimal(DIFF.substr(1), base) << " )";

        }
        cout << "\n\n";
    }
    return 0;
}