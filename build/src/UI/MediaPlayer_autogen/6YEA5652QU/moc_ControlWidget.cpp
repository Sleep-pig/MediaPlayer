/****************************************************************************
** Meta object code from reading C++ file 'ControlWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/UI/include/ControlWidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlWidget_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlWidget_t qt_meta_stringdata_ControlWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ControlWidget"
QT_MOC_LITERAL(1, 14, 9), // "startPlay"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "leftClicked"
QT_MOC_LITERAL(4, 37, 12), // "rightClicked"
QT_MOC_LITERAL(5, 50, 17), // "fullScreenRequest"
QT_MOC_LITERAL(6, 68, 19), // "onAudioClockChanged"
QT_MOC_LITERAL(7, 88, 11), // "pts_seconds"
QT_MOC_LITERAL(8, 100, 11), // "onslectPlay"
QT_MOC_LITERAL(9, 112, 9), // "startSeek"
QT_MOC_LITERAL(10, 122, 7), // "endSeek"
QT_MOC_LITERAL(11, 130, 13), // "terminatePlay"
QT_MOC_LITERAL(12, 144, 10) // "onPlayOver"

    },
    "ControlWidget\0startPlay\0\0leftClicked\0"
    "rightClicked\0fullScreenRequest\0"
    "onAudioClockChanged\0pts_seconds\0"
    "onslectPlay\0startSeek\0endSeek\0"
    "terminatePlay\0onPlayOver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   68,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startPlay(); break;
        case 1: _t->leftClicked(); break;
        case 2: _t->rightClicked(); break;
        case 3: _t->fullScreenRequest(); break;
        case 4: _t->onAudioClockChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onslectPlay(); break;
        case 6: _t->startSeek(); break;
        case 7: _t->endSeek(); break;
        case 8: _t->terminatePlay(); break;
        case 9: _t->onPlayOver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWidget::startPlay)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWidget::leftClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWidget::rightClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWidget::fullScreenRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ControlWidget.data,
    qt_meta_data_ControlWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ControlWidget::startPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ControlWidget::leftClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ControlWidget::rightClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ControlWidget::fullScreenRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
