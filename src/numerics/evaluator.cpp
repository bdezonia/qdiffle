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
 * evaluator.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: bdezonia
 */

#include <vector>
#include <cstdlib>
#include <iostream>

#include "evaluator.hpp"

extern "C" {

#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_miser.h>

struct p {
	PointFunction* function;
	Region* region;
};

double f(double *coords, size_t dim, void *params)
{
	struct p* p = (struct p*) params;

	if (p->region->includes(dim,coords))
		return p->function->evaluate(dim,coords);
	return 0;
}

// monte carlo integration (using GSL)

double integrate(const size_t dim, const double* xl, const double* xu, PointFunction* func, Region* region) {
	double res, err;

	const gsl_rng_type *T;
	gsl_rng *r;

	struct p params;
	params.function = func;
	params.region = region;

	gsl_monte_function F = { &f, dim, &params };

	size_t calls = 10000000;

	gsl_rng_env_setup ();

	T = gsl_rng_default;
	r = gsl_rng_alloc (T);

	gsl_monte_miser_state *s = gsl_monte_miser_alloc (1);
	gsl_monte_miser_integrate (&F, xl, xu, dim, calls, r, s,
							   &res, &err);
	gsl_monte_miser_free (s);

	std::cout << "Integral error estimate is " << err << std::endl;

	return res;
}

} // extern "C"

Evaluator::Evaluator() { }

Evaluator::~Evaluator() { }

double Evaluator::integrate(
		size_t numDims, const double* xl, const double* xu, PointFunction* func, Region* region)
{
	if (!func->acceptsDimensionality(numDims))
		throw std::runtime_error("Evaluator::integrate() - function cannot handle dimensions");
	if (!region->acceptsDimensionality(numDims))
		throw std::runtime_error("Evaluator::integrate() - region cannot handle dimensions");
	return ::integrate(numDims, xl, xu, func, region);
}

double Evaluator::derivative(PointFunction*, const size_t dim, double* point) {
	// TODO - using GSL??
	return 0.0;
}

std::vector<std::vector<double>> Evaluator::roots(PointFunction* func, Region* r) {
	// TODO - using GSL??
	return std::vector<std::vector<double>>();
}

double Evaluator::minimum(PointFunction* func, Region* r) {
	return -3;
}

double Evaluator::maximum(PointFunction* func, Region* r) {
	return 99;
}
