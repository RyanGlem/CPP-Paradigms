#include <iostream>
#include <stdio.h>

using namespace std;

// Omitting an enumerated type for the calculator operators because +, -, *, / can't be symbols
// User can type in any size string of an equation (1 + 3 * 15/20...) and the caculator will parse
// that equation into a postfix expression and then compuute it

struct Calc {
    
    // This struct will not calculate the values directly, instead it will be used to convert the equation string
    // into a readable postfix value
    
    Calc (float a, float b, char op) {
        switch (op) {
        case '+':
            printf ("%.2f \n", a + b);
            break;
        case '-':
            printf ("%.2f \n", a - b);
            break;
        case '/':
            printf ("%.2f \n", a / b);
            break;
        case '*':
            printf ("%.2f \n", a * b);
            break;
        }
    }
};

int main() {
    printf ("Simple calculator struct example using constructor \n");
    Calc (7, 4, '+');
    Calc (4, 15, '*');
    Calc (453, 67, '/');
    Calc (12.45, 7.89, '-');

    return 0;
}
