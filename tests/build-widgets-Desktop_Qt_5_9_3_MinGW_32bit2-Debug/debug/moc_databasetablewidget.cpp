/****************************************************************************
** Meta object code from reading C++ file 'databasetablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/base/databasetablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databasetablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseTableWidget_t {
    QByteArrayData data[7];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseTableWidget_t qt_meta_stringdata_DatabaseTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DatabaseTableWidget"
QT_MOC_LITERAL(1, 20, 17), // "updateDataRequest"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "updateData"
QT_MOC_LITERAL(4, 50, 17), // "operationFinished"
QT_MOC_LITERAL(5, 68, 25), // "QList<QVector<QVariant>*>"
QT_MOC_LITERAL(6, 94, 4) // "data"

    },
    "DatabaseTableWidget\0updateDataRequest\0"
    "\0updateData\0operationFinished\0"
    "QList<QVector<QVariant>*>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void DatabaseTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DatabaseTableWidget *_t = static_cast<DatabaseTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateDataRequest(); break;
        case 1: _t->updateData(); break;
        case 2: _t->operationFinished((*reinterpret_cast< QList<QVector<QVariant>*>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DatabaseTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseTableWidget::updateDataRequest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DatabaseTableWidget::staticMetaObject = {
    { &QTableSortWidget::staticMetaObject, qt_meta_stringdata_DatabaseTableWidget.data,
      qt_meta_data_DatabaseTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DatabaseTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QTableSortWidget::qt_metacast(_clname);
}

int DatabaseTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableSortWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DatabaseTableWidget::updateDataRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
