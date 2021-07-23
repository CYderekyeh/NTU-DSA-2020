#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define SIZE 257

void rev(char *string, int len);
int array_size(int *array, int size);
void divided_by_2(int *ptr, int size);
bool comparison(int *m, int *n, int size);
void substraction(int *m, int *n, int size);
void twice(int array[], int k, int size);


int main(void){
    char string_1[SIZE], string_2[SIZE];
    scanf("%s%s", string_1, string_2);
    int len_a = strlen(string_1);
    int len_b = strlen(string_2);

    char string_a[len_a], string_b[len_b];
    strcpy(string_a, string_1);
    strcpy(string_b, string_2);
    /*reverse the string*/
    rev(string_a, len_a); 
    rev(string_b, len_b);

    int max_size = (len_a > len_b) ? len_a : len_b;

    int a[SIZE] = {0}, b[SIZE] = {0};
    for (int i = 0; i < max_size; i++){
        if (i >= len_a)
            a[i] = 0;
        else
            a[i] = string_a[i] - '0';
    }
    for (int i = 0; i < max_size; i++){
        if (i >= len_b)
            b[i] = 0;
        else
            b[i] = string_b[i] - '0';
    }
    int k = 0; /* k for power*/
    int *m = a, *n = b;
    int m_size = len_a, n_size = len_b;
    /*binary algorithm for GCD */
    while(m_size != 0 && n_size != 0){
        if (m[0] % 2 == 0 && n[0] % 2 == 0){
            k++;
            divided_by_2(m, m_size);
            divided_by_2(n, n_size);
        }else if (m[0] % 2 == 0)
            divided_by_2(m, m_size);
        else if (n[0] % 2 == 0)
            divided_by_2(n, n_size);

        if (comparison(n, m, max_size)){
            int *temp = n;
            n = m;
            m = temp;
            int tep = m_size;
            m_size = n_size;
            n_size = tep;
        }
        substraction(m, n, max_size);
        m_size = array_size(m, m_size);
        n_size = array_size(n, n_size);
        max_size = (m_size > n_size) ? m_size : n_size;
    }

    max_size = (len_a > len_b) ? len_a : len_b;
    twice(n, k, max_size);

    bool zero = true;
    for (int i = (max_size - 1); i >= 0; i--){
        if (n[i] != 0 && zero)
            zero = false;
        if (!zero)
            printf("%d", n[i]);
    }
    system("pause");
    return 0;
}

void rev(char string[], int len){
    for (int i = 0; i < len / 2; i++){
        int temp = string[i];
        string[i] = string[len -  i - 1];
        string[len - i - 1] = temp;
    }
    return;
}

int array_size(int *array, int size){
    for (int i = size; i > 0; i--){
        if (array[i - 1] != 0){
            return i;
        }
    }
    return 0;
}

void twice(int *array, int k, int size){
    int carry = 0;
    for (int i = 0; i < k; i++)
        for (int index = 0; index < size; index++){
            int digit = array[index];
            if (digit == 0 && carry == 0)
                 continue;
        
            digit *= 2;
            digit += carry;
            if (digit >= 10){
                array[index] = digit % 10;
                carry = digit / 10;
            }else{
                array[index] = digit;
                carry = 0;
        } 
    }
    return;
}

void divided_by_2(int *ptr, int size){
    int digit = ptr[0];
    for (int index = 0; index < size; index++){
        if (index == size - 1){
            ptr[index] = digit / 2;
            break;
        }
        int prev = ptr[index + 1];
        if (prev % 2 == 0)
            ptr[index] = digit / 2;
        else{
            ptr[index] = (digit + 10) / 2;
            ptr[index + 1] -= 1;
        }
        digit = ptr[index + 1];
        }
    
    return;
}

bool comparison(int *m, int *n, int size){
    bool larger = false;
    for (int index = 0; index < size; index++){
        if (m[index] > n[index])
            larger = true;
        else if (n[index] > m[index]){
            larger = false;
        }
    }
    
    return larger;
}

void substraction(int *m, int *n, int size){
    int borrow = 0;
    for (int i = 0; i < size; i++){
        int digit = m[i] - n[i];
        digit -= borrow;
        if (digit >= 0){
            m[i] = digit;
            borrow = 0;
        }else{
            m[i] = digit + 10;
            borrow = 1;
        }
    }

    return;
}


