#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 100005
int c2i(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}
struct Stack{
    int top;
    char elements[SIZE];
};
typedef struct Stack Stack;

void init(Stack *s){
    s->top = 0;
}
bool empty(Stack s){
    return (s.top <= 0);
}
void push(Stack *s, char c){
    s->elements[s->top] = c;
    s->top++;
}

char pop(Stack *s){
    s->top--;
    return (s->elements[s->top]);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        char D[SIZE];
        char G[SIZE];
        scanf("%s%s", D, G);
        int lenD = strlen(D);
        int lenG = strlen(G);
        int o[64] = {0};
        int p[64] = {0};
        for (int i = 0; i < lenG; i++)
            o[c2i(G[i])]++;
        int s = 0;
        int count = 0;
        int s_index = -1;
        int minlen = lenD;
        /* find garbled text if existing*/
        if (lenD >= lenG){
            for (int i = 0; i < lenD; i++){
                if (o[c2i(D[i])] == 0)
                    continue;
                p[c2i(D[i])]++;
                if (p[c2i(D[i])] <= o[c2i(D[i])])
                    count++;
                if (count == lenG){
                    while(s < i){
                        if (o[c2i(D[s])] == 0){
                            s++;
                            continue;
                        }
                        if (p[c2i(D[s])] <= o[c2i(D[s])])
                            break;
                        p[c2i(D[s])]--;
                        s++;
                    }
                    int anslen = i - s + 1;
                    if (anslen < minlen){
                        minlen = anslen;
                        s_index = s;
                    }               
                }
            }
        }
        /* remove garbled text if existing */
        if (s_index != -1){
            int len_tail = lenD - s_index - minlen;
            memmove(D + s_index, D + s_index + minlen, len_tail);
            memset(D + s_index + len_tail, '\0', 1);
            lenD = lenD - minlen;
        }
        if (lenD == 1){
            puts(D);
            continue;
        }
        /* find blocks */
        int left = 0, right = left + 1;
        int h[2][2] = {{1, 0}, {0, 1}}, t[2][2] = {{1, 0}, {0, 1}};
        char ans[SIZE];
        int len_ans = 0;
        do {
            int x = c2i(D[right - 1]);
            int h00 = h[0][0] * x + h[0][1];
            int h01 = h[0][0];
            int h10 = h[1][0] * x + h[1][1];
            int h11 = h[1][0];
            h[0][0] = h00;
            h[0][1] = h01;
            h[1][0] = h10;
            h[1][1] = h11;
            int y = c2i(D[lenD - right]);
            int t00 = t[0][0] * y + t[1][0];
            int t01 = t[0][1] * y + t[1][1];
            int t10 = t[0][0];
            int t11 = t[0][1];
            t[0][0] = t00;
            t[0][1] = t01;
            t[1][0] = t10;
            t[1][1] = t11;
            if (h[0][0] != t[0][0] || h[0][1] != t[0][1] || 
                h[1][0] != t[1][0] || h[1][1] != t[1][1]){
                right++;  
                continue;
            }else{
                /* check whether spurious hit */
                bool match = true;
                for (int i = left; i < right; i++)
                    if (D[i] != D[lenD - right - left + i]){
                        right++;
                        match = false;
                        break;
                    }
                if (!match)
                    continue;
                else{
                    h[0][0] = 1;
                    h[0][1] = 0;
                    h[1][0] = 0;
                    h[1][1] = 1;
                    t[0][0] = 1;
                    t[0][1] = 0;
                    t[1][0] = 0;
                    t[1][1] = 1;
                }
                /* copy substring to ans if string match */
                for (int i = left; i < right; i++){
                    ans[len_ans] = D[i];
                    len_ans++;
                }
                ans[len_ans] = '|';
                len_ans++;
                /* keep matching */
                left = right;
                right = left + 1;
            }
        } while (right <= lenD / 2);
        /* output ans */
        for (int i = 0; i < len_ans; i++)
            printf("%c", ans[i]);
        /* print the no_match substring to ans */
        int tocopy = lenD - 2 * left;
        int tail;
        if (tocopy == 0)
            tail = len_ans - 1;
        else
            tail = len_ans;
        for (int i = 0; i < tocopy; i++){
            printf("%c", D[left + i]);
        }
        Stack block;
        init(&block);
        for (int i = tail - 1; i >= 0; i--){
            if (ans[i] != '|')
                push(&block, ans[i]);
            else{
                while (!empty(block))
                    printf("%c", pop(&block));
                printf("%c", ans[i]);
            }
        }
        while (!empty(block))
            printf("%c", pop(&block));
        printf("\n");
    }
    system("pause");
    return 0;
}
