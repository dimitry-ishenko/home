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
control::control(src::color_led& led, QWidget* parent) :
    QWidget(parent), ui(new Ui::control)
{
    ui->setupUi(this);
    using namespace src;

    // level
    connect(ui->level_slider, &QSlider::valueChanged, ui->level_spin, &QSpinBox::setValue);
    connect(ui->level_spin, VOID(QSpinBox, valueChanged, int), ui->level_slider, &QSlider::setValue);
    connect(ui->level_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.level(value); }
    );

    // temp
    connect(ui->temp_slider, &QSlider::valueChanged, ui->temp_spin, &QSpinBox::setValue);
    connect(ui->temp_spin, VOID(QSpinBox, valueChanged, int), ui->temp_slider, &QSlider::setValue);
    connect(ui->temp_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(static_cast<temp>(value)); }
    );

    // red
    connect(ui->red_slider, &QSlider::valueChanged, ui->red_spin, &QSpinBox::setValue);
    connect(ui->red_spin, VOID(QSpinBox, valueChanged, int), ui->red_slider, &QSlider::setValue);
    connect(ui->red_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(value, ui->green_spin->value(), ui->blue_spin->value())); }
    );

    // green
    connect(ui->green_slider, &QSlider::valueChanged, ui->green_spin, &QSpinBox::setValue);
    connect(ui->green_spin, VOID(QSpinBox, valueChanged, int), ui->green_slider, &QSlider::setValue);
    connect(ui->green_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(ui->red_spin->value(), value, ui->blue_spin->value())); }
    );

    // blue
    connect(ui->blue_slider, &QSlider::valueChanged, ui->blue_spin, &QSpinBox::setValue);
    connect(ui->blue_spin, VOID(QSpinBox, valueChanged, int), ui->blue_slider, &QSlider::setValue);
    connect(ui->blue_spin, VOID(QSpinBox, valueChanged, int),
        [&](int value){ led.color(rgb(ui->red_spin->value(), ui->green_spin->value(), value)); }
    );

    ////////////////////
    led.on_level_changed([&](int value){ ui->level_spin->setValue(value); });
    led.on_color_changed((color_led::rgb_call)[&](const rgb& value)
    {
        ui->  red_spin->setValue(get<red  >(value));
        ui->green_spin->setValue(get<green>(value));
        ui-> blue_spin->setValue(get<blue >(value));
    });
    led.on_color_changed([&](temp value){ ui->temp_spin->setValue(value); });
}

////////////////////////////////////////////////////////////////////////////////
control::~control()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////
}
