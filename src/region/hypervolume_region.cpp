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
 * hypervolume_region.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: bdezonia
 */

#include "hypervolume_region.hpp"

#include <algorithm>

HyperVolumeRegion::HyperVolumeRegion(const size_t dim, const double* origin, const double* extents)
  : dim(dim)
{
	mins = new double[dim];
	maxes = new double[dim];
	for (size_t i = 0; i < dim; i++) {
		double a = origin[i];
		double b = origin[i] + extents[i];
		mins[i] = std::min(a,b);
		maxes[i] = std::max(a,b);
	}
}

HyperVolumeRegion::~HyperVolumeRegion() {
	delete [] mins;
	delete [] maxes;
}

bool HyperVolumeRegion::acceptsDimensionality(const size_t d) const {
	return d == dim;
}

bool HyperVolumeRegion::includes(const size_t dim, const double* point) const {
	for (size_t i = 0; i < dim; i++) {
		double value = point[i];
		if (value < mins[i]) return false;
		if (value > maxes[i]) return false;
	}
	return true;
}

void HyperVolumeRegion::bounds(const size_t dim, double* min, double* max) const {
	for (size_t i = 0; i < dim; i++) {
		min[i] = mins[i];
		max[i] = maxes[i];
	}
}
