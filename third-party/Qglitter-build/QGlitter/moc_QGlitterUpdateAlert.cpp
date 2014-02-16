/****************************************************************************
** Meta object code from reading C++ file 'QGlitterUpdateAlert.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qglitter/QGlitter/QGlitterUpdateAlert.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGlitterUpdateAlert.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QGlitterUpdateAlert_t {
    QByteArrayData data[7];
    char stringdata[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QGlitterUpdateAlert_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QGlitterUpdateAlert_t qt_meta_stringdata_QGlitterUpdateAlert = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 17),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 24),
QT_MOC_LITERAL(4, 64, 16),
QT_MOC_LITERAL(5, 81, 9),
QT_MOC_LITERAL(6, 91, 10)
    },
    "QGlitterUpdateAlert\0toggleSkipVersion\0"
    "\0toggleAutomaticDownloads\0downloadFinished\0"
    "errorCode\0pathToFile\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGlitterUpdateAlert[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08,
       3,    0,   30,    2, 0x08,
       4,    2,   31,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,

       0        // eod
};

void QGlitterUpdateAlert::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGlitterUpdateAlert *_t = static_cast<QGlitterUpdateAlert *>(_o);
        switch (_id) {
        case 0: _t->toggleSkipVersion(); break;
        case 1: _t->toggleAutomaticDownloads(); break;
        case 2: _t->downloadFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject QGlitterUpdateAlert::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QGlitterUpdateAlert.data,
      qt_meta_data_QGlitterUpdateAlert,  qt_static_metacall, 0, 0}
};


const QMetaObject *QGlitterUpdateAlert::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGlitterUpdateAlert::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGlitterUpdateAlert.stringdata))
        return static_cast<void*>(const_cast< QGlitterUpdateAlert*>(this));
    return QDialog::qt_metacast(_clname);
}

int QGlitterUpdateAlert::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
