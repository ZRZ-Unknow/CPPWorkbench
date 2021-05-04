#include <iostream>
#include <assert.h>
using namespace std;

#define N 11

int double_compare(const void *p1, const void *p2){
    if(*(double*)p1 < *(double*)p2)
        return -1;
    else if(*(double*)p1 > *(double*)p2)
        return 1;
    else
        return 0;
}

void merge(void *base, unsigned int count, unsigned int element_size, int (*cmp)(const void*, const void*), int p, int q, int m){
    int n1 = m - p + 1;
	int n2 = q - m;
    void* L = malloc(n1*element_size);
	void* R = malloc(n2*element_size);
	for (int i = 0; i < n1; i++) {
		char *p1 = (char*) base + (p+i)*element_size;
        char *l = (char*) L + i*element_size;
        for(int k=0;k<element_size;k++){
            l[k] = p1[k];
        }  
	}
	for (int i = 0; i < n2; i++) {
        char *p1 = (char*) base + (i+m+1)*element_size;
        char *r = (char*) R + i*element_size;
        for(int k=0;k<element_size;k++){
            r[k] = p1[k];
        }  
	}
	int i = 0, j = 0;
	for (int r = p; r <= q; r++) {
        if(j>=n2){
            char *target = (char*) base + r*element_size;
            char *src = (char*) L + i*element_size;
            for(int k=0;k<element_size;k++){
                target[k] = src[k];
            }
            i++;
        }else if(i>=n1){
            char *target = (char*) base + r*element_size;
            char *src = (char*) R + j*element_size;
            for(int k=0;k<element_size;k++){
                target[k] = src[k];
            }
			j++;
        }else{
            if((*cmp)((char*)L + i*element_size, (char*)R + j*element_size) == -1){
                char *target = (char*) base + r*element_size;
                char *src = (char*) L + i*element_size;
                for(int k=0;k<element_size;k++){
                    target[k] = src[k];
                }
                i++;
            }else{
                char *target = (char*) base + r*element_size;
                char *src = (char*) R + j*element_size;
                for(int k=0;k<element_size;k++){
                    target[k] = src[k];
                }
	    		j++;
		    }
        }
	}
}

void mergesort(void *base, unsigned int count, unsigned int element_size, int (*cmp)(const void*, const void*), int p, int q){
    if(p<q){
        int m = (p+q)/2;
        mergesort(base, count, element_size, cmp, p, m);
        mergesort(base, count, element_size, cmp, m+1, q);
        merge(base, count, element_size, cmp, p, q, m);
    }
}
void merge_sort(void *base, unsigned int count, unsigned int element_size, int (*cmp)(const void *, const void *)){
    mergesort(base, count, element_size, cmp, 0, count-1);
}

void print(double *array){
    for(int i=0;i<N;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

int main(){
    double array[N];
    for(int i=0;i<N;i++){
        array[i] = N-i*1.3;
        if(i%2==0)
            array[i] = -array[i];
    }
    array[3] = 2;
    print(&array[0]);
    merge_sort(array, N, sizeof(double), double_compare);
    print(&array[0]);
    return 0;
}