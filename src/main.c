#include<stdio.h>
#include<stdlib.h>
#define N 10002
int c[N], n;
int a[N],b[N];
int cmp_int(const void *e1, const void *e2){
    return *(int*)e1 - *(int*) e2;
}
int main(){
    scanf("%d", &n);
    for(int i=1;i<=2*n;++i) scanf("%d",c+i);
    qsort(c+1,2*n, sizeof(int), cmp_int);
    int j=1;
    for(int i=1;i<=2*n;i+=2,j++){
        if(c[i]!=c[i+1]){
            printf("-1\n");
            return 0;
        }
        a[j] = b[j] = c[i];
    }
    for(int i=1;i<=n;i++){
        printf("%d",a[i]);
    }
    printf("\n");
    for(int i=1;i<=n;i++){
        printf("%d",b[i]);
    }
    printf("\n");
    return 0;
}