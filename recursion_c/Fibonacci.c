#include<stdio.h>
// 0 1 1 2 3 5 8 13 21 34 55

int main(){
int fibo();
int *v;
int n,i;
printf("Ate qual numero deseja saber: \n");
scanf("%i",&n);
v = (int*)malloc(n*sizeof(int));
for(i=0;i<n;i++){
v[i]= 0;

}

fibo(n,v);

}
 

int fibo(int n,int v[]){

if(n==1){
v[n]=0;
return 0;
printf(" %d",v[n]);
}

if(n==2){
v[n]=1;
return 1;  
printf(" %d",v[n]);  
}
else{
v[n] = fibo(n-1,v)+fibo(n-2,v);    
}

printf(" %d",v[n]);
return v[n];
}