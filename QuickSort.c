// taken from https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_program_in_c.htm
#include <stdlib.h>
#include "Sphere.h"
#include <stdlib.h>

void swap(int num1, int num2, Sphere *_particlesList) {
	Sphere temp = _particlesList[num1];
	_particlesList[num1] = _particlesList[num2];
	_particlesList[num2] = temp;
}

int partition(int left, int right, double pivot, Sphere *_particlesList) {
	int leftPointer = left - 1;
	int rightPointer = right;

	while (1) {
		while (getMinX(&_particlesList[++leftPointer]) < pivot) {
			//do nothing
		}

		while (rightPointer > 0 && getMinX(&_particlesList[--rightPointer]) > pivot) {
			//do nothing
		}

		if (leftPointer >= rightPointer) {
			break;
		}
		else {
			//printf(" item swapped :%d,%d\n", _particlesList[leftPointer], _particlesList[rightPointer]);
			swap(leftPointer, rightPointer, _particlesList);
		}
	}

	//printf(" pivot swapped :%d,%d\n", _particlesList[leftPointer], _particlesList[right]);
	swap(leftPointer, right, _particlesList);
	//printf("Updated Array: ");
	//display();
	return leftPointer;
}

void quickSort(int left, int right, Sphere *_particlesList) {
	if (right - left <= 0) {
		return;
	}
	else {
		double pivot = getMinX(&_particlesList[right]);
		int partitionPoint = partition(left, right, pivot, _particlesList);
		quickSort(left, partitionPoint - 1, _particlesList);
		quickSort(partitionPoint + 1, right, _particlesList);
	}
}