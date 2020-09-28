/****************************************************************************
** Meta object code from reading C++ file 'graphicwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../geology/inc/graphicwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicWidget_t {
    QByteArrayData data[18];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicWidget_t qt_meta_stringdata_GraphicWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GraphicWidget"
QT_MOC_LITERAL(1, 14, 19), // "settingsHaveChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "tabChanged"
QT_MOC_LITERAL(4, 46, 15), // "changedDrawType"
QT_MOC_LITERAL(5, 62, 8), // "drawType"
QT_MOC_LITERAL(6, 71, 17), // "changedFormatTime"
QT_MOC_LITERAL(7, 89, 24), // "DrawSettings::FormatTime"
QT_MOC_LITERAL(8, 114, 6), // "format"
QT_MOC_LITERAL(9, 121, 18), // "changedFormatDepth"
QT_MOC_LITERAL(10, 140, 25), // "DrawSettings::FormatDepth"
QT_MOC_LITERAL(11, 166, 20), // "changedPictureHeight"
QT_MOC_LITERAL(12, 187, 27), // "DrawSettings::LengthPicture"
QT_MOC_LITERAL(13, 215, 20), // "changedPictureFormat"
QT_MOC_LITERAL(14, 236, 14), // "QImage::Format"
QT_MOC_LITERAL(15, 251, 22), // "changedScalePixelPerMm"
QT_MOC_LITERAL(16, 274, 15), // "scalePixelPerMm"
QT_MOC_LITERAL(17, 290, 7) // "refresh"

    },
    "GraphicWidget\0settingsHaveChanged\0\0"
    "tabChanged\0changedDrawType\0drawType\0"
    "changedFormatTime\0DrawSettings::FormatTime\0"
    "format\0changedFormatDepth\0"
    "DrawSettings::FormatDepth\0"
    "changedPictureHeight\0DrawSettings::LengthPicture\0"
    "changedPictureFormat\0QImage::Format\0"
    "changedScalePixelPerMm\0scalePixelPerMm\0"
    "refresh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       9,    1,   67,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    1,   73,    2, 0x0a /* Public */,
      15,    1,   76,    2, 0x0a /* Public */,
      17,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    8,
    QMetaType::Void, 0x80000000 | 12,    8,
    QMetaType::Void, 0x80000000 | 14,    8,
    QMetaType::Void, QMetaType::QReal,   16,
    QMetaType::Void,

       0        // eod
};

void GraphicWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingsHaveChanged(); break;
        case 1: _t->tabChanged(); break;
        case 2: _t->changedDrawType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changedFormatTime((*reinterpret_cast< DrawSettings::FormatTime(*)>(_a[1]))); break;
        case 4: _t->changedFormatDepth((*reinterpret_cast< DrawSettings::FormatDepth(*)>(_a[1]))); break;
        case 5: _t->changedPictureHeight((*reinterpret_cast< DrawSettings::LengthPicture(*)>(_a[1]))); break;
        case 6: _t->changedPictureFormat((*reinterpret_cast< QImage::Format(*)>(_a[1]))); break;
        case 7: _t->changedScalePixelPerMm((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 8: _t->refresh(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GraphicWidget.data,
    qt_meta_data_GraphicWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GraphicWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
