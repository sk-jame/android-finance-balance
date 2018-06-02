/****************************************************************************
** Meta object code from reading C++ file 'dbtableview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/base/dbtableview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbtableview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DBTableView_t {
    QByteArrayData data[13];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DBTableView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DBTableView_t qt_meta_stringdata_DBTableView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DBTableView"
QT_MOC_LITERAL(1, 12, 18), // "requestContextMenu"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "point"
QT_MOC_LITERAL(4, 38, 16), // "enableDataWidget"
QT_MOC_LITERAL(5, 55, 6), // "enable"
QT_MOC_LITERAL(6, 62, 19), // "selectDataBaseTable"
QT_MOC_LITERAL(7, 82, 5), // "table"
QT_MOC_LITERAL(8, 88, 15), // "copyToClipBoard"
QT_MOC_LITERAL(9, 104, 15), // "showContextMenu"
QT_MOC_LITERAL(10, 120, 19), // "menuActionTriggered"
QT_MOC_LITERAL(11, 140, 8), // "QAction*"
QT_MOC_LITERAL(12, 149, 3) // "act"

    },
    "DBTableView\0requestContextMenu\0\0point\0"
    "enableDataWidget\0enable\0selectDataBaseTable\0"
    "table\0copyToClipBoard\0showContextMenu\0"
    "menuActionTriggered\0QAction*\0act"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBTableView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x08 /* Private */,
      10,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void DBTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DBTableView *_t = static_cast<DBTableView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->enableDataWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->selectDataBaseTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->copyToClipBoard(); break;
        case 4: _t->showContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->menuActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DBTableView::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DBTableView::requestContextMenu)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DBTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_DBTableView.data,
      qt_meta_data_DBTableView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DBTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DBTableView.stringdata0))
        return static_cast<void*>(this);
    return QTableView::qt_metacast(_clname);
}

int DBTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DBTableView::requestContextMenu(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
