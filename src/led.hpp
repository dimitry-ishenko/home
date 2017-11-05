////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LED_HPP
#define SRC_LED_HPP

////////////////////////////////////////////////////////////////////////////////
#include "color.hpp"
#include "firmata/call_chain.hpp"
#include "firmata/pin.hpp"
#include "temp.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
enum non_dim_t { non_dim };

constexpr int level_min = 0;
constexpr int level_max = 100;

////////////////////////////////////////////////////////////////////////////////
class led
{
public:
    ////////////////////
    explicit led(firmata::pin& pin) : led(pin, true) { }
    led(firmata::pin& pin, non_dim_t) : led(pin, false) { }

    ////////////////////
    void level(int);
    auto level() const noexcept { return level_; }

    ////////////////////
    using cid = firmata::cid;
    using int_call = firmata::call<void(int)>;

    cid on_level_changed(int_call);
    bool remove_call(cid id) { return chain_.erase(id); }

private:
    ////////////////////
    led(firmata::pin&, bool dim);

    firmata::pin& pin_;

    int level_ = 0;
    firmata::call_chain<int_call> chain_;

    void exec();
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class color_led
{
public:
    ////////////////////
    color_led(firmata::pin& red, firmata::pin& green, firmata::pin& blue) :
        color_led(red, green, blue, true) { }

    color_led(firmata::pin& red, firmata::pin& green, firmata::pin& blue, non_dim_t) :
        color_led(red, green, blue, false) { }

    ////////////////////
    void color(const rgb&);
    auto color_rgb() const noexcept { return rgb(red_, green_, blue_); }

    void color(temp);
    auto color_temp() const noexcept { return temp_; }

    void level(int);
    auto level() const noexcept { return level_; }

private:
    ////////////////////
    color_led(firmata::pin&, firmata::pin&, firmata::pin&, bool dim);

    firmata::pin &pin_red_, &pin_green_, &pin_blue_;

    int red_ = 255, green_ = 255, blue_ = 255;
    temp temp_ = from_rgb(rgb(red_, green_, blue_));
    int level_ = 0;

    void exec();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
