/****************************************************************************
** Meta object code from reading C++ file 'graphicscontrolpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../geology/inc/graphicscontrolpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicscontrolpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsControlPanel_t {
    QByteArrayData data[24];
    char stringdata0[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsControlPanel_t qt_meta_stringdata_GraphicsControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GraphicsControlPanel"
QT_MOC_LITERAL(1, 21, 15), // "changedDrawType"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 8), // "drawType"
QT_MOC_LITERAL(4, 47, 17), // "changedFormatTime"
QT_MOC_LITERAL(5, 65, 24), // "DrawSettings::FormatTime"
QT_MOC_LITERAL(6, 90, 6), // "format"
QT_MOC_LITERAL(7, 97, 18), // "changedFormatDepth"
QT_MOC_LITERAL(8, 116, 25), // "DrawSettings::FormatDepth"
QT_MOC_LITERAL(9, 142, 20), // "changedPictureHeight"
QT_MOC_LITERAL(10, 163, 27), // "DrawSettings::LengthPicture"
QT_MOC_LITERAL(11, 191, 20), // "changedPictureFormat"
QT_MOC_LITERAL(12, 212, 14), // "QImage::Format"
QT_MOC_LITERAL(13, 227, 22), // "changedScalePixelPerMm"
QT_MOC_LITERAL(14, 250, 15), // "scalePixelPerMm"
QT_MOC_LITERAL(15, 266, 7), // "refresh"
QT_MOC_LITERAL(16, 274, 14), // "changeDrawType"
QT_MOC_LITERAL(17, 289, 5), // "index"
QT_MOC_LITERAL(18, 295, 16), // "changeFormatTime"
QT_MOC_LITERAL(19, 312, 17), // "changeFormatDepth"
QT_MOC_LITERAL(20, 330, 19), // "changePictureHeight"
QT_MOC_LITERAL(21, 350, 19), // "changePictureFormat"
QT_MOC_LITERAL(22, 370, 21), // "changeScalePixelPerMm"
QT_MOC_LITERAL(23, 392, 5) // "scale"

    },
    "GraphicsControlPanel\0changedDrawType\0"
    "\0drawType\0changedFormatTime\0"
    "DrawSettings::FormatTime\0format\0"
    "changedFormatDepth\0DrawSettings::FormatDepth\0"
    "changedPictureHeight\0DrawSettings::LengthPicture\0"
    "changedPictureFormat\0QImage::Format\0"
    "changedScalePixelPerMm\0scalePixelPerMm\0"
    "refresh\0changeDrawType\0index\0"
    "changeFormatTime\0changeFormatDepth\0"
    "changePictureHeight\0changePictureFormat\0"
    "changeScalePixelPerMm\0scale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsControlPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       7,    1,   85,    2, 0x06 /* Public */,
       9,    1,   88,    2, 0x06 /* Public */,
      11,    1,   91,    2, 0x06 /* Public */,
      13,    1,   94,    2, 0x06 /* Public */,
      15,    0,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   98,    2, 0x0a /* Public */,
      18,    1,  101,    2, 0x0a /* Public */,
      19,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,
      21,    1,  110,    2, 0x0a /* Public */,
      22,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    6,
    QMetaType::Void, 0x80000000 | 10,    6,
    QMetaType::Void, 0x80000000 | 12,    6,
    QMetaType::Void, QMetaType::QReal,   14,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void GraphicsControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicsControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedDrawType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changedFormatTime((*reinterpret_cast< DrawSettings::FormatTime(*)>(_a[1]))); break;
        case 2: _t->changedFormatDepth((*reinterpret_cast< DrawSettings::FormatDepth(*)>(_a[1]))); break;
        case 3: _t->changedPictureHeight((*reinterpret_cast< DrawSettings::LengthPicture(*)>(_a[1]))); break;
        case 4: _t->changedPictureFormat((*reinterpret_cast< QImage::Format(*)>(_a[1]))); break;
        case 5: _t->changedScalePixelPerMm((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->refresh(); break;
        case 7: _t->changeDrawType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->changeFormatTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeFormatDepth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changePictureHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->changePictureFormat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->changeScalePixelPerMm((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GraphicsControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedDrawType)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)(DrawSettings::FormatTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedFormatTime)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)(DrawSettings::FormatDepth );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedFormatDepth)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)(DrawSettings::LengthPicture );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedPictureHeight)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)(QImage::Format );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedPictureFormat)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::changedScalePixelPerMm)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GraphicsControlPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsControlPanel::refresh)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicsControlPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GraphicsControlPanel.data,
    qt_meta_data_GraphicsControlPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsControlPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GraphicsControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GraphicsControlPanel::changedDrawType(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphicsControlPanel::changedFormatTime(DrawSettings::FormatTime _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphicsControlPanel::changedFormatDepth(DrawSettings::FormatDepth _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GraphicsControlPanel::changedPictureHeight(DrawSettings::LengthPicture _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GraphicsControlPanel::changedPictureFormat(QImage::Format _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GraphicsControlPanel::changedScalePixelPerMm(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GraphicsControlPanel::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
