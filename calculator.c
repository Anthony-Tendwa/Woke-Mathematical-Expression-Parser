#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ADD "add-up"
#define SUBTRACT "split-the-bill"
#define MULTIPLY "smash"
#define DIVIDE "slay"
#define PERCENT "flex"
#define POWER "glow-up"

double performOperation(double num1, char* operator, double num2) {
    if (strcmp(operator, ADD) == 0) return num1 + num2;
    if (strcmp(operator, SUBTRACT) == 0) return num1 - num2;
    if (strcmp(operator, MULTIPLY) == 0) return num1 * num2;
    if (strcmp(operator, DIVIDE) == 0) {
        if (num2 == 0) {
            printf("Error: Division by zero\n");
            exit(1);
        }
        return num1 / num2;
    }
    if (strcmp(operator, PERCENT) == 0) return num1 * (num2 / 100.0);
    if (strcmp(operator, POWER) == 0) return pow(num1, num2);

    printf("Error: Unknown operator '%s'\n", operator);
    exit(1);
}

int main() {
    while (1) {
        char input[1000];
        printf("Enter an expression: ");
        fgets(input, sizeof(input), stdin);

        char* token = strtok(input, " \n");
        double result = 0.0;
        int isResultSet = 0;

        while (token != NULL) {
            if (strcmp(token, ADD) == 0 || strcmp(token, SUBTRACT) == 0 ||
                strcmp(token, MULTIPLY) == 0 || strcmp(token, DIVIDE) == 0 ||
                strcmp(token, PERCENT) == 0 || strcmp(token, POWER) == 0) {
                char* operator = token;
                token = strtok(NULL, " \n");
                if (token != NULL) {
                    double operand = atof(token);
                    result = performOperation(result, operator, operand);
                    isResultSet = 1;
                } else {
                    printf("Error: Operator '%s' requires an operand\n", operator);
                    break;
                }
            } else if (atof(token) != 0 || strcmp(token, "0") == 0) {
                if (isResultSet) {
                    printf("Error: Expected an operator, found '%s'\n", token);
                    break;
                }
                result = atof(token);
                isResultSet = 1;
            } else {
                printf("Error: Unrecognized token '%s'\n", token);
                break;
            }
            token = strtok(NULL, " \n");
        }

        if (isResultSet) printf("Result: %.1f\n");

        char response;
        printf("Do you want to calculate again? (y/n): ");
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y') break;
        getchar();
    }
    return 0;
}
