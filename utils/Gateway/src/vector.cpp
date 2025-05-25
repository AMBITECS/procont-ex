//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#define GATEWAY_EXPORTS  // Важно: определяем перед включением заголовка!
#include "vector.h"

// Явное инстанцирование для DLL
template class ObservableVector<IEC_UINT*>;
template class ObservableVector<IEC_UDINT*>;
template class ObservableVector<IEC_ULINT*>;

