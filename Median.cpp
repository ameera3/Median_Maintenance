/*
 * Filename: Median.cpp
 * Usage: ./Median Median.txt
 * Description: The command line program Median.cpp first reads the text file 
 *              Median.txt, which contains a list of the integers from 1 to 
 *		10000 in unsorted order; this is treated as a stream of 
 *		numbers, arriving one by one. Letting x_i denote the ith number 
 *		of the file, the kth median m_k is defined as the median of the 
 *		numbers x_1,...,x_k. (So, if k is odd, then m_k is the 
 *		((k+1)/2)th smallest number among x_1,...,x_k; if k is even, 
 *		then m_k is the (k/2)th smallest number among x_1,...,x_k
 *		The program outputs the the sum of these 10000 medians, 
 *		modulo 10000 (i.e., only the last 4 digits). 
 */

#include <iostream>
#include <limits>
#include <queue>

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

// size of array
#define ARRAY_SIZE 10000

// modulus
#define MODULUS 10000

using namespace std;

/* When the streamSize is even, we want both the low and high heaps to have the
 * same size. When the streamSize is odd, we want the low heap to have one more
 * element than the high heap.
 */
void rebalance( priority_queue< unsigned int,
		        vector<unsigned int>, greater<unsigned int> >& high, 
			priority_queue<unsigned int>& low, unsigned int streamSize ) {

	// When the stream size is even, we want both the low and high heaps
	// to have the same size.
	if (streamSize % 2 == 0) {
		if( low.size() > high.size() ){
			while( low.size() > high.size() ){
				unsigned int maxLow = low.top();
				low.pop();
				high.push( maxLow );
			}
		}
		else if ( high.size() > low.size() ) { 
			while( high.size() > low.size() ) {
				unsigned int minHigh = high.top();
				high.pop();
				low.push( minHigh );
			}
		}
	}

	// When the stream size is odd, we want the low heap to have one
	// more element than the high heap.
	else {
		if( low.size() > high.size() + 1 ){

			while( low.size() > high.size() + 1 ){
				unsigned int maxLow = low.top();
				low.pop();
				high.push( maxLow );
			}
		}
		else if ( high.size() > low.size() - 1 ) {

			while( high.size() > low.size() - 1 ) {
				unsigned int minHigh = high.top();
				high.pop();
				low.push( minHigh );
			}
		}
	}
}

/* The input parameter is an array of integers from 1 to ARRAY_SIZE in
 * unsorted order, which we treat as a stream of integers. We have
 * two heaps, high and low that will store the highest and lowest
 * half of the integers that we have seen from the stream so far.
 * We input an integer from the stream into the low heap if it is less 
 * than minHigh, the minimum element of the high heap, and otherwise
 * into the low heap. We rebalance the heaps. By our choice of rebalancing,
 * the median is always the maximum element of the low heap. 
 */

unsigned int medianSum(unsigned int* myArray) {

	// store the medians m_k for k = 1 to ARRAY_SIZE
	unsigned int* medArray = new unsigned int[ARRAY_SIZE];

	// Minheap that stores the highest half of the integers 
	// in the stream so far. 
	priority_queue<unsigned int, vector< unsigned int >, 
		greater< unsigned int >> high;

	// Maxheap that stores the lowest half of the integers
	// in the stream so far.
	priority_queue< unsigned int > low;

	// used for looping 
	unsigned int i;

	// current median m_k
	unsigned int median;

	// sum of the medians m_k for k = 1 to ARRAY_SIZE
	unsigned int medSum = 0;
	
	for(i = 0; i < ARRAY_SIZE; ++i) {

		// if the high heap is empty, set its minimum element
		// to be the biggest unsigned int, so that we default
		// insert into the low heap.
		unsigned int minHigh = std::numeric_limits<unsigned int>::max();

		// otherwise, find the minimum of the high heap
		if( !high.empty() ) {
			minHigh = high.top();
		}	

		// if the integer in the stream is less than the minimum
		// element in the high heap, insert it into the low heap
		if ( myArray[i] < minHigh ){
			low.push( myArray[i] );
		}

		// Otherwise, insert it into the high heap.
		else {
			high.push( myArray[i] );
		}

		// Rebalance the heaps
		rebalance(high, low, i+1);

		// By our choice of rebalancing, the median is always the 
		// maximum element of the low heap
		median = low.top();
		medArray[i] = median;
	}

	// Sum up the medians
	for(i = 0; i < ARRAY_SIZE; ++i) {
		medSum += medArray[i];
	}

	// Mod the sum by the modulus
	medSum = medSum % MODULUS;

	// no memory leaks here
	delete[] medArray;

	// return the sum of the medians modulo the modulus
	return medSum;
}

unsigned int readFile(const char* inFile) {

	unsigned int* myArray = new unsigned int[ARRAY_SIZE];

	// Used to determine if we should keep scanning
	// from the array
	bool more_input = true;

	// used for looping
	unsigned int i;

	// open input file
	FILE *in = fopen(inFile, "r");

	// read the integers in the input file into the array
	while( more_input ) {

		// write ARRAY_SIZE elements into array from input file
		for( i = 0; i < ARRAY_SIZE; ++i ) {
			if( fscanf(in, "%d\n", &myArray[i]) != 1 ){
				more_input = false;
				break;
			}
		}
	}

	// close input file
	fclose(in);

	// compute sum of medians
	unsigned int sumMod = medianSum(myArray); 

	// no memory leaks here
	delete[] myArray;

	// return sum of medians
	return sumMod;

}

int main(int argc, char ** argv) {

	// check for arguments
	if( argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	// read the input file and compute the sume of the medians
	unsigned int medSum = readFile(argv[IN_IDX]);

	// output the sum of the medians
	cout << "The sum of the medians mod " << MODULUS << " is: "
	     << medSum << endl;
}

