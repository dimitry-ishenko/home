////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "encoder.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
encoder::encoder(firmata::pin& pin1, firmata::pin& pin2, firmata::pin& button) :
    button_(button)
{
    using namespace firmata::literals;
    pin1.mode(digital_in);
    pin2.mode(digital_in);
    encoder_ = firmata::encoder(pin1, pin2);

    button_.mode(pullup_in); // no pull-up resistor
}

////////////////////////////////////////////////////////////////////////////////
}
