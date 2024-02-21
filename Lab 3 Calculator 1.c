/*
@author Malcolm ALvarado
@date 09/15/2023
@project CSE130 Lab 3  Calculator
*/

#include "stdio.h"
#include "math.h"
// Function: 1. well organized source code 2. Reusage

void addition();
void subtraction();
void multiplication();
void division();
void modulus();
void test_if_prime();

void display_menu();

int main(){
	int option = 0;
	while(option !=7){
		display_menu();
		printf("\nPlease choose an operation:");
		scanf("%d",&option);
		switch(option){
			case 1:
				addition();
				break;
			case 2:
				subtraction();
				break;
			case 3:
				multiplication();
				break;
			case 4:
				division();
				break;
			case 5:
				modulus();
				break;
			case 6:
				test_if_prime();
				break;
			default:
				break;
		}
	}
	return 0;
}

void display_menu(){
	printf(
			"\n========================="
			"\n----(Calculator Menu)----"
			"\n(1) Addition"
			"\n(2) Subtraction"
			"\n(3) Multiplication"
			"\n(4) Division"
			"\n(5) Modulus(Inegers only)"
			"\n(6) Test if Prime(Integers Only)"
			"\n(7) Exit"
			"\n--------------------------"
			"\n"
	);
}

void take_input_2_float(float *a, float *b){
	printf("Enter the first number: ");
	scanf("%f" ,a);
	printf("\nEnter the second number");
	scanf("%f",b);
}

void take_input_2_int(int *a, int *b){
	printf("\nEnter the first number(Integer)");
	scanf("%d",a);
	printf("\nEnter the second number(Integer): ");
	scanf("%d",b);
}

void take_input_1_int(int *a){
	printf("\nEnter the number(Integer): ");
	scanf("%d", a);
}

void addition(){
	float a,b;
	take_input_2_float(&a,&b);
	float c = a + b;
	printf("\n%f + %f = %f", a,b,c);
}

void subtraction(){
	float a, b;
	take_input_2_float(&a,&b);
	float c = a - b;
	printf("\n%f - %f = %f", a, b, c);
}

void multiplication(){
	float a,b;
	take_input_2_float(&a,&b);
	float c = a * b;
	printf("\n%f * %f = %f", a,b,c);
}
void division(){
	float a,b;
	take_input_2_float(&a,&b);
	if( b == 0){
		printf("\nError: number can not be divided by ZERO!");
	}
	else{
		float c = a / b;
		printf("\n%f / %f = %f", a,b,c);
	}
}
void modulus(){
	int a,b;
	take_input_2_int(&a,&b);
	if( b == 0){
		printf("\nError: number can not be divided by ZERO!");
	}
	else{
		int mod = a % b;
		printf("\n%d mod %d = %d", a,b,mod);
	}

}

int is_prime(int a){
	if(a<= 1){
		return 0;
	}
	// 2 is prime
	if(a == 2){
		printf("\n%d is prime");
		return 1;
	}
	// all the other even is not prime
	if(0 == a%2){
		return 0;
		
	}
	// let i increase from 3 to the square root of a, with step of 2,
	// if a % i ==0, a is not a prime number
	int sr = sqrt(a);
	for(int i=3; i<sr; i+=2){
		if(0 == a % i){
			return 0;
		}
	}
	//a is a prime number for all the other cases
	return 1;
}
void test_if_prime(){
	int a;
	take_input_1_int(&a);
	if(is_prime(a)){
		printf("\n%d is prime.", a);
	}
	else{
		printf("\n%d is not prime", a);
	}
}





