/****************************************************************************
** Meta object code from reading C++ file 'verticalboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphics_lib/inc/verticalboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'verticalboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VerticalBoard_t {
    QByteArrayData data[7];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VerticalBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VerticalBoard_t qt_meta_stringdata_VerticalBoard = {
    {
QT_MOC_LITERAL(0, 0, 13), // "VerticalBoard"
QT_MOC_LITERAL(1, 14, 25), // "changingTheVisibilityZone"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 11), // "visibleArea"
QT_MOC_LITERAL(4, 53, 12), // "needToRedraw"
QT_MOC_LITERAL(5, 66, 13), // "scrollChanged"
QT_MOC_LITERAL(6, 80, 14) // "timerLeftClick"

    },
    "VerticalBoard\0changingTheVisibilityZone\0"
    "\0visibleArea\0needToRedraw\0scrollChanged\0"
    "timerLeftClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VerticalBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRectF,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VerticalBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VerticalBoard *_t = static_cast<VerticalBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changingTheVisibilityZone((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->needToRedraw(); break;
        case 2: _t->scrollChanged(); break;
        case 3: _t->timerLeftClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VerticalBoard::*_t)(QRectF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VerticalBoard::changingTheVisibilityZone)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VerticalBoard::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VerticalBoard::needToRedraw)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject VerticalBoard::staticMetaObject = {
    { &AGraphicBoard::staticMetaObject, qt_meta_stringdata_VerticalBoard.data,
      qt_meta_data_VerticalBoard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VerticalBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VerticalBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VerticalBoard.stringdata0))
        return static_cast<void*>(const_cast< VerticalBoard*>(this));
    return AGraphicBoard::qt_metacast(_clname);
}

int VerticalBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AGraphicBoard::qt_metacall(_c, _id, _a);
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
void VerticalBoard::changingTheVisibilityZone(QRectF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VerticalBoard::needToRedraw()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
