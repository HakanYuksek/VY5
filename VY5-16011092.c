#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct stack{
	int top;
	char val[SIZE];
	int top2;
	int value[SIZE];
}STACK;

void initialize(STACK *st){	
	st->top=0;
	st->top2=0;
}

int isFULL(STACK *st){
	if(st->top2==SIZE){
		return 1;
	}else{
		return 0;
	}
}

int isFull(STACK *st){
	if(st->top==SIZE){
		return 1;//stack is full
	}else{
		return 0;
	}
}

int isEMPTY(STACK *st){
	if(st->top2==0){
		return 1;
	}else{
		return 0;
	}
}

int isEmpty(STACK *st){
	if(st->top==0){
		return 1;
	}else{
		return 0;
	}
}

void PUSHforint(STACK *st,int v){
	if(!isFULL(st)){
		st->value[st->top2]=v;
		st->top2++;
	}else{
		printf("stack is full...\n");
	}
}

void push(STACK *st,char v){
	if(!isFull(st)){
		st->val[st->top]=v;
		st->top++;
	}else{
		printf("stack is full...\n");
	}
}



int POPforint(STACK *st){
	if(!isEMPTY(st)){
		st->top2--;
		return st->value[st->top2];
	}else{
		printf("stack is empty...\n");
	}	
}
char pop(STACK *st){
	if(!isEmpty(st)){
		st->top--;
		return st->val[st->top];
	}else{
		printf("stack is empty...\n");
	}
}



int toNumber(char *s){//it convert string to integer
	return atoi(s);
}

int size(char *str){//that function finds size of string
	int i=0;
	while(str[i]!=';'){
		i++;
	}
	return i;
}

char *ObtainPostFix(char *operation,STACK *st){//that function convert infix to postfix with using stack
	int i,j,k=0;
	char tmp;
	char *postfix=(char*)malloc(sizeof(char)*(strlen(operation)));
	for(i=0;i<size(operation);i++){
		postfix[i]=' ';
	}
	for(j=4;j<size(operation);j++){
			if(operation[j]=='('){
				push(st,operation[j]);
			}else if((operation[j])==')'){
				tmp=pop(st);
				while(tmp!='('){
					postfix[k]=tmp;
					k++;
					tmp=pop(st);		
				}	
			}else if(operation[j]=='+' || operation[j]=='-'){
				if(isEmpty(st)){
					push(st,operation[j]);	
				}else{
					tmp=pop(st);
					if(tmp=='('){
						push(st,'(');
						push(st,operation[j]);
					}else if(tmp=='/'){
						postfix[k]='/';
						k++;		
						while(!isEmpty(st) && (tmp=pop(st))!='('){
							postfix[k]=tmp;
							k++;
						}
						push(st,operation[j]);
					}else if(tmp=='*'){
						postfix[k]='*';
						k++;	
						while(!isEmpty(st) && (tmp=pop(st))!='('){
							postfix[k]=tmp;
							k++;	
						}		
						push(st,operation[j]);
					}else if(tmp!=operation[j]){
						postfix[k]=tmp;
						k++;
						push(st,operation[j]);
					}else{
						postfix[k]=tmp;
						k++;
						push(st,operation[j]);
					}
			}
			}else if(operation[j]=='/' || operation[j]=='*'){
				if(isEmpty(st)){
					push(st,operation[j]);
				}else{
					tmp=pop(st);
					if(tmp=='('){
						push(st,'(');
						push(st,operation[j]);
					}else if(tmp=='-' || tmp=='+'){
						push(st,tmp);
						push(st,operation[j]);				
					}else if(tmp!=operation[j]){
						postfix[k]=tmp;
						k++;
						push(st,operation[j]);
					}
				}
			}else if(isdigit(operation[j]) || isalpha(operation[j])){
				postfix[k]=operation[j];
				k++;
			}else if(operation[j]==' '){
				postfix[k]=operation[j];
				k++;
			}
			if(operation[j]!=' '){
				printf("postfix:");
				for(i=0;i<k;i++){
					printf("%c",postfix[i]);
				}
				printf("\t\t\tstack:");
				for(i=0;i<st->top;i++){
					printf("%c",st->val[i]);
				}	
				printf("\n");	
			}
			
		}
		while(!isEmpty(st)){
			postfix[k]=pop(st);
			k++;	
		}
	printf("ARA CIKIS--------->\n");
	printf("postfix:\n");
	for(i=0;i<size(operation);i++){
		printf("%c",postfix[i]);
	}	
	printf("\n");	
	return postfix;
}

