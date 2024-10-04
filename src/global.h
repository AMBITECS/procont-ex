#ifndef AMBI_DEF_STD_H
#define AMBI_DEF_STD_H
//#include "Tracer.h"
#include <QtGlobal>
#include <QtCore/qglobal.h>
#include <QCoreApplication>

#define EXP     explicit
#define NDS     [[nodiscard]]
#define MBU     [[maybe_unused]]
#define INL     inline
#define OVR     Q_DECL_OVERRIDE //override
#define FIN     final
#define CEX     constexpr
#define RCE     // constexpr with C++ 14
#define NEX     noexcept
#define DFL     default
#define VRT     virtual
#define DEL     delete
#define PURE    =0
#define NUL     nullptr

#define interface   struct
#define BAD_INDEX   (size_t(-1))

//NOLINTBEGIN
#define _T(...)         (tr(__VA_ARGS__))
#define _T2(func, ...)  (QCoreApplication::translate(func, __VA_ARGS__))
//NOLINTEND

// ----------------------------------------------------------------------------
#endif //AMBI_DEF_STD_H
