/****************************************************************************
** Meta object code from reading C++ file 'decode.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/Media/include/decode.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decode.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Decode_t {
    QByteArrayData data[14];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Decode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Decode_t qt_meta_stringdata_Decode = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Decode"
QT_MOC_LITERAL(1, 7, 9), // "startPlay"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "playOver"
QT_MOC_LITERAL(4, 27, 15), // "initAudioOutput"
QT_MOC_LITERAL(5, 43, 15), // "initVideoOutput"
QT_MOC_LITERAL(6, 59, 15), // "sendAudioPacket"
QT_MOC_LITERAL(7, 75, 9), // "AVPacket*"
QT_MOC_LITERAL(8, 85, 3), // "pkt"
QT_MOC_LITERAL(9, 89, 15), // "sendVideoPacket"
QT_MOC_LITERAL(10, 105, 11), // "setCurFrame"
QT_MOC_LITERAL(11, 117, 7), // "int64_t"
QT_MOC_LITERAL(12, 125, 9), // "_curFrame"
QT_MOC_LITERAL(13, 135, 12) // "decodePacket"

    },
    "Decode\0startPlay\0\0playOver\0initAudioOutput\0"
    "initVideoOutput\0sendAudioPacket\0"
    "AVPacket*\0pkt\0sendVideoPacket\0setCurFrame\0"
    "int64_t\0_curFrame\0decodePacket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Decode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    1,   58,    2, 0x06 /* Public */,
       9,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   64,    2, 0x0a /* Public */,
      13,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void Decode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Decode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startPlay(); break;
        case 1: _t->playOver(); break;
        case 2: _t->initAudioOutput(); break;
        case 3: _t->initVideoOutput(); break;
        case 4: _t->sendAudioPacket((*reinterpret_cast< AVPacket*(*)>(_a[1]))); break;
        case 5: _t->sendVideoPacket((*reinterpret_cast< AVPacket*(*)>(_a[1]))); break;
        case 6: _t->setCurFrame((*reinterpret_cast< int64_t(*)>(_a[1]))); break;
        case 7: _t->decodePacket(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Decode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::startPlay)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Decode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::playOver)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Decode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::initAudioOutput)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Decode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::initVideoOutput)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Decode::*)(AVPacket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::sendAudioPacket)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Decode::*)(AVPacket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Decode::sendVideoPacket)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Decode::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Decode.data,
    qt_meta_data_Decode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Decode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Decode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Decode.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Decode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Decode::startPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Decode::playOver()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Decode::initAudioOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Decode::initVideoOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Decode::sendAudioPacket(AVPacket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Decode::sendVideoPacket(AVPacket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
