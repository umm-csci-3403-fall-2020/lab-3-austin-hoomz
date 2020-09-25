#include "mergesort.h"
#include <cstdlib>
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
	         mergesortRange(values,0,length);
	         }
