#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack_o{
    int top;
    char *elements;
};
typedef struct stack_o Stack_opr;

void initStack(Stack_opr *s){
    s->top = 0;
    s->elements = (char *)malloc(1000000 * sizeof(char));
}

bool stackEmpty(Stack_opr *s){
    return (s->top <= 0);
}

void pushStack(Stack_opr *s, char c){
    s->elements[s->top] = c;
    s->top++;
}

char popStack(Stack_opr *s){
    s->top--;
    return (s->elements[s->top]);
}

char topStack(Stack_opr *s){
    return (s->elements[s->top - 1]);
}

bool precendece(char topStack, char token){
    return (((topStack == '*') || (topStack == '/')) || 
    (((topStack == '+') || (topStack == '-')) && ((token == '+') || (token == '-'))));
}

struct stack_d{
    int top;
    double *elements;
};
typedef struct stack_d Stack_d;

void initStackD(Stack_d *s){
    s->top = 0;
    s->elements = (double *)malloc(1000000 * sizeof(double));
}

bool stackDEmpty(Stack_d *s){
    return (s->top <= 0);
}

void pushStackD(Stack_d *s, double num){
    s->elements[s->top] = num;
    s->top++;
}

double popStackD(Stack_d *s){
    s->top--;
    return (s->elements[s->top]);
}

double topStackD(Stack_d *s){
    return (s->elements[s->top - 1]);
}

double result(char *rpn, int index);

int main(){
    /* turning input string into RPN string*/
    char token;
    char *rpn;
    rpn = (char *)malloc(1500000 * sizeof(char));
    rpn[0] = '_'; /* initialize the rpn */
    int index = 1;
    Stack_opr operator;
    Stack_opr *opr = &operator;
    initStack(opr);
    while (scanf("%c", &token) != EOF)
        if (token != '\n'){
            if (isdigit(token)){  /* if token is a number (or using ASCII) */
                rpn[index] = token; /* output token */
                index++;
            }
            else if (token == '(')     /* if token is a left parenthese */
                pushStack(opr, token); /* push token */
            else if (token == ')'){ /* if token is a right parenthese */
                while (topStack(opr) != '('){
                    rpn[index] = popStack(opr); /* pop and output token */
                    index++;
                }
                popStack(opr); /* remove left parenthese */
            }else
            { /* if token is an operator */
                while (precendece(topStack(opr), token))
                {
                    rpn[index] = popStack(opr); /* pop and output stack.top */
                    index++;
                }
                rpn[index] = '_'; /* split the number and operator */
                index++;
                pushStack(opr, token); /* push token to stack */
            }
        }else{
            /* output left operator in stack */
            while (!stackEmpty(opr)){
                rpn[index] = popStack(opr);
                index++;
            }
            printf("%.15f\n", result(rpn, index));  /* print the result */
            /* prepare for next line */
            /* initialize the rpn */
            rpn[0] = '_';
            index = 1;
            opr->top = 0;  /* initialize the stack */
        }
    free(rpn);
    free(opr->elements);
    system("pause");
    return 0;
}

double result(char rpn[], int length)
{
    Stack_d number;
    Stack_d *stack = &number;
    initStackD(stack);
    int index = 0;
    while (index < length)
    {
        char c = rpn[index];
        if (c == '_')
        {
            index++;
            c = rpn[index];
            double num = 0;
            while (isdigit(c))
            {
                num *= 10;
                int digit = c - '0';
                num += digit;
                index++;
                c = rpn[index];
            }
            pushStackD(stack, num);
        }
        else
        {
            double b = popStackD(stack);
            double a = popStackD(stack);
            double result;
            switch (c)
            {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            default:
                result = -1;
            }
            pushStackD(stack, result);
            index++;
        }
    }
    double result = popStackD(stack);
    free(stack->elements);
    return result;
}