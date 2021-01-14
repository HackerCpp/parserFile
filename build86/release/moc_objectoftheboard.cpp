/****************************************************************************
** Meta object code from reading C++ file 'objectoftheboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphics_lib/inc/objectoftheboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectoftheboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ObjectOfTheBoard_t {
    QByteArrayData data[5];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjectOfTheBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjectOfTheBoard_t qt_meta_stringdata_ObjectOfTheBoard = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ObjectOfTheBoard"
QT_MOC_LITERAL(1, 17, 25), // "changingTheVisibilityZone"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "newVisibilityZone"
QT_MOC_LITERAL(4, 62, 12) // "needToRedraw"

    },
    "ObjectOfTheBoard\0changingTheVisibilityZone\0"
    "\0newVisibilityZone\0needToRedraw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectOfTheBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QRectF,    3,
    QMetaType::Void,

       0        // eod
};

void ObjectOfTheBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObjectOfTheBoard *_t = static_cast<ObjectOfTheBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changingTheVisibilityZone((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->needToRedraw(); break;
        default: ;
        }
    }
}

const QMetaObject ObjectOfTheBoard::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ObjectOfTheBoard.data,
      qt_meta_data_ObjectOfTheBoard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ObjectOfTheBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectOfTheBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectOfTheBoard.stringdata0))
        return static_cast<void*>(const_cast< ObjectOfTheBoard*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< ObjectOfTheBoard*>(this));
    return QThread::qt_metacast(_clname);
}

int ObjectOfTheBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
