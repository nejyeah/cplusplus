/****************************************************************************
** Meta object code from reading C++ file 'gwin.h'
**
** Created: Fri Apr 11 12:19:21 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      22,    5,    5,    5, 0x08,
      32,    5,    5,    5, 0x08,
      49,   47,    5,    5, 0x08,
      69,    5,    5,    5, 0x08,
      82,    5,    5,    5, 0x08,
      96,    5,    5,    5, 0x08,
     106,    5,    5,    5, 0x08,
     116,    5,    5,    5, 0x08,
     128,    5,    5,    5, 0x08,
     138,    5,    5,    5, 0x08,
     150,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gWin[] = {
    "gWin\0\0sessionOpened()\0newConn()\0"
    "exchangeMsgs()\0s\0appendText(QString)\0"
    "fixWinSize()\0savePicture()\0saveLog()\0"
    "copyPic()\0helpAbout()\0aboutQt()\0"
    "showDebug()\0hideDebug()\0"
};

void gWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        gWin *_t = static_cast<gWin *>(_o);
        switch (_id) {
        case 0: _t->sessionOpened(); break;
        case 1: _t->newConn(); break;
        case 2: _t->exchangeMsgs(); break;
        case 3: _t->appendText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->fixWinSize(); break;
        case 5: _t->savePicture(); break;
        case 6: _t->saveLog(); break;
        case 7: _t->copyPic(); break;
        case 8: _t->helpAbout(); break;
        case 9: _t->aboutQt(); break;
        case 10: _t->showDebug(); break;
        case 11: _t->hideDebug(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData gWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject gWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gWin,
      qt_meta_data_gWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gWin))
        return static_cast<void*>(const_cast< gWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int gWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
