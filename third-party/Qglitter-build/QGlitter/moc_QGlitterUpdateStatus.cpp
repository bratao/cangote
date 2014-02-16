/****************************************************************************
** Meta object code from reading C++ file 'QGlitterUpdateStatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qglitter/QGlitter/QGlitterUpdateStatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGlitterUpdateStatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QGlitterUpdateStatus_t {
    QByteArrayData data[9];
    char stringdata[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QGlitterUpdateStatus_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QGlitterUpdateStatus_t qt_meta_stringdata_QGlitterUpdateStatus = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 16),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 9),
QT_MOC_LITERAL(4, 49, 10),
QT_MOC_LITERAL(5, 60, 16),
QT_MOC_LITERAL(6, 77, 13),
QT_MOC_LITERAL(7, 91, 10),
QT_MOC_LITERAL(8, 102, 13)
    },
    "QGlitterUpdateStatus\0downloadFinished\0"
    "\0errorCode\0pathToFile\0downloadProgress\0"
    "bytesReceived\0bytesTotal\0buttonPressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGlitterUpdateStatus[] = {

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
       1,    2,   29,    2, 0x0a,
       5,    2,   34,    2, 0x0a,
       8,    0,   39,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    7,
    QMetaType::Void,

       0        // eod
};

void QGlitterUpdateStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGlitterUpdateStatus *_t = static_cast<QGlitterUpdateStatus *>(_o);
        switch (_id) {
        case 0: _t->downloadFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->buttonPressed(); break;
        default: ;
        }
    }
}

const QMetaObject QGlitterUpdateStatus::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QGlitterUpdateStatus.data,
      qt_meta_data_QGlitterUpdateStatus,  qt_static_metacall, 0, 0}
};


const QMetaObject *QGlitterUpdateStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGlitterUpdateStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGlitterUpdateStatus.stringdata))
        return static_cast<void*>(const_cast< QGlitterUpdateStatus*>(this));
    return QDialog::qt_metacast(_clname);
}

int QGlitterUpdateStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
