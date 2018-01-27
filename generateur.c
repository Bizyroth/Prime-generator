#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_T 1000000000000000
/*---------------------------fait a*b mod m-------------------------------*/

long unsigned mulmod(long unsigned a, long unsigned b, long unsigned m){
	return ((a%m)*(b%m))%m;
}
/*------------------------------------------------------------------------*/
/*----------------renvoie l tq 2^l*t=x avec t impair----------------------*/

int last_one(long unsigned x){
	long res=x;
	int r=0;
	if(res==0){
		return -1;
	}
	while((res&1)==0){
		res>>=1;
		r++;
	}
	return r;
}
/*-------------------------------------------------------------------------*/
/*----------------renvoie un entier aleatoire x tq x in [a,b[-------------------*/

long long rand_a_b(long long a, long long b){
    return (long long)rand()%(b-a) +a;
}
/*-------------------------------------------------------------------------------*/
/*--------------------------------calcul a^n mod m-------------------------------*/

long unsigned expmod(long unsigned a, long unsigned n, long unsigned m){
	long i=n;
	long res=1;
	long temp =a;
	
	while(i>0){
		if(i&1!=0){
			res=mulmod(res, temp, m);			
		}
			temp=mulmod(temp, temp, m);
			i>>=1;
		
	}
	return res;
}
/*----------------------------------------------------------------------------------*/
/*renvoie 0 si n est composé en base a et 1 si il est probablement premier en base a*/

int TestMiller(int n, int a){
	int power;
	int t;
	int b;	
	int j;
	
	power=last_one(n-1);
	t=(n-1)>>power;
	b=expmod(a, t, n);
	if(b==1){
		return 1;
	}
	for(j=0; j<power; j++){
		if(b==(n-1)){
			return 1;
		}
		if(b==1){
			return 0;
		}
		b=expmod(b, 2, n);
	}
	return 0;
}
/*----------------------------------------------------------------*/
/*-----------applique le test de miller k fois sur des temoisn aleatoire-------------*/
/*----------renvoie 0 si n est compse 1 si il est probablement premier---------------------*/
int miller(int n, int k){
	int i, j;
	int alea;
	if(n==2){
		return 1;
	}
	if((n&1)==0){
		return 0;
	}
	srand(time(NULL));
	
	for(i=0; i<k; i++){
		alea=rand_a_b(2, n-1);
		if(TestMiller(n, alea)==0){
			return 0;
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------------------*/
/*genere un entier aleatoire de k bit*/

long long alea_k(int k){
	long long a=expmod(10, k-1, MAX_T);
	long long b=expmod(10, k, MAX_T);
	return rand_a_b(a,b); 	
}

long long genere_premier(int k, int t){
	srand(time(NULL));
	long long n=alea_k(k);
	while(miller(n,t)!=1){
		n=alea_k(k);
	}
	return n;
}
		
int main(){
	int k;
	printf("Entrez la taille du nombre premier desire\n");
	
	scanf("%d", &k);
	long long p=genere_premier(k, 10);
	printf("%llu est probablement premier\n", p);
	return 0;
}






