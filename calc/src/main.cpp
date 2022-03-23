// Ryan Glemaud
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <string.h>

using namespace std;

string trim_string(string s);
// User can type in any size string of an equation (1 + 3 * 15/20...) and the caculator will parse
// Determines precendec of corresponding values
// must do 0~[Number] for sqrt or the number will be invalid
// that equation into a postfix operators and then compute it
// POSTFIX CAN'T COMPUTE USER INPUTTED FLOAT VALUES 9.111... etc are all invalid strings
// PEMDAS
// Parentheses, Exponents, Multiplication, Division, Addition, Subtraction

struct Calculator
{
    // Enumerated type
    enum Ops
    {
        Add,
        Subtract,
        Multiply,
        Divide,
        Sqrt
    };

    // Caclculate method that computes and returns value depending on the operator
    float calculate(float a, float b, char op)
    {
        switch (op)
        {
        case '~':
            return (sqrt(a));
            break;
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
};

// Validates the inputted string with trimmed white space
bool validate_string(string s, ofstream& os)
{
    // Two stacks to count the valid amount of numbers and operators
    stack<float> numbers;
    stack<char> ops;

    string s_trim = trim_string(s);

    // Count for proper number of closing or opening braces
    int count_open = 0;
    int count_close = 0;

    // Regex expression to check if the string contains a float value
    const regex pattern("([0-9]?.[0-9]?)+(\\.([0-9]?[-+^/*~]?))");
    bool sequence = regex_match(s_trim.begin(), s_trim.end(), pattern);
    cout << sequence << endl;
    cout << s_trim << "\n";

    for (int i = 0; i < s_trim.length(); i++)
    {
        // Counting braces
        if (s_trim[i] == '(')
        {
            count_open++;
        }
        if (s_trim[i] == ')')
        {
            count_close++;
        }

        // If there is a letter inside the string, print an error
        if (s_trim[i] >= 'a' && s_trim[i] <= 'z' || s_trim[i] >= 'A' && s_trim[i] <= 'Z')
        {
            os << ("The expression contains a letter \n");
            return false;
        }

        // Adding the digits and operators to a stack
        if (isdigit(s_trim[i]))
        {
            numbers.push(s_trim[i]);
        }
        else if (s_trim[i] != '(' && s_trim[i] != ')')
        {
            ops.push(s_trim[i]);
        }
    }

    // Checks is braces are pairwise
    if (count_open != count_close)
    {
        os << ("Wrong number of opening or closing braces \n");
        return false;
    }

    // Checks if the numbers and operators are correctly paired
    if (ops.size() >= numbers.size())
    {
        os << ("Invalid number of operators and operands \n");
        return false;
    }

    // Checks for float values
    if (sequence)
    {
        os << ("The equation contains a float value which can't be computed in postfix \n");
        return false;
    }

    return true;
}

// Regex expression to trim white space
string trim_string(string s)
{
    regex r("\\s+");
    string s_trim = regex_replace(s, r, "");
    return s_trim;
}

// Order precedence to caculate the string, returns number order
int precedence(char m)
{
    if (m == '~')
    {
        return 4;
    }
    else if (m == '^')
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

// Converting from infix to postfix then caculating using stacks
float infix_to_postfix(string equ)
{
    Calculator cl;
    string equ_trim = trim_string(equ);
    stack<char> operators;
    stack<float> operands;
    int len = equ_trim.length();

    for (int i = 0; i < len; i++)
    {
        if (isdigit(equ_trim[i]))
        // There may be multidgit values, so multiply each corressponding element by 10 and push them in the stack
        // 32 will yield 30 + 2 and then push it to the stack until an operator is hit
        {
            float val = 0;
            while (i < equ_trim.length() && isdigit(equ_trim[i]))
            {
                val = (val * 10) + (equ_trim[i] - '0');
                i++;
            }
            operands.push(val);

            // Subtracting the offset
            i--;
        }

        // If there are braces, caculate everything in the braces first and then move on
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

                operands.push(cl.calculate(a, b, op));
            }

            if (!operators.empty())
            {
                operators.pop();
            }
        }
        else
        {
            // Computing the precendec order expression
            while (!operators.empty() && precedence(equ_trim[i]) <= precedence(operators.top()))
            {
                int a = operands.top();
                operands.pop();

                int b = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                operands.push(cl.calculate(a, b, op));
            }
            operators.push(equ_trim[i]);
        }
    }

    // Computign the rest of the parsed string
    while (!operators.empty())
    {
        int a = operands.top();
        operands.pop();

        int b = operands.top();
        operands.pop();

        char op = operators.top();
        operators.pop();

        operands.push(cl.calculate(a, b, op));
    }

    return operands.top();
}

int main()
{

    ofstream out_stream("output.txt");
    ifstream in_stream;
    string line;
    string flag;
    string equs;
    bool cont = true;
    float answer = 0;
    in_stream.open("input.txt"); // opening the file.

    if (in_stream.is_open())
    {
        while (getline(in_stream, line) && cont)
        {
            out_stream << "ENTER in an equation \n";
            out_stream << line << "\n";

            if (!validate_string(line, out_stream))
            {
                out_stream << "Invalid equation\n";
                // break;
            }
            else
            {
                answer = infix_to_postfix(line);
                out_stream << ("Answer: %.3f", answer) << "\n";
                out_stream << ("Continue? (y/n) \n");
                getline (in_stream, line);
                out_stream << line << "\n";
                if (line == "y")
                {
                    continue;
                } else if (line == "n") {
                    cont = false;
                }
            }
        }
        in_stream.close();
    }

    do
    {

        printf("ENTER in an equation \n");
        getline(cin, equs);

        if (!validate_string(equs, out_stream))
        {
            printf("Invalid equation\n");
            // break;
        }
        else
        {
            answer = infix_to_postfix(equs);
            printf("Answer: %.3f \n", answer);
            printf("Continue? (y/n) \n");
            getline(cin, flag);
            if (flag == "y")
            {
                continue;
            }
        }

    } while (flag != "n");
    return 0;
}
