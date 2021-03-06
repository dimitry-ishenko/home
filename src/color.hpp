////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_COLOR_HPP
#define SRC_COLOR_HPP

////////////////////////////////////////////////////////////////////////////////
#include <tuple>

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
using color = int;
using rgb = std::tuple<color, color, color>;

constexpr auto color_min = 0;
constexpr auto color_max = 255;

using std::get;
enum { red, green, blue };

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
