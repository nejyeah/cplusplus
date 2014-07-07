/*
 * File: gwin.cpp
 * Last modified September 2011 by Colin
 * -------------------------------------------------------
 * Interface definition for the gWin object
 */

#ifndef gWin_H
#define gWin_H

#include <QDialog>
#include <QtCore/QVariant>
#include <QtGui/QMainWindow>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include "cs106graphics.h"

#define VERSION "CS106 Graphics Server version 0.3.1"

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
class QTcpSocket;
class GraphicsHandler;
QT_END_NAMESPACE

class gWin : public QMainWindow
{
    Q_OBJECT

public:
    gWin(int port, QString host, bool showTextArea, QWidget *parent = 0);
    ~gWin();
    void setWinTitle(QString title);
    QString getWinTitle();
    void setWinSize(int w, int h);
    QString getWinSize(bool needsConversion, double resolution);
    void updateWin();

private slots:
    void sessionOpened();
    void newConn();
    void exchangeMsgs();
    void appendText(QString s);
    void fixWinSize();

    // menuBar methods
    void savePicture();
    void saveLog();
    void copyPic();
    void helpAbout();
    void aboutQt();
    void showDebug();
    void hideDebug();

private:
    void setupUi();
    void setupDebug();
    void setupMenus();
    void toggleDebug(bool on);

    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QTextEdit *textEdit;
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    GraphicsHandler *graphicsHandler;
    QStatusBar *statBar;
    int _port;
    QString _host;
    bool _showTextArea;
    QDockWidget *_debugDock;
    QLabel *_connMsg;
//    QDialog *aboutDlg;

    // menuBar items
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *savePicAct;
    QAction *saveLogAct;
    QAction *exitAct;
    QAction *copyPicAct;
    QAction *helpAboutAct;
    QAction *aboutQtAct;
    QActionGroup *debugGroup;
    QAction *showDebugAct;
    QAction *hideDebugAct;
};

#endif // gWin_H
