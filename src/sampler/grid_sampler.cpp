/*

Qdiffle

MIT License

Copyright (c) 2016 Barry DeZonia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 * Author: bdezonia
 */

#include "grid_sampler.hpp"

#include <iostream>

using std::cout;
using std::endl;

GridSampler::GridSampler(
		const size_t dim,
		const double* origin,
		const double* deltas,
		const int* counts)
  : dim(dim)
{
	this->origin = new double[dim];
	this->deltas = new double[dim];
	this->counts = new int[dim];
	for (size_t i = 0; i < dim; i++) {
		this->origin[i] = origin[i];
		this->deltas[i] = deltas[i];
		this->counts[i] = counts[i];
	}
}

GridSampler::~GridSampler() {
	delete [] this->origin;
	delete [] this->deltas;
	delete [] this->counts;
}

double GridSampler::sample(Region* r, PointFunction* pf, RegionFunction* rf) {
	double* pt = new double[dim];
	for (size_t i = 0; i < dim; i++) {
		pt[i] = origin[i];
	}
	int* indices = new int[dim];
	for (size_t i = 0; i < dim; i++) {
		indices[i] = 0;
	}
	rf->init(nullptr);
	while (!last(dim,indices,counts)) {
		point(dim,indices,pt);
		double value = pf->evaluate(dim,pt);
		rf->record(dim,pt,value);
		increment(dim,indices);
	}
	delete [] indices;
	delete [] pt;
	return rf->evaluate();
}

// private

bool GridSampler::last(const size_t dim, const int* indices, const int* counts) {
	for (size_t i = 0; i < dim; i++) {
		if (indices[i] != (counts[i]-1)) return false;
	}
	return true;
}

void GridSampler::increment(const size_t dim, int* indices) {
	size_t k = dim-1;
	while (true) {
		indices[k]++;
		if (indices[k] == counts[k]) {
			for (size_t p = k; p < dim; p++) {
				indices[p] = 0;
			}
			k--;
			if (k < 0) return;
		}
		else return;
	}
}

void GridSampler::point(const size_t dim, const int* indices, double* pt) {
	for (size_t i = 0; i < dim; i++) {
		pt[i] = origin[i] + (indices[i]) * deltas[i];
	}
}
