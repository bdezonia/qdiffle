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
 * expm1_function.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: bdezonia
 */

#include <cmath>

#include "expm1_function.hpp"


Expm1Function::Expm1Function(const std::shared_ptr<PointFunction>& other) : f(other) {
	if (!f->acceptsDimensionality(1))
		throw std::runtime_error("Expm1Function needs one dimensional function as input.");
}

Expm1Function::~Expm1Function() {}

double Expm1Function::evaluate(const size_t dim, const double* point) const {
	return expm1(f->evaluate(dim,point));
}

bool Expm1Function::acceptsDimensionality(const size_t d) const {
	return d == 1;
}
