#ifndef MATHLINEAR_H
#define MATHLINEAR_H

#include "head/decl.h"
#include <vector>
#include "cmdioprint.h"

namespace math
{
	class Linear
	{
	public:

		static std::vector<double> gauss_elimination(tdouble_type M);
	};
}

#endif
