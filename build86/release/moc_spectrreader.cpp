/****************************************************************************
** Meta object code from reading C++ file 'spectrreader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphics_lib/inc/spectrReader/spectrreader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spectrreader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SpectrReader_t {
    QByteArrayData data[14];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpectrReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpectrReader_t qt_meta_stringdata_SpectrReader = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SpectrReader"
QT_MOC_LITERAL(1, 13, 17), // "sliderWidthChange"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "width"
QT_MOC_LITERAL(4, 38, 12), // "insertFilter"
QT_MOC_LITERAL(5, 51, 15), // "rollBackFilters"
QT_MOC_LITERAL(6, 67, 15), // "applyAllFilters"
QT_MOC_LITERAL(7, 83, 5), // "apply"
QT_MOC_LITERAL(8, 89, 19), // "updateOneWaweWidget"
QT_MOC_LITERAL(9, 109, 10), // "scenePoint"
QT_MOC_LITERAL(10, 120, 9), // "allUpdate"
QT_MOC_LITERAL(11, 130, 25), // "changeBordersOfTheFilters"
QT_MOC_LITERAL(12, 156, 7), // "leftTop"
QT_MOC_LITERAL(13, 164, 9) // "rightDown"

    },
    "SpectrReader\0sliderWidthChange\0\0width\0"
    "insertFilter\0rollBackFilters\0"
    "applyAllFilters\0apply\0updateOneWaweWidget\0"
    "scenePoint\0allUpdate\0changeBordersOfTheFilters\0"
    "leftTop\0rightDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpectrReader[] = {

 // content:
       7,       // revision
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
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    2,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,   12,   13,

       0        // eod
};

void SpectrReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpectrReader *_t = static_cast<SpectrReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sliderWidthChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->insertFilter(); break;
        case 2: _t->rollBackFilters(); break;
        case 3: _t->applyAllFilters(); break;
        case 4: _t->apply(); break;
        case 5: _t->updateOneWaweWidget((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 6: _t->allUpdate(); break;
        case 7: _t->changeBordersOfTheFilters((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SpectrReader::staticMetaObject = {
    { &BaseCurveReader::staticMetaObject, qt_meta_stringdata_SpectrReader.data,
      qt_meta_data_SpectrReader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpectrReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpectrReader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpectrReader.stringdata0))
        return static_cast<void*>(const_cast< SpectrReader*>(this));
    return BaseCurveReader::qt_metacast(_clname);
}

int SpectrReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseCurveReader::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
