TYPE
  TError : (E_SUCCESS, E_ID, E_HEAD, E_INDEX, E_ITEMPOS, E_ITEM, E_GRID, E_AXIS, E_PRIO, E_MATER, E_PROFILE, E_VALUE, E_STACKSIZE, E_ROOT, E_ITEMSIZE, E_STEPSIZE, E_TIMESIZE, E_NOTREADY, E_STRUCT, E_VALIDATE, E_LOC2ABS, E_ABS2LOC, E_GETTEMP, E_SETTEMP, E_CHECKVALID, E_LINKITEMS, E_PROCESS, E_PREPROC, E_POSTPROC, E_BADTEMP, E_STATE, E_CHECK, E_FAIL, W_PERIOD) := E_SUCCESS;
  TStat : STRUCT
    RDY : BOOL := TRUE;
    DBG : BOOL := TRUE;
    ERR : TError := E_SUCCESS;
    PAR : UINT := 0;
    STR : STRING := '';
  END_STRUCT;
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := DEBUG;
END_TYPE

FUNCTION Err2Str : STRING
  VAR_INPUT
    ERR : TError := E_SUCCESS;
  END_VAR

  case ERR of
  (* Информационные сообщения *)
  E_SUCCESS:      Err2Str := 'Succeeded!';

  (* Критические ошибки *)
  E_FAIL:         Err2Str := 'Unexpected error';
  E_STATE:        Err2Str := 'Program state error';
  E_CHECK:        Err2Str := 'Check point error';
  E_HEAD:         Err2Str := 'Invalid head';
  E_INDEX:        Err2Str := 'Invalid index';
  E_ITEMPOS:      Err2Str := 'Invalid item position';
  E_ITEM:         Err2Str := 'Invalid element';
  E_GRID:         Err2Str := 'Invalid grid';
  E_AXIS:         Err2Str := 'Invalid axis';
  E_PRIO:         Err2Str := 'Invalid prio';
  E_MATER:        Err2Str := 'Invalid mater';
  E_PROFILE:      Err2Str := 'Invalid profile';
  E_VALUE:        Err2Str := 'Invalid value';
  E_ROOT:         Err2Str := 'Invalid ROOT';
  E_ITEMSIZE:     Err2Str := 'Bad ItemAt size';
  E_STEPSIZE:     Err2Str := 'Bad axis step';
  E_TIMESIZE:     Err2Str := 'Bad time step';
  E_STACKSIZE:    Err2Str := 'Small stacksize';
  E_NOTREADY:     Err2Str := 'Object dont ready';
  E_LOC2ABS:      Err2Str := 'Loc2Abs error';
  E_ABS2LOC:      Err2Str := 'Abs2Loc error';
  E_VALIDATE:     Err2Str := 'Validate error';
  E_CHECKVALID:   Err2Str := 'CheckValid error';
  E_LINKITEMS:    Err2Str := 'LinkItems error';
  E_PROCESS:      Err2Str := 'Process item error';
  E_BADTEMP:      Err2Str := 'GetTemp error';

  (* Предупреждения *)
  W_PERIOD:       Err2Str := 'Small period';
  else            Err2Str := 'Unknown error';
  end_case;
END_FUNCTION

FUNCTION LogMsg : STRING
  VAR_INPUT
    STR : STRING := '';
    LVL : LOGLEVEL := DEBUG;
    ERR : TError := E_SUCCESS;
  END_VAR

  {{
    #ifdef _BEREMIZ_H_
      #define __LOG_MSG(level,string,length) LogMessage(level,(char *)string,length)
    #else
      #define __LOG_MSG(level,string,length) printf("%s\n", (char *)string)
    #endif
    TSTAT *pStat = __GET_GLOBAL_STAT();
    if (LVL!=LOGLEVEL__DEBUG || (LVL==LOGLEVEL__DEBUG && pStat->DBG)) {
      if (STR.len) __LOG_MSG(LVL, (char *)STR.body, STR.len);
    }
    if (ERR!=TERROR__E_SUCCESS) {
      pStat->ERR=ERR;
      LVL=ERR2LEV(1,NULL,ERR); 
      STR=ERR2STR(1,NULL,ERR);
      if (STR.len) __LOG_MSG(LVL,(char *)STR.body,STR.len);
    }
    return (LOGMSG = __INIT_STRING);
  }}
END_FUNCTION

PROGRAM program0
  VAR
    LocalVar0 : DINT;
  END_VAR


  LocalVar0 := 1;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION

