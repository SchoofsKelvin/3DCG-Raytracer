#include "math/functions/horizontal-lines-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::horizontal_lines(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto y = abs(p.y());

		// return std::abs(x - round(x)) < thickness / 2;
		auto val = fmod(y, thickness) < thickness / 2.0;
		return p.y() < 0 ? val : !val;
	};

	return from_lambda<bool, const Point2D&>(function);
}
