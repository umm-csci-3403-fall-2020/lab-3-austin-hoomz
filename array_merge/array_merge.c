#include <stdlib.h>
#include <stdbool.h>
#include "array_merge.h"

bool needsSorting(int rangeSize) {
	        return rangeSize >= 2;
		                }

void mergeRanges(int *values, int startIndex, int midPoint, int endIndex) {
	    /*
	     ** Assume that the two ranges are sorted:
	     **   (forall i | startIndex <= i <= j < midPoint : values[i] <= values[j])
	     **   (forall i | midPoint <= i <= j < endIndex : values[i] <= values[j])
	     ** then merge them into a single sorted array, copy that back, and return.
	     */
	const int rangeSize = endIndex - startIndex;
	// int[] destination = new int[rangeSize];
	int *destination = (int*)calloc(rangeSize, sizeof(int));
	int firstIndex = startIndex;
	int secondIndex = midPoint;
	int copyIndex = 0;
	while (firstIndex < midPoint && secondIndex < endIndex) {
		if (values[firstIndex] < values[secondIndex]){				
			destination[copyIndex] = values[firstIndex];
			++firstIndex;
		} else {
			destination[copyIndex] = values[secondIndex];
			++secondIndex;
		}
		++copyIndex;
	}
	while (firstIndex < midPoint) {
		destination[copyIndex] = values[firstIndex];
		++copyIndex;
		++firstIndex;
	}
	while (secondIndex < endIndex) {
		destination[copyIndex] = values[secondIndex];
		++copyIndex;
		++secondIndex;
		}
	int i;
	for (i = 0; i < rangeSize; ++i) {						         
		values[i + startIndex] = destination[i];					      
	}
	free(destination);
}

void mergesortRange(int *values, int startIndex, int endIndex) {
	int rangeSize = endIndex - startIndex;
	if (needsSorting(rangeSize)) {
	int midPoint = (startIndex + endIndex) / 2;
	mergesortRange(values, startIndex, midPoint);
	mergesortRange(values, midPoint, endIndex);
	mergeRanges(values, startIndex, midPoint, endIndex);
	}
}

void mergesort(int length, int* values) {
	  // This obviously doesn't actually do any *sorting*, so there's
	  // certainly work still to be done.
	  // Miracle sort would be cool
	         mergesortRange(values,1,length);
	         }

void copyArray(int* toBeCopied, int* copy, int size){
	  for(int k = 0; k<size;++k){
	  toBeCopied[k] = copy[k];
  }
}

int* array_merge(int num_arrays, int* sizes, int** values) {
  int total = 0;
  int* result;
  int index = 1;
  
  for (int i=0; i<num_arrays; i++) {
          total = total + sizes[i];
  }
  total = total+1;
  int* temp = (int*)malloc(sizeof(int)*total);

  
  for(int i = 0; i<num_arrays;++i) {
	  for(int j = 0; j<sizes[i];++j) {
		  temp[index] = values[i][j];
	  	  index = index + 1;
    }
  }
  

  if (num_arrays == 0){ 
	result = (int*)malloc(sizeof(int)*0);
	free(temp);
	return result;
  } else {
  
  index = 2;

  mergesort(total, temp);
  for (int i = 2; i<total;++i){
	  if (temp[i]!=temp[i-1]){
		  temp[index]=temp[i];
		  index = index + 1;
	  }
  }

  
  temp[0]=index-1;
  result = (int*)malloc(sizeof(int)*index);

  copyArray(result, temp, index);

  free(temp);
  return result;
  }
}