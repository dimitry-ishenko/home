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
control::control(QWidget* parent) :
    QWidget(parent), ui(new Ui::control)
{
    ui->setupUi(this);

    connect(ui->level_slider, &QSlider::valueChanged, ui->level_spin, &QSpinBox::setValue);
    connect(ui->level_spin, VOID(QSpinBox, valueChanged, int), ui->level_slider, &QSlider::setValue);

    connect(ui->temp_slider, &QSlider::valueChanged, ui->temp_spin, &QSpinBox::setValue);
    connect(ui->temp_spin, VOID(QSpinBox, valueChanged, int), ui->temp_slider, &QSlider::setValue);

    connect(ui->red_slider, &QSlider::valueChanged, ui->red_spin, &QSpinBox::setValue);
    connect(ui->red_spin, VOID(QSpinBox, valueChanged, int), ui->red_slider, &QSlider::setValue);

    connect(ui->green_slider, &QSlider::valueChanged, ui->green_spin, &QSpinBox::setValue);
    connect(ui->green_spin, VOID(QSpinBox, valueChanged, int), ui->green_slider, &QSlider::setValue);

    connect(ui->blue_slider, &QSlider::valueChanged, ui->blue_spin, &QSpinBox::setValue);
    connect(ui->blue_spin, VOID(QSpinBox, valueChanged, int), ui->blue_slider, &QSlider::setValue);
}

////////////////////////////////////////////////////////////////////////////////
control::~control()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////
}
