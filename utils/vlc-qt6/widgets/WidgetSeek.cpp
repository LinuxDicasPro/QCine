/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QProgressBar>

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "widgets/WidgetSeek.h"

VlcWidgetSeek::VlcWidgetSeek(VlcMediaPlayer *player, QWidget *slider, bool connectSlider, QWidget *parent)
    : QWidget(parent), _vlcMediaPlayer(player), _connectSlider(connectSlider) {
    initWidgetSeek(slider);
}

VlcWidgetSeek::VlcWidgetSeek(QWidget *slider, bool connectSlider, QWidget *parent)
    : QWidget(parent), _connectSlider(connectSlider) {
    initWidgetSeek(slider);
}

VlcWidgetSeek::VlcWidgetSeek(QWidget *parent) : QWidget(parent), _connectSlider(true) {
    initWidgetSeek(nullptr);
}

VlcWidgetSeek::~VlcWidgetSeek() = default;

void VlcWidgetSeek::initWidgetSeek(QWidget *slider) {
    _autoHide = false;

    if (slider == nullptr)
        slider = new QSlider();

    auto *sl = qobject_cast<QAbstractSlider *>(slider);
    _slider = sl;
    if (sl != nullptr && _connectSlider) {
        sl->setOrientation(Qt::Horizontal);
        sl->setMaximum(1);
        if (_vlcMediaPlayer != nullptr) {
            connect(sl, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
            connect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), sl, SLOT(setEnabled(bool)));
        }
    }
    auto *bar = qobject_cast<QProgressBar *>(slider);
    _progress = bar;
    if (bar != nullptr && _connectSlider) {
        bar->setOrientation(Qt::Horizontal);
        bar->setMaximum(1);
        bar->setTextVisible(false);
    }

    if (_labelElapsed == nullptr)
        _labelElapsed = new QLabel(this);
    _labelElapsed->setText("--:--");

    if (_labelTotal == nullptr)
        _labelTotal = new QLabel(this);
    _labelTotal->setText("--:--");

    delete layout();
    auto *layout = new QHBoxLayout;
    layout->addWidget(_labelElapsed);
    layout->addWidget(slider);
    layout->addWidget(_labelTotal);
    setLayout(layout);
}

void VlcWidgetSeek::setAutoHide(bool autoHide) {
    _autoHide = autoHide;
    setVisible(!_autoHide);
}

void VlcWidgetSeek::setMediaPlayer(VlcMediaPlayer *player) {
    if (_vlcMediaPlayer) {
        disconnect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
        disconnect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
        if (_slider != nullptr) {
            disconnect(_slider, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
            disconnect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), _slider, SLOT(setEnabled(bool)));
        }
    }

    _vlcMediaPlayer = player;
    if (player == nullptr)
        return;

    connect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
    connect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
    if (_slider != nullptr && _connectSlider) {
        _slider->setOrientation(Qt::Horizontal);
        _slider->setMaximum(1);
        connect(_slider, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
        connect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), _slider, SLOT(setEnabled(bool)));
    } else if (_progress != nullptr && _connectSlider) {
        _progress->setOrientation(Qt::Horizontal);
        _progress->setMaximum(1);
        _progress->setTextVisible(false);
    }
}

void VlcWidgetSeek::setSliderWidget(QWidget *slider, bool updateSlider) {
    _connectSlider = updateSlider;
    if (slider == nullptr)
        return;
    if (slider == _slider || slider == _progress)
        return;
    delete _slider;
    delete _progress;
    initWidgetSeek(slider);
}

void VlcWidgetSeek::end() {
    _labelElapsed->setText("--:--");
    _labelTotal->setText("--:--");
    if (_slider != nullptr && _connectSlider) {
        _slider->setMaximum(1);
        _slider->setValue(0);
    } else if (_progress != nullptr && _connectSlider) {
        _progress->setMaximum(1);
        _progress->setValue(0);
    }
}

void VlcWidgetSeek::updateCurrentTime(int time) {
    QTime currentTime = QTime(0, 0);
    currentTime = currentTime.addMSecs(time);

    QString display = "mm:ss";
    if (currentTime.hour() > 0)
        display = "hh:mm:ss";

    _labelElapsed->setText(currentTime.toString(display));
    if (_slider && _connectSlider) {
        _slider->blockSignals(true);
        _slider->setValue(time);
        _slider->blockSignals(false);
    } else if (_progress && _connectSlider) {
        _progress->setValue(time);
    }
}

void VlcWidgetSeek::updateFullTime(int time) {
    if (time == 0) {
        _labelTotal->setText("--:--");
    } else {
        QTime fullTime = QTime(0, 0);
        fullTime = fullTime.addMSecs(time);

        QString display = "mm:ss";
        if (fullTime.hour() > 0)
            display = "hh:mm:ss";

        _labelTotal->setText(fullTime.toString(display));
    }

    if (!time) {
        if (_slider && _connectSlider)
            _slider->setMaximum(1);
        else if (_progress && _connectSlider)
            _progress->setMaximum(1);
        setVisible(!_autoHide);
    } else {
        if (_slider && _connectSlider) {
            _slider->setMaximum(time);
            _slider->setSingleStep(1000);
            _slider->setPageStep(time / 100);
        }
        if (_progress && _connectSlider)
            _progress->setMaximum(time);
        setVisible(true);
    }
}
