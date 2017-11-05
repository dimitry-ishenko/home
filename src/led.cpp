////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "clamp.hpp"
#include "led.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
led::led(firmata::pin& pin, bool dim) :
    pin_(pin)
{
    using namespace firmata::literals;
    pin_.mode(dim ? pwm : digital_out);
    exec();
}

////////////////////////////////////////////////////////////////////////////////
void led::level(int level)
{
    level_ = clamp(level, level_min, level_max);
    exec();
}

////////////////////////////////////////////////////////////////////////////////
void led::exec() { pin_.value(level_); }

////////////////////////////////////////////////////////////////////////////////
color_led::color_led(firmata::pin& red, firmata::pin& green, firmata::pin& blue, bool dim) :
    pin_red_(red), pin_green_(green), pin_blue_(blue)
{
    using namespace firmata::literals;

    auto mode = dim ? pwm : digital_out;
    pin_red_.mode(mode); pin_green_.mode(mode); pin_blue_.mode(mode);

    exec();
}

////////////////////////////////////////////////////////////////////////////////
void color_led::color(const rgb& value)
{
      red_ = clamp(get<red  >(value), color_min, color_max);
    green_ = clamp(get<green>(value), color_min, color_max);
     blue_ = clamp(get<blue >(value), color_min, color_max);
     temp_ = from_rgb(rgb(red_, green_, blue_));
    exec();
}

////////////////////////////////////////////////////////////////////////////////
void color_led::color(temp value)
{
    temp_ = clamp(value, temp_min, temp_max);
    std::tie(red_, green_, blue_) = to_rgb(temp_);
    exec();
}

////////////////////////////////////////////////////////////////////////////////
void color_led::level(int level)
{
    level_ = clamp(level, level_min, level_max);
    exec();
}

////////////////////////////////////////////////////////////////////////////////
void color_led::exec()
{
    pin_red_  .value(  red_ * level_ / (level_max - level_min));
    pin_green_.value(green_ * level_ / (level_max - level_min));
    pin_blue_ .value( blue_ * level_ / (level_max - level_min));
}

////////////////////////////////////////////////////////////////////////////////
}
