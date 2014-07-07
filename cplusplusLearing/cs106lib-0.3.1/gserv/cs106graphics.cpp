/*
 * File: cs106graphics.cpp
 * Created by Colin Leach, July 2011
 * --------------------------------------------------------
 * Implementation of the GraphicsHandler class
 * See cs106graphics.h for more description
 */

#include "cs106graphics.h"

using namespace std;

GraphicsHandler::GraphicsHandler(QGraphicsScene *graphicsScene,
                                 gWin *pWin):
    _gScene(graphicsScene),
    parentWin(pWin)


{
    _currState = new graphicsState;
    _currFont = new QFont;
    _currPen = new QPen;
    _currBrush = new QBrush;
    _sceneWidth = DEFWIDTH;
    _sceneHeight = DEFHEIGHT;
    _boundBox = NULL;
    _soundOn = false;

    /* _coord=INCH is the default (unfortunately?)
     * Change it with a "SETCOORDINATESYSTEM xx" message immediately after
     * INITGRAPHICS, and before any move, draw or resize commands.
     * Changing coordinates later will have no effect until the next InitGraphics() call.
     * Note that the server uses SCREEN cordinates internally.
     */
    _coord = INCH;

    initGraphics();
    initColors();
}

GraphicsHandler::~GraphicsHandler()
{
    delete _boundBox;
}

QString GraphicsHandler::parseMsg(QString msg)
{
    // tokenize the input string
    QTextStream ss(&msg);
    QString tokens[MAXTOKENS];
    QString cmd, rest;
    ss >> cmd;
    rest = ss.readAll().trimmed(); // untokenized string literal, needed by drawTextString
    ss.seek(0);
    for (int i=0; i<MAXTOKENS; i++) {
        ss >> tokens[i];
        if (tokens[i] == "") break;
    }

    // dispatch to the relevant private method
    cmd = cmd.toUpper();
    if (cmd == "INITGRAPHICS") return initGraphics();
    else if (cmd == "MOVEPEN") return movePen(tokens[1], tokens[2]);
    else if (cmd == "DRAWLINE") return drawLine(tokens[1], tokens[2]);
    else if (cmd == "DRAWARC") return drawArc(tokens[1], tokens[2], tokens[3]);
    else if (cmd == "DRAWELLIPTICALARC")
        return drawEllipticalArc(tokens[1], tokens[2], tokens[3], tokens[4]);
    else if (cmd == "STARTFILLEDREGION") return startFilledRegion(tokens[1]);
    else if (cmd == "ENDFILLEDREGION") return endFilledRegion();
    else if (cmd == "UPDATEDISPLAY") return updateDisplay();
    else if (cmd == "EXITGRAPHICS") return exitGraphics();
    else if (cmd == "GETCURRENTX") return getCurrentX();
    else if (cmd == "GETCURRENTY") return getCurrentY();
    else if (cmd == "GETWINDOWWIDTH") return getWindowWidth();
    else if (cmd == "GETWINDOWHEIGHT") return getWindowHeight();
    else if (cmd == "GETFULLSCREENWIDTH") return getFullScreenwWidth();
    else if (cmd == "GETFULLSCREENHEIGHT") return getFullScreenHeight();
    else if (cmd == "GETXRESOLUTION") return getXResolution();
    else if (cmd == "GETYRESOLUTION")return getYResolution();
    else if (cmd == "SETPENCOLOR")return setPenColor(tokens[1].toUpper());
    else if (cmd == "SETPENCOLORRGB")
        return setPenColorRGB(tokens[1], tokens[2], tokens[3]);
    else if (cmd == "GETPENCOLOR") return getPenColor();
    else if (cmd == "DEFINECOLOR")
        return defineColor(tokens[1].toUpper(), tokens[2], tokens[3], tokens[4]);
    else if (cmd == "DRAWTEXTSTRING") return drawTextString(rest);
    else if (cmd == "TEXTSTRINGWIDTH") return textStringWidth(rest);
    else if (cmd == "SETFONT") return setFont(rest);
    else if (cmd == "GETFONT") return getFont();
    else if (cmd == "SETPOINTSIZE") return setPointSize(tokens[1]);
    else if (cmd == "GETPOINTSIZE") return getPointSize();
    else if (cmd == "SETSTYLE") return setStyle(tokens[1]);
    else if (cmd == "GETSTYLE") return getStyle();
    else if (cmd == "GETFONTASCENT") return getFontAscent();
    else if (cmd == "GETFONTDESCENT") return getFontDescent();
    else if (cmd == "GETFONTHEIGHT") return getFontHeight();
    else if (cmd == "GETMOUSEX") return getMouseX();
    else if (cmd == "GETMOUSEY") return getMouseY();
    else if (cmd == "MOUSEBUTTONISDOWN") return _boundBox->mouseButtonIsDown();
    else if (cmd == "DRAWNAMEDPICTURE") return drawNamedPicture(rest);
    else if (cmd == "GETPICTUREWIDTH") return getPictureWidth(tokens[1]);
    else if (cmd == "GETPICTUREHEIGHT") return getPictureHeight(tokens[1]);
    else if (cmd == "SETCOORDINATESYSTEM") return setCoordinateSystem(tokens[1].toUpper());
    else if (cmd == "GETCOORDINATESYSTEM") return getCoordinateSystem();
    else if (cmd == "SETERASEMODE") return setEraseMode(tokens[1]);
    else if (cmd == "GETERASEMODE") return getEraseMode();
    else if (cmd == "SETWINDOWTITLE") return setWindowTitle(rest);
    else if (cmd == "GETWINDOWTITLE") return getWindowTitle();
    else if (cmd == "SETWINDOWSIZE") return setWindowSize(tokens[1], tokens[2]);
    else if (cmd == "GETWINDOWSIZE") return getWindowSize();
    else if (cmd == "SAVEGRAPHICSSTATE") return SaveGraphicsState();
    else if (cmd == "RESTOREGRAPHICSSTATE") return RestoreGraphicsState();
    else if (cmd == "PLAYNAMEDSOUND") return PlayNamedSound(tokens[1]);
    else if (cmd == "SETSOUNDON") return SetSoundOn(tokens[1]);
    else if (cmd == "TESTSOUND") return TestSound();
    else if (cmd == "PAUSE") return pause(tokens[1]);
    else if (cmd == "TESTCONNECTION") return "OK";
    else return "COMMAND NOT UNDERSTOOD";
}

