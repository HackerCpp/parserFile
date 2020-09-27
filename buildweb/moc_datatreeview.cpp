/****************************************************************************
** Meta object code from reading C++ file 'datatreeview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../geology/inc/datatreeview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datatreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataTreeView_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataTreeView_t qt_meta_stringdata_DataTreeView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DataTreeView"
QT_MOC_LITERAL(1, 13, 8), // "newCurve"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "deleteDataBlock"
QT_MOC_LITERAL(4, 39, 7), // "saveGFM"
QT_MOC_LITERAL(5, 47, 17), // "openPythonConsole"
QT_MOC_LITERAL(6, 65, 16), // "openPythonScript"
QT_MOC_LITERAL(7, 82, 16), // "openPythonEditor"
QT_MOC_LITERAL(8, 99, 17) // "makeActiveProject"

    },
    "DataTreeView\0newCurve\0\0deleteDataBlock\0"
    "saveGFM\0openPythonConsole\0openPythonScript\0"
    "openPythonEditor\0makeActiveProject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataTreeView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DataTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataTreeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newCurve(); break;
        case 1: _t->deleteDataBlock(); break;
        case 2: _t->saveGFM(); break;
        case 3: _t->openPythonConsole(); break;
        case 4: _t->openPythonScript(); break;
        case 5: _t->openPythonEditor(); break;
        case 6: _t->makeActiveProject(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DataTreeView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeView::staticMetaObject>(),
    qt_meta_stringdata_DataTreeView.data,
    qt_meta_data_DataTreeView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataTreeView.stringdata0))
        return static_cast<void*>(this);
    return QTreeView::qt_metacast(_clname);
}

int DataTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
