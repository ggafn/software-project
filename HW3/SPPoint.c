#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SPPoint.h"

struct sp_point_t {
    double *data;
    int dim;
    int index;
};

SPPoint spPointCreate(double* data, int dim, int index) {
	int i;
	struct sp_point_t *this = malloc(sizeof(struct sp_point_t));
	double *dataCopy = (double*) malloc(sizeof(double) * dim);
	if (!this || !dataCopy) {
		return NULL;
	}

	for (i=0; i<dim; i++) {
		dataCopy[i] = data[i];
	}

	this->dim = dim;
	this->index = index;
	this->data = dataCopy;

	return this;
}

SPPoint spPointCopy(SPPoint source) {
	assert(source != NULL);
	int i;
	int n = spPointGetDimension(source);

	// Create copy of data array
	double dataCopy[n];
	/*if (!dataCopy) {
		return NULL;
	}*/

	for(i=0; i<n; i++) {
		dataCopy[i] = spPointGetAxisCoor(source, i);
	}

	return spPointCreate(dataCopy, n, spPointGetIndex(source));
}

void spPointDestroy(SPPoint point) {
	assert(point != NULL);
	free(point->data);
	free(point);
}

int spPointGetDimension(SPPoint point) {
	assert(point != NULL);
	return point->dim;
}

int spPointGetIndex(SPPoint point) {
	assert(point != NULL);
	return point->index;
}

double spPointGetAxisCoor(SPPoint point, int axis) {
	assert(point!=NULL && axis < point->dim);
	return point->data[axis];
}

double spPointL2SquaredDistance(SPPoint p, SPPoint q) {
	assert(p != NULL && q!= NULL && p->dim == q->dim);
	int i;
	double res = 0;

	for(i=0; i<spPointGetDimension(p) ; i++) {
		double p_i = spPointGetAxisCoor(p, i);
		double q_i = spPointGetAxisCoor(q, i);
		res += (p_i-q_i)*(p_i-q_i);
	}
	return res;
}
