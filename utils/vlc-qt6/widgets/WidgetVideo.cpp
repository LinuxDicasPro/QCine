/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
* 2021 Andry <i@andry.io>
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

#include <QtGlobal>

#if QT_VERSION >= 0x060000
#include <QApplication>
#include <QHBoxLayout>
#include <QToolBar>
#else
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolBar>
#endif

#if defined(Q_WS_X11)
#include <X11/Xlib.h>
#include <qx11info_x11.h>
#endif

#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "widgets/WidgetVideo.h"

VlcWidgetVideo::VlcWidgetVideo(VlcMediaPlayer *player, QWidget *parent) : QFrame(parent), _vlcMediaPlayer(player) {
    if (_vlcMediaPlayer)
        connect(_vlcMediaPlayer, &VlcMediaPlayer::vout, this, &VlcWidgetVideo::applyPreviousSettings);

    initWidgetVideo();
}

VlcWidgetVideo::VlcWidgetVideo(QWidget *parent) : QFrame(parent), _vlcMediaPlayer(nullptr) {
    initWidgetVideo();
}

VlcWidgetVideo::~VlcWidgetVideo() = default;

void VlcWidgetVideo::initWidgetVideo() {
    _enableSettings = false;
    _defaultAspectRatio = Vlc::Original;
    _defaultCropRatio = Vlc::Original;
    _defaultDeinterlacing = Vlc::Disabled;
    _defaultScale = Vlc::NoScale;
    _currentAspectRatio = Vlc::Original;
    _currentCropRatio = Vlc::Original;
    _currentDeinterlacing = Vlc::Disabled;
    _currentScale = Vlc::NoScale;

    _layout = new QHBoxLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);

    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    this->setPalette(plt);
}

void VlcWidgetVideo::setMediaPlayer(VlcMediaPlayer *player) {
    if (_vlcMediaPlayer)
        disconnect(_vlcMediaPlayer, &VlcMediaPlayer::vout, this, &VlcWidgetVideo::applyPreviousSettings);

    _vlcMediaPlayer = player;
    connect(_vlcMediaPlayer, &VlcMediaPlayer::vout, this, &VlcWidgetVideo::applyPreviousSettings);
}

void VlcWidgetVideo::enableDefaultSettings() {
    initDefaultSettings();
    enablePreviousSettings();
}

void VlcWidgetVideo::initDefaultSettings() {
    _currentAspectRatio = defaultAspectRatio();
    _currentCropRatio = defaultCropRatio();
    _currentDeinterlacing = defaultDeinterlacing();
    _currentScale = defaultScale();
}

void VlcWidgetVideo::applyPreviousSettings() {
    if (!_enableSettings || !_vlcMediaPlayer) return;

    _vlcMediaPlayer->video()->setAspectRatio(_currentAspectRatio);
    _vlcMediaPlayer->video()->setCropGeometry(_currentCropRatio);
    _vlcMediaPlayer->video()->setScale(_currentScale);
    _vlcMediaPlayer->video()->setDeinterlace(_currentDeinterlacing);
    _enableSettings = false;
}

void VlcWidgetVideo::setAspectRatio(const Vlc::Ratio &ratio) {
    if (_vlcMediaPlayer) {
        _currentAspectRatio = ratio;
        _vlcMediaPlayer->video()->setAspectRatio(ratio);
    }
}

void VlcWidgetVideo::setCropRatio(const Vlc::Ratio &ratio) {
    if (_vlcMediaPlayer) {
        _currentCropRatio = ratio;
        _vlcMediaPlayer->video()->setCropGeometry(ratio);
    }
}

void VlcWidgetVideo::setDeinterlacing(const Vlc::Deinterlacing &deinterlacing) {
    if (_vlcMediaPlayer) {
        _currentDeinterlacing = deinterlacing;
        _vlcMediaPlayer->video()->setDeinterlace(deinterlacing);
    }
}

void VlcWidgetVideo::setScale(const Vlc::Scale &scale) {
    if (_vlcMediaPlayer) {
        _currentScale = scale;
        _vlcMediaPlayer->video()->setScale(scale);
    }
}

WId VlcWidgetVideo::request() {
    if (_video)
        return 0;

    _video = new QWidget();
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    _video->setPalette(plt);
    _video->setAutoFillBackground(true);
    _video->setMouseTracking(true);
    _layout->addWidget(_video);

#if defined(Q_WS_X11)
    XSync(QX11Info::display(), False);
#endif

    return _video->winId();
}

void VlcWidgetVideo::release() {
    if (_video) {
        _layout->removeWidget(_video);
        _video->deleteLater();
        _video = nullptr;
    }

    this->updateGeometry();
}
