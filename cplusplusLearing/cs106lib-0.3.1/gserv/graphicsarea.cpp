/*
 * File: graphicsarea.cpp
 * Last modified August 2011, by Colin
 * -------------------------------------------------
 * The GraphicsArea object is a rectangle within GraphicsHandler::_gScene
 * whose only function is to respond to mouse events.
 */

#include "graphicsarea.h"

GraphicsArea::GraphicsArea(double sceneWidth,
                           double sceneHeight) :
    QGraphicsRectItem(0, 0, sceneWidth, sceneHeight)
{
    this->setPen(QPen(Qt::lightGray));
    this->setPos(0, 0);

    _lastMouseEvent.pos = QPointF(0,0);
    _lastMouseEvent.btn = Qt::NoButton;
    _lastMouseEvent.pressed = false;
//    qDebug() << "Graphics area constructed";
}

// Mouse support

double GraphicsArea::getMouseX()
{
    return _lastMouseEvent.pos.x();
}

double GraphicsArea::getMouseY()
{
    return _lastMouseEvent.pos.y();
}

QString GraphicsArea::mouseButtonIsDown()
// WARNING - only accurate if the mouse was within the
// GraphicsArea when pressed
{
    if (_lastMouseEvent.pressed) return "TRUE";
    else return "FALSE";
}

// re-implemented QGraphicsItem functions

void GraphicsArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
// WARNING - only works if the  mouse was within the
// GraphicsArea when pressed
{
    _lastMouseEvent.pos = event->pos();
    _lastMouseEvent.btn = event->button();
    _lastMouseEvent.pressed = true;
//    qDebug() << "press" << _lastMouseEvent.pos.x()
//             << _lastMouseEvent.pos.y();
}

void GraphicsArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// works after any valid mousePressEvent, even if the pointer moves
// outside the GraphicsArea before release
{
    _lastMouseEvent.pos = event->pos();
    _lastMouseEvent.btn = event->button();
    _lastMouseEvent.pressed = false;
//    qDebug() << "release" << _lastMouseEvent.pos.x()
//             << _lastMouseEvent.pos.y();
}

void GraphicsArea::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
// WARNING - only works after a valid mousePressEvent and before
// the matching mouseReleaseEvent.  It's unclear how to track
// the mouse more generally (?)
{
    _lastMouseEvent.pos = event->pos();
//    qDebug() << "move" << _lastMouseEvent.pos.x()
//             << _lastMouseEvent.pos.y();
}
