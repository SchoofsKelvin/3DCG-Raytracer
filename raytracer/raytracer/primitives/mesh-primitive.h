#pragma once

#include "primitives/primitive.h"
#include "primitives/union-primitive.h"
#include "primitives/triangle-primitive.h"
#include <vector>
#include <memory>

#include "gg.h"

namespace raytracer
{
    namespace primitives
    {
        Primitive make_mesh(std::vector<gg::triangle>&);
    }
}
