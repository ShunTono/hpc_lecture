#include <cstdio>
#include <omp.h> 

void merge(int a[], int l, int m, int r){
  int temp[30];
  int w, x, y, z;
  x= l;
  z = m+1;
  for(w=l; x<=m && z<=r; w++){
    if(a[x]<=a[z]){
      temp[w] = a[x];
      x++;
    }else{
      temp[w] = a[z];
      z++;
    }
  }
  if(x>m){
    for(y=z; y<=r; y++){
      temp[w] = a[y];
      w++;
    }
  }else{
    for(y=x; y<=m; y++){
      temp[w] = a[y];
      w++;
    }
  }
  for(y=l; y<=r; y++)
    a[y] = temp[y];
}
 
void mergesort(int a[], int l, int r){
  int m;
  if(l<r){
m = (l+r)/2;
#pragma omp parallel sections num_threads(2)
{
#pragma omp section
  {
mergesort(a, l, m);
  }
#pragma omp section
    {
      mergesort(a, m+1, r);
    }
  }
  merge(a, l, m, r);
  }
}

int main(){
   int i;
   int a[] = {6, 5, 3, 1, 8, 7, 2, 4};
   int n = sizeof(a)/sizeof(a[0]);

   mergesort(a, 0, n-1);
   for(i=0; i<n; i++)
     printf("%d\n", a[i]);
return 0;
}
