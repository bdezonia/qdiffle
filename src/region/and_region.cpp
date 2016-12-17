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
 * and_region.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: bdezonia
 */

#include "and_region.hpp"

#include <cmath>
#include <algorithm>

AndRegion::AndRegion(Region* a, Region* b) : r1(a), r2(b) {}

bool AndRegion::acceptsDimensionality(const size_t d) const {
	return r1->acceptsDimensionality(d) && r2->acceptsDimensionality(d);
}

bool AndRegion::includes(const size_t dim, const double* point) const {
	return r1->includes(dim,point) && r2->includes(dim,point);
}

void AndRegion::bounds(const size_t dim, double* min, double* max) const {
	double* b1_min = new double[dim];
	double* b2_min = new double[dim];
	double* b1_max = new double[dim];
	double* b2_max = new double[dim];
	r1->bounds(dim, b1_min, b1_max);
	r2->bounds(dim, b2_min, b2_max);
	for (size_t i = 0; i < dim; i++) {
		// intervals don't overlap
		if (b1_min[i] > b2_max[i] || b2_min[i] > b1_max[i]) {
			min[i] = nan("");
			max[i] = nan("");
		}
		else { // intervals overlap
			min[i] = std::max(b1_min[i],b2_min[i]);
			max[i] = std::min(b1_max[i],b2_max[i]);
		}
	}
	delete b2_max;
	delete b1_max;
	delete b2_min;
	delete b1_min;
}
