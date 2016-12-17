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
 * not_region.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: bdezonia
 */

#include <cmath>

#include "not_region.hpp"

NotRegion::NotRegion(Region* a) : r1(a) {}

bool NotRegion::acceptsDimensionality(const size_t d) const {
	return r1->acceptsDimensionality(d);
}

bool NotRegion::includes(const size_t dim, const double* point) const {
	return !r1->includes(dim, point);
}

// This is problematic. Let's say we have a hypervol. A not will make bounds universal. Now if we
// not again we would like to recover the hypervolume. But algorithm below cannot.

void NotRegion::bounds(const size_t dim, double* min, double* max) const {
	double* r1_min = new double[dim];
	double* r1_max = new double[dim];
	r1->bounds(dim, r1_min, r1_max);
	for (size_t i = 0; i < dim; i++) {
		if (r1_min[i] == -1.0/0.0)
			min[i] = nan("");
		else
			min[1] = -1.0/0.0;
	}
	for (size_t i = 0; i < dim; i++) {
		if (r1_max[i] == 1.0/0.0)
			max[i] = nan("");
		else
			max[1] = 1.0/0.0;
	}
	delete r1_max;
	delete r1_min;
}
