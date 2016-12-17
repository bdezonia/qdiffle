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
 * atanh_function.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: bdezonia
 */

#include <cmath>

#include "atanh_function.hpp"


AtanhFunction::AtanhFunction(const std::shared_ptr<PointFunction>& other) : f(other) {
	if (!f->acceptsDimensionality(1))
		throw std::runtime_error("AtanhFunction needs one dimensional function as input.");
}

AtanhFunction::~AtanhFunction() {}

double AtanhFunction::evaluate(const size_t dim, const double* point) const {
	return atanh(f->evaluate(dim,point));
}

bool AtanhFunction::acceptsDimensionality(const size_t d) const {
	return d == 1;
}
