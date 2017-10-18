#include "math/functions/horizontal-lines-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::horizontal_lines(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto y = std::abs(p.y()) + thickness/4;

		// return std::abs(y - round(y)) < thickness / 2;
		return fmod(y, thickness) < thickness / 2.0;
	};

	return from_lambda<bool, const Point2D&>(function);
}