int find(char a,char *var){
	int i=0;
	while(var[i]!=a && i<strlen(var)){
		i++;
	}
	if(i<strlen(var)){
		return i;
	}else{
		return -1;
	}
}

int solve(char *postfix,STACK *st,int *variables,char *var){//that function solves the expressions and returns the result
	int i,a,b,j,k;
	for(i=0;i<strlen(postfix);i++){
		j=i;
		if(isalpha(postfix[i]) && find(postfix[i],var)!=-1){
			PUSHforint(st,variables[find(postfix[i],var)]);
		}else if(postfix[i]=='+'){
			a=POPforint(st);
			b=POPforint(st);
			PUSHforint(st,(a+b));
		}else if(postfix[i]=='-'){
			a=POPforint(st);
			b=POPforint(st);
			PUSHforint(st,(b-a));
		}else if(postfix[i]=='*'){
			a=POPforint(st);
			b=POPforint(st);
			PUSHforint(st,(a*b));
		}else if(postfix[i]=='/'){
			a=POPforint(st);
			b=POPforint(st);
			PUSHforint(st,(b/a));
		}else if(isdigit(postfix[i])){
			k=0;
			char *B=(char*)malloc(sizeof(char)*5);
			while(isdigit(postfix[i])){
				B[k]=postfix[i];
				i++;
				k++;
			}
			PUSHforint(st,toNumber(B));
		}
		if(postfix[j]!=' '){
			printf("YIGIN:");
			for(j=0;j<st->top2;j++){
				printf("%d\t",st->value[j]);
			}
			printf("\n");
		}
	}

	int deger=POPforint(st);
	while(!isEMPTY(st)){
		if(!isEMPTY(st)){
			deger=POPforint(st);
		}
	}
	printf("degeri=%d\n",deger);
	return deger;
	
}

int main(){
	STACK *st;
	char *operation[SIZE];
	int *A;
	int i,j,t,n,k=0;
	char postfix[SIZE];
	int *variables;
	char *var;
	FILE *fp=fopen("input.txt","r");
	st=(STACK*)malloc(sizeof(STACK));
	initialize(st);
	i=0;
	while(!feof(fp)){
		operation[i]=(char*)malloc(sizeof(char)*50);
		fgets(operation[i],50,fp);
		i=i+1;
	}
	n=i;
	variables=(int*)malloc(sizeof(int)*n);
	var=(char*)malloc(sizeof(char)*n);
	A=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++){
		var[i]=' ';
		variables[i]=0;
	}
	for(i=0;i<n;i++){
		printf("%s\n",operation[i]);
	}
	for(i=0;i<n;i++){
		t=find(operation[i][0],var);
		if(t==-1){
			var[k]=operation[i][0];
			k++;
		}
	}//we create an array of variables(char)
	char **B=(char**)malloc(sizeof(char*)*n);
	for(i=0;i<n;i++){
		B[i]=(char*)malloc(sizeof(char)*n);
	}
	printf("\n\nINFIX--POSTFIX DONUSUMU\n\n");
	for(i=0;i<n;i++){
		printf("----------------------------------------\n");
		printf("%d inci islem icin:\n",i+1);
		B[i]=ObtainPostFix(operation[i],st);
	}
	printf("\n-----------------------------------------------------------------------\n");
	printf("TUM POSTFIX IFADELER\n---------------------------------------------------\n");
	for(i=0;i<n;i++){
		printf("%s\n",B[i]);
	}
	printf("--------------------------------------------------------------------------\n");
	printf("\nPOSTFIX IFADELERIN COZUMU...\n\n");
	for(i=0;i<n;i++){
		printf("%s icin\n",B[i]);
		j=find(operation[i][0],var);
		variables[j]=solve(B[i],st,variables,var);
		A[i]=variables[j];
		printf("----------------------------------------------------------------------\n");
	}
	printf("\nTOPLAM SONUC------>\n");
	for(i=0;i<n;i++){
		printf("%c = %d\n",operation[i][0],A[i]);
	}

	
	
	
	getch();	
	return 0;	
}
