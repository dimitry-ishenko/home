////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "firmata/asio_or_boost.hpp"
#include "firmata/client.hpp"
#include "firmata/serial_port.hpp"
#include "encoder.hpp"
#include "gui/control.hpp"
#include "led.hpp"
#include "temp.hpp"

#include <QApplication>
#include <asio/system_timer.hpp>
#include <chrono>
#include <functional>

int main(int argc, char* argv[])
{
    using namespace src;
    using namespace firmata::literals;
    using namespace std::chrono_literals;

    ////////////////////
    asio::io_service io;
    firmata::serial_port device(io, "/dev/ttyACM0");

    firmata::client arduino(device);
    arduino.info();

    for(auto& pin : arduino.pins())
        if(pin.mode() == analog_in || pin.mode() == digital_in || pin.mode() == pullup_in)
            pin.mode(digital_out);

    ////////////////////
    QApplication app(argc, argv);

    asio::system_timer timer(io);
    using handler = std::function<void(const asio::error_code&)>;
    handler update_gui;

    timer.async_wait(update_gui = [&](const asio::error_code&)
    {
        app.processEvents();

        timer.expires_at(timer.expires_at() + 10ms);
        timer.async_wait(update_gui);
    });
    timer.expires_from_now(0ms);


    ////////////////////
    src::color_led led(arduino.pin(D3), arduino.pin(D5), arduino.pin(D6));
    src::encoder enc(arduino.pin(D0), arduino.pin(D1), arduino.pin(D2));
    gui::control ctrl(led);
    ctrl.show();

    bool do_color = false;
    enc.on_state_low([&](){ do_color = !do_color; });

    enc.on_rotate([&](int step)
    {
        if(do_color)
            led.color(static_cast<temp>(led.color_temp() + step * 100_K));
        else
            led.level(led.level() + step);
    });

    ////////////////////
    src::color_led bed_led(arduino.pin(D9), arduino.pin(D10), arduino.pin(D13));
    src::encoder bed_enc(arduino.pin(D18), arduino.pin(D19), arduino.pin(D20));
    gui::control bed_ctrl(bed_led);
    bed_ctrl.show();

    bool do_bed_color = false;
    bed_enc.on_state_low([&](){ do_bed_color = !do_bed_color; });

    bed_enc.on_rotate([&](int step)
    {
        if(do_bed_color)
            bed_led.color(static_cast<temp>(bed_led.color_temp() + step * 100_K));
        else
            bed_led.level(bed_led.level() + step);
    });

    ////////////////////
    io.run();
    return 0;
}