QString GraphicsHandler::initGraphics()
// called from the class constructor,
// also when erasing the current window and
// restarting from default settings
{
    _currFont->setFamily("Helvetica");
    _currFont->setPointSize(12);
    _currFont->setWeight(QFont::Normal);
    _currFont->setStyle(QFont::StyleNormal);

    _currState->penX = 1;
    _currState->penY = 1;
    _currState->fontName = _currFont->family();
    _currState->pointSize = _currFont->pointSize();
    _currState->penColor = Qt::black;
    _currState->penColorName = "Black";
    _currState->eraseMode = false;

    _currPen->setColor(Qt::black);
    _currBrush->setColor(Qt::black);

    _fillingRegion = false;
    _fillStarted = false;

    clearScreen();
    return "OK";
}

void GraphicsHandler::clearScreen()
{
    _gScene->clear();
    _gScene->setSceneRect(0, 0, _sceneWidth, _sceneHeight);
    _boundBox = new GraphicsArea(_sceneWidth, _sceneHeight);
    _gScene->addItem(_boundBox);
    _boundBox->show();
}

void GraphicsHandler::setBounds()
{
    if (_boundBox != NULL) {
        _gScene->removeItem(_boundBox);
        delete _boundBox;
    }
    _gScene->setSceneRect(0, 0, _sceneWidth, _sceneHeight);
    _boundBox = new GraphicsArea(_sceneWidth, _sceneHeight);
    _gScene->addItem(_boundBox);
    _boundBox->show();
}

