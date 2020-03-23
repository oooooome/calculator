#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

double analyze(string expression);
double cal(string expr);
double simple_cal(double x, double y, char s);
string rest(string e, int len, string s, char op, bool is_neg);

double analyze(string expression)
{
    int len = expression.length();
    string ns = "";
    if (expression.find('(') != string::npos && expression.find(')') != string::npos)
    {
        string ex = expression;
        while (ex.find('(') != string::npos && ex.find(')') != string::npos)
        {
            int e_len = ex.length();
            stack<size_t> pos_s;
            int f = -1;
            for (size_t i = 0; i < e_len; i++)
            {
                if (ex[i] == '(')
                {
                    pos_s.push(i);
                    if (f == -1)
                        f = i;
                }
                else if (ex[i] == ')')
                    pos_s.pop();
                if (pos_s.empty() && f != -1)
                {
                    string center = ex.substr(size_t(f) + 1, i - f - 1);
                    double result = analyze(center);
                    string r = std::to_string(result);
                    ex = ex.substr(0, f) + r + ex.substr(i + 1, len - i);
                    f = -1;
                    break;
                }
            }
        }
        ns = ex;
    }
    else if ((expression.find('(') == string::npos && expression.find(')') != string::npos) || (expression.find('(') != string::npos && expression.find(')') == string::npos))
        throw exception("输入的表达式有误");
    else
        ns = expression;
    return cal(ns);
}

double cal(string expr)
{   
    string e = expr;
    bool is_negative = false;
    if (e.length() == 0)
        return 0;
    char h = e[0];
    if (h == '+' || h == '*' || h == '/')
        throw exception("输入的表达式有误");
    else if (h == '-') 
    {
        e = e.substr(1);
        for (int i = 0; i < e.length(); i++)
        {
            if (e[i] == '+')
                e[i] = '-';
            else if (e[i] == '-')
                e[i] = '+';
        }
        is_negative = true;
    } 
    stringstream ss;
    int len = e.length();
    double r;
    string s = e;
    for (int i = 0; i < len; i++)
    {
        switch (e[i])
        {
        case '+':
            s[i] = '1';
            break;
        case '-':
            s[i] = '1';
            break; 
        case '*':
            s[i] = '2';
            break; 
        case '/':
            s[i] = '2';
            break;
        default:
            s[i] = '0';
        }
    }
    if (s.find('2') != string::npos)
    {
        string ne = rest(e, len, s, '2', is_negative);
        r = cal(ne);
    }
    else if (s.find('1') != string::npos)
    {
        string ne = rest(e, len, s, '1', is_negative);
        r = cal(ne);
    }
    else
    {
        ss << e;
        ss >> r;
    }
    if (is_negative)
        return -r;
    else
        return r;
}

double simple_cal(double x, double y, char s)
{
    double result = 0.0;
    switch (s)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        result = x / y;
    }
    return result;
}

string rest(string e, int len, string s, char op, bool is_neg)
{
    size_t index = s.find(op);
    size_t f, b;
    size_t t = 1;
    for (int i = index - 1; i >= 0 && s[i] == '0'; i--)
        f = i;
    if (s[index + 1] == '1') {
        if((!is_neg && e[index + 1] == '-') || (is_neg && e[index + 1] == '+'))
            t = 2;
    }
    for (int i = index + t; i <= len - 1 && s[i] == '0'; i++)
        b = i;
    string x, y;
    double x1, y1;
    x = e.substr(f, index - f);
    if (is_neg && e[index + 1] == '+') 
    {
        y = "-" + e.substr(index + 2, b - index);
    }
    else
    {
        y = e.substr(index + 1, b - index);
    }
    x1 = stod(x);
    y1 = stod(y);
    double result = simple_cal(x1, y1, e[index]);
    string r_s = std::to_string(result);
    string front, back;
    front = e.substr(0, int(f));
    back = e.substr(b + 1, size_t(len) - 1);
    string ne = front + r_s + back;
    return ne;
}


int main()
{
    string exp = "";
    double result;
    cout << "请输入表达式" << endl;
    cin >> exp;
    result = analyze(exp);
    cout << result << endl;
    return 0;
}