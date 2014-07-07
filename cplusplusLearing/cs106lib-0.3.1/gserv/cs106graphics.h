/*
 * File: cs106graphics.h
 * Created by Colin Leach, July 2011
 * ----------------------------------------
 * Implements the GraphicsHandler class
 * Responsible for:
 *  - parsing client messages
 *  - maintaining graphics state
 *  - low-level graphics operations in the QGraphicsScene
 *  - returning a suitable reponse
 * The response is always in QString format, suitable for passing
 *  to the client program via a TCP port
 *
 * Does not maintain its own on-screen window (gWin does that)
 * Does not separate graphics.h functions from extgraph.h functions
 */

#ifndef CS106GRAPHICS_H
#define CS106GRAPHICS_H

#include "gwin.h"
#include "graphicsarea.h"
#include <QVector>
#include <sstream>
#include <string>
#include <QtCore>
#include <QtGui>

QT_BEGIN_NAMESPACE
class gWin;
class GraphicsArea;
QT_END_NAMESPACE

class GraphicsHandler : public QObject
{
    Q_OBJECT

public:
    GraphicsHandler(QGraphicsScene *graphicsScene,
                    gWin *pWin);
    ~GraphicsHandler();
    QString parseMsg(QString msg);
    int width();
    int height();

    struct graphicsState {
        double penX;
        double penY;
        QString fontName;
        int pointSize;
        QColor penColor;
        QString penColorName;
        bool eraseMode;
    };

    enum e_coord {
        INCH,       // origin lower-left, values in inches"
                    // (though the size of an "inch" may differ on your screen)
        CARTESIAN,  // origin lower-left, values in pixels
        SCREEN      // origin upper-left, values in pixels (the server uses this internally)
    };

private:
    // CS106 graphics methods
    QString initGraphics();
    QString movePen(QString toX, QString toY);
    QString drawLine(QString dX, QString dY);
    QString drawArc(QString r, QString start, QString sweep);
    QString drawEllipticalArc(QString rx, QString ry, QString start, QString sweep);
    QString startFilledRegion(QString density);
    QString endFilledRegion();
    QString updateDisplay();
    QString exitGraphics();
    // get status information
    QString getCurrentX();
    QString getCurrentY();
    QString getWindowWidth();
    QString getWindowHeight();
    QString getFullScreenwWidth();
    QString getFullScreenHeight();
    QString getXResolution();
    QString getYResolution();
    // Color suppoprt
    QString setPenColor(QString color);
    QString setPenColorRGB(QString r, QString g, QString b);
    QString getPenColor();
    QString defineColor(QString name, QString r, QString g, QString b);
    // Text support
    QString drawTextString(QString text);
    QString textStringWidth(QString text);
    QString setFont(QString font);
    QString getFont();
    QString setPointSize(QString pSize);
    QString getPointSize();
    QString setStyle(QString style);
    QString getStyle();
    QString getFontAscent();
    QString getFontDescent();
    QString getFontHeight();
    // Mouse
    QString getMouseX();
    QString getMouseY();
    // Pictures
    QString drawNamedPicture(QString name);
    QString getPictureWidth(QString name);
    QString getPictureHeight(QString name);
    // Miscellaneous
    QString setCoordinateSystem(QString system);
    QString getCoordinateSystem();
    QString setEraseMode(QString eMode);
    QString getEraseMode();
    QString setWindowTitle(QString title);
    QString getWindowTitle();
    QString setWindowSize(QString width, QString height);
    QString getWindowSize();
    QString SaveGraphicsState();
    QString RestoreGraphicsState();
    QString PlayNamedSound(QString wavName);
    QString SetSoundOn(QString on);
    QString TestSound();
    QString pause(QString secs);

    // helper functions
    void initColors();
    void clearScreen();
    void setBounds();
    QString intToString(int n);
    QString doubleToString(double n);
    int stringToPositiveInt(QString s);
    double stringToPositiveDouble(QString s);
    double degToRad(double Angle);
    double ellipseRadius(double rX, double rY, double theta);
    Qt::BrushStyle translateDensity(double density);
    double xToScreen(double x);
    double yToScreen(double y);
    double deltaYToScreen(double y);
    double xFromScreen(double x);
    double yFromScreen(double y);

    // state variables
    graphicsState *_currState;
    QFont *_currFont;
    QPen *_currPen;
    QBrush *_currBrush;
    QMap<QString, QColor> _colorMap;
    GraphicsArea *_boundBox;
    QStack<GraphicsHandler::graphicsState*> _savedStates;

    // pointer to the scene passed from gWin
    QGraphicsScene *_gScene;

    // pointer to window that implements title & size functions
    gWin *parentWin;

    // bounding rectangle is from (0,0) to (sceneWidth, sceneHeight)
    double _sceneWidth;
    double _sceneHeight;

    /*
     * The default coordinate system is defined in graphics.h
     * Two more are defined in extgraph.h function SetCoordinateSystem(),
     * which in Stanford's version does not allow you to return to the default.
     * As an extension, this version allows you to change freely, multiple times.
     * However, you will re-initialize the graphics each time and lose your
     * current settings.
     *
     * Valid values are in the e_coord enum
     */
    e_coord _coord;

    // _fillingRegion is true after startFilledRegion() and before
    // endFilledRegion()
    bool _fillingRegion;
    // _fillStarted means the FilledRegion is part-constructed
    // and MovePen() is currently illegal
    bool _fillStarted;
    // _fillPath defines the outline for the filled region
    QPainterPath *_fillPath;

    // store basic information about pictures to avoid re-reading the files
    QMap<QString, QSizeF> _picMap;

    // sound?
    bool _soundOn;
};

#define MAXTOKENS 6
#define DEFWIDTH 400
#define DEFHEIGHT 200
#define DEFRESOLUTION 100 // pixels per inch

#endif // CS106GRAPHICS_H
