/*
 * File: gwin.cpp
 * Last modified September 2011 by Colin
 * -------------------------------------------------------
 * Implements the gWin class, the main window of the graphics server.
 * Handles the TCP connection and parses incoming messsages.
 * Creates a GraphicsHandler object to handle other details -
 *   see cs106graphics.cpp for details
 */

#include "gwin.h"
#include <iostream>
#include <QtGui>
#include <QtNetwork>
#include "cs106graphics.h"

using namespace std;

gWin::gWin(int port, QString host, bool showTextArea, QWidget *parent)
    : QMainWindow(parent),
    _port(port),
    _host(host),
    _showTextArea(showTextArea)
{
    // Create a visible main window
    setupUi();

    // start the tcpServer listening for connections
    sessionOpened();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConn()));

    // Create the GraphicsHandler object, which implements most of
    // the functions in graphics.h and extgraph.h
    graphicsHandler = new GraphicsHandler(graphicsScene, this);
}

gWin::~gWin() { }

/******************************************************************************
 * Functions to handle client-server connections
 */

void gWin::sessionOpened()
// Create the TCP Server and set it to listen for connections
{
    tcpServer = new QTcpServer(this);
    QHostAddress hostAddr;
    if (_host.toLower() == "any") hostAddr = QHostAddress::Any;
    else if (_host.toLower() == "localhost") hostAddr = QHostAddress::LocalHost;
    else hostAddr = QHostAddress(_host);

    if (!tcpServer->listen(hostAddr, _port)) {
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    QString ipAddress = hostAddr.toString();
    QString msg = QString("Waiting for connection, %1 port %2 ").arg(_host).arg(_port);
    _connMsg->setText(msg);
}

void gWin::newConn()
{
    clientConnection = new QTcpSocket(this);
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(exchangeMsgs()));
    _connMsg->setText("Connected");
}

void gWin::exchangeMsgs()
// triggered by a readyRead signal from clientConnection
{
    // get message from client
    QTextStream in(clientConnection);
    QString msg = in.readLine();
    QString cleanedMsg = msg.toUpper().trimmed();
    if (cleanedMsg == "QUIT" || cleanedMsg == "EXITGRAPHICS") {
        appendText("Connection ended");
        QByteArray ba("Server has disconnected");
        clientConnection->write(ba);
        clientConnection->disconnectFromHost();
        QString msg = QString("Waiting for connection, %1 port %2 ").arg(_host).arg(_port);
        _connMsg->setText(msg);
    } else {
        appendText(msg);
        QString response = graphicsHandler->parseMsg(msg);
;
        // send reply
        QByteArray ba(response.toAscii());
        clientConnection->write(ba);
    }
}

/******************************************************************************
 * Functions to handle displaying the graphics window
 */


void gWin::setupUi()
{
    graphicsScene = new QGraphicsScene;
    graphicsView = new QGraphicsView(graphicsScene);

    // try to get a solid white background - needed for exporting the image
    graphicsScene->setBackgroundBrush(Qt::white);

    setCentralWidget(graphicsView);

    _connMsg = new QLabel;
    statusBar()->setSizeGripEnabled(false);
    statusBar()->addPermanentWidget(_connMsg);
    statusBar()->show();

    setupDebug();
    setupMenus();

    QMetaObject::connectSlotsByName(this);

    _debugDock->setVisible(_showTextArea);
    setWinTitle("CS106 graphics server");
    setWinSize(450, 250);
} // setupUi

void gWin::setupDebug()
{
    _debugDock = new QDockWidget;
    _debugDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    _debugDock->setWindowTitle("Messages received");
    _debugDock->setFeatures(QDockWidget::DockWidgetFloatable
                            | QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea, _debugDock);

    textEdit = new QTextEdit;
    _debugDock->setWidget(textEdit);
    _debugDock->setFixedWidth(250);

    connect(_debugDock, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)),
            this, SLOT(fixWinSize()));
    connect(_debugDock, SIGNAL(visibilityChanged(bool)),
            this, SLOT(fixWinSize()));
    connect(_debugDock, SIGNAL(topLevelChanged(bool)),
            this, SLOT(fixWinSize()));
}

