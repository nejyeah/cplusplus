/*
 * File: graphicsarea.h
 * Last modified August 2011, by Colin
 */

#ifndef GRAPHICSAREA_H
#define GRAPHICSAREA_H

#include <QtGui>

class GraphicsArea : public QGraphicsRectItem
{

public:
    explicit GraphicsArea(double sceneWidth,
                          double sceneHeight);
    // Mouse support
    double getMouseX();
    double getMouseY();
    QString mouseButtonIsDown();

private:
    // re-implemented QGraphicsItem functions
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    int _areaWidth;
    int _areaHeight;

    struct mouseStatus {
        QPointF pos;
        Qt::MouseButton btn;
        bool pressed;
    };

    mouseStatus _lastMouseEvent;

};

#endif // GRAPHICSAREA_H
