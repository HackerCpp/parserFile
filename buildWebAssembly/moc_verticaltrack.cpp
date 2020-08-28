/****************************************************************************
** Meta object code from reading C++ file 'verticaltrack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../graphics_lib/inc/verticaltrack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'verticaltrack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VerticalTrack_t {
    QByteArrayData data[13];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VerticalTrack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VerticalTrack_t qt_meta_stringdata_VerticalTrack = {
    {
QT_MOC_LITERAL(0, 0, 13), // "VerticalTrack"
QT_MOC_LITERAL(1, 14, 11), // "changeBegin"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "newBegin"
QT_MOC_LITERAL(4, 36, 23), // "openSettingsActiveItems"
QT_MOC_LITERAL(5, 60, 13), // "applySettings"
QT_MOC_LITERAL(6, 74, 15), // "insertLeftTrack"
QT_MOC_LITERAL(7, 90, 16), // "insertRightTrack"
QT_MOC_LITERAL(8, 107, 11), // "deleteTrack"
QT_MOC_LITERAL(9, 119, 17), // "openSettingsTrack"
QT_MOC_LITERAL(10, 137, 16), // "openCurveBrowser"
QT_MOC_LITERAL(11, 154, 21), // "openEditorActiveItems"
QT_MOC_LITERAL(12, 176, 11) // "savePicture"

    },
    "VerticalTrack\0changeBegin\0\0newBegin\0"
    "openSettingsActiveItems\0applySettings\0"
    "insertLeftTrack\0insertRightTrack\0"
    "deleteTrack\0openSettingsTrack\0"
    "openCurveBrowser\0openEditorActiveItems\0"
    "savePicture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VerticalTrack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    0,   67,    2, 0x0a /* Public */,
       5,    0,   68,    2, 0x0a /* Public */,
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VerticalTrack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VerticalTrack *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeBegin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->openSettingsActiveItems(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->insertLeftTrack(); break;
        case 4: _t->insertRightTrack(); break;
        case 5: _t->deleteTrack(); break;
        case 6: _t->openSettingsTrack(); break;
        case 7: _t->openCurveBrowser(); break;
        case 8: _t->openEditorActiveItems(); break;
        case 9: _t->savePicture(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VerticalTrack::staticMetaObject = { {
    QMetaObject::SuperData::link<AGraphicTrack::staticMetaObject>(),
    qt_meta_stringdata_VerticalTrack.data,
    qt_meta_data_VerticalTrack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VerticalTrack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VerticalTrack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VerticalTrack.stringdata0))
        return static_cast<void*>(this);
    return AGraphicTrack::qt_metacast(_clname);
}

int VerticalTrack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AGraphicTrack::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
