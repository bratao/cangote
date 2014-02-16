/****************************************************************************
** Meta object code from reading C++ file 'QGlitterUpdater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qglitter/QGlitter/QGlitterUpdater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGlitterUpdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QGlitterUpdater_t {
    QByteArrayData data[23];
    char stringdata[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QGlitterUpdater_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QGlitterUpdater_t qt_meta_stringdata_QGlitterUpdater = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 19),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 24),
QT_MOC_LITERAL(4, 62, 22),
QT_MOC_LITERAL(5, 85, 15),
QT_MOC_LITERAL(6, 101, 7),
QT_MOC_LITERAL(7, 109, 11),
QT_MOC_LITERAL(8, 121, 19),
QT_MOC_LITERAL(9, 141, 11),
QT_MOC_LITERAL(10, 153, 16),
QT_MOC_LITERAL(11, 170, 18),
QT_MOC_LITERAL(12, 189, 14),
QT_MOC_LITERAL(13, 204, 21),
QT_MOC_LITERAL(14, 226, 11),
QT_MOC_LITERAL(15, 238, 11),
QT_MOC_LITERAL(16, 250, 25),
QT_MOC_LITERAL(17, 276, 9),
QT_MOC_LITERAL(18, 286, 13),
QT_MOC_LITERAL(19, 300, 17),
QT_MOC_LITERAL(20, 318, 14),
QT_MOC_LITERAL(21, 333, 5),
QT_MOC_LITERAL(22, 339, 13)
    },
    "QGlitterUpdater\0errorLoadingAppcast\0"
    "\0finishedInstallingUpdate\0"
    "finishedLoadingAppcast\0QGlitterAppcast\0"
    "appcast\0foundUpdate\0QGlitterAppcastItem\0"
    "appcastItem\0installingUpdate\0"
    "noUpdatesAvailable\0updateCanceled\0"
    "backgroundUpdateCheck\0updateCheck\0"
    "aboutToQuit\0automaticUpdateDownloaded\0"
    "errorCode\0installerPath\0appcastDownloaded\0"
    "QNetworkReply*\0reply\0updateTimeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGlitterUpdater[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06,
       3,    0,   80,    2, 0x06,
       4,    1,   81,    2, 0x06,
       7,    1,   84,    2, 0x06,
      10,    0,   87,    2, 0x06,
      11,    0,   88,    2, 0x06,
      12,    0,   89,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      13,    0,   90,    2, 0x0a,
      14,    0,   91,    2, 0x0a,
      15,    0,   92,    2, 0x08,
      16,    2,   93,    2, 0x08,
      19,    1,   98,    2, 0x08,
      22,    0,  101,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,

       0        // eod
};

void QGlitterUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGlitterUpdater *_t = static_cast<QGlitterUpdater *>(_o);
        switch (_id) {
        case 0: _t->errorLoadingAppcast(); break;
        case 1: _t->finishedInstallingUpdate(); break;
        case 2: _t->finishedLoadingAppcast((*reinterpret_cast< const QGlitterAppcast(*)>(_a[1]))); break;
        case 3: _t->foundUpdate((*reinterpret_cast< const QGlitterAppcastItem(*)>(_a[1]))); break;
        case 4: _t->installingUpdate(); break;
        case 5: _t->noUpdatesAvailable(); break;
        case 6: _t->updateCanceled(); break;
        case 7: _t->backgroundUpdateCheck(); break;
        case 8: _t->updateCheck(); break;
        case 9: _t->aboutToQuit(); break;
        case 10: _t->automaticUpdateDownloaded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->appcastDownloaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: _t->updateTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QGlitterUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::errorLoadingAppcast)) {
                *result = 0;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::finishedInstallingUpdate)) {
                *result = 1;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)(const QGlitterAppcast & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::finishedLoadingAppcast)) {
                *result = 2;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)(const QGlitterAppcastItem & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::foundUpdate)) {
                *result = 3;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::installingUpdate)) {
                *result = 4;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::noUpdatesAvailable)) {
                *result = 5;
            }
        }
        {
            typedef void (QGlitterUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterUpdater::updateCanceled)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject QGlitterUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGlitterUpdater.data,
      qt_meta_data_QGlitterUpdater,  qt_static_metacall, 0, 0}
};


const QMetaObject *QGlitterUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGlitterUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGlitterUpdater.stringdata))
        return static_cast<void*>(const_cast< QGlitterUpdater*>(this));
    if (!strcmp(_clname, "QGlitterObject"))
        return static_cast< QGlitterObject*>(const_cast< QGlitterUpdater*>(this));
    return QObject::qt_metacast(_clname);
}

int QGlitterUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QGlitterUpdater::errorLoadingAppcast()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QGlitterUpdater::finishedInstallingUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QGlitterUpdater::finishedLoadingAppcast(const QGlitterAppcast & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGlitterUpdater::foundUpdate(const QGlitterAppcastItem & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGlitterUpdater::installingUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QGlitterUpdater::noUpdatesAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QGlitterUpdater::updateCanceled()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
