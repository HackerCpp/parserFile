/****************************************************************************
** Meta object code from reading C++ file 'drawsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../graphics_lib/inc/drawsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DrawSettings_t {
    QByteArrayData data[15];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawSettings_t qt_meta_stringdata_DrawSettings = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DrawSettings"
QT_MOC_LITERAL(1, 13, 13), // "setFormatTime"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "FormatTime"
QT_MOC_LITERAL(4, 39, 6), // "format"
QT_MOC_LITERAL(5, 46, 14), // "setFormatDepth"
QT_MOC_LITERAL(6, 61, 11), // "FormatDepth"
QT_MOC_LITERAL(7, 73, 16), // "setLengthPicture"
QT_MOC_LITERAL(8, 90, 13), // "LengthPicture"
QT_MOC_LITERAL(9, 104, 16), // "setFormatPicture"
QT_MOC_LITERAL(10, 121, 14), // "QImage::Format"
QT_MOC_LITERAL(11, 136, 18), // "setScalePixelPerMm"
QT_MOC_LITERAL(12, 155, 15), // "scalePixelPerMm"
QT_MOC_LITERAL(13, 171, 11), // "setDrawType"
QT_MOC_LITERAL(14, 183, 8) // "drawType"

    },
    "DrawSettings\0setFormatTime\0\0FormatTime\0"
    "format\0setFormatDepth\0FormatDepth\0"
    "setLengthPicture\0LengthPicture\0"
    "setFormatPicture\0QImage::Format\0"
    "setScalePixelPerMm\0scalePixelPerMm\0"
    "setDrawType\0drawType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,
      11,    1,   56,    2, 0x0a /* Public */,
      13,    1,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, 0x80000000 | 10,    4,
    QMetaType::Void, QMetaType::QReal,   12,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void DrawSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DrawSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFormatTime((*reinterpret_cast< FormatTime(*)>(_a[1]))); break;
        case 1: _t->setFormatDepth((*reinterpret_cast< FormatDepth(*)>(_a[1]))); break;
        case 2: _t->setLengthPicture((*reinterpret_cast< LengthPicture(*)>(_a[1]))); break;
        case 3: _t->setFormatPicture((*reinterpret_cast< QImage::Format(*)>(_a[1]))); break;
        case 4: _t->setScalePixelPerMm((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 5: _t->setDrawType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DrawSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DrawSettings.data,
    qt_meta_data_DrawSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DrawSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DrawSettings.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DrawSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
