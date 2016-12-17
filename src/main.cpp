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
 * main.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: bdezonia
 */

// ideas
//   ConditionalRegion? might make bounds calc impossible
// todos
//   Make region bounds code work and make sense. who is responsible for dimensionality?
//   Kill universal, empty, and not regions. then regions can have a dimensionality and safe bounds
//     calcs and then integrate wouldn't need numdims parameter.
//   Add destructors to all regions and functions and parseresult
//   A lot of functions check dimensionality of inputs. But this might be able to be relaxed.
//   Pull in function parser from my old imglib-ops java code

#include <iostream>
#include <cstdlib>

#include "numerics/evaluator.hpp"
#include "parser/point_function_parser.hpp"
#include "region/region.hpp"
#include "region/hypervolume_region.hpp"
#include "region_function/region_average.hpp"
#include "sampler/grid_sampler.hpp"

#include "everything.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

extern "C" {
double integrate(
		size_t numDims, const double* xl, const double* xu, PointFunction* func, Region* region);
}

int main(int argc, char* argv[]) {
	try {
		srand(time(nullptr));
		string functionDef;
		cout << "Enter function:" << endl;
		cin >> functionDef;
		functionDef = "[x], x^2";
		// parse string into function
		PointFunctionParser parser;
		std::pair<std::shared_ptr<PointFunction>,string>* parseResult = parser.parse(functionDef);
		PointFunction* function = parseResult->first.get();
		string errMsg = parseResult->second;

		// choose a region
		double ll[] = { 3. };
		double ul[] = { 11. };
		double extents[] = { ul[0] - ll[0] };
		HyperVolumeRegion region(1, ll, extents);
		// choose a point in region
		// calculate , integral over region
		Evaluator evaluator;
		double integral_eval = evaluator.integrate(1, ll, ul, function, &region);
		cout << "My integral is " << integral_eval << endl;
		cout << "Exact integral should be " << ((11.*11*11/3) - (3.*3*3/3)) << endl;
		// calculate its derivative at the point
		double point[1] = {7.};
		double deriv_eval = evaluator.derivative(function, 1, point);
		cout << "Derivative is " << deriv_eval << endl;
		// find zeroes of function in region
		evaluator.roots(function,&region);
		cout << "Roots are undetermined" << endl;
		// calc sum of values by sampling the region on various grids
		double deltas[1] = { 0.00125 };
		int counts[1] = { 800 * 8 };
		GridSampler sampler(1, ll, deltas, counts);
		RegionAverage avg;
		double avg_eval = sampler.sample(&region, function, &avg);
		cout << "Average by sampling function across region is " << avg_eval << endl;
		cout << "Estimated integral is " << (avg_eval * extents[0]) << endl;
		double min = evaluator.minimum(function, &region);
		double max = evaluator.maximum(function, &region);
		cout << "(min,max) over region = (" << min << "," << max << ")";
		delete parseResult;
	}
	catch (std::runtime_error& e) {
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}
