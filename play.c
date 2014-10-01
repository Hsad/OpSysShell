#include <stdio.h>

int main(){
	double length = 100;
	double lastLen = 100;
	int x;
	int flop = 0;
	for (x =0; x < 100; x++){
		if (flop){
			printf("ADD>>length: %f,\t half of lastLen is %f\n", (double)length, (double)(lastLen/2));
			length += lastLen / 2;
			lastLen = lastLen / 2;
			printf("After %i flips and flops, the value is : %f\n", 1000-x, (double)length );
			flop = 0;
		}
		else if (!flop){
			printf("SUB>>length: %f,\t half of lastLen is %f\n", (double)length, (double)(lastLen/2));
			length -= lastLen / 2;
			lastLen = lastLen / 2;
			printf("After %i flips and flops, the value is : %f\n", 1000-x, (double)length );
			flop = 1;
		}
	}
	printf("After 1000 flips and flops, the value is : %f\n", (double)length );
	return 1;
} //diouxXfeEgGcs
