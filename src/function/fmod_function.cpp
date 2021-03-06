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
 * fmod_function.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: bdezonia
 */

#include <cmath>

#include "fmod_function.hpp"


FmodFunction::FmodFunction(const std::shared_ptr<PointFunction>& f1, const std::shared_ptr<PointFunction>& f2) : f1(f1), f2(f2) {
	if (!f1->acceptsDimensionality(1) || !f2->acceptsDimensionality(1))
		throw std::runtime_error("FmodFunction needs one dimensional functions as input.");
}

FmodFunction::~FmodFunction() {}

double FmodFunction::evaluate(const size_t dim, const double* point) const {
	return fmod(f1->evaluate(dim,point),f2->evaluate(dim,point));
}

bool FmodFunction::acceptsDimensionality(const size_t d) const {
	return d == 2;
}
