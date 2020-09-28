/****************************************************************************
** Meta object code from reading C++ file 'agraphictrack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../graphics_lib/inc/agraphictrack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agraphictrack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AGraphicTrack_t {
    QByteArrayData data[8];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGraphicTrack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGraphicTrack_t qt_meta_stringdata_AGraphicTrack = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AGraphicTrack"
QT_MOC_LITERAL(1, 14, 21), // "changedPositionBorder"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "position"
QT_MOC_LITERAL(4, 46, 11), // "changeBegin"
QT_MOC_LITERAL(5, 58, 8), // "newBegin"
QT_MOC_LITERAL(6, 67, 11), // "sceneUpdate"
QT_MOC_LITERAL(7, 79, 14) // "timerLeftClick"

    },
    "AGraphicTrack\0changedPositionBorder\0"
    "\0position\0changeBegin\0newBegin\0"
    "sceneUpdate\0timerLeftClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGraphicTrack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       6,    0,   40,    2, 0x0a /* Public */,
       7,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AGraphicTrack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AGraphicTrack *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedPositionBorder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeBegin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sceneUpdate(); break;
        case 3: _t->timerLeftClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AGraphicTrack::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AGraphicTrack::changedPositionBorder)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AGraphicTrack::staticMetaObject = { {
    QMetaObject::SuperData::link<ObjectOfTheBoard::staticMetaObject>(),
    qt_meta_stringdata_AGraphicTrack.data,
    qt_meta_data_AGraphicTrack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AGraphicTrack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGraphicTrack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AGraphicTrack.stringdata0))
        return static_cast<void*>(this);
    return ObjectOfTheBoard::qt_metacast(_clname);
}

int AGraphicTrack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectOfTheBoard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AGraphicTrack::changedPositionBorder(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
