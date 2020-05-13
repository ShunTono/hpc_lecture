#include <cstdio>

void countsort(int a[], int size, int m){
  int sort_a[size];
  int count[10] = {0};

  for(int i=0; i<size; i++){
    count[(a[i] / m) % 10]++;
  }

  for(int i=1; i<10; i++){
    count[i] += count[i-1];
  }

  for(int i=size-1; i>=0; i--){
    sort_a[count[(a[i] / m) % 10] -1] = a[i];
    count[(a[i] / m) % 10]--;
  }

  for(int i=0; i<size; i++){
    a[i] = sort_a[i];
  }
}

void bucketsort(int a[], int size){
  int max = a[0];
  for(int i=1; i<size; i++){
    if(a[i] > max){
      max = a[i];
    }
  }

  for(int m=1; max / m >0; m *= 10){
    countsort(a, size, m);
  }
}

int main(){
  int i;
  int a[] = {29, 25, 3, 49, 9, 37, 21, 43};
  int n = sizeof(a)/sizeof(a[0]);

  bucketsort(a, n);
  for(i=0; i<n; i++)
    printf("%d\n", a[i]);
return 0;
}
