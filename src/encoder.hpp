////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_ENCODER_HPP
#define SRC_ENCODER_HPP

////////////////////////////////////////////////////////////////////////////////
#include "firmata/encoder.hpp"
#include "firmata/pin.hpp"

#include <utility>

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
class encoder
{
    using cid = firmata::cid;
    using int_call = firmata::encoder::int_call;
    using void_call = firmata::encoder::void_call;

public:
    ////////////////////
    encoder(firmata::pin& pin1, firmata::pin& pin2, firmata::pin& button);

    // install rotate callback
    auto on_rotate(int_call fn) { return encoder_.on_rotate(std::move(fn)); }
    auto on_rotate_cw(void_call fn) { return encoder_.on_rotate_cw(std::move(fn)); }
    auto on_rotate_ccw(void_call fn) { return encoder_.on_rotate_ccw(std::move(fn)); }

    // install state changed/low/high callback
    auto on_state_changed(int_call fn) { return button_.on_state_changed(std::move(fn)); }
    auto on_state_low(void_call fn) { return button_.on_state_low(std::move(fn)); }
    auto on_state_high(void_call fn) { return button_.on_state_high(std::move(fn)); }

    // remove callback
    bool remove_call(cid id) { return encoder_.remove_call(id) || button_.remove_call(id); }

private:
    ////////////////////
    firmata::encoder encoder_;
    firmata::pin& button_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