void gWin::setupMenus()
{
    savePicAct = new QAction("Save &Picture...", this);
    connect(savePicAct, SIGNAL(triggered()), this, SLOT(savePicture()));
    saveLogAct = new QAction("Save &Log...", this);
    connect(saveLogAct, SIGNAL(triggered()), this, SLOT(saveLog()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    copyPicAct = new QAction("Copy &Image to Clipboard", this);
    connect(copyPicAct, SIGNAL(triggered()), this, SLOT(copyPic()));

    helpAboutAct = new QAction("&About CS106 Graphics...", this);
    connect(helpAboutAct, SIGNAL(triggered()), this, SLOT(helpAbout()));
    aboutQtAct = new QAction("About &Qt...", this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    debugGroup = new QActionGroup(this);
    showDebugAct = new QAction("&Show debug log", debugGroup);
    connect(showDebugAct, SIGNAL(triggered()), this, SLOT(showDebug()));
    hideDebugAct = new QAction("&Hide debug log", debugGroup);
    connect(hideDebugAct, SIGNAL(triggered()), this, SLOT(hideDebug()));

    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(savePicAct);
    fileMenu->addAction(saveLogAct);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(copyPicAct);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(helpAboutAct);
    helpMenu->addAction(aboutQtAct);
    helpMenu->addAction(showDebugAct);
    helpMenu->addAction(hideDebugAct);
    if (_showTextArea) showDebugAct->setEnabled(false);
    else hideDebugAct->setEnabled(false);
} // setupMenus


void gWin::appendText(QString s)
{
    if (_showTextArea)  // in debugging mode
        textEdit->append(s);
    // else do nothing
}

void gWin::savePicture()
{
    QImage img(graphicsScene->width(),
               graphicsScene->height(),
               QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    graphicsScene->render(&p);
    p.end();
    QString fileName = QFileDialog::getSaveFileName(this, "Save As PNG graphic", ".", "*.png");
    if (fileName.isEmpty()) {
        statusBar()->showMessage("Nothing saved!");
        return;
    }
    img.save(fileName);
    statusBar()->showMessage("File " + fileName + " saved");
}

void gWin::saveLog()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Log As Textfile");
    if (fileName.isEmpty()) {
        statusBar()->showMessage("Nothing saved!");
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    statusBar()->showMessage("File " + fileName + " saved");
}

void gWin::copyPic()
{
    QImage img(graphicsScene->width(),
               graphicsScene->height(),
               QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    graphicsScene->render(&p);
    p.end();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setImage(img);
}

void gWin::helpAbout()
{
    QString msg = "<h2>" + QString(VERSION) + "</h2>";
    msg += "<p>An open-source implementation of the libraries for";
    msg += "<br />Stanford's course 'Programming Abstractions', CS106B :<br />";
    msg += "<a href='http://see.stanford.edu/see/courses.aspx'>";
    msg += "http://see.stanford.edu/see/courses.aspx</a></p>";
    msg += "<p>Created by Colin Leach</p>";
    msg += "<p>For downloads and more details see:<br />";
    msg += "<a href='http://sourceforge.net/projects/progabstrlib/'>";
    msg += "http://sourceforge.net/projects/progabstrlib/</a></p>";
    msg += "<p>This is free software and is distributed under GNU GPL.<br />";
    msg += "It is provided as is and without warranty of any kind.</p>";

    QMessageBox::about(this, tr("CS106 Graphics"), msg);
    QMessageBox aboutDlg(QMessageBox::NoIcon, "About CS106 Graphics Server",
                         msg, QMessageBox::Ok, this, Qt::Window);

/* Alternative implementation, if you want to get fancy */

//    QDialog *aboutDlg = new QDialog(this, Qt::Dialog);
//    aboutDlg->resize(400, 300);
//    aboutDlg->setWindowTitle("About CS106 Graphics Server");
//    QVBoxLayout *vLayout = new QVBoxLayout(aboutDlg);
//    QLabel *lbl = new QLabel(aboutDlg);
//    lbl->setTextFormat(Qt::RichText);
//    lbl->setText(msg);
//    lbl->setAlignment(Qt::AlignCenter);
//    lbl->setOpenExternalLinks(true);
//    vLayout->addWidget(lbl);
//    QFrame *line = new QFrame(aboutDlg);
//    line->setFrameShape(QFrame::HLine);
//    line->setFrameShadow(QFrame::Sunken);
//    vLayout->addWidget(line);;
//    QDialogButtonBox *btnBox = new QDialogButtonBox(aboutDlg);
//    btnBox->addButton(QDialogButtonBox::Ok);
//    connect(btnBox, SIGNAL(accepted()), aboutDlg, SLOT(accept()));
//    vLayout->addWidget(btnBox);
//    aboutDlg->exec();
}

void gWin::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void gWin::showDebug()
{
    toggleDebug(true);
    showDebugAct->setEnabled(false);
    hideDebugAct->setEnabled(true);
}

void gWin::hideDebug()
{
    toggleDebug(false);
    showDebugAct->setEnabled(true);
    hideDebugAct->setEnabled(false);
}

void gWin::toggleDebug(bool on)
{
    _showTextArea = on;
    _debugDock->setVisible(on);
    this->update();
}

/******************************************************************************
 * Some public functions, needed by cs106graphics.cpp
 */

void gWin::setWinTitle(QString title)
{
    this->setWindowTitle(title);
    this->repaint();
}

QString gWin::getWinTitle()
{
    return this->windowTitle();
}

void gWin::setWinSize(int w, int h)
{
    const int HPAD = 20, VPAD=10; // very empirical borders!!!
    int fullWidth = w + HPAD;
    int fullHeight = h + menuBar()->height() + statusBar()->height() + VPAD;
    if (_showTextArea && ! _debugDock->isFloating() )
        fullWidth += _debugDock->width();
    this->resize(fullWidth, fullHeight);
    this->update();
}

void gWin::fixWinSize()
{
    setWinSize(graphicsHandler->width(), graphicsHandler->height());
}

QString gWin::getWinSize(bool needsConversion, double resolution)
{
    QTextStream ss;
    if (needsConversion)
        ss << (this->width() / resolution)  << (this->height() / resolution);
    else
        ss << this->width() << this->height();
    return ss.readAll();
}

void gWin::updateWin(){
    this->update();
}
