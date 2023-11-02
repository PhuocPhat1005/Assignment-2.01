#include <iostream>
#include <math.h>
using namespace std;

string sum(const string &x, const string &y, const unsigned short base);
string difference(string x, string y, const unsigned short base);

char numToChar(const unsigned int &num)
{
    if (num >= 10)
        return num - 10 + 'A';
    return num + '0';
}

unsigned int charToNum(const char &c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return c - '0';
}

string form(string s, const unsigned short &base)
{
    while (s[0] == '0')
        s.erase(0, 1);
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
    unsigned short value; // Vi value = num % base, nen khai bao theo kieu du lieu cua base
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

unsigned long long baseToDecimal(string x, const unsigned short &base)
{
    unsigned long long result = 0;
    unsigned long long power = 1;
    for (int i = x.size() - 1; i >= 0; i--)
    {
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
        res += numToChar(base - 1);  // Tao chuoi
    return difference(res, x, base); // Return chuoi vua tao tru x de lay bu 1
}

string twoComplement(string x, const unsigned short &base)
{
    return sum(oneComplement(x, base), "1", base); // Bu 1 + '1' la bu 2
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
    if (flag) // Neu 'nho 1'
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
        swap(x, y); // Swap string
        swap(i, j); // Swap lenght
    }
    while (i > 0)
    {
        if (j > 0)
            value = charToNum(x[i - 1]) - charToNum(y[j - 1]);
        else
            value = charToNum(x[i - 1]);
        if (flag) // Neu 'nho 1'
        {
            value--;
            flag = false;
        }
        if (value < 0)
        {
            value += base;
            flag = true; // 'nho 1' cho ki tu tiep theo
        }
        i--;
        j--;
        if (value || i) // Neu value khac 0 hoac i khac 0
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
    long long tmpX, tmpY, tmpBase;
    while (true)
    {
        cout << "Nhap he co so base (Nhap 1 de thoat): ";
        cin >> tmpBase;
        if (tmpBase == 1)
            break;
        if (tmpBase > 36 || tmpBase < 2)
        {
            cout << "Input khong dung voi yeu cau!\n\n";
            continue;
        }
        cout << "Nhap x: ";
        cin >> tmpX;
        cout << "Nhap y: ";
        cin >> tmpY;
        if (tmpX < 0 || tmpY < 0)
        {
            cout << "Input khong dung voi yeu cau!\n\n";
            continue;
        }
        base = tmpBase;
        x = tmpX;
        y = tmpY;
        string SUM = sum(decimalToBase(x, base), decimalToBase(y, base), base);
        string DIFF = difference(decimalToBase(x, base), decimalToBase(y, base), base);
        cout << "\nTong: x + y = " << SUM;
        if (base != 10)
            cout << " (Decimal value: " << baseToDecimal(SUM, base) << " )";
        cout << endl;
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
    cout << "Thoat chuong trinh thanh cong!";
    return 0;
}