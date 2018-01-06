#include "math/functions/vertical-lines-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::vertical_lines(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto x = abs(p.x());

		// return std::abs(x - round(x)) < thickness / 2;
		auto val = fmod(x, thickness) < thickness / 2.0;
		return p.x() < 0 ? val : !val;
	};

	return from_lambda<bool, const Point2D&>(function);
}
