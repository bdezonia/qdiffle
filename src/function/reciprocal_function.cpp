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
 * reciprocal_function.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: bdezonia
 */

#include "reciprocal_function.hpp"

ReciprocalFunction::ReciprocalFunction(const std::shared_ptr<PointFunction>& a) : f1(a) {
}

ReciprocalFunction::~ReciprocalFunction() {
}

double ReciprocalFunction::evaluate(const size_t dim, const double* point) const {
	return 1.0 / f1->evaluate(dim,point);
}

bool ReciprocalFunction::acceptsDimensionality(const size_t d) const {
	return f1->acceptsDimensionality(d);
}