void GraphicsHandler::initColors()
// Creates an initial color map; defineColor() can extend this later
{
    // these are the CS106 standard colors
    _colorMap["BLACK"] = Qt::black;
    _colorMap["DARKGRAY"] = Qt::darkGray;
    _colorMap["GRAY"] = Qt::gray;
    _colorMap["LIGHTGRAY"] = Qt::lightGray;
    _colorMap["WHITE"] = Qt::white;
    _colorMap["RED"] = Qt::red;
    _colorMap["YELLOW"] = Qt::yellow;
    _colorMap["GREEN"] = Qt::green;
    _colorMap["CYAN"] = Qt::cyan;
    _colorMap["BLUE"] = Qt::blue;
    _colorMap["MAGENTA"] = Qt::magenta;

    // these are not CS106 standard, but Qt (and many other programs)
    // understand them so let's add them as an extension
    _colorMap["WHITE"] = Qt::white;
    _colorMap["DARKRED"] = Qt::darkRed;
    _colorMap["DARKGREEN"] = Qt::darkGreen;
    _colorMap["DARKBLUE"] = Qt::darkBlue;
    _colorMap["DARKCYAN"] = Qt::darkCyan;
    _colorMap["DARKMAGENTA"] = Qt::darkMagenta;
    _colorMap["DARKYELLOW"] = Qt::darkYellow;
}

int GraphicsHandler::width()
{
       return _sceneWidth;
}

int GraphicsHandler::height()
{
    return _sceneHeight;
}

QString GraphicsHandler::movePen(QString toX, QString toY)
{
    if (_fillStarted) return "INVALID MOVEPEN DURING FILLED REGION";

    double x = xToScreen(stringToPositiveDouble(toX));
    double y = yToScreen(stringToPositiveDouble(toY));
//    qDebug() << "movePen: toY : " << toY << "    y: " << y << endl;

    if ((x >= 0) && (y >= 0)) {
        _currState->penX = x;
        _currState->penY = y;
        if (_fillingRegion) _fillPath->moveTo(x,y);
        return "OK";
    }
    else return "MOVE FAILED";
}

QString GraphicsHandler::drawLine(QString dX, QString dY)
{
    bool ok;

    double numdX = dX.toDouble(&ok);
    if (!ok) return "DRAW FAILED - COORDS NOT UNDERSTOOD";
    double numdY = dY.toDouble(&ok);
    if (!ok) return "DRAW FAILED - COORDS NOT UNDERSTOOD";

    double toX = _currState->penX + xToScreen(numdX);
    double toY = _currState->penY + deltaYToScreen(numdY);
//    qDebug() << "drawLine: dY : " << numdY
//             << "   from: "  << _currState->penY
//             << "    toY: " << toY << endl;

    // Don't allow drawing outside the box
//    if (toX>=0 && toY>=0 && toX<=_sceneWidth && toY<=_sceneHeight) {
        if (_fillingRegion) {
            _fillStarted = true;
            _fillPath->lineTo(toX, toY);
        }
        else {
            QGraphicsLineItem *line =
                    new QGraphicsLineItem(_currState->penX,
                                          _currState->penY,
                                          toX, toY,
                                          _boundBox, _gScene);
            if (_currState->eraseMode) line->setPen(QPen(Qt::white));
            else line->setPen(*_currPen);
        }
        _currState->penX = toX;
        _currState->penY = toY;
        return "OK";
//    }
//    else return "DRAW FAILED - COORDS OUT OF RANGE";
}

QString GraphicsHandler::drawArc(QString r, QString start, QString sweep)
// Wrapper function for drawEllipticalArc, setting both radii the same
{
    QString resp = drawEllipticalArc(r, r, start, sweep);
    return resp;
}

