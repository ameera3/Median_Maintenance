# Median_Maintenance

## Usage
To compile, type "g++ -o Median Median.cpp". To run the program, type "./Median Median.txt"

## Introduction
The command line program Median.cpp first reads the text file 
Median.txt, which contains a list of the integers from 1 to 
10000 in unsorted order; this is treated as a stream of 
numbers, arriving one by one. Letting x_i denote the ith number 
of the file, the kth median m_k is defined as the median of the 
numbers x_1,...,x_k. (So, if k is odd, then m_k is the 
((k+1)/2)th smallest number among x_1,...,x_k; if k is even, 
then m_k is the (k/2)th smallest number among x_1,...,x_k
The program outputs the the sum of these 10000 medians, 
modulo 10000 (i.e., only the last 4 digits). 

We solve this problem efficiently, using only log(k)
operations to find the median, where k is the number of integers
in the stream we have seen so far. To accomplish this, we use
two heaps, that will store the highest and lowest half of the 
integers that we have seen from the stream so far. We input an 
integer from the stream into the low heap if it is less than minHigh, 
the minimum element of the high heap, and otherwise into the low heap. 
We rebalance the heaps. By our choice of rebalancing, the median is 
always the maximum element of the low heap. 

