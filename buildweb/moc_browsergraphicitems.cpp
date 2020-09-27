/****************************************************************************
** Meta object code from reading C++ file 'browsergraphicitems.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../graphics_lib/inc/tools/browsergraphicitems.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browsergraphicitems.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BrowserGraphicItems_t {
    QByteArrayData data[19];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BrowserGraphicItems_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BrowserGraphicItems_t qt_meta_stringdata_BrowserGraphicItems = {
    {
QT_MOC_LITERAL(0, 0, 19), // "BrowserGraphicItems"
QT_MOC_LITERAL(1, 20, 11), // "changeColor"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "color"
QT_MOC_LITERAL(4, 39, 10), // "changeDate"
QT_MOC_LITERAL(5, 50, 4), // "date"
QT_MOC_LITERAL(6, 55, 12), // "changeDevice"
QT_MOC_LITERAL(7, 68, 6), // "device"
QT_MOC_LITERAL(8, 75, 11), // "changeTrack"
QT_MOC_LITERAL(9, 87, 5), // "track"
QT_MOC_LITERAL(10, 93, 14), // "changeDrawType"
QT_MOC_LITERAL(11, 108, 8), // "drawType"
QT_MOC_LITERAL(12, 117, 11), // "filterApply"
QT_MOC_LITERAL(13, 129, 6), // "column"
QT_MOC_LITERAL(14, 136, 4), // "text"
QT_MOC_LITERAL(15, 141, 14), // "changeMnemonic"
QT_MOC_LITERAL(16, 156, 8), // "mnemonic"
QT_MOC_LITERAL(17, 165, 9), // "setVisibl"
QT_MOC_LITERAL(18, 175, 9) // "isVisible"

    },
    "BrowserGraphicItems\0changeColor\0\0color\0"
    "changeDate\0date\0changeDevice\0device\0"
    "changeTrack\0track\0changeDrawType\0"
    "drawType\0filterApply\0column\0text\0"
    "changeMnemonic\0mnemonic\0setVisibl\0"
    "isVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BrowserGraphicItems[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      12,    2,   69,    2, 0x0a /* Public */,
      15,    1,   74,    2, 0x0a /* Public */,
      17,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void BrowserGraphicItems::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BrowserGraphicItems *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changeDate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->changeDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changeTrack((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->changeDrawType((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->filterApply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->changeMnemonic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setVisibl((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BrowserGraphicItems::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseSettingsWindow::staticMetaObject>(),
    qt_meta_stringdata_BrowserGraphicItems.data,
    qt_meta_data_BrowserGraphicItems,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BrowserGraphicItems::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BrowserGraphicItems::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BrowserGraphicItems.stringdata0))
        return static_cast<void*>(this);
    return BaseSettingsWindow::qt_metacast(_clname);
}

int BrowserGraphicItems::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseSettingsWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
