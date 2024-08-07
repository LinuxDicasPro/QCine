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

#ifndef VLCQT_WIDGETSEEKPROGRESS_H_
#define VLCQT_WIDGETSEEKPROGRESS_H_

#include "WidgetSeek.h"

class QProgressBar;

/*!
    \class VlcWidgetSeekProgress WidgetSeekProgress.h VLCQtWidgets/WidgetSeekProgress.h
    \ingroup VLCQtWidgets
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides a display of elapsed time and full time of the media using a progress bar.
*/
class VLCQT_WIDGETS_EXPORT VlcWidgetSeekProgress : public VlcWidgetSeek {
    Q_OBJECT
public:
    /*!
        \brief VlcWidgetSeekProgress constructor
        \param player media player
        \param parent seek widget's parent GUI widget
    */
    explicit VlcWidgetSeekProgress(VlcMediaPlayer *player, QWidget *parent = nullptr);

    /*!
        \brief VlcWidgetSeekProgress constructor
        \param parent seek widget's parent GUI widget
    */
    explicit VlcWidgetSeekProgress(QWidget *parent = nullptr);

    /*!
        \brief VlcWidgetSeekProgress destructor
    */
    ~VlcWidgetSeekProgress() override;

protected:
    /*!
        \brief Mouse move event override
        \param event mouse event
    */
    void mouseMoveEvent(QMouseEvent *event) override;

    /*!
        \brief Mouse press event override
        \param event mouse event
    */
    void mousePressEvent(QMouseEvent *event) override;

    /*!
        \brief Mouse release event override
        \param event mouse event
    */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /*!
        \brief Mouse wheel event override
        \param event mouse event
    */
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void updateCurrentTime(int time) override;

    void updateFullTime(int time) override;

private:
    void setSliderWidget(QWidget *slider, bool updateSlider) override;

    void updateEvent(const QPoint &pos);

    void lock() { _lock = true; }
    void unlock() { _lock = false; }

    bool _lock;
};

#endif // VLCQT_WIDGETSEEKPROGRESS_H_
