
#include "Mat2.h"
#include <cmath>

namespace math {

Mat2 Mat2::rotate(float radians)
{
	auto cosine = cos(radians);
	auto sine = sin(radians);
	return Mat2(cosine, -sine, sine, cosine);
}

}