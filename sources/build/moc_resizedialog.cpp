/****************************************************************************
** Meta object code from reading C++ file 'resizedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogs/resizedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resizedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ResizeDialog_t {
    QByteArrayData data[10];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ResizeDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ResizeDialog_t qt_meta_stringdata_ResizeDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ResizeDialog"
QT_MOC_LITERAL(1, 13, 19), // "pixelsButtonClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "flag"
QT_MOC_LITERAL(4, 39, 20), // "percentButtonClicked"
QT_MOC_LITERAL(5, 60, 19), // "pixelsWValueChanged"
QT_MOC_LITERAL(6, 80, 5), // "value"
QT_MOC_LITERAL(7, 86, 19), // "pixelsHValueChanged"
QT_MOC_LITERAL(8, 106, 20), // "percentWValueChanged"
QT_MOC_LITERAL(9, 127, 20) // "percentHValueChanged"

    },
    "ResizeDialog\0pixelsButtonClicked\0\0"
    "flag\0percentButtonClicked\0pixelsWValueChanged\0"
    "value\0pixelsHValueChanged\0"
    "percentWValueChanged\0percentHValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResizeDialog[] = {

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
       5,    1,   50,    2, 0x08 /* Private */,
       7,    1,   53,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void ResizeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ResizeDialog *_t = static_cast<ResizeDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pixelsButtonClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->percentButtonClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->pixelsWValueChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->pixelsHValueChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->percentWValueChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->percentHValueChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ResizeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResizeDialog.data,
      qt_meta_data_ResizeDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ResizeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResizeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ResizeDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ResizeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