QString GraphicsHandler::drawEllipticalArc(QString rx, QString ry, QString start, QString sweep)
/*
 *  Parameters: rx, ry = radius parallel to each axis,
 *              start = angle from x axis (degrees, can be negative)
 *              sweep = angle from start to end of arc (degrees, can be -ve)
 */
{
    bool ok;
    double numRx = rx.toDouble(&ok);
    if (!ok) return "DRAW FAILED - RADIUS NOT UNDERSTOOD";
    double numRy = ry.toDouble(&ok);
    if (!ok) return "DRAW FAILED - RADIUS NOT UNDERSTOOD";
    double numStart = start.toDouble(&ok);
    if (!ok) return "DRAW FAILED - ANGLE NOT UNDERSTOOD";
    double numSweep = sweep.toDouble(&ok);
    if (!ok) return "DRAW FAILED - ANGLE NOT UNDERSTOOD";

    // fix coordinate values
    numRx = xToScreen(numRx);
    numRy = xToScreen(numRy); // x is not a typo

    // need the bounding rect, so first find the radius at angles start & end
    double rStart, rEnd;

    if (rx == ry) { // circle is a special case
        rStart = numRx;
        rEnd = numRx;
    }
    else {  // use polar form of elipse equation
        rStart = ellipseRadius(numRx, numRy, numStart);
        rEnd = ellipseRadius(numRx, numRy, numStart + numSweep);
     }

    // next find the center
    double centerX = _currState->penX - rStart * cos(degToRad(numStart));
    double centerY = _currState->penY + rStart * sin(degToRad(numStart));

    QRect arcBound =
            QRect(centerX - numRx, centerY - numRy, 2 * numRx, 2 * numRy);

    if (_fillingRegion) {
        // add to the existing QPainterPath
        _fillStarted = true;
        _fillPath->arcTo(arcBound, numStart, numSweep);
    }
    else {
        // define the arc as a QPainterPath
        QPainterPath arcPath;
        arcPath.arcMoveTo(arcBound, numStart);
        arcPath.arcTo(arcBound, numStart, numSweep);

        QGraphicsPathItem *arc =
                new QGraphicsPathItem(arcPath, _boundBox, _gScene);
        if (_currState->eraseMode) arc->setPen(QPen(Qt::white));
        else arc->setPen(*_currPen);
    }

    // move the current pen position
    double endAngleRads = degToRad(numStart + numSweep);
    _currState->penX = centerX + rEnd * cos(endAngleRads);
    _currState->penY = centerY - rEnd * sin(endAngleRads);
    return "OK";
}

QString GraphicsHandler::startFilledRegion(QString density)
{
    double numDensity = stringToPositiveDouble(density);
    if (numDensity < 0) return "INVALID DENSITY";

    _currBrush->setStyle(translateDensity(numDensity));
//     postpone color setting to the end, in case it changes again
//    _currBrush->setColor(_currState->penColor);

    _fillingRegion = true;
    _fillPath = new QPainterPath(QPointF(_currState->penX, _currState->penY));
    _fillPath->setFillRule(Qt::WindingFill);
    return "OK";
}

QString GraphicsHandler::endFilledRegion()
{
//    _fillPath->closeSubpath();
    QGraphicsPathItem *filledRegion =
            new QGraphicsPathItem(*_fillPath, _boundBox, _gScene);
    if (_currState->eraseMode) {
        filledRegion->setPen(QPen(Qt::white));
        filledRegion->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    }
    else {
        filledRegion->setPen(*_currPen);
        filledRegion->setBrush(*_currBrush);
    }
    delete _fillPath;
    _fillingRegion = false;
    _fillStarted = false;
    return "OK";
}

QString GraphicsHandler::updateDisplay()
{
    _gScene->update(0, 0, _sceneWidth, _sceneHeight);
    return "OK";
}

QString GraphicsHandler::exitGraphics()
/*
 * Do we need this?  The client can send a QUIT signal to disconnect.
 * To be decided - should the client be allowed to close the server,
 * or should it keep listening for further clients?
 */
{
    return "NOT YET IMPLEMENTED";
}


QString GraphicsHandler::getCurrentX()
{
    return doubleToString(xFromScreen(_currState->penX));
}

QString GraphicsHandler::getCurrentY()
{
    return doubleToString(yFromScreen(_currState->penY));
}

QString GraphicsHandler::getWindowWidth()
{
    return doubleToString(xFromScreen(_sceneWidth));
}

QString GraphicsHandler::getWindowHeight()
{
    // this is kind of clumsy, but xFromScreen does the right thing for each _coord
    // yFromScreen worries about whether the origin is top or bottom, not relevant here
    return doubleToString(xFromScreen(_sceneHeight));
}

QString GraphicsHandler::getFullScreenwWidth()
{
    QDesktopWidget screen;
    QRect geom = screen.screenGeometry(parentWin);
    int width = geom.width();
    return intToString(xFromScreen(width));
}

QString GraphicsHandler::getFullScreenHeight()
{
    QDesktopWidget screen;
    QRect geom = screen.screenGeometry(parentWin);
    int height = geom.height();
    return intToString(xFromScreen(height));
}

