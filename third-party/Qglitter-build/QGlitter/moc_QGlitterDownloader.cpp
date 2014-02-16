/****************************************************************************
** Meta object code from reading C++ file 'QGlitterDownloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qglitter/QGlitter/QGlitterDownloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGlitterDownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QGlitterDownloader_t {
    QByteArrayData data[18];
    char stringdata[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QGlitterDownloader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QGlitterDownloader_t qt_meta_stringdata_QGlitterDownloader = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 16),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 9),
QT_MOC_LITERAL(4, 47, 10),
QT_MOC_LITERAL(5, 58, 16),
QT_MOC_LITERAL(6, 75, 13),
QT_MOC_LITERAL(7, 89, 10),
QT_MOC_LITERAL(8, 100, 14),
QT_MOC_LITERAL(9, 115, 3),
QT_MOC_LITERAL(10, 119, 9),
QT_MOC_LITERAL(11, 129, 14),
QT_MOC_LITERAL(12, 144, 5),
QT_MOC_LITERAL(13, 150, 27),
QT_MOC_LITERAL(14, 178, 4),
QT_MOC_LITERAL(15, 183, 8),
QT_MOC_LITERAL(16, 192, 8),
QT_MOC_LITERAL(17, 201, 9)
    },
    "QGlitterDownloader\0downloadFinished\0"
    "\0errorCode\0pathToFile\0downloadProgress\0"
    "bytesReceived\0bytesTotal\0downloadUpdate\0"
    "url\0signature\0cancelDownload\0error\0"
    "QNetworkReply::NetworkError\0code\0"
    "finished\0progress\0readyRead\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGlitterDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06,
       5,    2,   59,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    2,   64,    2, 0x0a,
      11,    0,   69,    2, 0x0a,
      12,    1,   70,    2, 0x08,
      15,    0,   73,    2, 0x08,
      16,    2,   74,    2, 0x08,
      17,    0,   79,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    7,
    QMetaType::Void,

       0        // eod
};

void QGlitterDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGlitterDownloader *_t = static_cast<QGlitterDownloader *>(_o);
        switch (_id) {
        case 0: _t->downloadFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->downloadUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->cancelDownload(); break;
        case 4: _t->error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 5: _t->finished(); break;
        case 6: _t->progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->readyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QGlitterDownloader::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterDownloader::downloadFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (QGlitterDownloader::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGlitterDownloader::downloadProgress)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QGlitterDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGlitterDownloader.data,
      qt_meta_data_QGlitterDownloader,  qt_static_metacall, 0, 0}
};


const QMetaObject *QGlitterDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGlitterDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGlitterDownloader.stringdata))
        return static_cast<void*>(const_cast< QGlitterDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int QGlitterDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QGlitterDownloader::downloadFinished(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGlitterDownloader::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
