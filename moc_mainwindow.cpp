/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Aug 28 16:37:47 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x08,
      45,   12,   11,   11, 0x08,
      69,   12,   11,   11, 0x08,
      92,   12,   11,   11, 0x08,
     115,   12,   11,   11, 0x08,
     138,   12,   11,   11, 0x08,
     161,   12,   11,   11, 0x08,
     187,   12,   11,   11, 0x08,
     212,   12,   11,   11, 0x08,
     237,   12,   11,   11, 0x08,
     268,  262,   11,   11, 0x08,
     307,  301,   11,   11, 0x08,
     335,  262,   11,   11, 0x08,
     368,   11,   11,   11, 0x08,
     387,   11,   11,   11, 0x08,
     413,   11,   11,   11, 0x08,
     439,   11,   11,   11, 0x08,
     465,   11,   11,   11, 0x08,
     491,   11,   11,   11, 0x08,
     517,   11,   11,   11, 0x08,
     543,   11,   11,   11, 0x08,
     569,   11,   11,   11, 0x08,
     595,   11,   11,   11, 0x08,
     621,   11,   11,   11, 0x08,
     647,   11,   11,   11, 0x08,
     673,   11,   11,   11, 0x08,
     699,   11,   11,   11, 0x08,
     725,   11,   11,   11, 0x08,
     751,   11,   11,   11, 0x08,
     777,   11,   11,   11, 0x08,
     803,   11,   11,   11, 0x08,
     829,   11,   11,   11, 0x08,
     855,   11,   11,   11, 0x08,
     881,   11,   11,   11, 0x08,
     907,   11,   11,   11, 0x08,
     933,   11,   11,   11, 0x08,
     959,   11,   11,   11, 0x08,
     985,   11,   11,   11, 0x08,
    1011,   11,   11,   11, 0x08,
    1037,   11,   11,   11, 0x08,
    1063,   11,   11,   11, 0x08,
    1089,   11,   11,   11, 0x08,
    1115,   11,   11,   11, 0x08,
    1142,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0checked\0on_con0202_toggled(bool)\0"
    "on_dacpad_toggled(bool)\0on_d1pad_toggled(bool)\0"
    "on_d2pad_toggled(bool)\0on_d3pad_toggled(bool)\0"
    "on_d4pad_toggled(bool)\0on_adcpadin_toggled(bool)\0"
    "on_d1padin_toggled(bool)\0"
    "on_d2padin_toggled(bool)\0"
    "on_d3padin_toggled(bool)\0index\0"
    "on_rate_currentIndexChanged(int)\0value\0"
    "on_master_valueChanged(int)\0"
    "on_card_currentIndexChanged(int)\0"
    "on_panic_pressed()\0on_b11_buttonClicked(int)\0"
    "on_b12_buttonClicked(int)\0"
    "on_b13_buttonClicked(int)\0"
    "on_b14_buttonClicked(int)\0"
    "on_b15_buttonClicked(int)\0"
    "on_b16_buttonClicked(int)\0"
    "on_b0l_buttonClicked(int)\0"
    "on_b0r_buttonClicked(int)\0"
    "on_ba0_buttonClicked(int)\0"
    "on_ba1_buttonClicked(int)\0"
    "on_ba2_buttonClicked(int)\0"
    "on_ba3_buttonClicked(int)\0"
    "on_ba4_buttonClicked(int)\0"
    "on_ba5_buttonClicked(int)\0"
    "on_ba6_buttonClicked(int)\0"
    "on_ba7_buttonClicked(int)\0"
    "on_bsl_buttonClicked(int)\0"
    "on_bsr_buttonClicked(int)\0"
    "on_b1l_buttonClicked(int)\0"
    "on_b1r_buttonClicked(int)\0"
    "on_b2l_buttonClicked(int)\0"
    "on_b2r_buttonClicked(int)\0"
    "on_b3l_buttonClicked(int)\0"
    "on_b3r_buttonClicked(int)\0"
    "on_b4l_buttonClicked(int)\0"
    "on_b4r_buttonClicked(int)\0"
    "on_bpl_buttonClicked(int)\0"
    "on_bpr_buttonClicked(int)\0"
    "on_bdsl_buttonClicked(int)\0"
    "on_bdsr_buttonClicked(int)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_con0202_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_dacpad_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_d1pad_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_d2pad_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: on_d3pad_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_d4pad_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_adcpadin_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: on_d1padin_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_d2padin_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: on_d3padin_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: on_rate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: on_master_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: on_card_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: on_panic_pressed(); break;
        case 14: on_b11_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: on_b12_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: on_b13_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: on_b14_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: on_b15_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: on_b16_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: on_b0l_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: on_b0r_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: on_ba0_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: on_ba1_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: on_ba2_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: on_ba3_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: on_ba4_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: on_ba5_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: on_ba6_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: on_ba7_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: on_bsl_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: on_bsr_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: on_b1l_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: on_b1r_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: on_b2l_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: on_b2r_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: on_b3l_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: on_b3r_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: on_b4l_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: on_b4r_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: on_bpl_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: on_bpr_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: on_bdsl_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: on_bdsr_buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 44;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
