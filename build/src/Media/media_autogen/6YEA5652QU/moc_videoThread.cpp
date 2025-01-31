/****************************************************************************
** Meta object code from reading C++ file 'videoThread.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/Media/include/videoThread.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoThread.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoThread_t {
    QByteArrayData data[18];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoThread_t qt_meta_stringdata_VideoThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoThread"
QT_MOC_LITERAL(1, 12, 13), // "videoDataUsed"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "videoQueueStatus"
QT_MOC_LITERAL(4, 44, 6), // "status"
QT_MOC_LITERAL(5, 51, 9), // "SendFrame"
QT_MOC_LITERAL(6, 61, 8), // "uint8_t*"
QT_MOC_LITERAL(7, 70, 9), // "pixelData"
QT_MOC_LITERAL(8, 80, 10), // "pixelWidth"
QT_MOC_LITERAL(9, 91, 11), // "pixelHeight"
QT_MOC_LITERAL(10, 103, 13), // "getAudioClock"
QT_MOC_LITERAL(11, 117, 7), // "double&"
QT_MOC_LITERAL(12, 125, 3), // "pts"
QT_MOC_LITERAL(13, 129, 15), // "recvVideoPacket"
QT_MOC_LITERAL(14, 145, 9), // "AVPacket*"
QT_MOC_LITERAL(15, 155, 3), // "pkt"
QT_MOC_LITERAL(16, 159, 14), // "recvVideoFrame"
QT_MOC_LITERAL(17, 174, 4) // "data"

    },
    "VideoThread\0videoDataUsed\0\0videoQueueStatus\0"
    "status\0SendFrame\0uint8_t*\0pixelData\0"
    "pixelWidth\0pixelHeight\0getAudioClock\0"
    "double&\0pts\0recvVideoPacket\0AVPacket*\0"
    "pkt\0recvVideoFrame\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    3,   48,    2, 0x06 /* Public */,
      10,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   58,    2, 0x0a /* Public */,
      16,    4,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int, QMetaType::Double,   17,    8,    9,   12,

       0        // eod
};

void VideoThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->videoDataUsed(); break;
        case 1: _t->videoQueueStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SendFrame((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->getAudioClock((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->recvVideoPacket((*reinterpret_cast< AVPacket*(*)>(_a[1]))); break;
        case 5: _t->recvVideoFrame((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::videoDataUsed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::videoQueueStatus)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VideoThread::*)(uint8_t * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::SendFrame)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VideoThread::*)(double & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::getAudioClock)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VideoThread.data,
    qt_meta_data_VideoThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VideoThread::videoDataUsed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoThread::videoQueueStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoThread::SendFrame(uint8_t * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VideoThread::getAudioClock(double & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
