////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "clamp.hpp"
#include "temp.hpp"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
rgb to_rgb(src::temp value)
{
    src::rgb rgb;

    // algorithm based on:
    // https://github.com/neilbartlett/color-temperature
    double temp = clamp(value, temp_min, temp_max) / 100;
    if(temp < 66)
    {
        get<red>(rgb) = color_max;

        double gr = temp - 2;
        gr = -155.25485562709179 - 0.44596950469579133 * gr + 104.49216199393888 * std::log(gr);
        get<green>(rgb) = clamp<color>(std::round(gr), color_min, color_max);

        if(temp > 20)
        {
            double bl = temp - 10;
            bl = -254.76935184120902 + 0.8274096064007395 * bl + 115.67994401066147 * std::log(bl);
            get<blue>(rgb) = clamp<color>(std::round(bl), color_min, color_max);
        }
        else get<blue>(rgb) = color_min;
    }
    else
    {
        double re = temp - 55;
        re = 351.97690566805693 + 0.114206453784165 * re - 40.25366309332127 * std::log(re);
        get<red>(rgb) = clamp<color>(std::round(re), color_min, color_max);

        double gr = temp - 50;
        gr = 325.4494125711974 + 0.07943456536662342 * gr - 28.0852963507957 * std::log(gr);
        get<green>(rgb) = clamp<color>(std::round(gr), color_min, color_max);

        get<blue>(rgb) = color_max;
    }

    return rgb;
}

////////////////////////////////////////////////////////////////////////////////
temp from_rgb(const src::rgb& val)
{
    for(double from = temp_min, to = temp_max, next;;)
    {
        next = (from + to) / 2;
        auto rgb = to_rgb(static_cast<temp>(std::round(next)));

        if(double(get<blue>(rgb)) / double(get<red>(rgb))
        >= double(get<blue>(val)) / double(get<red>(val)))
            to = next;
        else from = next;

        if(to - from <= 0.4) return static_cast<temp>(std::round(next));
    }
}

////////////////////////////////////////////////////////////////////////////////
}
