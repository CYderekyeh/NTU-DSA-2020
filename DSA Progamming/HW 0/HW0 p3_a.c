#include <stdio.h>
#include <stdlib.h>

int main(void){
    int fake_a [] = {1, 3};
    int fake_b [] = {2, 4};
    int *real_a = fake_a;
    int *real_b = fake_b;

    for (int i=0; i <2; i++)
        printf("%d ", *( real_a + i));
    for (int i=0; i <2; i++)
        printf("%d ", *( real_b + i));
    
    int *tmp = real_a;
    real_a = real_b;
    real_b = tmp;

    for (int i=0; i <2; i++)
        printf("%d ", *( real_a + i));
    for (int i=0; i <2; i++)
        printf("%d ", *( real_b + i));

    system("pause");
    return 0;
}
