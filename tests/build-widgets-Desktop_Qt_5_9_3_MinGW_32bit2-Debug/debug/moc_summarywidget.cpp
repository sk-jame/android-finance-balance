/****************************************************************************
** Meta object code from reading C++ file 'summarywidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/base/summarywidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'summarywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SummaryWidget_t {
    QByteArrayData data[10];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SummaryWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SummaryWidget_t qt_meta_stringdata_SummaryWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SummaryWidget"
QT_MOC_LITERAL(1, 14, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 61, 25), // "on_cbShowFilteres_toggled"
QT_MOC_LITERAL(5, 87, 7), // "checked"
QT_MOC_LITERAL(6, 95, 15), // "callTableUpdate"
QT_MOC_LITERAL(7, 111, 18), // "operation_finished"
QT_MOC_LITERAL(8, 130, 5), // "Task*"
QT_MOC_LITERAL(9, 136, 5) // "ftask"

    },
    "SummaryWidget\0on_pushButton_clicked\0"
    "\0on_pushButton_2_clicked\0"
    "on_cbShowFilteres_toggled\0checked\0"
    "callTableUpdate\0operation_finished\0"
    "Task*\0ftask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SummaryWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void SummaryWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SummaryWidget *_t = static_cast<SummaryWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_cbShowFilteres_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->callTableUpdate(); break;
        case 4: _t->operation_finished((*reinterpret_cast< Task*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SummaryWidget::staticMetaObject = {
    { &WidgetForStack::staticMetaObject, qt_meta_stringdata_SummaryWidget.data,
      qt_meta_data_SummaryWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SummaryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SummaryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SummaryWidget.stringdata0))
        return static_cast<void*>(this);
    return WidgetForStack::qt_metacast(_clname);
}

int SummaryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetForStack::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
