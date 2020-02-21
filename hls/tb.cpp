#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>


using namespace std;

void top_function(int *Input, int data_num,int burst_length);

#define TESTDATASIZE 16777216
//#define TESTDATASIZE 1024
#define TESTDATANUM 512
#define TESTBURST 256

int main(){
	cout<<"The TB is start!"<<endl;

	// Initialize the Input Array
	int Input[TESTDATASIZE];

	for(int i=0;i<TESTDATASIZE;i++){
		Input[i]=i;
	}

	int data_num=TESTDATANUM;
	int burst_length=TESTBURST;

	top_function(Input, data_num, burst_length);


	return 0;
}