/* Getting the actual screen resolution is an unsolved problem.
 * Let's just assume that DEFRESOLUTION dpi is approximately
 * typical, with x and y the same.
 */
QString GraphicsHandler::getXResolution()
{
    return intToString(DEFRESOLUTION);
}

QString GraphicsHandler::getYResolution()
{
    return intToString(DEFRESOLUTION);
}

QString GraphicsHandler::setPenColor(QString color)
// Note that all color names have been forced to uppercase
// Spaces in double-word names are omitted ("LIGHTGRAY", not "Light Gray")
{
    if (_colorMap.contains(color)) {
        QColor newColor = _colorMap.value(color);
        _currPen->setColor(newColor);
        _currBrush->setColor(newColor);
        _currState->penColor = newColor;
        _currState->penColorName = color;
        return "OK";
    }
    else return "INVALID COLOR";
}

QString GraphicsHandler::setPenColorRGB(QString r, QString g, QString b)
{
    double numRed = stringToPositiveDouble(r);
    double numGreen = stringToPositiveDouble(g);
    double numBlue = stringToPositiveDouble(b);

    if (numRed >= 0 && numGreen >= 0 && numBlue >= 0) {
        QColor newColor(numRed * 255, numGreen * 255, numBlue * 255);
        _currPen->setColor(newColor);
        _currBrush->setColor(newColor);
        _currState->penColor = newColor;
        _currState->penColorName = "custom"; // an RGB string like #FFFFFF would be better?
        return "OK";
    }
    else return "INVALID COLOR VALUE(S)";
}

QString GraphicsHandler::getPenColor()
{
    return _currState->penColorName;
}

QString GraphicsHandler::defineColor(QString name, QString r, QString g, QString b)
{
    double numRed = stringToPositiveDouble(r);
    double numGreen = stringToPositiveDouble(g);
    double numBlue = stringToPositiveDouble(b);

    if (numRed >= 0 && numGreen >= 0 && numBlue >= 0) {
        QColor newColor = QColor(numRed * 255, numGreen * 255, numBlue * 255);
        _colorMap[name] = newColor;
        return "OK";
    }
    else return "INVALID COLOR VALUE(S)";
}

// Text support
QString GraphicsHandler::drawTextString(QString text)
{
    QGraphicsTextItem *newText = new QGraphicsTextItem(text);
    newText->setFont(*_currFont);

    // Need to set the BOTTOM of the text to current pen position
    // Qt positions the TOP
    QFontMetrics inf(*_currFont);
    int textheight = inf.lineSpacing();

    /* PROBLEM!
     * When deleting, adding text in white leaves a visible outline
     * Not expected!
     * Workaround - add a white filled rectangle instead
     */
    //    if (_currState->eraseMode) {
    //        newText->setDefaultTextColor(Qt::white);
    //    }
    //    else {
    //        newText->setDefaultTextColor(_currState->penColor);
    //    }
    //    newText->setPos(_currState->penX, _currState->penY);
    //    _gScene->addItem(newText);

    if (!_currState->eraseMode) {
        newText->setDefaultTextColor(_currState->penColor);
        newText->setPos(_currState->penX, _currState->penY - textheight);
        _gScene->addItem(newText);
    }

    // Now get the dimensions, used to update the pen position
    QRectF textBound = newText->boundingRect();

    // If erasing, draw a white rectangle over the whole text area
    if (_currState->eraseMode) {
        QGraphicsRectItem *rect =
                _gScene->addRect(textBound, QPen(Qt::white), QBrush(Qt::white));
        rect->setPos(_currState->penX, _currState->penY - textheight);
     }

    _currState->penX += textBound.width();
    return "OK";
}

QString GraphicsHandler::textStringWidth(QString text)
{
    QGraphicsTextItem newText(text);
    newText.setFont(*_currFont);
    double textWidth = newText.boundingRect().width();
    return doubleToString(xFromScreen(textWidth));
}

QString GraphicsHandler::setFont(QString font)
{
    _currFont->setFamily(font);
    return "OK";
}

QString GraphicsHandler::getFont()
{
    return _currFont->family();
}

QString GraphicsHandler::setPointSize(QString pSize)
{
    int numSize = stringToPositiveInt(pSize);
    if (numSize > 0) {
        _currFont->setPointSize(numSize);
        return "OK";
    }
    else return "INVALID SIZE";
}

