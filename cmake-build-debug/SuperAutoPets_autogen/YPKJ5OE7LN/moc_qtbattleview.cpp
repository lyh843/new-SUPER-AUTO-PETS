/****************************************************************************
** Meta object code from reading C++ file 'qtbattleview.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/qtbattleview.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtbattleview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12QtBattleViewE_t {};
} // unnamed namespace

template <> constexpr inline auto QtBattleView::qt_create_metaobjectdata<qt_meta_tag_ZN12QtBattleViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QtBattleView",
        "battleFinished",
        "",
        "BattleResult",
        "result",
        "backToShop",
        "on_start_button_clicked",
        "on_auto_play_button_clicked",
        "on_forward_button_clicked",
        "onAutoStep",
        "onBattleEvent",
        "BattleEvent",
        "event"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'battleFinished'
        QtMocHelpers::SignalData<void(BattleResult)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'backToShop'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'on_start_button_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_auto_play_button_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_forward_button_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAutoStep'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBattleEvent'
        QtMocHelpers::SlotData<void(const BattleEvent &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QtBattleView, qt_meta_tag_ZN12QtBattleViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QtBattleView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12QtBattleViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12QtBattleViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12QtBattleViewE_t>.metaTypes,
    nullptr
} };

void QtBattleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QtBattleView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->battleFinished((*reinterpret_cast<std::add_pointer_t<BattleResult>>(_a[1]))); break;
        case 1: _t->backToShop(); break;
        case 2: _t->on_start_button_clicked(); break;
        case 3: _t->on_auto_play_button_clicked(); break;
        case 4: _t->on_forward_button_clicked(); break;
        case 5: _t->onAutoStep(); break;
        case 6: _t->onBattleEvent((*reinterpret_cast<std::add_pointer_t<BattleEvent>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QtBattleView::*)(BattleResult )>(_a, &QtBattleView::battleFinished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtBattleView::*)()>(_a, &QtBattleView::backToShop, 1))
            return;
    }
}

const QMetaObject *QtBattleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtBattleView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12QtBattleViewE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QtBattleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QtBattleView::battleFinished(BattleResult _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void QtBattleView::backToShop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
