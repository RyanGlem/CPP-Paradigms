#include <iostream>
#include <stdio.h>
#include <math.h>
#include <regex>
#include <string.h>

using namespace std;

string trim_string (string s);

// Omitting an enumerated type for the calculator operators because +, -, *, / can't be symbols
// User can type in any size string of an equation (1 + 3 * 15/20...) and the caculator will parse
// that equation into a postfix operators and then compute it
// PEMDAS
// Parentheses, Exponents, Multiplication, Division, Addition, Subtraction

bool validate_string (string s) {
    // 4 + 3 * 5 i
    stack <float> numbers;
    stack <char> ops;
    string s_trim = trim_string(s);
    int count_open = 0;
    int count_close = 0;

    const regex pattern ("([0-9]?[0-9]?[0-9]?)(\\.([0-9]?[0-9]?[0-9]?)){1}");
    bool sequence = regex_match (s_trim, pattern);

    for (int i = 0; i < s_trim.length(); i++) {
        if (s[i] == '(') { count_open++;}
        if (s[i] == ')') { count_close++;}


        if(s_trim[i] >= 'a' && s_trim[i] <= 'z' || s_trim[i] >= 'A' && s_trim[i] <= 'Z' ) {
            printf ("The expression contains a letter \n");
            return false;
        }

        if (isdigit (s_trim[i])) {
            numbers.push(s_trim[i]);
        } else if (s_trim[i] != '(' && s_trim[i] != ')') {
            ops.push(s_trim[i]);
        }
    }

    if (ops.size() >= numbers.size()) {
        printf ("Invalid number of operators and operands %ld %ld \n", ops.size(), numbers.size());
        return false;
    }

    if (count_open != count_close) {
        printf ("Wrong number of opening or closing braces \n");
        return false;
    }

    if (sequence) {
        printf ("The equation contains a float value which can't be computed in postfix \n");
        return false;
    }

    return true;
}

string trim_string (string s)
{
    regex r("\\s+");
    string s_trim = regex_replace(s, r, "");
    return s_trim;
}

int precedence(char m)
{
    if (m == '^')
    {
        return 3;
    }
    else if (m == '*' || m == '/')
    {
        return 2;
    }
    else if (m == '+' || m == '-')
    {
        return 1;
    }
    return 0;
}

float calculate_postfix(float a, float b, char op)
{
    // performing the operation on the operands
    switch (op)
    {
    case '^': // exponentials
        return (pow(b, a));
        break;
    case '*': // multiplication
        return (b * a);
        break;
    case '/': // division
        return (b / a);
        break;
    case '-': // subtraction
        return (b - a);
        break;
    case '+': // addition
        return (b + a);
        break;
    }
    return 0;
}

float infix_to_postfix(string equ)
{
    string equ_trim = trim_string (equ);
    stack<char> operators;
    stack<float> operands;
    int len = equ_trim.length();

    for (int i = 0; i < len; i++)
    {
        if (isdigit(equ_trim[i]))
        {
            float val = 0;
            while (i < equ_trim.length() && isdigit(equ_trim[i]))
            {
                val = (val * 10) + (equ_trim[i] - '0');
                i++;
            }
            operands.push(val);
            i--;
        }
        else if (equ_trim[i] == '(')
        {
            operators.push('(');
        }
        else if (equ_trim[i] == ')')
        {
            while (operators.top() != '(')
            {
                int a = operands.top();
                operands.pop();

                int b = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                operands.push(calculate_postfix(a, b, op));
            }

            if (!operators.empty())
            {
                operators.pop();
            }
        }
        else
        {
            while (!operators.empty() && precedence(equ_trim[i]) <= precedence(operators.top()))
            {
                int a = operands.top();
                operands.pop();

                int b = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                operands.push(calculate_postfix(a, b, op));
            }
            operators.push(equ_trim[i]);
        }
    }

    while (!operators.empty())
    {
        int a = operands.top();
        operands.pop();

        int b = operands.top();
        operands.pop();

        char op = operators.top();
        operators.pop();

        operands.push(calculate_postfix(a, b, op));
    }

    return operands.top();
}

int main()
{
    
    string flag;
    string equs;
    float answer = 0;

    do {
        
        printf ("ENTER in an equation \n");
        getline (cin, equs);

        if (!validate_string(equs)){
            printf ("Invalid equation\n");
            break;
        }

        answer = infix_to_postfix(equs);
        printf ("Answer: %.2f \n", answer);
        printf ("Continue? (y/n) \n");
        getline (cin, flag);
        if (flag == "y") {
            continue;
        }

    } while (flag != "n" );

    return 0;
}
