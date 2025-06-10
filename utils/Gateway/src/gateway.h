//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Internal buffers for I/O and memory.
// These buffers are defined in the auto-generated glueVars.cpp file
//-----------------------------------------------------------------------------
#ifndef PRO_GATEWAY_H
#define PRO_GATEWAY_H

#include "iec_types.h"
#include "binder.h"

constexpr unsigned int   BUFFER_SIZE     = 1024;    // Размер категорий регистров
constexpr unsigned short SPEC_FUNC_COUNT = 16;      // Special functions count

//lock for the buffers
extern pthread_mutex_t bufferLock;

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
extern Registry& getGlobalRegistry();

// Объявляем глобальные экземпляры прокси-объектов
extern Registry::IX IX;
extern Registry::QX QX;
extern Registry::MX MX;
extern Registry::SX SX;

extern Registry::IB IB;
extern Registry::QB QB;
extern Registry::MB MB;
extern Registry::SB SB;

extern Registry::IW IW;
extern Registry::QW QW;
extern Registry::MW MW;
extern Registry::SW SW;

extern Registry::ID ID;
extern Registry::QD QD;
extern Registry::MD MD;
extern Registry::SD SD;

extern Registry::IL IL;
extern Registry::QL QL;
extern Registry::ML ML;
extern Registry::SL SL;

extern Registry::IF IF;
extern Registry::QF QF;
extern Registry::MF MF;
extern Registry::SF SF;

extern Registry::IE IE;
extern Registry::QE QE;
extern Registry::ME ME;
extern Registry::SE SE;

template<typename T> T& getGlobalProxy();

#endif //PRO_GATEWAY_H
