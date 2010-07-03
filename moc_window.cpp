/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created: Sat Jul 3 05:12:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_window[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      23,    7,    7,    7, 0x0a,
      66,   37,    7,    7, 0x0a,
     100,   90,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_window[] = {
    "window\0\0startClicked()\0stopClicked()\0"
    "currentProgress,currentPrice\0"
    "updateProgress(int,int)\0aprox,bee\0"
    "updateResults(double,double)\0"
};

const QMetaObject window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_window,
      qt_meta_data_window, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_window))
        return static_cast<void*>(const_cast< window*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startClicked(); break;
        case 1: stopClicked(); break;
        case 2: updateProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: updateResults((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
