//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#include "registry.h"

// Инициализация глобальных ссылок
//VEC_BOOL& IX = Registry::IX();
//VEC_BOOL& QX = Registry::QX();

VEC_BYTE&  IB = Registry::IB();
VEC_BYTE&  QB = Registry::QB();
VEC_UINT&  IW = Registry::IW();
VEC_UINT&  QW = Registry::QW();
VEC_UDINT& ID = Registry::ID();
VEC_UDINT& QD = Registry::QD();
VEC_ULINT& IL = Registry::IL();
VEC_ULINT& QL = Registry::QL();
VEC_UINT&  MW = Registry::MW();
VEC_UDINT& MD = Registry::MD();
VEC_ULINT& ML = Registry::ML();

// Функция инициализации (опционально)
void InitPLCRegisters() {
    // Явная инициализация для thread-safe доступа
//    static_cast<void>(Registry::IX());
//    static_cast<void>(Registry::QX());
    static_cast<void>(Registry::IB());
    static_cast<void>(Registry::QB());
    static_cast<void>(Registry::IW());
    static_cast<void>(Registry::QW());
    static_cast<void>(Registry::ID());
    static_cast<void>(Registry::QD());
    static_cast<void>(Registry::IL());
    static_cast<void>(Registry::QL());
    static_cast<void>(Registry::MW());
    static_cast<void>(Registry::MD());
    static_cast<void>(Registry::ML());
}

