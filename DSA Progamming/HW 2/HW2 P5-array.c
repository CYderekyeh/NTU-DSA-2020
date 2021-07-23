#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generator.h"

void mergepqr(int arr[], int q[], int r[], int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2], L_q[n1], R_q[n2], L_r[n1], R_r[n2];
	if (n1 == 1){
		if (r[left] > q[left]){
			int temp = r[left];
			r[left] = q[left];
			q[left] = temp;
		}
	}
	if (n2 == 1){
		if (r[mid + 1] > q[mid + 1]){
			int temp = r[mid + 1];
			r[mid + 1] = q[mid + 1];
			q[mid + 1] = temp;
		}
	}
    for (i = 0; i < n1; i++){
        L[i] = arr[left + i];
		L_q[i] = q[left + i];
		L_r[i] = r[left + i];
	}
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
		R_q[j] = q[mid + 1 + j];
		R_r[j] = r[mid + 1 + j];
	}
    i = 0; 
    j = 0; 
    k = left; 
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
			q[k] = L_q[i];
			r[k] = L_r[i];
			i++;
        }
        else if (L[i] > R[j]){
            arr[k] = R[j];
			q[k] = R_q[j];
			r[k] = R_r[j];
            j++;
        }else if (L_q[i] > R_q[j]){
            arr[k] = L[i];
			q[k] = L_q[i];
			r[k] = L_r[i];
			i++;
		}else{
            arr[k] = R[j];
			q[k] = R_q[j];
			r[k] = R_r[j];
            j++;
		}
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
		q[k] = L_q[i];
		r[k] = L_r[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
		q[k] = R_q[j];
		r[k] = R_r[j];
        j++;
        k++;
    }
}
void mergeSort(int p[], int q[], int r[], int left, int right){
    if (left < right){
        int m = left + (right - left) / 2;
        mergeSort(p, q, r, left, m);
        mergeSort(p, q, r, m + 1, right);
        mergepqr(p, q, r, left, m, right);
    }
}
void merge(int arr[], int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];	
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0; 
    j = 0; 
    k = left; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
			i++;
        }
        else{
            arr[k] = R[j];
            j++;
		}
		k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void showdata(int p[], int q[], int r[], int n){
	for (int i = 0; i < n; i++)
		printf("%d %d %d\n", p[i], q[i], r[i]);
}
long long ans;
long long c;
void count(int q[], int r[], int left, int mid, int right){
	int i = left;
	int n1 = mid + 1;
	int j = mid + 1;
	int n2 = right + 1;
	while (i < n1){
		if ((j == n2) || (q[i] < r[j])){
			ans += c;
			i++;
		}else{
			c++;
			j++;
		}
	}
}
void mergecount(int q[], int r[], int left, int right){
	if (left < right){
		int mid = left + (right - left) / 2;
		mergecount(q, r, left, mid);
		mergecount(q, r, mid + 1, right);
		c = 0;
		count(q, r, left, mid, right);
		merge(q, left, mid, right);
		merge(r, left, mid, right);
	}
}
int main(){
    generator.init();
    int t = generator.getT();
    while (t--) {
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
		mergeSort(p, q, r, 0, n - 1);
		ans = 0;
		mergecount(q, r, 0, n - 1);
		printf("%lld\n", ans);
	}
    return 0;
}