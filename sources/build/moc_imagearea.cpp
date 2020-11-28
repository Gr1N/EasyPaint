/****************************************************************************
** Meta object code from reading C++ file 'imagearea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imagearea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagearea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageArea_t {
    QByteArrayData data[14];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageArea_t qt_meta_stringdata_ImageArea = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ImageArea"
QT_MOC_LITERAL(1, 10, 20), // "sendPrimaryColorView"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 22), // "sendSecondaryColorView"
QT_MOC_LITERAL(4, 55, 16), // "sendNewImageSize"
QT_MOC_LITERAL(5, 72, 13), // "sendCursorPos"
QT_MOC_LITERAL(6, 86, 9), // "sendColor"
QT_MOC_LITERAL(7, 96, 29), // "sendRestorePreviousInstrument"
QT_MOC_LITERAL(8, 126, 17), // "sendSetInstrument"
QT_MOC_LITERAL(9, 144, 15), // "InstrumentsEnum"
QT_MOC_LITERAL(10, 160, 24), // "sendEnableCopyCutActions"
QT_MOC_LITERAL(11, 185, 6), // "enable"
QT_MOC_LITERAL(12, 192, 29), // "sendEnableSelectionInstrument"
QT_MOC_LITERAL(13, 222, 8) // "autoSave"

    },
    "ImageArea\0sendPrimaryColorView\0\0"
    "sendSecondaryColorView\0sendNewImageSize\0"
    "sendCursorPos\0sendColor\0"
    "sendRestorePreviousInstrument\0"
    "sendSetInstrument\0InstrumentsEnum\0"
    "sendEnableCopyCutActions\0enable\0"
    "sendEnableSelectionInstrument\0autoSave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    1,   66,    2, 0x06 /* Public */,
       5,    1,   69,    2, 0x06 /* Public */,
       6,    1,   72,    2, 0x06 /* Public */,
       7,    0,   75,    2, 0x06 /* Public */,
       8,    1,   76,    2, 0x06 /* Public */,
      10,    1,   79,    2, 0x06 /* Public */,
      12,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ImageArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageArea *_t = static_cast<ImageArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPrimaryColorView(); break;
        case 1: _t->sendSecondaryColorView(); break;
        case 2: _t->sendNewImageSize((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 3: _t->sendCursorPos((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->sendColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->sendRestorePreviousInstrument(); break;
        case 6: _t->sendSetInstrument((*reinterpret_cast< InstrumentsEnum(*)>(_a[1]))); break;
        case 7: _t->sendEnableCopyCutActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sendEnableSelectionInstrument((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->autoSave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ImageArea::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendPrimaryColorView)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendSecondaryColorView)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(const QSize & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendNewImageSize)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendCursorPos)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendColor)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendRestorePreviousInstrument)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(InstrumentsEnum );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendSetInstrument)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendEnableCopyCutActions)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ImageArea::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageArea::sendEnableSelectionInstrument)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject ImageArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageArea.data,
      qt_meta_data_ImageArea,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ImageArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ImageArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ImageArea::sendPrimaryColorView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ImageArea::sendSecondaryColorView()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ImageArea::sendNewImageSize(const QSize & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ImageArea::sendCursorPos(const QPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ImageArea::sendColor(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ImageArea::sendRestorePreviousInstrument()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ImageArea::sendSetInstrument(InstrumentsEnum _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ImageArea::sendEnableCopyCutActions(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ImageArea::sendEnableSelectionInstrument(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
