/****************************************************************************
** Meta object code from reading C++ file 'tab38k.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../parserFile/inc/tabs/tab38k.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab38k.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tab38k_t {
    QByteArrayData data[12];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tab38k_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tab38k_t qt_meta_stringdata_Tab38k = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Tab38k"
QT_MOC_LITERAL(1, 7, 8), // "showText"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 29, 5), // "index"
QT_MOC_LITERAL(5, 35, 9), // "setFilter"
QT_MOC_LITERAL(6, 45, 10), // "setSorting"
QT_MOC_LITERAL(7, 56, 5), // "value"
QT_MOC_LITERAL(8, 62, 14), // "addModulesData"
QT_MOC_LITERAL(9, 77, 20), // "PacketModulesData38k"
QT_MOC_LITERAL(10, 98, 4), // "pack"
QT_MOC_LITERAL(11, 103, 11) // "allUploaded"

    },
    "Tab38k\0showText\0\0QModelIndex\0index\0"
    "setFilter\0setSorting\0value\0addModulesData\0"
    "PacketModulesData38k\0pack\0allUploaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tab38k[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,
       8,    1,   46,    2, 0x0a /* Public */,
      11,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,

       0        // eod
};

void Tab38k::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tab38k *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showText((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->setFilter(); break;
        case 2: _t->setSorting((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addModulesData((*reinterpret_cast< PacketModulesData38k(*)>(_a[1]))); break;
        case 4: _t->allUploaded(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tab38k::staticMetaObject = { {
    &AbstractTab::staticMetaObject,
    qt_meta_stringdata_Tab38k.data,
    qt_meta_data_Tab38k,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tab38k::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tab38k::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tab38k.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AbstractTabSaveFiles"))
        return static_cast< AbstractTabSaveFiles*>(this);
    return AbstractTab::qt_metacast(_clname);
}

int Tab38k::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