QString GraphicsHandler::getPointSize()
{
    return intToString(_currFont->pointSize());
}

QString GraphicsHandler::setStyle(QString style)
{
    int intStyle = stringToPositiveInt(style);
    if (intStyle & 0x01) _currFont->setBold(true);
      else _currFont->setBold(false);
    if (intStyle & 0x02) _currFont->setStyle(QFont::StyleItalic);
      else _currFont->setStyle(QFont::StyleNormal);
    return "OK";
}

QString GraphicsHandler::getStyle()
{
    int currStyle = 0;
    if (_currFont->style() == QFont::StyleItalic) currStyle =+ 2;
    if (_currFont->weight() == QFont::Bold) currStyle =+ 1;
    return intToString(currStyle);
}

QString GraphicsHandler::getFontAscent()
{
    QFontMetrics inf(*_currFont);
    return doubleToString(xFromScreen(inf.ascent()));
}

QString GraphicsHandler::getFontDescent()
{
    QFontMetrics inf(*_currFont);
    return doubleToString(xFromScreen(inf.descent()));
}

QString GraphicsHandler::getFontHeight()
// In the CS106 definition this includes leading.
// Contrast QFontMetrics.height(), which doesn't.
// Therefore we use lineSpacing() instead.
{
    QFontMetrics inf(*_currFont);
    return doubleToString(xFromScreen(inf.lineSpacing()));
}

// Mouse stuff - -boundBox does the tracking, here we just need coordinate conversions
QString GraphicsHandler::getMouseX()
{
    return doubleToString(xFromScreen(_boundBox->getMouseX()));
}

QString GraphicsHandler::getMouseY()
{
//    double lastY = _boundBox->getMouseY();
//    qDebug() << "raw y: " << lastY << "  processed: " << doubleToString(yFromScreen(lastY));
    return doubleToString(yFromScreen(_boundBox->getMouseY()));
}

/*   PICTURES
 *
 * The name must be an absolute path, as the server doesn't know
 * the client's working directory.
 *
 * Also, the TCP connection had better be on Localhost!
 */

QString GraphicsHandler::drawNamedPicture(QString name)
{
    QFile picFile(name);
    if (picFile.exists()) {
        QPixmap pic(name);
        QGraphicsPixmapItem *picItem =
                new QGraphicsPixmapItem(pic, _boundBox, _gScene);
        picItem->setPos(_currState->penX, _currState->penY);

        // save some key details, to save re-reading big files later
        QFileInfo picInfo(picFile);
        QSizeF picSize(pic.width(), pic.height());
        _picMap.insert(picInfo.fileName(), picSize);
        return "OK";
    }
    else return "FILE NOT FOUND";
}

QString GraphicsHandler::getPictureWidth(QString name)
{

    if (_picMap.contains(name))
        return doubleToString(xFromScreen(_picMap.value(name).width()));
    else return "INVALID NAME";
}

QString GraphicsHandler::getPictureHeight(QString name)
{
    if (_picMap.contains(name))
        return doubleToString(xFromScreen(_picMap.value(name).height()));
    else return "INVALID NAME";
}

// Miscellaneous
QString GraphicsHandler::setCoordinateSystem(QString system)
{
    if (system == "INCH") { // an extension to Stanford's API, for debugging use
        _coord = INCH;
        return "OK";
    }
    if (system == "CARTESIAN") {
        _coord = CARTESIAN;
        return "OK";
    }
    if (system == "SCREEN") {
        _coord = SCREEN;
        return "OK";
    }
    return "INVALID SETTING";
}

QString GraphicsHandler::getCoordinateSystem()
{
    switch (_coord) {
        case INCH:
            return "INCH";
            break;
        case CARTESIAN:
            return "CARTESIAN";
            break;
        case SCREEN:
            return "SCREEN";
            break;
        default:
            return "INVALID!!";
    }
}

QString GraphicsHandler::setEraseMode(QString eMode)
{
    if (eMode == "TRUE") {
        _currState->eraseMode = true;
        return "OK";
    }
    if (eMode == "FALSE") {
        _currState->eraseMode = false;
        return "OK";
    }
    return "INVALID MODE";
}

