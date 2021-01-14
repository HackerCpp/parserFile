/****************************************************************************
** Meta object code from reading C++ file 'projectpathnamewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projectpathnamewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectpathnamewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProjectPathNameWidget_t {
    QByteArrayData data[12];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectPathNameWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectPathNameWidget_t qt_meta_stringdata_ProjectPathNameWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ProjectPathNameWidget"
QT_MOC_LITERAL(1, 22, 10), // "changeName"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "name"
QT_MOC_LITERAL(4, 39, 10), // "changePath"
QT_MOC_LITERAL(5, 50, 4), // "path"
QT_MOC_LITERAL(6, 55, 5), // "apply"
QT_MOC_LITERAL(7, 61, 6), // "cancel"
QT_MOC_LITERAL(8, 68, 7), // "openDir"
QT_MOC_LITERAL(9, 76, 10), // "closeEvent"
QT_MOC_LITERAL(10, 87, 12), // "QCloseEvent*"
QT_MOC_LITERAL(11, 100, 5) // "event"

    },
    "ProjectPathNameWidget\0changeName\0\0"
    "name\0changePath\0path\0apply\0cancel\0"
    "openDir\0closeEvent\0QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectPathNameWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void ProjectPathNameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProjectPathNameWidget *_t = static_cast<ProjectPathNameWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->apply(); break;
        case 3: _t->cancel(); break;
        case 4: _t->openDir(); break;
        case 5: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ProjectPathNameWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProjectPathNameWidget.data,
      qt_meta_data_ProjectPathNameWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProjectPathNameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectPathNameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectPathNameWidget.stringdata0))
        return static_cast<void*>(const_cast< ProjectPathNameWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProjectPathNameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
