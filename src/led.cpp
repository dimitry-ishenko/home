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
    level = clamp(level, level_min, level_max);
    if(level != level_)
    {
        exec();
        chain_(level_ = level);
    }
}

////////////////////////////////////////////////////////////////////////////////
led::cid led::on_level_changed(int_call fn) { return chain_.insert(std::move(fn)); }

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
    src::color red, green, blue;
    std::tie(red, green, blue) = value;
    red   = clamp(red  , color_min, color_max);
    green = clamp(green, color_min, color_max);
    blue  = clamp(blue , color_min, color_max);

    if(red != red_ || green != green_ || blue != blue_)
    {
        auto value = src::rgb(red_ = red, green_ = green, blue_ = blue);
        exec();

        chain_rgb_(value);
        auto temp = from_rgb(value);
        if(temp != temp_) chain_temp_(temp_ = temp);
    }
}

////////////////////////////////////////////////////////////////////////////////
void color_led::color(temp value)
{
    value = clamp(value, temp_min, temp_max);

    if(value != temp_)
    {
        src::color red, green, blue;
        std::tie(red, green, blue) = to_rgb(temp_ = value);

        if(red != red_ || green != green_ || blue != blue_)
        {
            red_ = red; green_ = green; blue_ = blue;
            exec();

            chain_rgb_(rgb(red_, green_, blue_));
        }
        chain_temp_(temp_);
    }
}

////////////////////////////////////////////////////////////////////////////////
void color_led::level(int level)
{
    level = clamp(level, level_min, level_max);
    if(level != level_)
    {
        chain_level_(level_ = level);
        exec();
    }
}

////////////////////////////////////////////////////////////////////////////////
color_led::cid color_led::on_color_changed( rgb_call fn)
{ return chain_rgb_.insert(std::move(fn)); }

color_led::cid color_led::on_color_changed(temp_call fn)
{ return chain_temp_.insert(std::move(fn)); }

color_led::cid color_led::on_level_changed( int_call fn)
{ return chain_level_.insert(std::move(fn)); }

bool color_led::remove_call(cid id)
{ return chain_rgb_.erase(id) || chain_temp_.erase(id) || chain_level_.erase(id); }

////////////////////////////////////////////////////////////////////////////////
void color_led::exec()
{
    pin_red_  .value(  red_ * level_ / (level_max - level_min));
    pin_green_.value(green_ * level_ / (level_max - level_min));
    pin_blue_ .value( blue_ * level_ / (level_max - level_min));
}

////////////////////////////////////////////////////////////////////////////////
}
