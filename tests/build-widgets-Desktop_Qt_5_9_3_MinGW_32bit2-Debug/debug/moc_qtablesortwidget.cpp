/****************************************************************************
** Meta object code from reading C++ file 'qtablesortwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/base/qtablesortwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtablesortwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTableSortWidget_t {
    QByteArrayData data[13];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTableSortWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTableSortWidget_t qt_meta_stringdata_QTableSortWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QTableSortWidget"
QT_MOC_LITERAL(1, 17, 11), // "setSortType"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "col"
QT_MOC_LITERAL(4, 34, 27), // "QTableSortWidget::ESortType"
QT_MOC_LITERAL(5, 62, 4), // "type"
QT_MOC_LITERAL(6, 67, 18), // "convertColumnValue"
QT_MOC_LITERAL(7, 86, 15), // "ConvertFunction"
QT_MOC_LITERAL(8, 102, 4), // "func"
QT_MOC_LITERAL(9, 107, 4), // "find"
QT_MOC_LITERAL(10, 112, 9), // "searchStr"
QT_MOC_LITERAL(11, 122, 10), // "sortColumn"
QT_MOC_LITERAL(12, 133, 3) // "num"

    },
    "QTableSortWidget\0setSortType\0\0col\0"
    "QTableSortWidget::ESortType\0type\0"
    "convertColumnValue\0ConvertFunction\0"
    "func\0find\0searchStr\0sortColumn\0num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTableSortWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       6,    2,   39,    2, 0x0a /* Public */,
       9,    1,   44,    2, 0x0a /* Public */,
      11,    1,   47,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    3,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void QTableSortWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTableSortWidget *_t = static_cast<QTableSortWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setSortType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QTableSortWidget::ESortType(*)>(_a[2]))); break;
        case 1: _t->convertColumnValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ConvertFunction(*)>(_a[2]))); break;
        case 2: _t->find((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sortColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QTableSortWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_QTableSortWidget.data,
      qt_meta_data_QTableSortWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QTableSortWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTableSortWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTableSortWidget.stringdata0))
        return static_cast<void*>(this);
    return QTableWidget::qt_metacast(_clname);
}

int QTableSortWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
