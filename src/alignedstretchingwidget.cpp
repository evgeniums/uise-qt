/**
@copyright Evgeny Sidorov 2021

This software is dual-licensed. Choose the appropriate license for your project.

1. For open source projects this software is distrubuted under the GNU GENERAL PUBLIC LICENSE, Version 3.0.
(See accompanying file LICENSE-GPLv3.md or copy at https://www.gnu.org/licenses/gpl-3.0.txt)

2. For proprietary license contact evgeniums@dracosha.com.

*/

/****************************************************************************/

/** @file uise/desktop/src/alignedstretchingwidget.cpp
*
*  Defines AlignedStretchingWidget.
*
*/

/****************************************************************************/

#include <QVariant>
#include <QResizeEvent>

#include <uise/desktop/utils/layout.hpp>
#include <uise/desktop/utils/destroywidget.hpp>
#include <uise/desktop/alignedstretchingwidget.hpp>

UISE_DESKTOP_NAMESPACE_BEGIN

//--------------------------------------------------------------------------
AlignedStretchingWidget::AlignedStretchingWidget(QWidget *parent)
    : m_widget(parent),
      m_orientation(Qt::Vertical),
      m_alignment(Qt::Alignment())
{
}

//--------------------------------------------------------------------------
QWidget* AlignedStretchingWidget::takeWidget()
{
    if (m_widget)
    {
        m_widget->setProperty("AlignedStretchingWidget",QVariant());
    }

    m_alignment=Qt::Alignment();
    return m_widget.data();
}

//--------------------------------------------------------------------------
void AlignedStretchingWidget::setWidget(
        QWidget *widget,
        Qt::Orientation orientation,
        Qt::Alignment alignment
    )
{
    if (m_widget)
    {
        destroyWidget(m_widget);
    }
    delete layout();

    if (!widget)
    {
        return;
    }

    m_orientation=orientation;
    m_alignment=alignment;

    m_widget=widget;
    m_widget->setParent(this);
    m_widget->setProperty("AlignedStretchingWidget",true);

    m_widget->installEventFilter(this);

    updateSize();
}

//--------------------------------------------------------------------------
void AlignedStretchingWidget::updateSize()
{
    if (!m_widget)
    {
        return;
    }

    auto totalSize=oprop(this,OProp::size);
    auto minSize=oprop(m_widget.data(),OProp::min_size);
    auto maxSize=oprop(m_widget.data(),OProp::max_size);

    auto targetSize=qBound(minSize,totalSize,maxSize);

    auto borderSize=frameWidth();
    auto borderSizeDouble=borderSize*2;
    if (targetSize>=borderSizeDouble)
    {
        targetSize-=borderSizeDouble;
    }

    auto otherSize=oprop(this,OProp::size,true);
    if (otherSize>=borderSizeDouble)
    {
        otherSize-=borderSizeDouble;
    }

    auto oldSize=m_widget->size();
    auto widgetSize=oldSize;
    setOProp(widgetSize,OProp::size,targetSize);
    setOProp(widgetSize,OProp::size,otherSize,true);

    QPoint pos=m_widget->pos();
    m_widget->resize(widgetSize);

    bool move=false;
    if (m_orientation==Qt::Horizontal)
    {
        if (m_alignment & Qt::AlignHCenter)
        {
            setOProp(pos,OProp::pos,(width()-targetSize)/2);
            move=true;
        }
        else if (m_alignment & Qt::AlignRight)
        {
            setOProp(pos,OProp::pos,width()-targetSize-borderSize);
            move=true;
        }
        else if (m_alignment & Qt::AlignLeft)
        {
            setOProp(pos,OProp::pos,borderSize);
            move=true;
        }

        if (m_alignment & Qt::AlignVCenter || (m_alignment & Qt::AlignVertical_Mask)==0)
        {
            setOProp(pos,OProp::pos,(height()-otherSize)/2,true);
            move=true;
        }
        else if (m_alignment & Qt::AlignTop)
        {
            setOProp(pos,OProp::pos,borderSize,true);
            move=true;
        }
        else if (m_alignment & Qt::AlignBottom)
        {
            setOProp(pos,OProp::pos,height()-otherSize-borderSize,true);
            move=true;
        }
    }
    else
    {
        if (m_alignment & Qt::AlignVCenter)
        {
            setOProp(pos,OProp::pos,(height()-targetSize)/2);
            move=true;
        }
        else if (m_alignment & Qt::AlignTop)
        {
            setOProp(pos,OProp::pos,borderSize);
            move=true;
        }
        else if (m_alignment & Qt::AlignBottom)
        {
            setOProp(pos,OProp::pos,height()-targetSize-borderSize);
            move=true;
        }

        if (m_alignment & Qt::AlignHCenter || (m_alignment & Qt::AlignHorizontal_Mask)==0)
        {
            setOProp(pos,OProp::pos,(width()-otherSize)/2,true);
            move=true;
        }
        else if (m_alignment & Qt::AlignRight)
        {
            setOProp(pos,OProp::pos,width()-otherSize-borderSize,true);
            move=true;
        }
        else if (m_alignment & Qt::AlignLeft)
        {
            setOProp(pos,OProp::pos,borderSize,true);
            move=true;
        }
    }

    if (move)
    {
        m_widget->move(pos);
    }

    // after move there can ne artefacts, repaint widget to get rid of them
    repaint();
}

//--------------------------------------------------------------------------
void AlignedStretchingWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    updateSize();
}

//--------------------------------------------------------------------------
bool AlignedStretchingWidget::isHorizontal() const noexcept
{
    return m_orientation==Qt::Horizontal;
}

//--------------------------------------------------------------------------

UISE_DESKTOP_NAMESPACE_EMD