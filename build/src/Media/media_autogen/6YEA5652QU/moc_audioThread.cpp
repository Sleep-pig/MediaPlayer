/****************************************************************************
** Meta object code from reading C++ file 'audioThread.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/Media/include/audioThread.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioThread.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioThread_t {
    QByteArrayData data[18];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioThread_t qt_meta_stringdata_AudioThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioThread"
QT_MOC_LITERAL(1, 12, 13), // "audioDataUsed"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "audioClockChanged"
QT_MOC_LITERAL(4, 45, 11), // "pts_seconds"
QT_MOC_LITERAL(5, 57, 17), // "onInitAudioOutput"
QT_MOC_LITERAL(6, 75, 10), // "samplerate"
QT_MOC_LITERAL(7, 86, 8), // "channels"
QT_MOC_LITERAL(8, 95, 15), // "recvAudioPacket"
QT_MOC_LITERAL(9, 111, 9), // "AVPacket*"
QT_MOC_LITERAL(10, 121, 3), // "pkt"
QT_MOC_LITERAL(11, 125, 15), // "recvAudioBuffer"
QT_MOC_LITERAL(12, 141, 8), // "uint8_t*"
QT_MOC_LITERAL(13, 150, 4), // "data"
QT_MOC_LITERAL(14, 155, 4), // "size"
QT_MOC_LITERAL(15, 160, 3), // "pts"
QT_MOC_LITERAL(16, 164, 15), // "onGetAudioClock"
QT_MOC_LITERAL(17, 180, 7) // "double&"

    },
    "AudioThread\0audioDataUsed\0\0audioClockChanged\0"
    "pts_seconds\0onInitAudioOutput\0samplerate\0"
    "channels\0recvAudioPacket\0AVPacket*\0"
    "pkt\0recvAudioBuffer\0uint8_t*\0data\0"
    "size\0pts\0onGetAudioClock\0double&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   48,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
      11,    3,   56,    2, 0x0a /* Public */,
      16,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int, QMetaType::Double,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   15,

       0        // eod
};

void AudioThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->audioDataUsed(); break;
        case 1: _t->audioClockChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onInitAudioOutput((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->recvAudioPacket((*reinterpret_cast< AVPacket*(*)>(_a[1]))); break;
        case 4: _t->recvAudioBuffer((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->onGetAudioClock((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::audioDataUsed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AudioThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioThread::audioClockChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AudioThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AudioThread.data,
    qt_meta_data_AudioThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AudioThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AudioThread::audioDataUsed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AudioThread::audioClockChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
