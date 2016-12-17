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
 * grid_sampler.hpp
 *
 *  Created on: Nov 26, 2015
 *      Author: bdezonia
 */

#ifndef SRC_GRID_SAMPLER_HPP_
#define SRC_GRID_SAMPLER_HPP_

#include "sampler.hpp"

class GridSampler : public Sampler {

public:

	GridSampler(const size_t dim, const double* origin,
			    const double* deltas,
				const int* counts);

    double sample(Region* r, PointFunction* pf, RegionFunction* rf);

    ~GridSampler();

private:

    size_t dim;
    double* origin;
    double* deltas;
    int* counts;

    bool last(const size_t dim, const int* indices, const int* counts);
    void increment(const size_t dim, int* indices);
    void point(const size_t dim, const int* indices, double* pt);
};

#endif /* SRC_GRID_SAMPLER_HPP_ */