QString GraphicsHandler::getEraseMode()
{
    if (_currState->eraseMode) return "TRUE";
    else return "FALSE";
}

QString GraphicsHandler::setWindowTitle(QString title)
{
    parentWin->setWinTitle(title);
    return "OK";
}

QString GraphicsHandler::getWindowTitle()
{
    return parentWin->getWinTitle();
}

QString GraphicsHandler::setWindowSize(QString width, QString height)
/* NOTE!!
 * This sets the QGraphicsScene to the specified size
 * The surrounding window is larger, by an amount set in gWin::setWinSize()
 */
{
    double w = stringToPositiveDouble(width);
    double h = stringToPositiveDouble(height);
    if (w>0 && h>0) {
        w = xToScreen(w);
        h = xToScreen(h);
        parentWin->setWinSize(w, h);
        _sceneWidth= w;
        _sceneHeight = h;
        setBounds();
        return "OK";
    }
    return "INVALID SIZE(S)";
}

QString GraphicsHandler::getWindowSize()
{
    return parentWin->getWinSize(_coord, DEFRESOLUTION);
}

QString GraphicsHandler::SaveGraphicsState()
{
    graphicsState *toSave = new graphicsState;
    toSave->penX = _currState->penX;
    toSave->penY = _currState->penY;
    toSave->fontName = _currFont->family();
    toSave->pointSize = _currFont->pointSize();
    toSave->penColor = _currState->penColor;
    toSave->penColorName = _currState->penColorName;
    toSave->eraseMode = _currState->eraseMode;
    _savedStates.push(toSave);
    return "OK";
}

QString GraphicsHandler::RestoreGraphicsState()
{
    if (_savedStates.isEmpty()) return "ERROR - NOTHING TO RESTORE";
    else {
        graphicsState *toRestore = _savedStates.pop();
        _currState->penX = toRestore->penX;
        _currState->penY = toRestore->penY;
        _currState->fontName = toRestore->fontName;
        _currState->pointSize = toRestore->pointSize;
        _currFont->setFamily(_currState->fontName);
        _currFont->setPointSize(_currState->pointSize);
// Colors are not part of the CS106 standard for this function (a bit odd??)
//        _currState->penColor = toRestore->penColor;
//        _currState->penColorName = toRestore->penColorName;
        _currState->eraseMode = toRestore->eraseMode;
        delete toRestore;
        return "OK";
    }

}

QString GraphicsHandler::pause(QString msecs)
/* NOTE: this expects an integer number of milliseconds
 * Contrast the CS106 pause() function, which passes seconds as a double.
 *
 * In practice, 1 millisec resolution is the best you can probably
 * hope for from most computers.
 * The return value is the actual delay, maybe a bit higher than
 * you asked for.
 */
{
    int msecDelay = stringToPositiveInt(msecs);
    if (msecDelay > 0) {
        QTime start;
        start = QTime::currentTime();
        while (start.msecsTo(QTime::currentTime()) < msecDelay) {
             // do nothing
        }
        return intToString(start.msecsTo(QTime::currentTime()));
    }
    else return "INVALID DELAY";
}


/****************************************************************
 * Sound files, implementing sound.h functions.
 * Don't try anything fancy - small WAV files should work,
 * but this isn't an interface to a full media player.
 *
 * As with ShowNamedPicture(), a fully-specified filename is
 * needed, including an absolute path.
 */

QString GraphicsHandler::PlayNamedSound(QString wavName)
{
    QFile wavFile(wavName);
    if (wavFile.exists() && _soundOn) {
        QSound::play(wavName);
        return "OK";
    }
    return "COULD NOT OPEN SOUND FILE";
}

QString GraphicsHandler::SetSoundOn(QString on)
{
    if (on.toUpper() == "Y") _soundOn = true;
    else _soundOn = false;
    return "OK";
}

QString GraphicsHandler::TestSound()
{
    if (QSound::isAvailable()) return "OK";
    else return "NO SOUND ON THIS SYSTEM";
}

/****************************************************************
 * That's the end of the Stanford CS106B/X methods
 * Various helper functions follow
 */

QString GraphicsHandler::intToString(int n)
{
    QString str;
    str.setNum(n);
    return str;
}

