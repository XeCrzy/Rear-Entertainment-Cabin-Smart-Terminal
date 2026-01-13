/****************************************************************************
** Meta object code from reading C++ file 'clientbthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clientbthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientbthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientBThread_t {
    QByteArrayData data[20];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientBThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientBThread_t qt_meta_stringdata_ClientBThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientBThread"
QT_MOC_LITERAL(1, 14, 19), // "weatherDataReceived"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "city"
QT_MOC_LITERAL(4, 40, 7), // "weather"
QT_MOC_LITERAL(5, 48, 11), // "temperature"
QT_MOC_LITERAL(6, 60, 8), // "humidity"
QT_MOC_LITERAL(7, 69, 15), // "commandReceived"
QT_MOC_LITERAL(8, 85, 7), // "command"
QT_MOC_LITERAL(9, 93, 17), // "connectedToServer"
QT_MOC_LITERAL(10, 111, 22), // "disconnectedFromServer"
QT_MOC_LITERAL(11, 134, 15), // "connectionError"
QT_MOC_LITERAL(12, 150, 5), // "error"
QT_MOC_LITERAL(13, 156, 12), // "cityNameSent"
QT_MOC_LITERAL(14, 169, 13), // "dataSendError"
QT_MOC_LITERAL(15, 183, 12), // "debugMessage"
QT_MOC_LITERAL(16, 196, 3), // "msg"
QT_MOC_LITERAL(17, 200, 25), // "manualConnectionCompleted"
QT_MOC_LITERAL(18, 226, 7), // "success"
QT_MOC_LITERAL(19, 234, 18) // "onReconnectTimeout"

    },
    "ClientBThread\0weatherDataReceived\0\0"
    "city\0weather\0temperature\0humidity\0"
    "commandReceived\0command\0connectedToServer\0"
    "disconnectedFromServer\0connectionError\0"
    "error\0cityNameSent\0dataSendError\0"
    "debugMessage\0msg\0manualConnectionCompleted\0"
    "success\0onReconnectTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientBThread[] = {

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
       1,    4,   64,    2, 0x06 /* Public */,
       7,    1,   73,    2, 0x06 /* Public */,
       9,    0,   76,    2, 0x06 /* Public */,
      10,    0,   77,    2, 0x06 /* Public */,
      11,    1,   78,    2, 0x06 /* Public */,
      13,    1,   81,    2, 0x06 /* Public */,
      14,    1,   84,    2, 0x06 /* Public */,
      15,    1,   87,    2, 0x06 /* Public */,
      17,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Bool,   18,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ClientBThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientBThread *_t = static_cast<ClientBThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->weatherDataReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 1: _t->commandReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connectedToServer(); break;
        case 3: _t->disconnectedFromServer(); break;
        case 4: _t->connectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->cityNameSent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->dataSendError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->debugMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->manualConnectionCompleted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onReconnectTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientBThread::*_t)(const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::weatherDataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::commandReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::connectedToServer)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::disconnectedFromServer)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::connectionError)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::cityNameSent)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::dataSendError)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::debugMessage)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ClientBThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientBThread::manualConnectionCompleted)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject ClientBThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClientBThread.data,
      qt_meta_data_ClientBThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClientBThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientBThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClientBThread.stringdata0))
        return static_cast<void*>(const_cast< ClientBThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ClientBThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void ClientBThread::weatherDataReceived(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientBThread::commandReceived(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientBThread::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ClientBThread::disconnectedFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ClientBThread::connectionError(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientBThread::cityNameSent(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientBThread::dataSendError(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClientBThread::debugMessage(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ClientBThread::manualConnectionCompleted(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
