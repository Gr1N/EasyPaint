/****************************************************************************
** Meta object code from reading C++ file 'selectioninstrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../instruments/selectioninstrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectioninstrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectionInstrument_t {
    QByteArrayData data[5];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectionInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectionInstrument_t qt_meta_stringdata_SelectionInstrument = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SelectionInstrument"
QT_MOC_LITERAL(1, 20, 24), // "sendEnableCopyCutActions"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 6), // "enable"
QT_MOC_LITERAL(4, 53, 29) // "sendEnableSelectionInstrument"

    },
    "SelectionInstrument\0sendEnableCopyCutActions\0"
    "\0enable\0sendEnableSelectionInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectionInstrument[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void SelectionInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SelectionInstrument *_t = static_cast<SelectionInstrument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEnableCopyCutActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sendEnableSelectionInstrument((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionInstrument::sendEnableCopyCutActions)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionInstrument::sendEnableSelectionInstrument)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SelectionInstrument::staticMetaObject = {
    { &AbstractSelection::staticMetaObject, qt_meta_stringdata_SelectionInstrument.data,
      qt_meta_data_SelectionInstrument,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SelectionInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectionInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectionInstrument.stringdata0))
        return static_cast<void*>(this);
    return AbstractSelection::qt_metacast(_clname);
}

int SelectionInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractSelection::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SelectionInstrument::sendEnableCopyCutActions(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SelectionInstrument::sendEnableSelectionInstrument(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
