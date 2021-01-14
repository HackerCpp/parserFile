/****************************************************************************
** Meta object code from reading C++ file 'updatewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updatewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updatewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UpdateWindow_t {
    QByteArrayData data[7];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpdateWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpdateWindow_t qt_meta_stringdata_UpdateWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UpdateWindow"
QT_MOC_LITERAL(1, 13, 28), // "processingFileAfterUploading"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 8), // "fileName"
QT_MOC_LITERAL(4, 52, 22), // "processingErrorLoading"
QT_MOC_LITERAL(5, 75, 5), // "error"
QT_MOC_LITERAL(6, 81, 11) // "updateStart"

    },
    "UpdateWindow\0processingFileAfterUploading\0"
    "\0fileName\0processingErrorLoading\0error\0"
    "updateStart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpdateWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void UpdateWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpdateWindow *_t = static_cast<UpdateWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processingFileAfterUploading((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->processingErrorLoading((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateStart(); break;
        default: ;
        }
    }
}

const QMetaObject UpdateWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UpdateWindow.data,
      qt_meta_data_UpdateWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UpdateWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpdateWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateWindow.stringdata0))
        return static_cast<void*>(const_cast< UpdateWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int UpdateWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