(*DBG:char md5[] = "228082dcb39f862b7d9728e7e83abcc8";*)
(*DBG:/**)
(*DBG: * This file is part of OpenPLC Runtime*)
(*DBG: **)
(*DBG: * Copyright (C) 2023 Autonomy, GP Orcullo*)
(*DBG: * Based on the work by GP Orcullo on Beremiz for uC*)
(*DBG: **)
(*DBG: * This program is free software; you can redistribute it and/or*)
(*DBG: * modify it under the terms of the GNU General Public License*)
(*DBG: * as published by the Free Software Foundation; either version 2*)
(*DBG: * of the License, or (at your option) any later version.*)
(*DBG: **)
(*DBG: * This program is distributed in the hope that it will be useful,*)
(*DBG: * but WITHOUT ANY WARRANTY; without even the implied warranty of*)
(*DBG: * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*)
(*DBG: * GNU General Public License for more details.*)
(*DBG: **)
(*DBG: * You should have received a copy of the GNU General Public License*)
(*DBG: * along with this program; If not, see <http://www.gnu.org/licenses/>.*)
(*DBG: **)
(*DBG: */*)
(*DBG:*)
(*DBG:#include <stdbool.h>*)
(*DBG:*)
(*DBG:#include "iec_types_all.h"*)
(*DBG:#include "POUS.h"*)
(*DBG:*)
(*DBG:#define SAME_ENDIANNESS      0*)
(*DBG:#define REVERSE_ENDIANNESS   1*)
(*DBG:*)
(*DBG:uint8_t endianness;*)
(*DBG:*)
(*DBG:*)
(*DBG:extern PROGRAM0 RES0__INSTANCE0;*)
(*DBG:*)
(*DBG:static const struct {*)
(*DBG:    void *ptr;*)
(*DBG:    __IEC_types_enum type;*)
(*DBG:} debug_vars[] = {*)
(*DBG:    {&(RES0__INSTANCE0.LOCALVAR0), DINT_ENUM},*)
(*DBG:};*)
(*DBG:*)
(*DBG:#define VAR_COUNT               1*)
(*DBG:*)
(*DBG:uint16_t get_var_count(void)*)
(*DBG:{*)
(*DBG:    return VAR_COUNT;*)
(*DBG:}*)
(*DBG:*)
(*DBG:size_t get_var_size(size_t idx)*)
(*DBG:{*)
(*DBG:    if (idx >= VAR_COUNT)*)
(*DBG:    {*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case DINT_ENUM:*)
(*DBG:        return sizeof(DINT);*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void *get_var_addr(size_t idx)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case DINT_ENUM:*)
(*DBG:        return (void *)&((__IEC_DINT_t *) ptr)->value;*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void force_var(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    if (forced) {*)
(*DBG:        size_t var_size = get_var_size(idx);*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case DINT_ENUM: {*)
(*DBG:            memcpy(&((__IEC_DINT_t *) ptr)->value, val, var_size);*)
(*DBG:            //((__IEC_DINT_t *) ptr)->value = *((DINT *) val);*)
(*DBG:            ((__IEC_DINT_t *) ptr)->flags |= __IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    } else {*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case DINT_ENUM:*)
(*DBG:            ((__IEC_DINT_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void swap_bytes(void *ptr, size_t size) *)
(*DBG:{*)
(*DBG:    uint8_t *bytePtr = (uint8_t *)ptr;*)
(*DBG:    size_t i;*)
(*DBG:    for (i = 0; i < size / 2; ++i) *)
(*DBG:    {*)
(*DBG:        uint8_t temp = bytePtr[i];*)
(*DBG:        bytePtr[i] = bytePtr[size - 1 - i];*)
(*DBG:        bytePtr[size - 1 - i] = temp;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void trace_reset(void)*)
(*DBG:{*)
(*DBG:    for (size_t i=0; i < VAR_COUNT; i++) *)
(*DBG:    {*)
(*DBG:        force_var(i, false, 0);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_trace(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    if (idx >= 0 && idx < VAR_COUNT) *)
(*DBG:    {*)
(*DBG:        if (endianness == REVERSE_ENDIANNESS)*)
(*DBG:        {*)
(*DBG:            // Aaaaarghhhh... Stupid AVR is Big Endian.*)
(*DBG:            swap_bytes(val, get_var_size(idx));*)
(*DBG:        }*)
(*DBG:*)
(*DBG:        force_var(idx, forced, val);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_endianness(uint8_t value)*)
(*DBG:{*)
(*DBG:    if (value == SAME_ENDIANNESS || value == REVERSE_ENDIANNESS)*)
(*DBG:    {*)
(*DBG:        endianness = value;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)