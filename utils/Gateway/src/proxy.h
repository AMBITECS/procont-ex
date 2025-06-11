//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Proxy-objects for Registry memory.
//-----------------------------------------------------------------------------
#ifndef REG_PROXY_H
#define REG_PROXY_H

#include "registry.h"

constexpr unsigned int   BUFFER_SIZE = 1024;    // Размер категорий регистров

//lock for the buffers
extern pthread_mutex_t bufferLock;

// Интерфейс для работы с глобальным реестром
Registry& getGlobalRegistry();

// Доступ к proxy-объектам
template<typename T, Registry::Category CATEGORY>
auto& getProxy();

// Получение сырого значения
template<Registry::Category CAT>
uint64_t getProxyValue(const Address& addr);

// Проверка изменений
template<Registry::Category CAT>
bool isProxyChanged(const Address& addr);

// Глобальные proxy-объекты
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


#endif //REG_PROXY_H
