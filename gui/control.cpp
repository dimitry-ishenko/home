////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "control.hpp"
#include "ui_control.h"

////////////////////////////////////////////////////////////////////////////////
#define VOID(cl, fn, ...) (void(cl::*)(__VA_ARGS__))(&cl::fn)

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
template<typename Control>
void set(Control* ctrl, int value)
{
    auto before = ctrl->blockSignals(true);
    ctrl->setValue(value);
    ctrl->blockSignals(before);
}

////////////////////////////////////////////////////////////////////////////////
control::control(src::color_led& led, QWidget* parent) :
    QWidget(parent), ui(new Ui::control)
{
    ui->setupUi(this);
    using namespace src;

    // level
    connect(ui->level_slider, &QSlider::valueChanged,
        [&](int value){ set(ui->level_spin, value); }
    );
    connect(ui->level_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ set(ui->level_slider, value); }
    );
    connect(ui->level_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.level(value); }
    );

    // temp
    connect(ui->temp_slider, &QSlider::valueChanged,
        [&](int value){ set(ui->temp_spin, value); }
    );
    connect(ui->temp_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ set(ui->temp_slider, value); }
    );
    connect(ui->temp_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(static_cast<temp>(value)); }
    );

    // red
    connect(ui->red_slider, &QSlider::valueChanged,
        [&](int value){ set(ui->red_spin, value); }
    );
    connect(ui->red_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ set(ui->red_slider, value); }
    );
    connect(ui->red_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(value, ui->green_spin->value(), ui->blue_spin->value())); }
    );

    // green
    connect(ui->green_slider, &QSlider::valueChanged,
        [&](int value){ set(ui->green_spin, value); }
    );
    connect(ui->green_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ set(ui->green_slider, value); }
    );
    connect(ui->green_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(ui->red_spin->value(), value, ui->blue_spin->value())); }
    );

    // blue
    connect(ui->blue_slider, &QSlider::valueChanged,
        [&](int value){ set(ui->blue_spin, value); }
    );
    connect(ui->blue_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ set(ui->blue_slider, value); }
    );
    connect(ui->blue_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(ui->red_spin->value(), ui->green_spin->value(), value)); }
    );

    ////////////////////
    led.on_level_changed([&](int value)
    {
        set(ui->level_spin, value);
        set(ui->level_slider, value);
    });
    led.on_color_changed((color_led::rgb_call)[&](const rgb& value)
    {
        set(ui->red_spin, get<red>(value));
        set(ui->red_slider, get<red>(value));

        set(ui->green_spin, get<green>(value));
        set(ui->green_slider, get<green>(value));

        set(ui->blue_spin, get<blue>(value));
        set(ui->blue_slider, get<blue>(value));
    });
    led.on_color_changed([&](temp value)
    {
        set(ui->temp_spin, value);
        set(ui->temp_slider, value);
    });
}

////////////////////////////////////////////////////////////////////////////////
control::~control()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////
}