QString GraphicsHandler::doubleToString(double n)
{
    QString str;
    str.setNum(n);
    return str;
}

int GraphicsHandler::stringToPositiveInt(QString s)
// negative return value means error
{
    bool ok;
    int i;
    i = s.toInt(&ok);
    if (ok) return i;
    else return -1;
}

double GraphicsHandler::stringToPositiveDouble(QString s)
// negative return value means error
{
    bool ok;
    double n;
    n = s.toDouble(&ok);
    if (ok) return n;
    else return -1;
}

double GraphicsHandler::degToRad(double Angle)
/* pi radians = 180 degrees
 * The CS106 libraries work in degrees, C++ trig functions need radians
 */
{
  static double ratio = 3.141592653589793238 / 180;
  return Angle * ratio;
}

double GraphicsHandler::ellipseRadius(double rX, double rY, double theta)
/* Thanks to Wikipedia for the equation:
 * http://en.wikipedia.org/wiki/Ellipse#Polar_form_relative_to_center
 * rX, rY are the semimajor axes, theta is the angle from the x axis
 * Returns the radius (from the center) at the specified angle
 */
{
    double rTheta;
    double cosTheta = cos(degToRad(theta));
    double sinTheta = sin(degToRad(theta));

    rTheta = rX * rY /
            sqrt((rY * rY * cosTheta * cosTheta) +
                 (rX * rX * sinTheta * sinTheta));
    return rTheta;
}

Qt::BrushStyle GraphicsHandler::translateDensity(double density)
{
    if (density < 0.06) return Qt::NoBrush;
    if (density < 0.19) return Qt::Dense7Pattern;
    if (density < 0.31) return Qt::Dense6Pattern;
    if (density < 0.43) return Qt::Dense5Pattern;
    if (density < 0.56) return Qt::Dense4Pattern;
    if (density < 0.68) return Qt::Dense3Pattern;
    if (density < 0.80) return Qt::Dense2Pattern;
    if (density < 0.92) return Qt::Dense1Pattern;
    return Qt::SolidPattern;
}

/*
 * Coordinate translation functions
 *
 * Note that X values always increase to the right, but Y values
 * can increase either up (INCH, CARTESIAN) or down (SCREEN)
 */

double GraphicsHandler::xToScreen(double x)
/*
 * Input depends on coordinate system stored in _coord,
 * return value is in SCREEN pixels, used internally by the server
 */
{
    switch (_coord) {
        case INCH:
            return x * DEFRESOLUTION;
            break;
        case CARTESIAN:
        case SCREEN:
            return x;
            break;
        default:
            return -999; // garbage value in _coord - should we throw an exception instead?
    }
}

double GraphicsHandler::yToScreen(double y)
{
    switch (_coord) {
        case INCH:
            return _sceneHeight - (y * DEFRESOLUTION);
            break;
        case CARTESIAN:
            return _sceneHeight - y;
            break;
        case SCREEN:
            return y;
            break;
        default:
            return -999; // garbage value in _coord - should we throw an exception instead?
    }
}

double GraphicsHandler::deltaYToScreen(double y)
{
    switch (_coord) {
        case INCH:
            return -(y * DEFRESOLUTION);
            break;
        case CARTESIAN:
            return -y;
            break;
        case SCREEN:
            return y;
            break;
        default:
            return -999; // garbage value in _coord - should we throw an exception instead?
    }
}

double GraphicsHandler::xFromScreen(double x)
/*
 * Input is in SCREEN pixels,
 * return value depends on coordinate system stored in _coord
 */
{
    switch (_coord) {
        case INCH:
            return x / DEFRESOLUTION;
            break;
        case CARTESIAN:
        case SCREEN:
            return x;
            break;
        default:
            return -999; // garbage value in _coord - should we throw an exception instead?
    }
}

double GraphicsHandler::yFromScreen(double y)
{
    switch (_coord) {
        case INCH:
            return (_sceneHeight - y) / DEFRESOLUTION;
            break;
        case CARTESIAN:
            return _sceneHeight - y;
            break;
        case SCREEN:
            return y;
            break;
        default:
            return -999; // garbage value in _coord - should we throw an exception instead?
    }
}

