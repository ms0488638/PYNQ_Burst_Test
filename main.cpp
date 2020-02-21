#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ap_int.h>

//#define DEBUG


#ifdef DEBUG
	#include<iostream>
	#include<stdlib.h>
	using namespace std;
#endif


#define BufferSize 256

typedef ap_uint<10> UCHAR;

void mmcpy_inputport(int *input,int input_memcpy_buffer[BufferSize],int Offset,UCHAR RowIntNum)
{
	memcpy(input_memcpy_buffer,(int *)(input + Offset),RowIntNum*sizeof(int));
	#ifdef DEBUG
		cout<<"Show the first data: "<<input_memcpy_buffer[0]<<" @ "<<Offset<<endl;
	#endif
}




void top_function(int *Input, int data_num,int burst_length){

// Maximum Length: 64MB=16*1024*1024 (4byte) 16777216
//#pragma HLS INTERFACE m_axi depth=16777216 port=Input offset=slave num_read_outstanding=1 num_write_outstanding=1
#pragma HLS INTERFACE m_axi depth=16777216 port=Input offset=slave num_read_outstanding=128 num_write_outstanding=128 max_read_burst_length=256 max_write_burst_length=256
#pragma HLS INTERFACE s_axilite register port=return bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=burst_length bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=data_num bundle=CTRL_BUS


	int input_memcpy_buffer[BufferSize];



	const ap_uint<32> data_num_temp=data_num;
	const UCHAR burst_length_temp=burst_length;


	int remainder=data_num_temp%burst_length_temp;
	int divider  =data_num_temp/burst_length_temp;
	int max_round;
	int round, counter;

	if(remainder!=0)
		max_round=divider+1;
	else
		max_round=divider;


	Loading_Loop:for(round=0, counter=0; round< max_round ;counter+burst_length_temp, round++){
//#pragma HLS PIPELINE
//#pragma HLS DATAFLOW
		UCHAR ReadLength;
		int Offset=round*burst_length_temp;

		if(round==divider)
			// If round==divider, it means the remain data less than a burst.
			ReadLength=remainder+1;
		else
			ReadLength=burst_length_temp;

		mmcpy_inputport(Input, input_memcpy_buffer, Offset, ReadLength);

		#ifdef DEBUG
			cout<<round<<" round, current location: "<<Offset<<" to "<<Offset+ReadLength-1<<", ReadLength: "<<ReadLength<<endl;
		#endif
	}
	#ifdef DEBUG
		cout<<"Done!!"<<endl;
	#endif

}
