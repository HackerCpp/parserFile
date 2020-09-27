/****************************************************************************
** Meta object code from reading C++ file 'windowformenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../geology/inc/windowformenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowformenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowForMenu_t {
    QByteArrayData data[10];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowForMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowForMenu_t qt_meta_stringdata_WindowForMenu = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WindowForMenu"
QT_MOC_LITERAL(1, 14, 8), // "openFile"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "saveGFM"
QT_MOC_LITERAL(4, 32, 7), // "saveLIS"
QT_MOC_LITERAL(5, 40, 17), // "openConsolePython"
QT_MOC_LITERAL(6, 58, 16), // "openEditorPython"
QT_MOC_LITERAL(7, 75, 28), // "insertCalibrationInTheScript"
QT_MOC_LITERAL(8, 104, 19), // "openInterpretations"
QT_MOC_LITERAL(9, 124, 15) // "openConstructor"

    },
    "WindowForMenu\0openFile\0\0saveGFM\0saveLIS\0"
    "openConsolePython\0openEditorPython\0"
    "insertCalibrationInTheScript\0"
    "openInterpretations\0openConstructor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowForMenu[] = {

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
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
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

void WindowForMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowForMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveGFM(); break;
        case 2: _t->saveLIS(); break;
        case 3: _t->openConsolePython(); break;
        case 4: _t->openEditorPython(); break;
        case 5: _t->insertCalibrationInTheScript(); break;
        case 6: _t->openInterpretations(); break;
        case 7: _t->openConstructor(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject WindowForMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WindowForMenu.data,
    qt_meta_data_WindowForMenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowForMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowForMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowForMenu.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WindowForMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
