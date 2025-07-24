//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// (!) ЭТОТ ФАЙЛ - ИНЪЕКЦИЯ В IEC-ПРОГРАММУ (в procont-ex не включать)
#pragma once

#include "iec_types_all.h"
#include "reg_binder.h"

// Объявляем ссылку на переменную
extern "C" {
    //__attribute__((visibility("default")))
    extern TIME __CURRENT_TIME;

}
