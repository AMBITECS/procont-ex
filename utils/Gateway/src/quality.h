//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

/**
 * Quality - Качество данных тега
 */
enum class Quality : int {
    GOOD = 0,       // Хорошее качество
    BAD = 1,        // Плохое качество
    UNCERTAIN = 2   // Неопределенное качество
};

namespace QualityUtils {
    inline const char* toString(Quality quality) {
        switch (quality) {
            case Quality::GOOD: return "GOOD";
            case Quality::BAD: return "BAD";
            case Quality::UNCERTAIN: return "UNCERTAIN";
            default: return "UNKNOWN";
        }
    }

    inline Quality fromInt(int value) {
        switch (value) {
            case 0: return Quality::GOOD;
            case 1: return Quality::BAD;
            case 2: return Quality::UNCERTAIN;
            default: return Quality::BAD; // По умолчанию считаем плохим
        }
    }
}
