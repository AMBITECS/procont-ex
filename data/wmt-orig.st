TYPE
  TVar : DINT;
  TGrid : STRUCT
    A : ARRAY [0..6271] OF TVar;
  END_STRUCT;
  P_SINT : STRUCT
    A : SINT;
    B : SINT;
  END_STRUCT;
  TProf : ARRAY [0..11] OF P_SINT;
  THandle : ULINT;
  TMatter : STRUCT
    a : REAL := 0.0001;
    l : REAL := 1.0;
    h : REAL := 0.001;
    k : REAL := 1.0;
  END_STRUCT;
  P_INT : STRUCT
    A : INT := -1;
    B : INT := -1;
  END_STRUCT;
  TPos8 : SINT := -1;
  TItem : STRUCT
    ID : UINT := 0;
    Im : SINT := -1;
    Iv : SINT := -1;
    PDT : ARRAY [0..2] OF DT := [t#0ms, t#0ms, t#0ms];
    Par : TPos8 := -1;
    Num : SINT := 0;
    Kids : ARRAY [0..15] OF TPos8 := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  END_STRUCT;
  TDir : (DIR_UP, DIR_DOWN);
  TIter : STRUCT
    dir : TDir := DIR_UP;
    prev : TPos8 := -1;
    item : TPos8 := -1;
    next : TPos8 := -1;
    last : TPos8 := -1;
    stack : ARRAY [0..3] OF TPos8 := [0, 0, 0, 0];
  END_STRUCT;
  P_RESI : STRUCT
    A : REAL := 0.0;
    B : SINT := 0;
  END_STRUCT;
  TPos16 : INT := -1;
  TProps : STRUCT
    Air : BOOL := false;
    Oil : BOOL := false;
    Fluid : BOOL := false;
    Solid : BOOL := false;
  END_STRUCT;
  P_SIBT : STRUCT
    A : SINT := 0;
    B : BYTE := 0;
  END_STRUCT;
  TAxO : STRUCT
    x : USINT := 0;
    y : USINT := 0;
    z : USINT := 0;
  END_STRUCT;
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := DEBUG;
  TKnot : ARRAY [0..2] OF INT := [0, 0, 0];
  TPoint : ARRAY [0..2] OF REAL;
  TShape : STRUCT
    wF : WORD := 0;
    Kn : TKnot := [0, 0, 0];
    p0 : TPoint := [0.0, 0.0, 0.0];
    pL : TPoint := [0.0, 0.0, 0.0];
    Lx : TPoint := [0.0, 0.0, 0.0];
  END_STRUCT;
  P_UINT : STRUCT
    A : UINT := 0;
    B : UINT := 0;
  END_STRUCT;
  P_IDPIT : STRUCT
    A : UINT := 0;
    B : TPos8 := -1;
  END_STRUCT;
  TDot : STRUCT
    V : INT := 0;
    A : TKnot := [0, 0, 0];
  END_STRUCT;
  TCond : STRUCT
    ID : UINT := 0;
    Tmid : INT := 0;
    Tmin : TDot;
    Tmax : TDot;
  END_STRUCT;
  TGrid2 : STRUCT
    A : ARRAY [0..12543] OF TVar;
  END_STRUCT;
  TItems : STRUCT
    Pr : ARRAY [0..99] OF P_IDPIT := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    It : ARRAY [0..99] OF TItem := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Sh : ARRAY [0..100] OF TShape := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Cn : ARRAY [0..100] OF TCond := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Gr : ARRAY [0..99] OF TGrid := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Gr2 : ARRAY [0..1] OF TGrid2 := [0, 0];
  END_STRUCT;
  TError : (E_SUCCESS, E_ID, E_HEAD, E_INDEX, E_ITEMPOS, E_ITEM, E_GRID, E_AXIS, E_PRIO, E_MATER, E_PROFILE, E_VALUE, E_STACKSIZE, E_ROOT, E_ITEMSIZE, E_STEPSIZE, E_TIMESIZE, E_NOTREADY, E_STRUCT, E_VALIDATE, E_LOC2ABS, E_ABS2LOC, E_GETTEMP, E_SETTEMP, E_CHECKVALID, E_LINKITEMS, E_PROCESS, E_PREPROC, E_POSTPROC, E_BADTEMP, E_STATE, E_CHECK, E_FAIL, W_PERIOD) := E_SUCCESS;
  TVarI : STRUCT
    DTI : UDINT := 0;
    TMI : TIME := T#0s;
    TOV : REAL := 0.0;
    MHT : REAL := 0.0;
    RI1 : REAL := 0.0;
    RI2 : REAL := 0.0;
  END_STRUCT;
  TDef : STRUCT
    ID : UINT := 0;
    CF : WORD := 0;
    R0 : INT := 0;
    XYZ : ARRAY [0..2] OF INT := [0, 0, 0];
    LWH : ARRAY [0..2] OF INT := [100, 100, 100];
    Ig : SINT := 0;
    Im : SINT := 0;
    Iv : SINT := 0;
  END_STRUCT;
  TVarO : STRUCT
    DTO : UDINT := 0;
    TMO : TIME := T#0s;
    QTY : REAL := 0.0;
    QTS : REAL := 0.0;
    RO1 : REAL := 0.0;
    RO2 : REAL := 0.0;
  END_STRUCT;
  P_RERE : STRUCT
    A : REAL := 0.0;
    B : REAL := 0.0;
  END_STRUCT;
  TMat : STRUCT
    KT : REAL := 0.11;
    CP : REAL := 1666.0;
    PL : REAL := 880.3;
    MD : REAL := 198.1;
  END_STRUCT;
  TVal : STRUCT
    Iv : INT := 0;
    Vi : ARRAY [0..2] OF P_SINT := [0, 0, 0];
  END_STRUCT;
  TSets : STRUCT
    Mt : ARRAY [0..11] OF TMat := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Vl : ARRAY [0..24] OF TVal := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Pr : ARRAY [0..29] OF TProf := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    Bf : ARRAY [0..31] OF REAL := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  END_STRUCT;
  TPhaseO : STRUCT
    Q0 : REAL := 0.0;
    Q1 : REAL := 0.0;
    Q2 : REAL := 0.0;
    Tin : REAL := 20.0;
    Tout : REAL := 80.0;
    Qm : REAL := 0.01;
    Se : REAL := 0.01;
    Ve : REAL := 0.01;
  END_STRUCT;
  TPhaseI : STRUCT
    Ic : REAL := 100.0;
    Tin : REAL := 40.0;
    Tout : REAL := 80.0;
    Rn : DWORD := 16#FFFF;
    RD : ARRAY [0..7] OF P_SINT := [0, 0, 0, 0, 0, 0, 0, 0];
  END_STRUCT;
  TRad : STRUCT
    Vm : REAL := 0.02;
    Fk : REAL := 1.1;
    Q0 : REAL := 0.003;
    Q1 : REAL := 0.01;
    BL : ARRAY [0..3] OF REAL := [0.2, 0.6, 0.85, 1.0];
  END_STRUCT;
  TConf : STRUCT
    Nm : UINT := 0;
    Nr : UINT := 0;
    Tc : TIME := T#10s;
  END_STRUCT;
  TStat : STRUCT
    RDY : BOOL := FALSE;
    DBG : BOOL := TRUE;
    ERR : TError := E_SUCCESS;
    PAR : UINT := 0;
    STR : STRING := '';
  END_STRUCT;
  P_BOOL : STRUCT
    A : BOOL := false;
    B : BOOL := false;
  END_STRUCT;
  TRes : STRUCT
    DR : UDINT := 0;
    TR : TIME := T#0s;
    FP : TIME := T#0s;
    ER : UINT := 0;
    FL : WORD := 0;
    RV : ARRAY [0..5] OF UDINT := [0, 0, 0, 0, 0, 0];
  END_STRUCT;
  THead : STRUCT
    Ni : SINT := 0;
    Ng : SINT := 0;
    Nm : SINT := 0;
    Nv : SINT := 0;
    Np : SINT := 0;
    Ri : SINT := 0;
    ID : UINT := 0;
    TR : ARRAY [0..3] OF TIME := [T#60s, T#30s, T#10s, T#5s];
    Ax : UINT := 0;
    pX : INT := 0;
    pY : INT := 0;
    pZ : INT := 0;
    RV : ARRAY [0..1] OF DINT := [0, 0];
  END_STRUCT;
END_TYPE

FUNCTION is_parent : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (IS_PARENT = (__GET_GLOBAL_ITS()->IT.table[PIT].NUM > 0)); }}
END_FUNCTION

FUNCTION Err2Lev : LOGLEVEL
  VAR_INPUT
    Err : TError := E_SUCCESS;
  END_VAR

  CASE Err OF
  E_SUCCESS:  
    Err2Lev:=INFO;  
  W_PERIOD:   
    Err2Lev:=WARNING;  
  ELSE        
    Err2Lev:=CRITICAL;  
  END_CASE;
  RETURN;
END_FUNCTION

FUNCTION st_check : BOOL
  VAR_INPUT
    Force : BOOL := FALSE;
  END_VAR

  {{ 
    return (
      ST_CHECK = ( 
        FORCE || (ERR2LEV(1,NULL,__GET_GLOBAL_STAT()->ERR) != LOGLEVEL__CRITICAL) 
      )
    ); 
  }}
END_FUNCTION

FUNCTION m_var_out : TVarO
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
  END_VAR

  m_var_out.DTO := MD0;  (* секунд от 01-01-1970 *)
  m_var_out.TMO := UDINT_TO_TIME(MD1);
  m_var_out.QTY := UDINT_TO_REAL(MD2);
  m_var_out.QTS := UDINT_TO_REAL(MD3);
  m_var_out.RO1 := UDINT_TO_REAL(MD4);
  m_var_out.RO2 := UDINT_TO_REAL(MD5);
END_FUNCTION

FUNCTION m_rad : TRad
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
  END_VAR

  m_rad.Vm := UDINT_TO_REAL(MD0);
  m_rad.Fk := UDINT_TO_REAL(MD1);
  m_rad.Q0 := UDINT_TO_REAL(MD2);
  m_rad.Q1 := UDINT_TO_REAL(MD3);
  m_rad.BL[0] := UDINT_TO_REAL(MD4);
  m_rad.BL[1] := UDINT_TO_REAL(MD5);
  m_rad.BL[2] := UDINT_TO_REAL(MD6);
  m_rad.BL[3] := UDINT_TO_REAL(MD7);
END_FUNCTION

FUNCTION it_lev : SINT
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    IID : UINT := 16#ffff;
  END_VAR

  {{
    IID = __GET_GLOBAL_ITS()->IT.table[PIT].ID;
    if (IID==0 || IID==0xffff) return (IT_LEV=-1);
    IT_LEV = 3;
    if (IID & 0x000F) return(IT_LEV); IT_LEV--;
    if (IID & 0x00F0) return(IT_LEV); IT_LEV--;
    if (IID & 0x0F00) return(IT_LEV); IT_LEV--;
  }}
END_FUNCTION

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

FUNCTION halt : BOOL
  VAR_INPUT
    ERR : TError := E_FAIL;
  END_VAR

  (* Использует вызов sleep() и exit() для завершения потоков *)
  {{
    //#ifndef __ASSERT_H
    //#define __ASSERT_H 1
       //#include <unistd.h> // Include "unistd.h" for sleep() & exit() function
    //#endif // __ASSERT_H
    //sleep(3); // Wait for message logging..
    //exit(ERR);
  }}
END_FUNCTION

FUNCTION MakeMsg : STRING
  VAR_INPUT
    S0 : STRING := '';
    S1 : STRING := '';
    S2 : STRING := '';
    S3 : STRING := '';
  END_VAR
  VAR
    BLOG : BOOL := FALSE;
  END_VAR

  {{ BLOG = __GET_GLOBAL_STAT()->DBG; }}
  if (BLOG) then 
    MakeMsg:=concat(concat(concat(S0, S1), S2), S3); 
  else 
    MakeMsg:=''; 
  end_if;
END_FUNCTION

FUNCTION assert : BOOL
  VAR_INPUT
    STAT : BOOL := FALSE;
    ERR : TError := E_FAIL;
    STR : STRING := '';
  END_VAR

  {{
  //  #ifndef __ASSERT_H
  //  #define __ASSERT_H 1
  //     #include <unistd.h> // Include "unistd.h" for sleep() & exit() function
  //     #include <assert.h> // Include "unistd.h" for sleep() & exit() function
  //  #endif // __ASSERT_H
    if (!(ASSERT=STAT)) { 
      STR = MAKEMSG(1, NULL, 
        __STRING_LITERAL(27,"OpenPLC: ASSERTION FAILED! "), 
        STR,
        __INIT_STRING,
        __INIT_STRING
      );
      LOGMSG(1, NULL, STR, LOGLEVEL__CRITICAL, ERR); 
      //HALT(1, NULL, ERR);
      //sleep(3); // Wait for message logging..
      //exit(ERR);
  //    assert(0);
    }
  }}
END_FUNCTION

FUNCTION it_pos : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
    bForce : BOOL := false;
  END_VAR

  {{ 
    if (BFORCE) {
      ASSERT(1, NULL, 
       (PIT >= 0) && (PIT < __GET_GLOBAL_HDR()->NI), TERROR__E_ITEMPOS, __INIT_STRING);
    }
    return (IT_POS = ( (PIT < 0) || (PIT >= __GET_GLOBAL_HDR()->NI) ? (0) : PIT ));
  }}
END_FUNCTION

FUNCTION it_end : TIter
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ 
    return (IT_END = ((TITER){ TDIR__DIR_UP, -1, -1, -1, -1, {0,0,0,0} } )); 
  }}
END_FUNCTION

FUNCTION it_next : TIter
  VAR_INPUT
    it : TIter;
  END_VAR

  {{ 
    /* Алгоритм обхода:
      1) Если предыдущий узел - родительский для этого узла 
         -> переходим к первому дочернему узлу (если нет->к родителю);
      2) Если предыдущий узел - дочерний для этого узла  
         -> переходим к следующему дочернему узлу (если нет->к родителю) 
    */
    SINT iSub = 0;
    SINT iLevel = 0;
    BOOL bBreak = FALSE;
    TITEM *Items = &(__GET_GLOBAL_ITS()->IT.table[0]);
    
    while (!bBreak && IT.ITEM!=(-1)) { 
      IT.ITEM = IT.NEXT;  // Переход к следующему элементу
      if (IT.ITEM!=(-1)) {
        // Запоминаем уровень текущего узла в стеке со смещением +1
        iLevel = IT_LEV(1,NULL,IT.ITEM)+1; 
        
        // Определение следующего узла
        if (IT.PREV == Items[IT.ITEM].PAR) {
          // предыдущий узел является является родительским узлом этого узла ->
          iSub = 0;
          if (Items[IT.ITEM].NUM > iSub) { 
            // ВНИЗ -> к первому дочернему узлу (если есть)
            IT.NEXT = Items[IT.ITEM].KIDS.table[iSub];
            IT.STACK.table[iLevel] = iSub;
            IT.DIR = TDIR__DIR_DOWN;  // Актуально если есть потомки
            bBreak = TRUE; 
          } else {    
            // ВВЕРХ -> к родителю (потомков нет)
            IT.NEXT = (IT.ITEM != IT.LAST) ? IT.NEXT = Items[IT.ITEM].PAR : (-1);
            IT.DIR = TDIR__DIR_UP;    // Актуально для любого элемента
            bBreak = TRUE;
          }
        } else if (Items[IT.PREV].PAR == IT.ITEM) { 
          // предыдущий узел является дочерним узлом этого узла ->
          iSub = IT.STACK.table[iLevel]+1;
          if (iSub < Items[IT.ITEM].NUM) {
            // ПО ГОРИЗОНТАЛИ -> к следующему дочернему узлу (если есть)
            IT.NEXT = Items[IT.ITEM].KIDS.table[iSub];
            IT.STACK.table[iLevel] = iSub;
          } else {
            // ВВЕРХ -> к родителю (потомков больше нет)
            IT.NEXT = (IT.ITEM != IT.LAST) ? IT.NEXT = Items[IT.ITEM].PAR : (-1);
            IT.DIR = TDIR__DIR_UP;
            bBreak = TRUE;
          }
        } else {
          //ASSERT(1,NULL,FALSE, TERROR__E_FAIL, 
            //__STRING_LITERAL(24,"it_next: Bad struct!"));
          return (IT_NEXT = IT_END(1,NULL,-1)); // так не бывает - ошибка структуры!!!
        }
      }
      IT.PREV = IT.ITEM;  // Сохранение текущего узла
    }
    return (IT_NEXT = IT);
  }}
END_FUNCTION

FUNCTION it_begin : TIter
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    bValid : BOOL := true;
  END_VAR

  (* Инициализация итератора *)
  {{
    BOOL bValid = (PIT >= 0 && PIT < __GET_GLOBAL_HDR()->NI);
    if (bValid) {
      IT_BEGIN.PREV = __GET_GLOBAL_ITS()->IT.table[PIT].PAR;
      IT_BEGIN.ITEM = IT_BEGIN.NEXT = IT_BEGIN.LAST = PIT;
      // Если позиция начала верна - делаем первую итерацию
      return (IT_BEGIN = IT_NEXT(1,NULL,IT_BEGIN));
    } else 
        // Если позиция не верна - переход в конечное состояние
        return (IT_BEGIN = IT_END(1,NULL,(-1)));
  }}
END_FUNCTION

FUNCTION C2T : REAL
  VAR_INPUT
    Code : INT := 0;
  END_VAR

  C2T := int_to_real(Code)/100.0;
END_FUNCTION

FUNCTION is_poly : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ 
    return (IS_POLY = (__GET_GLOBAL_ITS()->IT.table[PIT].NUM > 0)); 
  }}
END_FUNCTION

FUNCTION ID2Str : STRING
  VAR_INPUT
    IID : UINT;
  END_VAR
  VAR
    i : USINT;
    IDs : ARRAY [0..3] OF USINT;
    ch : ARRAY [0..3] OF STRING;
  END_VAR

  (* Распаковка идентификатора элемента на отдельные байты *)
  IDs[0]  := WORD_TO_USINT(SHR((UINT_TO_WORD(IID) and 16#F000),12));
  IDs[1]  := WORD_TO_USINT(SHR((UINT_TO_WORD(IID) and 16#0F00), 8));
  IDs[2]  := WORD_TO_USINT(SHR((UINT_TO_WORD(IID) and 16#00F0), 4));
  IDs[3]  := WORD_TO_USINT(SHR((UINT_TO_WORD(IID) and 16#000F), 0));
  (* Замена цифр на символы *)
  for i:=0 to 3 do
    case (IDs[i]-10) of
    0: ch[i]:='A';
    1: ch[i]:='B';
    2: ch[i]:='C';
    3: ch[i]:='D';
    4: ch[i]:='E';
    5: ch[i]:='F';
    else ch[i]:=USINT_TO_STRING(IDs[i]);
    end_case;
  end_for;
  (* Сборка идентификатора *)
  ID2Str := MakeMsg(ch[0], ch[1], ch[2], ch[3]);
END_FUNCTION

FUNCTION it_id : UINT
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (IT_ID = __GET_GLOBAL_ITS()->IT.table[PIT].ID); }}
END_FUNCTION

FUNCTION _knot : TKnot
  VAR_INPUT
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
  END_VAR

  _knot[0] := I; 
  _knot[1] := J; 
  _knot[2] := K; 
END_FUNCTION

FUNCTION _dot : TDot
  VAR_INPUT
    V : INT := 0;
    i : INT := 0;
    j : INT := 0;
    k : INT := 0;
  END_VAR

  _dot.V := V; 
  _dot.A := _knot(i,j,k); 
END_FUNCTION

FUNCTION _cond : TCond
  VAR_INPUT
    ID : UINT := 0;
    Tmid : INT := -1;
    Tmin : TDot;
    Tmax : TDot;
  END_VAR

  _COND.ID   := ID;
  _COND.TMID := TMID;
  _COND.TMIN := TMIN;
  _COND.TMAX := TMAX;
END_FUNCTION

FUNCTION get_cn : TCond
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ 
    return (GET_CN = 
      (
        (PIT != -1) ? 
        __GET_GLOBAL_ITS()->CN.table[PIT] 
        : _COND(1, NULL, 0, 2000, _DOT(1,NULL,2000,0,0,0), _DOT(1,NULL,2000,0,0,0))
      )
    ); 
  }}
END_FUNCTION

FUNCTION IT_CondStr : STRING
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    Cond : TCond;
    bP : BOOL := FALSE;
    msg : STRING := '';
  END_VAR

  Cond := get_cn(it_pos(PIT));
  if (is_poly(PIT)) then
    msg := MakeMsg(msg, ' [', ID2Str(IT_ID(PIT)), ',');
    msg := MakeMsg(msg,       SINT_TO_STRING(PIT), ',');
    msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmid)) ), ',');
    (* msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmin.V)) ), ']'); *)
    msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmax.V)) ), ']');
  else 
    msg := MakeMsg(msg, ' (', ID2Str(IT_ID(PIT)), ',');
    msg := MakeMsg(msg,       SINT_TO_STRING(PIT), ',');
    msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmid)) ), ',');
    (* msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmin.V)) ), ']'); *)
    msg := MakeMsg(msg, INT_TO_STRING( REAL_TO_INT(C2T(Cond.Tmax.V)) ), ')');
  end_if;
  IT_CondStr:=msg;
END_FUNCTION

FUNCTION Do_LogCond : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
    msg : STRING := '';
    i : SINT := 0;
  END_VAR

  Do_LogCond := st_check(false);
  if (not Do_LogCond) then return; end_if;
  (* Обход дерева элементов *)
  i:=0;
  it := it_begin(it_pos(PIT));
  while (it.item <>-1) do
    if (len(msg)=0) then msg := MakeMsg(' -> '); end_if;
    case (it.dir) of
    DIR_UP:
      (*if (not it_parent(it.item)) then*) (* состояние терминального элемента *)
        msg := MakeMsg(msg, IT_CondStr(it.item));
        if (mod((i+1),5)=0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
        i := i+1;
      (*end_if;*)
    end_case;
    it := it_next(it);
  end_while;
  if (len(msg)>0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
  msg:=LogMsg(' --- ');
  (*Do_LogCond := true;*)
END_FUNCTION

FUNCTION set_var : TPos8
  VAR_INPUT
    HGR : THandle := 0;
    PGR : TPos8 := -1;
    OFF : P_INT;
    TV : TVar := -1;
    IX : USINT := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)
    
    // Получаем массив сеток по дескриптору  
    TGRID *Grids = (TGRID *)(HGR);
    
    if (IX == 0xFF) { // Направление не задано  - заполнение ячеек узла шаблоном TV
    
      for (short int k=0; k < OFF.B; k++) {
        Grids[PGR].A.table[OFF.A+k] = TV;
      }    
      
    } else {          //  Направление задано =>
      if (IX == 0) {    // Главная ячейка (IX == 0)
        Grids[PGR].A.table[OFF.A] = TV;
        /*
        pvar_t pDest = (var_t *) &Grids[PGR].A.table[OFF.A];
        pvar_t pvar  = (var_t *) &TV;
        if (pvar->r) *pDest = *pvar;
        else {
          // if (pvar->A != -16384) 
            pDest->A = pvar->A;
            
          // if (pvar->B != -16384) 
            pDest->B = pvar->B;
            
          pDest->C = pvar->C;
        }
        */
      } else {          // Смежная ячейка (IX > 0)
      
        // В смежных ячейках могут быть только ссылки или воздух (-1)
        // ASSERT(1,NULL,((pvar_t)&TV)->r,TERROR__E_FAIL, 
          //__STRING_LITERAL(29,"it_var_set: Reference wanted!"));
        
        pvar_t pDest = NULL;
        for (short int k=1; k < OFF.B; k++) {
          pvar_t pvar = (var_t *) &Grids[PGR].A.table[OFF.A+k];
          if ((pDest==NULL && pvar->d==0) || pvar->d == IX) {
            pDest = pvar;
            if (pDest->d == IX) break;
          }
        }
        
        // Ячейка должна найтись!!!
        //ASSERT(1,NULL,pDest!=NULL,TERROR__E_FAIL,
          //_STRING_LITERAL(26, "it_var_set: Cell not found!"));
          
        //if (pDest!=NULL) {
          pDest->tv = TV; 
          pDest->d  = IX;  // Значение IX перезаписывается
        //}
      }
    }
    SET_VAR = PGR;
  }}
END_FUNCTION

FUNCTION_BLOCK DistCond
  VAR_OUTPUT
    MD0 : UDINT := 0;
    MD1 : UDINT := 0;
    MD2 : UDINT := 0;
    MD3 : UDINT := 0;
    MD4 : UDINT := 0;
  END_VAR
  VAR_INPUT
    COND : TCond;
  END_VAR

  MD0 := UINT_TO_UDINT(COND.ID)*65536 + INT_TO_UDINT(COND.Tmid);

  MD1 := INT_TO_UDINT(COND.Tmin.A[0])*65536 + INT_TO_UDINT(COND.Tmin.A[1]);
  MD2 := INT_TO_UDINT(COND.Tmin.A[2])*65536 + INT_TO_UDINT(COND.Tmin.V);

  MD3 := INT_TO_UDINT(COND.Tmax.A[0])*65536 + INT_TO_UDINT(COND.Tmax.A[1]);
  MD4 := INT_TO_UDINT(COND.Tmax.A[2])*65536 + INT_TO_UDINT(COND.Tmax.V);
END_FUNCTION_BLOCK

FUNCTION_BLOCK SetCond
  VAR_EXTERNAL
    MW1000 : UINT;
    MW1001 : UINT;
    MW1002 : UINT;
    MW1003 : UINT;
    MW1004 : UINT;
    MW1005 : UINT;
    MW1006 : UINT;
    MW1007 : UINT;
    MW1008 : UINT;
    MW1009 : UINT;
    MD500 : UDINT;
    MD501 : UDINT;
    MD502 : UDINT;
    MD503 : UDINT;
    MD504 : UDINT;
    MD505 : UDINT;
    MD506 : UDINT;
    MD507 : UDINT;
    MD508 : UDINT;
    MD509 : UDINT;
    MD510 : UDINT;
    MD511 : UDINT;
    MD512 : UDINT;
    MD513 : UDINT;
    MD514 : UDINT;
    MD515 : UDINT;
    MD516 : UDINT;
    MD517 : UDINT;
    MD518 : UDINT;
    MD519 : UDINT;
    MD520 : UDINT;
    MD521 : UDINT;
    MD522 : UDINT;
    MD523 : UDINT;
    MD524 : UDINT;
    MD525 : UDINT;
    MD526 : UDINT;
    MD527 : UDINT;
    MD528 : UDINT;
    MD529 : UDINT;
    MD530 : UDINT;
    MD531 : UDINT;
    MD532 : UDINT;
    MD533 : UDINT;
    MD534 : UDINT;
    MD535 : UDINT;
    MD536 : UDINT;
    MD537 : UDINT;
    MD538 : UDINT;
    MD539 : UDINT;
    MD540 : UDINT;
    MD541 : UDINT;
    MD542 : UDINT;
    MD543 : UDINT;
    MD544 : UDINT;
    MD545 : UDINT;
    MD546 : UDINT;
    MD547 : UDINT;
    MD548 : UDINT;
    MD549 : UDINT;
    MD550 : UDINT;
    MD551 : UDINT;
    MD552 : UDINT;
    MD553 : UDINT;
    MD554 : UDINT;
    MD555 : UDINT;
    MD556 : UDINT;
    MD557 : UDINT;
    MD558 : UDINT;
    MD559 : UDINT;
    MD560 : UDINT;
    MD561 : UDINT;
    MD562 : UDINT;
    MD563 : UDINT;
    MD564 : UDINT;
    MD565 : UDINT;
    MD566 : UDINT;
    MD567 : UDINT;
    MD568 : UDINT;
    MD569 : UDINT;
    MD570 : UDINT;
    MD571 : UDINT;
    MD572 : UDINT;
    MD573 : UDINT;
    MD574 : UDINT;
    MD575 : UDINT;
    MD576 : UDINT;
    MD577 : UDINT;
    MD578 : UDINT;
    MD579 : UDINT;
    MD580 : UDINT;
    MD581 : UDINT;
    MD582 : UDINT;
    MD583 : UDINT;
    MD584 : UDINT;
    MD585 : UDINT;
    MD586 : UDINT;
    MD587 : UDINT;
    MD588 : UDINT;
    MD589 : UDINT;
    MD590 : UDINT;
    MD591 : UDINT;
    MD592 : UDINT;
    MD593 : UDINT;
    MD594 : UDINT;
    MD595 : UDINT;
    MD596 : UDINT;
    MD597 : UDINT;
    MD598 : UDINT;
    MD599 : UDINT;
    MD600 : UDINT;
    MD601 : UDINT;
    MD602 : UDINT;
    MD603 : UDINT;
    MD604 : UDINT;
    MD605 : UDINT;
    MD606 : UDINT;
    MD607 : UDINT;
    MD608 : UDINT;
    MD609 : UDINT;
    MD610 : UDINT;
    MD611 : UDINT;
    MD612 : UDINT;
    MD613 : UDINT;
    MD614 : UDINT;
    MD615 : UDINT;
    MD616 : UDINT;
    MD617 : UDINT;
    MD618 : UDINT;
    MD619 : UDINT;
    MD620 : UDINT;
    MD621 : UDINT;
    MD622 : UDINT;
    MD623 : UDINT;
    MD624 : UDINT;
    MD625 : UDINT;
    MD626 : UDINT;
    MD627 : UDINT;
    MD628 : UDINT;
    MD629 : UDINT;
    MD630 : UDINT;
    MD631 : UDINT;
    MD632 : UDINT;
    MD633 : UDINT;
    MD634 : UDINT;
    MD635 : UDINT;
    MD636 : UDINT;
    MD637 : UDINT;
    MD638 : UDINT;
    MD639 : UDINT;
    MD640 : UDINT;
    MD641 : UDINT;
    MD642 : UDINT;
    MD643 : UDINT;
    MD644 : UDINT;
    MD645 : UDINT;
    MD646 : UDINT;
    MD647 : UDINT;
    MD648 : UDINT;
    MD649 : UDINT;
    MD650 : UDINT;
    MD651 : UDINT;
    MD652 : UDINT;
    MD653 : UDINT;
    MD654 : UDINT;
    MD655 : UDINT;
    MD656 : UDINT;
    MD657 : UDINT;
    MD658 : UDINT;
    MD659 : UDINT;
    MD660 : UDINT;
    MD661 : UDINT;
    MD662 : UDINT;
    MD663 : UDINT;
    MD664 : UDINT;
    MD665 : UDINT;
    MD666 : UDINT;
    MD667 : UDINT;
    MD668 : UDINT;
    MD669 : UDINT;
    MD670 : UDINT;
    MD671 : UDINT;
    MD672 : UDINT;
    MD673 : UDINT;
    MD674 : UDINT;
    MD675 : UDINT;
    MD676 : UDINT;
    MD677 : UDINT;
    MD678 : UDINT;
    MD679 : UDINT;
    MD680 : UDINT;
    MD681 : UDINT;
    MD682 : UDINT;
    MD683 : UDINT;
    MD684 : UDINT;
    MD685 : UDINT;
    MD686 : UDINT;
    MD687 : UDINT;
    MD688 : UDINT;
    MD689 : UDINT;
    MD690 : UDINT;
    MD691 : UDINT;
    MD692 : UDINT;
    MD693 : UDINT;
    MD694 : UDINT;
    MD695 : UDINT;
    MD696 : UDINT;
    MD697 : UDINT;
    MD698 : UDINT;
    MD699 : UDINT;
    MD700 : UDINT;
    MD701 : UDINT;
    MD702 : UDINT;
    MD703 : UDINT;
    MD704 : UDINT;
    MD705 : UDINT;
    MD706 : UDINT;
    MD707 : UDINT;
    MD708 : UDINT;
    MD709 : UDINT;
    MD710 : UDINT;
    MD711 : UDINT;
    MD712 : UDINT;
    MD713 : UDINT;
    MD714 : UDINT;
    MD715 : UDINT;
    MD716 : UDINT;
    MD717 : UDINT;
    MD718 : UDINT;
    MD719 : UDINT;
    MD720 : UDINT;
    MD721 : UDINT;
    MD722 : UDINT;
    MD723 : UDINT;
    MD724 : UDINT;
    MD725 : UDINT;
    MD726 : UDINT;
    MD727 : UDINT;
    MD728 : UDINT;
    MD729 : UDINT;
    MD730 : UDINT;
    MD731 : UDINT;
    MD732 : UDINT;
    MD733 : UDINT;
    MD734 : UDINT;
    MD735 : UDINT;
    MD736 : UDINT;
    MD737 : UDINT;
    MD738 : UDINT;
    MD739 : UDINT;
    MD740 : UDINT;
    MD741 : UDINT;
    MD742 : UDINT;
    MD743 : UDINT;
    MD744 : UDINT;
    MD745 : UDINT;
    MD746 : UDINT;
    MD747 : UDINT;
    MD748 : UDINT;
    MD749 : UDINT;
    MD750 : UDINT;
    MD751 : UDINT;
    MD752 : UDINT;
    MD753 : UDINT;
    MD754 : UDINT;
    MD755 : UDINT;
    MD756 : UDINT;
    MD757 : UDINT;
    MD758 : UDINT;
    MD759 : UDINT;
    MD760 : UDINT;
    MD761 : UDINT;
    MD762 : UDINT;
    MD763 : UDINT;
    MD764 : UDINT;
    MD765 : UDINT;
    MD766 : UDINT;
    MD767 : UDINT;
    MD768 : UDINT;
    MD769 : UDINT;
    MD770 : UDINT;
    MD771 : UDINT;
    MD772 : UDINT;
    MD773 : UDINT;
    MD774 : UDINT;
    MD775 : UDINT;
    MD776 : UDINT;
    MD777 : UDINT;
    MD778 : UDINT;
    MD779 : UDINT;
    MD780 : UDINT;
    MD781 : UDINT;
    MD782 : UDINT;
    MD783 : UDINT;
    MD784 : UDINT;
    MD785 : UDINT;
    MD786 : UDINT;
    MD787 : UDINT;
    MD788 : UDINT;
    MD789 : UDINT;
    MD790 : UDINT;
    MD791 : UDINT;
    MD792 : UDINT;
    MD793 : UDINT;
    MD794 : UDINT;
    MD795 : UDINT;
    MD796 : UDINT;
    MD797 : UDINT;
    MD798 : UDINT;
    MD799 : UDINT;
    MD800 : UDINT;
    MD801 : UDINT;
    MD802 : UDINT;
    MD803 : UDINT;
    MD804 : UDINT;
    MD805 : UDINT;
    MD806 : UDINT;
    MD807 : UDINT;
    MD808 : UDINT;
    MD809 : UDINT;
    MD810 : UDINT;
    MD811 : UDINT;
    MD812 : UDINT;
    MD813 : UDINT;
    MD814 : UDINT;
    MD815 : UDINT;
    MD816 : UDINT;
    MD817 : UDINT;
    MD818 : UDINT;
    MD819 : UDINT;
    MD820 : UDINT;
    MD821 : UDINT;
    MD822 : UDINT;
    MD823 : UDINT;
    MD824 : UDINT;
    MD825 : UDINT;
    MD826 : UDINT;
    MD827 : UDINT;
    MD828 : UDINT;
    MD829 : UDINT;
    MD830 : UDINT;
    MD831 : UDINT;
    MD832 : UDINT;
    MD833 : UDINT;
    MD834 : UDINT;
    MD835 : UDINT;
    MD836 : UDINT;
    MD837 : UDINT;
    MD838 : UDINT;
    MD839 : UDINT;
    MD840 : UDINT;
    MD841 : UDINT;
    MD842 : UDINT;
    MD843 : UDINT;
    MD844 : UDINT;
    MD845 : UDINT;
    MD846 : UDINT;
    MD847 : UDINT;
    MD848 : UDINT;
    MD849 : UDINT;
    MD850 : UDINT;
    MD851 : UDINT;
    MD852 : UDINT;
    MD853 : UDINT;
    MD854 : UDINT;
    MD855 : UDINT;
    MD856 : UDINT;
    MD857 : UDINT;
    MD858 : UDINT;
    MD859 : UDINT;
    MD860 : UDINT;
    MD861 : UDINT;
    MD862 : UDINT;
    MD863 : UDINT;
    MD864 : UDINT;
    MD865 : UDINT;
    MD866 : UDINT;
    MD867 : UDINT;
    MD868 : UDINT;
    MD869 : UDINT;
    MD870 : UDINT;
    MD871 : UDINT;
    MD872 : UDINT;
    MD873 : UDINT;
    MD874 : UDINT;
    MD875 : UDINT;
    MD876 : UDINT;
    MD877 : UDINT;
    MD878 : UDINT;
    MD879 : UDINT;
    MD880 : UDINT;
    MD881 : UDINT;
    MD882 : UDINT;
    MD883 : UDINT;
    MD884 : UDINT;
    MD885 : UDINT;
    MD886 : UDINT;
    MD887 : UDINT;
    MD888 : UDINT;
    MD889 : UDINT;
    MD890 : UDINT;
    MD891 : UDINT;
    MD892 : UDINT;
    MD893 : UDINT;
    MD894 : UDINT;
    MD895 : UDINT;
    MD896 : UDINT;
    MD897 : UDINT;
    MD898 : UDINT;
    MD899 : UDINT;
    MD900 : UDINT;
    MD901 : UDINT;
    MD902 : UDINT;
    MD903 : UDINT;
    MD904 : UDINT;
    MD905 : UDINT;
    MD906 : UDINT;
    MD907 : UDINT;
    MD908 : UDINT;
    MD909 : UDINT;
    MD910 : UDINT;
    MD911 : UDINT;
    MD912 : UDINT;
    MD913 : UDINT;
    MD914 : UDINT;
    MD915 : UDINT;
    MD916 : UDINT;
    MD917 : UDINT;
    MD918 : UDINT;
    MD919 : UDINT;
    MD920 : UDINT;
    MD921 : UDINT;
    MD922 : UDINT;
    MD923 : UDINT;
    MD924 : UDINT;
    MD925 : UDINT;
    MD926 : UDINT;
    MD927 : UDINT;
    MD928 : UDINT;
    MD929 : UDINT;
    MD930 : UDINT;
    MD931 : UDINT;
    MD932 : UDINT;
    MD933 : UDINT;
    MD934 : UDINT;
    MD935 : UDINT;
    MD936 : UDINT;
    MD937 : UDINT;
    MD938 : UDINT;
    MD939 : UDINT;
    MD940 : UDINT;
    MD941 : UDINT;
    MD942 : UDINT;
    MD943 : UDINT;
    MD944 : UDINT;
    MD945 : UDINT;
    MD946 : UDINT;
    MD947 : UDINT;
    MD948 : UDINT;
    MD949 : UDINT;
    MD950 : UDINT;
    MD951 : UDINT;
    MD952 : UDINT;
    MD953 : UDINT;
    MD954 : UDINT;
    MD955 : UDINT;
    MD956 : UDINT;
    MD957 : UDINT;
    MD958 : UDINT;
    MD959 : UDINT;
    MD960 : UDINT;
    MD961 : UDINT;
    MD962 : UDINT;
    MD963 : UDINT;
    MD964 : UDINT;
    MD965 : UDINT;
    MD966 : UDINT;
    MD967 : UDINT;
    MD968 : UDINT;
    MD969 : UDINT;
    MD970 : UDINT;
    MD971 : UDINT;
    MD972 : UDINT;
    MD973 : UDINT;
    MD974 : UDINT;
    MD975 : UDINT;
    MD976 : UDINT;
    MD977 : UDINT;
    MD978 : UDINT;
    MD979 : UDINT;
    MD980 : UDINT;
    MD981 : UDINT;
    MD982 : UDINT;
    MD983 : UDINT;
    MD984 : UDINT;
    MD985 : UDINT;
    MD986 : UDINT;
    MD987 : UDINT;
    MD988 : UDINT;
    MD989 : UDINT;
    MD990 : UDINT;
    MD991 : UDINT;
    MD992 : UDINT;
    MD993 : UDINT;
    MD994 : UDINT;
    MD995 : UDINT;
    MD996 : UDINT;
    MD997 : UDINT;
    MD998 : UDINT;
    MD999 : UDINT;
  END_VAR
  VAR_INPUT
    I : UINT := 0;
    COND : TCond;
  END_VAR
  VAR
    DIST : DistCond;
    msg : STRING := '';
  END_VAR

  CASE i OF
  0  : DIST(COND:=COND,MD0=>MD500,MD1=>MD501,MD2=>MD502,MD3=>MD503,MD4=>MD504);
  1  : DIST(COND:=COND,MD0=>MD505,MD1=>MD506,MD2=>MD507,MD3=>MD508,MD4=>MD509);
  2  : DIST(COND:=COND,MD0=>MD510,MD1=>MD511,MD2=>MD512,MD3=>MD513,MD4=>MD514);
  3  : DIST(COND:=COND,MD0=>MD515,MD1=>MD516,MD2=>MD517,MD3=>MD518,MD4=>MD519);
  4  : DIST(COND:=COND,MD0=>MD520,MD1=>MD521,MD2=>MD522,MD3=>MD523,MD4=>MD524);
  5  : DIST(COND:=COND,MD0=>MD525,MD1=>MD526,MD2=>MD527,MD3=>MD528,MD4=>MD529);
  6  : DIST(COND:=COND,MD0=>MD530,MD1=>MD531,MD2=>MD532,MD3=>MD533,MD4=>MD534);
  7  : DIST(COND:=COND,MD0=>MD535,MD1=>MD536,MD2=>MD537,MD3=>MD538,MD4=>MD539);
  8  : DIST(COND:=COND,MD0=>MD540,MD1=>MD541,MD2=>MD542,MD3=>MD543,MD4=>MD544);
  9  : DIST(COND:=COND,MD0=>MD545,MD1=>MD546,MD2=>MD547,MD3=>MD548,MD4=>MD549);

  10 : DIST(COND:=COND,MD0=>MD550,MD1=>MD551,MD2=>MD552,MD3=>MD553,MD4=>MD554);
  11 : DIST(COND:=COND,MD0=>MD555,MD1=>MD556,MD2=>MD557,MD3=>MD558,MD4=>MD559);
  12 : DIST(COND:=COND,MD0=>MD560,MD1=>MD561,MD2=>MD562,MD3=>MD563,MD4=>MD564);
  13 : DIST(COND:=COND,MD0=>MD565,MD1=>MD566,MD2=>MD567,MD3=>MD568,MD4=>MD569);
  14 : DIST(COND:=COND,MD0=>MD570,MD1=>MD571,MD2=>MD572,MD3=>MD573,MD4=>MD574);
  15 : DIST(COND:=COND,MD0=>MD575,MD1=>MD576,MD2=>MD577,MD3=>MD578,MD4=>MD579);
  16 : DIST(COND:=COND,MD0=>MD580,MD1=>MD581,MD2=>MD582,MD3=>MD583,MD4=>MD584);
  17 : DIST(COND:=COND,MD0=>MD585,MD1=>MD586,MD2=>MD587,MD3=>MD588,MD4=>MD589);
  18 : DIST(COND:=COND,MD0=>MD590,MD1=>MD591,MD2=>MD592,MD3=>MD593,MD4=>MD594);
  19 : DIST(COND:=COND,MD0=>MD595,MD1=>MD596,MD2=>MD597,MD3=>MD598,MD4=>MD599);

  20 : DIST(COND:=COND,MD0=>MD600,MD1=>MD601,MD2=>MD602,MD3=>MD603,MD4=>MD604);
  21 : DIST(COND:=COND,MD0=>MD605,MD1=>MD606,MD2=>MD607,MD3=>MD608,MD4=>MD609);
  22 : DIST(COND:=COND,MD0=>MD610,MD1=>MD611,MD2=>MD612,MD3=>MD613,MD4=>MD614);
  23 : DIST(COND:=COND,MD0=>MD615,MD1=>MD616,MD2=>MD617,MD3=>MD618,MD4=>MD619);
  24 : DIST(COND:=COND,MD0=>MD620,MD1=>MD621,MD2=>MD622,MD3=>MD623,MD4=>MD624);
  25 : DIST(COND:=COND,MD0=>MD625,MD1=>MD626,MD2=>MD627,MD3=>MD628,MD4=>MD629);
  26 : DIST(COND:=COND,MD0=>MD630,MD1=>MD631,MD2=>MD632,MD3=>MD633,MD4=>MD634);
  27 : DIST(COND:=COND,MD0=>MD635,MD1=>MD636,MD2=>MD637,MD3=>MD638,MD4=>MD639);
  28 : DIST(COND:=COND,MD0=>MD640,MD1=>MD641,MD2=>MD642,MD3=>MD643,MD4=>MD644);
  29 : DIST(COND:=COND,MD0=>MD645,MD1=>MD646,MD2=>MD647,MD3=>MD648,MD4=>MD649);

  30 : DIST(COND:=COND,MD0=>MD650,MD1=>MD651,MD2=>MD652,MD3=>MD653,MD4=>MD654);
  31 : DIST(COND:=COND,MD0=>MD655,MD1=>MD656,MD2=>MD657,MD3=>MD658,MD4=>MD659);
  32 : DIST(COND:=COND,MD0=>MD660,MD1=>MD661,MD2=>MD662,MD3=>MD663,MD4=>MD664);
  33 : DIST(COND:=COND,MD0=>MD665,MD1=>MD666,MD2=>MD667,MD3=>MD668,MD4=>MD669);
  34 : DIST(COND:=COND,MD0=>MD670,MD1=>MD671,MD2=>MD672,MD3=>MD673,MD4=>MD674);
  35 : DIST(COND:=COND,MD0=>MD675,MD1=>MD676,MD2=>MD677,MD3=>MD678,MD4=>MD679);
  36 : DIST(COND:=COND,MD0=>MD680,MD1=>MD681,MD2=>MD682,MD3=>MD683,MD4=>MD684);
  37 : DIST(COND:=COND,MD0=>MD685,MD1=>MD686,MD2=>MD687,MD3=>MD688,MD4=>MD689);
  38 : DIST(COND:=COND,MD0=>MD690,MD1=>MD691,MD2=>MD692,MD3=>MD693,MD4=>MD694);
  39 : DIST(COND:=COND,MD0=>MD695,MD1=>MD696,MD2=>MD697,MD3=>MD698,MD4=>MD699);

  40 : DIST(COND:=COND,MD0=>MD700,MD1=>MD701,MD2=>MD702,MD3=>MD703,MD4=>MD704);
  41 : DIST(COND:=COND,MD0=>MD705,MD1=>MD706,MD2=>MD707,MD3=>MD708,MD4=>MD709);
  42 : DIST(COND:=COND,MD0=>MD710,MD1=>MD711,MD2=>MD712,MD3=>MD713,MD4=>MD714);
  43 : DIST(COND:=COND,MD0=>MD715,MD1=>MD716,MD2=>MD717,MD3=>MD718,MD4=>MD719);
  44 : DIST(COND:=COND,MD0=>MD720,MD1=>MD721,MD2=>MD722,MD3=>MD723,MD4=>MD724);
  45 : DIST(COND:=COND,MD0=>MD725,MD1=>MD726,MD2=>MD727,MD3=>MD728,MD4=>MD729);
  46 : DIST(COND:=COND,MD0=>MD730,MD1=>MD731,MD2=>MD732,MD3=>MD733,MD4=>MD734);
  47 : DIST(COND:=COND,MD0=>MD735,MD1=>MD736,MD2=>MD737,MD3=>MD738,MD4=>MD739);
  48 : DIST(COND:=COND,MD0=>MD740,MD1=>MD741,MD2=>MD742,MD3=>MD743,MD4=>MD744);
  49 : DIST(COND:=COND,MD0=>MD745,MD1=>MD746,MD2=>MD747,MD3=>MD748,MD4=>MD749);

  50 : DIST(COND:=COND,MD0=>MD750,MD1=>MD751,MD2=>MD752,MD3=>MD753,MD4=>MD754);
  51 : DIST(COND:=COND,MD0=>MD755,MD1=>MD756,MD2=>MD757,MD3=>MD758,MD4=>MD759);
  52 : DIST(COND:=COND,MD0=>MD760,MD1=>MD761,MD2=>MD762,MD3=>MD763,MD4=>MD764);
  53 : DIST(COND:=COND,MD0=>MD765,MD1=>MD766,MD2=>MD767,MD3=>MD768,MD4=>MD769);
  (*TEST*)
  (*
  mw1000 := UDINT_TO_UINT(MD765/65536);
  mw1001 := UDINT_TO_UINT(mod(MD765,65536));

  mw1002 := UDINT_TO_UINT(MD766/65536);
  mw1003 := UDINT_TO_UINT(mod(MD766,65536));
  mw1004 := UDINT_TO_UINT(MD767/65536);
  mw1005 := UDINT_TO_UINT(mod(MD767,65536));

  mw1006 := UDINT_TO_UINT(MD768/65536);
  mw1007 := UDINT_TO_UINT(mod(MD768,65536));
  mw1008 := UDINT_TO_UINT(MD769/65536);
  mw1009 := UDINT_TO_UINT(mod(MD769,65536));

  msg := MakeMsg('= TEST2: Tmax.P(53) = [');
  msg := MakeMsg(msg, INT_TO_STRING(UINT_TO_INT(mw1006)), ',');
  msg := MakeMsg(msg, INT_TO_STRING(UINT_TO_INT(mw1007)), ',');
  msg := MakeMsg(msg, INT_TO_STRING(UINT_TO_INT(mw1008)), ']');
  msg := LogMsg (msg);
  *)
  54 : DIST(COND:=COND,MD0=>MD770,MD1=>MD771,MD2=>MD772,MD3=>MD773,MD4=>MD774);
  55 : DIST(COND:=COND,MD0=>MD775,MD1=>MD776,MD2=>MD777,MD3=>MD778,MD4=>MD779);
  56 : DIST(COND:=COND,MD0=>MD780,MD1=>MD781,MD2=>MD782,MD3=>MD783,MD4=>MD784);
  57 : DIST(COND:=COND,MD0=>MD785,MD1=>MD786,MD2=>MD787,MD3=>MD788,MD4=>MD789);
  58 : DIST(COND:=COND,MD0=>MD790,MD1=>MD791,MD2=>MD792,MD3=>MD793,MD4=>MD794);
  59 : DIST(COND:=COND,MD0=>MD795,MD1=>MD796,MD2=>MD797,MD3=>MD798,MD4=>MD799);

  60 : DIST(COND:=COND,MD0=>MD800,MD1=>MD801,MD2=>MD802,MD3=>MD803,MD4=>MD804);
  61 : DIST(COND:=COND,MD0=>MD805,MD1=>MD806,MD2=>MD807,MD3=>MD808,MD4=>MD809);
  62 : DIST(COND:=COND,MD0=>MD810,MD1=>MD811,MD2=>MD812,MD3=>MD813,MD4=>MD814);
  63 : DIST(COND:=COND,MD0=>MD815,MD1=>MD816,MD2=>MD817,MD3=>MD818,MD4=>MD819);
  64 : DIST(COND:=COND,MD0=>MD820,MD1=>MD821,MD2=>MD822,MD3=>MD823,MD4=>MD824);
  65 : DIST(COND:=COND,MD0=>MD825,MD1=>MD826,MD2=>MD827,MD3=>MD828,MD4=>MD829);
  66 : DIST(COND:=COND,MD0=>MD830,MD1=>MD831,MD2=>MD832,MD3=>MD833,MD4=>MD834);
  67 : DIST(COND:=COND,MD0=>MD835,MD1=>MD836,MD2=>MD837,MD3=>MD838,MD4=>MD839);
  68 : DIST(COND:=COND,MD0=>MD840,MD1=>MD841,MD2=>MD842,MD3=>MD843,MD4=>MD844);
  69 : DIST(COND:=COND,MD0=>MD845,MD1=>MD846,MD2=>MD847,MD3=>MD848,MD4=>MD849);

  70 : DIST(COND:=COND,MD0=>MD850,MD1=>MD851,MD2=>MD852,MD3=>MD853,MD4=>MD854);
  71 : DIST(COND:=COND,MD0=>MD855,MD1=>MD856,MD2=>MD857,MD3=>MD858,MD4=>MD859);
  72 : DIST(COND:=COND,MD0=>MD860,MD1=>MD861,MD2=>MD862,MD3=>MD863,MD4=>MD864);
  73 : DIST(COND:=COND,MD0=>MD865,MD1=>MD866,MD2=>MD867,MD3=>MD868,MD4=>MD869);
  74 : DIST(COND:=COND,MD0=>MD870,MD1=>MD871,MD2=>MD872,MD3=>MD873,MD4=>MD874);
  75 : DIST(COND:=COND,MD0=>MD875,MD1=>MD876,MD2=>MD877,MD3=>MD878,MD4=>MD879);
  76 : DIST(COND:=COND,MD0=>MD880,MD1=>MD881,MD2=>MD882,MD3=>MD883,MD4=>MD884);
  77 : DIST(COND:=COND,MD0=>MD885,MD1=>MD886,MD2=>MD887,MD3=>MD888,MD4=>MD889);
  78 : DIST(COND:=COND,MD0=>MD890,MD1=>MD891,MD2=>MD892,MD3=>MD893,MD4=>MD894);
  79 : DIST(COND:=COND,MD0=>MD895,MD1=>MD896,MD2=>MD897,MD3=>MD898,MD4=>MD899);

  80 : DIST(COND:=COND,MD0=>MD900,MD1=>MD901,MD2=>MD902,MD3=>MD903,MD4=>MD904);
  81 : DIST(COND:=COND,MD0=>MD905,MD1=>MD906,MD2=>MD907,MD3=>MD908,MD4=>MD909);
  82 : DIST(COND:=COND,MD0=>MD910,MD1=>MD911,MD2=>MD912,MD3=>MD913,MD4=>MD914);
  83 : DIST(COND:=COND,MD0=>MD915,MD1=>MD916,MD2=>MD917,MD3=>MD918,MD4=>MD919);
  84 : DIST(COND:=COND,MD0=>MD920,MD1=>MD921,MD2=>MD922,MD3=>MD923,MD4=>MD924);
  85 : DIST(COND:=COND,MD0=>MD925,MD1=>MD926,MD2=>MD927,MD3=>MD928,MD4=>MD929);
  86 : DIST(COND:=COND,MD0=>MD930,MD1=>MD931,MD2=>MD932,MD3=>MD933,MD4=>MD934);
  87 : DIST(COND:=COND,MD0=>MD935,MD1=>MD936,MD2=>MD937,MD3=>MD938,MD4=>MD939);
  88 : DIST(COND:=COND,MD0=>MD940,MD1=>MD941,MD2=>MD942,MD3=>MD943,MD4=>MD944);
  89 : DIST(COND:=COND,MD0=>MD945,MD1=>MD946,MD2=>MD947,MD3=>MD948,MD4=>MD949);

  90 : DIST(COND:=COND,MD0=>MD950,MD1=>MD951,MD2=>MD952,MD3=>MD953,MD4=>MD954);
  91 : DIST(COND:=COND,MD0=>MD955,MD1=>MD956,MD2=>MD957,MD3=>MD958,MD4=>MD959);
  92 : DIST(COND:=COND,MD0=>MD960,MD1=>MD961,MD2=>MD962,MD3=>MD963,MD4=>MD964);
  93 : DIST(COND:=COND,MD0=>MD965,MD1=>MD966,MD2=>MD967,MD3=>MD968,MD4=>MD969);
  94 : DIST(COND:=COND,MD0=>MD970,MD1=>MD971,MD2=>MD972,MD3=>MD973,MD4=>MD974);
  95 : DIST(COND:=COND,MD0=>MD975,MD1=>MD976,MD2=>MD977,MD3=>MD978,MD4=>MD979);
  96 : DIST(COND:=COND,MD0=>MD980,MD1=>MD981,MD2=>MD982,MD3=>MD983,MD4=>MD984);
  97 : DIST(COND:=COND,MD0=>MD985,MD1=>MD986,MD2=>MD987,MD3=>MD988,MD4=>MD989);
  98 : DIST(COND:=COND,MD0=>MD990,MD1=>MD991,MD2=>MD992,MD3=>MD993,MD4=>MD994);
  99 : DIST(COND:=COND,MD0=>MD995,MD1=>MD996,MD2=>MD997,MD3=>MD998,MD4=>MD999);

  END_CASE;
END_FUNCTION_BLOCK

FUNCTION Beta_N4 : REAL
  VAR_INPUT
    Ht : REAL := 0.0;
    M1 : TMatter;
    M2 : TMatter;
    Alfa_Nm1 : P_RERE;
    Tn_N : REAL := 0.0;
    Tn_Np1 : REAL;
    Q1n_N : REAL := 0.0;
    Q2n_N : REAL := 0.0;
  END_VAR
  VAR
    B : REAL := 0.0;
    C : REAL := 0.0;
    F : REAL := 0.0;
  END_VAR

  (* Малый шаг - условие симметрии *)
  if (M1.h < 1.0E-4 or M2.h < 1.0E-4) then
    Beta_N4 := Tn_Np1;
  else
    (* Cчитаем известной T=Tn_Np1 в точке i=N+1, тогда Alfa.A=0, Alfa.B=T *)
    C :=  M1.l / M1.h;

    B :=    (M1.l / M1.h) 
          + (M2.l / M2.h) 
          + (M1.l * M1.h / (2.0*M1.a*Ht))  
          + (M2.l * M2.h / (2.0*M2.a*Ht));

    F :=  - Tn_N * ( (M1.l*M1.h/(2.0*M1.a*Ht)) + (M2.l*M2.h/(2.0*M2.a*Ht)) ) 
          - (M1.l * M1.h / (2.0*M1.a)) * Q1n_N  
          - (M2.l * M2.h / (2.0*M2.a)) * Q2n_N
          - (M2.l / M2.h) * Tn_Np1; (* доп слагаемое - см. Tn_Np1 *)

    Beta_N4 := (C * Alfa_Nm1.B - F) / (B - C * Alfa_Nm1.A);
  end_if;
END_FUNCTION

FUNCTION _ref : TVar
  VAR_INPUT
    PIT : SINT := -1;
    DOT : TDot;
    DIR : USINT := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    union { // 32-бит (4 байта)
      TVAR tv;
      struct {  // Значение (var)
        USINT  R:1;       // Флаг R (для var = 0)
          INT  A:15;      // Значение A (актуальное)
        USINT  C:1;       // Флаг C (1-расчёт готов)
          INT  B:15;      // Значение B (предыдущее)
      };
      struct {  // Ссылка   (ref)
        USINT  r:1;       // Флаг r (для ref = 1)
        USINT  d:2;       // Направление (0,1,2,3)
        USINT  p:8;       // Позиция элемента
        USINT  i:7;       // Индекс сетки по DOT (0..127)
        USINT  j:7;       // Индекс сетки по J (0..127)
        USINT  k:7;       // Индекс сетки по K (0..127)
      };
    } var /*= {0}*/;
    #pragma pack(pop)
    var.r=1;              // Флаг r = 1
    var.d=DIR;            // Индекс направления     (d)
    var.p=PIT;            // Ссылка на элемент      (p)
    var.i=DOT.A.table[0]; // Индексы узла элемента  (i)
    var.j=DOT.A.table[1]; // Индексы узла элемента  (j)
    var.k=DOT.A.table[2]; // Индексы узла элемента  (k)
    _REF=var.tv;
  }}
END_FUNCTION

FUNCTION Beta_N3 : REAL
  VAR_INPUT
    Ht : REAL := 0.0;
    M : TMatter;
    Alfa_N1 : P_RERE;
    Tn_N : REAL := 0.0;
    Tq_N : REAL := 0.0;
    Qn_N : REAL := 0.0;
    V_N : REAL := 0.0;
    R_N : REAL := 0.0;
    Bound3 : BOOL := TRUE;
  END_VAR
  VAR
    D_N : REAL := 0.0;
    E_N : REAL := 0.0;
    b_N : REAL := 0.0;
    k_N : REAL := 0.0;
    h2 : REAL := 0.0;
    at2 : REAL := 0.0;
    DE : REAL := 0.0;
    denom : REAL := 0.0;
  END_VAR

  if (R_N > 1.0E-5) then 
    if (not Bound3) then M.k := 1.0; end_if;
    b_N := M.k/M.l;
    k_N := b_N*Tq_N;
    if (not Bound3) then b_N := 0.0; end_if;
    if (R_N < 1.0E5) then E_N := M.h / (2.0*R_N); end_if;
    D_N := (abs(V_N)*M.h) / (2.0*M.a);
  else
    (* Малый радиус - условия симметрии h=0 *)
    M.h := 0.0;
  end_if;

  h2    := M.h * M.h;
  at2   := 2.0 * M.a * Ht;
  DE    := (1.0 - D_N + E_N);
  denom := h2 + at2 * (1.0 + DE * M.h*b_N - Alfa_N1.A);

  Beta_N3 := ( h2 * (Tn_N + Ht*Qn_N) + at2 * (Alfa_N1.B + DE * M.h*k_N) ) / denom;
END_FUNCTION

FUNCTION its_gr2 : THandle
  VAR_INPUT
    Off : TPos8 := 0;
  END_VAR

  {{ ITS_GR2 = (THANDLE)&__GET_GLOBAL_ITS()->GR2.table[OFF]; }}
END_FUNCTION

FUNCTION int4ul : ULINT
  VAR_INPUT
    I0 : INT;
    I1 : INT;
    I2 : INT;
    I3 : INT;
  END_VAR

  int4ul := INT_TO_ULINT(I0)*16#0001000000000000 + 
            INT_TO_ULINT(I1)*16#0000000100000000 +
            INT_TO_ULINT(I2)*16#0000000000010000 +
            INT_TO_ULINT(I3);
           
END_FUNCTION

FUNCTION_BLOCK DistVarO
  VAR_OUTPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
  END_VAR
  VAR_INPUT
    VarO : TVarO;
  END_VAR

  MD0 := VarO.DTO;  (* секунд от 01-01-1970 *)
  MD1 := TIME_TO_UDINT(VarO.TMO);
  MD2 := REAL_TO_UDINT(VarO.QTY);
  MD3 := REAL_TO_UDINT(VarO.QTS);
  MD4 := REAL_TO_UDINT(VarO.RO1);
  MD5 := REAL_TO_UDINT(VarO.RO2);
END_FUNCTION_BLOCK

FUNCTION_BLOCK FRONT
  VAR_INPUT
    IN : BOOL := TRUE;
    PT : TIME := T#1s;
  END_VAR
  VAR_OUTPUT
    OUT : BOOL := FALSE;
    INV : BOOL := FALSE;
  END_VAR
  VAR
    f_TP : TP;
    f_TP_ET : TIME := T#0s;
    f_TP_Q : BOOL := FALSE;
  END_VAR

  VAR
    (*Run    : R_TRIG;*)
    bReStart : BOOL   := TRUE;
  END_VAR
    
  (*Run(CLK := IN);*)
  IF (IN) THEN
    IF ((*Run.Q*)bReStart) THEN     
      bReStart := FALSE;
      (* Инициализация *)
      f_TP(IN := FALSE);
      f_TP(IN := TRUE, PT := PT, Q => f_TP_Q, ET => f_TP_ET);
      OUT := TRUE;      (* Взвод триггера *)
    END_IF; 
    (* Нормальная работа *)
    (* Отсчет таймера *)
    f_TP(IN := FALSE, PT := PT, Q => f_TP_Q, ET => f_TP_ET);
    
    (* Анализ результата *)
    IF (f_TP.Q = FALSE) THEN 
      (* если отсчет закончился и ... *)
      IF (OUT = FALSE) THEN 
        (* ... если выход сброшен, тогда сразу начинаем новый отсчет *)
        f_TP(IN := TRUE, PT := PT, Q => f_TP_Q, ET => f_TP_ET);
        OUT := TRUE;  (* Взвод триггера *)
      ELSE 
        (* ... если выход взведен, то один цикл нужно пропустить !!! *)
        OUT := FALSE; (* Сброс триггера *)
      END_IF;
    ELSE
      OUT := FALSE;   (* Сброс триггера *)
    END_IF;
  ELSE
    bReStart := TRUE;
  END_IF; (* IN *)

  (* Устанавливаем инверсный выход *)
  IF (OUT <> TRUE) THEN INV := TRUE; ELSE INV := FALSE; END_IF;
    
  RETURN;
END_FUNCTION_BLOCK

FUNCTION st_is_debug : BOOL
  VAR_INPUT
    tmp : BOOL := FALSE;
  END_VAR

  {{ return (ST_IS_DEBUG=__GET_GLOBAL_STAT()->DBG); }}
END_FUNCTION

FUNCTION it_ip : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (IT_IP = __GET_GLOBAL_ITS()->IT.table[PIT].PAR); }}
END_FUNCTION

FUNCTION m_head : THead
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
    MD8 : UDINT;
    MD9 : UDINT;
  END_VAR

  m_head.Ni     := UINT_TO_SINT(UDINT_TO_UINT(MD0/65536)/256);            (* Количество элементов  *)
  m_head.Ng     := UINT_TO_SINT(mod(UDINT_TO_UINT(MD0/65536),256));       (* Количество сеток      *)
  m_head.Nm     := UINT_TO_SINT(UDINT_TO_UINT(mod(MD0,65536))/256);       (* Количество материалов *)
  m_head.Nv     := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD0,65536)),256));  (* Количество величин    *)
  m_head.Np     := UINT_TO_SINT(UDINT_TO_UINT(MD1/65536)/256);            (* Количество профилей   *)
  m_head.Ri     := UINT_TO_SINT(mod(UDINT_TO_UINT(MD1/65536),256));       (* Резерв                *)

  m_head.ID     := UDINT_TO_UINT(mod(MD1,65536)); (* ID эл-та для выкладки сетки в регистры *)

  m_head.TR[0]  := UDINT_TO_TIME(MD2); (* Период 1 *)
  m_head.TR[1]  := UDINT_TO_TIME(MD3); (* Период 2 *)
  m_head.TR[2]  := UDINT_TO_TIME(MD4); (* Период 3 *)
  m_head.TR[3]  := UDINT_TO_TIME(MD5); (* Период 4 *)

  m_head.Ax     := UDINT_TO_UINT(MD6/65536);      (* Направление перпендикуляра секущей *)
  m_head.pX     := UDINT_TO_INT(mod(MD6,65536));  (* Координата X опорной точки секущей *)
  m_head.pY     := UDINT_TO_INT(MD7/65536);       (* Координата Y опорной точки секущей *)
  m_head.pZ     := UDINT_TO_INT(mod(MD7,65536));  (* Координата Z опорной точки секущей *)

  m_head.RV[0]  := UDINT_TO_DINT(MD8); (* резерв *)
  m_head.RV[1]  := UDINT_TO_DINT(MD9); (* резерв *)
END_FUNCTION

FUNCTION_BLOCK GetHead
  VAR_EXTERNAL
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
    MD8 : UDINT;
    MD9 : UDINT;
  END_VAR
  VAR_OUTPUT
    HEAD : THead;
  END_VAR

  HEAD := m_head(MD0,MD1,MD2,MD3,MD4,MD5,MD6,MD7,MD8,MD9);
END_FUNCTION_BLOCK

FUNCTION it_iv : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (IT_IV = __GET_GLOBAL_ITS()->IT.table[PIT].IV); }}
END_FUNCTION

FUNCTION sh_get_ax : USINT
  VAR_INPUT
    SH : TShape;
  END_VAR

  sh_get_ax := WORD_TO_USINT(SHR((Sh.wF AND 16#3000), 12));
END_FUNCTION

FUNCTION Alfa_i : P_RERE
  VAR_INPUT
    Ht : REAL := 0.0;
    M : TMatter;
    Alfa_im : P_RERE;
    Ti : REAL := 0.0;
    Qi : REAL := 0.0;
    Vi : REAL := 0.0;
    Ri : REAL := 0.0;
  END_VAR
  VAR
    Ai : REAL := 0.0;
    Bi : REAL := 0.0;
    Ci : REAL := 0.0;
    Fi : REAL := 0.0;
    rh : REAL := 0.0;
    rk : REAL := 0.0;
    Via : REAL := 0.0;
    Vip : REAL := 0.0;
    Vim : REAL := 0.0;
    Di : REAL := 0.0;
    Ei : REAL := 0.0;
    denom : REAL := 0.0;
  END_VAR

  (* Малый радиус - условие симметрии *)
  if (Ri < 1.0E-4) then 
    Alfa_i.A := 1.0;
    Alfa_i.B := 0.0;
  else

    (* расчёт движения по радиусу *)
    if (Ri < 1.0e5) then Ei := M.h / (2.0 * Ri); end_if;
    
    (* расчёт движения среды *)
    if (Vi <> 0.0) then
      Via := abs(Vi);
      Vip := (Via + Vi)   / 2.0;
      Vim := (Via - Vi)   / 2.0;
      Di  := (Via * M.h)  / (2.0 * M.a);
    end_if;

    rh := Ht / M.h;       (* Отношение     (rh=dt/dx)     *)
    rk := (M.a*rh) / M.h; (* Число Куранта (rk=a*dt/dx^2) *)

    Ai :=       rk*(1.0+Ei) / (1.0+Di) + Vim*rh; 
    Ci :=       rk*(1.0-Ei) / (1.0+Di) + Vip*rh; 
    Bi := 1.0 +    (2.0*rk) / (1.0+Di) + Via*rh; 
    Fi := -Ti - Ht*Qi;

    denom := (Bi - Ci*Alfa_im.A);

    Alfa_i.A := Ai / denom;
    Alfa_i.B := (Ci*Alfa_im.B - Fi) / denom;
  end_if;
END_FUNCTION

FUNCTION Temp_i : REAL
  VAR_INPUT
    _Alfa_i : P_RERE;
    T_ip : REAL := 0.0;
  END_VAR

  Temp_i := _Alfa_i.A * T_ip + _Alfa_i.B;
END_FUNCTION

FUNCTION REAL2UDI : UDINT
  VAR_INPUT
    VALUE : REAL := 0.0;
  END_VAR
  VAR
    tmp : UDINT := 0;
  END_VAR

  {{
    union { UDINT  udint; float real; } value;
    value.real = VALUE;
    TMP = value.udint;
  }}
  REAL2UDI := TMP;
END_FUNCTION

FUNCTION _point : TPoint
  VAR_INPUT
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
  END_VAR

  {{ 
    _POINT.table[0] = X; 
    _POINT.table[1] = Y; 
    _POINT.table[2] = Z; 
  }}
END_FUNCTION

FUNCTION kto_oil : REAL
  VAR_INPUT
    L : REAL := 0.0;
    dTm : REAL := 0.0;
  END_VAR
  VAR CONSTANT
    C : REAL := 0.59;
    n : REAL := 0.25;
  END_VAR

  kto_oil:=36.0;
END_FUNCTION

FUNCTION _Matter : TMatter
  VAR_INPUT
    a : REAL := 0.0;
    l : REAL := 0.0;
    h : REAL := 0.0;
    k : REAL := 0.0;
  END_VAR

  _Matter.a:=a;
  _Matter.l:=l;
  _Matter.h:=h;
  _Matter.k:=k;
END_FUNCTION

FUNCTION grad : REAL
  VAR_INPUT
    RAD : REAL := 0.0;
  END_VAR

  grad:=RAD*57.295779513082320876798154814105;
END_FUNCTION

FUNCTION AxO : TAxO
  VAR_INPUT
    Ax : USINT := 0;
    inside : BOOL := TRUE;
  END_VAR

  (*  Порядок координат при различной ориентации оси *)
  if (inside) then
    (* Взгляд изнутри: какой индекс в локальных координатах элемента
      X(R),Y(F),Z имеет абсолютная координата (Ox,Oy,Oz)
      при заданной ориентации оси симметрии Ax?
    (* Индексы координат, ставших X,Y,Z:  Ax  | 1 | 2 | 3 | *)
    (* O.x-индекс радиуса,O.y-угол,O.z-высота ------------- *)
    AxO.x := (0+Ax) mod 3; (* Ind_of_X  (O.x) | 1 | 2 | 0 | *)
    AxO.y := (1+Ax) mod 3; (* Ind_of_Y  (O.y) | 2 | 0 | 1 | *)  
    AxO.z := (2+Ax) mod 3; (* Ind_of_Z  (O.z) | 0 | 1 | 2 | *)
  else  (* Обратное преобразование -> *)
    (* Взгляд снаружи: какую роль абсолютная координата (Ox,Oy,Oz)
       играет для вложенного во внешнюю систему элемента?   *)
    (* Порядок "перебора" координат:  Ax=Ix+1 | 1 | 2 | 3 | *)
    (* где 0-внешний цикл, 2-самый вложенный  ------------- *)
    AxO.x := (3-Ax) mod 3; (* Ind_of_X  (O.x) | 2 | 1 | 0 | *)
    AxO.y := (4-Ax) mod 3; (* Ind_of_Y  (O.y) | 0 | 2 | 1 | *)  
    AxO.z := (5-Ax) mod 3; (* Ind_of_Z  (O.z) | 1 | 0 | 2 | *)
  end_if;
END_FUNCTION

FUNCTION get_sh : TShape
  VAR_INPUT
    PSH : TPos8 := -1;
  END_VAR

  {{ return (GET_SH = __GET_GLOBAL_ITS()->SH.table[PSH]); }}
END_FUNCTION

FUNCTION Sh_Abs2Loc : TPoint
  VAR_INPUT
    Sh : TShape;
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
  END_VAR
  VAR
    Ax : USINT := 0;
    A : TPoint := [0.0, 0.0, 0.0];
    B : TPoint := [0.0, 0.0, 0.0];
    O : TAxO;
    PI : REAL := 3.1415926535897932384626433832795;
    PI_2 : REAL := 1.5707963267948966192313216916398;
  END_VAR
  VAR CONSTANT
    RAD : BOOL := FALSE;
    DX : REAL := 1.0E-5;
  END_VAR

  (* Sh := get_sh(PIT); *)
  Ax := sh_get_ax(Sh);

  A := _point(X-Sh.P0[0],Y-Sh.P0[1],Z-Sh.P0[2]); 
  if (Ax > 0) then 
    (* Декарт -> Цилиндр *)
    O := AxO(Ax);
    B[O.x] := sqrt(A[O.x]*A[O.x] + A[O.y]*A[O.y]);
    if (abs(A[O.x]) < DX) then A[O.x] := 0.0; end_if;
    if (abs(A[O.y]) < DX) then A[O.y] := 0.0; end_if;
    (* интерпретация atan2(y,x) *)
    if (A[O.x] < 0.0) then 
      if (A[O.y] < 0.0) then  B[O.y] := atan(A[O.y]/A[O.x])-PI; 
      else                    B[O.y] := atan(A[O.y]/A[O.x])+PI; 
      end_if;
    else 
      if (A[O.x] > 0.0) then
        B[O.y] := atan(A[O.y]/A[O.x]);
      else (* A[O.x] = 0.0 *)
        if (A[O.y] < 0.0) then 
          B[O.y] := -PI_2;  
        else 
          if (A[O.y] > 0.0) then
            B[O.y] := PI_2;   
          else (* y = 0.0 *)
            B[O.y] := 0.0; 
          end_if;
        end_if;
      end_if;
    end_if;
    if (abs(B[O.y]) < DX) then B[O.y] := 0.0; end_if;
    if (not RAD) then B[O.y] := grad(B[O.y]); end_if;
    B[O.z] := A[O.z];
  else 
    B := A;
  end_if;
  Sh_Abs2Loc := B; 
END_FUNCTION

FUNCTION radi : REAL
  VAR_INPUT
    GRA : REAL := 0.0;
  END_VAR

  radi:=GRA*0.01745329251994329576923690768489;
END_FUNCTION

FUNCTION angle : REAL
  VAR_INPUT
    A : REAL := 0.0;
    L0 : REAL := 0.0;
    PI2 : REAL := 360.0;
  END_VAR

  (* Приведение аргумента к диапазону [L0..L0+2*PI] *)
  while (A < L0    ) do A := A+PI2; end_while;
  while (A > L0+PI2) do A := A-PI2; end_while;
  angle := A;
END_FUNCTION

FUNCTION Reform : TPoint
  VAR_INPUT
    wF : WORD := 0;
    Ang : REAL := 0.0;
    Pt : REAL := 0.0;
    pL : REAL := 0.0;
    Lx : REAL := 0.0;
  END_VAR
  VAR
    pR : REAL := 0.0;
    LR : P_BOOL;
    Q : SINT := 0;
    K : REAL := 0.0;
    Kx : REAL := 0.0;
  END_VAR
  VAR CONSTANT
    PI_2 : REAL := 90.0;
    PI_4 : REAL := 45.0;
    PI : REAL := 180.0;
    PI3_2 : REAL := 270.0;
  END_VAR

  (* Нормируем угол 0-360 град. *)
  Ang:=angle(Ang);

  (* Определяем номер квадранта Q = [0..3] *)
  if (Ang >= 0.0) then
    if    (Ang >= 0.0   and Ang <  PI_2 ) then Q := 0; 
    elsif (Ang >= PI_2  and Ang <  PI   ) then Q := 1; 
    elsif (Ang >= PI    and Ang <  PI3_2) then Q := 2; 
    else Q := 3;
    end_if;
  else
    if    (Ang <= 0.0   and Ang > -PI_2 ) then Q := 3; 
    elsif (Ang <= -PI_2 and Ang > -PI   ) then Q := 2; 
    elsif (Ang <= -PI   and Ang > -PI3_2) then Q := 1; 
    else Q := 0;
    end_if;
  end_if;

  (* Определяем форму границ в квадранте Q *)
  LR.A := ((wF and shl(16#10, Q))<>0);
  LR.B := ((wF and shl(16#01, Q))<>0);

  (* Делаем преобразование границ и точки Pt *)
  if (LR.A or LR.B) then 
    (* Растяжение по радиусу от угла *)
    Ang := angle(Ang, 0.0, PI_2); 
    if (Ang < PI_4) 
    then Kx := 1.0/cos(radi(Ang));    (* коэффициент растяжения         *)
    else Kx := 1.0/sin(radi(Ang));    (* коэффициент растяжения         *)
    end_if;
    pR := pL + Lx;                    (* координата правой границы      *)
    K  := (Pt - pL)/Lx;               (* коэффициент пропорциональности *)
    if (LR.A) then pL:=pL*Kx; end_if; (* коррекция левой  границы       *)
    if (LR.B) then pR:=pR*Kx; end_if; (* коррекция правой границы       *)
    Lx := (pR - pL);                  (* размер по координате           *)
    Pt := pL + K * Lx;                (* координата точки               *)
  end_if;

  Reform[0] := Pt; (* текущая   координата *)
  Reform[1] := pL; (* начальная координата *)
  Reform[2] := Lx; (* размер по координате *)
END_FUNCTION

FUNCTION Sh_Point2Dot : TDot
  VAR_INPUT
    Sh : TShape;
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
    fChk : BOOL := TRUE;
  END_VAR
  VAR
    Hn : TPoint := [0.0, 0.0, 0.0];
    Ax : USINT := 0;
    pL : TPoint := [0.0, 0.0, 0.0];
    pR : TPoint := [0.0, 0.0, 0.0];
    pDL : TPoint := [0.0, 0.0, 0.0];
    pDR : TPoint := [0.0, 0.0, 0.0];
    Ox : TAxO;
    Pt : TPoint := [0.0, 0.0, 0.0];
    Hx : TPoint := [0.0, 0.0, 0.0];
    P : TPoint := [0.0, 0.0, 0.0];
    B : BYTE := 0;
    bRes : BOOL := true;
  END_VAR
  VAR CONSTANT
    DX : REAL := 1.0E-5;
  END_VAR

  Ax := sh_get_ax(Sh);

  (* точка (X,Y,Z)->лок *)
  Pt := Sh_Abs2Loc(Sh, X, Y, Z);

  (* Коррекция границ при изменении формы *)
  if (Ax<>0) then
    Ox := AxO(Ax);
    Pt[Ox.y]:=angle(Pt[Ox.y], Sh.pL[Ox.y]);
    P := Reform(Sh.wF, Pt[Ox.y], 0.0, Sh.pL[Ox.x], Sh.Lx[Ox.x]);
    Sh.pL[Ox.x] := P[1]; Sh.Lx[Ox.x] := P[2];
  end_if;

  if (fChk) then 
    (* B[0] - 0x01 (In)    - точка внутри элемента    *)
    (* B[1] - 0x02 (Left)  - точка на левой грани     *)
    (* B[2] - 0x04 (Right) - точка на правой грани    *)
    (* B[3] - 0x08 (Front) - точка на передней грани  *)
    (* B[4] - 0x10 (Back)  - точка на задней грани    *)
    (* B[5] - 0x20 (Down)  - точка на нижней грани    *)
    (* B[6] - 0x40 (Up)    - точка на верхней грани   *)
    (* B[7] - 0x80 (Err)   - ошибка (не используется) *)
    pL  := Sh.pL;
    pR  := _point(Sh.pL[0]+Sh.Lx[0], Sh.pL[1]+Sh.Lx[1], Sh.pL[2]+Sh.Lx[2]);
    
    pDL := _point((pL[0])*(1.0+DX), (pL[1])*(1.0+DX), (pL[2])*(1.0+DX));
    pDR := _point((pR[0])*(1.0-DX), (pR[1])*(1.0-DX), (pR[2])*(1.0-DX));
    
    (*
    pDL := _point( pL[0]+(Sh.Lx[0]*DX), pL[1]+(Sh.Lx[1]*DX), pL[2]+(Sh.Lx[2]*DX) );
    pDR := _point( pR[0]-(Sh.Lx[0]*DX), pR[1]-(Sh.Lx[1]*DX), pR[2]-(Sh.Lx[2]*DX) );
    *)
    
    (* Проверка: точка внутри элемента -> B=1 *)
    if ( (Pt[0] > pDL[0]) and (Pt[0] < pDR[0]) ) then 
      if ( (Pt[1] > pDL[1]) and (Pt[1] < pDR[1]) ) then
        if ( (Pt[2] > pDL[2]) and (Pt[2] < pDR[2]) ) then B:=16#01; end_if;
      end_if;
    end_if;
    
    (* Сравниваем координаты Pt с гранями элемента *)
    if (B = 0) then
      if    ( Pt[0] >= pL[0] and Pt[0] <= pDL[0] ) then B:=(B or shl(16#01, 1)); 
      elsif ( Pt[0] <= pR[0] and Pt[0] >= pDR[0] ) then B:=(B or shl(16#01, 2)); end_if;
      if    ( Pt[1] >= pL[1] and Pt[1] <= pDL[1] ) then B:=(B or shl(16#01, 3));
      elsif ( Pt[1] <= pR[1] and Pt[1] >= pDR[1] ) then B:=(B or shl(16#01, 4)); end_if;
      if    ( Pt[2] >= pL[2] and Pt[2] <= pDL[2] ) then B:=(B or shl(16#01, 5)); 
      elsif ( Pt[2] <= pR[2] and Pt[2] >= pDR[2] ) then B:=(B or shl(16#01, 6)); end_if;
    end_if;
    if (B = 0) then (* точка вне элемента *)
      {}(* bRes := assert(false, E_CHECK); *) 
    end_if;
  end_if;

  (* Получение узла сетки элемента *)
  if (Sh.Kn[0]>1) then Hn[0]:=(Sh.Lx[0]/INT_TO_REAL(Sh.Kn[0]-1)); end_if;
  if (Sh.Kn[1]>1) then Hn[1]:=(Sh.Lx[1]/INT_TO_REAL(Sh.Kn[1]-1)); end_if;
  if (Sh.Kn[2]>1) then Hn[2]:=(Sh.Lx[2]/INT_TO_REAL(Sh.Kn[2]-1)); end_if;

  Sh_Point2Dot := _dot(
      byte_to_int(B),
      min(Sh.Kn[0]-1, max(0, REAL_TO_INT((Pt[0]-Sh.pL[0])/Hn[0]) )), 
      min(Sh.Kn[1]-1, max(0, REAL_TO_INT((Pt[1]-Sh.pL[1])/Hn[1]) )), 
      min(Sh.Kn[2]-1, max(0, REAL_TO_INT((Pt[2]-Sh.pL[2])/Hn[2]) ))
  );
END_FUNCTION

FUNCTION ID2PIT : TPos8
  VAR_INPUT
    ID : UINT := 0;
  END_VAR
  VAR
    bFound : BOOL := false;
  END_VAR

  {{
    ID2PIT = -1;
    P_IDPIT *IDS = &(__GET_GLOBAL_ITS()->PR.table[0]);
    if (ID != 0) {
      int lBound=0, rBound=99, test;
      if (IDS[rBound].A == ID)      ID2PIT = IDS[rBound].B;
      else if (IDS[lBound].A == ID) ID2PIT = IDS[lBound].B;
      else {
        if ( (IDS[lBound].A < ID) && (ID < IDS[rBound].A) ) {
          while (TRUE) {
            test = (lBound+rBound)/2;
            if (IDS[test].A == ID) { ID2PIT = IDS[test].B; break; }
            if (rBound-lBound <= 1) break;
            if (IDS[test].A <  ID) lBound = test; else rBound = test; 
          }
        }
      }
    } else ID2PIT = IDS[0].B;
  }}
END_FUNCTION

FUNCTION Do_FindDot : TDot
  VAR_INPUT
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
    ign : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
    skip_to : TPos8 := -1;
    i : SINT := 0;
    N : SINT := 0;
    Dots : ARRAY [0..7] OF TDot;
    P : ARRAY [0..7] OF TPos8;
  END_VAR

  if (not st_check(false)) then return; end_if;

  (* Обход дерева - сбор элементов, содержащих точку *)
  it  := it_begin(ID2PIT(0));
  while (it.item<>-1 and N < 8) do (* не более 8 владельцев *)
    case (it.dir) of
    DIR_DOWN:
      if (skip_to = -1) then
        (* Если точка не входит в родителя, потомков пропускаем *)
        if (is_poly(it.item)) then
          Do_FindDot := Sh_Point2Dot(get_sh(it.item), X, Y, Z);
          if (Do_FindDot.V <= 0) then skip_to := it.item; end_if;
        end_if;
      end_if;
    DIR_UP:
      if (skip_to <> -1) then
        if (skip_to = it.item) then skip_to := -1; end_if;
      else
        (* если элемент конечный - проверяем точку *)
        if (not is_poly(it.item)) then
          Dots[N] := Sh_Point2Dot(get_sh(it.item), X, Y, Z);
          if (Dots[N].V > 0) then 
            P[N] := it.item; 
            N    := N+1; 
          end_if;
        end_if;
      end_if;
    end_case;
    it := it_next(it);
  end_while;

  (* Выбор элемента *)
  Do_FindDot := _dot(-1);
  if (N > 0) then
    for i:=0 to N-1 do
    
      if (((*ign<>-1 and*) P[i]<>ign) or N=1) then 
          Do_FindDot   := Dots[i]; 
          Do_FindDot.V := sint_to_int(P[i]); 
         exit; 
      end_if;
      
    end_for;
  end_if;
END_FUNCTION

FUNCTION var_d : TDot
  VAR_INPUT
    TV : TVar := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)

    // Величина должна быть ссылкой
    // ASSERT(1, NULL, pvar->r, TERROR__E_FAIL, __INIT_STRING);
    VAR_D.A.table[0] = ((pvar_t) &TV)->i;
    VAR_D.A.table[1] = ((pvar_t) &TV)->j;
    VAR_D.A.table[2] = ((pvar_t) &TV)->k;
    VAR_D.V          = ((pvar_t) &TV)->p;
  }}
END_FUNCTION

FUNCTION_BLOCK DistLong4
  VAR_INPUT
    LONG4 : ARRAY [0..3] OF ULINT;
  END_VAR
  VAR_OUTPUT
    ML0 : ULINT;
    ML1 : ULINT;
    ML2 : ULINT;
    ML3 : ULINT;
  END_VAR

  ML0 := LONG4[0]; 
  ML1 := LONG4[1]; 
  ML2 := LONG4[2]; 
  ML3 := LONG4[3]; 
END_FUNCTION_BLOCK

FUNCTION_BLOCK SetLong4
  VAR_EXTERNAL
    ML0 : ULINT;
    ML1 : ULINT;
    ML2 : ULINT;
    ML3 : ULINT;
    ML4 : ULINT;
    ML5 : ULINT;
    ML6 : ULINT;
    ML7 : ULINT;
    ML8 : ULINT;
    ML9 : ULINT;
    ML10 : ULINT;
    ML11 : ULINT;
    ML12 : ULINT;
    ML13 : ULINT;
    ML14 : ULINT;
    ML15 : ULINT;
    ML16 : ULINT;
    ML17 : ULINT;
    ML18 : ULINT;
    ML19 : ULINT;
    ML20 : ULINT;
    ML21 : ULINT;
    ML22 : ULINT;
    ML23 : ULINT;
    ML24 : ULINT;
    ML25 : ULINT;
    ML26 : ULINT;
    ML27 : ULINT;
    ML28 : ULINT;
    ML29 : ULINT;
    ML30 : ULINT;
    ML31 : ULINT;
    ML32 : ULINT;
    ML33 : ULINT;
    ML34 : ULINT;
    ML35 : ULINT;
    ML36 : ULINT;
    ML37 : ULINT;
    ML38 : ULINT;
    ML39 : ULINT;
    ML40 : ULINT;
    ML41 : ULINT;
    ML42 : ULINT;
    ML43 : ULINT;
    ML44 : ULINT;
    ML45 : ULINT;
    ML46 : ULINT;
    ML47 : ULINT;
    ML48 : ULINT;
    ML49 : ULINT;
    ML50 : ULINT;
    ML51 : ULINT;
    ML52 : ULINT;
    ML53 : ULINT;
    ML54 : ULINT;
    ML55 : ULINT;
    ML56 : ULINT;
    ML57 : ULINT;
    ML58 : ULINT;
    ML59 : ULINT;
    ML60 : ULINT;
    ML61 : ULINT;
    ML62 : ULINT;
    ML63 : ULINT;
    ML64 : ULINT;
    ML65 : ULINT;
    ML66 : ULINT;
    ML67 : ULINT;
    ML68 : ULINT;
    ML69 : ULINT;
    ML70 : ULINT;
    ML71 : ULINT;
    ML72 : ULINT;
    ML73 : ULINT;
    ML74 : ULINT;
    ML75 : ULINT;
    ML76 : ULINT;
    ML77 : ULINT;
    ML78 : ULINT;
    ML79 : ULINT;
    ML80 : ULINT;
    ML81 : ULINT;
    ML82 : ULINT;
    ML83 : ULINT;
    ML84 : ULINT;
    ML85 : ULINT;
    ML86 : ULINT;
    ML87 : ULINT;
    ML88 : ULINT;
    ML89 : ULINT;
    ML90 : ULINT;
    ML91 : ULINT;
    ML92 : ULINT;
    ML93 : ULINT;
    ML94 : ULINT;
    ML95 : ULINT;
    ML96 : ULINT;
    ML97 : ULINT;
    ML98 : ULINT;
    ML99 : ULINT;
    ML100 : ULINT;
    ML101 : ULINT;
    ML102 : ULINT;
    ML103 : ULINT;
    ML104 : ULINT;
    ML105 : ULINT;
    ML106 : ULINT;
    ML107 : ULINT;
    ML108 : ULINT;
    ML109 : ULINT;
    ML110 : ULINT;
    ML111 : ULINT;
    ML112 : ULINT;
    ML113 : ULINT;
    ML114 : ULINT;
    ML115 : ULINT;
    ML116 : ULINT;
    ML117 : ULINT;
    ML118 : ULINT;
    ML119 : ULINT;
    ML120 : ULINT;
    ML121 : ULINT;
    ML122 : ULINT;
    ML123 : ULINT;
    ML124 : ULINT;
    ML125 : ULINT;
    ML126 : ULINT;
    ML127 : ULINT;
    ML128 : ULINT;
    ML129 : ULINT;
    ML130 : ULINT;
    ML131 : ULINT;
    ML132 : ULINT;
    ML133 : ULINT;
    ML134 : ULINT;
    ML135 : ULINT;
    ML136 : ULINT;
    ML137 : ULINT;
    ML138 : ULINT;
    ML139 : ULINT;
    ML140 : ULINT;
    ML141 : ULINT;
    ML142 : ULINT;
    ML143 : ULINT;
    ML144 : ULINT;
    ML145 : ULINT;
    ML146 : ULINT;
    ML147 : ULINT;
    ML148 : ULINT;
    ML149 : ULINT;
    ML150 : ULINT;
    ML151 : ULINT;
    ML152 : ULINT;
    ML153 : ULINT;
    ML154 : ULINT;
    ML155 : ULINT;
    ML156 : ULINT;
    ML157 : ULINT;
    ML158 : ULINT;
    ML159 : ULINT;
    ML160 : ULINT;
    ML161 : ULINT;
    ML162 : ULINT;
    ML163 : ULINT;
    ML164 : ULINT;
    ML165 : ULINT;
    ML166 : ULINT;
    ML167 : ULINT;
    ML168 : ULINT;
    ML169 : ULINT;
    ML170 : ULINT;
    ML171 : ULINT;
    ML172 : ULINT;
    ML173 : ULINT;
    ML174 : ULINT;
    ML175 : ULINT;
    ML176 : ULINT;
    ML177 : ULINT;
    ML178 : ULINT;
    ML179 : ULINT;
    ML180 : ULINT;
    ML181 : ULINT;
    ML182 : ULINT;
    ML183 : ULINT;
    ML184 : ULINT;
    ML185 : ULINT;
    ML186 : ULINT;
    ML187 : ULINT;
    ML188 : ULINT;
    ML189 : ULINT;
    ML190 : ULINT;
    ML191 : ULINT;
    ML192 : ULINT;
    ML193 : ULINT;
    ML194 : ULINT;
    ML195 : ULINT;
    ML196 : ULINT;
    ML197 : ULINT;
    ML198 : ULINT;
    ML199 : ULINT;
    ML200 : ULINT;
    ML201 : ULINT;
    ML202 : ULINT;
    ML203 : ULINT;
    ML204 : ULINT;
    ML205 : ULINT;
    ML206 : ULINT;
    ML207 : ULINT;
    ML208 : ULINT;
    ML209 : ULINT;
    ML210 : ULINT;
    ML211 : ULINT;
    ML212 : ULINT;
    ML213 : ULINT;
    ML214 : ULINT;
    ML215 : ULINT;
    ML216 : ULINT;
    ML217 : ULINT;
    ML218 : ULINT;
    ML219 : ULINT;
    ML220 : ULINT;
    ML221 : ULINT;
    ML222 : ULINT;
    ML223 : ULINT;
    ML224 : ULINT;
    ML225 : ULINT;
    ML226 : ULINT;
    ML227 : ULINT;
    ML228 : ULINT;
    ML229 : ULINT;
    ML230 : ULINT;
    ML231 : ULINT;
    ML232 : ULINT;
    ML233 : ULINT;
    ML234 : ULINT;
    ML235 : ULINT;
    ML236 : ULINT;
    ML237 : ULINT;
    ML238 : ULINT;
    ML239 : ULINT;
    ML240 : ULINT;
    ML241 : ULINT;
    ML242 : ULINT;
    ML243 : ULINT;
    ML244 : ULINT;
    ML245 : ULINT;
    ML246 : ULINT;
    ML247 : ULINT;
    ML248 : ULINT;
    ML249 : ULINT;
    ML250 : ULINT;
    ML251 : ULINT;
    ML252 : ULINT;
    ML253 : ULINT;
    ML254 : ULINT;
    ML255 : ULINT;
    ML256 : ULINT;
    ML257 : ULINT;
    ML258 : ULINT;
    ML259 : ULINT;
    ML260 : ULINT;
    ML261 : ULINT;
    ML262 : ULINT;
    ML263 : ULINT;
    ML264 : ULINT;
    ML265 : ULINT;
    ML266 : ULINT;
    ML267 : ULINT;
    ML268 : ULINT;
    ML269 : ULINT;
    ML270 : ULINT;
    ML271 : ULINT;
    ML272 : ULINT;
    ML273 : ULINT;
    ML274 : ULINT;
    ML275 : ULINT;
    ML276 : ULINT;
    ML277 : ULINT;
    ML278 : ULINT;
    ML279 : ULINT;
    ML280 : ULINT;
    ML281 : ULINT;
    ML282 : ULINT;
    ML283 : ULINT;
    ML284 : ULINT;
    ML285 : ULINT;
    ML286 : ULINT;
    ML287 : ULINT;
    ML288 : ULINT;
    ML289 : ULINT;
    ML290 : ULINT;
    ML291 : ULINT;
    ML292 : ULINT;
    ML293 : ULINT;
    ML294 : ULINT;
    ML295 : ULINT;
    ML296 : ULINT;
    ML297 : ULINT;
    ML298 : ULINT;
    ML299 : ULINT;
    ML300 : ULINT;
    ML301 : ULINT;
    ML302 : ULINT;
    ML303 : ULINT;
    ML304 : ULINT;
    ML305 : ULINT;
    ML306 : ULINT;
    ML307 : ULINT;
    ML308 : ULINT;
    ML309 : ULINT;
    ML310 : ULINT;
    ML311 : ULINT;
    ML312 : ULINT;
    ML313 : ULINT;
    ML314 : ULINT;
    ML315 : ULINT;
    ML316 : ULINT;
    ML317 : ULINT;
    ML318 : ULINT;
    ML319 : ULINT;
    ML320 : ULINT;
    ML321 : ULINT;
    ML322 : ULINT;
    ML323 : ULINT;
    ML324 : ULINT;
    ML325 : ULINT;
    ML326 : ULINT;
    ML327 : ULINT;
    ML328 : ULINT;
    ML329 : ULINT;
    ML330 : ULINT;
    ML331 : ULINT;
    ML332 : ULINT;
    ML333 : ULINT;
    ML334 : ULINT;
    ML335 : ULINT;
    ML336 : ULINT;
    ML337 : ULINT;
    ML338 : ULINT;
    ML339 : ULINT;
    ML340 : ULINT;
    ML341 : ULINT;
    ML342 : ULINT;
    ML343 : ULINT;
    ML344 : ULINT;
    ML345 : ULINT;
    ML346 : ULINT;
    ML347 : ULINT;
    ML348 : ULINT;
    ML349 : ULINT;
    ML350 : ULINT;
    ML351 : ULINT;
    ML352 : ULINT;
    ML353 : ULINT;
    ML354 : ULINT;
    ML355 : ULINT;
    ML356 : ULINT;
    ML357 : ULINT;
    ML358 : ULINT;
    ML359 : ULINT;
    ML360 : ULINT;
    ML361 : ULINT;
    ML362 : ULINT;
    ML363 : ULINT;
    ML364 : ULINT;
    ML365 : ULINT;
    ML366 : ULINT;
    ML367 : ULINT;
    ML368 : ULINT;
    ML369 : ULINT;
    ML370 : ULINT;
    ML371 : ULINT;
    ML372 : ULINT;
    ML373 : ULINT;
    ML374 : ULINT;
    ML375 : ULINT;
    ML376 : ULINT;
    ML377 : ULINT;
    ML378 : ULINT;
    ML379 : ULINT;
    ML380 : ULINT;
    ML381 : ULINT;
    ML382 : ULINT;
    ML383 : ULINT;
    ML384 : ULINT;
    ML385 : ULINT;
    ML386 : ULINT;
    ML387 : ULINT;
    ML388 : ULINT;
    ML389 : ULINT;
    ML390 : ULINT;
    ML391 : ULINT;
    ML392 : ULINT;
    ML393 : ULINT;
    ML394 : ULINT;
    ML395 : ULINT;
    ML396 : ULINT;
    ML397 : ULINT;
    ML398 : ULINT;
    ML399 : ULINT;
    ML400 : ULINT;
    ML401 : ULINT;
    ML402 : ULINT;
    ML403 : ULINT;
    ML404 : ULINT;
    ML405 : ULINT;
    ML406 : ULINT;
    ML407 : ULINT;
    ML408 : ULINT;
    ML409 : ULINT;
    ML410 : ULINT;
    ML411 : ULINT;
    ML412 : ULINT;
    ML413 : ULINT;
    ML414 : ULINT;
    ML415 : ULINT;
    ML416 : ULINT;
    ML417 : ULINT;
    ML418 : ULINT;
    ML419 : ULINT;
    ML420 : ULINT;
    ML421 : ULINT;
    ML422 : ULINT;
    ML423 : ULINT;
    ML424 : ULINT;
    ML425 : ULINT;
    ML426 : ULINT;
    ML427 : ULINT;
    ML428 : ULINT;
    ML429 : ULINT;
    ML430 : ULINT;
    ML431 : ULINT;
    ML432 : ULINT;
    ML433 : ULINT;
    ML434 : ULINT;
    ML435 : ULINT;
    ML436 : ULINT;
    ML437 : ULINT;
    ML438 : ULINT;
    ML439 : ULINT;
    ML440 : ULINT;
    ML441 : ULINT;
    ML442 : ULINT;
    ML443 : ULINT;
    ML444 : ULINT;
    ML445 : ULINT;
    ML446 : ULINT;
    ML447 : ULINT;
    ML448 : ULINT;
    ML449 : ULINT;
    ML450 : ULINT;
    ML451 : ULINT;
    ML452 : ULINT;
    ML453 : ULINT;
    ML454 : ULINT;
    ML455 : ULINT;
    ML456 : ULINT;
    ML457 : ULINT;
    ML458 : ULINT;
    ML459 : ULINT;
    ML460 : ULINT;
    ML461 : ULINT;
    ML462 : ULINT;
    ML463 : ULINT;
    ML464 : ULINT;
    ML465 : ULINT;
    ML466 : ULINT;
    ML467 : ULINT;
    ML468 : ULINT;
    ML469 : ULINT;
    ML470 : ULINT;
    ML471 : ULINT;
    ML472 : ULINT;
    ML473 : ULINT;
    ML474 : ULINT;
    ML475 : ULINT;
    ML476 : ULINT;
    ML477 : ULINT;
    ML478 : ULINT;
    ML479 : ULINT;
    ML480 : ULINT;
    ML481 : ULINT;
    ML482 : ULINT;
    ML483 : ULINT;
    ML484 : ULINT;
    ML485 : ULINT;
    ML486 : ULINT;
    ML487 : ULINT;
    ML488 : ULINT;
    ML489 : ULINT;
    ML490 : ULINT;
    ML491 : ULINT;
    ML492 : ULINT;
    ML493 : ULINT;
    ML494 : ULINT;
    ML495 : ULINT;
    ML496 : ULINT;
    ML497 : ULINT;
    ML498 : ULINT;
    ML499 : ULINT;
    ML500 : ULINT;
    ML501 : ULINT;
    ML502 : ULINT;
    ML503 : ULINT;
    ML504 : ULINT;
    ML505 : ULINT;
    ML506 : ULINT;
    ML507 : ULINT;
    ML508 : ULINT;
    ML509 : ULINT;
    ML510 : ULINT;
    ML511 : ULINT;
    ML512 : ULINT;
    ML513 : ULINT;
    ML514 : ULINT;
    ML515 : ULINT;
    ML516 : ULINT;
    ML517 : ULINT;
    ML518 : ULINT;
    ML519 : ULINT;
    ML520 : ULINT;
    ML521 : ULINT;
    ML522 : ULINT;
    ML523 : ULINT;
    ML524 : ULINT;
    ML525 : ULINT;
    ML526 : ULINT;
    ML527 : ULINT;
    ML528 : ULINT;
    ML529 : ULINT;
    ML530 : ULINT;
    ML531 : ULINT;
    ML532 : ULINT;
    ML533 : ULINT;
    ML534 : ULINT;
    ML535 : ULINT;
    ML536 : ULINT;
    ML537 : ULINT;
    ML538 : ULINT;
    ML539 : ULINT;
    ML540 : ULINT;
    ML541 : ULINT;
    ML542 : ULINT;
    ML543 : ULINT;
    ML544 : ULINT;
    ML545 : ULINT;
    ML546 : ULINT;
    ML547 : ULINT;
    ML548 : ULINT;
    ML549 : ULINT;
    ML550 : ULINT;
    ML551 : ULINT;
    ML552 : ULINT;
    ML553 : ULINT;
    ML554 : ULINT;
    ML555 : ULINT;
    ML556 : ULINT;
    ML557 : ULINT;
    ML558 : ULINT;
    ML559 : ULINT;
    ML560 : ULINT;
    ML561 : ULINT;
    ML562 : ULINT;
    ML563 : ULINT;
    ML564 : ULINT;
    ML565 : ULINT;
    ML566 : ULINT;
    ML567 : ULINT;
    ML568 : ULINT;
    ML569 : ULINT;
    ML570 : ULINT;
    ML571 : ULINT;
    ML572 : ULINT;
    ML573 : ULINT;
    ML574 : ULINT;
    ML575 : ULINT;
    ML576 : ULINT;
    ML577 : ULINT;
    ML578 : ULINT;
    ML579 : ULINT;
    ML580 : ULINT;
    ML581 : ULINT;
    ML582 : ULINT;
    ML583 : ULINT;
    ML584 : ULINT;
    ML585 : ULINT;
    ML586 : ULINT;
    ML587 : ULINT;
    ML588 : ULINT;
    ML589 : ULINT;
    ML590 : ULINT;
    ML591 : ULINT;
    ML592 : ULINT;
    ML593 : ULINT;
    ML594 : ULINT;
    ML595 : ULINT;
    ML596 : ULINT;
    ML597 : ULINT;
    ML598 : ULINT;
    ML599 : ULINT;
    ML600 : ULINT;
    ML601 : ULINT;
    ML602 : ULINT;
    ML603 : ULINT;
    ML604 : ULINT;
    ML605 : ULINT;
    ML606 : ULINT;
    ML607 : ULINT;
    ML608 : ULINT;
    ML609 : ULINT;
    ML610 : ULINT;
    ML611 : ULINT;
    ML612 : ULINT;
    ML613 : ULINT;
    ML614 : ULINT;
    ML615 : ULINT;
    ML616 : ULINT;
    ML617 : ULINT;
    ML618 : ULINT;
    ML619 : ULINT;
    ML620 : ULINT;
    ML621 : ULINT;
    ML622 : ULINT;
    ML623 : ULINT;
    ML624 : ULINT;
    ML625 : ULINT;
    ML626 : ULINT;
    ML627 : ULINT;
    ML628 : ULINT;
    ML629 : ULINT;
    ML630 : ULINT;
    ML631 : ULINT;
    ML632 : ULINT;
    ML633 : ULINT;
    ML634 : ULINT;
    ML635 : ULINT;
    ML636 : ULINT;
    ML637 : ULINT;
    ML638 : ULINT;
    ML639 : ULINT;
    ML640 : ULINT;
    ML641 : ULINT;
    ML642 : ULINT;
    ML643 : ULINT;
    ML644 : ULINT;
    ML645 : ULINT;
    ML646 : ULINT;
    ML647 : ULINT;
    ML648 : ULINT;
    ML649 : ULINT;
    ML650 : ULINT;
    ML651 : ULINT;
    ML652 : ULINT;
    ML653 : ULINT;
    ML654 : ULINT;
    ML655 : ULINT;
    ML656 : ULINT;
    ML657 : ULINT;
    ML658 : ULINT;
    ML659 : ULINT;
    ML660 : ULINT;
    ML661 : ULINT;
    ML662 : ULINT;
    ML663 : ULINT;
    ML664 : ULINT;
    ML665 : ULINT;
    ML666 : ULINT;
    ML667 : ULINT;
    ML668 : ULINT;
    ML669 : ULINT;
    ML670 : ULINT;
    ML671 : ULINT;
    ML672 : ULINT;
    ML673 : ULINT;
    ML674 : ULINT;
    ML675 : ULINT;
    ML676 : ULINT;
    ML677 : ULINT;
    ML678 : ULINT;
    ML679 : ULINT;
    ML680 : ULINT;
    ML681 : ULINT;
    ML682 : ULINT;
    ML683 : ULINT;
    ML684 : ULINT;
    ML685 : ULINT;
    ML686 : ULINT;
    ML687 : ULINT;
    ML688 : ULINT;
    ML689 : ULINT;
    ML690 : ULINT;
    ML691 : ULINT;
    ML692 : ULINT;
    ML693 : ULINT;
    ML694 : ULINT;
    ML695 : ULINT;
    ML696 : ULINT;
    ML697 : ULINT;
    ML698 : ULINT;
    ML699 : ULINT;
    ML700 : ULINT;
    ML701 : ULINT;
    ML702 : ULINT;
    ML703 : ULINT;
    ML704 : ULINT;
    ML705 : ULINT;
    ML706 : ULINT;
    ML707 : ULINT;
    ML708 : ULINT;
    ML709 : ULINT;
    ML710 : ULINT;
    ML711 : ULINT;
    ML712 : ULINT;
    ML713 : ULINT;
    ML714 : ULINT;
    ML715 : ULINT;
    ML716 : ULINT;
    ML717 : ULINT;
    ML718 : ULINT;
    ML719 : ULINT;
    ML720 : ULINT;
    ML721 : ULINT;
    ML722 : ULINT;
    ML723 : ULINT;
    ML724 : ULINT;
    ML725 : ULINT;
    ML726 : ULINT;
    ML727 : ULINT;
    ML728 : ULINT;
    ML729 : ULINT;
    ML730 : ULINT;
    ML731 : ULINT;
    ML732 : ULINT;
    ML733 : ULINT;
    ML734 : ULINT;
    ML735 : ULINT;
    ML736 : ULINT;
    ML737 : ULINT;
    ML738 : ULINT;
    ML739 : ULINT;
    ML740 : ULINT;
    ML741 : ULINT;
    ML742 : ULINT;
    ML743 : ULINT;
    ML744 : ULINT;
    ML745 : ULINT;
    ML746 : ULINT;
    ML747 : ULINT;
    ML748 : ULINT;
    ML749 : ULINT;
    ML750 : ULINT;
    ML751 : ULINT;
    ML752 : ULINT;
    ML753 : ULINT;
    ML754 : ULINT;
    ML755 : ULINT;
    ML756 : ULINT;
    ML757 : ULINT;
    ML758 : ULINT;
    ML759 : ULINT;
    ML760 : ULINT;
    ML761 : ULINT;
    ML762 : ULINT;
    ML763 : ULINT;
    ML764 : ULINT;
    ML765 : ULINT;
    ML766 : ULINT;
    ML767 : ULINT;
    ML768 : ULINT;
    ML769 : ULINT;
    ML770 : ULINT;
    ML771 : ULINT;
    ML772 : ULINT;
    ML773 : ULINT;
    ML774 : ULINT;
    ML775 : ULINT;
    ML776 : ULINT;
    ML777 : ULINT;
    ML778 : ULINT;
    ML779 : ULINT;
    ML780 : ULINT;
    ML781 : ULINT;
    ML782 : ULINT;
    ML783 : ULINT;
    ML784 : ULINT;
    ML785 : ULINT;
    ML786 : ULINT;
    ML787 : ULINT;
    ML788 : ULINT;
    ML789 : ULINT;
    ML790 : ULINT;
    ML791 : ULINT;
    ML792 : ULINT;
    ML793 : ULINT;
    ML794 : ULINT;
    ML795 : ULINT;
    ML796 : ULINT;
    ML797 : ULINT;
    ML798 : ULINT;
    ML799 : ULINT;
    ML800 : ULINT;
    ML801 : ULINT;
    ML802 : ULINT;
    ML803 : ULINT;
    ML804 : ULINT;
    ML805 : ULINT;
    ML806 : ULINT;
    ML807 : ULINT;
    ML808 : ULINT;
    ML809 : ULINT;
    ML810 : ULINT;
    ML811 : ULINT;
    ML812 : ULINT;
    ML813 : ULINT;
    ML814 : ULINT;
    ML815 : ULINT;
    ML816 : ULINT;
    ML817 : ULINT;
    ML818 : ULINT;
    ML819 : ULINT;
    ML820 : ULINT;
    ML821 : ULINT;
    ML822 : ULINT;
    ML823 : ULINT;
    ML824 : ULINT;
    ML825 : ULINT;
    ML826 : ULINT;
    ML827 : ULINT;
    ML828 : ULINT;
    ML829 : ULINT;
    ML830 : ULINT;
    ML831 : ULINT;
    ML832 : ULINT;
    ML833 : ULINT;
    ML834 : ULINT;
    ML835 : ULINT;
    ML836 : ULINT;
    ML837 : ULINT;
    ML838 : ULINT;
    ML839 : ULINT;
    ML840 : ULINT;
    ML841 : ULINT;
    ML842 : ULINT;
    ML843 : ULINT;
    ML844 : ULINT;
    ML845 : ULINT;
    ML846 : ULINT;
    ML847 : ULINT;
    ML848 : ULINT;
    ML849 : ULINT;
    ML850 : ULINT;
    ML851 : ULINT;
    ML852 : ULINT;
    ML853 : ULINT;
    ML854 : ULINT;
    ML855 : ULINT;
    ML856 : ULINT;
    ML857 : ULINT;
    ML858 : ULINT;
    ML859 : ULINT;
    ML860 : ULINT;
    ML861 : ULINT;
    ML862 : ULINT;
    ML863 : ULINT;
    ML864 : ULINT;
    ML865 : ULINT;
    ML866 : ULINT;
    ML867 : ULINT;
    ML868 : ULINT;
    ML869 : ULINT;
    ML870 : ULINT;
    ML871 : ULINT;
    ML872 : ULINT;
    ML873 : ULINT;
    ML874 : ULINT;
    ML875 : ULINT;
    ML876 : ULINT;
    ML877 : ULINT;
    ML878 : ULINT;
    ML879 : ULINT;
    ML880 : ULINT;
    ML881 : ULINT;
    ML882 : ULINT;
    ML883 : ULINT;
    ML884 : ULINT;
    ML885 : ULINT;
    ML886 : ULINT;
    ML887 : ULINT;
    ML888 : ULINT;
    ML889 : ULINT;
    ML890 : ULINT;
    ML891 : ULINT;
    ML892 : ULINT;
    ML893 : ULINT;
    ML894 : ULINT;
    ML895 : ULINT;
    ML896 : ULINT;
    ML897 : ULINT;
    ML898 : ULINT;
    ML899 : ULINT;
    ML900 : ULINT;
    ML901 : ULINT;
    ML902 : ULINT;
    ML903 : ULINT;
    ML904 : ULINT;
    ML905 : ULINT;
    ML906 : ULINT;
    ML907 : ULINT;
    ML908 : ULINT;
    ML909 : ULINT;
    ML910 : ULINT;
    ML911 : ULINT;
    ML912 : ULINT;
    ML913 : ULINT;
    ML914 : ULINT;
    ML915 : ULINT;
    ML916 : ULINT;
    ML917 : ULINT;
    ML918 : ULINT;
    ML919 : ULINT;
    ML920 : ULINT;
    ML921 : ULINT;
    ML922 : ULINT;
    ML923 : ULINT;
    ML924 : ULINT;
    ML925 : ULINT;
    ML926 : ULINT;
    ML927 : ULINT;
    ML928 : ULINT;
    ML929 : ULINT;
    ML930 : ULINT;
    ML931 : ULINT;
    ML932 : ULINT;
    ML933 : ULINT;
    ML934 : ULINT;
    ML935 : ULINT;
    ML936 : ULINT;
    ML937 : ULINT;
    ML938 : ULINT;
    ML939 : ULINT;
    ML940 : ULINT;
    ML941 : ULINT;
    ML942 : ULINT;
    ML943 : ULINT;
    ML944 : ULINT;
    ML945 : ULINT;
    ML946 : ULINT;
    ML947 : ULINT;
    ML948 : ULINT;
    ML949 : ULINT;
    ML950 : ULINT;
    ML951 : ULINT;
    ML952 : ULINT;
    ML953 : ULINT;
    ML954 : ULINT;
    ML955 : ULINT;
    ML956 : ULINT;
    ML957 : ULINT;
    ML958 : ULINT;
    ML959 : ULINT;
    ML960 : ULINT;
    ML961 : ULINT;
    ML962 : ULINT;
    ML963 : ULINT;
    ML964 : ULINT;
    ML965 : ULINT;
    ML966 : ULINT;
    ML967 : ULINT;
    ML968 : ULINT;
    ML969 : ULINT;
    ML970 : ULINT;
    ML971 : ULINT;
    ML972 : ULINT;
    ML973 : ULINT;
    ML974 : ULINT;
    ML975 : ULINT;
    ML976 : ULINT;
    ML977 : ULINT;
    ML978 : ULINT;
    ML979 : ULINT;
    ML980 : ULINT;
    ML981 : ULINT;
    ML982 : ULINT;
    ML983 : ULINT;
    ML984 : ULINT;
    ML985 : ULINT;
    ML986 : ULINT;
    ML987 : ULINT;
    ML988 : ULINT;
    ML989 : ULINT;
    ML990 : ULINT;
    ML991 : ULINT;
    ML992 : ULINT;
    ML993 : ULINT;
    ML994 : ULINT;
    ML995 : ULINT;
    ML996 : ULINT;
    ML997 : ULINT;
    ML998 : ULINT;
    ML999 : ULINT;
    ML1000 : ULINT;
    ML1001 : ULINT;
    ML1002 : ULINT;
    ML1003 : ULINT;
    ML1004 : ULINT;
    ML1005 : ULINT;
    ML1006 : ULINT;
    ML1007 : ULINT;
    ML1008 : ULINT;
    ML1009 : ULINT;
    ML1010 : ULINT;
    ML1011 : ULINT;
    ML1012 : ULINT;
    ML1013 : ULINT;
    ML1014 : ULINT;
    ML1015 : ULINT;
    ML1016 : ULINT;
    ML1017 : ULINT;
    ML1018 : ULINT;
    ML1019 : ULINT;
    ML1020 : ULINT;
    ML1021 : ULINT;
    ML1022 : ULINT;
    ML1023 : ULINT;
  END_VAR
  VAR_INPUT
    I : INT := 0;
    LONG4 : ARRAY [0..3] OF ULINT;
  END_VAR
  VAR
    DIST : DistLong4;
  END_VAR

  CASE I OF
  0:  DIST(LONG4:=LONG4, ML0=>ML0,  ML1=>ML1,  ML2=>ML2,  ML3=>ML3);
  1:  DIST(LONG4:=LONG4, ML0=>ML4,  ML1=>ML5,  ML2=>ML6,  ML3=>ML7);
  2:  DIST(LONG4:=LONG4, ML0=>ML8,  ML1=>ML9,  ML2=>ML10, ML3=>ML11);
  3:  DIST(LONG4:=LONG4, ML0=>ML12, ML1=>ML13, ML2=>ML14, ML3=>ML15);
  4:  DIST(LONG4:=LONG4, ML0=>ML16, ML1=>ML17, ML2=>ML18, ML3=>ML19);
  5:  DIST(LONG4:=LONG4, ML0=>ML20, ML1=>ML21, ML2=>ML22, ML3=>ML23);
  6:  DIST(LONG4:=LONG4, ML0=>ML24, ML1=>ML25, ML2=>ML26, ML3=>ML27);
  7:  DIST(LONG4:=LONG4, ML0=>ML28, ML1=>ML29, ML2=>ML30, ML3=>ML31);
  8:  DIST(LONG4:=LONG4, ML0=>ML32, ML1=>ML33, ML2=>ML34, ML3=>ML35);
  9:  DIST(LONG4:=LONG4, ML0=>ML36, ML1=>ML37, ML2=>ML38, ML3=>ML39);
  10: DIST(LONG4:=LONG4, ML0=>ML40, ML1=>ML41, ML2=>ML42, ML3=>ML43);
  11: DIST(LONG4:=LONG4, ML0=>ML44, ML1=>ML45, ML2=>ML46, ML3=>ML47);
  12: DIST(LONG4:=LONG4, ML0=>ML48, ML1=>ML49, ML2=>ML50, ML3=>ML51);
  13: DIST(LONG4:=LONG4, ML0=>ML52, ML1=>ML53, ML2=>ML54, ML3=>ML55);
  14: DIST(LONG4:=LONG4, ML0=>ML56, ML1=>ML57, ML2=>ML58, ML3=>ML59);
  15: DIST(LONG4:=LONG4, ML0=>ML60, ML1=>ML61, ML2=>ML62, ML3=>ML63);
  16: DIST(LONG4:=LONG4, ML0=>ML64, ML1=>ML65, ML2=>ML66, ML3=>ML67);
  17: DIST(LONG4:=LONG4, ML0=>ML68, ML1=>ML69, ML2=>ML70, ML3=>ML71);
  18: DIST(LONG4:=LONG4, ML0=>ML72, ML1=>ML73, ML2=>ML74, ML3=>ML75);
  19: DIST(LONG4:=LONG4, ML0=>ML76, ML1=>ML77, ML2=>ML78, ML3=>ML79);
  20: DIST(LONG4:=LONG4, ML0=>ML80, ML1=>ML81, ML2=>ML82, ML3=>ML83);
  21: DIST(LONG4:=LONG4, ML0=>ML84, ML1=>ML85, ML2=>ML86, ML3=>ML87);
  22: DIST(LONG4:=LONG4, ML0=>ML88, ML1=>ML89, ML2=>ML90, ML3=>ML91);
  23: DIST(LONG4:=LONG4, ML0=>ML92, ML1=>ML93, ML2=>ML94, ML3=>ML95);
  24: DIST(LONG4:=LONG4, ML0=>ML96, ML1=>ML97, ML2=>ML98, ML3=>ML99);
  25: DIST(LONG4:=LONG4, ML0=>ML100, ML1=>ML101, ML2=>ML102, ML3=>ML103);
  26: DIST(LONG4:=LONG4, ML0=>ML104, ML1=>ML105, ML2=>ML106, ML3=>ML107);
  27: DIST(LONG4:=LONG4, ML0=>ML108, ML1=>ML109, ML2=>ML110, ML3=>ML111);
  28: DIST(LONG4:=LONG4, ML0=>ML112, ML1=>ML113, ML2=>ML114, ML3=>ML115);
  29: DIST(LONG4:=LONG4, ML0=>ML116, ML1=>ML117, ML2=>ML118, ML3=>ML119);
  30: DIST(LONG4:=LONG4, ML0=>ML120, ML1=>ML121, ML2=>ML122, ML3=>ML123);
  31: DIST(LONG4:=LONG4, ML0=>ML124, ML1=>ML125, ML2=>ML126, ML3=>ML127);
  32: DIST(LONG4:=LONG4, ML0=>ML128, ML1=>ML129, ML2=>ML130, ML3=>ML131);
  33: DIST(LONG4:=LONG4, ML0=>ML132, ML1=>ML133, ML2=>ML134, ML3=>ML135);
  34: DIST(LONG4:=LONG4, ML0=>ML136, ML1=>ML137, ML2=>ML138, ML3=>ML139);
  35: DIST(LONG4:=LONG4, ML0=>ML140, ML1=>ML141, ML2=>ML142, ML3=>ML143);
  36: DIST(LONG4:=LONG4, ML0=>ML144, ML1=>ML145, ML2=>ML146, ML3=>ML147);
  37: DIST(LONG4:=LONG4, ML0=>ML148, ML1=>ML149, ML2=>ML150, ML3=>ML151);
  38: DIST(LONG4:=LONG4, ML0=>ML152, ML1=>ML153, ML2=>ML154, ML3=>ML155);
  39: DIST(LONG4:=LONG4, ML0=>ML156, ML1=>ML157, ML2=>ML158, ML3=>ML159);
  40: DIST(LONG4:=LONG4, ML0=>ML160, ML1=>ML161, ML2=>ML162, ML3=>ML163);
  41: DIST(LONG4:=LONG4, ML0=>ML164, ML1=>ML165, ML2=>ML166, ML3=>ML167);
  42: DIST(LONG4:=LONG4, ML0=>ML168, ML1=>ML169, ML2=>ML170, ML3=>ML171);
  43: DIST(LONG4:=LONG4, ML0=>ML172, ML1=>ML173, ML2=>ML174, ML3=>ML175);
  44: DIST(LONG4:=LONG4, ML0=>ML176, ML1=>ML177, ML2=>ML178, ML3=>ML179);
  45: DIST(LONG4:=LONG4, ML0=>ML180, ML1=>ML181, ML2=>ML182, ML3=>ML183);
  46: DIST(LONG4:=LONG4, ML0=>ML184, ML1=>ML185, ML2=>ML186, ML3=>ML187);
  47: DIST(LONG4:=LONG4, ML0=>ML188, ML1=>ML189, ML2=>ML190, ML3=>ML191);
  48: DIST(LONG4:=LONG4, ML0=>ML192, ML1=>ML193, ML2=>ML194, ML3=>ML195);
  49: DIST(LONG4:=LONG4, ML0=>ML196, ML1=>ML197, ML2=>ML198, ML3=>ML199);
  50: DIST(LONG4:=LONG4, ML0=>ML200, ML1=>ML201, ML2=>ML202, ML3=>ML203);
  51: DIST(LONG4:=LONG4, ML0=>ML204, ML1=>ML205, ML2=>ML206, ML3=>ML207);
  52: DIST(LONG4:=LONG4, ML0=>ML208, ML1=>ML209, ML2=>ML210, ML3=>ML211);
  53: DIST(LONG4:=LONG4, ML0=>ML212, ML1=>ML213, ML2=>ML214, ML3=>ML215);
  54: DIST(LONG4:=LONG4, ML0=>ML216, ML1=>ML217, ML2=>ML218, ML3=>ML219);
  55: DIST(LONG4:=LONG4, ML0=>ML220, ML1=>ML221, ML2=>ML222, ML3=>ML223);
  56: DIST(LONG4:=LONG4, ML0=>ML224, ML1=>ML225, ML2=>ML226, ML3=>ML227);
  57: DIST(LONG4:=LONG4, ML0=>ML228, ML1=>ML229, ML2=>ML230, ML3=>ML231);
  58: DIST(LONG4:=LONG4, ML0=>ML232, ML1=>ML233, ML2=>ML234, ML3=>ML235);
  59: DIST(LONG4:=LONG4, ML0=>ML236, ML1=>ML237, ML2=>ML238, ML3=>ML239);
  60: DIST(LONG4:=LONG4, ML0=>ML240, ML1=>ML241, ML2=>ML242, ML3=>ML243);
  61: DIST(LONG4:=LONG4, ML0=>ML244, ML1=>ML245, ML2=>ML246, ML3=>ML247);
  62: DIST(LONG4:=LONG4, ML0=>ML248, ML1=>ML249, ML2=>ML250, ML3=>ML251);
  63: DIST(LONG4:=LONG4, ML0=>ML252, ML1=>ML253, ML2=>ML254, ML3=>ML255);
  64: DIST(LONG4:=LONG4, ML0=>ML256, ML1=>ML257, ML2=>ML258, ML3=>ML259);
  65: DIST(LONG4:=LONG4, ML0=>ML260, ML1=>ML261, ML2=>ML262, ML3=>ML263);
  66: DIST(LONG4:=LONG4, ML0=>ML264, ML1=>ML265, ML2=>ML266, ML3=>ML267);
  67: DIST(LONG4:=LONG4, ML0=>ML268, ML1=>ML269, ML2=>ML270, ML3=>ML271);
  68: DIST(LONG4:=LONG4, ML0=>ML272, ML1=>ML273, ML2=>ML274, ML3=>ML275);
  69: DIST(LONG4:=LONG4, ML0=>ML276, ML1=>ML277, ML2=>ML278, ML3=>ML279);
  70: DIST(LONG4:=LONG4, ML0=>ML280, ML1=>ML281, ML2=>ML282, ML3=>ML283);
  71: DIST(LONG4:=LONG4, ML0=>ML284, ML1=>ML285, ML2=>ML286, ML3=>ML287);
  72: DIST(LONG4:=LONG4, ML0=>ML288, ML1=>ML289, ML2=>ML290, ML3=>ML291);
  73: DIST(LONG4:=LONG4, ML0=>ML292, ML1=>ML293, ML2=>ML294, ML3=>ML295);
  74: DIST(LONG4:=LONG4, ML0=>ML296, ML1=>ML297, ML2=>ML298, ML3=>ML299);
  75: DIST(LONG4:=LONG4, ML0=>ML300, ML1=>ML301, ML2=>ML302, ML3=>ML303);
  76: DIST(LONG4:=LONG4, ML0=>ML304, ML1=>ML305, ML2=>ML306, ML3=>ML307);
  77: DIST(LONG4:=LONG4, ML0=>ML308, ML1=>ML309, ML2=>ML310, ML3=>ML311);
  78: DIST(LONG4:=LONG4, ML0=>ML312, ML1=>ML313, ML2=>ML314, ML3=>ML315);
  79: DIST(LONG4:=LONG4, ML0=>ML316, ML1=>ML317, ML2=>ML318, ML3=>ML319);
  80: DIST(LONG4:=LONG4, ML0=>ML320, ML1=>ML321, ML2=>ML322, ML3=>ML323);
  81: DIST(LONG4:=LONG4, ML0=>ML324, ML1=>ML325, ML2=>ML326, ML3=>ML327);
  82: DIST(LONG4:=LONG4, ML0=>ML328, ML1=>ML329, ML2=>ML330, ML3=>ML331);
  83: DIST(LONG4:=LONG4, ML0=>ML332, ML1=>ML333, ML2=>ML334, ML3=>ML335);
  84: DIST(LONG4:=LONG4, ML0=>ML336, ML1=>ML337, ML2=>ML338, ML3=>ML339);
  85: DIST(LONG4:=LONG4, ML0=>ML340, ML1=>ML341, ML2=>ML342, ML3=>ML343);
  86: DIST(LONG4:=LONG4, ML0=>ML344, ML1=>ML345, ML2=>ML346, ML3=>ML347);
  87: DIST(LONG4:=LONG4, ML0=>ML348, ML1=>ML349, ML2=>ML350, ML3=>ML351);
  88: DIST(LONG4:=LONG4, ML0=>ML352, ML1=>ML353, ML2=>ML354, ML3=>ML355);
  89: DIST(LONG4:=LONG4, ML0=>ML356, ML1=>ML357, ML2=>ML358, ML3=>ML359);
  90: DIST(LONG4:=LONG4, ML0=>ML360, ML1=>ML361, ML2=>ML362, ML3=>ML363);
  91: DIST(LONG4:=LONG4, ML0=>ML364, ML1=>ML365, ML2=>ML366, ML3=>ML367);
  92: DIST(LONG4:=LONG4, ML0=>ML368, ML1=>ML369, ML2=>ML370, ML3=>ML371);
  93: DIST(LONG4:=LONG4, ML0=>ML372, ML1=>ML373, ML2=>ML374, ML3=>ML375);
  94: DIST(LONG4:=LONG4, ML0=>ML376, ML1=>ML377, ML2=>ML378, ML3=>ML379);
  95: DIST(LONG4:=LONG4, ML0=>ML380, ML1=>ML381, ML2=>ML382, ML3=>ML383);
  96: DIST(LONG4:=LONG4, ML0=>ML384, ML1=>ML385, ML2=>ML386, ML3=>ML387);
  97: DIST(LONG4:=LONG4, ML0=>ML388, ML1=>ML389, ML2=>ML390, ML3=>ML391);
  98: DIST(LONG4:=LONG4, ML0=>ML392, ML1=>ML393, ML2=>ML394, ML3=>ML395);
  99: DIST(LONG4:=LONG4, ML0=>ML396, ML1=>ML397, ML2=>ML398, ML3=>ML399);
  100: DIST(LONG4:=LONG4, ML0=>ML400, ML1=>ML401, ML2=>ML402, ML3=>ML403);
  101: DIST(LONG4:=LONG4, ML0=>ML404, ML1=>ML405, ML2=>ML406, ML3=>ML407);
  102: DIST(LONG4:=LONG4, ML0=>ML408, ML1=>ML409, ML2=>ML410, ML3=>ML411);
  103: DIST(LONG4:=LONG4, ML0=>ML412, ML1=>ML413, ML2=>ML414, ML3=>ML415);
  104: DIST(LONG4:=LONG4, ML0=>ML416, ML1=>ML417, ML2=>ML418, ML3=>ML419);
  105: DIST(LONG4:=LONG4, ML0=>ML420, ML1=>ML421, ML2=>ML422, ML3=>ML423);
  106: DIST(LONG4:=LONG4, ML0=>ML424, ML1=>ML425, ML2=>ML426, ML3=>ML427);
  107: DIST(LONG4:=LONG4, ML0=>ML428, ML1=>ML429, ML2=>ML430, ML3=>ML431);
  108: DIST(LONG4:=LONG4, ML0=>ML432, ML1=>ML433, ML2=>ML434, ML3=>ML435);
  109: DIST(LONG4:=LONG4, ML0=>ML436, ML1=>ML437, ML2=>ML438, ML3=>ML439);
  110: DIST(LONG4:=LONG4, ML0=>ML440, ML1=>ML441, ML2=>ML442, ML3=>ML443);
  111: DIST(LONG4:=LONG4, ML0=>ML444, ML1=>ML445, ML2=>ML446, ML3=>ML447);
  112: DIST(LONG4:=LONG4, ML0=>ML448, ML1=>ML449, ML2=>ML450, ML3=>ML451);
  113: DIST(LONG4:=LONG4, ML0=>ML452, ML1=>ML453, ML2=>ML454, ML3=>ML455);
  114: DIST(LONG4:=LONG4, ML0=>ML456, ML1=>ML457, ML2=>ML458, ML3=>ML459);
  115: DIST(LONG4:=LONG4, ML0=>ML460, ML1=>ML461, ML2=>ML462, ML3=>ML463);
  116: DIST(LONG4:=LONG4, ML0=>ML464, ML1=>ML465, ML2=>ML466, ML3=>ML467);
  117: DIST(LONG4:=LONG4, ML0=>ML468, ML1=>ML469, ML2=>ML470, ML3=>ML471);
  118: DIST(LONG4:=LONG4, ML0=>ML472, ML1=>ML473, ML2=>ML474, ML3=>ML475);
  119: DIST(LONG4:=LONG4, ML0=>ML476, ML1=>ML477, ML2=>ML478, ML3=>ML479);
  120: DIST(LONG4:=LONG4, ML0=>ML480, ML1=>ML481, ML2=>ML482, ML3=>ML483);
  121: DIST(LONG4:=LONG4, ML0=>ML484, ML1=>ML485, ML2=>ML486, ML3=>ML487);
  122: DIST(LONG4:=LONG4, ML0=>ML488, ML1=>ML489, ML2=>ML490, ML3=>ML491);
  123: DIST(LONG4:=LONG4, ML0=>ML492, ML1=>ML493, ML2=>ML494, ML3=>ML495);
  124: DIST(LONG4:=LONG4, ML0=>ML496, ML1=>ML497, ML2=>ML498, ML3=>ML499);
  125: DIST(LONG4:=LONG4, ML0=>ML500, ML1=>ML501, ML2=>ML502, ML3=>ML503);
  126: DIST(LONG4:=LONG4, ML0=>ML504, ML1=>ML505, ML2=>ML506, ML3=>ML507);
  127: DIST(LONG4:=LONG4, ML0=>ML508, ML1=>ML509, ML2=>ML510, ML3=>ML511);
  128: DIST(LONG4:=LONG4, ML0=>ML512, ML1=>ML513, ML2=>ML514, ML3=>ML515);
  129: DIST(LONG4:=LONG4, ML0=>ML516, ML1=>ML517, ML2=>ML518, ML3=>ML519);
  130: DIST(LONG4:=LONG4, ML0=>ML520, ML1=>ML521, ML2=>ML522, ML3=>ML523);
  131: DIST(LONG4:=LONG4, ML0=>ML524, ML1=>ML525, ML2=>ML526, ML3=>ML527);
  132: DIST(LONG4:=LONG4, ML0=>ML528, ML1=>ML529, ML2=>ML530, ML3=>ML531);
  133: DIST(LONG4:=LONG4, ML0=>ML532, ML1=>ML533, ML2=>ML534, ML3=>ML535);
  134: DIST(LONG4:=LONG4, ML0=>ML536, ML1=>ML537, ML2=>ML538, ML3=>ML539);
  135: DIST(LONG4:=LONG4, ML0=>ML540, ML1=>ML541, ML2=>ML542, ML3=>ML543);
  136: DIST(LONG4:=LONG4, ML0=>ML544, ML1=>ML545, ML2=>ML546, ML3=>ML547);
  137: DIST(LONG4:=LONG4, ML0=>ML548, ML1=>ML549, ML2=>ML550, ML3=>ML551);
  138: DIST(LONG4:=LONG4, ML0=>ML552, ML1=>ML553, ML2=>ML554, ML3=>ML555);
  139: DIST(LONG4:=LONG4, ML0=>ML556, ML1=>ML557, ML2=>ML558, ML3=>ML559);
  140: DIST(LONG4:=LONG4, ML0=>ML560, ML1=>ML561, ML2=>ML562, ML3=>ML563);
  141: DIST(LONG4:=LONG4, ML0=>ML564, ML1=>ML565, ML2=>ML566, ML3=>ML567);
  142: DIST(LONG4:=LONG4, ML0=>ML568, ML1=>ML569, ML2=>ML570, ML3=>ML571);
  143: DIST(LONG4:=LONG4, ML0=>ML572, ML1=>ML573, ML2=>ML574, ML3=>ML575);
  144: DIST(LONG4:=LONG4, ML0=>ML576, ML1=>ML577, ML2=>ML578, ML3=>ML579);
  145: DIST(LONG4:=LONG4, ML0=>ML580, ML1=>ML581, ML2=>ML582, ML3=>ML583);
  146: DIST(LONG4:=LONG4, ML0=>ML584, ML1=>ML585, ML2=>ML586, ML3=>ML587);
  147: DIST(LONG4:=LONG4, ML0=>ML588, ML1=>ML589, ML2=>ML590, ML3=>ML591);
  148: DIST(LONG4:=LONG4, ML0=>ML592, ML1=>ML593, ML2=>ML594, ML3=>ML595);
  149: DIST(LONG4:=LONG4, ML0=>ML596, ML1=>ML597, ML2=>ML598, ML3=>ML599);
  150: DIST(LONG4:=LONG4, ML0=>ML600, ML1=>ML601, ML2=>ML602, ML3=>ML603);
  151: DIST(LONG4:=LONG4, ML0=>ML604, ML1=>ML605, ML2=>ML606, ML3=>ML607);
  152: DIST(LONG4:=LONG4, ML0=>ML608, ML1=>ML609, ML2=>ML610, ML3=>ML611);
  153: DIST(LONG4:=LONG4, ML0=>ML612, ML1=>ML613, ML2=>ML614, ML3=>ML615);
  154: DIST(LONG4:=LONG4, ML0=>ML616, ML1=>ML617, ML2=>ML618, ML3=>ML619);
  155: DIST(LONG4:=LONG4, ML0=>ML620, ML1=>ML621, ML2=>ML622, ML3=>ML623);
  156: DIST(LONG4:=LONG4, ML0=>ML624, ML1=>ML625, ML2=>ML626, ML3=>ML627);
  157: DIST(LONG4:=LONG4, ML0=>ML628, ML1=>ML629, ML2=>ML630, ML3=>ML631);
  158: DIST(LONG4:=LONG4, ML0=>ML632, ML1=>ML633, ML2=>ML634, ML3=>ML635);
  159: DIST(LONG4:=LONG4, ML0=>ML636, ML1=>ML637, ML2=>ML638, ML3=>ML639);
  160: DIST(LONG4:=LONG4, ML0=>ML640, ML1=>ML641, ML2=>ML642, ML3=>ML643);
  161: DIST(LONG4:=LONG4, ML0=>ML644, ML1=>ML645, ML2=>ML646, ML3=>ML647);
  162: DIST(LONG4:=LONG4, ML0=>ML648, ML1=>ML649, ML2=>ML650, ML3=>ML651);
  163: DIST(LONG4:=LONG4, ML0=>ML652, ML1=>ML653, ML2=>ML654, ML3=>ML655);
  164: DIST(LONG4:=LONG4, ML0=>ML656, ML1=>ML657, ML2=>ML658, ML3=>ML659);
  165: DIST(LONG4:=LONG4, ML0=>ML660, ML1=>ML661, ML2=>ML662, ML3=>ML663);
  166: DIST(LONG4:=LONG4, ML0=>ML664, ML1=>ML665, ML2=>ML666, ML3=>ML667);
  167: DIST(LONG4:=LONG4, ML0=>ML668, ML1=>ML669, ML2=>ML670, ML3=>ML671);
  168: DIST(LONG4:=LONG4, ML0=>ML672, ML1=>ML673, ML2=>ML674, ML3=>ML675);
  169: DIST(LONG4:=LONG4, ML0=>ML676, ML1=>ML677, ML2=>ML678, ML3=>ML679);
  170: DIST(LONG4:=LONG4, ML0=>ML680, ML1=>ML681, ML2=>ML682, ML3=>ML683);
  171: DIST(LONG4:=LONG4, ML0=>ML684, ML1=>ML685, ML2=>ML686, ML3=>ML687);
  172: DIST(LONG4:=LONG4, ML0=>ML688, ML1=>ML689, ML2=>ML690, ML3=>ML691);
  173: DIST(LONG4:=LONG4, ML0=>ML692, ML1=>ML693, ML2=>ML694, ML3=>ML695);
  174: DIST(LONG4:=LONG4, ML0=>ML696, ML1=>ML697, ML2=>ML698, ML3=>ML699);
  175: DIST(LONG4:=LONG4, ML0=>ML700, ML1=>ML701, ML2=>ML702, ML3=>ML703);
  176: DIST(LONG4:=LONG4, ML0=>ML704, ML1=>ML705, ML2=>ML706, ML3=>ML707);
  177: DIST(LONG4:=LONG4, ML0=>ML708, ML1=>ML709, ML2=>ML710, ML3=>ML711);
  178: DIST(LONG4:=LONG4, ML0=>ML712, ML1=>ML713, ML2=>ML714, ML3=>ML715);
  179: DIST(LONG4:=LONG4, ML0=>ML716, ML1=>ML717, ML2=>ML718, ML3=>ML719);
  180: DIST(LONG4:=LONG4, ML0=>ML720, ML1=>ML721, ML2=>ML722, ML3=>ML723);
  181: DIST(LONG4:=LONG4, ML0=>ML724, ML1=>ML725, ML2=>ML726, ML3=>ML727);
  182: DIST(LONG4:=LONG4, ML0=>ML728, ML1=>ML729, ML2=>ML730, ML3=>ML731);
  183: DIST(LONG4:=LONG4, ML0=>ML732, ML1=>ML733, ML2=>ML734, ML3=>ML735);
  184: DIST(LONG4:=LONG4, ML0=>ML736, ML1=>ML737, ML2=>ML738, ML3=>ML739);
  185: DIST(LONG4:=LONG4, ML0=>ML740, ML1=>ML741, ML2=>ML742, ML3=>ML743);
  186: DIST(LONG4:=LONG4, ML0=>ML744, ML1=>ML745, ML2=>ML746, ML3=>ML747);
  187: DIST(LONG4:=LONG4, ML0=>ML748, ML1=>ML749, ML2=>ML750, ML3=>ML751);
  188: DIST(LONG4:=LONG4, ML0=>ML752, ML1=>ML753, ML2=>ML754, ML3=>ML755);
  189: DIST(LONG4:=LONG4, ML0=>ML756, ML1=>ML757, ML2=>ML758, ML3=>ML759);
  190: DIST(LONG4:=LONG4, ML0=>ML760, ML1=>ML761, ML2=>ML762, ML3=>ML763);
  191: DIST(LONG4:=LONG4, ML0=>ML764, ML1=>ML765, ML2=>ML766, ML3=>ML767);
  192: DIST(LONG4:=LONG4, ML0=>ML768, ML1=>ML769, ML2=>ML770, ML3=>ML771);
  193: DIST(LONG4:=LONG4, ML0=>ML772, ML1=>ML773, ML2=>ML774, ML3=>ML775);
  194: DIST(LONG4:=LONG4, ML0=>ML776, ML1=>ML777, ML2=>ML778, ML3=>ML779);
  195: DIST(LONG4:=LONG4, ML0=>ML780, ML1=>ML781, ML2=>ML782, ML3=>ML783);
  196: DIST(LONG4:=LONG4, ML0=>ML784, ML1=>ML785, ML2=>ML786, ML3=>ML787);
  197: DIST(LONG4:=LONG4, ML0=>ML788, ML1=>ML789, ML2=>ML790, ML3=>ML791);
  198: DIST(LONG4:=LONG4, ML0=>ML792, ML1=>ML793, ML2=>ML794, ML3=>ML795);
  199: DIST(LONG4:=LONG4, ML0=>ML796, ML1=>ML797, ML2=>ML798, ML3=>ML799);
  200: DIST(LONG4:=LONG4, ML0=>ML800, ML1=>ML801, ML2=>ML802, ML3=>ML803);
  201: DIST(LONG4:=LONG4, ML0=>ML804, ML1=>ML805, ML2=>ML806, ML3=>ML807);
  202: DIST(LONG4:=LONG4, ML0=>ML808, ML1=>ML809, ML2=>ML810, ML3=>ML811);
  203: DIST(LONG4:=LONG4, ML0=>ML812, ML1=>ML813, ML2=>ML814, ML3=>ML815);
  204: DIST(LONG4:=LONG4, ML0=>ML816, ML1=>ML817, ML2=>ML818, ML3=>ML819);
  205: DIST(LONG4:=LONG4, ML0=>ML820, ML1=>ML821, ML2=>ML822, ML3=>ML823);
  206: DIST(LONG4:=LONG4, ML0=>ML824, ML1=>ML825, ML2=>ML826, ML3=>ML827);
  207: DIST(LONG4:=LONG4, ML0=>ML828, ML1=>ML829, ML2=>ML830, ML3=>ML831);
  208: DIST(LONG4:=LONG4, ML0=>ML832, ML1=>ML833, ML2=>ML834, ML3=>ML835);
  209: DIST(LONG4:=LONG4, ML0=>ML836, ML1=>ML837, ML2=>ML838, ML3=>ML839);
  210: DIST(LONG4:=LONG4, ML0=>ML840, ML1=>ML841, ML2=>ML842, ML3=>ML843);
  211: DIST(LONG4:=LONG4, ML0=>ML844, ML1=>ML845, ML2=>ML846, ML3=>ML847);
  212: DIST(LONG4:=LONG4, ML0=>ML848, ML1=>ML849, ML2=>ML850, ML3=>ML851);
  213: DIST(LONG4:=LONG4, ML0=>ML852, ML1=>ML853, ML2=>ML854, ML3=>ML855);
  214: DIST(LONG4:=LONG4, ML0=>ML856, ML1=>ML857, ML2=>ML858, ML3=>ML859);
  215: DIST(LONG4:=LONG4, ML0=>ML860, ML1=>ML861, ML2=>ML862, ML3=>ML863);
  216: DIST(LONG4:=LONG4, ML0=>ML864, ML1=>ML865, ML2=>ML866, ML3=>ML867);
  217: DIST(LONG4:=LONG4, ML0=>ML868, ML1=>ML869, ML2=>ML870, ML3=>ML871);
  218: DIST(LONG4:=LONG4, ML0=>ML872, ML1=>ML873, ML2=>ML874, ML3=>ML875);
  219: DIST(LONG4:=LONG4, ML0=>ML876, ML1=>ML877, ML2=>ML878, ML3=>ML879);
  220: DIST(LONG4:=LONG4, ML0=>ML880, ML1=>ML881, ML2=>ML882, ML3=>ML883);
  221: DIST(LONG4:=LONG4, ML0=>ML884, ML1=>ML885, ML2=>ML886, ML3=>ML887);
  222: DIST(LONG4:=LONG4, ML0=>ML888, ML1=>ML889, ML2=>ML890, ML3=>ML891);
  223: DIST(LONG4:=LONG4, ML0=>ML892, ML1=>ML893, ML2=>ML894, ML3=>ML895);
  224: DIST(LONG4:=LONG4, ML0=>ML896, ML1=>ML897, ML2=>ML898, ML3=>ML899);
  225: DIST(LONG4:=LONG4, ML0=>ML900, ML1=>ML901, ML2=>ML902, ML3=>ML903);
  226: DIST(LONG4:=LONG4, ML0=>ML904, ML1=>ML905, ML2=>ML906, ML3=>ML907);
  227: DIST(LONG4:=LONG4, ML0=>ML908, ML1=>ML909, ML2=>ML910, ML3=>ML911);
  228: DIST(LONG4:=LONG4, ML0=>ML912, ML1=>ML913, ML2=>ML914, ML3=>ML915);
  229: DIST(LONG4:=LONG4, ML0=>ML916, ML1=>ML917, ML2=>ML918, ML3=>ML919);
  230: DIST(LONG4:=LONG4, ML0=>ML920, ML1=>ML921, ML2=>ML922, ML3=>ML923);
  231: DIST(LONG4:=LONG4, ML0=>ML924, ML1=>ML925, ML2=>ML926, ML3=>ML927);
  232: DIST(LONG4:=LONG4, ML0=>ML928, ML1=>ML929, ML2=>ML930, ML3=>ML931);
  233: DIST(LONG4:=LONG4, ML0=>ML932, ML1=>ML933, ML2=>ML934, ML3=>ML935);
  234: DIST(LONG4:=LONG4, ML0=>ML936, ML1=>ML937, ML2=>ML938, ML3=>ML939);
  235: DIST(LONG4:=LONG4, ML0=>ML940, ML1=>ML941, ML2=>ML942, ML3=>ML943);
  236: DIST(LONG4:=LONG4, ML0=>ML944, ML1=>ML945, ML2=>ML946, ML3=>ML947);
  237: DIST(LONG4:=LONG4, ML0=>ML948, ML1=>ML949, ML2=>ML950, ML3=>ML951);
  238: DIST(LONG4:=LONG4, ML0=>ML952, ML1=>ML953, ML2=>ML954, ML3=>ML955);
  239: DIST(LONG4:=LONG4, ML0=>ML956, ML1=>ML957, ML2=>ML958, ML3=>ML959);
  240: DIST(LONG4:=LONG4, ML0=>ML960, ML1=>ML961, ML2=>ML962, ML3=>ML963);
  241: DIST(LONG4:=LONG4, ML0=>ML964, ML1=>ML965, ML2=>ML966, ML3=>ML967);
  242: DIST(LONG4:=LONG4, ML0=>ML968, ML1=>ML969, ML2=>ML970, ML3=>ML971);
  243: DIST(LONG4:=LONG4, ML0=>ML972, ML1=>ML973, ML2=>ML974, ML3=>ML975);
  244: DIST(LONG4:=LONG4, ML0=>ML976, ML1=>ML977, ML2=>ML978, ML3=>ML979);
  245: DIST(LONG4:=LONG4, ML0=>ML980, ML1=>ML981, ML2=>ML982, ML3=>ML983);
  246: DIST(LONG4:=LONG4, ML0=>ML984, ML1=>ML985, ML2=>ML986, ML3=>ML987);
  247: DIST(LONG4:=LONG4, ML0=>ML988, ML1=>ML989, ML2=>ML990, ML3=>ML991);
  248: DIST(LONG4:=LONG4, ML0=>ML992, ML1=>ML993, ML2=>ML994, ML3=>ML995);
  249: DIST(LONG4:=LONG4, ML0=>ML996, ML1=>ML997, ML2=>ML998, ML3=>ML999);
  250: DIST(LONG4:=LONG4, ML0=>ML1000, ML1=>ML1001, ML2=>ML1002, ML3=>ML1003);
  251: DIST(LONG4:=LONG4, ML0=>ML1004, ML1=>ML1005, ML2=>ML1006, ML3=>ML1007);
  252: DIST(LONG4:=LONG4, ML0=>ML1008, ML1=>ML1009, ML2=>ML1010, ML3=>ML1011);
  253: DIST(LONG4:=LONG4, ML0=>ML1012, ML1=>ML1013, ML2=>ML1014, ML3=>ML1015);
  254: DIST(LONG4:=LONG4, ML0=>ML1016, ML1=>ML1017, ML2=>ML1018, ML3=>ML1019);
  255: DIST(LONG4:=LONG4, ML0=>ML1020, ML1=>ML1021, ML2=>ML1022, ML3=>ML1023);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION knoff : P_INT
  VAR_INPUT
    Nx : INT := 1;
    Ny : INT := 1;
    Nz : INT := 1;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
  END_VAR

  knoff.A := 0;  (* начальное смещение 0-ячейки в массиве Grid *)
  knoff.B := 1;  (* количество ячеек  в массиве Grid (min = 1) *)
  if (K > 0) then
    knoff.A := knoff.A + K*2*(Nx+Ny) + (K+1)*Nx*Ny;
    if (K = (Nz-1)) then knoff.B := knoff.B+1; end_if;
  else knoff.B := knoff.B+1;
  end_if;
  if (J > 0) then
    knoff.A := knoff.A + J*(2+knoff.B*Nx) + Nx;
    if (J = (Ny-1)) then knoff.B := knoff.B+1; end_if;
  else knoff.B := knoff.B+1;
  end_if;
  if (I > 0) then
    knoff.A := knoff.A + I*knoff.B + 1;
    if (I = (Nx-1)) then knoff.B := knoff.B+1; end_if;
  else knoff.B := knoff.B+1;
  end_if;

END_FUNCTION

FUNCTION var_v : INT
  VAR_INPUT
    TV : TVar := -1;
    GET_A : BOOL := true;
  END_VAR
  VAR
    Sh : TShape;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)
    pvar_t pvar = (pvar_t)&TV;
    
    // Решаем ссылку (если нужно)
    while (pvar->r) {
      if (pvar->p >= 0) {
        // ссылка должна быть реальной (!)
        //ASSERT(1, NULL, (pvar->p < __GET_GLOBAL_HDR()->NI), 
        //  TERROR__E_FAIL, __STRING_LITERAL(22,"var_v: Reference fail!") );
        
        // Переход к элементу по ссылке:
        SH = GET_SH(1, NULL, pvar->p);
        P_INT Off = KNOFF(1, NULL, 
            SH.KN.table[0], SH.KN.table[1], SH.KN.table[2], 
            pvar->i, pvar->j, pvar->k
        );
        pvar = (pvar_t) &__GET_GLOBAL_ITS()->GR.table[pvar->p].A.table[Off.A];
      } else {  
        // элемент не существует -> воздух
        return (VAR_V = 2000); // 20.00 градусов Цельсия
      }
    }
    
    VAR_V = (GET_A) ? pvar->A : pvar->B;
  }}
END_FUNCTION

FUNCTION get_var : TVar
  VAR_INPUT
    HGR : THandle := 0;
    PGR : TPos8 := -1;
    OFF : P_INT;
    IX : USINT := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)

    // Получаем массив сеток по дескриптору  
    TGRID *Grids = (TGRID *)(HGR);
    
    if (IX == 0) {        // Главная ячейка узла
    
      GET_VAR = Grids[PGR].A.table[OFF.A];
      
    } else if (IX < 4) {  // Смежная ячейка узла
    
      for (int k=(GET_VAR=(TVAR)0, 1); k < OFF.B; k++) {
        GET_VAR = Grids[PGR].A.table[OFF.A+k];
        if (((pvar_t)&GET_VAR)->d == IX) break;
      }
      
      // Значение смежных ячеек может быть только ссылочным (!)
      // ASSERT(1, NULL, ((pvar_t)&GET_VAR)->r, TERROR__E_FAIL, 
        //__STRING_LITERAL(29,"GET_VAR: Reference wanted!"));
        
    } else {

      // Неверное значение IX
      // ASSERT(1, NULL, FALSE, TERROR__E_FAIL, 
        //__STRING_LITERAL(29,"GET_VAR: Invalid IX!"));
    
    }
  }}
END_FUNCTION

FUNCTION_BLOCK Grid2ul
  VAR_INPUT
    HGR : THandle := 0;
    PGR : TPos8 := -1;
    SH : TShape;
  END_VAR
  VAR_OUTPUT
    iRes : TError := E_SUCCESS;
    iLog : INT := 0;
  END_VAR
  VAR
    msg : STRING := '0';
    _SetLong4 : SetLong4;
  END_VAR

  VAR
    m4,n4,idx   : INT;       (* счётчики слов        *)  
    i,j,k       : INT;       (* индексы узлов сетки  *)  
    w: ARRAY[0..3] of INT;   (* буфер 2-байтных слов *)
    l: ARRAY[0..3] of ULINT; (* буфер 4-байтных слов *)
  END_VAR

  (* Установка начальных значений *)
  iLog:=0;
  iRes := E_FAIL;
  m4:=0; n4:=0; idx:=0;

  (* Запись значений температуры сетки в регистры *)
  FOR k := 0 TO SH.Kn[2]-1 DO 
    FOR j := 0 TO SH.Kn[1]-1 DO 
      FOR i := 0 TO SH.Kn[0]-1 DO 

        w[m4]:=var_v(
          get_var( HGR, PGR, 
            knoff(SH.Kn[0], SH.Kn[1], SH.Kn[2], i, j, k)
          )
        );
        
        if (iLog<4096) then  
          if (len(msg)=0) then msg := MakeMsg(' =!=> '); end_if;
          msg := MakeMsg(msg, INT_TO_STRING(w[m4]), ' ');
          if (mod((iLog+1),64)=0) then msg:=LogMsg(MakeMsg(msg)); end_if;
          iLog:=iLog+1;
        end_if;
        
        m4 := m4+1;
        if (mod(m4, 4)=0) then 
          m4 := 0;
          
          (*
          if (iLog<64) then  
            if (len(msg)=0) then msg := MakeMsg(' => '); end_if;
            msg := MakeMsg(msg, '[', INT_TO_STRING(w[0]), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(w[1]), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(w[2]), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(w[3]), ']');
          end_if;
          *)
          
          l[n4] := int4ul(w[0], w[1], w[2], w[3]); 
          
          n4 := n4+1;
          if (mod(n4, 4)=0) then 
            n4 := 0;
          
            (*if (iLog<64) then msg:=LogMsg(MakeMsg(msg,';')); iLog:=iLog+1; end_if;*)
            
            _SetLong4(I:=idx, LONG4:=l); idx := idx+1;
          end_if;
          
        end_if;
        
      END_FOR; 
    END_FOR; 
  END_FOR;

  if (len(msg)>0) then msg:=LogMsg(MakeMsg(msg)); end_if;

  (* Установка результата *)
  if (mod(m4,4)<>0) or (mod(n4,4)<>0) then 
        iRes:=E_INDEX;    (* ошибка индекса    *)
  else  iRes:=E_SUCCESS;  (* выполнено успешно *)
  end_if; 
END_FUNCTION_BLOCK

FUNCTION get_bf : REAL
  VAR_INPUT
    PBF : TPos16 := -1;
  END_VAR

  {{ return (GET_BF = __GET_GLOBAL_STS()->BF.table[PBF]); }}
END_FUNCTION

FUNCTION mat_oil : TMat
  VAR_INPUT
    Tm : REAL := 20.0;
  END_VAR

  mat_oil.kt := 0.1124  - 0.000085 * Tm;
  mat_oil.pl := 892.0   - 0.6075   * Tm;
  mat_oil.cp := 1549.0  + 5.93334  * Tm;
  mat_oil.md := 0.13515 * exp(2820.0/(272.0+1.13*Tm))/100000.0;
END_FUNCTION

FUNCTION var_p : TPos8
  VAR_INPUT
    TV : TVar := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)
    pvar_t pvar = (pvar_t)&TV;
    
    // Величина должна быть ссылкой
    // ASSERT(1, NULL, pvar->r, TERROR__E_FAIL, __INIT_STRING);
    VAR_P = pvar->p;
  }}
END_FUNCTION

FUNCTION m_prof : TProf
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
  END_VAR

  m_prof[0].A := UINT_TO_SINT(UDINT_TO_UINT(MD0/65536)/256);
  m_prof[0].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD0/65536),256));
  m_prof[1].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD0,65536))/256);
  m_prof[1].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD0,65536)),256));

  m_prof[2].A := UINT_TO_SINT(UDINT_TO_UINT(MD1/65536)/256);
  m_prof[2].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD1/65536),256));
  m_prof[3].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD1,65536))/256);
  m_prof[3].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD1,65536)),256));

  m_prof[4].A := UINT_TO_SINT(UDINT_TO_UINT(MD2/65536)/256);
  m_prof[4].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD2/65536),256));
  m_prof[5].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD2,65536))/256);
  m_prof[5].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD2,65536)),256));

  m_prof[6].A := UINT_TO_SINT(UDINT_TO_UINT(MD3/65536)/256);
  m_prof[6].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD3/65536),256));
  m_prof[7].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD3,65536))/256);
  m_prof[7].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD3,65536)),256));

  m_prof[8].A := UINT_TO_SINT(UDINT_TO_UINT(MD4/65536)/256);
  m_prof[8].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD4/65536),256));
  m_prof[9].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD4,65536))/256);
  m_prof[9].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD4,65536)),256));

  m_prof[10].A := UINT_TO_SINT(UDINT_TO_UINT(MD5/65536)/256);
  m_prof[10].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD5/65536),256));
  m_prof[11].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD5,65536))/256);
  m_prof[11].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD5,65536)),256));
END_FUNCTION

FUNCTION_BLOCK GetProf
  VAR_EXTERNAL
    MD120 : UDINT;
    MD121 : UDINT;
    MD122 : UDINT;
    MD123 : UDINT;
    MD124 : UDINT;
    MD125 : UDINT;
    MD126 : UDINT;
    MD127 : UDINT;
    MD128 : UDINT;
    MD129 : UDINT;
    MD130 : UDINT;
    MD131 : UDINT;
    MD132 : UDINT;
    MD133 : UDINT;
    MD134 : UDINT;
    MD135 : UDINT;
    MD136 : UDINT;
    MD137 : UDINT;
    MD138 : UDINT;
    MD139 : UDINT;
    MD140 : UDINT;
    MD141 : UDINT;
    MD142 : UDINT;
    MD143 : UDINT;
    MD144 : UDINT;
    MD145 : UDINT;
    MD146 : UDINT;
    MD147 : UDINT;
    MD148 : UDINT;
    MD149 : UDINT;
    MD150 : UDINT;
    MD151 : UDINT;
    MD152 : UDINT;
    MD153 : UDINT;
    MD154 : UDINT;
    MD155 : UDINT;
    MD156 : UDINT;
    MD157 : UDINT;
    MD158 : UDINT;
    MD159 : UDINT;
    MD160 : UDINT;
    MD161 : UDINT;
    MD162 : UDINT;
    MD163 : UDINT;
    MD164 : UDINT;
    MD165 : UDINT;
    MD166 : UDINT;
    MD167 : UDINT;
    MD168 : UDINT;
    MD169 : UDINT;
    MD170 : UDINT;
    MD171 : UDINT;
    MD172 : UDINT;
    MD173 : UDINT;
    MD174 : UDINT;
    MD175 : UDINT;
    MD176 : UDINT;
    MD177 : UDINT;
    MD178 : UDINT;
    MD179 : UDINT;
    MD180 : UDINT;
    MD181 : UDINT;
    MD182 : UDINT;
    MD183 : UDINT;
    MD184 : UDINT;
    MD185 : UDINT;
    MD186 : UDINT;
    MD187 : UDINT;
    MD188 : UDINT;
    MD189 : UDINT;
    MD190 : UDINT;
    MD191 : UDINT;
    MD192 : UDINT;
    MD193 : UDINT;
    MD194 : UDINT;
    MD195 : UDINT;
    MD196 : UDINT;
    MD197 : UDINT;
    MD198 : UDINT;
    MD199 : UDINT;
    MD200 : UDINT;
    MD201 : UDINT;
    MD202 : UDINT;
    MD203 : UDINT;
    MD204 : UDINT;
    MD205 : UDINT;
    MD206 : UDINT;
    MD207 : UDINT;
    MD208 : UDINT;
    MD209 : UDINT;
    MD210 : UDINT;
    MD211 : UDINT;
    MD212 : UDINT;
    MD213 : UDINT;
    MD214 : UDINT;
    MD215 : UDINT;
    MD216 : UDINT;
    MD217 : UDINT;
    MD218 : UDINT;
    MD219 : UDINT;
    MD220 : UDINT;
    MD221 : UDINT;
    MD222 : UDINT;
    MD223 : UDINT;
    MD224 : UDINT;
    MD225 : UDINT;
    MD226 : UDINT;
    MD227 : UDINT;
    MD228 : UDINT;
    MD229 : UDINT;
    MD230 : UDINT;
    MD231 : UDINT;
    MD232 : UDINT;
    MD233 : UDINT;
    MD234 : UDINT;
    MD235 : UDINT;
    MD236 : UDINT;
    MD237 : UDINT;
    MD238 : UDINT;
    MD239 : UDINT;
    MD240 : UDINT;
    MD241 : UDINT;
    MD242 : UDINT;
    MD243 : UDINT;
    MD244 : UDINT;
    MD245 : UDINT;
    MD246 : UDINT;
    MD247 : UDINT;
    MD248 : UDINT;
    MD249 : UDINT;
    MD250 : UDINT;
    MD251 : UDINT;
    MD252 : UDINT;
    MD253 : UDINT;
    MD254 : UDINT;
    MD255 : UDINT;
    MD256 : UDINT;
    MD257 : UDINT;
    MD258 : UDINT;
    MD259 : UDINT;
    MD260 : UDINT;
    MD261 : UDINT;
    MD262 : UDINT;
    MD263 : UDINT;
    MD264 : UDINT;
    MD265 : UDINT;
    MD266 : UDINT;
    MD267 : UDINT;
    MD268 : UDINT;
    MD269 : UDINT;
    MD270 : UDINT;
    MD271 : UDINT;
    MD272 : UDINT;
    MD273 : UDINT;
    MD274 : UDINT;
    MD275 : UDINT;
    MD276 : UDINT;
    MD277 : UDINT;
    MD278 : UDINT;
    MD279 : UDINT;
    MD280 : UDINT;
    MD281 : UDINT;
    MD282 : UDINT;
    MD283 : UDINT;
    MD284 : UDINT;
    MD285 : UDINT;
    MD286 : UDINT;
    MD287 : UDINT;
    MD288 : UDINT;
    MD289 : UDINT;
    MD290 : UDINT;
    MD291 : UDINT;
    MD292 : UDINT;
    MD293 : UDINT;
    MD294 : UDINT;
    MD295 : UDINT;
    MD296 : UDINT;
    MD297 : UDINT;
    MD298 : UDINT;
    MD299 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    PROF : TProf;
  END_VAR

  CASE i OF
  0 : PROF := m_prof(MD120,MD121,MD122,MD123,MD124,MD125);
  1 : PROF := m_prof(MD126,MD127,MD128,MD129,MD130,MD131);
  2 : PROF := m_prof(MD132,MD133,MD134,MD135,MD136,MD137);
  3 : PROF := m_prof(MD138,MD139,MD140,MD141,MD142,MD143);
  4 : PROF := m_prof(MD144,MD145,MD146,MD147,MD148,MD149);
  5 : PROF := m_prof(MD150,MD151,MD152,MD153,MD154,MD155);
  6 : PROF := m_prof(MD156,MD157,MD158,MD159,MD160,MD161);
  7 : PROF := m_prof(MD162,MD163,MD164,MD165,MD166,MD167);
  8 : PROF := m_prof(MD168,MD169,MD170,MD171,MD172,MD173);
  9 : PROF := m_prof(MD174,MD175,MD176,MD177,MD178,MD179);
  10: PROF := m_prof(MD180,MD181,MD182,MD183,MD184,MD185);
  11: PROF := m_prof(MD186,MD187,MD188,MD189,MD190,MD191);
  12: PROF := m_prof(MD192,MD193,MD194,MD195,MD196,MD197);
  13: PROF := m_prof(MD198,MD199,MD200,MD201,MD202,MD203);
  14: PROF := m_prof(MD204,MD205,MD206,MD207,MD208,MD209);
  15: PROF := m_prof(MD210,MD211,MD212,MD213,MD214,MD215);
  16: PROF := m_prof(MD216,MD217,MD218,MD219,MD220,MD221);
  17: PROF := m_prof(MD222,MD223,MD224,MD225,MD226,MD227);
  18: PROF := m_prof(MD228,MD229,MD230,MD231,MD232,MD233);
  19: PROF := m_prof(MD234,MD235,MD236,MD237,MD238,MD239);
  20: PROF := m_prof(MD240,MD241,MD242,MD243,MD244,MD245);
  21: PROF := m_prof(MD246,MD247,MD248,MD249,MD250,MD251);
  22: PROF := m_prof(MD252,MD253,MD254,MD255,MD256,MD257);
  23: PROF := m_prof(MD258,MD259,MD260,MD261,MD262,MD263);
  24: PROF := m_prof(MD264,MD265,MD266,MD267,MD268,MD269);
  25: PROF := m_prof(MD270,MD271,MD272,MD273,MD274,MD275);
  26: PROF := m_prof(MD276,MD277,MD278,MD279,MD280,MD281);
  27: PROF := m_prof(MD282,MD283,MD284,MD285,MD286,MD287);
  28: PROF := m_prof(MD288,MD289,MD290,MD291,MD292,MD293);
  29: PROF := m_prof(MD294,MD295,MD296,MD297,MD298,MD299);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION get_vl : TVal
  VAR_INPUT
    PVL : TPos8 := -1;
  END_VAR

  {{ return (GET_VL = __GET_GLOBAL_STS()->VL.table[PVL]); }}
END_FUNCTION

FUNCTION its_gr : THandle
  VAR_INPUT
    Off : TPos8 := 0;
  END_VAR

  {{ ITS_GR = (THANDLE)&__GET_GLOBAL_ITS()->GR.table[OFF]; }}
END_FUNCTION

FUNCTION m_cond : TCond
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
  END_VAR

  m_cond.ID   := UDINT_TO_UINT(MD0/65536);
  m_cond.Tmid := UDINT_TO_INT(mod(MD0,65536));

  m_cond.Tmin.A[0] := UDINT_TO_INT(MD1/65536);
  m_cond.Tmin.A[1] := UDINT_TO_INT(mod(MD1,65536));
  m_cond.Tmin.A[2] := UDINT_TO_INT(MD2/65536);
  m_cond.Tmin.V    := UDINT_TO_INT(mod(MD2,65536));

  m_cond.Tmax.A[0] := UDINT_TO_INT(MD3/65536);
  m_cond.Tmax.A[1] := UDINT_TO_INT(mod(MD3,65536));
  m_cond.Tmax.A[2] := UDINT_TO_INT(MD4/65536);
  m_cond.Tmax.V    := UDINT_TO_INT(mod(MD4,65536));
END_FUNCTION

FUNCTION_BLOCK WriteItem
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    Cond : TCond;
    msg : STRING := '';
    _SetCond : SetCond;
  END_VAR

  (* Запись состояния в регистры *)
  Cond    := get_cn(PIT);
  Cond.ID := it_id(PIT);
  (*TEST*)
  (* #53 - ID = 16761, 0x4179, REG = 3578-3587 *)
  (*
  if (Cond.ID = 16761) then 
    msg := MakeMsg(msg, '= TEST1 [', ID2Str(IT_ID(PIT)), ',');
    msg := MakeMsg(msg, SINT_TO_STRING(PIT), ',');
    msg := MakeMsg(msg, 'Tmid=', REAL_TO_STRING(INT_TO_REAL(Cond.Tmid)/100.0), ',');
    msg := MakeMsg(msg, 'Tmax=', REAL_TO_STRING(INT_TO_REAL(Cond.Tmax.v)/100.0), ',');
    msg := MakeMsg(msg,  INT_TO_STRING(Cond.Tmax.i[0]), ',');
    msg := MakeMsg(msg,  INT_TO_STRING(Cond.Tmax.i[1]), ',');
    msg := MakeMsg(msg,  INT_TO_STRING(Cond.Tmax.i[2]), ']');
    msg := LogMsg(msg);
  end_if;
  *)
  _SetCond(I := SINT_TO_UINT(PIT), COND := Cond);
END_FUNCTION_BLOCK

FUNCTION UDI2REAL : REAL
  VAR_INPUT
    VALUE : UDINT := 0;
  END_VAR
  VAR
    tmp : REAL := 0.0;
  END_VAR

  {{
    union { UDINT  udint; float real; } value;
    value.udint = VALUE;
    TMP = value.real;
  }}
  UDI2REAL := TMP;
END_FUNCTION

FUNCTION LogErr : STRING
  VAR_INPUT
    ERR : TError := E_SUCCESS;
  END_VAR

  LogErr := LogMsg('',Info,ERR);


END_FUNCTION

FUNCTION m_phase_out : TPhaseO
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
  END_VAR

  m_phase_out.Q0   := UDINT_TO_REAL(MD0);
  m_phase_out.Q1   := UDINT_TO_REAL(MD1);
  m_phase_out.Q2   := UDINT_TO_REAL(MD2);
  m_phase_out.Tin  := UDINT_TO_REAL(MD3);
  m_phase_out.Tout := UDINT_TO_REAL(MD4);
  m_phase_out.Qm   := UDINT_TO_REAL(MD5);
  m_phase_out.Se   := UDINT_TO_REAL(MD6);
  m_phase_out.Ve   := UDINT_TO_REAL(MD7);
END_FUNCTION

FUNCTION sh_set_ax : TShape
  VAR_INPUT
    SH : TShape;
    Ax : USINT;
  END_VAR

  Sh.wF := Sh.wF or shl(USINT_TO_WORD(Ax), 12);
  sh_set_ax := Sh;
END_FUNCTION

FUNCTION set_it : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
    ITEM : TItem;
  END_VAR

  {{ return (SET_IT = ( __GET_GLOBAL_ITS()->IT.table[PIT] = ITEM, PIT) ); }}
END_FUNCTION

FUNCTION m_def : TDef
  VAR_INPUT
    MW0 : UINT;
    MW1 : UINT;
    MW2 : UINT;
    MW3 : UINT;
    MW4 : UINT;
    MW5 : UINT;
    MW6 : UINT;
    MW7 : UINT;
    MW8 : UINT;
    MW9 : UINT;
  END_VAR

  (* Идентификатор, флаги и радиус *)
  m_def.ID    := MW0;
  m_def.CF    := UINT_TO_WORD(MW1);
  m_def.R0    := UINT_TO_INT (MW2);

  (* Определение точки начала отсчёта *)
  m_def.XYZ[0]:= UINT_TO_INT (MW3);
  m_def.XYZ[1]:= UINT_TO_INT (MW4);
  m_def.XYZ[2]:= UINT_TO_INT (MW5);

  (* Определение габаритов элемента   *)
  m_def.LWH[0]:= UINT_TO_INT (MW6);
  m_def.LWH[1]:= UINT_TO_INT (MW7);
  m_def.LWH[2]:= UINT_TO_INT (MW8);

  (* Определение индексов элемента   *)
  m_def.Ig    := UINT_TO_SINT((MW9/256)/16);
  m_def.Im    := UINT_TO_SINT(mod((MW9/256),16));
  m_def.Iv    := UINT_TO_SINT(mod(MW9, 256));
END_FUNCTION

FUNCTION_BLOCK GetDef
  VAR_EXTERNAL
    MW0 : UINT;
    MW1 : UINT;
    MW2 : UINT;
    MW3 : UINT;
    MW4 : UINT;
    MW5 : UINT;
    MW6 : UINT;
    MW7 : UINT;
    MW8 : UINT;
    MW9 : UINT;
    MW10 : UINT;
    MW11 : UINT;
    MW12 : UINT;
    MW13 : UINT;
    MW14 : UINT;
    MW15 : UINT;
    MW16 : UINT;
    MW17 : UINT;
    MW18 : UINT;
    MW19 : UINT;
    MW20 : UINT;
    MW21 : UINT;
    MW22 : UINT;
    MW23 : UINT;
    MW24 : UINT;
    MW25 : UINT;
    MW26 : UINT;
    MW27 : UINT;
    MW28 : UINT;
    MW29 : UINT;
    MW30 : UINT;
    MW31 : UINT;
    MW32 : UINT;
    MW33 : UINT;
    MW34 : UINT;
    MW35 : UINT;
    MW36 : UINT;
    MW37 : UINT;
    MW38 : UINT;
    MW39 : UINT;
    MW40 : UINT;
    MW41 : UINT;
    MW42 : UINT;
    MW43 : UINT;
    MW44 : UINT;
    MW45 : UINT;
    MW46 : UINT;
    MW47 : UINT;
    MW48 : UINT;
    MW49 : UINT;
    MW50 : UINT;
    MW51 : UINT;
    MW52 : UINT;
    MW53 : UINT;
    MW54 : UINT;
    MW55 : UINT;
    MW56 : UINT;
    MW57 : UINT;
    MW58 : UINT;
    MW59 : UINT;
    MW60 : UINT;
    MW61 : UINT;
    MW62 : UINT;
    MW63 : UINT;
    MW64 : UINT;
    MW65 : UINT;
    MW66 : UINT;
    MW67 : UINT;
    MW68 : UINT;
    MW69 : UINT;
    MW70 : UINT;
    MW71 : UINT;
    MW72 : UINT;
    MW73 : UINT;
    MW74 : UINT;
    MW75 : UINT;
    MW76 : UINT;
    MW77 : UINT;
    MW78 : UINT;
    MW79 : UINT;
    MW80 : UINT;
    MW81 : UINT;
    MW82 : UINT;
    MW83 : UINT;
    MW84 : UINT;
    MW85 : UINT;
    MW86 : UINT;
    MW87 : UINT;
    MW88 : UINT;
    MW89 : UINT;
    MW90 : UINT;
    MW91 : UINT;
    MW92 : UINT;
    MW93 : UINT;
    MW94 : UINT;
    MW95 : UINT;
    MW96 : UINT;
    MW97 : UINT;
    MW98 : UINT;
    MW99 : UINT;
    MW100 : UINT;
    MW101 : UINT;
    MW102 : UINT;
    MW103 : UINT;
    MW104 : UINT;
    MW105 : UINT;
    MW106 : UINT;
    MW107 : UINT;
    MW108 : UINT;
    MW109 : UINT;
    MW110 : UINT;
    MW111 : UINT;
    MW112 : UINT;
    MW113 : UINT;
    MW114 : UINT;
    MW115 : UINT;
    MW116 : UINT;
    MW117 : UINT;
    MW118 : UINT;
    MW119 : UINT;
    MW120 : UINT;
    MW121 : UINT;
    MW122 : UINT;
    MW123 : UINT;
    MW124 : UINT;
    MW125 : UINT;
    MW126 : UINT;
    MW127 : UINT;
    MW128 : UINT;
    MW129 : UINT;
    MW130 : UINT;
    MW131 : UINT;
    MW132 : UINT;
    MW133 : UINT;
    MW134 : UINT;
    MW135 : UINT;
    MW136 : UINT;
    MW137 : UINT;
    MW138 : UINT;
    MW139 : UINT;
    MW140 : UINT;
    MW141 : UINT;
    MW142 : UINT;
    MW143 : UINT;
    MW144 : UINT;
    MW145 : UINT;
    MW146 : UINT;
    MW147 : UINT;
    MW148 : UINT;
    MW149 : UINT;
    MW150 : UINT;
    MW151 : UINT;
    MW152 : UINT;
    MW153 : UINT;
    MW154 : UINT;
    MW155 : UINT;
    MW156 : UINT;
    MW157 : UINT;
    MW158 : UINT;
    MW159 : UINT;
    MW160 : UINT;
    MW161 : UINT;
    MW162 : UINT;
    MW163 : UINT;
    MW164 : UINT;
    MW165 : UINT;
    MW166 : UINT;
    MW167 : UINT;
    MW168 : UINT;
    MW169 : UINT;
    MW170 : UINT;
    MW171 : UINT;
    MW172 : UINT;
    MW173 : UINT;
    MW174 : UINT;
    MW175 : UINT;
    MW176 : UINT;
    MW177 : UINT;
    MW178 : UINT;
    MW179 : UINT;
    MW180 : UINT;
    MW181 : UINT;
    MW182 : UINT;
    MW183 : UINT;
    MW184 : UINT;
    MW185 : UINT;
    MW186 : UINT;
    MW187 : UINT;
    MW188 : UINT;
    MW189 : UINT;
    MW190 : UINT;
    MW191 : UINT;
    MW192 : UINT;
    MW193 : UINT;
    MW194 : UINT;
    MW195 : UINT;
    MW196 : UINT;
    MW197 : UINT;
    MW198 : UINT;
    MW199 : UINT;
    MW200 : UINT;
    MW201 : UINT;
    MW202 : UINT;
    MW203 : UINT;
    MW204 : UINT;
    MW205 : UINT;
    MW206 : UINT;
    MW207 : UINT;
    MW208 : UINT;
    MW209 : UINT;
    MW210 : UINT;
    MW211 : UINT;
    MW212 : UINT;
    MW213 : UINT;
    MW214 : UINT;
    MW215 : UINT;
    MW216 : UINT;
    MW217 : UINT;
    MW218 : UINT;
    MW219 : UINT;
    MW220 : UINT;
    MW221 : UINT;
    MW222 : UINT;
    MW223 : UINT;
    MW224 : UINT;
    MW225 : UINT;
    MW226 : UINT;
    MW227 : UINT;
    MW228 : UINT;
    MW229 : UINT;
    MW230 : UINT;
    MW231 : UINT;
    MW232 : UINT;
    MW233 : UINT;
    MW234 : UINT;
    MW235 : UINT;
    MW236 : UINT;
    MW237 : UINT;
    MW238 : UINT;
    MW239 : UINT;
    MW240 : UINT;
    MW241 : UINT;
    MW242 : UINT;
    MW243 : UINT;
    MW244 : UINT;
    MW245 : UINT;
    MW246 : UINT;
    MW247 : UINT;
    MW248 : UINT;
    MW249 : UINT;
    MW250 : UINT;
    MW251 : UINT;
    MW252 : UINT;
    MW253 : UINT;
    MW254 : UINT;
    MW255 : UINT;
    MW256 : UINT;
    MW257 : UINT;
    MW258 : UINT;
    MW259 : UINT;
    MW260 : UINT;
    MW261 : UINT;
    MW262 : UINT;
    MW263 : UINT;
    MW264 : UINT;
    MW265 : UINT;
    MW266 : UINT;
    MW267 : UINT;
    MW268 : UINT;
    MW269 : UINT;
    MW270 : UINT;
    MW271 : UINT;
    MW272 : UINT;
    MW273 : UINT;
    MW274 : UINT;
    MW275 : UINT;
    MW276 : UINT;
    MW277 : UINT;
    MW278 : UINT;
    MW279 : UINT;
    MW280 : UINT;
    MW281 : UINT;
    MW282 : UINT;
    MW283 : UINT;
    MW284 : UINT;
    MW285 : UINT;
    MW286 : UINT;
    MW287 : UINT;
    MW288 : UINT;
    MW289 : UINT;
    MW290 : UINT;
    MW291 : UINT;
    MW292 : UINT;
    MW293 : UINT;
    MW294 : UINT;
    MW295 : UINT;
    MW296 : UINT;
    MW297 : UINT;
    MW298 : UINT;
    MW299 : UINT;
    MW300 : UINT;
    MW301 : UINT;
    MW302 : UINT;
    MW303 : UINT;
    MW304 : UINT;
    MW305 : UINT;
    MW306 : UINT;
    MW307 : UINT;
    MW308 : UINT;
    MW309 : UINT;
    MW310 : UINT;
    MW311 : UINT;
    MW312 : UINT;
    MW313 : UINT;
    MW314 : UINT;
    MW315 : UINT;
    MW316 : UINT;
    MW317 : UINT;
    MW318 : UINT;
    MW319 : UINT;
    MW320 : UINT;
    MW321 : UINT;
    MW322 : UINT;
    MW323 : UINT;
    MW324 : UINT;
    MW325 : UINT;
    MW326 : UINT;
    MW327 : UINT;
    MW328 : UINT;
    MW329 : UINT;
    MW330 : UINT;
    MW331 : UINT;
    MW332 : UINT;
    MW333 : UINT;
    MW334 : UINT;
    MW335 : UINT;
    MW336 : UINT;
    MW337 : UINT;
    MW338 : UINT;
    MW339 : UINT;
    MW340 : UINT;
    MW341 : UINT;
    MW342 : UINT;
    MW343 : UINT;
    MW344 : UINT;
    MW345 : UINT;
    MW346 : UINT;
    MW347 : UINT;
    MW348 : UINT;
    MW349 : UINT;
    MW350 : UINT;
    MW351 : UINT;
    MW352 : UINT;
    MW353 : UINT;
    MW354 : UINT;
    MW355 : UINT;
    MW356 : UINT;
    MW357 : UINT;
    MW358 : UINT;
    MW359 : UINT;
    MW360 : UINT;
    MW361 : UINT;
    MW362 : UINT;
    MW363 : UINT;
    MW364 : UINT;
    MW365 : UINT;
    MW366 : UINT;
    MW367 : UINT;
    MW368 : UINT;
    MW369 : UINT;
    MW370 : UINT;
    MW371 : UINT;
    MW372 : UINT;
    MW373 : UINT;
    MW374 : UINT;
    MW375 : UINT;
    MW376 : UINT;
    MW377 : UINT;
    MW378 : UINT;
    MW379 : UINT;
    MW380 : UINT;
    MW381 : UINT;
    MW382 : UINT;
    MW383 : UINT;
    MW384 : UINT;
    MW385 : UINT;
    MW386 : UINT;
    MW387 : UINT;
    MW388 : UINT;
    MW389 : UINT;
    MW390 : UINT;
    MW391 : UINT;
    MW392 : UINT;
    MW393 : UINT;
    MW394 : UINT;
    MW395 : UINT;
    MW396 : UINT;
    MW397 : UINT;
    MW398 : UINT;
    MW399 : UINT;
    MW400 : UINT;
    MW401 : UINT;
    MW402 : UINT;
    MW403 : UINT;
    MW404 : UINT;
    MW405 : UINT;
    MW406 : UINT;
    MW407 : UINT;
    MW408 : UINT;
    MW409 : UINT;
    MW410 : UINT;
    MW411 : UINT;
    MW412 : UINT;
    MW413 : UINT;
    MW414 : UINT;
    MW415 : UINT;
    MW416 : UINT;
    MW417 : UINT;
    MW418 : UINT;
    MW419 : UINT;
    MW420 : UINT;
    MW421 : UINT;
    MW422 : UINT;
    MW423 : UINT;
    MW424 : UINT;
    MW425 : UINT;
    MW426 : UINT;
    MW427 : UINT;
    MW428 : UINT;
    MW429 : UINT;
    MW430 : UINT;
    MW431 : UINT;
    MW432 : UINT;
    MW433 : UINT;
    MW434 : UINT;
    MW435 : UINT;
    MW436 : UINT;
    MW437 : UINT;
    MW438 : UINT;
    MW439 : UINT;
    MW440 : UINT;
    MW441 : UINT;
    MW442 : UINT;
    MW443 : UINT;
    MW444 : UINT;
    MW445 : UINT;
    MW446 : UINT;
    MW447 : UINT;
    MW448 : UINT;
    MW449 : UINT;
    MW450 : UINT;
    MW451 : UINT;
    MW452 : UINT;
    MW453 : UINT;
    MW454 : UINT;
    MW455 : UINT;
    MW456 : UINT;
    MW457 : UINT;
    MW458 : UINT;
    MW459 : UINT;
    MW460 : UINT;
    MW461 : UINT;
    MW462 : UINT;
    MW463 : UINT;
    MW464 : UINT;
    MW465 : UINT;
    MW466 : UINT;
    MW467 : UINT;
    MW468 : UINT;
    MW469 : UINT;
    MW470 : UINT;
    MW471 : UINT;
    MW472 : UINT;
    MW473 : UINT;
    MW474 : UINT;
    MW475 : UINT;
    MW476 : UINT;
    MW477 : UINT;
    MW478 : UINT;
    MW479 : UINT;
    MW480 : UINT;
    MW481 : UINT;
    MW482 : UINT;
    MW483 : UINT;
    MW484 : UINT;
    MW485 : UINT;
    MW486 : UINT;
    MW487 : UINT;
    MW488 : UINT;
    MW489 : UINT;
    MW490 : UINT;
    MW491 : UINT;
    MW492 : UINT;
    MW493 : UINT;
    MW494 : UINT;
    MW495 : UINT;
    MW496 : UINT;
    MW497 : UINT;
    MW498 : UINT;
    MW499 : UINT;
    MW500 : UINT;
    MW501 : UINT;
    MW502 : UINT;
    MW503 : UINT;
    MW504 : UINT;
    MW505 : UINT;
    MW506 : UINT;
    MW507 : UINT;
    MW508 : UINT;
    MW509 : UINT;
    MW510 : UINT;
    MW511 : UINT;
    MW512 : UINT;
    MW513 : UINT;
    MW514 : UINT;
    MW515 : UINT;
    MW516 : UINT;
    MW517 : UINT;
    MW518 : UINT;
    MW519 : UINT;
    MW520 : UINT;
    MW521 : UINT;
    MW522 : UINT;
    MW523 : UINT;
    MW524 : UINT;
    MW525 : UINT;
    MW526 : UINT;
    MW527 : UINT;
    MW528 : UINT;
    MW529 : UINT;
    MW530 : UINT;
    MW531 : UINT;
    MW532 : UINT;
    MW533 : UINT;
    MW534 : UINT;
    MW535 : UINT;
    MW536 : UINT;
    MW537 : UINT;
    MW538 : UINT;
    MW539 : UINT;
    MW540 : UINT;
    MW541 : UINT;
    MW542 : UINT;
    MW543 : UINT;
    MW544 : UINT;
    MW545 : UINT;
    MW546 : UINT;
    MW547 : UINT;
    MW548 : UINT;
    MW549 : UINT;
    MW550 : UINT;
    MW551 : UINT;
    MW552 : UINT;
    MW553 : UINT;
    MW554 : UINT;
    MW555 : UINT;
    MW556 : UINT;
    MW557 : UINT;
    MW558 : UINT;
    MW559 : UINT;
    MW560 : UINT;
    MW561 : UINT;
    MW562 : UINT;
    MW563 : UINT;
    MW564 : UINT;
    MW565 : UINT;
    MW566 : UINT;
    MW567 : UINT;
    MW568 : UINT;
    MW569 : UINT;
    MW570 : UINT;
    MW571 : UINT;
    MW572 : UINT;
    MW573 : UINT;
    MW574 : UINT;
    MW575 : UINT;
    MW576 : UINT;
    MW577 : UINT;
    MW578 : UINT;
    MW579 : UINT;
    MW580 : UINT;
    MW581 : UINT;
    MW582 : UINT;
    MW583 : UINT;
    MW584 : UINT;
    MW585 : UINT;
    MW586 : UINT;
    MW587 : UINT;
    MW588 : UINT;
    MW589 : UINT;
    MW590 : UINT;
    MW591 : UINT;
    MW592 : UINT;
    MW593 : UINT;
    MW594 : UINT;
    MW595 : UINT;
    MW596 : UINT;
    MW597 : UINT;
    MW598 : UINT;
    MW599 : UINT;
    MW600 : UINT;
    MW601 : UINT;
    MW602 : UINT;
    MW603 : UINT;
    MW604 : UINT;
    MW605 : UINT;
    MW606 : UINT;
    MW607 : UINT;
    MW608 : UINT;
    MW609 : UINT;
    MW610 : UINT;
    MW611 : UINT;
    MW612 : UINT;
    MW613 : UINT;
    MW614 : UINT;
    MW615 : UINT;
    MW616 : UINT;
    MW617 : UINT;
    MW618 : UINT;
    MW619 : UINT;
    MW620 : UINT;
    MW621 : UINT;
    MW622 : UINT;
    MW623 : UINT;
    MW624 : UINT;
    MW625 : UINT;
    MW626 : UINT;
    MW627 : UINT;
    MW628 : UINT;
    MW629 : UINT;
    MW630 : UINT;
    MW631 : UINT;
    MW632 : UINT;
    MW633 : UINT;
    MW634 : UINT;
    MW635 : UINT;
    MW636 : UINT;
    MW637 : UINT;
    MW638 : UINT;
    MW639 : UINT;
    MW640 : UINT;
    MW641 : UINT;
    MW642 : UINT;
    MW643 : UINT;
    MW644 : UINT;
    MW645 : UINT;
    MW646 : UINT;
    MW647 : UINT;
    MW648 : UINT;
    MW649 : UINT;
    MW650 : UINT;
    MW651 : UINT;
    MW652 : UINT;
    MW653 : UINT;
    MW654 : UINT;
    MW655 : UINT;
    MW656 : UINT;
    MW657 : UINT;
    MW658 : UINT;
    MW659 : UINT;
    MW660 : UINT;
    MW661 : UINT;
    MW662 : UINT;
    MW663 : UINT;
    MW664 : UINT;
    MW665 : UINT;
    MW666 : UINT;
    MW667 : UINT;
    MW668 : UINT;
    MW669 : UINT;
    MW670 : UINT;
    MW671 : UINT;
    MW672 : UINT;
    MW673 : UINT;
    MW674 : UINT;
    MW675 : UINT;
    MW676 : UINT;
    MW677 : UINT;
    MW678 : UINT;
    MW679 : UINT;
    MW680 : UINT;
    MW681 : UINT;
    MW682 : UINT;
    MW683 : UINT;
    MW684 : UINT;
    MW685 : UINT;
    MW686 : UINT;
    MW687 : UINT;
    MW688 : UINT;
    MW689 : UINT;
    MW690 : UINT;
    MW691 : UINT;
    MW692 : UINT;
    MW693 : UINT;
    MW694 : UINT;
    MW695 : UINT;
    MW696 : UINT;
    MW697 : UINT;
    MW698 : UINT;
    MW699 : UINT;
    MW700 : UINT;
    MW701 : UINT;
    MW702 : UINT;
    MW703 : UINT;
    MW704 : UINT;
    MW705 : UINT;
    MW706 : UINT;
    MW707 : UINT;
    MW708 : UINT;
    MW709 : UINT;
    MW710 : UINT;
    MW711 : UINT;
    MW712 : UINT;
    MW713 : UINT;
    MW714 : UINT;
    MW715 : UINT;
    MW716 : UINT;
    MW717 : UINT;
    MW718 : UINT;
    MW719 : UINT;
    MW720 : UINT;
    MW721 : UINT;
    MW722 : UINT;
    MW723 : UINT;
    MW724 : UINT;
    MW725 : UINT;
    MW726 : UINT;
    MW727 : UINT;
    MW728 : UINT;
    MW729 : UINT;
    MW730 : UINT;
    MW731 : UINT;
    MW732 : UINT;
    MW733 : UINT;
    MW734 : UINT;
    MW735 : UINT;
    MW736 : UINT;
    MW737 : UINT;
    MW738 : UINT;
    MW739 : UINT;
    MW740 : UINT;
    MW741 : UINT;
    MW742 : UINT;
    MW743 : UINT;
    MW744 : UINT;
    MW745 : UINT;
    MW746 : UINT;
    MW747 : UINT;
    MW748 : UINT;
    MW749 : UINT;
    MW750 : UINT;
    MW751 : UINT;
    MW752 : UINT;
    MW753 : UINT;
    MW754 : UINT;
    MW755 : UINT;
    MW756 : UINT;
    MW757 : UINT;
    MW758 : UINT;
    MW759 : UINT;
    MW760 : UINT;
    MW761 : UINT;
    MW762 : UINT;
    MW763 : UINT;
    MW764 : UINT;
    MW765 : UINT;
    MW766 : UINT;
    MW767 : UINT;
    MW768 : UINT;
    MW769 : UINT;
    MW770 : UINT;
    MW771 : UINT;
    MW772 : UINT;
    MW773 : UINT;
    MW774 : UINT;
    MW775 : UINT;
    MW776 : UINT;
    MW777 : UINT;
    MW778 : UINT;
    MW779 : UINT;
    MW780 : UINT;
    MW781 : UINT;
    MW782 : UINT;
    MW783 : UINT;
    MW784 : UINT;
    MW785 : UINT;
    MW786 : UINT;
    MW787 : UINT;
    MW788 : UINT;
    MW789 : UINT;
    MW790 : UINT;
    MW791 : UINT;
    MW792 : UINT;
    MW793 : UINT;
    MW794 : UINT;
    MW795 : UINT;
    MW796 : UINT;
    MW797 : UINT;
    MW798 : UINT;
    MW799 : UINT;
    MW800 : UINT;
    MW801 : UINT;
    MW802 : UINT;
    MW803 : UINT;
    MW804 : UINT;
    MW805 : UINT;
    MW806 : UINT;
    MW807 : UINT;
    MW808 : UINT;
    MW809 : UINT;
    MW810 : UINT;
    MW811 : UINT;
    MW812 : UINT;
    MW813 : UINT;
    MW814 : UINT;
    MW815 : UINT;
    MW816 : UINT;
    MW817 : UINT;
    MW818 : UINT;
    MW819 : UINT;
    MW820 : UINT;
    MW821 : UINT;
    MW822 : UINT;
    MW823 : UINT;
    MW824 : UINT;
    MW825 : UINT;
    MW826 : UINT;
    MW827 : UINT;
    MW828 : UINT;
    MW829 : UINT;
    MW830 : UINT;
    MW831 : UINT;
    MW832 : UINT;
    MW833 : UINT;
    MW834 : UINT;
    MW835 : UINT;
    MW836 : UINT;
    MW837 : UINT;
    MW838 : UINT;
    MW839 : UINT;
    MW840 : UINT;
    MW841 : UINT;
    MW842 : UINT;
    MW843 : UINT;
    MW844 : UINT;
    MW845 : UINT;
    MW846 : UINT;
    MW847 : UINT;
    MW848 : UINT;
    MW849 : UINT;
    MW850 : UINT;
    MW851 : UINT;
    MW852 : UINT;
    MW853 : UINT;
    MW854 : UINT;
    MW855 : UINT;
    MW856 : UINT;
    MW857 : UINT;
    MW858 : UINT;
    MW859 : UINT;
    MW860 : UINT;
    MW861 : UINT;
    MW862 : UINT;
    MW863 : UINT;
    MW864 : UINT;
    MW865 : UINT;
    MW866 : UINT;
    MW867 : UINT;
    MW868 : UINT;
    MW869 : UINT;
    MW870 : UINT;
    MW871 : UINT;
    MW872 : UINT;
    MW873 : UINT;
    MW874 : UINT;
    MW875 : UINT;
    MW876 : UINT;
    MW877 : UINT;
    MW878 : UINT;
    MW879 : UINT;
    MW880 : UINT;
    MW881 : UINT;
    MW882 : UINT;
    MW883 : UINT;
    MW884 : UINT;
    MW885 : UINT;
    MW886 : UINT;
    MW887 : UINT;
    MW888 : UINT;
    MW889 : UINT;
    MW890 : UINT;
    MW891 : UINT;
    MW892 : UINT;
    MW893 : UINT;
    MW894 : UINT;
    MW895 : UINT;
    MW896 : UINT;
    MW897 : UINT;
    MW898 : UINT;
    MW899 : UINT;
    MW900 : UINT;
    MW901 : UINT;
    MW902 : UINT;
    MW903 : UINT;
    MW904 : UINT;
    MW905 : UINT;
    MW906 : UINT;
    MW907 : UINT;
    MW908 : UINT;
    MW909 : UINT;
    MW910 : UINT;
    MW911 : UINT;
    MW912 : UINT;
    MW913 : UINT;
    MW914 : UINT;
    MW915 : UINT;
    MW916 : UINT;
    MW917 : UINT;
    MW918 : UINT;
    MW919 : UINT;
    MW920 : UINT;
    MW921 : UINT;
    MW922 : UINT;
    MW923 : UINT;
    MW924 : UINT;
    MW925 : UINT;
    MW926 : UINT;
    MW927 : UINT;
    MW928 : UINT;
    MW929 : UINT;
    MW930 : UINT;
    MW931 : UINT;
    MW932 : UINT;
    MW933 : UINT;
    MW934 : UINT;
    MW935 : UINT;
    MW936 : UINT;
    MW937 : UINT;
    MW938 : UINT;
    MW939 : UINT;
    MW940 : UINT;
    MW941 : UINT;
    MW942 : UINT;
    MW943 : UINT;
    MW944 : UINT;
    MW945 : UINT;
    MW946 : UINT;
    MW947 : UINT;
    MW948 : UINT;
    MW949 : UINT;
    MW950 : UINT;
    MW951 : UINT;
    MW952 : UINT;
    MW953 : UINT;
    MW954 : UINT;
    MW955 : UINT;
    MW956 : UINT;
    MW957 : UINT;
    MW958 : UINT;
    MW959 : UINT;
    MW960 : UINT;
    MW961 : UINT;
    MW962 : UINT;
    MW963 : UINT;
    MW964 : UINT;
    MW965 : UINT;
    MW966 : UINT;
    MW967 : UINT;
    MW968 : UINT;
    MW969 : UINT;
    MW970 : UINT;
    MW971 : UINT;
    MW972 : UINT;
    MW973 : UINT;
    MW974 : UINT;
    MW975 : UINT;
    MW976 : UINT;
    MW977 : UINT;
    MW978 : UINT;
    MW979 : UINT;
    MW980 : UINT;
    MW981 : UINT;
    MW982 : UINT;
    MW983 : UINT;
    MW984 : UINT;
    MW985 : UINT;
    MW986 : UINT;
    MW987 : UINT;
    MW988 : UINT;
    MW989 : UINT;
    MW990 : UINT;
    MW991 : UINT;
    MW992 : UINT;
    MW993 : UINT;
    MW994 : UINT;
    MW995 : UINT;
    MW996 : UINT;
    MW997 : UINT;
    MW998 : UINT;
    MW999 : UINT;
  END_VAR
  VAR_INPUT
    I : TPos8 := -1;
  END_VAR
  VAR_OUTPUT
    DEF : TDef;
  END_VAR

  CASE i OF
  0 : DEF := m_def(MW0,MW1,MW2,MW3,MW4,MW5,MW6,MW7,MW8,MW9);
  1 : DEF := m_def(MW10,MW11,MW12,MW13,MW14,MW15,MW16,MW17,MW18,MW19);
  2 : DEF := m_def(MW20,MW21,MW22,MW23,MW24,MW25,MW26,MW27,MW28,MW29);
  3 : DEF := m_def(MW30,MW31,MW32,MW33,MW34,MW35,MW36,MW37,MW38,MW39);
  4 : DEF := m_def(MW40,MW41,MW42,MW43,MW44,MW45,MW46,MW47,MW48,MW49);
  5 : DEF := m_def(MW50,MW51,MW52,MW53,MW54,MW55,MW56,MW57,MW58,MW59);
  6 : DEF := m_def(MW60,MW61,MW62,MW63,MW64,MW65,MW66,MW67,MW68,MW69);
  7 : DEF := m_def(MW70,MW71,MW72,MW73,MW74,MW75,MW76,MW77,MW78,MW79);
  8 : DEF := m_def(MW80,MW81,MW82,MW83,MW84,MW85,MW86,MW87,MW88,MW89);
  9 : DEF := m_def(MW90,MW91,MW92,MW93,MW94,MW95,MW96,MW97,MW98,MW99);

  10 : DEF := m_def(MW100,MW101,MW102,MW103,MW104,MW105,MW106,MW107,MW108,MW109);
  11 : DEF := m_def(MW110,MW111,MW112,MW113,MW114,MW115,MW116,MW117,MW118,MW119);
  12 : DEF := m_def(MW120,MW121,MW122,MW123,MW124,MW125,MW126,MW127,MW128,MW129);
  13 : DEF := m_def(MW130,MW131,MW132,MW133,MW134,MW135,MW136,MW137,MW138,MW139);
  14 : DEF := m_def(MW140,MW141,MW142,MW143,MW144,MW145,MW146,MW147,MW148,MW149);
  15 : DEF := m_def(MW150,MW151,MW152,MW153,MW154,MW155,MW156,MW157,MW158,MW159);
  16 : DEF := m_def(MW160,MW161,MW162,MW163,MW164,MW165,MW166,MW167,MW168,MW169);
  17 : DEF := m_def(MW170,MW171,MW172,MW173,MW174,MW175,MW176,MW177,MW178,MW179);
  18 : DEF := m_def(MW180,MW181,MW182,MW183,MW184,MW185,MW186,MW187,MW188,MW189);
  19 : DEF := m_def(MW190,MW191,MW192,MW193,MW194,MW195,MW196,MW197,MW198,MW199);

  20 : DEF := m_def(MW200,MW201,MW202,MW203,MW204,MW205,MW206,MW207,MW208,MW209);
  21 : DEF := m_def(MW210,MW211,MW212,MW213,MW214,MW215,MW216,MW217,MW218,MW219);
  22 : DEF := m_def(MW220,MW221,MW222,MW223,MW224,MW225,MW226,MW227,MW228,MW229);
  23 : DEF := m_def(MW230,MW231,MW232,MW233,MW234,MW235,MW236,MW237,MW238,MW239);
  24 : DEF := m_def(MW240,MW241,MW242,MW243,MW244,MW245,MW246,MW247,MW248,MW249);
  25 : DEF := m_def(MW250,MW251,MW252,MW253,MW254,MW255,MW256,MW257,MW258,MW259);
  26 : DEF := m_def(MW260,MW261,MW262,MW263,MW264,MW265,MW266,MW267,MW268,MW269);
  27 : DEF := m_def(MW270,MW271,MW272,MW273,MW274,MW275,MW276,MW277,MW278,MW279);
  28 : DEF := m_def(MW280,MW281,MW282,MW283,MW284,MW285,MW286,MW287,MW288,MW289);
  29 : DEF := m_def(MW290,MW291,MW292,MW293,MW294,MW295,MW296,MW297,MW298,MW299);

  30 : DEF := m_def(MW300,MW301,MW302,MW303,MW304,MW305,MW306,MW307,MW308,MW309);
  31 : DEF := m_def(MW310,MW311,MW312,MW313,MW314,MW315,MW316,MW317,MW318,MW319);
  32 : DEF := m_def(MW320,MW321,MW322,MW323,MW324,MW325,MW326,MW327,MW328,MW329);
  33 : DEF := m_def(MW330,MW331,MW332,MW333,MW334,MW335,MW336,MW337,MW338,MW339);
  34 : DEF := m_def(MW340,MW341,MW342,MW343,MW344,MW345,MW346,MW347,MW348,MW349);
  35 : DEF := m_def(MW350,MW351,MW352,MW353,MW354,MW355,MW356,MW357,MW358,MW359);
  36 : DEF := m_def(MW360,MW361,MW362,MW363,MW364,MW365,MW366,MW367,MW368,MW369);
  37 : DEF := m_def(MW370,MW371,MW372,MW373,MW374,MW375,MW376,MW377,MW378,MW379);
  38 : DEF := m_def(MW380,MW381,MW382,MW383,MW384,MW385,MW386,MW387,MW388,MW389);
  39 : DEF := m_def(MW390,MW391,MW392,MW393,MW394,MW395,MW396,MW397,MW398,MW399);

  40 : DEF := m_def(MW400,MW401,MW402,MW403,MW404,MW405,MW406,MW407,MW408,MW409);
  41 : DEF := m_def(MW410,MW411,MW412,MW413,MW414,MW415,MW416,MW417,MW418,MW419);
  42 : DEF := m_def(MW420,MW421,MW422,MW423,MW424,MW425,MW426,MW427,MW428,MW429);
  43 : DEF := m_def(MW430,MW431,MW432,MW433,MW434,MW435,MW436,MW437,MW438,MW439);
  44 : DEF := m_def(MW440,MW441,MW442,MW443,MW444,MW445,MW446,MW447,MW448,MW449);
  45 : DEF := m_def(MW450,MW451,MW452,MW453,MW454,MW455,MW456,MW457,MW458,MW459);
  46 : DEF := m_def(MW460,MW461,MW462,MW463,MW464,MW465,MW466,MW467,MW468,MW469);
  47 : DEF := m_def(MW470,MW471,MW472,MW473,MW474,MW475,MW476,MW477,MW478,MW479);
  48 : DEF := m_def(MW480,MW481,MW482,MW483,MW484,MW485,MW486,MW487,MW488,MW489);
  49 : DEF := m_def(MW490,MW491,MW492,MW493,MW494,MW495,MW496,MW497,MW498,MW499);

  50 : DEF := m_def(MW500,MW501,MW502,MW503,MW504,MW505,MW506,MW507,MW508,MW509);
  51 : DEF := m_def(MW510,MW511,MW512,MW513,MW514,MW515,MW516,MW517,MW518,MW519);
  52 : DEF := m_def(MW520,MW521,MW522,MW523,MW524,MW525,MW526,MW527,MW528,MW529);
  53 : DEF := m_def(MW530,MW531,MW532,MW533,MW534,MW535,MW536,MW537,MW538,MW539);
  54 : DEF := m_def(MW540,MW541,MW542,MW543,MW544,MW545,MW546,MW547,MW548,MW549);
  55 : DEF := m_def(MW550,MW551,MW552,MW553,MW554,MW555,MW556,MW557,MW558,MW559);
  56 : DEF := m_def(MW560,MW561,MW562,MW563,MW564,MW565,MW566,MW567,MW568,MW569);
  57 : DEF := m_def(MW570,MW571,MW572,MW573,MW574,MW575,MW576,MW577,MW578,MW579);
  58 : DEF := m_def(MW580,MW581,MW582,MW583,MW584,MW585,MW586,MW587,MW588,MW589);
  59 : DEF := m_def(MW590,MW591,MW592,MW593,MW594,MW595,MW596,MW597,MW598,MW599);

  60 : DEF := m_def(MW600,MW601,MW602,MW603,MW604,MW605,MW606,MW607,MW608,MW609);
  61 : DEF := m_def(MW610,MW611,MW612,MW613,MW614,MW615,MW616,MW617,MW618,MW619);
  62 : DEF := m_def(MW620,MW621,MW622,MW623,MW624,MW625,MW626,MW627,MW628,MW629);
  63 : DEF := m_def(MW630,MW631,MW632,MW633,MW634,MW635,MW636,MW637,MW638,MW639);
  64 : DEF := m_def(MW640,MW641,MW642,MW643,MW644,MW645,MW646,MW647,MW648,MW649);
  65 : DEF := m_def(MW650,MW651,MW652,MW653,MW654,MW655,MW656,MW657,MW658,MW659);
  66 : DEF := m_def(MW660,MW661,MW662,MW663,MW664,MW665,MW666,MW667,MW668,MW669);
  67 : DEF := m_def(MW670,MW671,MW672,MW673,MW674,MW675,MW676,MW677,MW678,MW679);
  68 : DEF := m_def(MW680,MW681,MW682,MW683,MW684,MW685,MW686,MW687,MW688,MW689);
  69 : DEF := m_def(MW690,MW691,MW692,MW693,MW694,MW695,MW696,MW697,MW698,MW699);

  70 : DEF := m_def(MW700,MW701,MW702,MW703,MW704,MW705,MW706,MW707,MW708,MW709);
  71 : DEF := m_def(MW710,MW711,MW712,MW713,MW714,MW715,MW716,MW717,MW718,MW719);
  72 : DEF := m_def(MW720,MW721,MW722,MW723,MW724,MW725,MW726,MW727,MW728,MW729);
  73 : DEF := m_def(MW730,MW731,MW732,MW733,MW734,MW735,MW736,MW737,MW738,MW739);
  74 : DEF := m_def(MW740,MW741,MW742,MW743,MW744,MW745,MW746,MW747,MW748,MW749);
  75 : DEF := m_def(MW750,MW751,MW752,MW753,MW754,MW755,MW756,MW757,MW758,MW759);
  76 : DEF := m_def(MW760,MW761,MW762,MW763,MW764,MW765,MW766,MW767,MW768,MW769);
  77 : DEF := m_def(MW770,MW771,MW772,MW773,MW774,MW775,MW776,MW777,MW778,MW779);
  78 : DEF := m_def(MW780,MW781,MW782,MW783,MW784,MW785,MW786,MW787,MW788,MW789);
  79 : DEF := m_def(MW790,MW791,MW792,MW793,MW794,MW795,MW796,MW797,MW798,MW799);

  80 : DEF := m_def(MW800,MW801,MW802,MW803,MW804,MW805,MW806,MW807,MW808,MW809);
  81 : DEF := m_def(MW810,MW811,MW812,MW813,MW814,MW815,MW816,MW817,MW818,MW819);
  82 : DEF := m_def(MW820,MW821,MW822,MW823,MW824,MW825,MW826,MW827,MW828,MW829);
  83 : DEF := m_def(MW830,MW831,MW832,MW833,MW834,MW835,MW836,MW837,MW838,MW839);
  84 : DEF := m_def(MW840,MW841,MW842,MW843,MW844,MW845,MW846,MW847,MW848,MW849);
  85 : DEF := m_def(MW850,MW851,MW852,MW853,MW854,MW855,MW856,MW857,MW858,MW859);
  86 : DEF := m_def(MW860,MW861,MW862,MW863,MW864,MW865,MW866,MW867,MW868,MW869);
  87 : DEF := m_def(MW870,MW871,MW872,MW873,MW874,MW875,MW876,MW877,MW878,MW879);
  88 : DEF := m_def(MW880,MW881,MW882,MW883,MW884,MW885,MW886,MW887,MW888,MW889);
  89 : DEF := m_def(MW890,MW891,MW892,MW893,MW894,MW895,MW896,MW897,MW898,MW899);

  90 : DEF := m_def(MW900,MW901,MW902,MW903,MW904,MW905,MW906,MW907,MW908,MW909);
  91 : DEF := m_def(MW910,MW911,MW912,MW913,MW914,MW915,MW916,MW917,MW918,MW919);
  92 : DEF := m_def(MW920,MW921,MW922,MW923,MW924,MW925,MW926,MW927,MW928,MW929);
  93 : DEF := m_def(MW930,MW931,MW932,MW933,MW934,MW935,MW936,MW937,MW938,MW939);
  94 : DEF := m_def(MW940,MW941,MW942,MW943,MW944,MW945,MW946,MW947,MW948,MW949);
  95 : DEF := m_def(MW950,MW951,MW952,MW953,MW954,MW955,MW956,MW957,MW958,MW959);
  96 : DEF := m_def(MW960,MW961,MW962,MW963,MW964,MW965,MW966,MW967,MW968,MW969);
  97 : DEF := m_def(MW970,MW971,MW972,MW973,MW974,MW975,MW976,MW977,MW978,MW979);
  98 : DEF := m_def(MW980,MW981,MW982,MW983,MW984,MW985,MW986,MW987,MW988,MW989);
  99 : DEF := m_def(MW990,MW991,MW992,MW993,MW994,MW995,MW996,MW997,MW998,MW999);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION set_sh : TPos8
  VAR_INPUT
    PSH : TPos8 := -1;
    Shape : TShape;
  END_VAR

  {{ return (SET_SH = ( __GET_GLOBAL_ITS()->SH.table[PSH] = SHAPE, PSH) ); }}
END_FUNCTION

FUNCTION_BLOCK ReadItem
  VAR_EXTERNAL
    HDR : THead;
  END_VAR
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR_OUTPUT
    iRes : TError := E_SUCCESS;
  END_VAR
  VAR
    Def : TDef;
    Item : TItem;
    Shape : TShape;
    Off : P_INT;
    msg : STRING;
    _GetDef : GetDef;
  END_VAR

  iRes:=E_SUCCESS;

  (* Проверка корректности индекса элемента *)
  if (PIT < 0 or PIT >= HDR.Ni) then iRes:=E_INDEX; {goto __exit} end_if;

  (* Получение определения элемента из массива конфигурации *)
  _GetDef(i := PIT, DEF => Def);

  (* Проверка индексов в массивах VAL, MAT, KNT *)
  if (HDR.Nv<>0 and Def.Iv >= HDR.Nv) then iRes:=E_VALUE; {goto __exit} end_if;
  if (HDR.Nm=0  or  Def.Im >= HDR.Nm) then iRes:=E_MATER; {goto __exit} end_if;
  if (HDR.Ng=0  or  Def.Ig >= HDR.Ng) then iRes:=E_GRID;  {goto __exit} end_if;

  (* Инициализация *)
  Item.ID  := Def.ID;  (* Копирование идентификатора элемента          *)
  Item.Im  := Def.Im;  (* Копирование индекса материала                *)
  Item.Iv  := Def.Iv;  (* Копирование индекса величины (если есть)     *)
  Item.Par := -1;      (* Родитель не определен, дерево строится позже *)
  Item.Num := 0;       (* Детей пока тоже нет, дерево строится позже   *)

  (* Флаги геометрии (расшифровка в Do_Validate)  *)
  Shape.wF  := Def.CF;   

  (* Временное размещение начальных смещений в Кn (int[0..2]) *)
  Shape.Kn[0] := Def.R0;                       (* начальный радиус (X0) *)
  Shape.Kn[1] := 
    WORD_TO_INT(SHR((Def.CF and 16#0F00), 8)); (* начальный сектор (Y0) *)
  Shape.Kn[2] := 0;                            (* начальная высота (Z0) *)

  (* Копирование xyz[], lwh[] *)
  Shape.pL[0] := INT_TO_REAL(Def.XYZ[0]);
  Shape.pL[1] := INT_TO_REAL(Def.XYZ[1]);
  Shape.pL[2] := INT_TO_REAL(Def.XYZ[2]);
  Shape.Lx[0] := INT_TO_REAL(Def.LWH[0]);
  Shape.Lx[1] := INT_TO_REAL(Def.LWH[1]);
  Shape.Lx[2] := INT_TO_REAL(Def.LWH[2]);

  (* Завершение процедуры *)
  {__exit:}
  if (iRes = E_SUCCESS) then 
    PIT := set_sh(PIT, Shape);
    PIT := set_it(PIT, Item);
  end_if;
END_FUNCTION_BLOCK

FUNCTION T2C : INT
  VAR_INPUT
    Temp : REAL := 0.0;
  END_VAR

  T2C := real_to_int(Temp*100.0);
END_FUNCTION

FUNCTION _var : TVar
  VAR_INPUT
    A : INT := -16384;
    B : INT := -16384;
    C : BOOL := false;
  END_VAR

  {{
    #pragma pack(push, 4)
    union { // 32-бит (4 байта)
      TVAR tv;
      struct {  // Значение (var)
        USINT  R:1;     // Флаг R (для var = 0)
          INT  A:15;    // Значение A (актуальное)
        USINT  C:1;     // Флаг C (1-расчёт готов)
          INT  B:15;    // Значение B (предыдущее)
      };
      struct {  // Ссылка   (ref)
        USINT  r:1;     // Флаг r (для ref = 1)
        USINT  d:2;     // Направление (0,1,2,3)
        USINT  p:8;     // Позиция элемента
        USINT  i:7;     // Индекс сетки по I (0..127)
        USINT  j:7;     // Индекс сетки по J (0..127)
        USINT  k:7;     // Индекс сетки по K (0..127)
      };
    } var = {0};
    #pragma pack(pop)
    
    var.A = A;  // Значение A (текущее)
    var.B = B;  // Значение B (предыдущее)
    var.C = C;  // Флаг "расчёт выполнен" (A!=B)
    
    _VAR = var.tv;
  }}
END_FUNCTION

FUNCTION IT_InitTemp : TPos8
  VAR_INPUT
    PIT : TPos8 := 0;
    Temp : REAL := 0.0;
    CLR : BOOL := false;
  END_VAR
  VAR
    Sh : TShape;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
    M : INT := 0;
    Off : P_INT;
  END_VAR

  Sh := get_sh(it_pos(PIT));
  for I:=0 to Sh.Kn[0]-1 do
    for J:=0 to Sh.Kn[1]-1 do
      for K:=0 to Sh.Kn[2]-1 do
        Off := knoff(Sh.Kn[0], Sh.Kn[1], Sh.Kn[2], I,J,K);
        if (CLR) then PIT := set_var(its_gr(0), PIT, Off, 0, 16#ff); end_if;
        PIT := set_var(its_gr(0), PIT, Off, _var(T2C(Temp), T2C(Temp)));
      end_for;
    end_for;
  end_for;
  IT_InitTemp := PIT;
END_FUNCTION

FUNCTION get_it : TItem
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (GET_IT = __GET_GLOBAL_ITS()->IT.table[PIT]); }}
END_FUNCTION

FUNCTION Do_Validate : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
    Item : TItem;
    Sh : TShape;
    Ax : USINT := 0;
    bAx : BOOL := false;
    bCx : BOOL := false;
    bOx : BOOL := false;
    OFF : P_INT;
    i : INT := 0;
    j : INT := 0;
    k : INT := 0;
    m : INT := 0;
    iP : TPos8 := 0;
    P0 : TPoint := [0.0, 0.0, 0.0];
    Lx : TPoint := [0.0, 0.0, 0.0];
    O : TAxO;
    RI : ARRAY [0..2] OF P_RESI;
    temp : P_RESI;
    rTemp : REAL := 0.0;
    bRes : BOOL := false;
  END_VAR
  VAR CONSTANT
    PI : REAL := 180.0;
    PI2 : REAL := 360.0;
    PI_RAD : REAL := 3.1415926535897932384626433832795;
  END_VAR

  Do_Validate := st_check(false);
  if (not Do_Validate) then return; end_if;

  (* Обход дерева элементов *)
  it := it_begin(ID2PIT(0));
  while (it.item<>-1) do
    (* Локальная копия элемента *)
    Item  := get_it(it.item);
    Sh    := get_sh(it.item);
    
    (* Расшифровка гео-флагов *)
    (* Флаги границ  - 0-7 биты в wF *)
    (* Sh.bF := WORD_TO_BYTE(Sh.wF AND 16#00FF); *)
    
    (* Номер сектора скопирован в Sh.Kn[1] в ReadItem() *)
    (*Item.nS := WORD_TO_USINT(SHR((Def.CF AND 16#0F00), 8)); *)

    (* Флаг составного элемента - 16 бит (не используется) *)
    (* Item.bP := ((Def.CF AND 16#8000)<>0); *)
    
    (* Ось симметрии - следующие 12-13 биты в wF *)
    Ax  := WORD_TO_USINT(SHR((Sh.wF AND 16#3000), 12));

    bCx := ((Sh.wF and 16#4000)<>0); (* Признак 'цилиндрич. система'   *)
    bAx := (Ax<>0);                  (* Признак 'ось задана'           *)
    bOx := (not bCx or bAx);         (* Признак 'задана точка отсчёта' *)

    case (it.dir) of
    DIR_DOWN:
      (* Определение точек начала отсчёта (НО) в ABS координатах   *)
      if (Item.Num>0 and bOx) then   (* Элемент с новой точкой отсчёта *)
        (* Прибавляем координаты НО к накопителю P0 *)
        P0[0] := P0[0] + Sh.pL[0]; 
        P0[1] := P0[1] + Sh.pL[1]; 
        P0[2] := P0[2] + Sh.pL[2];
      end_if;
      
    DIR_UP:
      (* Определение точек начала отсчёта в ABS координатах *)
      if (Item.Num>0 and bOx) then  (* Элемент с новой точкой отсчёта *)
        (* Вычитаем координаты НО из накопителя P0 *)
        P0[0] := P0[0] - Sh.pL[0]; 
        P0[1] := P0[1] - Sh.pL[1]; 
        P0[2] := P0[2] - Sh.pL[2];
      end_if;
      
      (* Сохраняем собственную точку НО *)
      Sh.p0[0] := P0[0]; 
      Sh.p0[1] := P0[1];
      Sh.p0[2] := P0[2];
      
      (* === Цилиндрическая система === *)
      if (bCx) then
      
        (* Если ось не задана - она наследуется от родителя *)
        if (not bAx)  then
          iP := Item.Par;
          while (iP<>-1) do
            Ax := sh_get_ax(get_sh(iP));
            iP := it_ip(iP);
            if (Ax<>0) then exit; end_if;
          end_while;
          if (Ax=0) then {goto __error} end_if;
        end_if;

        (* Индексы "оригинальных" координат: Ax -> O *)
         O := AxO(Ax);
         
        (* --- Преобразование начальной точки --- *)
        if (bAx) then
          (* Если ось задана:       *)
          (* (1) XYZ->OOO (декарт); *)
          Sh.p0[0]   := Sh.p0[0] + Sh.pL[0];
          Sh.p0[1]   := Sh.p0[1] + Sh.pL[1];
          Sh.p0[2]   := Sh.p0[2] + Sh.pL[2];
          
          (* (2) R0->X, nS->Y, Z=0  *)
          Sh.pL[O.x] := INT_TO_REAL(Sh.Kn[0]);            (* R0  *)
          Sh.pL[O.y] := INT_TO_REAL(Sh.Kn[1]) *(PI/8.0);  (* nS  *)
          Sh.pL[O.z] := INT_TO_REAL(Sh.Kn[2]);            (* 0.0 *)
        end_if;
        
        (* Приведение угловой координаты к диапазону [-PI..PI] *)
        Sh.pL[O.y]:=angle(Sh.pL[O.y], (-PI));
        
        (* Приведение углового размера   к диапазону [0..2*PI] *)
        Sh.Lx[O.y]:=angle(Sh.Lx[O.y], 0.0);
        
        (* Если размер =0 -> делаем его =360град *)
        if (Sh.Lx[O.y]=0.0) then Sh.Lx[O.y]:=PI2; end_if;
        
      else  (* Прямоугольные координаты *)
        Ax := 0;
      end_if;
      
      (* Установка флагов оси симметрии Ax *)
      Sh := sh_set_ax(Sh, Ax);
      
      (* === Расчёт сетки BEGIN === *)
      Lx:=Sh.Lx;
      
      (* Вычисление радиального размера *)
      if (Ax<>0) then Lx[O.y]:=Lx[O.x]*Lx[O.y]*PI_RAD/360.0; end_if;
      
      (* Инициализация перед сортировкой пар 'размер-индекс' *) 
      RI[0].A := Lx[0]; RI[0].B := 0;
      RI[1].A := Lx[1]; RI[1].B := 1;
      RI[2].A := Lx[2]; RI[2].B := 2;
      
      (* Сортировка пузырьком пар 'размер-индекс' *) 
      for i:=0 to 1 do
        for  j:=0 to 1-i do
          if (RI[j].A > RI[j+1].A) then
            temp:=RI[j]; RI[j]:=RI[j+1]; RI[j+1]:=temp;
          end_if;
        end_for;
      end_for;
      
      (* Определяем количество узлов сети (Kn) *)
      if ((RI[1].A+RI[2].A)/RI[0].A > 4.0) then
        Sh.Kn[RI[0].B]:=8;
        if ((RI[2].A/RI[1].A) > 4.0) then
          Sh.Kn[RI[1].B]:=8;  
          Sh.Kn[RI[2].B]:=64;
        else
          Sh.Kn[RI[1].B]:=16; 
          Sh.Kn[RI[2].B]:=32;
        end_if;
      else
        Sh.Kn[0]:=16; 
        Sh.Kn[1]:=16; 
        Sh.Kn[2]:=16;
      end_if;
      (* === Расчёт сетки END === *)

    end_case;

    (* TEST -> *)
    if not (
      (it.item>=1 and it.item<=99) 
    ) then 
      Item.Im := 0; (* воздух *)
    end_if;
    (* <- TEST *)

    (* Записываем "валидный" элемент ОБРАТНО в массив *)
    it.item := set_sh(it.item, Sh);
    it.item := set_it(it.item, Item);
    
    (* === Инициализация сетки элемента === *)
    it.item := IT_InitTemp(it.item, 20.0, true);
    
    it := it_next(it);
  end_while;

  (*PIT := IT_InitTemp(42, 100.0, true);*)

  Do_Validate := true;
  return;

  { __error: }
  Do_Validate := false;
END_FUNCTION

FUNCTION m_res : TRes
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
    MD8 : UDINT;
    MD9 : UDINT;
  END_VAR

  m_res.DR := MD0;  (* секунд от 01-01-1970 *)
  m_res.TR := UDINT_TO_TIME(MD1);
  m_res.FP := UDINT_TO_TIME(MD2);
  m_res.ER := UDINT_TO_UINT(MD3/65536);
  m_res.FL := UDINT_TO_WORD(mod(MD3,65536));
  m_res.RV[0] := MD4;
  m_res.RV[1] := MD5;
  m_res.RV[2] := MD6;
  m_res.RV[3] := MD7;
  m_res.RV[4] := MD8;
  m_res.RV[5] := MD9;
END_FUNCTION

FUNCTION_BLOCK GetRes
  VAR_EXTERNAL
    MD490 : UDINT;
    MD491 : UDINT;
    MD492 : UDINT;
    MD493 : UDINT;
    MD494 : UDINT;
    MD495 : UDINT;
    MD496 : UDINT;
    MD497 : UDINT;
    MD498 : UDINT;
    MD499 : UDINT;
  END_VAR
  VAR_OUTPUT
    RES : TRes;
  END_VAR

  RES := m_res(MD490,MD491,MD492,MD493,MD494,MD495,MD496,MD497,MD498,MD499);
END_FUNCTION_BLOCK

FUNCTION_BLOCK DistRes
  VAR_OUTPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
    MD8 : UDINT;
    MD9 : UDINT;
  END_VAR
  VAR_INPUT
    RES : TRes;
  END_VAR

  MD0 := RES.DR;  (* секунд от 01-01-1970 *)
  MD1 := TIME_TO_UDINT(RES.TR);
  MD2 := TIME_TO_UDINT(RES.FP);
  MD3 := UINT_TO_UDINT(RES.ER)*65536 + WORD_TO_UDINT(RES.FL);
  MD4 := RES.RV[0];
  MD5 := RES.RV[1];
  MD6 := RES.RV[2];
  MD7 := RES.RV[3];
  MD8 := RES.RV[4];
  MD9 := RES.RV[5];

END_FUNCTION_BLOCK

FUNCTION m_mat : TMat
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
  END_VAR

  m_mat.KT := UDI2REAL(MD0);
  m_mat.CP := UDI2REAL(MD1);
  m_mat.PL := UDI2REAL(MD2);
  m_mat.MD := UDI2REAL(MD3);
END_FUNCTION

FUNCTION_BLOCK GetMat
  VAR_EXTERNAL
    MD22 : UDINT;
    MD23 : UDINT;
    MD24 : UDINT;
    MD25 : UDINT;
    MD26 : UDINT;
    MD27 : UDINT;
    MD28 : UDINT;
    MD29 : UDINT;
    MD30 : UDINT;
    MD31 : UDINT;
    MD32 : UDINT;
    MD33 : UDINT;
    MD34 : UDINT;
    MD35 : UDINT;
    MD36 : UDINT;
    MD37 : UDINT;
    MD38 : UDINT;
    MD39 : UDINT;
    MD40 : UDINT;
    MD41 : UDINT;
    MD42 : UDINT;
    MD43 : UDINT;
    MD44 : UDINT;
    MD45 : UDINT;
    MD46 : UDINT;
    MD47 : UDINT;
    MD48 : UDINT;
    MD49 : UDINT;
    MD50 : UDINT;
    MD51 : UDINT;
    MD52 : UDINT;
    MD53 : UDINT;
    MD54 : UDINT;
    MD55 : UDINT;
    MD56 : UDINT;
    MD57 : UDINT;
    MD58 : UDINT;
    MD59 : UDINT;
    MD60 : UDINT;
    MD61 : UDINT;
    MD62 : UDINT;
    MD63 : UDINT;
    MD64 : UDINT;
    MD65 : UDINT;
    MD66 : UDINT;
    MD67 : UDINT;
    MD68 : UDINT;
    MD69 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    MAT : TMat;
  END_VAR

  CASE i OF
  0 : MAT := m_mat(MD22,MD23,MD24,MD25);
  1 : MAT := m_mat(MD26,MD27,MD28,MD29);
  2 : MAT := m_mat(MD30,MD31,MD32,MD33);
  3 : MAT := m_mat(MD34,MD35,MD36,MD37);
  4 : MAT := m_mat(MD38,MD39,MD40,MD41);
  5 : MAT := m_mat(MD42,MD43,MD44,MD45);
  6 : MAT := m_mat(MD46,MD47,MD48,MD49);
  7 : MAT := m_mat(MD50,MD51,MD52,MD53);
  8 : MAT := m_mat(MD54,MD55,MD56,MD57);
  9 : MAT := m_mat(MD58,MD59,MD60,MD61);
  10: MAT := m_mat(MD62,MD63,MD64,MD65);
  11: MAT := m_mat(MD66,MD67,MD68,MD69);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION st_set_stat : BOOL
  VAR_INPUT
    err : TError := E_SUCCESS;
    par : UINT := 0;
    str : STRING := '';
  END_VAR

  {{ 
    __GET_GLOBAL_STAT()->ERR=ERR; 
    __GET_GLOBAL_STAT()->PAR=PAR; 
    __GET_GLOBAL_STAT()->STR=STR;
    LOGMSG(1,NULL,STR,LOGLEVEL__DEBUG,ERR);
    return (ST_SET_STAT=ST_CHECK(1,NULL,FALSE));
  }}
END_FUNCTION

FUNCTION var_up : TVar
  VAR_INPUT
    TV : TVar := 0;
  END_VAR

  {{
    #pragma pack(push, 4)
    typedef union {
      TVAR tv;
      struct { USINT R:1;   INT A:15; USINT C:1;   INT B:15; };
      struct { USINT r:1; USINT d:2;   SINT p:8; USINT i:7; USINT j:7; USINT k:7; };
    } var_t, *pvar_t;
    #pragma pack(pop)
    pvar_t pvar = (pvar_t)&TV;
    // Если значение не ссылка - "поднимаем" значение A->B!
    if (!pvar->r) {
      //if (pvar->C) 
        pvar->B = (pvar->C=0, pvar->A);
    }
    VAR_UP = TV;
  }}
END_FUNCTION

FUNCTION set_cn : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
    COND : TCond;
  END_VAR

  {{ 
    __GET_GLOBAL_ITS()->CN.table[PIT] = COND;
    return (SET_CN = PIT);
  }}
END_FUNCTION

FUNCTION Sh_Loc2Abs : TPoint
  VAR_INPUT
    Sh : TShape;
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
  END_VAR
  VAR
    Ax : USINT := 0;
    A : TPoint := [0.0, 0.0, 0.0];
    B : TPoint := [0.0, 0.0, 0.0];
    O : TAxO;
  END_VAR

  (*Sh := get_sh(PIT);*)
  Ax := sh_get_ax(Sh);

  A := _point(X,Y,Z); 
  if (Ax > 0) then 
    (* Цилиндр -> Декарт *)
    O := AxO(Ax);
    A[O.y] := radi(A[O.y]); (* град -> радианы *)
    B[O.x] := A[O.x]*cos(A[O.y]);
    B[O.y] := A[O.x]*sin(A[O.y]);
    B[O.z] := A[O.z];
  else 
    B := A;
  end_if;
  Sh_Loc2Abs := _point(B[0]+Sh.P0[0],B[1]+Sh.P0[1],B[2]+Sh.P0[2]); 



END_FUNCTION

FUNCTION Sh_Dot2Point : TPoint
  VAR_INPUT
    Sh : TShape;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
    bAbs : BOOL := TRUE;
  END_VAR
  VAR
    Hn : TPoint := [0.0, 0.0, 0.0];
    Ax : USINT := 0;
    Ang : REAL := 0.0;
    Ox : TAxO;
    P : TPoint := [0.0, 0.0, 0.0];
  END_VAR

  Ax := sh_get_ax(Sh);

  (* (1) Определение локальной точки X, Y, Z  *)
  if (Sh.Kn[0]>1) then Hn[0]:=(Sh.Lx[0]/INT_TO_REAL(Sh.Kn[0]-1)); end_if;
  if (Sh.Kn[1]>1) then Hn[1]:=(Sh.Lx[1]/INT_TO_REAL(Sh.Kn[1]-1)); end_if;
  if (Sh.Kn[2]>1) then Hn[2]:=(Sh.Lx[2]/INT_TO_REAL(Sh.Kn[2]-1)); end_if;

  Sh_Dot2Point := _point( 
    Sh.pL[0] + INT_TO_REAL(I) * Hn[0],
    Sh.pL[1] + INT_TO_REAL(J) * Hn[1],
    Sh.pL[2] + INT_TO_REAL(K) * Hn[2] 
  );

  (* (2) Коррекция точки при изменении формы  *)
  if (Ax<>0) then
    Ox := AxO(Ax, true);
    P := Reform(Sh.wF, Sh_Dot2Point[Ox.y], 
                  Sh_Dot2Point[Ox.x], Sh.pL[Ox.x], Sh.Lx[Ox.x]);
    Sh_Dot2Point[Ox.x] := P[0];
  end_if;

  (* Преобразование локальной точки в абсолют *)
  if (bAbs) then
    Sh_Dot2Point := 
      Sh_Loc2Abs(Sh, Sh_Dot2Point[0], Sh_Dot2Point[1], Sh_Dot2Point[2]);
  end_if;
END_FUNCTION

FUNCTION it_update : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    Pt : TPoint;
    Kn : TKnot;
    Sh : TShape;
    Off : P_INT;
    iVar : INT := 0;
    TV : TVar := -1;
    Tmid : REAL := 0.0;
    count : INT := 0;
    i : INT := 0;
    j : INT := 0;
    k : INT := 0;
    Cond : TCond;
  END_VAR

  Sh := get_sh(it_pos(PIT));
  Kn := Sh.Kn;
  Cond.Tmin.V := 16383;   (* max_int7 *)
  Cond.Tmax.V := -16384;  (* min_int7 *)

  (* Вычисление средней, минимальной и максимальной температур *)
  for i:=0 to Kn[0]-1 do
    for J:=0 to Kn[1]-1 do
      for K:=0 to Kn[2]-1 do
        Off   := knoff(Kn[0], Kn[1], Kn[2], i,J,K);
        TV    := get_var(its_gr(0), PIT, Off);
        iVar  := var_v(TV);
        
        Tmid  := ( Tmid*int_to_real(count) + (int_to_real(iVar)/100.0) ) / 
                      int_to_real(count+1);
        if (iVar < Cond.Tmin.V) then Cond.Tmin := _dot(iVar, i,j,k); end_if;
        if (iVar > Cond.Tmax.V) then Cond.Tmax := _dot(iVar, i,j,k); end_if;
        
        TV    := var_up(TV);
        PIT   := set_var(its_gr(0), PIT, Off, (TV));
        count := count+1;
      end_for;
    end_for;
  end_for;

  (* Средняя температура элемента *)
  (* Cond.Tmid := T2C(Tmid); *)
  {{ COND.TMID = (INT)(TMID * 100.0); }}

  (* Минимальная температура элемента *)
  Pt := Sh_Dot2Point(Sh, Cond.Tmin.A[0], Cond.Tmin.A[1], Cond.Tmin.A[2]);
  Cond.Tmin.A[0] := real_to_int(Pt[0]);
  Cond.Tmin.A[1] := real_to_int(Pt[1]);
  Cond.Tmin.A[2] := real_to_int(Pt[2]);

  (* Максимальная температура элемента *)         
  Pt := Sh_Dot2Point(Sh, Cond.Tmax.A[0], Cond.Tmax.A[1], Cond.Tmax.A[2]);
  Cond.Tmax.A[0] := real_to_int(Pt[0]);
  Cond.Tmax.A[1] := real_to_int(Pt[1]);
  Cond.Tmax.A[2] := real_to_int(Pt[2]);

  (* Сохраняем состояние элемента *)
  PIT := set_cn(PIT, Cond);

  {{ // TEST
    if (PIT==53) *__GET_GLOBAL_RTEST() = TMID;
  }}

  IT_Update := PIT;

END_FUNCTION

FUNCTION Do_PostProc : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
  END_VAR

  (* Проверка статуса программы *)
  Do_PostProc := st_check(false);
  if (not Do_PostProc) then return; end_if;

  (* Обход дерева элементов *)
  Do_PostProc := true;
  it := it_begin(it_pos(PIT));
  while (it.item <>-1) do
    case (it.dir) of
    DIR_UP:
      (* Обновление состояния сетки элемента *)
      it.item := it_update(it.item);
    end_case;
    it := it_next(it);
  end_while;

  { __exit: }
  return;

  { __error: }
  Do_PostProc := st_set_stat(E_POSTPROC, it_id(it.item));

END_FUNCTION

FUNCTION Byte2Str : STRING
  VAR_INPUT
    Bt : BYTE := 0;
  END_VAR
  VAR
    i : SINT := 0;
    str : STRING := '2#';
  END_VAR

  for i:=7 to 0 by -1 do
    if ((Bt and shl(1, i))<>0) then
      str:=MakeMsg(str, '1');
    else
      str:=MakeMsg(str, '0');
    end_if;
  end_for;
  Byte2Str:=str;
END_FUNCTION

FUNCTION m_var_in : TVarI
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
  END_VAR

  m_var_in.DTI := MD0; (* секунд от 01-01-1970 *)
  m_var_in.TMI := UDINT_TO_TIME(MD1);
  m_var_in.TOV := UDINT_TO_REAL(MD2);
  m_var_in.MHT := UDINT_TO_REAL(MD3);
  m_var_in.RI1 := UDINT_TO_REAL(MD4);
  m_var_in.RI2 := UDINT_TO_REAL(MD5);
END_FUNCTION

FUNCTION Alfa_03 : P_RERE
  VAR_INPUT
    Ht : REAL := 0.0;
    M : TMatter;
    Tn_0 : REAL := 0.0;
    Tq_0 : REAL := 0.0;
    Qn_0 : REAL := 0.0;
    V_0 : REAL := 0.0;
    R_0 : REAL := 0.0;
    Bound3 : BOOL := TRUE;
  END_VAR
  VAR
    D_0 : REAL := 0.0;
    E_0 : REAL := 0.0;
    b_0 : REAL := 0.0;
    k_0 : REAL := 0.0;
    h2 : REAL := 0.0;
    at2 : REAL := 0.0;
    DE : REAL := 0.0;
    denom : REAL := 0.0;
    Res : P_RERE;
  END_VAR

  if (R_0 > 1.0E-5) then 
    if (not Bound3) then M.k := 1.0; end_if;
    b_0 := M.k/M.l;
    k_0 := b_0*Tq_0;
    if (not Bound3) then b_0 := 0.0; end_if;
    if (R_0 < 1.0E5) then E_0 := M.h / (2.0*R_0); end_if;
    D_0 := (abs(V_0)*M.h) / (2.0*M.a);
  else
    (* Малый радиус - условия симметрии h=0 *)
    M.h := 0.0;
  end_if;

  h2    := M.h * M.h;
  at2   := 2.0 * M.a * Ht;
  DE    := (1.0 + D_0 - E_0);
  denom := h2 + at2 * (1.0 + DE * M.h*b_0);

  Alfa_03.A := at2 / denom;
  Alfa_03.B := ( h2 * (Tn_0 + Ht*Qn_0) + at2 * DE * M.h*k_0 ) / denom;
END_FUNCTION

FUNCTION Alfa_04 : P_RERE
  VAR_INPUT
    Ht : REAL := 0.0;
    M1 : TMatter;
    M2 : TMatter;
    Alfa : P_RERE;
    Tn_0 : REAL := 0.0;
    Q1n_0 : REAL := 0.0;
    Q2n_0 : REAL := 0.0;
  END_VAR
  VAR
    A : REAL := 0.0;
    B : REAL := 0.0;
    F : REAL := 0.0;
  END_VAR

  (* Малый шаг - условие симметрии *)
  if (M1.h < 1.0E-4 or M2.h < 1.0E-4) then
    Alfa_04.A := 1.0;
    Alfa_04.B := 0.0;
  else
    (* Вариант-1: считаем известной T в точке i=-1, тогда Alfa.A=0, Alfa.B=T *)
    (* Вариант-2: считаем известной пару Alfa|Beta в точке i=-1 на момент расчёта *)

    A :=    M1.l / M1.h;

    B :=    (M1.l / M1.h) 
          + (M2.l / M2.h) 
          + (M1.l*M1.h/(2.0*M1.a*Ht))  
          + (M2.l*M2.h/(2.0*M2.a*Ht))
          - (M2.l / M2.h) * Alfa.A; (* Доп слагаемое - вариант 1 или 2 *)

    F :=  - Tn_0 * ( (M1.l*M1.h/(2.0*M1.a*Ht)) + (M2.l*M2.h/(2.0*M2.a*Ht)) ) 
          - (M1.l*M1.h/(2.0*M1.a)) * Q1n_0  
          - (M2.l*M2.h/(2.0*M2.a)) * Q2n_0 
          - (M2.l / M2.h) * Alfa.B; (* Доп слагаемое - вариант 1 или 2 *)

    Alfa_04.A :=  A/B;
    Alfa_04.B := -F/B;
  end_if;
END_FUNCTION

FUNCTION set_pdt : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
    Ix : USINT := 0;
    CDT : DT := DT#2000-01-01-00:00:00;
  END_VAR

  {{ return (SET_PDT = (__GET_GLOBAL_ITS()->IT.table[PIT].PDT.table[IX] = CDT, PIT)); }}
END_FUNCTION

FUNCTION get_mt : TMat
  VAR_INPUT
    PMT : TPos8 := -1;
  END_VAR

  {{ return (GET_MT = __GET_GLOBAL_STS()->MT.table[PMT]); }}
END_FUNCTION

FUNCTION link_var : TDot
  VAR_INPUT
    HGR : THandle := 0;
    PGR : TPos8 := -1;
    Sh : TShape;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
    Ix : USINT := 0;
    ign : TPos8 := -1;
    Dx : REAL := 0.1;
    Dyz : REAL := 0.1;
  END_VAR
  VAR
    Mx : REAL := 0.0;
    My : REAL := 0.0;
    Mz : REAL := 0.0;
    Pt : TPoint := [0.0, 0.0, 0.0];
    Dot : TDot;
  END_VAR

  if (Ix <> 0) then (* при линковке узлов смежных элементов *)

    (* Находим точку в данном узле решётки (лок) *)
    Pt  := Sh_Dot2Point(Sh, I, J, K, false);

    (* "Сверлим стену" *)
    if (I=0) then Mx:=1.0; elsif (I=Sh.Kn[0]-1) then Mx:=-1.0; end_if;
    if (J=0) then My:=1.0; elsif (J=Sh.Kn[1]-1) then My:=-1.0; end_if;
    if (K=0) then Mz:=1.0; elsif (K=Sh.Kn[2]-1) then Mz:=-1.0; end_if;
    
    case Ix of
      1: Pt := _point(Pt[0]-Mx*Dx , Pt[1]+My*Dyz, Pt[2]+Mz*Dyz);
      2: Pt := _point(Pt[0]+Mx*Dyz, Pt[1]-My*Dx , Pt[2]+Mz*Dyz);
      3: Pt := _point(Pt[0]+Mx*Dyz, Pt[1]+My*Dyz, Pt[2]-Mz*Dx );
    end_case;
    
    (* Преобразование локальной точки в абсолют *)
    Pt := Sh_Loc2Abs(Sh, Pt[0], Pt[1], Pt[2]);

  else (* при линковке узлов составных элементов и поверхностей *)

    (* Находим точку в данном узле решётки (абс) *)
    Pt := Sh_Dot2Point(Sh, I, J, K);

  end_if;

  (* Находим элемент, содержащий эту точку *)
  Dot := Do_FindDot(Pt[0], Pt[1], Pt[2], ign);

  (* Заносим ссылку на найденный элемент в сетку *)
  PGR := set_var( HGR, PGR, 
    knoff(Sh.Kn[0], Sh.Kn[1], Sh.Kn[2], I,J,K), 
    _ref(int_to_sint(Dot.v), Dot), 
    Ix 
  );

  (* Возвращаем позицию сетки, если слинковано, иначе = -1 *)
  link_var := (Dot);
END_FUNCTION

FUNCTION _surf : TShape
  VAR_INPUT
    PIT : TPos8 := -1;
    Ax : USINT := 0;
    X : REAL := 0.0;
    Y : REAL := 0.0;
    Z : REAL := 0.0;
  END_VAR
  VAR
    Pt : TPoint := [0.0, 0.0, 0.0];
  END_VAR

  (* Наследуем фигуру элемента модели *)
  if (PIT < 0) then PIT := 0; end_if;
  _surf := get_sh(PIT);

  (* Уточняем размерность сетки [64x64] *)
  _surf.wF := 0;
  _surf.Kn := _knot(64,64,64);
  _surf.Kn[Ax] := 1;

  (* Уточняем положение по точке привязки *)
  Pt := _point(X,Y,Z);
  (*
  _surf.pL[0] := _surf.pL[0]+0.1;
  _surf.pL[1] := _surf.pL[1]+0.1;
  _surf.pL[2] := _surf.pL[2]+0.1;
  *)
  _surf.pL[Ax] := Pt[Ax]; (* смещение по координате Ax *)
  (*
  _surf.Lx[0] := _surf.Lx[0]-0.2;
  _surf.Lx[1] := _surf.Lx[1]-0.2;
  _surf.Lx[2] := _surf.Lx[2]-0.2;
  *)
  _surf.Lx[Ax] := 0.0;    (* размер плоскости по Ax =0 *)
END_FUNCTION

PROGRAM P_RES
  VAR_EXTERNAL
    f_Res : BOOL;
    HDR : THead;
    ITS : TItems;
  END_VAR
  VAR
    pit : TPos8 := 0;
    Sh : TShape;
    Pt : TPoint;
    Off : P_INT;
    PGR : TPos8 := -1;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
    Dot : TDot;
    bRes : BOOL := false;
    iRes : TError := E_SUCCESS;
    iLog : INT := 0;
    msg : STRING := '';
    _WriteItem : WriteItem;
    _Grid2ul : Grid2ul;
    _GetHead : GetHead;
  END_VAR

  (* Считывание заголовка *)
  _GetHead(HEAD => HDR);

  (* Test *)
  (* if (HDR.ID = 100)  then HDR.ID := 99; end_if; *)
  (*
  HDR.ID := 100;
  HDR.Ax := 2;
  HDR.pX := 1800;
  HDR.pY := 620;
  HDR.pZ := 1575;
  *)
  (* =1= Протоколирование на консоль === *)
  bRes := Do_LogCond(ID2PIT(0));

  (* =2= Запись массива элементов в регистры === *)
  (*msg:=LogMsg('Write items ... '); *)
  FOR pit := 0 TO HDR.Ni-1 DO 
    _WriteItem(PIT := pit);
    (*
    if (len(msg)=0) then msg := MakeMsg(' - Updated items: '); end_if;
    msg := MakeMsg(msg, ' [', ID2Str(IT_ID(pit)), ',');
    msg := MakeMsg(msg,       SINT_TO_STRING(pit), ']');
    if (mod((pit+1),5)=0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
    *)
  END_FOR; 
  (* if (len(msg)>0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if; *)

  (* =3= Вывод T-поля объекта [POS=HDR.ID] в регистры === *)
  msg:=LogMsg(MakeMsg(msg, '===== T-Field START ====='));      

  pit := UINT_TO_SINT(HDR.ID); (* it_pos(ID2PIT(HDR.ID)); *)
  if (pit >= 0 and pit < HDR.Ni) then 

    (* Вывод поля обычного элемента *)
    Sh := get_sh(pit);
    _Grid2ul(HGR := its_gr(0), PGR := pit, SH := Sh, iRes=>iRes);
    
  elsif (pit = 100) then (* Вывод поля поверхности *)
    
    Sh := _surf(
      ID2PIT(0), 
      UINT_TO_USINT(HDR.Ax), 
      INT_TO_REAL(HDR.pX), 
      INT_TO_REAL(HDR.pY), 
      INT_TO_REAL(HDR.pZ)
    );
    (*Sh := get_sh(0);*)
    ITS.Sh[pit] := Sh;
    
    (* Линковка узлов *)
    iLog := 0;
    for I:=0 to Sh.Kn[0]-1 do
      for J:=0 to Sh.Kn[1]-1 do
        for K:=0 to Sh.Kn[2]-1 do
        
          Dot := link_var(its_gr2(0), 0, Sh, I, J, K);
          (*
          Pt  := Sh_Dot2Point(Sh, I, J, K);
          Dot := Do_FindDot(Pt[0], Pt[1], Pt[2]);
          Off := knoff(Sh.Kn[0], Sh.Kn[1], Sh.Kn[2], I,J,K);
          PGR := set_var( its_gr2(0), 0, Off, _ref(int_to_sint(Dot.v), Dot));
          *)
          
          (*
          if (false or iLog<80) then  
            if (len(msg)=0) then msg := MakeMsg(' =!=> '); end_if;
            msg := MakeMsg(msg, '[', INT_TO_STRING(REAL_TO_INT(Pt[0])), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(REAL_TO_INT(Pt[1])), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(REAL_TO_INT(Pt[2])), ']');
            if (mod((iLog+1),8)=0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
            iLog:=iLog+1;
          end_if;
          *)
          (*
          if (iLog<80) then  
            if (len(msg)=0) then msg := MakeMsg(' =!=> '); end_if;
            msg := MakeMsg(msg, '[', INT_TO_STRING(Dot.v), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(Dot.a[0]), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(Dot.a[1]), ',');
            msg := MakeMsg(msg,  '', INT_TO_STRING(Dot.a[2]), ']');
            if (mod((iLog+1),8)=0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
            iLog:=iLog+1;
          end_if;
          *)
        end_for;
      end_for;
    end_for;
    if (len(msg)>0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
    
    _Grid2ul(HGR := its_gr2(0), PGR := 0, SH := Sh, iRes=>iRes);
    
  else (* ошибка позиции *)
    {}

  end_if;
  msg:=LogMsg(MakeMsg(msg, '===== T-Field (END) ====='));      

  (* Сброс флага *)
  f_Res := FALSE;
END_PROGRAM

FUNCTION m_val : TVal
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
  END_VAR

  m_val.Iv      := UDINT_TO_INT(MD0/65536);
  m_val.Vi[0].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD0,65536))/256);
  m_val.Vi[0].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD0,65536)),256));
  m_val.Vi[1].A := UINT_TO_SINT(UDINT_TO_UINT(MD1/65536)/256);
  m_val.Vi[1].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD1/65536),256));
  m_val.Vi[2].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD1,65536))/256);
  m_val.Vi[2].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD1,65536)),256));


END_FUNCTION

FUNCTION_BLOCK GetVal
  VAR_EXTERNAL
    MD70 : UDINT;
    MD71 : UDINT;
    MD72 : UDINT;
    MD73 : UDINT;
    MD74 : UDINT;
    MD75 : UDINT;
    MD76 : UDINT;
    MD77 : UDINT;
    MD78 : UDINT;
    MD79 : UDINT;
    MD80 : UDINT;
    MD81 : UDINT;
    MD82 : UDINT;
    MD83 : UDINT;
    MD84 : UDINT;
    MD85 : UDINT;
    MD86 : UDINT;
    MD87 : UDINT;
    MD88 : UDINT;
    MD89 : UDINT;
    MD90 : UDINT;
    MD91 : UDINT;
    MD92 : UDINT;
    MD93 : UDINT;
    MD94 : UDINT;
    MD95 : UDINT;
    MD96 : UDINT;
    MD97 : UDINT;
    MD98 : UDINT;
    MD99 : UDINT;
    MD100 : UDINT;
    MD101 : UDINT;
    MD102 : UDINT;
    MD103 : UDINT;
    MD104 : UDINT;
    MD105 : UDINT;
    MD106 : UDINT;
    MD107 : UDINT;
    MD108 : UDINT;
    MD109 : UDINT;
    MD110 : UDINT;
    MD111 : UDINT;
    MD112 : UDINT;
    MD113 : UDINT;
    MD114 : UDINT;
    MD115 : UDINT;
    MD116 : UDINT;
    MD117 : UDINT;
    MD118 : UDINT;
    MD119 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    VAL : TVal;
  END_VAR

  CASE i OF
  0 : VAL := m_val(MD70,MD71);
  1 : VAL := m_val(MD72,MD73);
  2 : VAL := m_val(MD74,MD75);
  3 : VAL := m_val(MD76,MD77);
  4 : VAL := m_val(MD78,MD79);
  5 : VAL := m_val(MD80,MD81);
  6 : VAL := m_val(MD82,MD83);
  7 : VAL := m_val(MD84,MD85);
  8 : VAL := m_val(MD86,MD87);
  9 : VAL := m_val(MD88,MD89);
  10: VAL := m_val(MD90,MD91);
  11: VAL := m_val(MD92,MD93);
  12: VAL := m_val(MD94,MD95);
  13: VAL := m_val(MD96,MD97);
  14: VAL := m_val(MD98,MD99);
  15: VAL := m_val(MD100,MD101);
  16: VAL := m_val(MD102,MD103);
  17: VAL := m_val(MD104,MD105);
  18: VAL := m_val(MD106,MD107);
  19: VAL := m_val(MD108,MD109);
  20: VAL := m_val(MD110,MD111);
  21: VAL := m_val(MD112,MD113);
  22: VAL := m_val(MD114,MD115);
  23: VAL := m_val(MD116,MD117);
  24: VAL := m_val(MD118,MD119);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION_BLOCK Sort_IDS
  VAR_EXTERNAL
    ITS : TItems;
  END_VAR
  VAR_INPUT
    iBegin : TPos8 := 0;
    iEnd : TPos8 := 0;
  END_VAR
  VAR_OUTPUT
    iRes : TError := E_SUCCESS;
  END_VAR
  VAR
    iL : TPos8;
    iR : TPos8;
    LL : TPos8;
    RR : TPos8;
    Z : P_IDPIT;
    iS : TPos8;
    Stack : ARRAY [0..49] OF TPos8;
    fBreak : BOOL;
    tmp : P_IDPIT;
  END_VAR

  (* Начальные значения *)
  iRes  := E_SUCCESS;				
  iS    := 0; 
  iL    := iBegin; 
  iR    := iEnd; 

  fBreak := false;
  WHILE NOT fBreak DO         (* внешний цикл = "рекурсия" *)
    
  	IF iL < iR THEN
      (* Значение среднего элемента в качестве опорного значения *)
  		Z := ITS.Pr[WORD_TO_SINT(SHR(UINT_TO_WORD(SINT_TO_UINT(iR)+SINT_TO_UINT(iL)),1))]; 
      
  		LL := iL; RR := iR;
  		WHILE (LL <= RR) DO     (* внутренний цикл = выделение частей *)
   			(* Сравнение - возрастающий порядок *)
        while (ITS.Pr[LL].A < Z.A) do LL:=LL+1; end_while;
        while (ITS.Pr[RR].A > Z.A) do RR:=RR-1; end_while;
  			if LL <= RR then  
          if (LL <> RR) then  (* Обмен значений *)
            tmp := ITS.Pr[RR]; 
            ITS.Pr[RR] := ITS.Pr[LL]; 
            ITS.Pr[LL] := tmp; 
          end_if;        
          LL:=LL+1; RR:=RR-1;
  			end_if;
  		END_WHILE;

  		(* Вставка в стек *)
  		IF iS < 49 THEN 
        Stack[iS] := iR;		  (* Отложенная сортировка правой части  *)
        iS := iS+1; 
      ELSE                    (* Стек выбран - ошибка величины стека *)
        fBreak := TRUE; 
        iRes := E_STACKSIZE; 
      END_IF;
        
  		iR := MAX(iL, LL-1);    (* Сортировка левой части - в следующем цикле *)
      
    ELSE
      
  		IF iS > 0 THEN          (* Теперь сортируем правую часть *)
  			iL := iR+1;
  			(* Выборка из стека *)
  			iS := iS-1;	
  			iR:= Stack[iS];
  		ELSE                    (* Стек выбран - конец работы *)
        fBreak := TRUE;
  		END_IF;
      
  	END_IF;
    
  END_WHILE; (* Сортировка завершена *)
END_FUNCTION_BLOCK

FUNCTION st_is_ready : BOOL
  VAR_INPUT
    tmp : BOOL := FALSE;
  END_VAR

  {{ return (ST_IS_READY=__GET_GLOBAL_STAT()->RDY); }}
END_FUNCTION

FUNCTION kto_air : REAL
  VAR_INPUT
    L : REAL := 0.0;
  END_VAR

  kto_air:=10.0;
END_FUNCTION

FUNCTION get_pdt : DT
  VAR_INPUT
    PIT : TPos8 := -1;
    Ix : USINT := 0;
  END_VAR

  {{ return (GET_PDT = __GET_GLOBAL_ITS()->IT.table[PIT].PDT.table[IX]); }}
END_FUNCTION

FUNCTION get_h : THead
  VAR_INPUT
    Dummy : DINT := 0;
  END_VAR

  {{ return (GET_H = *__GET_GLOBAL_HDR()); }}
END_FUNCTION

FUNCTION get_pr : TProf
  VAR_INPUT
    PPR : TPos8 := -1;
  END_VAR

  {{ return (GET_PR = __GET_GLOBAL_STS()->PR.table[PPR]); }}
END_FUNCTION

FUNCTION cn_mid : INT
  VAR_INPUT
    Cond : TCond;
  END_VAR

  CN_MID := COND.TMID;
END_FUNCTION

FUNCTION IT_Process : TError
  VAR_INPUT
    PIT : TPos8 := -1;
    Ix : USINT := 0;
    CDT : DT := DT#2000-01-01-00:00:00;
  END_VAR
  VAR
    PDT : DT := DT#2000-01-01-00:00:00;
    It : TItem;
    Hd : THead;
    Sh : TShape;
    Ax : USINT := 0;
    Ox : TAxO;
    Cx : TAxO;
    Q : SINT := 0;
    Ht : REAL := 0.0;
    K : ARRAY [0..2] OF INT;
    L : ARRAY [0..2] OF INT;
    H0 : TPoint := [0.0, 0.0, 0.0];
    Hx2 : TPoint := [0.0, 0.0, 0.0];
    pR : TPoint := [0.0, 0.0, 0.0];
    Iv : SINT := 0;
    Im : SINT := 0;
    V : TVal;
    Vx : REAL := 0.0;
    Px : TProf;
    Cm : TMat;
    Pm : TProps;
    P0 : TPoint := [0.0, 0.0, 0.0];
    Hi : REAL := 0.0;
    Hi2 : REAL := 0.0;
    Pi : TPoint := [0.0, 0.0, 0.0];
    Ri : REAL := 0.0;
    Li : REAL := 0.0;
    Vi1 : REAL := 0.0;
    Qi1 : REAL := 0.0;
    Ti1 : REAL := 0.0;
    M : TMatter;
    P : TPoint := [0.0, 0.0, 0.0];
    TV : TVar := 0;
    LR : ARRAY [0..3] OF P_BOOL := [FALSE, FALSE, FALSE, FALSE];
    PIT2 : TPos8 := -1;
    Kn2 : TKnot := [0, 0, 0];
    Im2 : SINT := 0;
    Cm2 : TMat;
    Pm2 : TProps;
    Iv2 : SINT := 0;
    V2 : TVal;
    Vx2 : REAL := 0.0;
    Px2 : TProf;
    Vi2 : REAL := 0.0;
    Qi2 : REAL := 0.0;
    Ti2 : REAL := 0.0;
    M2 : TMatter;
    Tmid2 : REAL := 0.0;
    i : INT := 0;
    N : INT := 0;
    off : P_INT;
    xx : REAL := 0.0;
    ii : INT := 0;
    Alfa : P_RERE;
    Alfas : ARRAY [0..63] OF P_RERE;
    iRes : TError := E_SUCCESS;
    bRes : BOOL := false;
    msg : STRING := '';
  END_VAR
  VAR CONSTANT
    Kt : REAL := 300.0;
    Hmin : REAL := 1.0E-5;
  END_VAR

  (* Получаем время предыдущего расчёта и сохраняем текущее *)
  PDT := get_pdt(PIT, Ix);
  PIT := set_pdt(PIT, Ix, CDT);

  Hd := get_h(0);       (* Заголовок модели *)
  It := get_it(PIT);    (* Элемент          *)
  Sh := get_sh(PIT);    (* Фигура элемента  *)
  Ax := sh_get_ax(Sh);  (* Направление оси  *)

  Im := It.Im;          (* Индекс материала *)
  Iv := It.Iv;          (* Индекс величины  *)

  Cm := get_mt(It.Im);  (* Материал *)

  (* Получение значения динамической величины элемента-1 и её профиля *)
  if (Iv > 0 and Iv < Hd.Nv) then
    V  := get_vl(It.Iv);
    Vx := get_bf(V.Iv) * sint_to_real(V.Vi[Ix].A);
    Px := get_pr(V.Vi[Ix].B);
  end_if;

  (* Ориентация элемента *)
  Ox := AXO(Ax,  TRUE);     (* Порядок перебора координат *)
  Cx := AXO(Ix+1, FALSE);   (* Порядок обхода сетки       *)

  (* Признаки материала *)
  Pm.Air   := (Im = 0);            (* Признак - воздух (нулевой материал) *)
  Pm.Oil   := (Cm.MD <> 0.0);      (* Признак - масло  (задана вязкость)  *)
  Pm.Fluid := (Pm.Oil or Pm.Air);  (* Признак - флюид  (воздух или масло) *)
  Pm.Solid := (not Pm.Fluid);      (* Признак - твердое тело (не флюид)   *)

  (* Если элемент - воздух - не считаем *)
  if (Pm.Air) then {goto __exit} end_if;

  (* Опредедение шага (Ht>0) по времени в секундах *)
  Ht := 300.0; (*Kt * ULINT_TO_REAL(DT_TO_ULINT(CDT)-DT_TO_ULINT(PDT));*)
  if (Ht < 1.0) then iRes:=E_TIMESIZE; {goto __exit} end_if;

  (* Опредедение шага по сетке (ориг) *)
  H0 := _point( Sh.Lx[0]/INT_TO_REAL(Sh.Kn[0]-1), 
                Sh.Lx[1]/INT_TO_REAL(Sh.Kn[1]-1), 
                Sh.Lx[2]/INT_TO_REAL(Sh.Kn[2]-1) );
  if ( (H0[0]<Hmin) or (H0[1]<Hmin) or (H0[2]<Hmin) ) 
    then iRes:=E_STEPSIZE; {goto __exit} end_if;

  (* TEST *)
  (* Имитация тепловыделения в обмотках низкого и высокого напряжения *)
  if (PIT = 21 or PIT = 31) then Vx := 5.0; end_if;
  if (PIT = 38 or PIT = 59 or PIT = 80) then Vx := 3.0;  end_if;
  if (PIT = 42 or PIT = 63 or PIT = 84) then Vx := 12.0; end_if;
  if (PIT = 45 or PIT = 46 or PIT = 47 or PIT = 48 or PIT = 49 or 
      PIT = 50 or PIT = 51 or PIT = 52 or PIT = 53 or PIT = 54) then Vx := 20.0; end_if;
  if (PIT = 66 or PIT = 67 or PIT = 68 or PIT = 69 or PIT = 70 or 
      PIT = 71 or PIT = 72 or PIT = 73 or PIT = 74 or PIT = 75) then Vx := 20.0; end_if;
  if (PIT = 87 or PIT = 88 or PIT = 89 or PIT = 90 or PIT = 91 or 
      PIT = 92 or PIT = 93 or PIT = 94 or PIT = 95 or PIT = 96) then Vx := 20.0; end_if;

  (* Базовые значения профилируемых величин-1 - "равномерно без профиля" *)
  if (Vx=0.0) then Vi1 := 0.0; Qi1 := 0.0;
  else
    if (Pm.Fluid) then Vi1 := abs(Vx);                    (* скорость       *)
    else Qi1 := Vx/INT_TO_REAL(Sh.Kn[0]*Sh.Kn[1]*Sh.Kn[2]);  (* тепловыделение *)
    end_if; 
  end_if;

  (* Сохранение верхних индексов узлов сетки по координатным осям *)
  L[Cx.x] := Sh.Kn[0]-1; (* =2 при iX=0 *)
  L[Cx.y] := Sh.Kn[1]-1; (* =0 при iX=0 *)
  L[Cx.z] := Sh.Kn[2]-1; (* =1 при iX=0 *)
  N:=L[2];  (* верхний индекс прогонки *)

  (* Циклы по сетке в направлении Ix *)
  K[0]:=0;
  while (K[0] <= L[0]) do (* Цикл (0) *)
    K[1]:=0;
    while (K[1] <= L[1]) do (* Цикл (1) *)
      K[2]:=0;
    
      (* Локальная точка элемента в начале нити *)
      P0 := _point( Sh.pL[0] + H0[0]*INT_TO_REAL(K[Cx.x]), 
                    Sh.pL[1] + H0[1]*INT_TO_REAL(K[Cx.y]),
                    Sh.pL[2] + H0[2]*INT_TO_REAL(K[Cx.z]) );

      (* Коррекция начальной точки и шага в направлении радиуса *)
      if (Ax<>0 (*and Ix=Ox.x*)) then
        P0[Ox.y] := angle(P0[Ox.y], Sh.pL[Ox.y]);
        P := Reform(Sh.wF, P0[Ox.y], P0[Ox.x], Sh.pL[Ox.x], Sh.Lx[Ox.x]);
        P0[Ox.x] := P[0];                 (* коррекция начальной точки *)
        H0[Ox.x] := P[2]/INT_TO_REAL(N);  (* коррекция шага по радиусу *)
      end_if;
                                                        
      (* === Прямая прогонка === *)
      for i:=0 to N do (* Цикл (2) - прогонка по направлению Ix *)
        K[2]   := i;                      (* i -  индекс нити прогонки *)
        Pi     := P0;                     (* P0 - начальная точка нити *)
        Pi[Ix] := P0[Ix] + 
                  H0[Ix]*INT_TO_REAL(i);  (* текущая точка узла        *)
        
        (* Расчёт радиуса Ri и шага Hi *)
        if (Ax<>0 and Ix=Ox.x) then    (* движение по радиусу       *)
          Ri := Pi[Ix]   * 0.001;         (* мм->м                     *)
          Hi := H0[Ix]   * 0.001;         (* мм->м                     *)
        elsif (Ax<>0 and Ix=Ox.y) then (* движение по дуге          *)
          P  := Reform(Sh.wF, Pi[Ox.y], Pi[Ox.x], Sh.pL[Ox.x], Sh.Lx[Ox.x]);
          Pi[Ox.x] := P[0];               (* радиальная координата     *)
          Ri := Pi[Ox.x] * 0.001;         (* мм->м                     *)
          Hi := Ri * radi(H0[Ix]);        (* длина дуги (м)            *)
        else                              (* "плоское" движение        *)
          Ri := 1.0e6;                    (* большой радиус            *)
          Hi := H0[Ix]   * 0.001;         (* мм->м                     *)
        end_if;

        (* Свойства материи M(a, lambda, h, k) *)
        M := _Matter(Cm.kt/(Cm.PL*Cm.CP), Cm.kt, Hi);
        
        (* Смещение расчётного узла в сетке *)
        Off := knoff(Sh.Kn[0], Sh.Kn[1], Sh.Kn[2], K[Cx.x], K[Cx.y], K[Cx.z]);
        
        (* Температура расчётного узла (код (int) -> °С (real)) *)
        Ti1 := C2T(var_v( get_var(its_gr(0), PIT, Off) )); 
        
        (* Обработка краевых условий *)
        if ((i = 0) or (i = N)) then
        
          (* Получение дескриптора смежного элемента (PIT2) *)
          TV   := get_var(its_gr(0), PIT, Off, Ix+1);
          PIT2 := var_p(TV); (* может быть = (-1) *)
          
          {{
            // Доступ к свойствам элемента-2
            TITEM *pItem2 = ((PIT2==-1) ? NULL : &(__GET_GLOBAL_ITS()->IT.table[PIT2]));
            IM2 = ((pItem2==NULL) ? 0 : pItem2->IM);  // Индекс материала
            CM2 = GET_MT(1,NULL,IM2);                 // Материал
            
            if (IM2==0) { // воздух =>
              VX2 = 0.0;                              // динимаческая величина = 0
            } else {      // обычный элемент =>
              IM2 = pItem2->IM;                       // Индекс материала
              IV2 = pItem2->IV;                       // Индекс величины

              __ARRAY_OF_TVAL_25  *pVAL = &__GET_GLOBAL_STS()->VL; // Связанные величины
              __ARRAY_OF_TPROF_30 *pPRO = &__GET_GLOBAL_STS()->PR; // Профили
              __ARRAY_OF_REAL_32  *pBUF = &__GET_GLOBAL_STS()->BF; // Буфер величин
                          
              if (IV2 > 0 && IV2 < HD.NV) {
                VX2 = pVAL->table[IV2].VI.table[IX].A * pBUF->table[pVAL->table[IV2].IV];
                PX2 = pPRO->table[pVAL->table[IV2].VI.table[IX].B];
              }
            }
            
          }}
          
          (*Kn2   := it_kn(PIT2);*) (* размерность сетки элемента-2 *)
          
          (* времяночка - заплатка *)
          Tmid2 := C2T(cn_mid(get_cn(PIT2)));
          
          (* Признаки материала 2 (соседа) *)
          Pm2.Air   := (Im2 = 0);             (* Признак - воздух (Im=0)         *)
          Pm2.Oil   := (Cm2.md <> 0.0);       (* Признак - масло  (md<>0)        *)
          Pm2.Fluid := (Pm2.Oil or Pm2.Air);  (* Признак - флюид  (Air or Oil)   *)
          Pm2.Solid := (not Pm2.Fluid);       (* Признак - твердое тело          *)

          (* Базовые значения профилируемых величин-2 - "равномерно без профиля" *)
          if (Vx2=0.0) then Vi2 := 0.0; Qi2 := 0.0;
          else
            if (Pm2.Fluid) then Vi2 := abs(Vx2);
            else Qi2 := Vx2/INT_TO_REAL( 4096 (*Kn2[0] * Kn2[1] * Kn2[2]*) ); 
            end_if; 
          end_if;

          (* Запрашиваем температуру в узле сетки-2, ближайшем к точке расчёта *)
          (*
          P   := Sh_Loc2Abs(PIT, Pi[0], Pi[1], Pi[2]);
          TV := IT_Check(PIT2, P[0], P[1], P[2], false);
          *)
          
          Ti2 := C2T(var_v(TV)); (* код (int) -> °С (real) *)
          
          (* TV.PT := Sh_Dot2Point(PIT2, var_d(TV.TV)) *)
          (* Hi2 := abs(P[Ix]-TV.PT[Ix]); *)
          
          (*+*)   if (K[0]=0 and K[1]=0 and PIT=3) then
                    msg := MakeMsg(   '-> Ti2= ', REAL_TO_STRING(Ti2));
                    msg := MakeMsg(msg, ' off= ', INT_TO_STRING(OFF.A));
                    msg := MakeMsg(msg, ' PIT= ', SINT_TO_STRING(PIT2));
                    msg := MakeMsg(msg, ' Hi2= ', REAL_TO_STRING(Hi2));
                    msg := LogMsg (msg);
                  end_if; 
                                                  
          (* Свойства материи-2 *)
          M2 := _Matter(Cm2.kt/(Cm2.PL*Cm2.CP), Cm2.KT, (* Hi2* *)0.001); (* в метрах *)
          
          (* === Метод прогонки === *)
          if (i = 0) then (* левая граница *)
          
            (* --- Расчёт коэффициентов Alfas[0] на левой границе --- *)
            if (Pm2.Air) then (* ГУ-3 *)
            
              if (true) then
                M.k := kto_air(1.0);
                Alfas[0] := Alfa_03(Ht, M, Ti1, Ti2, Qi1, Vi1, Ri);
              else
                Alfa.A := 0.0; Alfa.B := Ti2; 
                Alfas[0] := Alfa_i(Ht, M, Alfa, Ti1, Qi1, Vi1, Ri);
              end_if;
              
            elsif ((*(Pm.Oil and Pm2.Solid) or*) (Pm.Solid and Pm2.Oil)) then
            
                M.k := kto_oil(1.0);
                Alfas[0] := Alfa_03(Ht, M, Ti1, Tmid2-(Tmid2-20.0)/2.2, Qi1, Vi1, Ri);
            
            else  (* ГУ-4 *)
            
              Alfa.A := 0.0; Alfa.B := Ti2; 
              if (true) then
                (* Вариант 1 *)
                Alfas[0] := Alfa_i(Ht, M, Alfa, Ti1, Qi1, Vi1, Ri);
              else
                (* Вариант 2 *)
                M2.h := 0.001;
                Alfas[0] := Alfa_04(Ht, M, M2, Alfa, Ti1, Qi1, Qi2);
              end_if;
              
            end_if;
            
          elsif (i = N) then (* правая граница *)
          
            (* --- Расчёт температуры T[N] на правой границе --- *)
            if (Pm2.Air) then (* ГУ-3 *)
            
              if (true) then
                M.k := kto_air(1.0);
                xx := Beta_N3(Ht, M, Alfas[N-1], Ti1, Ti2, Qi1, Vi1, Ri);
              else
                Alfas[N] := Alfa_i(Ht, M, Alfas[N-1], Ti1, Qi1, Vi1, Ri);
                xx := Temp_i(Alfas[N], Ti2);
              end_if;
              
            elsif ((*(Pm.Oil and Pm2.Solid) or*) (Pm.Solid and Pm2.Oil)) then
            
                M.k := kto_oil(1.0);
                xx := Beta_N3(Ht, M, Alfas[N-1], Ti1, Tmid2-(Tmid2-20.0)/2.2, Qi1, Vi1, Ri);
            
            else (* ГУ-4 *)
            
              if (true) then
                (* Вариант 1 *)
                (*M.h := Hx2[Ix] * 0.001;*)
                Alfas[N] := Alfa_i(Ht, M, Alfas[N-1], Ti1, Qi1, Vi1, Ri);
                xx := Temp_i(Alfas[N], Ti2);
              else
                (* Вариант 2 *)
                M2.h := 0.001;
                xx := Beta_N4(Ht, M, M2, Alfas[N-1], Ti1, Ti2, Qi1, Qi2);
              end_if;
              
            end_if;
            
            (* Запись значения xx в сетку, °С (real) -> код (int) *)
            PIT := set_var(its_gr(0), PIT, OFF, _var(T2C(xx)));
            
            (*+*)     if (K[0]=0 and K[1]=0 and PIT =3) then
                        msg := MakeMsg(' T[', INT_TO_STRING(i), ']= ', REAL_TO_STRING(xx));
                        msg := MakeMsg(msg, ' M.a=', REAL_TO_STRING(M.a));
                        msg := MakeMsg(msg, ' M.h=', REAL_TO_STRING(M.h));
                        msg := MakeMsg(msg, ' M.l=', REAL_TO_STRING(M.l)); 
                        msg := MakeMsg(msg, ' R=',   REAL_TO_STRING(Ri));
                        msg := LogMsg(msg);
                      end_if; 
                      
          end_if;

        else (* не краевые точки *)
          (* --- Расчёт коэффициентов Alfas[i], Betas[i] --- *)
          Alfas[i] := Alfa_i(Ht, M, Alfas[i-1], Ti1, Qi1, Vi1, Ri);
        end_if; (* Обработка краевых условий *)

      end_for; (* прямая прогонка *)

      (* === Обратная прогонка === *)
      for i:=N-1 to 0 by -1 do
        K[2]:=i;
        
        (* --- Расчёт температуры T[N-1]..T[0] --- *)
        xx := Temp_i(Alfas[i], xx);
        
        (* Запись значения xx в сетку, °С (real) -> код (int) *)
        Off := knoff(Sh.Kn[0], Sh.Kn[1], Sh.Kn[2], K[Cx.x], K[Cx.y], K[Cx.z]);
        
        PIT := set_var(its_gr(0), PIT, Off, _var(T2C(xx)));
        
        (*+*) if (K[0]=0 and K[1]=0 and PIT =3) then
                msg := MakeMsg('T[', INT_TO_STRING(i), ']= ', REAL_TO_STRING(xx));
                msg := LogMsg(msg);
              end_if; 
              
      end_for; (* обратная прогонка *)
      
      K[1] := K[1]+1;
    end_while; (* Цикл (1) *)
    K[0] := K[0]+1;
  end_while; (* Цикл (0) *)

  { __exit: }
  IT_PROCESS := iRes;
END_FUNCTION

FUNCTION_BLOCK Process_XYZ
  VAR_EXTERNAL
    rTest : REAL;
    HDR : THead;
    ITS : TItems;
  END_VAR
  VAR_INPUT
    IN : BOOL := TRUE;
    Ix : USINT := 0;
    N : SINT := -1;
  END_VAR
  VAR_OUTPUT
    bRes : BOOL := FALSE;
  END_VAR
  VAR
    iErr : TError := E_SUCCESS;
    i : SINT := 0;
    Ix_local : USINT := 0;
    bRestart : BOOL := true;
    bBreak : BOOL := false;
    It : TIter;
    CDT : DT := DT#2000-01-01-00:00:00;
    PDT : DT := DT#2000-01-01-00:00:00;
    msg : STRING := '';
    rr : REAL := 0.0;
    RTIME : RTC;
    DTIME : TON;
  END_VAR

  IF (IN) THEN                          (* Деблокировка блока          *)
    IF (bReStart) THEN                  (* Инициализация блока         *)
      (* Проверка корректности конфигурации перед стартом *)
      if (Ix<0 or Ix>2) then iErr:=E_AXIS; {goto __error;} end_if;
      if (true) then
        (* Инициализация *)
        msg:=MakeMsg('== PROCESS init ... ');
        i:=0; it:=it_end(-1);
        bRes      := true;               
        bReStart  := false;
        bBreak    := false;
        Ix_local  := Ix;                 (* Направление запоминается    *)
        RTIME(EN  := false);             (* Текущее время -> PDT        *)
        RTIME(EN  := true, PDT := DT#2000-01-01-00:00:00, CDT => CDT);
        DTIME(IN  := false);             (* Рестарт счётчика DTIME      *)
        DTIME(IN  := true, PT := T#24h);
        PDT := CDT;
        (* Заносим время расчёта по направлению Ix в каждый элемент    *)
        it := it_begin(ID2PIT(0));
        while (it.item<>-1) do
          if (it.dir = DIR_UP) then ITS.IT[it.item].PDT[Ix]:=CDT; end_if;
          it := it_next(it);
        end_while;
        msg:=LogMsg(MakeMsg(msg, 'Ok! [time=', DT_TO_STRING(CDT),  '];'));
      end_if;
      RETURN; (* После инициализации - выход из блока *)
    END_IF;

    (* Проверка условий выполнения (нет ли блокировки на уровне модели) *)
    if (not st_is_ready(0)) then {goto __error;} end_if;
    (*bRes := TRUE;*)
    
    (* Проверка вхождения точки в модель *)
    (* TEST *) (*it := it_begin(42);*) 
    if (N<>0 and it.item=-1) then it := it_begin(ID2PIT(0)); end_if;

    (* TEST *) if (Ix_local=0) then msg:=LogMsg(MakeMsg(msg, 'START')); end_if;

    while (not bBreak and it.item<>-1) do
      case (it.dir) of
      DIR_UP:
        (* ВОПРОС: считаемем только конечные элементы? - пока да...  *)
        if (not is_poly(it.item)) then
          (* Крутим таймер - определяем текущее время расчёта *)
          DTIME(); 
          CDT := ULINT_TO_DT(ADD(DT_TO_ULINT(PDT), TIME_TO_ULINT(DTIME.ET)));
          
  (* TEST -------- *)        
  if (
    (it.item>=1 and it.item<=99) 
  ) then 
  (* ------------- *)        
          (* === Расчёт элемента по направлению Ix === *)
          msg:=MakeMsg(msg, 'Process item ID=', ID2Str(IT_ID(it.item)), ' ... '); 
          
          iErr := IT_Process(it.item, Ix_local, CDT);
          bRes := (iErr = E_SUCCESS);
          if (not bRes) then 
            msg:=LogMsg(MakeMsg(msg, 'FAILED!'));
            {goto __error;} 
          else 
            msg:=LogMsg('');
          end_if;
  (* ------------- *)        
  end_if;        
  (* ------------- *)        

        end_if; (* not is_poly(it.item) *)
      end_case; (* it.dir *)

      it := it_next(it);
      (* Проверка на досрочный выход из цикла *)
      if (not bBreak and N<>-1) then
        i:=i+1;
        if (i >= N) then i:=0; bBreak:=true; end_if;
      end_if;
      
    end_while;
    bBreak:=false;
    
    (* TEST *)
    if (Ix_local=0) then msg := LogMsg(MakeMsg(msg, 'END')); end_if; 

    (* Каждый час - рестарт счётчика в защиту от переполнения *)
    if (DTIME.ET > T#1h) then 
      PDT := CDT;
      DTIME(IN:=false);
      DTIME(IN:=true);
    end_if;
    return;

    {{__error:}}
    if (iErr = E_SUCCESS) then iErr := E_PROCESS; end_if;
    bRes := FALSE;
    bReStart := TRUE; (* Посылаем на рестарт *)
    
    (* Протоколирование ошибки *)
    msg:=LogMsg( MakeMsg('== PROCESS ERROR -> will be re-started! [ERR=', 
        Err2Str(iErr), ']'), Warning, iErr);
  ELSE
    bRes := FALSE;
    bReStart := TRUE;
  END_IF; (* IN *)
END_FUNCTION_BLOCK

FUNCTION st_set_ready : BOOL
  VAR_INPUT
    RDY : BOOL := FALSE;
  END_VAR

  {{ return (ST_SET_READY=(__GET_GLOBAL_STAT()->RDY=RDY)); }}
END_FUNCTION

FUNCTION is_cyl : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  IS_CYL := (sh_get_ax(get_sh(PIT)) <> 0);
END_FUNCTION

FUNCTION Do_CheckValid : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    PIT2 : TPos8 := 0;
    bRes : BOOL := false;
    It : TIter;
    stack : ARRAY [0..99] OF TPos8;
    kids : ARRAY [0..15] OF TPos8;
    n : SINT := 0;
    m : SINT := 0;
    im : SINT := 0;
    j : SINT := 0;
    Chk : TDot;
    bC : BOOL := false;
    Sh : TShape;
    p0 : TPoint;
    p1 : TPoint;
    p2 : TPoint;
    msg : STRING := '';
  END_VAR

  Do_CheckValid := st_check(false);
  if (not Do_CheckValid) then return; end_if;

  (* Обход дерева элементов *)
  it := it_begin(ID2PIT(0));
  while (it.item<>-1) do

    case (it.dir) of
    DIR_DOWN:
      (* Запись родителя в стек *)
      if (n > 99) then msg:='CheckValid: Stack overflow'; {goto __error} end_if;
      stack[n] := it.item;
      n:=n+1;
    DIR_UP:
      (* Извлечение из стека *)
      if (is_poly(it.item)) then  (* элемент - родитель *)
      
        (* Выборка потомства из стека *)
        m:=0;
        while (stack[n-1]<>it.item) do
          n:=n-1;
          if (m > 15) then msg:='CheckValid: Kids overflow'; {goto __error} end_if;
          kids[m]:=stack[n];
          m:=m+1;
        end_while;
        
        (* Анализ потомства *)
        for im:=0 to m-1 do
          PIT:=kids[im]; (* Позиция ребёнка *)
          msg:=MakeMsg('CheckValid: P=', ID2Str(IT_ID(IT.ITEM)), ', C=', ID2Str(IT_ID(PIT)));
          
          (* === Проверка 1: Если родитель в цилиндрической СК, то дети - тоже  *)
          if (is_cyl(IT.ITEM) and not is_cyl(PIT)) then
            msg := MakeMsg(msg, ', Er=CS does not match');
            { goto __exit;  }
          end_if;
          
          (* === Проверка 2: Размер не может быть нулевым  *)
          Sh := get_sh(PIT);
          P0 := sh.p0; (* Начало отсчёта  (абс) *)
          P1 := sh.pl; (* Начало элемента (лок) *)
          P2 := sh.lx; (* Размер элемента (лок) *)
          
          msg := MakeMsg(msg, ' LWH=(',REAL_TO_STRING(P2[0]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P2[1]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P2[2]), ');' );
          
          if (p2[0]<=0.1 or p2[1]<=0.1 or p2[2]<=0.1) then 
            msg := MakeMsg(msg, ', Er=LWH must be nonzero'); 
            {goto __exit} 
          end_if;

          (* Преобразуем точки p1, p2 в абсолютные координаты *)
          p2 := _point((p1[0]+p2[0]), (p1[1]+p2[1]), (p1[2]+p2[2]));
          
          p1 := Sh_Loc2Abs(Sh, p1[0], p1[1], p1[2]);
          p2 := Sh_Loc2Abs(Sh, p2[0], p2[1], p2[2]);
          
          msg := MakeMsg(msg, ' P1=(', REAL_TO_STRING(P1[0]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P1[1]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P1[2]), ');' );
          msg := MakeMsg(msg, ' P2=(', REAL_TO_STRING(P2[0]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P2[1]), ','  );
          msg := MakeMsg(msg, '',      REAL_TO_STRING(P2[2]), ');' );
                          
          (* === Проверка 3: Точки p1, p2 элемента не могут быть вне родителя   *)
          Chk := Sh_Point2Dot(get_sh(IT.ITEM), p1[0], p1[1], p1[2]);
          if (Chk.V <= 0) then 
            msg := MakeMsg(msg, ', Er=P1 out of parent' ); 
            {goto __exit} 
          end_if;
          Chk := Sh_Point2Dot(get_sh(IT.ITEM), p2[0], p2[1], p2[2]);
          if (Chk.V <= 0) then 
            msg := MakeMsg(msg, ', Er=P2 out of parent' ); 
            {goto __exit} 
          end_if;

          (* === Проверка 4,5: *)
          if (not is_poly(PIT)) then
            for j:=0 to m-1 do
              (* Проверка 4: p1,p2 одного элемента не могут быть внутри другого *)
              if (j<>im) then
                PIT2:=kids[j];
                Chk := Sh_Point2Dot(get_sh(PIT2), p1[0], p1[1], p1[2]);
                if (Chk.V = 16#01 or Chk.V = 16#ff) then 
                  msg := MakeMsg(msg, ', Err: P1 of ', SINT_TO_STRING(PIT));
                  msg := MakeMsg(msg, ' is into ',   SINT_TO_STRING(PIT2));
                  {goto __exit} 
                end_if;
                Chk := Sh_Point2Dot(get_sh(PIT2), p2[0], p2[1], p2[2]);
                if (Chk.V = 16#01 or Chk.V = 16#ff) then 
                  msg := MakeMsg(msg, ', Err: P2 of ', SINT_TO_STRING(PIT));
                  msg := MakeMsg(msg, ' is into ',   SINT_TO_STRING(PIT2));
                  {goto __exit} 
                end_if;
              end_if;
              
              (* Проверка 5: *)
              (* --- *)
              
            end_for;
          end_if;
          
          msg:=LogMsg(msg);      
        end_for;
        
      else (* конечный элемент *)
        (* Запись конечного элемента в стек *)
        if (n > 99) then msg := 'CheckValid: Stack overflow'; {goto __error} end_if;
        stack[n] := it.item;
        n:=n+1;
      end_if;
      
    end_case;
    
    it := it_next(it);
  end_while;

  bRes:=true;

  { __exit: }
  msg:=LogMsg(msg);
  Do_CheckValid := bRes;
  return;

  { __error: }
  Do_CheckValid := st_set_stat(E_CHECKVALID, IT_ID(it.item), msg);
END_FUNCTION

FUNCTION Do_LinkItems : INT
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
    B : BYTE := 0;
    I : INT := 0;
    J : INT := 0;
    K : INT := 0;
    nPos : SINT := 0;
    nAir : INT := 0;
    nItems : INT := 0;
    Sh : TShape;
    Dot : TDot;
    Pt : TPoint;
  END_VAR

  Do_LinkItems := (-1);
  if (not st_check(false)) then return; end_if;

  (* Обход дерева элементов *)
  it := it_begin(it_pos(PIT));
  while (it.item <> -1) do
    case (it.dir) of
    DIR_UP:
      B     := 0; 
      nAir  := 0;
      Sh := get_sh(it.item);
      
      (* Рассчитываем точки по граням X=(Х0,Kn[0]-1) *)
      for I:=0 to Sh.Kn[0]-1 do
        for J:=0 to Sh.Kn[1]-1 do
          for K:=0 to Sh.Kn[2]-1 do

            if (not is_poly(it.item)) then  
              (* линкуем узлы конечных элементов *)
            
              if (I=0 or I=Sh.Kn[0]-1) then  (* по координате X (Ix=1) *)
                Dot := link_var(its_gr(0), it.item, Sh, I, J, K, 1, it.item);
                if (Dot.v = -1) then   (* Воздух *)
                  if (I=0) then B:=(B or shl(16#01, 1)); else B:=(B or shl(16#01, 2)); end_if;
                end_if;
              end_if;
              
              if (J=0 or J=Sh.Kn[1]-1) then  (* по координате Y  (Ix=2) *)
                Dot := link_var(its_gr(0), it.item, Sh, I, J, K, 2, it.item);
                if (Dot.v = -1) then  (* Воздух *)
                  if (J=0) then B:=(B or shl(16#01, 3)); else B:=(B or shl(16#01, 4)); end_if;
                end_if;
              end_if;
              
              if (K=0 or K=Sh.Kn[2]-1) then  (* по координате Z  (Ix=3) *)
                Dot := link_var(its_gr(0), it.item, Sh, I, J, K, 3, it.item);
                if (Dot.v = -1) then  (* Воздух *)
                  if (K=0) then B:=(B or shl(16#01, 5)); else B:=(B or shl(16#01, 6)); end_if;
                end_if;
              end_if;
              
            else    (* линкуем сетку составного элемента (Ix=0, default) *)
            
              Dot := link_var(its_gr(0), it.item, Sh, I, J, K);
              
            end_if;
            
          end_for;
        end_for;
      end_for;
      
      (* Суммируем количество граней, контактирующих с воздухом *)
      for i:=1 to 6 do
        if ((B and shl(16#01, i)) <> 0) then nAir:=nAir+1; end_if;
      end_for;
        
      (* Подсчёт элеметов, контактирующих с "воздухом" *)
      if (nAir > 0) then nItems := nItems+1; end_if;
      
    end_case;
    it := it_next(it);
  end_while;

  Do_LinkItems := (nItems);
END_FUNCTION

FUNCTION st_set_debug : BOOL
  VAR_INPUT
    DBG : BOOL := FALSE;
  END_VAR

  {{ return (ST_SET_DEBUG=(__GET_GLOBAL_STAT()->DBG=DBG)); }}
END_FUNCTION

PROGRAM P_CONF
  VAR_EXTERNAL
    STAT : TStat;
    f_Conf : BOOL;
    HDR : THead;
    STS : TSets;
    ITS : TItems;
  END_VAR
  VAR
    msg : STRING;
    _GetHead : GetHead;
    _GetMat : GetMat;
    _GetVal : GetVal;
    _GetProf : GetProf;
    _ReadItem : ReadItem;
    _Sort_IDS : Sort_IDS;
    _Process_X : Process_XYZ;
  END_VAR

  (* Локальные переменные *)
  VAR
    i,j,k,l : SINT;      (* Индексы в массивах              *)
    iLev    : SINT;      (* Уровень элемента                *)
    pit,idx : TPos8;     (* Индексы элементов               *)
    iPar    : TPos8;     (* Индекс родителя                 *)
    iPrev   : TPos8;     (* Индекс предыдущего элемента     *)
    nRes    : TError;    (* Код результата выполнения       *)
    iRes    : INT;       (* Возвращаемое значение           *)
    it      : TITER;     (* Итератор для обхода дерева      *)
    btRes   : BYTE;      (* Результат проверки точки модели *)
    bRes    : BOOL;
    rRes    : REAL;
    ii      : DINT;
    sibt    : P_SIBT;
  END_VAR

  (* Установка начальных значений *)
  {{
    // Инициализация фиктивного элемента
    //TITEM *pItem0 = __GET_GLOBAL_DUMMY();
    //memset(pItem0,0x00,sizeof(TITEM));
    //pItem0->ID = 0xffff;
    
    // Инициализация состояния ресурса
    TSTAT *pStat = __GET_GLOBAL_STAT();
    *pStat = (TSTAT) {FALSE, TRUE, TERROR__E_SUCCESS, 0, __INIT_STRING};
  }}

  nRes := E_SUCCESS;          (* Установка кода результата    *)
  bRes := st_set_debug(TRUE); (* Установка флага отладки      *) 

  msg  := LogMsg('== CONFIG ...');

  (* === Чтение и валидация заголовка === *)
  _GetHead(HEAD => HDR);

  msg := MakeMsg(' - Read header ... (');
  msg := MakeMsg(msg, SINT_TO_STRING(HDR.Ni), ', ');
  msg := MakeMsg(msg, SINT_TO_STRING(HDR.Nm), ', ');
  msg := MakeMsg(msg, SINT_TO_STRING(HDR.Nv), ', ');
  msg := MakeMsg(msg, SINT_TO_STRING(HDR.Np), ')');

  (* Валидация заголовка *)
  if (HDR.Ni= 0 or HDR.Ni>100) then nRes:=E_HEAD; {goto __exit} end_if;
  if (HDR.Nm= 0 or HDR.Nm>12)  then nRes:=E_HEAD; {goto __exit} end_if;
  if (HDR.Nv< 0 or HDR.Nv>25)  then nRes:=E_HEAD; {goto __exit} end_if;
  if (HDR.Np< 0 or HDR.Np>30)  then nRes:=E_HEAD; {goto __exit} end_if;
  msg:=LogMsg(MakeMsg(msg, ';'));

  (* Проверка периодов расчёта элемента *)
  if (HDR.TR[0] = T#0s) then HDR.TR[0]:=T#15s; end_if;
  if (HDR.TR[1] = T#0s) then HDR.TR[1]:=T#30s; end_if;
  if (HDR.TR[2] = T#0s) then HDR.TR[2]:=T#45s; end_if;
  if (HDR.TR[3] = T#0s) then HDR.TR[3]:=T#60s; end_if;

  (* === Чтение и валидация массива материалов === *)
  msg:=LogMsg('Read materials ... ');
  FOR i := 0 TO HDR.Nm-1 DO 
    _GetMat(I:=i, MAT => STS.Mt[i]);
    msg := MakeMsg(' - Get material [', SINT_TO_STRING(i), '] ... (');
    msg := MakeMsg(msg, REAL_TO_STRING(STS.Mt[i].KT), ', ');
    msg := MakeMsg(msg, REAL_TO_STRING(STS.Mt[i].CP), ', ');
    msg := MakeMsg(msg, REAL_TO_STRING(STS.Mt[i].PL), ', ');
    msg := MakeMsg(msg, REAL_TO_STRING(STS.Mt[i].MD), ')');
    (* Валидация *)
    if (STS.Mt[i].KT < 1.0E-8) then nRes:=E_MATER; {goto __exit} end_if;
    if (STS.Mt[i].CP < 1.0E-8) then nRes:=E_MATER; {goto __exit} end_if;
    if (STS.Mt[i].PL < 1.0E-8) then nRes:=E_MATER; {goto __exit} end_if;
    msg:=LogMsg(MakeMsg(msg, ';'));
  END_FOR;

  (* === Чтение и валидация профилей === *)
  msg:=LogMsg('Read profiles ... ');
  FOR i := 0 TO HDR.Np-1 DO 
    _GetProf(I:=i, PROF => STS.Pr[i]);
    msg := MakeMsg(' - Get profile [', SINT_TO_STRING(i), '] ...');
    FOR j := 0 TO 11 DO
      msg := MakeMsg(msg, ' (', SINT_TO_STRING(STS.Pr[i][j].A), ',');
      msg := MakeMsg(msg,       SINT_TO_STRING(STS.Pr[i][j].B), ')');
      (* Валидация *)
      if (STS.Pr[i][j].A <    0 or STS.Pr[i][j].A > 100) then nRes:=E_PROFILE; {goto __exit} end_if;
      if (STS.Pr[i][j].B < -100 or STS.Pr[i][j].B > 100) then nRes:=E_PROFILE; {goto __exit} end_if;
    END_FOR;
    msg:=LogMsg(MakeMsg(msg, ';'));
  END_FOR;

  (* === Чтение и валидация связанных величин === *)
  msg:=LogMsg('Read values ... ');
  FOR i := 0 TO HDR.Nv-1 DO 
    _GetVal(I:=i, VAL => STS.Vl[i]);
    msg := MakeMsg(' - Get value [', SINT_TO_STRING(i), '] ...');
    if (STS.Vl[i].Iv >=USINT_TO_INT(30) and STS.Vl[i].Iv <> -1) then nRes:=E_VALUE; {goto __exit} end_if;
    FOR j := 0 TO 2 DO
      msg := MakeMsg(msg, ' (', SINT_TO_STRING(STS.Vl[i].Vi[j].A), ',');
      msg := MakeMsg(msg,       SINT_TO_STRING(STS.Vl[i].Vi[j].B), ')');
      (* Валидация *)
      if (STS.Vl[i].Vi[j].A < 0 or STS.Vl[i].Vi[j].A >     100) then nRes:=E_VALUE; {goto __exit} end_if;
      if (STS.Vl[i].Vi[j].B < 0 or STS.Vl[i].Vi[j].B >= HDR.Np) then nRes:=E_VALUE; {goto __exit} end_if;
    END_FOR;
    msg:=LogMsg(MakeMsg(msg, ';'));
  END_FOR;

  (* === Чтение массива элементов === *)
  msg:=LogMsg('Read items ... '); 
  FOR pit := 0 TO HDR.Ni-1 DO 
    _ReadItem(PIT := pit, iRes => nRes); 
    
    (* Протоколирование *)
    if (len(msg)=0) then msg := MakeMsg(' - Updated items: '); end_if;
    msg := MakeMsg(msg, ' [', ID2Str(IT_ID(pit)), ',');
    msg := MakeMsg(msg,       SINT_TO_STRING(pit), ']');
    if (mod((pit+1),5)=0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;
    if (nRes <> E_SUCCESS) then {goto __exit} end_if;
    
    (* Регистрация элемента в массиве IDs (UI->SI)*)
    ITS.Pr[pit].A := ITS.It[pit].ID; 
    ITS.Pr[pit].B := (pit);
  END_FOR; 
  if (len(msg)>0) then msg:=LogMsg(MakeMsg(msg, ';')); end_if;

  (* === Упорядочивание массива по IDs === *)
  msg:=LogMsg(MakeMsg('Sort items ... '));
  _Sort_IDS(iBegin:=0, iEnd:=HDR.Ni-1, iRes => nRes); 
  if (nRes <> E_SUCCESS) then {goto __exit} end_if;

  (* === Формирование иерархической структуры === *)
  if (ITS.Pr[0].A<>0) then 
    nRes  := E_ROOT; 
    {goto __exit} 
  end_if;

  (* ROOT settings *)
  iPrev := ITS.Pr[0].B;   
  iPar  := iPrev;
  iLev  := -1;
  ITS.It[iPar].Par := -1; 

  (* Построение дерева *)
  FOR idx := 1 TO HDR.Ni-1 DO
    pit := ITS.Pr[idx].B;   (* Индекс элемента  *)
    l := IT_Lev(pit);       (* Уровень элемента *)
    if (l < 0) then nRes:=E_STRUCT; {goto __exit} end_if;

    (* Определяем индекс родителя iPar *)  
    if (l <> iLev) then     (* Смена уровня вложенности - смена родителя *)
      (* Нахождение родителя для текущего элемента *)
      if (l > iLev) then    (* Спускаемся на уровень вниз  *)
        (* Возможен спуск только на одну ступень (!) *)
        if (l-iLev <> 1) then nRes:=E_STRUCT; {goto __exit} end_if;
        (* Предыдущий элемент должен быть родительским *)
        (*if (not ITS.IT[iPrev].bP) then nRes:=E_STRUCT; {goto __exit} end_if;*)
        iPar := iPrev;      (* Родитель - предыдущий элемент *)
      else                  (* Поднимаемся вверх *)
        (* Вычисление родителя по ступенькам вверх от предыдущего *)
        iPar := iPrev;
        for k := l to iLev do 
          if (iPar<>-1) then iPar := ITS.IT[iPar].Par; end_if;
        end_for;
      end_if;
    else (* Тот же уровень вложенности - родитель не меняется *)
      iPar := iPar;
    end_if;
    (* Родительский элемент должен существовать (!) *)
    if (iPar=-1) then nRes:=E_STRUCT; {goto __exit} end_if;
    
    ITS.It[pit].Par := iPar;      (* Сохраняем индекс родителя              *)
    k := ITS.It[iPar].Num;        (* Читается количество детей              *)
    ITS.It[iPar].Kids[k] := pit;  (* Сохраняем элемент в массиве детей      *)
    ITS.It[iPar].Num := k+1;      (* Увеличиваем счётчик детей              *) 
    iLev  := l;                   (* сохраняем уровень предыдущего элемента *)
    iPrev := pit;                 (* сохраняем индекс  предыдущего элемента *)
  END_FOR;

  (* === Валидация (подготовка модели) === *)
  bRes:=Do_Validate(ID2PIT(0));
  msg:=LogMsg(MakeMsg('Validate model ... ', BOOL_TO_STRING(bRes)));
  msg:=LogMsg(STAT.STR);

  (* === Проверка согласованности модели === *)
  bRes:=Do_CheckValid(ID2PIT(0));
  msg:=LogMsg(MakeMsg('Model CheckValid ... ', BOOL_TO_STRING(bRes)));
  msg:=LogMsg(MakeMsg(STAT.STR));

  (* === Линкование элементов === *)
  msg:=LogMsg('Model LinkItems ... ');
  iRes:=Do_LinkItems(ID2PIT(0));

  if (iRes<>-1) then
    msg:=LogMsg(MakeMsg('Model LinkItems ... OK [items -> Air = ', INT_TO_STRING(iRes), '];'));
  else
    msg:=LogMsg('Model LinkItems ... FAILED');
  end_if;

  bRes := st_set_ready(TRUE); (* Установка флага деблокировки *) 

  {__exit:}
  (* === Протоколирование результата === *)
  if (nRes <> E_SUCCESS) then msg:=LogMsg(msg); end_if;
  msg:=LogMsg(MakeMsg('== CONFIG -> ', Err2Str(nRes)), Debug, nRes);

  f_Conf := FALSE;            (* Сброс флага конфигурирования *)
END_PROGRAM

FUNCTION_BLOCK GetPhaseO
  VAR_EXTERNAL
    MD466 : UDINT;
    MD467 : UDINT;
    MD468 : UDINT;
    MD469 : UDINT;
    MD470 : UDINT;
    MD471 : UDINT;
    MD472 : UDINT;
    MD473 : UDINT;
    MD474 : UDINT;
    MD475 : UDINT;
    MD476 : UDINT;
    MD477 : UDINT;
    MD478 : UDINT;
    MD479 : UDINT;
    MD480 : UDINT;
    MD481 : UDINT;
    MD482 : UDINT;
    MD483 : UDINT;
    MD484 : UDINT;
    MD485 : UDINT;
    MD486 : UDINT;
    MD487 : UDINT;
    MD488 : UDINT;
    MD489 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    PHASE : TPhaseO;
  END_VAR

  CASE i OF
  0 : PHASE := m_phase_out(MD466,MD467,MD468,MD469,MD470,MD471,MD472,MD473);
  1 : PHASE := m_phase_out(MD474,MD475,MD476,MD477,MD478,MD479,MD480,MD481);
  2 : PHASE := m_phase_out(MD482,MD483,MD484,MD485,MD486,MD487,MD488,MD489);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION_BLOCK Buffer32
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
    MD8 : UDINT;
    MD9 : UDINT;
    MD10 : UDINT;
    MD11 : UDINT;
    MD12 : UDINT;
    MD13 : UDINT;
    MD14 : UDINT;
    MD15 : UDINT;
    MD16 : UDINT;
    MD17 : UDINT;
    MD18 : UDINT;
    MD19 : UDINT;
    MD20 : UDINT;
    MD21 : UDINT;
    MD22 : UDINT;
    MD23 : UDINT;
    MD24 : UDINT;
    MD25 : UDINT;
    MD26 : UDINT;
    MD27 : UDINT;
    MD28 : UDINT;
    MD29 : UDINT;
    MD30 : UDINT;
    MD31 : UDINT;
  END_VAR
  VAR_OUTPUT
    BUF : ARRAY [0..31] OF REAL;
  END_VAR

  BUF[0] :=UDI2REAL(MD0);
  BUF[1] :=UDI2REAL(MD1);
  BUF[2] :=UDI2REAL(MD2);
  BUF[3] :=UDI2REAL(MD3);
  BUF[4] :=UDI2REAL(MD4);
  BUF[5] :=UDI2REAL(MD5);
  BUF[6] :=UDI2REAL(MD6);
  BUF[7] :=UDI2REAL(MD7);
  BUF[8] :=UDI2REAL(MD8);
  BUF[9] :=UDI2REAL(MD9);
  BUF[10]:=UDI2REAL(MD10);
  BUF[11]:=UDI2REAL(MD11);
  BUF[12]:=UDI2REAL(MD12);
  BUF[13]:=UDI2REAL(MD13);
  BUF[14]:=UDI2REAL(MD14);
  BUF[15]:=UDI2REAL(MD15);
  BUF[16]:=UDI2REAL(MD16);
  BUF[17]:=UDI2REAL(MD17);
  BUF[18]:=UDI2REAL(MD18);
  BUF[19]:=UDI2REAL(MD19);
  BUF[20]:=UDI2REAL(MD20);
  BUF[21]:=UDI2REAL(MD21);
  BUF[22]:=UDI2REAL(MD22);
  BUF[23]:=UDI2REAL(MD23);
  BUF[24]:=UDI2REAL(MD24);
  BUF[25]:=UDI2REAL(MD25);
  BUF[26]:=UDI2REAL(MD26);
  BUF[27]:=UDI2REAL(MD27);
  BUF[28]:=UDI2REAL(MD28);
  BUF[29]:=UDI2REAL(MD29);
  BUF[30]:=UDI2REAL(MD30);
  BUF[31]:=UDI2REAL(MD31);
END_FUNCTION_BLOCK

FUNCTION_BLOCK GetVarI
  VAR_EXTERNAL
    MD430 : UDINT;
    MD431 : UDINT;
    MD432 : UDINT;
    MD433 : UDINT;
    MD434 : UDINT;
    MD435 : UDINT;
  END_VAR
  VAR_OUTPUT
    VarI : TVarI;
  END_VAR

  VarI := m_var_in(MD430,MD431,MD432,MD433,MD434,MD435);
END_FUNCTION_BLOCK

FUNCTION_BLOCK GetVarO
  VAR_EXTERNAL
    MD460 : UDINT;
    MD461 : UDINT;
    MD462 : UDINT;
    MD463 : UDINT;
    MD464 : UDINT;
    MD465 : UDINT;
  END_VAR
  VAR_OUTPUT
    VarO : TVarO;
  END_VAR

  VarO := m_var_out(MD460,MD461,MD462,MD463,MD464,MD465);
END_FUNCTION_BLOCK

FUNCTION m_phase_in : TPhaseI
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
  END_VAR

  m_phase_in.Ic   := UDINT_TO_REAL(MD0);
  m_phase_in.Tin  := UDINT_TO_REAL(MD1);
  m_phase_in.Tout := UDINT_TO_REAL(MD2);
  m_phase_in.RN   := UDINT_TO_DWORD(MD3);

  m_phase_in.RD[0].A := UINT_TO_SINT(UDINT_TO_UINT(MD4/65536)/256);
  m_phase_in.RD[0].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD4/65536),256));
  m_phase_in.RD[1].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD4,65536))/256);
  m_phase_in.RD[1].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD4,65536)),256));

  m_phase_in.RD[2].A := UINT_TO_SINT(UDINT_TO_UINT(MD5/65536)/256);
  m_phase_in.RD[2].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD5/65536),256));
  m_phase_in.RD[3].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD5,65536))/256);
  m_phase_in.RD[3].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD5,65536)),256));

  m_phase_in.RD[4].A := UINT_TO_SINT(UDINT_TO_UINT(MD6/65536)/256);
  m_phase_in.RD[4].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD6/65536),256));
  m_phase_in.RD[5].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD6,65536))/256);
  m_phase_in.RD[5].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD6,65536)),256));

  m_phase_in.RD[6].A := UINT_TO_SINT(UDINT_TO_UINT(MD7/65536)/256);
  m_phase_in.RD[6].B := UINT_TO_SINT(mod(UDINT_TO_UINT(MD7/65536),256));
  m_phase_in.RD[7].A := UINT_TO_SINT(UDINT_TO_UINT(mod(MD7,65536))/256);
  m_phase_in.RD[7].B := UINT_TO_SINT(mod(UDINT_TO_UINT(mod(MD7,65536)),256));
END_FUNCTION

FUNCTION m_conf : TConf
  VAR_INPUT
    MD0 : UDINT;
    MD1 : UDINT;
  END_VAR

  m_conf.Nm := UDINT_TO_UINT(MD0/65536);
  m_conf.Nr := UDINT_TO_UINT(mod(MD0,65536));
  m_conf.Tc := UDINT_TO_TIME(MD1);
END_FUNCTION

FUNCTION Do_PreProc : BOOL
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    It : TIter;
  END_VAR

  Do_PreProc := st_check(false);
  if (not Do_PreProc) then return; end_if;

  (* Обход дерева элементов *)
  Do_PreProc := true;
  it := it_begin(it_pos(PIT));
  while (it.item <>-1) do
    case (it.dir) of
    DIR_UP:
      { }
    end_case;
    it := it_next(it);
  end_while;

  { __exit: }
  return;

  { __error: } 
  Do_PreProc := st_set_stat(E_PREPROC, it_id(it.item));
END_FUNCTION

PROGRAM P_MOD1
  VAR_EXTERNAL
    STAT : TStat;
    F_Res : BOOL;
  END_VAR
  VAR
    CDT : DT;
    bRes : BOOL;
    Process_X1 : Process_XYZ;
    Process_X2 : Process_XYZ;
    Process_X0 : Process_XYZ;
    _TMP_NOT33_OUT : BOOL;
    _TMP_AND32_OUT : BOOL;
    _TMP_Do_PreProc19_ENO : BOOL;
    _TMP_Do_PreProc19_OUT : BOOL;
    _TMP_Do_PostProc37_ENO : BOOL;
    _TMP_Do_PostProc37_OUT : BOOL;
  END_VAR

  _TMP_NOT33_OUT := NOT(F_Res);
  _TMP_AND32_OUT := AND(STAT.RDY, _TMP_NOT33_OUT);
  _TMP_Do_PreProc19_OUT := Do_PreProc(EN := _TMP_AND32_OUT, PIT := 0, ENO => _TMP_Do_PreProc19_ENO);
  Process_X0(IN := _TMP_Do_PreProc19_ENO, Ix := 0, N := -1);
  Process_X1(IN := Process_X0.bRes, Ix := 1, N := -1);
  Process_X2(IN := Process_X1.bRes, Ix := 2, N := -1);
  _TMP_Do_PostProc37_OUT := Do_PostProc(EN := Process_X2.bRes, PIT := 0, ENO => _TMP_Do_PostProc37_ENO);
  IF _TMP_Do_PostProc37_ENO THEN
      STAT.RDY := _TMP_Do_PostProc37_ENO;
  END_IF;
  F_Res := STAT.RDY;
END_PROGRAM

PROGRAM P_MOD2
  VAR_EXTERNAL
    STS : TSets;
    MD460 : UDINT;
    MD461 : UDINT;
    MD462 : UDINT;
    MD463 : UDINT;
    MD464 : UDINT;
    MD465 : UDINT;
    MD466 : UDINT;
    MD467 : UDINT;
    MD468 : UDINT;
    MD469 : UDINT;
    MD470 : UDINT;
    MD471 : UDINT;
    MD472 : UDINT;
    MD473 : UDINT;
    MD474 : UDINT;
    MD475 : UDINT;
    MD476 : UDINT;
    MD477 : UDINT;
    MD478 : UDINT;
    MD479 : UDINT;
    MD480 : UDINT;
    MD481 : UDINT;
    MD482 : UDINT;
    MD483 : UDINT;
    MD484 : UDINT;
    MD485 : UDINT;
    MD486 : UDINT;
    MD487 : UDINT;
    MD488 : UDINT;
    MD489 : UDINT;
  END_VAR

  MD460 := 0;
END_PROGRAM

FUNCTION_BLOCK GetPhaseI
  VAR_EXTERNAL
    MD436 : UDINT;
    MD437 : UDINT;
    MD438 : UDINT;
    MD439 : UDINT;
    MD440 : UDINT;
    MD441 : UDINT;
    MD442 : UDINT;
    MD443 : UDINT;
    MD444 : UDINT;
    MD445 : UDINT;
    MD446 : UDINT;
    MD447 : UDINT;
    MD448 : UDINT;
    MD449 : UDINT;
    MD450 : UDINT;
    MD451 : UDINT;
    MD452 : UDINT;
    MD453 : UDINT;
    MD454 : UDINT;
    MD455 : UDINT;
    MD456 : UDINT;
    MD457 : UDINT;
    MD458 : UDINT;
    MD459 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    PHASE : TPhaseI;
  END_VAR

  CASE i OF
  0 : PHASE := m_phase_in(MD436,MD437,MD438,MD439,MD440,MD441,MD442,MD443);
  1 : PHASE := m_phase_in(MD444,MD445,MD446,MD447,MD448,MD449,MD450,MD451);
  2 : PHASE := m_phase_in(MD452,MD453,MD454,MD455,MD456,MD457,MD458,MD459);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION_BLOCK SetVarO
  VAR_EXTERNAL
    MD460 : UDINT;
    MD461 : UDINT;
    MD462 : UDINT;
    MD463 : UDINT;
    MD464 : UDINT;
    MD465 : UDINT;
  END_VAR
  VAR_INPUT
    VarO : TVarO;
  END_VAR
  VAR
    DIST : DistVarO;
  END_VAR

  DIST(VarO:=VarO,MD0=>MD460,MD1=>MD461,MD2=>MD462,MD3=>MD463,MD4=>MD464,MD5=>MD465);
END_FUNCTION_BLOCK

FUNCTION_BLOCK DistPhaseO
  VAR_OUTPUT
    MD0 : UDINT;
    MD1 : UDINT;
    MD2 : UDINT;
    MD3 : UDINT;
    MD4 : UDINT;
    MD5 : UDINT;
    MD6 : UDINT;
    MD7 : UDINT;
  END_VAR
  VAR_INPUT
    PhaseO : TPhaseO;
  END_VAR

  MD0 := REAL_TO_UDINT(PhaseO.Q0);
  MD1 := REAL_TO_UDINT(PhaseO.Q1);  
  MD2 := REAL_TO_UDINT(PhaseO.Q2);
  MD3 := REAL_TO_UDINT(PhaseO.Tin); 
  MD4 := REAL_TO_UDINT(PhaseO.Tout);
  MD5 := REAL_TO_UDINT(PhaseO.Qm);
  MD6 := REAL_TO_UDINT(PhaseO.Se);  
  MD7 := REAL_TO_UDINT(PhaseO.Ve);
END_FUNCTION_BLOCK

FUNCTION_BLOCK SetPhaseO
  VAR_EXTERNAL
    MD466 : UDINT;
    MD467 : UDINT;
    MD468 : UDINT;
    MD469 : UDINT;
    MD470 : UDINT;
    MD471 : UDINT;
    MD472 : UDINT;
    MD473 : UDINT;
    MD474 : UDINT;
    MD475 : UDINT;
    MD476 : UDINT;
    MD477 : UDINT;
    MD478 : UDINT;
    MD479 : UDINT;
    MD480 : UDINT;
    MD481 : UDINT;
    MD482 : UDINT;
    MD483 : UDINT;
    MD484 : UDINT;
    MD485 : UDINT;
    MD486 : UDINT;
    MD487 : UDINT;
    MD488 : UDINT;
    MD489 : UDINT;
  END_VAR
  VAR_INPUT
    I : UINT := 0;
    PHASE : TPhaseO;
  END_VAR
  VAR
    DIST : DistPhaseO;
  END_VAR

  CASE i OF
  0: DIST(PhaseO:=PHASE,MD0=>MD466,MD1=>MD467,MD2=>MD468,MD3=>MD469,MD4=>MD470,MD5=>MD471,MD6=>MD472,MD7=>MD473);
  1: DIST(PhaseO:=PHASE,MD0=>MD474,MD1=>MD475,MD2=>MD476,MD3=>MD477,MD4=>MD478,MD5=>MD479,MD6=>MD480,MD7=>MD481);
  2: DIST(PhaseO:=PHASE,MD0=>MD482,MD1=>MD483,MD2=>MD484,MD3=>MD485,MD4=>MD486,MD5=>MD487,MD6=>MD488,MD7=>MD489);
  END_CASE;
END_FUNCTION_BLOCK

PROGRAM P_EVAL
  VAR
    LocalVar0 : DINT;
  END_VAR

  LocalVar0:=0;
END_PROGRAM

FUNCTION_BLOCK SetRes
  VAR_EXTERNAL
    MD490 : UDINT;
    MD491 : UDINT;
    MD492 : UDINT;
    MD493 : UDINT;
    MD494 : UDINT;
    MD495 : UDINT;
    MD496 : UDINT;
    MD497 : UDINT;
    MD498 : UDINT;
    MD499 : UDINT;
  END_VAR
  VAR_INPUT
    RES : TRes;
  END_VAR
  VAR
    DIST : DistRes;
  END_VAR

  DIST(RES:=RES,MD0=>MD490,MD1=>MD491,MD2=>MD492,MD3=>MD493,MD4=>MD494,
                MD5=>MD495,MD6=>MD496,MD7=>MD497,MD8=>MD498,MD9=>MD499);
END_FUNCTION_BLOCK

FUNCTION_BLOCK GetRad
  VAR_EXTERNAL
    MD302 : UDINT;
    MD303 : UDINT;
    MD304 : UDINT;
    MD305 : UDINT;
    MD306 : UDINT;
    MD307 : UDINT;
    MD308 : UDINT;
    MD309 : UDINT;
    MD310 : UDINT;
    MD311 : UDINT;
    MD312 : UDINT;
    MD313 : UDINT;
    MD314 : UDINT;
    MD315 : UDINT;
    MD316 : UDINT;
    MD317 : UDINT;
    MD318 : UDINT;
    MD319 : UDINT;
    MD320 : UDINT;
    MD321 : UDINT;
    MD322 : UDINT;
    MD323 : UDINT;
    MD324 : UDINT;
    MD325 : UDINT;
    MD326 : UDINT;
    MD327 : UDINT;
    MD328 : UDINT;
    MD329 : UDINT;
    MD330 : UDINT;
    MD331 : UDINT;
    MD332 : UDINT;
    MD333 : UDINT;
    MD334 : UDINT;
    MD335 : UDINT;
    MD336 : UDINT;
    MD337 : UDINT;
    MD338 : UDINT;
    MD339 : UDINT;
    MD340 : UDINT;
    MD341 : UDINT;
    MD342 : UDINT;
    MD343 : UDINT;
    MD344 : UDINT;
    MD345 : UDINT;
    MD346 : UDINT;
    MD347 : UDINT;
    MD348 : UDINT;
    MD349 : UDINT;
    MD350 : UDINT;
    MD351 : UDINT;
    MD352 : UDINT;
    MD353 : UDINT;
    MD354 : UDINT;
    MD355 : UDINT;
    MD356 : UDINT;
    MD357 : UDINT;
    MD358 : UDINT;
    MD359 : UDINT;
    MD360 : UDINT;
    MD361 : UDINT;
    MD362 : UDINT;
    MD363 : UDINT;
    MD364 : UDINT;
    MD365 : UDINT;
    MD366 : UDINT;
    MD367 : UDINT;
    MD368 : UDINT;
    MD369 : UDINT;
    MD370 : UDINT;
    MD371 : UDINT;
    MD372 : UDINT;
    MD373 : UDINT;
    MD374 : UDINT;
    MD375 : UDINT;
    MD376 : UDINT;
    MD377 : UDINT;
    MD378 : UDINT;
    MD379 : UDINT;
    MD380 : UDINT;
    MD381 : UDINT;
    MD382 : UDINT;
    MD383 : UDINT;
    MD384 : UDINT;
    MD385 : UDINT;
    MD386 : UDINT;
    MD387 : UDINT;
    MD388 : UDINT;
    MD389 : UDINT;
    MD390 : UDINT;
    MD391 : UDINT;
    MD392 : UDINT;
    MD393 : UDINT;
    MD394 : UDINT;
    MD395 : UDINT;
    MD396 : UDINT;
    MD397 : UDINT;
    MD398 : UDINT;
    MD399 : UDINT;
    MD400 : UDINT;
    MD401 : UDINT;
    MD402 : UDINT;
    MD403 : UDINT;
    MD404 : UDINT;
    MD405 : UDINT;
    MD406 : UDINT;
    MD407 : UDINT;
    MD408 : UDINT;
    MD409 : UDINT;
    MD410 : UDINT;
    MD411 : UDINT;
    MD412 : UDINT;
    MD413 : UDINT;
    MD414 : UDINT;
    MD415 : UDINT;
    MD416 : UDINT;
    MD417 : UDINT;
    MD418 : UDINT;
    MD419 : UDINT;
    MD420 : UDINT;
    MD421 : UDINT;
    MD422 : UDINT;
    MD423 : UDINT;
    MD424 : UDINT;
    MD425 : UDINT;
    MD426 : UDINT;
    MD427 : UDINT;
    MD428 : UDINT;
    MD429 : UDINT;
  END_VAR
  VAR_INPUT
    I : SINT := 0;
  END_VAR
  VAR_OUTPUT
    RAD : TRad;
  END_VAR

  CASE i OF
  0 : RAD := m_rad(MD302,MD303,MD304,MD305,MD306,MD307,MD308,MD309);
  1 : RAD := m_rad(MD310,MD311,MD312,MD313,MD314,MD315,MD316,MD317);
  2 : RAD := m_rad(MD318,MD319,MD320,MD321,MD322,MD323,MD324,MD325);
  3 : RAD := m_rad(MD326,MD327,MD328,MD329,MD330,MD331,MD332,MD333);
  4 : RAD := m_rad(MD334,MD335,MD336,MD337,MD338,MD339,MD340,MD341);
  5 : RAD := m_rad(MD342,MD343,MD344,MD345,MD346,MD347,MD348,MD349);
  6 : RAD := m_rad(MD350,MD351,MD352,MD353,MD354,MD355,MD356,MD357);
  7 : RAD := m_rad(MD358,MD359,MD360,MD361,MD362,MD363,MD364,MD365);
  8 : RAD := m_rad(MD366,MD367,MD368,MD369,MD370,MD371,MD372,MD373);
  9 : RAD := m_rad(MD374,MD375,MD376,MD377,MD378,MD379,MD380,MD381);
  10: RAD := m_rad(MD382,MD383,MD384,MD385,MD386,MD387,MD388,MD389);
  11: RAD := m_rad(MD390,MD391,MD392,MD393,MD394,MD395,MD396,MD397);
  12: RAD := m_rad(MD398,MD399,MD400,MD401,MD402,MD403,MD404,MD405);
  13: RAD := m_rad(MD406,MD407,MD408,MD409,MD410,MD411,MD412,MD413);
  14: RAD := m_rad(MD414,MD415,MD416,MD417,MD418,MD419,MD420,MD421);
  15: RAD := m_rad(MD422,MD423,MD424,MD425,MD426,MD427,MD428,MD429);
  END_CASE;
END_FUNCTION_BLOCK

FUNCTION IT_InfoStr : STRING
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR
  VAR
    Item : TItem;
    Shape : TShape;
    msg : STRING := '';
  END_VAR

  Item  := get_it(it_pos(PIT));
  Shape := get_sh(PIT);
  msg  := MakeMsg(msg, ' [',   ID2Str(Item.ID) );
  msg  := MakeMsg(msg, ', P=', SINT_TO_STRING(Item.Par) );
  msg  := MakeMsg(msg, ', O=(',REAL_TO_STRING(Shape.p0[0]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.p0[1]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.p0[2]), ')');
  msg  := MakeMsg(msg, ', N=(',REAL_TO_STRING(Shape.pL[0]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.pL[1]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.pL[2]), ')');
  msg  := MakeMsg(msg, ', W=(',REAL_TO_STRING(Shape.Lx[0]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.Lx[1]), '');
  msg  := MakeMsg(msg, ', ',   REAL_TO_STRING(Shape.Lx[2]), ')]');
  IT_InfoStr:=MSG;
END_FUNCTION

FUNCTION_BLOCK GetConf
  VAR_EXTERNAL
    MD300 : UDINT;
    MD301 : UDINT;
  END_VAR
  VAR_OUTPUT
    CONF : TConf;
  END_VAR

  CONF := m_conf(MD300,MD301);
END_FUNCTION_BLOCK

FUNCTION_BLOCK GetCond
  VAR_EXTERNAL
    MD500 : UDINT;
    MD501 : UDINT;
    MD502 : UDINT;
    MD503 : UDINT;
    MD504 : UDINT;
    MD505 : UDINT;
    MD506 : UDINT;
    MD507 : UDINT;
    MD508 : UDINT;
    MD509 : UDINT;
    MD510 : UDINT;
    MD511 : UDINT;
    MD512 : UDINT;
    MD513 : UDINT;
    MD514 : UDINT;
    MD515 : UDINT;
    MD516 : UDINT;
    MD517 : UDINT;
    MD518 : UDINT;
    MD519 : UDINT;
    MD520 : UDINT;
    MD521 : UDINT;
    MD522 : UDINT;
    MD523 : UDINT;
    MD524 : UDINT;
    MD525 : UDINT;
    MD526 : UDINT;
    MD527 : UDINT;
    MD528 : UDINT;
    MD529 : UDINT;
    MD530 : UDINT;
    MD531 : UDINT;
    MD532 : UDINT;
    MD533 : UDINT;
    MD534 : UDINT;
    MD535 : UDINT;
    MD536 : UDINT;
    MD537 : UDINT;
    MD538 : UDINT;
    MD539 : UDINT;
    MD540 : UDINT;
    MD541 : UDINT;
    MD542 : UDINT;
    MD543 : UDINT;
    MD544 : UDINT;
    MD545 : UDINT;
    MD546 : UDINT;
    MD547 : UDINT;
    MD548 : UDINT;
    MD549 : UDINT;
    MD550 : UDINT;
    MD551 : UDINT;
    MD552 : UDINT;
    MD553 : UDINT;
    MD554 : UDINT;
    MD555 : UDINT;
    MD556 : UDINT;
    MD557 : UDINT;
    MD558 : UDINT;
    MD559 : UDINT;
    MD560 : UDINT;
    MD561 : UDINT;
    MD562 : UDINT;
    MD563 : UDINT;
    MD564 : UDINT;
    MD565 : UDINT;
    MD566 : UDINT;
    MD567 : UDINT;
    MD568 : UDINT;
    MD569 : UDINT;
    MD570 : UDINT;
    MD571 : UDINT;
    MD572 : UDINT;
    MD573 : UDINT;
    MD574 : UDINT;
    MD575 : UDINT;
    MD576 : UDINT;
    MD577 : UDINT;
    MD578 : UDINT;
    MD579 : UDINT;
    MD580 : UDINT;
    MD581 : UDINT;
    MD582 : UDINT;
    MD583 : UDINT;
    MD584 : UDINT;
    MD585 : UDINT;
    MD586 : UDINT;
    MD587 : UDINT;
    MD588 : UDINT;
    MD589 : UDINT;
    MD590 : UDINT;
    MD591 : UDINT;
    MD592 : UDINT;
    MD593 : UDINT;
    MD594 : UDINT;
    MD595 : UDINT;
    MD596 : UDINT;
    MD597 : UDINT;
    MD598 : UDINT;
    MD599 : UDINT;
    MD600 : UDINT;
    MD601 : UDINT;
    MD602 : UDINT;
    MD603 : UDINT;
    MD604 : UDINT;
    MD605 : UDINT;
    MD606 : UDINT;
    MD607 : UDINT;
    MD608 : UDINT;
    MD609 : UDINT;
    MD610 : UDINT;
    MD611 : UDINT;
    MD612 : UDINT;
    MD613 : UDINT;
    MD614 : UDINT;
    MD615 : UDINT;
    MD616 : UDINT;
    MD617 : UDINT;
    MD618 : UDINT;
    MD619 : UDINT;
    MD620 : UDINT;
    MD621 : UDINT;
    MD622 : UDINT;
    MD623 : UDINT;
    MD624 : UDINT;
    MD625 : UDINT;
    MD626 : UDINT;
    MD627 : UDINT;
    MD628 : UDINT;
    MD629 : UDINT;
    MD630 : UDINT;
    MD631 : UDINT;
    MD632 : UDINT;
    MD633 : UDINT;
    MD634 : UDINT;
    MD635 : UDINT;
    MD636 : UDINT;
    MD637 : UDINT;
    MD638 : UDINT;
    MD639 : UDINT;
    MD640 : UDINT;
    MD641 : UDINT;
    MD642 : UDINT;
    MD643 : UDINT;
    MD644 : UDINT;
    MD645 : UDINT;
    MD646 : UDINT;
    MD647 : UDINT;
    MD648 : UDINT;
    MD649 : UDINT;
    MD650 : UDINT;
    MD651 : UDINT;
    MD652 : UDINT;
    MD653 : UDINT;
    MD654 : UDINT;
    MD655 : UDINT;
    MD656 : UDINT;
    MD657 : UDINT;
    MD658 : UDINT;
    MD659 : UDINT;
    MD660 : UDINT;
    MD661 : UDINT;
    MD662 : UDINT;
    MD663 : UDINT;
    MD664 : UDINT;
    MD665 : UDINT;
    MD666 : UDINT;
    MD667 : UDINT;
    MD668 : UDINT;
    MD669 : UDINT;
    MD670 : UDINT;
    MD671 : UDINT;
    MD672 : UDINT;
    MD673 : UDINT;
    MD674 : UDINT;
    MD675 : UDINT;
    MD676 : UDINT;
    MD677 : UDINT;
    MD678 : UDINT;
    MD679 : UDINT;
    MD680 : UDINT;
    MD681 : UDINT;
    MD682 : UDINT;
    MD683 : UDINT;
    MD684 : UDINT;
    MD685 : UDINT;
    MD686 : UDINT;
    MD687 : UDINT;
    MD688 : UDINT;
    MD689 : UDINT;
    MD690 : UDINT;
    MD691 : UDINT;
    MD692 : UDINT;
    MD693 : UDINT;
    MD694 : UDINT;
    MD695 : UDINT;
    MD696 : UDINT;
    MD697 : UDINT;
    MD698 : UDINT;
    MD699 : UDINT;
    MD700 : UDINT;
    MD701 : UDINT;
    MD702 : UDINT;
    MD703 : UDINT;
    MD704 : UDINT;
    MD705 : UDINT;
    MD706 : UDINT;
    MD707 : UDINT;
    MD708 : UDINT;
    MD709 : UDINT;
    MD710 : UDINT;
    MD711 : UDINT;
    MD712 : UDINT;
    MD713 : UDINT;
    MD714 : UDINT;
    MD715 : UDINT;
    MD716 : UDINT;
    MD717 : UDINT;
    MD718 : UDINT;
    MD719 : UDINT;
    MD720 : UDINT;
    MD721 : UDINT;
    MD722 : UDINT;
    MD723 : UDINT;
    MD724 : UDINT;
    MD725 : UDINT;
    MD726 : UDINT;
    MD727 : UDINT;
    MD728 : UDINT;
    MD729 : UDINT;
    MD730 : UDINT;
    MD731 : UDINT;
    MD732 : UDINT;
    MD733 : UDINT;
    MD734 : UDINT;
    MD735 : UDINT;
    MD736 : UDINT;
    MD737 : UDINT;
    MD738 : UDINT;
    MD739 : UDINT;
    MD740 : UDINT;
    MD741 : UDINT;
    MD742 : UDINT;
    MD743 : UDINT;
    MD744 : UDINT;
    MD745 : UDINT;
    MD746 : UDINT;
    MD747 : UDINT;
    MD748 : UDINT;
    MD749 : UDINT;
    MD750 : UDINT;
    MD751 : UDINT;
    MD752 : UDINT;
    MD753 : UDINT;
    MD754 : UDINT;
    MD755 : UDINT;
    MD756 : UDINT;
    MD757 : UDINT;
    MD758 : UDINT;
    MD759 : UDINT;
    MD760 : UDINT;
    MD761 : UDINT;
    MD762 : UDINT;
    MD763 : UDINT;
    MD764 : UDINT;
    MD765 : UDINT;
    MD766 : UDINT;
    MD767 : UDINT;
    MD768 : UDINT;
    MD769 : UDINT;
    MD770 : UDINT;
    MD771 : UDINT;
    MD772 : UDINT;
    MD773 : UDINT;
    MD774 : UDINT;
    MD775 : UDINT;
    MD776 : UDINT;
    MD777 : UDINT;
    MD778 : UDINT;
    MD779 : UDINT;
    MD780 : UDINT;
    MD781 : UDINT;
    MD782 : UDINT;
    MD783 : UDINT;
    MD784 : UDINT;
    MD785 : UDINT;
    MD786 : UDINT;
    MD787 : UDINT;
    MD788 : UDINT;
    MD789 : UDINT;
    MD790 : UDINT;
    MD791 : UDINT;
    MD792 : UDINT;
    MD793 : UDINT;
    MD794 : UDINT;
    MD795 : UDINT;
    MD796 : UDINT;
    MD797 : UDINT;
    MD798 : UDINT;
    MD799 : UDINT;
    MD800 : UDINT;
    MD801 : UDINT;
    MD802 : UDINT;
    MD803 : UDINT;
    MD804 : UDINT;
    MD805 : UDINT;
    MD806 : UDINT;
    MD807 : UDINT;
    MD808 : UDINT;
    MD809 : UDINT;
    MD810 : UDINT;
    MD811 : UDINT;
    MD812 : UDINT;
    MD813 : UDINT;
    MD814 : UDINT;
    MD815 : UDINT;
    MD816 : UDINT;
    MD817 : UDINT;
    MD818 : UDINT;
    MD819 : UDINT;
    MD820 : UDINT;
    MD821 : UDINT;
    MD822 : UDINT;
    MD823 : UDINT;
    MD824 : UDINT;
    MD825 : UDINT;
    MD826 : UDINT;
    MD827 : UDINT;
    MD828 : UDINT;
    MD829 : UDINT;
    MD830 : UDINT;
    MD831 : UDINT;
    MD832 : UDINT;
    MD833 : UDINT;
    MD834 : UDINT;
    MD835 : UDINT;
    MD836 : UDINT;
    MD837 : UDINT;
    MD838 : UDINT;
    MD839 : UDINT;
    MD840 : UDINT;
    MD841 : UDINT;
    MD842 : UDINT;
    MD843 : UDINT;
    MD844 : UDINT;
    MD845 : UDINT;
    MD846 : UDINT;
    MD847 : UDINT;
    MD848 : UDINT;
    MD849 : UDINT;
    MD850 : UDINT;
    MD851 : UDINT;
    MD852 : UDINT;
    MD853 : UDINT;
    MD854 : UDINT;
    MD855 : UDINT;
    MD856 : UDINT;
    MD857 : UDINT;
    MD858 : UDINT;
    MD859 : UDINT;
    MD860 : UDINT;
    MD861 : UDINT;
    MD862 : UDINT;
    MD863 : UDINT;
    MD864 : UDINT;
    MD865 : UDINT;
    MD866 : UDINT;
    MD867 : UDINT;
    MD868 : UDINT;
    MD869 : UDINT;
    MD870 : UDINT;
    MD871 : UDINT;
    MD872 : UDINT;
    MD873 : UDINT;
    MD874 : UDINT;
    MD875 : UDINT;
    MD876 : UDINT;
    MD877 : UDINT;
    MD878 : UDINT;
    MD879 : UDINT;
    MD880 : UDINT;
    MD881 : UDINT;
    MD882 : UDINT;
    MD883 : UDINT;
    MD884 : UDINT;
    MD885 : UDINT;
    MD886 : UDINT;
    MD887 : UDINT;
    MD888 : UDINT;
    MD889 : UDINT;
    MD890 : UDINT;
    MD891 : UDINT;
    MD892 : UDINT;
    MD893 : UDINT;
    MD894 : UDINT;
    MD895 : UDINT;
    MD896 : UDINT;
    MD897 : UDINT;
    MD898 : UDINT;
    MD899 : UDINT;
    MD900 : UDINT;
    MD901 : UDINT;
    MD902 : UDINT;
    MD903 : UDINT;
    MD904 : UDINT;
    MD905 : UDINT;
    MD906 : UDINT;
    MD907 : UDINT;
    MD908 : UDINT;
    MD909 : UDINT;
    MD910 : UDINT;
    MD911 : UDINT;
    MD912 : UDINT;
    MD913 : UDINT;
    MD914 : UDINT;
    MD915 : UDINT;
    MD916 : UDINT;
    MD917 : UDINT;
    MD918 : UDINT;
    MD919 : UDINT;
    MD920 : UDINT;
    MD921 : UDINT;
    MD922 : UDINT;
    MD923 : UDINT;
    MD924 : UDINT;
    MD925 : UDINT;
    MD926 : UDINT;
    MD927 : UDINT;
    MD928 : UDINT;
    MD929 : UDINT;
    MD930 : UDINT;
    MD931 : UDINT;
    MD932 : UDINT;
    MD933 : UDINT;
    MD934 : UDINT;
    MD935 : UDINT;
    MD936 : UDINT;
    MD937 : UDINT;
    MD938 : UDINT;
    MD939 : UDINT;
    MD940 : UDINT;
    MD941 : UDINT;
    MD942 : UDINT;
    MD943 : UDINT;
    MD944 : UDINT;
    MD945 : UDINT;
    MD946 : UDINT;
    MD947 : UDINT;
    MD948 : UDINT;
    MD949 : UDINT;
    MD950 : UDINT;
    MD951 : UDINT;
    MD952 : UDINT;
    MD953 : UDINT;
    MD954 : UDINT;
    MD955 : UDINT;
    MD956 : UDINT;
    MD957 : UDINT;
    MD958 : UDINT;
    MD959 : UDINT;
    MD960 : UDINT;
    MD961 : UDINT;
    MD962 : UDINT;
    MD963 : UDINT;
    MD964 : UDINT;
    MD965 : UDINT;
    MD966 : UDINT;
    MD967 : UDINT;
    MD968 : UDINT;
    MD969 : UDINT;
    MD970 : UDINT;
    MD971 : UDINT;
    MD972 : UDINT;
    MD973 : UDINT;
    MD974 : UDINT;
    MD975 : UDINT;
    MD976 : UDINT;
    MD977 : UDINT;
    MD978 : UDINT;
    MD979 : UDINT;
    MD980 : UDINT;
    MD981 : UDINT;
    MD982 : UDINT;
    MD983 : UDINT;
    MD984 : UDINT;
    MD985 : UDINT;
    MD986 : UDINT;
    MD987 : UDINT;
    MD988 : UDINT;
    MD989 : UDINT;
    MD990 : UDINT;
    MD991 : UDINT;
    MD992 : UDINT;
    MD993 : UDINT;
    MD994 : UDINT;
    MD995 : UDINT;
    MD996 : UDINT;
    MD997 : UDINT;
    MD998 : UDINT;
    MD999 : UDINT;
  END_VAR
  VAR_INPUT
    I : UINT := 0;
  END_VAR
  VAR_OUTPUT
    COND : TCond;
  END_VAR

  CASE i OF
  0  : COND := m_cond(MD500,MD501,MD502,MD503,MD504);
  1  : COND := m_cond(MD505,MD506,MD507,MD508,MD509);
  2  : COND := m_cond(MD510,MD511,MD512,MD513,MD514);
  3  : COND := m_cond(MD515,MD516,MD517,MD518,MD519);
  4  : COND := m_cond(MD520,MD521,MD522,MD523,MD524);
  5  : COND := m_cond(MD525,MD526,MD527,MD528,MD529);
  6  : COND := m_cond(MD530,MD531,MD532,MD533,MD534);
  7  : COND := m_cond(MD535,MD536,MD537,MD538,MD539);
  8  : COND := m_cond(MD540,MD541,MD542,MD543,MD544);
  9  : COND := m_cond(MD545,MD546,MD547,MD548,MD549);

  10 : COND := m_cond(MD550,MD551,MD552,MD553,MD554);
  11 : COND := m_cond(MD555,MD556,MD557,MD558,MD559);
  12 : COND := m_cond(MD560,MD561,MD562,MD563,MD564);
  13 : COND := m_cond(MD565,MD566,MD567,MD568,MD569);
  14 : COND := m_cond(MD570,MD571,MD572,MD573,MD574);
  15 : COND := m_cond(MD575,MD576,MD577,MD578,MD579);
  16 : COND := m_cond(MD580,MD581,MD582,MD583,MD584);
  17 : COND := m_cond(MD585,MD586,MD587,MD588,MD589);
  18 : COND := m_cond(MD590,MD591,MD592,MD593,MD594);
  19 : COND := m_cond(MD595,MD596,MD597,MD598,MD599);

  20 : COND := m_cond(MD600,MD601,MD602,MD603,MD604);
  21 : COND := m_cond(MD605,MD606,MD607,MD608,MD609);
  22 : COND := m_cond(MD610,MD611,MD612,MD613,MD614);
  23 : COND := m_cond(MD615,MD616,MD617,MD618,MD619);
  24 : COND := m_cond(MD620,MD621,MD622,MD623,MD624);
  25 : COND := m_cond(MD625,MD626,MD627,MD628,MD629);
  26 : COND := m_cond(MD630,MD631,MD632,MD633,MD634);
  27 : COND := m_cond(MD635,MD636,MD637,MD638,MD639);
  28 : COND := m_cond(MD640,MD641,MD642,MD643,MD644);
  29 : COND := m_cond(MD645,MD646,MD647,MD648,MD649);

  30 : COND := m_cond(MD650,MD651,MD652,MD653,MD654);
  31 : COND := m_cond(MD655,MD656,MD657,MD658,MD659);
  32 : COND := m_cond(MD660,MD661,MD662,MD663,MD664);
  33 : COND := m_cond(MD665,MD666,MD667,MD668,MD669);
  34 : COND := m_cond(MD670,MD671,MD672,MD673,MD674);
  35 : COND := m_cond(MD675,MD676,MD677,MD678,MD679);
  36 : COND := m_cond(MD680,MD681,MD682,MD683,MD684);
  37 : COND := m_cond(MD685,MD686,MD687,MD688,MD689);
  38 : COND := m_cond(MD690,MD691,MD692,MD693,MD694);
  39 : COND := m_cond(MD695,MD696,MD697,MD698,MD699);

  40 : COND := m_cond(MD700,MD701,MD702,MD703,MD704);
  41 : COND := m_cond(MD705,MD706,MD707,MD708,MD709);
  42 : COND := m_cond(MD710,MD711,MD712,MD713,MD714);
  43 : COND := m_cond(MD715,MD716,MD717,MD718,MD719);
  44 : COND := m_cond(MD720,MD721,MD722,MD723,MD724);
  45 : COND := m_cond(MD725,MD726,MD727,MD728,MD729);
  46 : COND := m_cond(MD730,MD731,MD732,MD733,MD734);
  47 : COND := m_cond(MD735,MD736,MD737,MD738,MD739);
  48 : COND := m_cond(MD740,MD741,MD742,MD743,MD744);
  49 : COND := m_cond(MD745,MD746,MD747,MD748,MD749);

  50 : COND := m_cond(MD750,MD751,MD752,MD753,MD754);
  51 : COND := m_cond(MD755,MD756,MD757,MD758,MD759);
  52 : COND := m_cond(MD760,MD761,MD762,MD763,MD764);
  53 : COND := m_cond(MD765,MD766,MD767,MD768,MD769);
  54 : COND := m_cond(MD770,MD771,MD772,MD773,MD774);
  55 : COND := m_cond(MD775,MD776,MD777,MD778,MD779);
  56 : COND := m_cond(MD780,MD781,MD782,MD783,MD784);
  57 : COND := m_cond(MD785,MD786,MD787,MD788,MD789);
  58 : COND := m_cond(MD790,MD791,MD792,MD793,MD794);
  59 : COND := m_cond(MD795,MD796,MD797,MD798,MD799);

  60 : COND := m_cond(MD800,MD801,MD802,MD803,MD804);
  61 : COND := m_cond(MD805,MD806,MD807,MD808,MD809);
  62 : COND := m_cond(MD810,MD811,MD812,MD813,MD814);
  63 : COND := m_cond(MD815,MD816,MD817,MD818,MD819);
  64 : COND := m_cond(MD820,MD821,MD822,MD823,MD824);
  65 : COND := m_cond(MD825,MD826,MD827,MD828,MD829);
  66 : COND := m_cond(MD830,MD831,MD832,MD833,MD834);
  67 : COND := m_cond(MD835,MD836,MD837,MD838,MD839);
  68 : COND := m_cond(MD840,MD841,MD842,MD843,MD844);
  69 : COND := m_cond(MD845,MD846,MD847,MD848,MD849);

  70 : COND := m_cond(MD850,MD851,MD852,MD853,MD854);
  71 : COND := m_cond(MD855,MD856,MD857,MD858,MD859);
  72 : COND := m_cond(MD860,MD861,MD862,MD863,MD864);
  73 : COND := m_cond(MD865,MD866,MD867,MD868,MD869);
  74 : COND := m_cond(MD870,MD871,MD872,MD873,MD874);
  75 : COND := m_cond(MD875,MD876,MD877,MD878,MD879);
  76 : COND := m_cond(MD880,MD881,MD882,MD883,MD884);
  77 : COND := m_cond(MD885,MD886,MD887,MD888,MD889);
  78 : COND := m_cond(MD890,MD891,MD892,MD893,MD894);
  79 : COND := m_cond(MD895,MD896,MD897,MD898,MD899);

  80 : COND := m_cond(MD900,MD901,MD902,MD903,MD904);
  81 : COND := m_cond(MD905,MD906,MD907,MD908,MD909);
  82 : COND := m_cond(MD910,MD911,MD912,MD913,MD914);
  83 : COND := m_cond(MD915,MD916,MD917,MD918,MD919);
  84 : COND := m_cond(MD920,MD921,MD922,MD923,MD924);
  85 : COND := m_cond(MD925,MD926,MD927,MD928,MD929);
  86 : COND := m_cond(MD930,MD931,MD932,MD933,MD934);
  87 : COND := m_cond(MD935,MD936,MD937,MD938,MD939);
  88 : COND := m_cond(MD940,MD941,MD942,MD943,MD944);
  89 : COND := m_cond(MD945,MD946,MD947,MD948,MD949);

  90 : COND := m_cond(MD950,MD951,MD952,MD953,MD954);
  91 : COND := m_cond(MD955,MD956,MD957,MD958,MD959);
  92 : COND := m_cond(MD960,MD961,MD962,MD963,MD964);
  93 : COND := m_cond(MD965,MD966,MD967,MD968,MD969);
  94 : COND := m_cond(MD970,MD971,MD972,MD973,MD974);
  95 : COND := m_cond(MD975,MD976,MD977,MD978,MD979);
  96 : COND := m_cond(MD980,MD981,MD982,MD983,MD984);
  97 : COND := m_cond(MD985,MD986,MD987,MD988,MD989);
  98 : COND := m_cond(MD990,MD991,MD992,MD993,MD994);
  99 : COND := m_cond(MD995,MD996,MD997,MD998,MD999);

  END_CASE;
END_FUNCTION_BLOCK

FUNCTION it_im : TPos8
  VAR_INPUT
    PIT : TPos8 := -1;
  END_VAR

  {{ return (IT_IM = __GET_GLOBAL_ITS()->IT.table[PIT].IM); }}
END_FUNCTION


CONFIGURATION Config0
  VAR_GLOBAL
    F_Conf : BOOL := TRUE;
    F_Res : BOOL := FALSE;
    STAT : TStat;
    HDR : THead;
    STS : TSets;
    ITS : TItems;
    SFC : ARRAY [0..2] OF TItem := [0, 0, 0];
    CFG : TConf;
    RAD : ARRAY [0..15] OF TRad := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    VRI : TVarI;
    PHI : ARRAY [0..2] OF TPhaseI := [0, 0, 0];
    VRO : TVarO;
    PHO : ARRAY [0..2] OF TPhaseO := [0, 0, 0];
    RES : TRes;
    rTest : REAL := 0.0;
  END_VAR

  RESOURCE Res0 ON PLC
    VAR_GLOBAL RETAIN
      MW0 AT %MW0 : UINT := 16#0000;
      MW1 AT %MW1 : UINT := 16#8000;
      MW2 AT %MW2 : UINT := 0;
      MW3 AT %MW3 : UINT := 0;
      MW4 AT %MW4 : UINT := 0;
      MW5 AT %MW5 : UINT := 0;
      MW6 AT %MW6 : UINT := 3600;
      MW7 AT %MW7 : UINT := 1240;
      MW8 AT %MW8 : UINT := 3150;
      MW9 AT %MW9 : UINT := 16#7000;
      MW10 AT %MW10 : UINT := 16#1000;
      MW11 AT %MW11 : UINT := 16#8000;
      MW12 AT %MW12 : UINT := 0;
      MW13 AT %MW13 : UINT := 0;
      MW14 AT %MW14 : UINT := 0;
      MW15 AT %MW15 : UINT := 0;
      MW16 AT %MW16 : UINT := 3600;
      MW17 AT %MW17 : UINT := 1240;
      MW18 AT %MW18 : UINT := 3150;
      MW19 AT %MW19 : UINT := 16#8000;
      MW20 AT %MW20 : UINT := 16#1100;
      MW21 AT %MW21 : UINT := 16#0000;
      MW22 AT %MW22 : UINT := 0;
      MW23 AT %MW23 : UINT := 620;
      MW24 AT %MW24 : UINT := 0;
      MW25 AT %MW25 : UINT := 3140;
      MW26 AT %MW26 : UINT := 2360;
      MW27 AT %MW27 : UINT := 1240;
      MW28 AT %MW28 : UINT := 10;
      MW29 AT %MW29 : UINT := 16#8200;
      MW30 AT %MW30 : UINT := 16#1200;
      MW31 AT %MW31 : UINT := 16#7400;
      MW32 AT %MW32 : UINT := 0;
      MW33 AT %MW33 : UINT := 620;
      MW34 AT %MW34 : UINT := 620;
      MW35 AT %MW35 : UINT := 3140;
      MW36 AT %MW36 : UINT := 620;
      MW37 AT %MW37 : UINT := 180;
      MW38 AT %MW38 : UINT := 10;
      MW39 AT %MW39 : UINT := 16#3200;
      MW40 AT %MW40 : UINT := 16#1300;
      MW41 AT %MW41 : UINT := 16#7C00;
      MW42 AT %MW42 : UINT := 0;
      MW43 AT %MW43 : UINT := 2980;
      MW44 AT %MW44 : UINT := 620;
      MW45 AT %MW45 : UINT := 3140;
      MW46 AT %MW46 : UINT := 620;
      MW47 AT %MW47 : UINT := 180;
      MW48 AT %MW48 : UINT := 10;
      MW49 AT %MW49 : UINT := 16#3200;
      MW50 AT %MW50 : UINT := 16#1400;
      MW51 AT %MW51 : UINT := 16#0000;
      MW52 AT %MW52 : UINT := 0;
      MW53 AT %MW53 : UINT := 620;
      MW54 AT %MW54 : UINT := 0;
      MW55 AT %MW55 : UINT := 0;
      MW56 AT %MW56 : UINT := 2360;
      MW57 AT %MW57 : UINT := 1240;
      MW58 AT %MW58 : UINT := 10;
      MW59 AT %MW59 : UINT := 16#8200;
      MW60 AT %MW60 : UINT := 16#1500;
      MW61 AT %MW61 : UINT := 16#7400;
      MW62 AT %MW62 : UINT := 0;
      MW63 AT %MW63 : UINT := 620;
      MW64 AT %MW64 : UINT := 620;
      MW65 AT %MW65 : UINT := 0;
      MW66 AT %MW66 : UINT := 620;
      MW67 AT %MW67 : UINT := 180;
      MW68 AT %MW68 : UINT := 10;
      MW69 AT %MW69 : UINT := 16#3200;
      MW70 AT %MW70 : UINT := 16#1600;
      MW71 AT %MW71 : UINT := 16#7C00;
      MW72 AT %MW72 : UINT := 0;
      MW73 AT %MW73 : UINT := 2980;
      MW74 AT %MW74 : UINT := 620;
      MW75 AT %MW75 : UINT := 0;
      MW76 AT %MW76 : UINT := 620;
      MW77 AT %MW77 : UINT := 180;
      MW78 AT %MW78 : UINT := 10;
      MW79 AT %MW79 : UINT := 16#3200;
      MW80 AT %MW80 : UINT := 16#1700;
      MW81 AT %MW81 : UINT := 16#7400;
      MW82 AT %MW82 : UINT := 610;
      MW83 AT %MW83 : UINT := 620;
      MW84 AT %MW84 : UINT := 620;
      MW85 AT %MW85 : UINT := 10;
      MW86 AT %MW86 : UINT := 10;
      MW87 AT %MW87 : UINT := 180;
      MW88 AT %MW88 : UINT := 3130;
      MW89 AT %MW89 : UINT := 16#1200;
      MW90 AT %MW90 : UINT := 16#1800;
      MW91 AT %MW91 : UINT := 16#7C00;
      MW92 AT %MW92 : UINT := 610;
      MW93 AT %MW93 : UINT := 2980;
      MW94 AT %MW94 : UINT := 620;
      MW95 AT %MW95 : UINT := 10;
      MW96 AT %MW96 : UINT := 10;
      MW97 AT %MW97 : UINT := 180;
      MW98 AT %MW98 : UINT := 3130;
      MW99 AT %MW99 : UINT := 16#1200;
      MW100 AT %MW100 : UINT := 16#1900;
      MW101 AT %MW101 : UINT := 16#0000;
      MW102 AT %MW102 : UINT := 0;
      MW103 AT %MW103 : UINT := 620;
      MW104 AT %MW104 : UINT := 0;
      MW105 AT %MW105 : UINT := 10;
      MW106 AT %MW106 : UINT := 2360;
      MW107 AT %MW107 : UINT := 10;
      MW108 AT %MW108 : UINT := 3130;
      MW109 AT %MW109 : UINT := 16#7200;
      MW110 AT %MW110 : UINT := 16#1A00;
      MW111 AT %MW111 : UINT := 16#0000;
      MW112 AT %MW112 : UINT := 0;
      MW113 AT %MW113 : UINT := 620;
      MW114 AT %MW114 : UINT := 1230;
      MW115 AT %MW115 : UINT := 10;
      MW116 AT %MW116 : UINT := 2360;
      MW117 AT %MW117 : UINT := 10;
      MW118 AT %MW118 : UINT := 3130;
      MW119 AT %MW119 : UINT := 16#7200;
      MW120 AT %MW120 : UINT := 16#1B00;
      MW121 AT %MW121 : UINT := 16#7400;
      MW122 AT %MW122 : UINT := 590;
      MW123 AT %MW123 : UINT := 620;
      MW124 AT %MW124 : UINT := 620;
      MW125 AT %MW125 : UINT := 10;
      MW126 AT %MW126 : UINT := 20;
      MW127 AT %MW127 : UINT := 180;
      MW128 AT %MW128 : UINT := 3130;
      MW129 AT %MW129 : UINT := 16#1100;
      MW130 AT %MW130 : UINT := 16#1C00;
      MW131 AT %MW131 : UINT := 16#7C00;
      MW132 AT %MW132 : UINT := 590;
      MW133 AT %MW133 : UINT := 2980;
      MW134 AT %MW134 : UINT := 620;
      MW135 AT %MW135 : UINT := 10;
      MW136 AT %MW136 : UINT := 20;
      MW137 AT %MW137 : UINT := 180;
      MW138 AT %MW138 : UINT := 3130;
      MW139 AT %MW139 : UINT := 16#1100;
      MW140 AT %MW140 : UINT := 16#1D00;
      MW141 AT %MW141 : UINT := 16#0000;
      MW142 AT %MW142 : UINT := 0;
      MW143 AT %MW143 : UINT := 620;
      MW144 AT %MW144 : UINT := 10;
      MW145 AT %MW145 : UINT := 10;
      MW146 AT %MW146 : UINT := 2360;
      MW147 AT %MW147 : UINT := 20;
      MW148 AT %MW148 : UINT := 3130;
      MW149 AT %MW149 : UINT := 16#7100;
      MW150 AT %MW150 : UINT := 16#1E00;
      MW151 AT %MW151 : UINT := 16#0000;
      MW152 AT %MW152 : UINT := 0;
      MW153 AT %MW153 : UINT := 620;
      MW154 AT %MW154 : UINT := 1210;
      MW155 AT %MW155 : UINT := 10;
      MW156 AT %MW156 : UINT := 2360;
      MW157 AT %MW157 : UINT := 20;
      MW158 AT %MW158 : UINT := 3130;
      MW159 AT %MW159 : UINT := 16#7100;
      MW160 AT %MW160 : UINT := 16#2000;
      MW161 AT %MW161 : UINT := 16#8000;
      MW162 AT %MW162 : UINT := 0;
      MW163 AT %MW163 : UINT := 30;
      MW164 AT %MW164 : UINT := 30;
      MW165 AT %MW165 : UINT := 2400;
      MW166 AT %MW166 : UINT := 3540;
      MW167 AT %MW167 : UINT := 1180;
      MW168 AT %MW168 : UINT := 740;
      MW169 AT %MW169 : UINT := 16#8000;
      MW170 AT %MW170 : UINT := 16#2100;
      MW171 AT %MW171 : UINT := 16#0000;
      MW172 AT %MW172 : UINT := 0;
      MW173 AT %MW173 : UINT := 590;
      MW174 AT %MW174 : UINT := 0;
      MW175 AT %MW175 : UINT := 350;
      MW176 AT %MW176 : UINT := 2360;
      MW177 AT %MW177 : UINT := 1180;
      MW178 AT %MW178 : UINT := 390;
      MW179 AT %MW179 : UINT := 16#8100;
      MW180 AT %MW180 : UINT := 16#2200;
      MW181 AT %MW181 : UINT := 16#7400;
      MW182 AT %MW182 : UINT := 0;
      MW183 AT %MW183 : UINT := 590;
      MW184 AT %MW184 : UINT := 590;
      MW185 AT %MW185 : UINT := 350;
      MW186 AT %MW186 : UINT := 590;
      MW187 AT %MW187 : UINT := 180;
      MW188 AT %MW188 : UINT := 390;
      MW189 AT %MW189 : UINT := 16#3100;
      MW190 AT %MW190 : UINT := 16#2300;
      MW191 AT %MW191 : UINT := 16#7C00;
      MW192 AT %MW192 : UINT := 0;
      MW193 AT %MW193 : UINT := 2950;
      MW194 AT %MW194 : UINT := 590;
      MW195 AT %MW195 : UINT := 350;
      MW196 AT %MW196 : UINT := 590;
      MW197 AT %MW197 : UINT := 180;
      MW198 AT %MW198 : UINT := 390;
      MW199 AT %MW199 : UINT := 16#3100;
      MW200 AT %MW200 : UINT := 16#2400;
      MW201 AT %MW201 : UINT := 16#8000;
      MW202 AT %MW202 : UINT := 0;
      MW203 AT %MW203 : UINT := 0;
      MW204 AT %MW204 : UINT := 0;
      MW205 AT %MW205 : UINT := 0;
      MW206 AT %MW206 : UINT := 3540;
      MW207 AT %MW207 : UINT := 1180;
      MW208 AT %MW208 : UINT := 350;
      MW209 AT %MW209 : UINT := 16#8000;
      MW210 AT %MW210 : UINT := 16#2410;
      MW211 AT %MW211 : UINT := 16#0000;
      MW212 AT %MW212 : UINT := 0;
      MW213 AT %MW213 : UINT := 275;
      MW214 AT %MW214 : UINT := 275;
      MW215 AT %MW215 : UINT := 0;
      MW216 AT %MW216 : UINT := 2990;
      MW217 AT %MW217 : UINT := 630;
      MW218 AT %MW218 : UINT := 350;
      MW219 AT %MW219 : UINT := 16#8300;
      MW220 AT %MW220 : UINT := 16#2420;
      MW221 AT %MW221 : UINT := 16#7460;
      MW222 AT %MW222 : UINT := 315;
      MW223 AT %MW223 : UINT := 590;
      MW224 AT %MW224 : UINT := 590;
      MW225 AT %MW225 : UINT := 0;
      MW226 AT %MW226 : UINT := 275;
      MW227 AT %MW227 : UINT := 180;
      MW228 AT %MW228 : UINT := 350;
      MW229 AT %MW229 : UINT := 16#3100;
      MW230 AT %MW230 : UINT := 16#2430;
      MW231 AT %MW231 : UINT := 16#7C90;
      MW232 AT %MW232 : UINT := 315;
      MW233 AT %MW233 : UINT := 2950;
      MW234 AT %MW234 : UINT := 590;
      MW235 AT %MW235 : UINT := 0;
      MW236 AT %MW236 : UINT := 275;
      MW237 AT %MW237 : UINT := 180;
      MW238 AT %MW238 : UINT := 350;
      MW239 AT %MW239 : UINT := 16#3100;
      MW240 AT %MW240 : UINT := 16#2440;
      MW241 AT %MW241 : UINT := 16#0000;
      MW242 AT %MW242 : UINT := 0;
      MW243 AT %MW243 : UINT := 590;
      MW244 AT %MW244 : UINT := 0;
      MW245 AT %MW245 : UINT := 0;
      MW246 AT %MW246 : UINT := 2360;
      MW247 AT %MW247 : UINT := 275;
      MW248 AT %MW248 : UINT := 350;
      MW249 AT %MW249 : UINT := 16#8100;
      MW250 AT %MW250 : UINT := 16#2450;
      MW251 AT %MW251 : UINT := 16#0000;
      MW252 AT %MW252 : UINT := 0;
      MW253 AT %MW253 : UINT := 590;
      MW254 AT %MW254 : UINT := 905;
      MW255 AT %MW255 : UINT := 0;
      MW256 AT %MW256 : UINT := 2360;
      MW257 AT %MW257 : UINT := 275;
      MW258 AT %MW258 : UINT := 350;
      MW259 AT %MW259 : UINT := 16#8100;
      MW260 AT %MW260 : UINT := 16#3000;
      MW261 AT %MW261 : UINT := 16#8000;
      MW262 AT %MW262 : UINT := 0;
      MW263 AT %MW263 : UINT := 30;
      MW264 AT %MW264 : UINT := 30;
      MW265 AT %MW265 : UINT := 10;
      MW266 AT %MW266 : UINT := 3540;
      MW267 AT %MW267 : UINT := 1180;
      MW268 AT %MW268 : UINT := 390;
      MW269 AT %MW269 : UINT := 16#8000;
      MW270 AT %MW270 : UINT := 16#3100;
      MW271 AT %MW271 : UINT := 16#0000;
      MW272 AT %MW272 : UINT := 0;
      MW273 AT %MW273 : UINT := 590;
      MW274 AT %MW274 : UINT := 0;
      MW275 AT %MW275 : UINT := 0;
      MW276 AT %MW276 : UINT := 2360;
      MW277 AT %MW277 : UINT := 1180;
      MW278 AT %MW278 : UINT := 40;
      MW279 AT %MW279 : UINT := 16#8100;
      MW280 AT %MW280 : UINT := 16#3200;
      MW281 AT %MW281 : UINT := 16#7400;
      MW282 AT %MW282 : UINT := 0;
      MW283 AT %MW283 : UINT := 590;
      MW284 AT %MW284 : UINT := 590;
      MW285 AT %MW285 : UINT := 0;
      MW286 AT %MW286 : UINT := 590;
      MW287 AT %MW287 : UINT := 180;
      MW288 AT %MW288 : UINT := 40;
      MW289 AT %MW289 : UINT := 16#3100;
      MW290 AT %MW290 : UINT := 16#3300;
      MW291 AT %MW291 : UINT := 16#7C00;
      MW292 AT %MW292 : UINT := 0;
      MW293 AT %MW293 : UINT := 2950;
      MW294 AT %MW294 : UINT := 590;
      MW295 AT %MW295 : UINT := 0;
      MW296 AT %MW296 : UINT := 590;
      MW297 AT %MW297 : UINT := 180;
      MW298 AT %MW298 : UINT := 40;
      MW299 AT %MW299 : UINT := 16#3100;
      MW300 AT %MW300 : UINT := 16#3400;
      MW301 AT %MW301 : UINT := 16#8000;
      MW302 AT %MW302 : UINT := 0;
      MW303 AT %MW303 : UINT := 0;
      MW304 AT %MW304 : UINT := 0;
      MW305 AT %MW305 : UINT := 40;
      MW306 AT %MW306 : UINT := 3540;
      MW307 AT %MW307 : UINT := 1180;
      MW308 AT %MW308 : UINT := 350;
      MW309 AT %MW309 : UINT := 16#8000;
      MW310 AT %MW310 : UINT := 16#3410;
      MW311 AT %MW311 : UINT := 16#0000;
      MW312 AT %MW312 : UINT := 0;
      MW313 AT %MW313 : UINT := 275;
      MW314 AT %MW314 : UINT := 275;
      MW315 AT %MW315 : UINT := 0;
      MW316 AT %MW316 : UINT := 2990;
      MW317 AT %MW317 : UINT := 630;
      MW318 AT %MW318 : UINT := 350;
      MW319 AT %MW319 : UINT := 16#8300;
      MW320 AT %MW320 : UINT := 16#3420;
      MW321 AT %MW321 : UINT := 16#7460;
      MW322 AT %MW322 : UINT := 315;
      MW323 AT %MW323 : UINT := 590;
      MW324 AT %MW324 : UINT := 590;
      MW325 AT %MW325 : UINT := 0;
      MW326 AT %MW326 : UINT := 275;
      MW327 AT %MW327 : UINT := 180;
      MW328 AT %MW328 : UINT := 350;
      MW329 AT %MW329 : UINT := 16#3100;
      MW330 AT %MW330 : UINT := 16#3430;
      MW331 AT %MW331 : UINT := 16#7C90;
      MW332 AT %MW332 : UINT := 315;
      MW333 AT %MW333 : UINT := 2950;
      MW334 AT %MW334 : UINT := 590;
      MW335 AT %MW335 : UINT := 0;
      MW336 AT %MW336 : UINT := 275;
      MW337 AT %MW337 : UINT := 180;
      MW338 AT %MW338 : UINT := 350;
      MW339 AT %MW339 : UINT := 16#3100;
      MW340 AT %MW340 : UINT := 16#3440;
      MW341 AT %MW341 : UINT := 16#0000;
      MW342 AT %MW342 : UINT := 0;
      MW343 AT %MW343 : UINT := 590;
      MW344 AT %MW344 : UINT := 0;
      MW345 AT %MW345 : UINT := 0;
      MW346 AT %MW346 : UINT := 2360;
      MW347 AT %MW347 : UINT := 275;
      MW348 AT %MW348 : UINT := 350;
      MW349 AT %MW349 : UINT := 16#8100;
      MW350 AT %MW350 : UINT := 16#3450;
      MW351 AT %MW351 : UINT := 16#0000;
      MW352 AT %MW352 : UINT := 0;
      MW353 AT %MW353 : UINT := 590;
      MW354 AT %MW354 : UINT := 905;
      MW355 AT %MW355 : UINT := 0;
      MW356 AT %MW356 : UINT := 2360;
      MW357 AT %MW357 : UINT := 275;
      MW358 AT %MW358 : UINT := 350;
      MW359 AT %MW359 : UINT := 16#8100;
      MW360 AT %MW360 : UINT := 16#4000;
      MW361 AT %MW361 : UINT := 16#8000;
      MW362 AT %MW362 : UINT := 0;
      MW363 AT %MW363 : UINT := 30;
      MW364 AT %MW364 : UINT := 30;
      MW365 AT %MW365 : UINT := 400;
      MW366 AT %MW366 : UINT := 3540;
      MW367 AT %MW367 : UINT := 1180;
      MW368 AT %MW368 : UINT := 2000;
      MW369 AT %MW369 : UINT := 16#8000;
      MW370 AT %MW370 : UINT := 16#4100;
      MW371 AT %MW371 : UINT := 16#F009;
      MW372 AT %MW372 : UINT := 0;
      MW373 AT %MW373 : UINT := 590;
      MW374 AT %MW374 : UINT := 590;
      MW375 AT %MW375 : UINT := 0;
      MW376 AT %MW376 : UINT := 590;
      MW377 AT %MW377 : UINT := 360;
      MW378 AT %MW378 : UINT := 2000;
      MW379 AT %MW379 : UINT := 16#1000;
      MW380 AT %MW380 : UINT := 16#4110;
      MW381 AT %MW381 : UINT := 16#4000;
      MW382 AT %MW382 : UINT := 0;
      MW383 AT %MW383 : UINT := 0;
      MW384 AT %MW384 : UINT := 0;
      MW385 AT %MW385 : UINT := 0;
      MW386 AT %MW386 : UINT := 315;
      MW387 AT %MW387 : UINT := 360;
      MW388 AT %MW388 : UINT := 2000;
      MW389 AT %MW389 : UINT := 16#1300;
      MW390 AT %MW390 : UINT := 16#4120;
      MW391 AT %MW391 : UINT := 16#4009;
      MW392 AT %MW392 : UINT := 0;
      MW393 AT %MW393 : UINT := 315;
      MW394 AT %MW394 : UINT := 0;
      MW395 AT %MW395 : UINT := 1850;
      MW396 AT %MW396 : UINT := 275;
      MW397 AT %MW397 : UINT := 360;
      MW398 AT %MW398 : UINT := 150;
      MW399 AT %MW399 : UINT := 16#5100;
      MW400 AT %MW400 : UINT := 16#4130;
      MW401 AT %MW401 : UINT := 16#4009;
      MW402 AT %MW402 : UINT := 0;
      MW403 AT %MW403 : UINT := 315;
      MW404 AT %MW404 : UINT := 0;
      MW405 AT %MW405 : UINT := 0;
      MW406 AT %MW406 : UINT := 275;
      MW407 AT %MW407 : UINT := 360;
      MW408 AT %MW408 : UINT := 150;
      MW409 AT %MW409 : UINT := 16#5100;
      MW410 AT %MW410 : UINT := 16#4140;
      MW411 AT %MW411 : UINT := 16#4000;
      MW412 AT %MW412 : UINT := 0;
      MW413 AT %MW413 : UINT := 315;
      MW414 AT %MW414 : UINT := 0;
      MW415 AT %MW415 : UINT := 150;
      MW416 AT %MW416 : UINT := 30;
      MW417 AT %MW417 : UINT := 360;
      MW418 AT %MW418 : UINT := 1700;
      MW419 AT %MW419 : UINT := 16#1100;
      MW420 AT %MW420 : UINT := 16#4150;
      MW421 AT %MW421 : UINT := 16#4000;
      MW422 AT %MW422 : UINT := 0;
      MW423 AT %MW423 : UINT := 345;
      MW424 AT %MW424 : UINT := 0;
      MW425 AT %MW425 : UINT := 150;
      MW426 AT %MW426 : UINT := 80;
      MW427 AT %MW427 : UINT := 360;
      MW428 AT %MW428 : UINT := 1700;
      MW429 AT %MW429 : UINT := 16#1400;
      MW430 AT %MW430 : UINT := 16#4160;
      MW431 AT %MW431 : UINT := 16#4000;
      MW432 AT %MW432 : UINT := 0;
      MW433 AT %MW433 : UINT := 425;
      MW434 AT %MW434 : UINT := 0;
      MW435 AT %MW435 : UINT := 150;
      MW436 AT %MW436 : UINT := 30;
      MW437 AT %MW437 : UINT := 360;
      MW438 AT %MW438 : UINT := 1700;
      MW439 AT %MW439 : UINT := 16#1100;
      MW440 AT %MW440 : UINT := 16#4170;
      MW441 AT %MW441 : UINT := 16#C000;
      MW442 AT %MW442 : UINT := 0;
      MW443 AT %MW443 : UINT := 455;
      MW444 AT %MW444 : UINT := 0;
      MW445 AT %MW445 : UINT := 150;
      MW446 AT %MW446 : UINT := 90;
      MW447 AT %MW447 : UINT := 360;
      MW448 AT %MW448 : UINT := 1700;
      MW449 AT %MW449 : UINT := 16#1000;
      MW450 AT %MW450 : UINT := 16#4171;
      MW451 AT %MW451 : UINT := 16#4000;
      MW452 AT %MW452 : UINT := 0;
      MW453 AT %MW453 : UINT := 455;
      MW454 AT %MW454 : UINT := 0;
      MW455 AT %MW455 : UINT := 150;
      MW456 AT %MW456 : UINT := 90;
      MW457 AT %MW457 : UINT := 360;
      MW458 AT %MW458 : UINT := 170;
      MW459 AT %MW459 : UINT := 16#3500;
      MW460 AT %MW460 : UINT := 16#4172;
      MW461 AT %MW461 : UINT := 16#4000;
      MW462 AT %MW462 : UINT := 0;
      MW463 AT %MW463 : UINT := 455;
      MW464 AT %MW464 : UINT := 0;
      MW465 AT %MW465 : UINT := 320;
      MW466 AT %MW466 : UINT := 90;
      MW467 AT %MW467 : UINT := 360;
      MW468 AT %MW468 : UINT := 170;
      MW469 AT %MW469 : UINT := 16#3500;
      MW470 AT %MW470 : UINT := 16#4173;
      MW471 AT %MW471 : UINT := 16#4000;
      MW472 AT %MW472 : UINT := 0;
      MW473 AT %MW473 : UINT := 455;
      MW474 AT %MW474 : UINT := 0;
      MW475 AT %MW475 : UINT := 490;
      MW476 AT %MW476 : UINT := 90;
      MW477 AT %MW477 : UINT := 360;
      MW478 AT %MW478 : UINT := 170;
      MW479 AT %MW479 : UINT := 16#3500;
      MW480 AT %MW480 : UINT := 16#4174;
      MW481 AT %MW481 : UINT := 16#4000;
      MW482 AT %MW482 : UINT := 0;
      MW483 AT %MW483 : UINT := 455;
      MW484 AT %MW484 : UINT := 0;
      MW485 AT %MW485 : UINT := 660;
      MW486 AT %MW486 : UINT := 90;
      MW487 AT %MW487 : UINT := 360;
      MW488 AT %MW488 : UINT := 170;
      MW489 AT %MW489 : UINT := 16#3500;
      MW490 AT %MW490 : UINT := 16#4175;
      MW491 AT %MW491 : UINT := 16#4000;
      MW492 AT %MW492 : UINT := 0;
      MW493 AT %MW493 : UINT := 455;
      MW494 AT %MW494 : UINT := 0;
      MW495 AT %MW495 : UINT := 830;
      MW496 AT %MW496 : UINT := 90;
      MW497 AT %MW497 : UINT := 360;
      MW498 AT %MW498 : UINT := 170;
      MW499 AT %MW499 : UINT := 16#3500;
      MW500 AT %MW500 : UINT := 16#4176;
      MW501 AT %MW501 : UINT := 16#4000;
      MW502 AT %MW502 : UINT := 0;
      MW503 AT %MW503 : UINT := 455;
      MW504 AT %MW504 : UINT := 0;
      MW505 AT %MW505 : UINT := 1000;
      MW506 AT %MW506 : UINT := 90;
      MW507 AT %MW507 : UINT := 360;
      MW508 AT %MW508 : UINT := 170;
      MW509 AT %MW509 : UINT := 16#3500;
      MW510 AT %MW510 : UINT := 16#4177;
      MW511 AT %MW511 : UINT := 16#4000;
      MW512 AT %MW512 : UINT := 0;
      MW513 AT %MW513 : UINT := 455;
      MW514 AT %MW514 : UINT := 0;
      MW515 AT %MW515 : UINT := 1170;
      MW516 AT %MW516 : UINT := 90;
      MW517 AT %MW517 : UINT := 360;
      MW518 AT %MW518 : UINT := 170;
      MW519 AT %MW519 : UINT := 16#3500;
      MW520 AT %MW520 : UINT := 16#4178;
      MW521 AT %MW521 : UINT := 16#4000;
      MW522 AT %MW522 : UINT := 0;
      MW523 AT %MW523 : UINT := 455;
      MW524 AT %MW524 : UINT := 0;
      MW525 AT %MW525 : UINT := 1340;
      MW526 AT %MW526 : UINT := 90;
      MW527 AT %MW527 : UINT := 360;
      MW528 AT %MW528 : UINT := 170;
      MW529 AT %MW529 : UINT := 16#3500;
      MW530 AT %MW530 : UINT := 16#4179;
      MW531 AT %MW531 : UINT := 16#4000;
      MW532 AT %MW532 : UINT := 0;
      MW533 AT %MW533 : UINT := 455;
      MW534 AT %MW534 : UINT := 0;
      MW535 AT %MW535 : UINT := 1510;
      MW536 AT %MW536 : UINT := 90;
      MW537 AT %MW537 : UINT := 360;
      MW538 AT %MW538 : UINT := 170;
      MW539 AT %MW539 : UINT := 16#3500;
      MW540 AT %MW540 : UINT := 16#417A;
      MW541 AT %MW541 : UINT := 16#4000;
      MW542 AT %MW542 : UINT := 0;
      MW543 AT %MW543 : UINT := 455;
      MW544 AT %MW544 : UINT := 0;
      MW545 AT %MW545 : UINT := 1680;
      MW546 AT %MW546 : UINT := 90;
      MW547 AT %MW547 : UINT := 360;
      MW548 AT %MW548 : UINT := 170;
      MW549 AT %MW549 : UINT := 16#3500;
      MW550 AT %MW550 : UINT := 16#4180;
      MW551 AT %MW551 : UINT := 16#C009;
      MW552 AT %MW552 : UINT := 0;
      MW553 AT %MW553 : UINT := 545;
      MW554 AT %MW554 : UINT := 0;
      MW555 AT %MW555 : UINT := 150;
      MW556 AT %MW556 : UINT := 45;
      MW557 AT %MW557 : UINT := 360;
      MW558 AT %MW558 : UINT := 1700;
      MW559 AT %MW559 : UINT := 16#1000;
      MW560 AT %MW560 : UINT := 16#4181;
      MW561 AT %MW561 : UINT := 16#4000;
      MW562 AT %MW562 : UINT := 0;
      MW563 AT %MW563 : UINT := 545;
      MW564 AT %MW564 : UINT := 90;
      MW565 AT %MW565 : UINT := 150;
      MW566 AT %MW566 : UINT := 45;
      MW567 AT %MW567 : UINT := 180;
      MW568 AT %MW568 : UINT := 1700;
      MW569 AT %MW569 : UINT := 16#1100;
      MW570 AT %MW570 : UINT := 16#4182;
      MW571 AT %MW571 : UINT := 16#4009;
      MW572 AT %MW572 : UINT := 0;
      MW573 AT %MW573 : UINT := 545;
      MW574 AT %MW574 : UINT := -90;
      MW575 AT %MW575 : UINT := 150;
      MW576 AT %MW576 : UINT := 45;
      MW577 AT %MW577 : UINT := 180;
      MW578 AT %MW578 : UINT := 1700;
      MW579 AT %MW579 : UINT := 16#1100;
      MW580 AT %MW580 : UINT := 16#4200;
      MW581 AT %MW581 : UINT := 16#F00F;
      MW582 AT %MW582 : UINT := 0;
      MW583 AT %MW583 : UINT := 1770;
      MW584 AT %MW584 : UINT := 590;
      MW585 AT %MW585 : UINT := 0;
      MW586 AT %MW586 : UINT := 590;
      MW587 AT %MW587 : UINT := 360;
      MW588 AT %MW588 : UINT := 2000;
      MW589 AT %MW589 : UINT := 16#1000;
      MW590 AT %MW590 : UINT := 16#4210;
      MW591 AT %MW591 : UINT := 16#4000;
      MW592 AT %MW592 : UINT := 0;
      MW593 AT %MW593 : UINT := 0;
      MW594 AT %MW594 : UINT := 0;
      MW595 AT %MW595 : UINT := 0;
      MW596 AT %MW596 : UINT := 315;
      MW597 AT %MW597 : UINT := 360;
      MW598 AT %MW598 : UINT := 2000;
      MW599 AT %MW599 : UINT := 16#1300;
      MW600 AT %MW600 : UINT := 16#4220;
      MW601 AT %MW601 : UINT := 16#400F;
      MW602 AT %MW602 : UINT := 0;
      MW603 AT %MW603 : UINT := 315;
      MW604 AT %MW604 : UINT := 0;
      MW605 AT %MW605 : UINT := 1850;
      MW606 AT %MW606 : UINT := 275;
      MW607 AT %MW607 : UINT := 360;
      MW608 AT %MW608 : UINT := 150;
      MW609 AT %MW609 : UINT := 16#5100;
      MW610 AT %MW610 : UINT := 16#4230;
      MW611 AT %MW611 : UINT := 16#400F;
      MW612 AT %MW612 : UINT := 0;
      MW613 AT %MW613 : UINT := 315;
      MW614 AT %MW614 : UINT := 0;
      MW615 AT %MW615 : UINT := 0;
      MW616 AT %MW616 : UINT := 275;
      MW617 AT %MW617 : UINT := 360;
      MW618 AT %MW618 : UINT := 150;
      MW619 AT %MW619 : UINT := 16#5100;
      MW620 AT %MW620 : UINT := 16#4240;
      MW621 AT %MW621 : UINT := 16#4000;
      MW622 AT %MW622 : UINT := 0;
      MW623 AT %MW623 : UINT := 315;
      MW624 AT %MW624 : UINT := 0;
      MW625 AT %MW625 : UINT := 150;
      MW626 AT %MW626 : UINT := 30;
      MW627 AT %MW627 : UINT := 360;
      MW628 AT %MW628 : UINT := 1700;
      MW629 AT %MW629 : UINT := 16#1100;
      MW630 AT %MW630 : UINT := 16#4250;
      MW631 AT %MW631 : UINT := 16#4000;
      MW632 AT %MW632 : UINT := 0;
      MW633 AT %MW633 : UINT := 345;
      MW634 AT %MW634 : UINT := 0;
      MW635 AT %MW635 : UINT := 150;
      MW636 AT %MW636 : UINT := 80;
      MW637 AT %MW637 : UINT := 360;
      MW638 AT %MW638 : UINT := 1700;
      MW639 AT %MW639 : UINT := 16#1400;
      MW640 AT %MW640 : UINT := 16#4260;
      MW641 AT %MW641 : UINT := 16#4000;
      MW642 AT %MW642 : UINT := 0;
      MW643 AT %MW643 : UINT := 425;
      MW644 AT %MW644 : UINT := 0;
      MW645 AT %MW645 : UINT := 150;
      MW646 AT %MW646 : UINT := 30;
      MW647 AT %MW647 : UINT := 360;
      MW648 AT %MW648 : UINT := 1700;
      MW649 AT %MW649 : UINT := 16#1100;
      MW650 AT %MW650 : UINT := 16#4270;
      MW651 AT %MW651 : UINT := 16#C000;
      MW652 AT %MW652 : UINT := 0;
      MW653 AT %MW653 : UINT := 455;
      MW654 AT %MW654 : UINT := 0;
      MW655 AT %MW655 : UINT := 150;
      MW656 AT %MW656 : UINT := 90;
      MW657 AT %MW657 : UINT := 360;
      MW658 AT %MW658 : UINT := 1700;
      MW659 AT %MW659 : UINT := 16#1000;
      MW660 AT %MW660 : UINT := 16#4271;
      MW661 AT %MW661 : UINT := 16#4000;
      MW662 AT %MW662 : UINT := 0;
      MW663 AT %MW663 : UINT := 455;
      MW664 AT %MW664 : UINT := 0;
      MW665 AT %MW665 : UINT := 150;
      MW666 AT %MW666 : UINT := 90;
      MW667 AT %MW667 : UINT := 360;
      MW668 AT %MW668 : UINT := 170;
      MW669 AT %MW669 : UINT := 16#3500;
      MW670 AT %MW670 : UINT := 16#4272;
      MW671 AT %MW671 : UINT := 16#4000;
      MW672 AT %MW672 : UINT := 0;
      MW673 AT %MW673 : UINT := 455;
      MW674 AT %MW674 : UINT := 0;
      MW675 AT %MW675 : UINT := 320;
      MW676 AT %MW676 : UINT := 90;
      MW677 AT %MW677 : UINT := 360;
      MW678 AT %MW678 : UINT := 170;
      MW679 AT %MW679 : UINT := 16#3500;
      MW680 AT %MW680 : UINT := 16#4273;
      MW681 AT %MW681 : UINT := 16#4000;
      MW682 AT %MW682 : UINT := 0;
      MW683 AT %MW683 : UINT := 455;
      MW684 AT %MW684 : UINT := 0;
      MW685 AT %MW685 : UINT := 490;
      MW686 AT %MW686 : UINT := 90;
      MW687 AT %MW687 : UINT := 360;
      MW688 AT %MW688 : UINT := 170;
      MW689 AT %MW689 : UINT := 16#3500;
      MW690 AT %MW690 : UINT := 16#4274;
      MW691 AT %MW691 : UINT := 16#4000;
      MW692 AT %MW692 : UINT := 0;
      MW693 AT %MW693 : UINT := 455;
      MW694 AT %MW694 : UINT := 0;
      MW695 AT %MW695 : UINT := 660;
      MW696 AT %MW696 : UINT := 90;
      MW697 AT %MW697 : UINT := 360;
      MW698 AT %MW698 : UINT := 170;
      MW699 AT %MW699 : UINT := 16#3500;
      MW700 AT %MW700 : UINT := 16#4275;
      MW701 AT %MW701 : UINT := 16#4000;
      MW702 AT %MW702 : UINT := 0;
      MW703 AT %MW703 : UINT := 455;
      MW704 AT %MW704 : UINT := 0;
      MW705 AT %MW705 : UINT := 830;
      MW706 AT %MW706 : UINT := 90;
      MW707 AT %MW707 : UINT := 360;
      MW708 AT %MW708 : UINT := 170;
      MW709 AT %MW709 : UINT := 16#3500;
      MW710 AT %MW710 : UINT := 16#4276;
      MW711 AT %MW711 : UINT := 16#4000;
      MW712 AT %MW712 : UINT := 0;
      MW713 AT %MW713 : UINT := 455;
      MW714 AT %MW714 : UINT := 0;
      MW715 AT %MW715 : UINT := 1000;
      MW716 AT %MW716 : UINT := 90;
      MW717 AT %MW717 : UINT := 360;
      MW718 AT %MW718 : UINT := 170;
      MW719 AT %MW719 : UINT := 16#3500;
      MW720 AT %MW720 : UINT := 16#4277;
      MW721 AT %MW721 : UINT := 16#4000;
      MW722 AT %MW722 : UINT := 0;
      MW723 AT %MW723 : UINT := 455;
      MW724 AT %MW724 : UINT := 0;
      MW725 AT %MW725 : UINT := 1170;
      MW726 AT %MW726 : UINT := 90;
      MW727 AT %MW727 : UINT := 360;
      MW728 AT %MW728 : UINT := 170;
      MW729 AT %MW729 : UINT := 16#3500;
      MW730 AT %MW730 : UINT := 16#4278;
      MW731 AT %MW731 : UINT := 16#4000;
      MW732 AT %MW732 : UINT := 0;
      MW733 AT %MW733 : UINT := 455;
      MW734 AT %MW734 : UINT := 0;
      MW735 AT %MW735 : UINT := 1340;
      MW736 AT %MW736 : UINT := 90;
      MW737 AT %MW737 : UINT := 360;
      MW738 AT %MW738 : UINT := 170;
      MW739 AT %MW739 : UINT := 16#3500;
      MW740 AT %MW740 : UINT := 16#4279;
      MW741 AT %MW741 : UINT := 16#4000;
      MW742 AT %MW742 : UINT := 0;
      MW743 AT %MW743 : UINT := 455;
      MW744 AT %MW744 : UINT := 0;
      MW745 AT %MW745 : UINT := 1510;
      MW746 AT %MW746 : UINT := 90;
      MW747 AT %MW747 : UINT := 360;
      MW748 AT %MW748 : UINT := 170;
      MW749 AT %MW749 : UINT := 16#3500;
      MW750 AT %MW750 : UINT := 16#427A;
      MW751 AT %MW751 : UINT := 16#4000;
      MW752 AT %MW752 : UINT := 0;
      MW753 AT %MW753 : UINT := 455;
      MW754 AT %MW754 : UINT := 0;
      MW755 AT %MW755 : UINT := 1680;
      MW756 AT %MW756 : UINT := 90;
      MW757 AT %MW757 : UINT := 360;
      MW758 AT %MW758 : UINT := 170;
      MW759 AT %MW759 : UINT := 16#3500;
      MW760 AT %MW760 : UINT := 16#4280;
      MW761 AT %MW761 : UINT := 16#C00F;
      MW762 AT %MW762 : UINT := 0;
      MW763 AT %MW763 : UINT := 545;
      MW764 AT %MW764 : UINT := 0;
      MW765 AT %MW765 : UINT := 150;
      MW766 AT %MW766 : UINT := 45;
      MW767 AT %MW767 : UINT := 360;
      MW768 AT %MW768 : UINT := 1700;
      MW769 AT %MW769 : UINT := 16#1000;
      MW770 AT %MW770 : UINT := 16#4281;
      MW771 AT %MW771 : UINT := 16#400F;
      MW772 AT %MW772 : UINT := 0;
      MW773 AT %MW773 : UINT := 545;
      MW774 AT %MW774 : UINT := 90;
      MW775 AT %MW775 : UINT := 150;
      MW776 AT %MW776 : UINT := 45;
      MW777 AT %MW777 : UINT := 180;
      MW778 AT %MW778 : UINT := 1700;
      MW779 AT %MW779 : UINT := 16#1100;
      MW780 AT %MW780 : UINT := 16#4282;
      MW781 AT %MW781 : UINT := 16#400F;
      MW782 AT %MW782 : UINT := 0;
      MW783 AT %MW783 : UINT := 545;
      MW784 AT %MW784 : UINT := -90;
      MW785 AT %MW785 : UINT := 150;
      MW786 AT %MW786 : UINT := 45;
      MW787 AT %MW787 : UINT := 180;
      MW788 AT %MW788 : UINT := 1700;
      MW789 AT %MW789 : UINT := 16#1100;
      MW790 AT %MW790 : UINT := 16#4300;
      MW791 AT %MW791 : UINT := 16#F006;
      MW792 AT %MW792 : UINT := 0;
      MW793 AT %MW793 : UINT := 2950;
      MW794 AT %MW794 : UINT := 590;
      MW795 AT %MW795 : UINT := 0;
      MW796 AT %MW796 : UINT := 590;
      MW797 AT %MW797 : UINT := 360;
      MW798 AT %MW798 : UINT := 2000;
      MW799 AT %MW799 : UINT := 16#1000;
      MW800 AT %MW800 : UINT := 16#4310;
      MW801 AT %MW801 : UINT := 16#4000;
      MW802 AT %MW802 : UINT := 0;
      MW803 AT %MW803 : UINT := 0;
      MW804 AT %MW804 : UINT := 0;
      MW805 AT %MW805 : UINT := 0;
      MW806 AT %MW806 : UINT := 315;
      MW807 AT %MW807 : UINT := 360;
      MW808 AT %MW808 : UINT := 2000;
      MW809 AT %MW809 : UINT := 16#1300;
      MW810 AT %MW810 : UINT := 16#4320;
      MW811 AT %MW811 : UINT := 16#4006;
      MW812 AT %MW812 : UINT := 0;
      MW813 AT %MW813 : UINT := 315;
      MW814 AT %MW814 : UINT := 0;
      MW815 AT %MW815 : UINT := 1850;
      MW816 AT %MW816 : UINT := 275;
      MW817 AT %MW817 : UINT := 360;
      MW818 AT %MW818 : UINT := 150;
      MW819 AT %MW819 : UINT := 16#5100;
      MW820 AT %MW820 : UINT := 16#4330;
      MW821 AT %MW821 : UINT := 16#4006;
      MW822 AT %MW822 : UINT := 0;
      MW823 AT %MW823 : UINT := 315;
      MW824 AT %MW824 : UINT := 0;
      MW825 AT %MW825 : UINT := 0;
      MW826 AT %MW826 : UINT := 275;
      MW827 AT %MW827 : UINT := 360;
      MW828 AT %MW828 : UINT := 150;
      MW829 AT %MW829 : UINT := 16#5100;
      MW830 AT %MW830 : UINT := 16#4340;
      MW831 AT %MW831 : UINT := 16#4000;
      MW832 AT %MW832 : UINT := 0;
      MW833 AT %MW833 : UINT := 315;
      MW834 AT %MW834 : UINT := 0;
      MW835 AT %MW835 : UINT := 150;
      MW836 AT %MW836 : UINT := 30;
      MW837 AT %MW837 : UINT := 360;
      MW838 AT %MW838 : UINT := 1700;
      MW839 AT %MW839 : UINT := 16#1100;
      MW840 AT %MW840 : UINT := 16#4350;
      MW841 AT %MW841 : UINT := 16#4000;
      MW842 AT %MW842 : UINT := 0;
      MW843 AT %MW843 : UINT := 345;
      MW844 AT %MW844 : UINT := 0;
      MW845 AT %MW845 : UINT := 150;
      MW846 AT %MW846 : UINT := 80;
      MW847 AT %MW847 : UINT := 360;
      MW848 AT %MW848 : UINT := 1700;
      MW849 AT %MW849 : UINT := 16#1400;
      MW850 AT %MW850 : UINT := 16#4360;
      MW851 AT %MW851 : UINT := 16#4000;
      MW852 AT %MW852 : UINT := 0;
      MW853 AT %MW853 : UINT := 425;
      MW854 AT %MW854 : UINT := 0;
      MW855 AT %MW855 : UINT := 150;
      MW856 AT %MW856 : UINT := 30;
      MW857 AT %MW857 : UINT := 360;
      MW858 AT %MW858 : UINT := 1700;
      MW859 AT %MW859 : UINT := 16#1100;
      MW860 AT %MW860 : UINT := 16#4370;
      MW861 AT %MW861 : UINT := 16#C000;
      MW862 AT %MW862 : UINT := 0;
      MW863 AT %MW863 : UINT := 455;
      MW864 AT %MW864 : UINT := 0;
      MW865 AT %MW865 : UINT := 150;
      MW866 AT %MW866 : UINT := 90;
      MW867 AT %MW867 : UINT := 360;
      MW868 AT %MW868 : UINT := 1700;
      MW869 AT %MW869 : UINT := 16#1000;
      MW870 AT %MW870 : UINT := 16#4371;
      MW871 AT %MW871 : UINT := 16#4000;
      MW872 AT %MW872 : UINT := 0;
      MW873 AT %MW873 : UINT := 455;
      MW874 AT %MW874 : UINT := 0;
      MW875 AT %MW875 : UINT := 150;
      MW876 AT %MW876 : UINT := 90;
      MW877 AT %MW877 : UINT := 360;
      MW878 AT %MW878 : UINT := 170;
      MW879 AT %MW879 : UINT := 16#3500;
      MW880 AT %MW880 : UINT := 16#4372;
      MW881 AT %MW881 : UINT := 16#4000;
      MW882 AT %MW882 : UINT := 0;
      MW883 AT %MW883 : UINT := 455;
      MW884 AT %MW884 : UINT := 0;
      MW885 AT %MW885 : UINT := 320;
      MW886 AT %MW886 : UINT := 90;
      MW887 AT %MW887 : UINT := 360;
      MW888 AT %MW888 : UINT := 170;
      MW889 AT %MW889 : UINT := 16#3500;
      MW890 AT %MW890 : UINT := 16#4373;
      MW891 AT %MW891 : UINT := 16#4000;
      MW892 AT %MW892 : UINT := 0;
      MW893 AT %MW893 : UINT := 455;
      MW894 AT %MW894 : UINT := 0;
      MW895 AT %MW895 : UINT := 490;
      MW896 AT %MW896 : UINT := 90;
      MW897 AT %MW897 : UINT := 360;
      MW898 AT %MW898 : UINT := 170;
      MW899 AT %MW899 : UINT := 16#3500;
      MW900 AT %MW900 : UINT := 16#4374;
      MW901 AT %MW901 : UINT := 16#4000;
      MW902 AT %MW902 : UINT := 0;
      MW903 AT %MW903 : UINT := 455;
      MW904 AT %MW904 : UINT := 0;
      MW905 AT %MW905 : UINT := 660;
      MW906 AT %MW906 : UINT := 90;
      MW907 AT %MW907 : UINT := 360;
      MW908 AT %MW908 : UINT := 170;
      MW909 AT %MW909 : UINT := 16#3500;
      MW910 AT %MW910 : UINT := 16#4375;
      MW911 AT %MW911 : UINT := 16#4000;
      MW912 AT %MW912 : UINT := 0;
      MW913 AT %MW913 : UINT := 455;
      MW914 AT %MW914 : UINT := 0;
      MW915 AT %MW915 : UINT := 830;
      MW916 AT %MW916 : UINT := 90;
      MW917 AT %MW917 : UINT := 360;
      MW918 AT %MW918 : UINT := 170;
      MW919 AT %MW919 : UINT := 16#3500;
      MW920 AT %MW920 : UINT := 16#4376;
      MW921 AT %MW921 : UINT := 16#4000;
      MW922 AT %MW922 : UINT := 0;
      MW923 AT %MW923 : UINT := 455;
      MW924 AT %MW924 : UINT := 0;
      MW925 AT %MW925 : UINT := 1000;
      MW926 AT %MW926 : UINT := 90;
      MW927 AT %MW927 : UINT := 360;
      MW928 AT %MW928 : UINT := 170;
      MW929 AT %MW929 : UINT := 16#3500;
      MW930 AT %MW930 : UINT := 16#4377;
      MW931 AT %MW931 : UINT := 16#4000;
      MW932 AT %MW932 : UINT := 0;
      MW933 AT %MW933 : UINT := 455;
      MW934 AT %MW934 : UINT := 0;
      MW935 AT %MW935 : UINT := 1170;
      MW936 AT %MW936 : UINT := 90;
      MW937 AT %MW937 : UINT := 360;
      MW938 AT %MW938 : UINT := 170;
      MW939 AT %MW939 : UINT := 16#3500;
      MW940 AT %MW940 : UINT := 16#4378;
      MW941 AT %MW941 : UINT := 16#4000;
      MW942 AT %MW942 : UINT := 0;
      MW943 AT %MW943 : UINT := 455;
      MW944 AT %MW944 : UINT := 0;
      MW945 AT %MW945 : UINT := 1340;
      MW946 AT %MW946 : UINT := 90;
      MW947 AT %MW947 : UINT := 360;
      MW948 AT %MW948 : UINT := 170;
      MW949 AT %MW949 : UINT := 16#3500;
      MW950 AT %MW950 : UINT := 16#4379;
      MW951 AT %MW951 : UINT := 16#4000;
      MW952 AT %MW952 : UINT := 0;
      MW953 AT %MW953 : UINT := 455;
      MW954 AT %MW954 : UINT := 0;
      MW955 AT %MW955 : UINT := 1510;
      MW956 AT %MW956 : UINT := 90;
      MW957 AT %MW957 : UINT := 360;
      MW958 AT %MW958 : UINT := 170;
      MW959 AT %MW959 : UINT := 16#3500;
      MW960 AT %MW960 : UINT := 16#437A;
      MW961 AT %MW961 : UINT := 16#4000;
      MW962 AT %MW962 : UINT := 0;
      MW963 AT %MW963 : UINT := 455;
      MW964 AT %MW964 : UINT := 0;
      MW965 AT %MW965 : UINT := 1680;
      MW966 AT %MW966 : UINT := 90;
      MW967 AT %MW967 : UINT := 360;
      MW968 AT %MW968 : UINT := 170;
      MW969 AT %MW969 : UINT := 16#3500;
      MW970 AT %MW970 : UINT := 16#4380;
      MW971 AT %MW971 : UINT := 16#C006;
      MW972 AT %MW972 : UINT := 0;
      MW973 AT %MW973 : UINT := 545;
      MW974 AT %MW974 : UINT := 0;
      MW975 AT %MW975 : UINT := 150;
      MW976 AT %MW976 : UINT := 45;
      MW977 AT %MW977 : UINT := 360;
      MW978 AT %MW978 : UINT := 1700;
      MW979 AT %MW979 : UINT := 16#1000;
      MW980 AT %MW980 : UINT := 16#4381;
      MW981 AT %MW981 : UINT := 16#4006;
      MW982 AT %MW982 : UINT := 0;
      MW983 AT %MW983 : UINT := 545;
      MW984 AT %MW984 : UINT := 90;
      MW985 AT %MW985 : UINT := 150;
      MW986 AT %MW986 : UINT := 45;
      MW987 AT %MW987 : UINT := 180;
      MW988 AT %MW988 : UINT := 1700;
      MW989 AT %MW989 : UINT := 16#1100;
      MW990 AT %MW990 : UINT := 16#4382;
      MW991 AT %MW991 : UINT := 16#4000;
      MW992 AT %MW992 : UINT := 0;
      MW993 AT %MW993 : UINT := 545;
      MW994 AT %MW994 : UINT := -90;
      MW995 AT %MW995 : UINT := 150;
      MW996 AT %MW996 : UINT := 45;
      MW997 AT %MW997 : UINT := 180;
      MW998 AT %MW998 : UINT := 1700;
      MW999 AT %MW999 : UINT := 16#1100;
      MW1000 AT %MW1000 : UINT := 0;
      MW1001 AT %MW1001 : UINT := 0;
      MW1002 AT %MW1002 : UINT := 0;
      MW1003 AT %MW1003 : UINT := 0;
      MW1004 AT %MW1004 : UINT := 0;
      MW1005 AT %MW1005 : UINT := 0;
      MW1006 AT %MW1006 : UINT := 0;
      MW1007 AT %MW1007 : UINT := 0;
      MW1008 AT %MW1008 : UINT := 0;
      MW1009 AT %MW1009 : UINT := 0;
      MW1010 AT %MW1010 : UINT := 0;
      MW1011 AT %MW1011 : UINT := 0;
      MW1012 AT %MW1012 : UINT := 0;
      MW1013 AT %MW1013 : UINT := 0;
      MW1014 AT %MW1014 : UINT := 0;
      MW1015 AT %MW1015 : UINT := 0;
      MW1016 AT %MW1016 : UINT := 0;
      MW1017 AT %MW1017 : UINT := 0;
      MW1018 AT %MW1018 : UINT := 0;
      MW1019 AT %MW1019 : UINT := 0;
      MW1020 AT %MW1020 : UINT := 0;
      MW1021 AT %MW1021 : UINT := 0;
      MW1022 AT %MW1022 : UINT := 0;
      MW1023 AT %MW1023 : UINT := 0;
      MD0 AT %MD0 : UDINT := 16#640A0600;
      MD1 AT %MD1 : UDINT := 16#01000000;
      MD2 AT %MD2 : UDINT := 16#00000000;
      MD3 AT %MD3 : UDINT := 16#00000000;
      MD4 AT %MD4 : UDINT := 16#00000000;
      MD5 AT %MD5 : UDINT := 16#00000000;
      MD6 AT %MD6 : UDINT := 16#00000000;
      MD7 AT %MD7 : UDINT := 16#00000000;
      MD8 AT %MD8 : UDINT := 16#00000000;
      MD9 AT %MD9 : UDINT := 16#00000000;
      MD10 AT %MD10 : UDINT := 16#08084000;
      MD11 AT %MD11 : UDINT := 16#08102000;
      MD12 AT %MD12 : UDINT := 16#08201000;
      MD13 AT %MD13 : UDINT := 16#08400800;
      MD14 AT %MD14 : UDINT := 16#10082000;
      MD15 AT %MD15 : UDINT := 16#10101000;
      MD16 AT %MD16 : UDINT := 16#10200800;
      MD17 AT %MD17 : UDINT := 16#20081000;
      MD18 AT %MD18 : UDINT := 16#20100800;
      MD19 AT %MD19 : UDINT := 16#40080800;
      MD20 AT %MD20 : UDINT := 16#FFFFFFFF;
      MD21 AT %MD21 : UDINT := 16#FFFFFFFF;
      MD22 AT %MD22 : UDINT := 1021719033;
      MD23 AT %MD23 : UDINT := 1148928000;
      MD24 AT %MD24 : UDINT := 1067240653;
      MD25 AT %MD25 : UDINT := 0;
      MD26 AT %MD26 : UDINT := 1038254657;
      MD27 AT %MD27 : UDINT := 1154523136;
      MD28 AT %MD28 : UDINT := 1146934067;
      MD29 AT %MD29 : UDINT := 1017263004;
      MD30 AT %MD30 : UDINT := 1112014848;
      MD31 AT %MD31 : UDINT := 1139146752;
      MD32 AT %MD32 : UDINT := 1173536768;
      MD33 AT %MD33 : UDINT := 0;
      MD34 AT %MD34 : UDINT := 1110966272;
      MD35 AT %MD35 : UDINT := 1139802112;
      MD36 AT %MD36 : UDINT := 1173295104;
      MD37 AT %MD37 : UDINT := 0;
      MD38 AT %MD38 : UDINT := 1137180672;
      MD39 AT %MD39 : UDINT := 1136689152;
      MD40 AT %MD40 : UDINT := 1175163904;
      MD41 AT %MD41 : UDINT := 0;
      MD42 AT %MD42 : UDINT := 1137180672;
      MD43 AT %MD43 : UDINT := 1136689152;
      MD44 AT %MD44 : UDINT := 1175163904;
      MD45 AT %MD45 : UDINT := 0;
      MD46 AT %MD46 : UDINT := 16#FFFFFFFF;
      MD47 AT %MD47 : UDINT := 16#FFFFFFFF;
      MD48 AT %MD48 : UDINT := 16#FFFFFFFF;
      MD49 AT %MD49 : UDINT := 16#FFFFFFFF;
      MD50 AT %MD50 : UDINT := 16#FFFFFFFF;
      MD51 AT %MD51 : UDINT := 16#FFFFFFFF;
      MD52 AT %MD52 : UDINT := 16#FFFFFFFF;
      MD53 AT %MD53 : UDINT := 16#FFFFFFFF;
      MD54 AT %MD54 : UDINT := 16#FFFFFFFF;
      MD55 AT %MD55 : UDINT := 16#FFFFFFFF;
      MD56 AT %MD56 : UDINT := 16#FFFFFFFF;
      MD57 AT %MD57 : UDINT := 16#FFFFFFFF;
      MD58 AT %MD58 : UDINT := 16#FFFFFFFF;
      MD59 AT %MD59 : UDINT := 16#FFFFFFFF;
      MD60 AT %MD60 : UDINT := 16#FFFFFFFF;
      MD61 AT %MD61 : UDINT := 16#FFFFFFFF;
      MD62 AT %MD62 : UDINT := 16#FFFFFFFF;
      MD63 AT %MD63 : UDINT := 16#FFFFFFFF;
      MD64 AT %MD64 : UDINT := 16#FFFFFFFF;
      MD65 AT %MD65 : UDINT := 16#FFFFFFFF;
      MD66 AT %MD66 : UDINT := 16#FFFFFFFF;
      MD67 AT %MD67 : UDINT := 16#FFFFFFFF;
      MD68 AT %MD68 : UDINT := 16#FFFFFFFF;
      MD69 AT %MD69 : UDINT := 16#FFFFFFFF;
      MD70 AT %MD70 : UDINT := 16#00000000;
      MD71 AT %MD71 : UDINT := 16#00000000;
      MD72 AT %MD72 : UDINT := 16#00000000;
      MD73 AT %MD73 : UDINT := 16#00000000;
      MD74 AT %MD74 : UDINT := 16#00000000;
      MD75 AT %MD75 : UDINT := 16#00000000;
      MD76 AT %MD76 : UDINT := 16#00000000;
      MD77 AT %MD77 : UDINT := 16#00000000;
      MD78 AT %MD78 : UDINT := 16#00000000;
      MD79 AT %MD79 : UDINT := 16#00000000;
      MD80 AT %MD80 : UDINT := 16#00000000;
      MD81 AT %MD81 : UDINT := 16#00000000;
      MD82 AT %MD82 : UDINT := 16#00000000;
      MD83 AT %MD83 : UDINT := 16#00000000;
      MD84 AT %MD84 : UDINT := 16#00000000;
      MD85 AT %MD85 : UDINT := 16#00000000;
      MD86 AT %MD86 : UDINT := 16#00000000;
      MD87 AT %MD87 : UDINT := 16#00000000;
      MD88 AT %MD88 : UDINT := 16#00000000;
      MD89 AT %MD89 : UDINT := 16#00000000;
      MD90 AT %MD90 : UDINT := 16#00000000;
      MD91 AT %MD91 : UDINT := 16#00000000;
      MD92 AT %MD92 : UDINT := 16#00000000;
      MD93 AT %MD93 : UDINT := 16#00000000;
      MD94 AT %MD94 : UDINT := 16#00000000;
      MD95 AT %MD95 : UDINT := 16#00000000;
      MD96 AT %MD96 : UDINT := 16#00000000;
      MD97 AT %MD97 : UDINT := 16#00000000;
      MD98 AT %MD98 : UDINT := 16#00000000;
      MD99 AT %MD99 : UDINT := 16#00000000;
      MD100 AT %MD100 : UDINT := 16#00000000;
      MD101 AT %MD101 : UDINT := 16#00000000;
      MD102 AT %MD102 : UDINT := 16#00000000;
      MD103 AT %MD103 : UDINT := 16#00000000;
      MD104 AT %MD104 : UDINT := 16#00000000;
      MD105 AT %MD105 : UDINT := 16#00000000;
      MD106 AT %MD106 : UDINT := 16#00000000;
      MD107 AT %MD107 : UDINT := 16#00000000;
      MD108 AT %MD108 : UDINT := 16#00000000;
      MD109 AT %MD109 : UDINT := 16#00000000;
      MD110 AT %MD110 : UDINT := 16#00000000;
      MD111 AT %MD111 : UDINT := 16#00000000;
      MD112 AT %MD112 : UDINT := 16#00000000;
      MD113 AT %MD113 : UDINT := 16#00000000;
      MD114 AT %MD114 : UDINT := 16#00000000;
      MD115 AT %MD115 : UDINT := 16#00000000;
      MD116 AT %MD116 : UDINT := 16#00000000;
      MD117 AT %MD117 : UDINT := 16#00000000;
      MD118 AT %MD118 : UDINT := 16#00000000;
      MD119 AT %MD119 : UDINT := 16#00000000;
      MD120 AT %MD120 : UDINT := 16#00000000;
      MD121 AT %MD121 : UDINT := 16#00000000;
      MD122 AT %MD122 : UDINT := 16#00000000;
      MD123 AT %MD123 : UDINT := 16#00000000;
      MD124 AT %MD124 : UDINT := 16#00000000;
      MD125 AT %MD125 : UDINT := 16#00000000;
      MD126 AT %MD126 : UDINT := 16#00000000;
      MD127 AT %MD127 : UDINT := 16#00000000;
      MD128 AT %MD128 : UDINT := 16#00000000;
      MD129 AT %MD129 : UDINT := 16#00000000;
      MD130 AT %MD130 : UDINT := 16#00000000;
      MD131 AT %MD131 : UDINT := 16#00000000;
      MD132 AT %MD132 : UDINT := 16#00000000;
      MD133 AT %MD133 : UDINT := 16#00000000;
      MD134 AT %MD134 : UDINT := 16#00000000;
      MD135 AT %MD135 : UDINT := 16#00000000;
      MD136 AT %MD136 : UDINT := 16#00000000;
      MD137 AT %MD137 : UDINT := 16#00000000;
      MD138 AT %MD138 : UDINT := 16#00000000;
      MD139 AT %MD139 : UDINT := 16#00000000;
      MD140 AT %MD140 : UDINT := 16#00000000;
      MD141 AT %MD141 : UDINT := 16#00000000;
      MD142 AT %MD142 : UDINT := 16#00000000;
      MD143 AT %MD143 : UDINT := 16#00000000;
      MD144 AT %MD144 : UDINT := 16#00000000;
      MD145 AT %MD145 : UDINT := 16#00000000;
      MD146 AT %MD146 : UDINT := 16#00000000;
      MD147 AT %MD147 : UDINT := 16#00000000;
      MD148 AT %MD148 : UDINT := 16#00000000;
      MD149 AT %MD149 : UDINT := 16#00000000;
      MD150 AT %MD150 : UDINT := 16#00000000;
      MD151 AT %MD151 : UDINT := 16#00000000;
      MD152 AT %MD152 : UDINT := 16#00000000;
      MD153 AT %MD153 : UDINT := 16#00000000;
      MD154 AT %MD154 : UDINT := 16#00000000;
      MD155 AT %MD155 : UDINT := 16#00000000;
      MD156 AT %MD156 : UDINT := 16#00000000;
      MD157 AT %MD157 : UDINT := 16#00000000;
      MD158 AT %MD158 : UDINT := 16#00000000;
      MD159 AT %MD159 : UDINT := 16#00000000;
      MD160 AT %MD160 : UDINT := 16#00000000;
      MD161 AT %MD161 : UDINT := 16#00000000;
      MD162 AT %MD162 : UDINT := 16#00000000;
      MD163 AT %MD163 : UDINT := 16#00000000;
      MD164 AT %MD164 : UDINT := 16#00000000;
      MD165 AT %MD165 : UDINT := 16#00000000;
      MD166 AT %MD166 : UDINT := 16#00000000;
      MD167 AT %MD167 : UDINT := 16#00000000;
      MD168 AT %MD168 : UDINT := 16#00000000;
      MD169 AT %MD169 : UDINT := 16#00000000;
      MD170 AT %MD170 : UDINT := 16#00000000;
      MD171 AT %MD171 : UDINT := 16#00000000;
      MD172 AT %MD172 : UDINT := 16#00000000;
      MD173 AT %MD173 : UDINT := 16#00000000;
      MD174 AT %MD174 : UDINT := 16#00000000;
      MD175 AT %MD175 : UDINT := 16#00000000;
      MD176 AT %MD176 : UDINT := 16#00000000;
      MD177 AT %MD177 : UDINT := 16#00000000;
      MD178 AT %MD178 : UDINT := 16#00000000;
      MD179 AT %MD179 : UDINT := 16#00000000;
      MD180 AT %MD180 : UDINT := 16#00000000;
      MD181 AT %MD181 : UDINT := 16#00000000;
      MD182 AT %MD182 : UDINT := 16#00000000;
      MD183 AT %MD183 : UDINT := 16#00000000;
      MD184 AT %MD184 : UDINT := 16#00000000;
      MD185 AT %MD185 : UDINT := 16#00000000;
      MD186 AT %MD186 : UDINT := 16#00000000;
      MD187 AT %MD187 : UDINT := 16#00000000;
      MD188 AT %MD188 : UDINT := 16#00000000;
      MD189 AT %MD189 : UDINT := 16#00000000;
      MD190 AT %MD190 : UDINT := 16#00000000;
      MD191 AT %MD191 : UDINT := 16#00000000;
      MD192 AT %MD192 : UDINT := 16#00000000;
      MD193 AT %MD193 : UDINT := 16#00000000;
      MD194 AT %MD194 : UDINT := 16#00000000;
      MD195 AT %MD195 : UDINT := 16#00000000;
      MD196 AT %MD196 : UDINT := 16#00000000;
      MD197 AT %MD197 : UDINT := 16#00000000;
      MD198 AT %MD198 : UDINT := 16#00000000;
      MD199 AT %MD199 : UDINT := 16#00000000;
      MD200 AT %MD200 : UDINT := 16#00000000;
      MD201 AT %MD201 : UDINT := 16#00000000;
      MD202 AT %MD202 : UDINT := 16#00000000;
      MD203 AT %MD203 : UDINT := 16#00000000;
      MD204 AT %MD204 : UDINT := 16#00000000;
      MD205 AT %MD205 : UDINT := 16#00000000;
      MD206 AT %MD206 : UDINT := 16#00000000;
      MD207 AT %MD207 : UDINT := 16#00000000;
      MD208 AT %MD208 : UDINT := 16#00000000;
      MD209 AT %MD209 : UDINT := 16#00000000;
      MD210 AT %MD210 : UDINT := 16#00000000;
      MD211 AT %MD211 : UDINT := 16#00000000;
      MD212 AT %MD212 : UDINT := 16#00000000;
      MD213 AT %MD213 : UDINT := 16#00000000;
      MD214 AT %MD214 : UDINT := 16#00000000;
      MD215 AT %MD215 : UDINT := 16#00000000;
      MD216 AT %MD216 : UDINT := 16#00000000;
      MD217 AT %MD217 : UDINT := 16#00000000;
      MD218 AT %MD218 : UDINT := 16#00000000;
      MD219 AT %MD219 : UDINT := 16#00000000;
      MD220 AT %MD220 : UDINT := 16#00000000;
      MD221 AT %MD221 : UDINT := 16#00000000;
      MD222 AT %MD222 : UDINT := 16#00000000;
      MD223 AT %MD223 : UDINT := 16#00000000;
      MD224 AT %MD224 : UDINT := 16#00000000;
      MD225 AT %MD225 : UDINT := 16#00000000;
      MD226 AT %MD226 : UDINT := 16#00000000;
      MD227 AT %MD227 : UDINT := 16#00000000;
      MD228 AT %MD228 : UDINT := 16#00000000;
      MD229 AT %MD229 : UDINT := 16#00000000;
      MD230 AT %MD230 : UDINT := 16#00000000;
      MD231 AT %MD231 : UDINT := 16#00000000;
      MD232 AT %MD232 : UDINT := 16#00000000;
      MD233 AT %MD233 : UDINT := 16#00000000;
      MD234 AT %MD234 : UDINT := 16#00000000;
      MD235 AT %MD235 : UDINT := 16#00000000;
      MD236 AT %MD236 : UDINT := 16#00000000;
      MD237 AT %MD237 : UDINT := 16#00000000;
      MD238 AT %MD238 : UDINT := 16#00000000;
      MD239 AT %MD239 : UDINT := 16#00000000;
      MD240 AT %MD240 : UDINT := 16#00000000;
      MD241 AT %MD241 : UDINT := 16#00000000;
      MD242 AT %MD242 : UDINT := 16#00000000;
      MD243 AT %MD243 : UDINT := 16#00000000;
      MD244 AT %MD244 : UDINT := 16#00000000;
      MD245 AT %MD245 : UDINT := 16#00000000;
      MD246 AT %MD246 : UDINT := 16#00000000;
      MD247 AT %MD247 : UDINT := 16#00000000;
      MD248 AT %MD248 : UDINT := 16#00000000;
      MD249 AT %MD249 : UDINT := 16#00000000;
      MD250 AT %MD250 : UDINT := 16#00000000;
      MD251 AT %MD251 : UDINT := 16#00000000;
      MD252 AT %MD252 : UDINT := 16#00000000;
      MD253 AT %MD253 : UDINT := 16#00000000;
      MD254 AT %MD254 : UDINT := 16#00000000;
      MD255 AT %MD255 : UDINT := 16#00000000;
      MD256 AT %MD256 : UDINT := 16#00000000;
      MD257 AT %MD257 : UDINT := 16#00000000;
      MD258 AT %MD258 : UDINT := 16#00000000;
      MD259 AT %MD259 : UDINT := 16#00000000;
      MD260 AT %MD260 : UDINT := 16#00000000;
      MD261 AT %MD261 : UDINT := 16#00000000;
      MD262 AT %MD262 : UDINT := 16#00000000;
      MD263 AT %MD263 : UDINT := 16#00000000;
      MD264 AT %MD264 : UDINT := 16#00000000;
      MD265 AT %MD265 : UDINT := 16#00000000;
      MD266 AT %MD266 : UDINT := 16#00000000;
      MD267 AT %MD267 : UDINT := 16#00000000;
      MD268 AT %MD268 : UDINT := 16#00000000;
      MD269 AT %MD269 : UDINT := 16#00000000;
      MD270 AT %MD270 : UDINT := 16#00000000;
      MD271 AT %MD271 : UDINT := 16#00000000;
      MD272 AT %MD272 : UDINT := 16#00000000;
      MD273 AT %MD273 : UDINT := 16#00000000;
      MD274 AT %MD274 : UDINT := 16#00000000;
      MD275 AT %MD275 : UDINT := 16#00000000;
      MD276 AT %MD276 : UDINT := 16#00000000;
      MD277 AT %MD277 : UDINT := 16#00000000;
      MD278 AT %MD278 : UDINT := 16#00000000;
      MD279 AT %MD279 : UDINT := 16#00000000;
      MD280 AT %MD280 : UDINT := 16#00000000;
      MD281 AT %MD281 : UDINT := 16#00000000;
      MD282 AT %MD282 : UDINT := 16#00000000;
      MD283 AT %MD283 : UDINT := 16#00000000;
      MD284 AT %MD284 : UDINT := 16#00000000;
      MD285 AT %MD285 : UDINT := 16#00000000;
      MD286 AT %MD286 : UDINT := 16#00000000;
      MD287 AT %MD287 : UDINT := 16#00000000;
      MD288 AT %MD288 : UDINT := 16#00000000;
      MD289 AT %MD289 : UDINT := 16#00000000;
      MD290 AT %MD290 : UDINT := 16#00000000;
      MD291 AT %MD291 : UDINT := 16#00000000;
      MD292 AT %MD292 : UDINT := 16#00000000;
      MD293 AT %MD293 : UDINT := 16#00000000;
      MD294 AT %MD294 : UDINT := 16#00000000;
      MD295 AT %MD295 : UDINT := 16#00000000;
      MD296 AT %MD296 : UDINT := 16#00000000;
      MD297 AT %MD297 : UDINT := 16#00000000;
      MD298 AT %MD298 : UDINT := 16#00000000;
      MD299 AT %MD299 : UDINT := 16#00000000;
      MD300 AT %MD300 : UDINT := 16#00000000;
      MD301 AT %MD301 : UDINT := 16#00000000;
      MD302 AT %MD302 : UDINT := 16#00000000;
      MD303 AT %MD303 : UDINT := 16#00000000;
      MD304 AT %MD304 : UDINT := 16#00000000;
      MD305 AT %MD305 : UDINT := 16#00000000;
      MD306 AT %MD306 : UDINT := 16#00000000;
      MD307 AT %MD307 : UDINT := 16#00000000;
      MD308 AT %MD308 : UDINT := 16#00000000;
      MD309 AT %MD309 : UDINT := 16#00000000;
      MD310 AT %MD310 : UDINT := 16#00000000;
      MD311 AT %MD311 : UDINT := 16#00000000;
      MD312 AT %MD312 : UDINT := 16#00000000;
      MD313 AT %MD313 : UDINT := 16#00000000;
      MD314 AT %MD314 : UDINT := 16#00000000;
      MD315 AT %MD315 : UDINT := 16#00000000;
      MD316 AT %MD316 : UDINT := 16#00000000;
      MD317 AT %MD317 : UDINT := 16#00000000;
      MD318 AT %MD318 : UDINT := 16#00000000;
      MD319 AT %MD319 : UDINT := 16#00000000;
      MD320 AT %MD320 : UDINT := 16#00000000;
      MD321 AT %MD321 : UDINT := 16#00000000;
      MD322 AT %MD322 : UDINT := 16#00000000;
      MD323 AT %MD323 : UDINT := 16#00000000;
      MD324 AT %MD324 : UDINT := 16#00000000;
      MD325 AT %MD325 : UDINT := 16#00000000;
      MD326 AT %MD326 : UDINT := 16#00000000;
      MD327 AT %MD327 : UDINT := 16#00000000;
      MD328 AT %MD328 : UDINT := 16#00000000;
      MD329 AT %MD329 : UDINT := 16#00000000;
      MD330 AT %MD330 : UDINT := 16#00000000;
      MD331 AT %MD331 : UDINT := 16#00000000;
      MD332 AT %MD332 : UDINT := 16#00000000;
      MD333 AT %MD333 : UDINT := 16#00000000;
      MD334 AT %MD334 : UDINT := 16#00000000;
      MD335 AT %MD335 : UDINT := 16#00000000;
      MD336 AT %MD336 : UDINT := 16#00000000;
      MD337 AT %MD337 : UDINT := 16#00000000;
      MD338 AT %MD338 : UDINT := 16#00000000;
      MD339 AT %MD339 : UDINT := 16#00000000;
      MD340 AT %MD340 : UDINT := 16#00000000;
      MD341 AT %MD341 : UDINT := 16#00000000;
      MD342 AT %MD342 : UDINT := 16#00000000;
      MD343 AT %MD343 : UDINT := 16#00000000;
      MD344 AT %MD344 : UDINT := 16#00000000;
      MD345 AT %MD345 : UDINT := 16#00000000;
      MD346 AT %MD346 : UDINT := 16#00000000;
      MD347 AT %MD347 : UDINT := 16#00000000;
      MD348 AT %MD348 : UDINT := 16#00000000;
      MD349 AT %MD349 : UDINT := 16#00000000;
      MD350 AT %MD350 : UDINT := 16#00000000;
      MD351 AT %MD351 : UDINT := 16#00000000;
      MD352 AT %MD352 : UDINT := 16#00000000;
      MD353 AT %MD353 : UDINT := 16#00000000;
      MD354 AT %MD354 : UDINT := 16#00000000;
      MD355 AT %MD355 : UDINT := 16#00000000;
      MD356 AT %MD356 : UDINT := 16#00000000;
      MD357 AT %MD357 : UDINT := 16#00000000;
      MD358 AT %MD358 : UDINT := 16#00000000;
      MD359 AT %MD359 : UDINT := 16#00000000;
      MD360 AT %MD360 : UDINT := 16#00000000;
      MD361 AT %MD361 : UDINT := 16#00000000;
      MD362 AT %MD362 : UDINT := 16#00000000;
      MD363 AT %MD363 : UDINT := 16#00000000;
      MD364 AT %MD364 : UDINT := 16#00000000;
      MD365 AT %MD365 : UDINT := 16#00000000;
      MD366 AT %MD366 : UDINT := 16#00000000;
      MD367 AT %MD367 : UDINT := 16#00000000;
      MD368 AT %MD368 : UDINT := 16#00000000;
      MD369 AT %MD369 : UDINT := 16#00000000;
      MD370 AT %MD370 : UDINT := 16#00000000;
      MD371 AT %MD371 : UDINT := 16#00000000;
      MD372 AT %MD372 : UDINT := 16#00000000;
      MD373 AT %MD373 : UDINT := 16#00000000;
      MD374 AT %MD374 : UDINT := 16#00000000;
      MD375 AT %MD375 : UDINT := 16#00000000;
      MD376 AT %MD376 : UDINT := 16#00000000;
      MD377 AT %MD377 : UDINT := 16#00000000;
      MD378 AT %MD378 : UDINT := 16#00000000;
      MD379 AT %MD379 : UDINT := 16#00000000;
      MD380 AT %MD380 : UDINT := 16#00000000;
      MD381 AT %MD381 : UDINT := 16#00000000;
      MD382 AT %MD382 : UDINT := 16#00000000;
      MD383 AT %MD383 : UDINT := 16#00000000;
      MD384 AT %MD384 : UDINT := 16#00000000;
      MD385 AT %MD385 : UDINT := 16#00000000;
      MD386 AT %MD386 : UDINT := 16#00000000;
      MD387 AT %MD387 : UDINT := 16#00000000;
      MD388 AT %MD388 : UDINT := 16#00000000;
      MD389 AT %MD389 : UDINT := 16#00000000;
      MD390 AT %MD390 : UDINT := 16#00000000;
      MD391 AT %MD391 : UDINT := 16#00000000;
      MD392 AT %MD392 : UDINT := 16#00000000;
      MD393 AT %MD393 : UDINT := 16#00000000;
      MD394 AT %MD394 : UDINT := 16#00000000;
      MD395 AT %MD395 : UDINT := 16#00000000;
      MD396 AT %MD396 : UDINT := 16#00000000;
      MD397 AT %MD397 : UDINT := 16#00000000;
      MD398 AT %MD398 : UDINT := 16#00000000;
      MD399 AT %MD399 : UDINT := 16#00000000;
      MD400 AT %MD400 : UDINT := 16#00000000;
      MD401 AT %MD401 : UDINT := 16#00000000;
      MD402 AT %MD402 : UDINT := 16#00000000;
      MD403 AT %MD403 : UDINT := 16#00000000;
      MD404 AT %MD404 : UDINT := 16#00000000;
      MD405 AT %MD405 : UDINT := 16#00000000;
      MD406 AT %MD406 : UDINT := 16#00000000;
      MD407 AT %MD407 : UDINT := 16#00000000;
      MD408 AT %MD408 : UDINT := 16#00000000;
      MD409 AT %MD409 : UDINT := 16#00000000;
      MD410 AT %MD410 : UDINT := 16#00000000;
      MD411 AT %MD411 : UDINT := 16#00000000;
      MD412 AT %MD412 : UDINT := 16#00000000;
      MD413 AT %MD413 : UDINT := 16#00000000;
      MD414 AT %MD414 : UDINT := 16#00000000;
      MD415 AT %MD415 : UDINT := 16#00000000;
      MD416 AT %MD416 : UDINT := 16#00000000;
      MD417 AT %MD417 : UDINT := 16#00000000;
      MD418 AT %MD418 : UDINT := 16#00000000;
      MD419 AT %MD419 : UDINT := 16#00000000;
      MD420 AT %MD420 : UDINT := 16#00000000;
      MD421 AT %MD421 : UDINT := 16#00000000;
      MD422 AT %MD422 : UDINT := 16#00000000;
      MD423 AT %MD423 : UDINT := 16#00000000;
      MD424 AT %MD424 : UDINT := 16#00000000;
      MD425 AT %MD425 : UDINT := 16#00000000;
      MD426 AT %MD426 : UDINT := 16#00000000;
      MD427 AT %MD427 : UDINT := 16#00000000;
      MD428 AT %MD428 : UDINT := 16#00000000;
      MD429 AT %MD429 : UDINT := 16#00000000;
      MD430 AT %MD430 : UDINT := 16#00000000;
      MD431 AT %MD431 : UDINT := 16#00000000;
      MD432 AT %MD432 : UDINT := 16#00000000;
      MD433 AT %MD433 : UDINT := 16#00000000;
      MD434 AT %MD434 : UDINT := 16#00000000;
      MD435 AT %MD435 : UDINT := 16#00000000;
      MD436 AT %MD436 : UDINT := 16#00000000;
      MD437 AT %MD437 : UDINT := 16#00000000;
      MD438 AT %MD438 : UDINT := 16#00000000;
      MD439 AT %MD439 : UDINT := 16#00000000;
      MD440 AT %MD440 : UDINT := 16#00000000;
      MD441 AT %MD441 : UDINT := 16#00000000;
      MD442 AT %MD442 : UDINT := 16#00000000;
      MD443 AT %MD443 : UDINT := 16#00000000;
      MD444 AT %MD444 : UDINT := 16#00000000;
      MD445 AT %MD445 : UDINT := 16#00000000;
      MD446 AT %MD446 : UDINT := 16#00000000;
      MD447 AT %MD447 : UDINT := 16#00000000;
      MD448 AT %MD448 : UDINT := 16#00000000;
      MD449 AT %MD449 : UDINT := 16#00000000;
      MD450 AT %MD450 : UDINT := 16#00000000;
      MD451 AT %MD451 : UDINT := 16#00000000;
      MD452 AT %MD452 : UDINT := 16#00000000;
      MD453 AT %MD453 : UDINT := 16#00000000;
      MD454 AT %MD454 : UDINT := 16#00000000;
      MD455 AT %MD455 : UDINT := 16#00000000;
      MD456 AT %MD456 : UDINT := 16#00000000;
      MD457 AT %MD457 : UDINT := 16#00000000;
      MD458 AT %MD458 : UDINT := 16#00000000;
      MD459 AT %MD459 : UDINT := 16#00000000;
      MD460 AT %MD460 : UDINT := 16#00000000;
      MD461 AT %MD461 : UDINT := 16#00000000;
      MD462 AT %MD462 : UDINT := 16#00000000;
      MD463 AT %MD463 : UDINT := 16#00000000;
      MD464 AT %MD464 : UDINT := 16#00000000;
      MD465 AT %MD465 : UDINT := 16#00000000;
      MD466 AT %MD466 : UDINT := 16#00000000;
      MD467 AT %MD467 : UDINT := 16#00000000;
      MD468 AT %MD468 : UDINT := 16#00000000;
      MD469 AT %MD469 : UDINT := 16#00000000;
      MD470 AT %MD470 : UDINT := 16#00000000;
      MD471 AT %MD471 : UDINT := 16#00000000;
      MD472 AT %MD472 : UDINT := 16#00000000;
      MD473 AT %MD473 : UDINT := 16#00000000;
      MD474 AT %MD474 : UDINT := 16#00000000;
      MD475 AT %MD475 : UDINT := 16#00000000;
      MD476 AT %MD476 : UDINT := 16#00000000;
      MD477 AT %MD477 : UDINT := 16#00000000;
      MD478 AT %MD478 : UDINT := 16#00000000;
      MD479 AT %MD479 : UDINT := 16#00000000;
      MD480 AT %MD480 : UDINT := 16#00000000;
      MD481 AT %MD481 : UDINT := 16#00000000;
      MD482 AT %MD482 : UDINT := 16#00000000;
      MD483 AT %MD483 : UDINT := 16#00000000;
      MD484 AT %MD484 : UDINT := 16#00000000;
      MD485 AT %MD485 : UDINT := 16#00000000;
      MD486 AT %MD486 : UDINT := 16#00000000;
      MD487 AT %MD487 : UDINT := 16#00000000;
      MD488 AT %MD488 : UDINT := 16#00000000;
      MD489 AT %MD489 : UDINT := 16#00000000;
      MD490 AT %MD490 : UDINT := 16#00000000;
      MD491 AT %MD491 : UDINT := 16#00000000;
      MD492 AT %MD492 : UDINT := 16#00000000;
      MD493 AT %MD493 : UDINT := 16#00000000;
      MD494 AT %MD494 : UDINT := 16#00000000;
      MD495 AT %MD495 : UDINT := 16#00000000;
      MD496 AT %MD496 : UDINT := 16#00000000;
      MD497 AT %MD497 : UDINT := 16#00000000;
      MD498 AT %MD498 : UDINT := 16#00000000;
      MD499 AT %MD499 : UDINT := 16#00000000;
      MD500 AT %MD500 : UDINT := 16#00000000;
      MD501 AT %MD501 : UDINT := 16#00000000;
      MD502 AT %MD502 : UDINT := 16#00000000;
      MD503 AT %MD503 : UDINT := 16#00000000;
      MD504 AT %MD504 : UDINT := 16#00000000;
      MD505 AT %MD505 : UDINT := 16#00000000;
      MD506 AT %MD506 : UDINT := 16#00000000;
      MD507 AT %MD507 : UDINT := 16#00000000;
      MD508 AT %MD508 : UDINT := 16#00000000;
      MD509 AT %MD509 : UDINT := 16#00000000;
      MD510 AT %MD510 : UDINT := 16#00000000;
      MD511 AT %MD511 : UDINT := 16#00000000;
      MD512 AT %MD512 : UDINT := 16#00000000;
      MD513 AT %MD513 : UDINT := 16#00000000;
      MD514 AT %MD514 : UDINT := 16#00000000;
      MD515 AT %MD515 : UDINT := 16#00000000;
      MD516 AT %MD516 : UDINT := 16#00000000;
      MD517 AT %MD517 : UDINT := 16#00000000;
      MD518 AT %MD518 : UDINT := 16#00000000;
      MD519 AT %MD519 : UDINT := 16#00000000;
      MD520 AT %MD520 : UDINT := 16#00000000;
      MD521 AT %MD521 : UDINT := 16#00000000;
      MD522 AT %MD522 : UDINT := 16#00000000;
      MD523 AT %MD523 : UDINT := 16#00000000;
      MD524 AT %MD524 : UDINT := 16#00000000;
      MD525 AT %MD525 : UDINT := 16#00000000;
      MD526 AT %MD526 : UDINT := 16#00000000;
      MD527 AT %MD527 : UDINT := 16#00000000;
      MD528 AT %MD528 : UDINT := 16#00000000;
      MD529 AT %MD529 : UDINT := 16#00000000;
      MD530 AT %MD530 : UDINT := 16#00000000;
      MD531 AT %MD531 : UDINT := 16#00000000;
      MD532 AT %MD532 : UDINT := 16#00000000;
      MD533 AT %MD533 : UDINT := 16#00000000;
      MD534 AT %MD534 : UDINT := 16#00000000;
      MD535 AT %MD535 : UDINT := 16#00000000;
      MD536 AT %MD536 : UDINT := 16#00000000;
      MD537 AT %MD537 : UDINT := 16#00000000;
      MD538 AT %MD538 : UDINT := 16#00000000;
      MD539 AT %MD539 : UDINT := 16#00000000;
      MD540 AT %MD540 : UDINT := 16#00000000;
      MD541 AT %MD541 : UDINT := 16#00000000;
      MD542 AT %MD542 : UDINT := 16#00000000;
      MD543 AT %MD543 : UDINT := 16#00000000;
      MD544 AT %MD544 : UDINT := 16#00000000;
      MD545 AT %MD545 : UDINT := 16#00000000;
      MD546 AT %MD546 : UDINT := 16#00000000;
      MD547 AT %MD547 : UDINT := 16#00000000;
      MD548 AT %MD548 : UDINT := 16#00000000;
      MD549 AT %MD549 : UDINT := 16#00000000;
      MD550 AT %MD550 : UDINT := 16#00000000;
      MD551 AT %MD551 : UDINT := 16#00000000;
      MD552 AT %MD552 : UDINT := 16#00000000;
      MD553 AT %MD553 : UDINT := 16#00000000;
      MD554 AT %MD554 : UDINT := 16#00000000;
      MD555 AT %MD555 : UDINT := 16#00000000;
      MD556 AT %MD556 : UDINT := 16#00000000;
      MD557 AT %MD557 : UDINT := 16#00000000;
      MD558 AT %MD558 : UDINT := 16#00000000;
      MD559 AT %MD559 : UDINT := 16#00000000;
      MD560 AT %MD560 : UDINT := 16#00000000;
      MD561 AT %MD561 : UDINT := 16#00000000;
      MD562 AT %MD562 : UDINT := 16#00000000;
      MD563 AT %MD563 : UDINT := 16#00000000;
      MD564 AT %MD564 : UDINT := 16#00000000;
      MD565 AT %MD565 : UDINT := 16#00000000;
      MD566 AT %MD566 : UDINT := 16#00000000;
      MD567 AT %MD567 : UDINT := 16#00000000;
      MD568 AT %MD568 : UDINT := 16#00000000;
      MD569 AT %MD569 : UDINT := 16#00000000;
      MD570 AT %MD570 : UDINT := 16#00000000;
      MD571 AT %MD571 : UDINT := 16#00000000;
      MD572 AT %MD572 : UDINT := 16#00000000;
      MD573 AT %MD573 : UDINT := 16#00000000;
      MD574 AT %MD574 : UDINT := 16#00000000;
      MD575 AT %MD575 : UDINT := 16#00000000;
      MD576 AT %MD576 : UDINT := 16#00000000;
      MD577 AT %MD577 : UDINT := 16#00000000;
      MD578 AT %MD578 : UDINT := 16#00000000;
      MD579 AT %MD579 : UDINT := 16#00000000;
      MD580 AT %MD580 : UDINT := 16#00000000;
      MD581 AT %MD581 : UDINT := 16#00000000;
      MD582 AT %MD582 : UDINT := 16#00000000;
      MD583 AT %MD583 : UDINT := 16#00000000;
      MD584 AT %MD584 : UDINT := 16#00000000;
      MD585 AT %MD585 : UDINT := 16#00000000;
      MD586 AT %MD586 : UDINT := 16#00000000;
      MD587 AT %MD587 : UDINT := 16#00000000;
      MD588 AT %MD588 : UDINT := 16#00000000;
      MD589 AT %MD589 : UDINT := 16#00000000;
      MD590 AT %MD590 : UDINT := 16#00000000;
      MD591 AT %MD591 : UDINT := 16#00000000;
      MD592 AT %MD592 : UDINT := 16#00000000;
      MD593 AT %MD593 : UDINT := 16#00000000;
      MD594 AT %MD594 : UDINT := 16#00000000;
      MD595 AT %MD595 : UDINT := 16#00000000;
      MD596 AT %MD596 : UDINT := 16#00000000;
      MD597 AT %MD597 : UDINT := 16#00000000;
      MD598 AT %MD598 : UDINT := 16#00000000;
      MD599 AT %MD599 : UDINT := 16#00000000;
      MD600 AT %MD600 : UDINT := 16#00000000;
      MD601 AT %MD601 : UDINT := 16#00000000;
      MD602 AT %MD602 : UDINT := 16#00000000;
      MD603 AT %MD603 : UDINT := 16#00000000;
      MD604 AT %MD604 : UDINT := 16#00000000;
      MD605 AT %MD605 : UDINT := 16#00000000;
      MD606 AT %MD606 : UDINT := 16#00000000;
      MD607 AT %MD607 : UDINT := 16#00000000;
      MD608 AT %MD608 : UDINT := 16#00000000;
      MD609 AT %MD609 : UDINT := 16#00000000;
      MD610 AT %MD610 : UDINT := 16#00000000;
      MD611 AT %MD611 : UDINT := 16#00000000;
      MD612 AT %MD612 : UDINT := 16#00000000;
      MD613 AT %MD613 : UDINT := 16#00000000;
      MD614 AT %MD614 : UDINT := 16#00000000;
      MD615 AT %MD615 : UDINT := 16#00000000;
      MD616 AT %MD616 : UDINT := 16#00000000;
      MD617 AT %MD617 : UDINT := 16#00000000;
      MD618 AT %MD618 : UDINT := 16#00000000;
      MD619 AT %MD619 : UDINT := 16#00000000;
      MD620 AT %MD620 : UDINT := 16#00000000;
      MD621 AT %MD621 : UDINT := 16#00000000;
      MD622 AT %MD622 : UDINT := 16#00000000;
      MD623 AT %MD623 : UDINT := 16#00000000;
      MD624 AT %MD624 : UDINT := 16#00000000;
      MD625 AT %MD625 : UDINT := 16#00000000;
      MD626 AT %MD626 : UDINT := 16#00000000;
      MD627 AT %MD627 : UDINT := 16#00000000;
      MD628 AT %MD628 : UDINT := 16#00000000;
      MD629 AT %MD629 : UDINT := 16#00000000;
      MD630 AT %MD630 : UDINT := 16#00000000;
      MD631 AT %MD631 : UDINT := 16#00000000;
      MD632 AT %MD632 : UDINT := 16#00000000;
      MD633 AT %MD633 : UDINT := 16#00000000;
      MD634 AT %MD634 : UDINT := 16#00000000;
      MD635 AT %MD635 : UDINT := 16#00000000;
      MD636 AT %MD636 : UDINT := 16#00000000;
      MD637 AT %MD637 : UDINT := 16#00000000;
      MD638 AT %MD638 : UDINT := 16#00000000;
      MD639 AT %MD639 : UDINT := 16#00000000;
      MD640 AT %MD640 : UDINT := 16#00000000;
      MD641 AT %MD641 : UDINT := 16#00000000;
      MD642 AT %MD642 : UDINT := 16#00000000;
      MD643 AT %MD643 : UDINT := 16#00000000;
      MD644 AT %MD644 : UDINT := 16#00000000;
      MD645 AT %MD645 : UDINT := 16#00000000;
      MD646 AT %MD646 : UDINT := 16#00000000;
      MD647 AT %MD647 : UDINT := 16#00000000;
      MD648 AT %MD648 : UDINT := 16#00000000;
      MD649 AT %MD649 : UDINT := 16#00000000;
      MD650 AT %MD650 : UDINT := 16#00000000;
      MD651 AT %MD651 : UDINT := 16#00000000;
      MD652 AT %MD652 : UDINT := 16#00000000;
      MD653 AT %MD653 : UDINT := 16#00000000;
      MD654 AT %MD654 : UDINT := 16#00000000;
      MD655 AT %MD655 : UDINT := 16#00000000;
      MD656 AT %MD656 : UDINT := 16#00000000;
      MD657 AT %MD657 : UDINT := 16#00000000;
      MD658 AT %MD658 : UDINT := 16#00000000;
      MD659 AT %MD659 : UDINT := 16#00000000;
      MD660 AT %MD660 : UDINT := 16#00000000;
      MD661 AT %MD661 : UDINT := 16#00000000;
      MD662 AT %MD662 : UDINT := 16#00000000;
      MD663 AT %MD663 : UDINT := 16#00000000;
      MD664 AT %MD664 : UDINT := 16#00000000;
      MD665 AT %MD665 : UDINT := 16#00000000;
      MD666 AT %MD666 : UDINT := 16#00000000;
      MD667 AT %MD667 : UDINT := 16#00000000;
      MD668 AT %MD668 : UDINT := 16#00000000;
      MD669 AT %MD669 : UDINT := 16#00000000;
      MD670 AT %MD670 : UDINT := 16#00000000;
      MD671 AT %MD671 : UDINT := 16#00000000;
      MD672 AT %MD672 : UDINT := 16#00000000;
      MD673 AT %MD673 : UDINT := 16#00000000;
      MD674 AT %MD674 : UDINT := 16#00000000;
      MD675 AT %MD675 : UDINT := 16#00000000;
      MD676 AT %MD676 : UDINT := 16#00000000;
      MD677 AT %MD677 : UDINT := 16#00000000;
      MD678 AT %MD678 : UDINT := 16#00000000;
      MD679 AT %MD679 : UDINT := 16#00000000;
      MD680 AT %MD680 : UDINT := 16#00000000;
      MD681 AT %MD681 : UDINT := 16#00000000;
      MD682 AT %MD682 : UDINT := 16#00000000;
      MD683 AT %MD683 : UDINT := 16#00000000;
      MD684 AT %MD684 : UDINT := 16#00000000;
      MD685 AT %MD685 : UDINT := 16#00000000;
      MD686 AT %MD686 : UDINT := 16#00000000;
      MD687 AT %MD687 : UDINT := 16#00000000;
      MD688 AT %MD688 : UDINT := 16#00000000;
      MD689 AT %MD689 : UDINT := 16#00000000;
      MD690 AT %MD690 : UDINT := 16#00000000;
      MD691 AT %MD691 : UDINT := 16#00000000;
      MD692 AT %MD692 : UDINT := 16#00000000;
      MD693 AT %MD693 : UDINT := 16#00000000;
      MD694 AT %MD694 : UDINT := 16#00000000;
      MD695 AT %MD695 : UDINT := 16#00000000;
      MD696 AT %MD696 : UDINT := 16#00000000;
      MD697 AT %MD697 : UDINT := 16#00000000;
      MD698 AT %MD698 : UDINT := 16#00000000;
      MD699 AT %MD699 : UDINT := 16#00000000;
      MD700 AT %MD700 : UDINT := 16#00000000;
      MD701 AT %MD701 : UDINT := 16#00000000;
      MD702 AT %MD702 : UDINT := 16#00000000;
      MD703 AT %MD703 : UDINT := 16#00000000;
      MD704 AT %MD704 : UDINT := 16#00000000;
      MD705 AT %MD705 : UDINT := 16#00000000;
      MD706 AT %MD706 : UDINT := 16#00000000;
      MD707 AT %MD707 : UDINT := 16#00000000;
      MD708 AT %MD708 : UDINT := 16#00000000;
      MD709 AT %MD709 : UDINT := 16#00000000;
      MD710 AT %MD710 : UDINT := 16#00000000;
      MD711 AT %MD711 : UDINT := 16#00000000;
      MD712 AT %MD712 : UDINT := 16#00000000;
      MD713 AT %MD713 : UDINT := 16#00000000;
      MD714 AT %MD714 : UDINT := 16#00000000;
      MD715 AT %MD715 : UDINT := 16#00000000;
      MD716 AT %MD716 : UDINT := 16#00000000;
      MD717 AT %MD717 : UDINT := 16#00000000;
      MD718 AT %MD718 : UDINT := 16#00000000;
      MD719 AT %MD719 : UDINT := 16#00000000;
      MD720 AT %MD720 : UDINT := 16#00000000;
      MD721 AT %MD721 : UDINT := 16#00000000;
      MD722 AT %MD722 : UDINT := 16#00000000;
      MD723 AT %MD723 : UDINT := 16#00000000;
      MD724 AT %MD724 : UDINT := 16#00000000;
      MD725 AT %MD725 : UDINT := 16#00000000;
      MD726 AT %MD726 : UDINT := 16#00000000;
      MD727 AT %MD727 : UDINT := 16#00000000;
      MD728 AT %MD728 : UDINT := 16#00000000;
      MD729 AT %MD729 : UDINT := 16#00000000;
      MD730 AT %MD730 : UDINT := 16#00000000;
      MD731 AT %MD731 : UDINT := 16#00000000;
      MD732 AT %MD732 : UDINT := 16#00000000;
      MD733 AT %MD733 : UDINT := 16#00000000;
      MD734 AT %MD734 : UDINT := 16#00000000;
      MD735 AT %MD735 : UDINT := 16#00000000;
      MD736 AT %MD736 : UDINT := 16#00000000;
      MD737 AT %MD737 : UDINT := 16#00000000;
      MD738 AT %MD738 : UDINT := 16#00000000;
      MD739 AT %MD739 : UDINT := 16#00000000;
      MD740 AT %MD740 : UDINT := 16#00000000;
      MD741 AT %MD741 : UDINT := 16#00000000;
      MD742 AT %MD742 : UDINT := 16#00000000;
      MD743 AT %MD743 : UDINT := 16#00000000;
      MD744 AT %MD744 : UDINT := 16#00000000;
      MD745 AT %MD745 : UDINT := 16#00000000;
      MD746 AT %MD746 : UDINT := 16#00000000;
      MD747 AT %MD747 : UDINT := 16#00000000;
      MD748 AT %MD748 : UDINT := 16#00000000;
      MD749 AT %MD749 : UDINT := 16#00000000;
      MD750 AT %MD750 : UDINT := 16#00000000;
      MD751 AT %MD751 : UDINT := 16#00000000;
      MD752 AT %MD752 : UDINT := 16#00000000;
      MD753 AT %MD753 : UDINT := 16#00000000;
      MD754 AT %MD754 : UDINT := 16#00000000;
      MD755 AT %MD755 : UDINT := 16#00000000;
      MD756 AT %MD756 : UDINT := 16#00000000;
      MD757 AT %MD757 : UDINT := 16#00000000;
      MD758 AT %MD758 : UDINT := 16#00000000;
      MD759 AT %MD759 : UDINT := 16#00000000;
      MD760 AT %MD760 : UDINT := 16#00000000;
      MD761 AT %MD761 : UDINT := 16#00000000;
      MD762 AT %MD762 : UDINT := 16#00000000;
      MD763 AT %MD763 : UDINT := 16#00000000;
      MD764 AT %MD764 : UDINT := 16#00000000;
      MD765 AT %MD765 : UDINT := 16#00000000;
      MD766 AT %MD766 : UDINT := 16#00000000;
      MD767 AT %MD767 : UDINT := 16#00000000;
      MD768 AT %MD768 : UDINT := 16#00000000;
      MD769 AT %MD769 : UDINT := 16#00000000;
      MD770 AT %MD770 : UDINT := 16#00000000;
      MD771 AT %MD771 : UDINT := 16#00000000;
      MD772 AT %MD772 : UDINT := 16#00000000;
      MD773 AT %MD773 : UDINT := 16#00000000;
      MD774 AT %MD774 : UDINT := 16#00000000;
      MD775 AT %MD775 : UDINT := 16#00000000;
      MD776 AT %MD776 : UDINT := 16#00000000;
      MD777 AT %MD777 : UDINT := 16#00000000;
      MD778 AT %MD778 : UDINT := 16#00000000;
      MD779 AT %MD779 : UDINT := 16#00000000;
      MD780 AT %MD780 : UDINT := 16#00000000;
      MD781 AT %MD781 : UDINT := 16#00000000;
      MD782 AT %MD782 : UDINT := 16#00000000;
      MD783 AT %MD783 : UDINT := 16#00000000;
      MD784 AT %MD784 : UDINT := 16#00000000;
      MD785 AT %MD785 : UDINT := 16#00000000;
      MD786 AT %MD786 : UDINT := 16#00000000;
      MD787 AT %MD787 : UDINT := 16#00000000;
      MD788 AT %MD788 : UDINT := 16#00000000;
      MD789 AT %MD789 : UDINT := 16#00000000;
      MD790 AT %MD790 : UDINT := 16#00000000;
      MD791 AT %MD791 : UDINT := 16#00000000;
      MD792 AT %MD792 : UDINT := 16#00000000;
      MD793 AT %MD793 : UDINT := 16#00000000;
      MD794 AT %MD794 : UDINT := 16#00000000;
      MD795 AT %MD795 : UDINT := 16#00000000;
      MD796 AT %MD796 : UDINT := 16#00000000;
      MD797 AT %MD797 : UDINT := 16#00000000;
      MD798 AT %MD798 : UDINT := 16#00000000;
      MD799 AT %MD799 : UDINT := 16#00000000;
      MD800 AT %MD800 : UDINT := 16#00000000;
      MD801 AT %MD801 : UDINT := 16#00000000;
      MD802 AT %MD802 : UDINT := 16#00000000;
      MD803 AT %MD803 : UDINT := 16#00000000;
      MD804 AT %MD804 : UDINT := 16#00000000;
      MD805 AT %MD805 : UDINT := 16#00000000;
      MD806 AT %MD806 : UDINT := 16#00000000;
      MD807 AT %MD807 : UDINT := 16#00000000;
      MD808 AT %MD808 : UDINT := 16#00000000;
      MD809 AT %MD809 : UDINT := 16#00000000;
      MD810 AT %MD810 : UDINT := 16#00000000;
      MD811 AT %MD811 : UDINT := 16#00000000;
      MD812 AT %MD812 : UDINT := 16#00000000;
      MD813 AT %MD813 : UDINT := 16#00000000;
      MD814 AT %MD814 : UDINT := 16#00000000;
      MD815 AT %MD815 : UDINT := 16#00000000;
      MD816 AT %MD816 : UDINT := 16#00000000;
      MD817 AT %MD817 : UDINT := 16#00000000;
      MD818 AT %MD818 : UDINT := 16#00000000;
      MD819 AT %MD819 : UDINT := 16#00000000;
      MD820 AT %MD820 : UDINT := 16#00000000;
      MD821 AT %MD821 : UDINT := 16#00000000;
      MD822 AT %MD822 : UDINT := 16#00000000;
      MD823 AT %MD823 : UDINT := 16#00000000;
      MD824 AT %MD824 : UDINT := 16#00000000;
      MD825 AT %MD825 : UDINT := 16#00000000;
      MD826 AT %MD826 : UDINT := 16#00000000;
      MD827 AT %MD827 : UDINT := 16#00000000;
      MD828 AT %MD828 : UDINT := 16#00000000;
      MD829 AT %MD829 : UDINT := 16#00000000;
      MD830 AT %MD830 : UDINT := 16#00000000;
      MD831 AT %MD831 : UDINT := 16#00000000;
      MD832 AT %MD832 : UDINT := 16#00000000;
      MD833 AT %MD833 : UDINT := 16#00000000;
      MD834 AT %MD834 : UDINT := 16#00000000;
      MD835 AT %MD835 : UDINT := 16#00000000;
      MD836 AT %MD836 : UDINT := 16#00000000;
      MD837 AT %MD837 : UDINT := 16#00000000;
      MD838 AT %MD838 : UDINT := 16#00000000;
      MD839 AT %MD839 : UDINT := 16#00000000;
      MD840 AT %MD840 : UDINT := 16#00000000;
      MD841 AT %MD841 : UDINT := 16#00000000;
      MD842 AT %MD842 : UDINT := 16#00000000;
      MD843 AT %MD843 : UDINT := 16#00000000;
      MD844 AT %MD844 : UDINT := 16#00000000;
      MD845 AT %MD845 : UDINT := 16#00000000;
      MD846 AT %MD846 : UDINT := 16#00000000;
      MD847 AT %MD847 : UDINT := 16#00000000;
      MD848 AT %MD848 : UDINT := 16#00000000;
      MD849 AT %MD849 : UDINT := 16#00000000;
      MD850 AT %MD850 : UDINT := 16#00000000;
      MD851 AT %MD851 : UDINT := 16#00000000;
      MD852 AT %MD852 : UDINT := 16#00000000;
      MD853 AT %MD853 : UDINT := 16#00000000;
      MD854 AT %MD854 : UDINT := 16#00000000;
      MD855 AT %MD855 : UDINT := 16#00000000;
      MD856 AT %MD856 : UDINT := 16#00000000;
      MD857 AT %MD857 : UDINT := 16#00000000;
      MD858 AT %MD858 : UDINT := 16#00000000;
      MD859 AT %MD859 : UDINT := 16#00000000;
      MD860 AT %MD860 : UDINT := 16#00000000;
      MD861 AT %MD861 : UDINT := 16#00000000;
      MD862 AT %MD862 : UDINT := 16#00000000;
      MD863 AT %MD863 : UDINT := 16#00000000;
      MD864 AT %MD864 : UDINT := 16#00000000;
      MD865 AT %MD865 : UDINT := 16#00000000;
      MD866 AT %MD866 : UDINT := 16#00000000;
      MD867 AT %MD867 : UDINT := 16#00000000;
      MD868 AT %MD868 : UDINT := 16#00000000;
      MD869 AT %MD869 : UDINT := 16#00000000;
      MD870 AT %MD870 : UDINT := 16#00000000;
      MD871 AT %MD871 : UDINT := 16#00000000;
      MD872 AT %MD872 : UDINT := 16#00000000;
      MD873 AT %MD873 : UDINT := 16#00000000;
      MD874 AT %MD874 : UDINT := 16#00000000;
      MD875 AT %MD875 : UDINT := 16#00000000;
      MD876 AT %MD876 : UDINT := 16#00000000;
      MD877 AT %MD877 : UDINT := 16#00000000;
      MD878 AT %MD878 : UDINT := 16#00000000;
      MD879 AT %MD879 : UDINT := 16#00000000;
      MD880 AT %MD880 : UDINT := 16#00000000;
      MD881 AT %MD881 : UDINT := 16#00000000;
      MD882 AT %MD882 : UDINT := 16#00000000;
      MD883 AT %MD883 : UDINT := 16#00000000;
      MD884 AT %MD884 : UDINT := 16#00000000;
      MD885 AT %MD885 : UDINT := 16#00000000;
      MD886 AT %MD886 : UDINT := 16#00000000;
      MD887 AT %MD887 : UDINT := 16#00000000;
      MD888 AT %MD888 : UDINT := 16#00000000;
      MD889 AT %MD889 : UDINT := 16#00000000;
      MD890 AT %MD890 : UDINT := 16#00000000;
      MD891 AT %MD891 : UDINT := 16#00000000;
      MD892 AT %MD892 : UDINT := 16#00000000;
      MD893 AT %MD893 : UDINT := 16#00000000;
      MD894 AT %MD894 : UDINT := 16#00000000;
      MD895 AT %MD895 : UDINT := 16#00000000;
      MD896 AT %MD896 : UDINT := 16#00000000;
      MD897 AT %MD897 : UDINT := 16#00000000;
      MD898 AT %MD898 : UDINT := 16#00000000;
      MD899 AT %MD899 : UDINT := 16#00000000;
      MD900 AT %MD900 : UDINT := 16#00000000;
      MD901 AT %MD901 : UDINT := 16#00000000;
      MD902 AT %MD902 : UDINT := 16#00000000;
      MD903 AT %MD903 : UDINT := 16#00000000;
      MD904 AT %MD904 : UDINT := 16#00000000;
      MD905 AT %MD905 : UDINT := 16#00000000;
      MD906 AT %MD906 : UDINT := 16#00000000;
      MD907 AT %MD907 : UDINT := 16#00000000;
      MD908 AT %MD908 : UDINT := 16#00000000;
      MD909 AT %MD909 : UDINT := 16#00000000;
      MD910 AT %MD910 : UDINT := 16#00000000;
      MD911 AT %MD911 : UDINT := 16#00000000;
      MD912 AT %MD912 : UDINT := 16#00000000;
      MD913 AT %MD913 : UDINT := 16#00000000;
      MD914 AT %MD914 : UDINT := 16#00000000;
      MD915 AT %MD915 : UDINT := 16#00000000;
      MD916 AT %MD916 : UDINT := 16#00000000;
      MD917 AT %MD917 : UDINT := 16#00000000;
      MD918 AT %MD918 : UDINT := 16#00000000;
      MD919 AT %MD919 : UDINT := 16#00000000;
      MD920 AT %MD920 : UDINT := 16#00000000;
      MD921 AT %MD921 : UDINT := 16#00000000;
      MD922 AT %MD922 : UDINT := 16#00000000;
      MD923 AT %MD923 : UDINT := 16#00000000;
      MD924 AT %MD924 : UDINT := 16#00000000;
      MD925 AT %MD925 : UDINT := 16#00000000;
      MD926 AT %MD926 : UDINT := 16#00000000;
      MD927 AT %MD927 : UDINT := 16#00000000;
      MD928 AT %MD928 : UDINT := 16#00000000;
      MD929 AT %MD929 : UDINT := 16#00000000;
      MD930 AT %MD930 : UDINT := 16#00000000;
      MD931 AT %MD931 : UDINT := 16#00000000;
      MD932 AT %MD932 : UDINT := 16#00000000;
      MD933 AT %MD933 : UDINT := 16#00000000;
      MD934 AT %MD934 : UDINT := 16#00000000;
      MD935 AT %MD935 : UDINT := 16#00000000;
      MD936 AT %MD936 : UDINT := 16#00000000;
      MD937 AT %MD937 : UDINT := 16#00000000;
      MD938 AT %MD938 : UDINT := 16#00000000;
      MD939 AT %MD939 : UDINT := 16#00000000;
      MD940 AT %MD940 : UDINT := 16#00000000;
      MD941 AT %MD941 : UDINT := 16#00000000;
      MD942 AT %MD942 : UDINT := 16#00000000;
      MD943 AT %MD943 : UDINT := 16#00000000;
      MD944 AT %MD944 : UDINT := 16#00000000;
      MD945 AT %MD945 : UDINT := 16#00000000;
      MD946 AT %MD946 : UDINT := 16#00000000;
      MD947 AT %MD947 : UDINT := 16#00000000;
      MD948 AT %MD948 : UDINT := 16#00000000;
      MD949 AT %MD949 : UDINT := 16#00000000;
      MD950 AT %MD950 : UDINT := 16#00000000;
      MD951 AT %MD951 : UDINT := 16#00000000;
      MD952 AT %MD952 : UDINT := 16#00000000;
      MD953 AT %MD953 : UDINT := 16#00000000;
      MD954 AT %MD954 : UDINT := 16#00000000;
      MD955 AT %MD955 : UDINT := 16#00000000;
      MD956 AT %MD956 : UDINT := 16#00000000;
      MD957 AT %MD957 : UDINT := 16#00000000;
      MD958 AT %MD958 : UDINT := 16#00000000;
      MD959 AT %MD959 : UDINT := 16#00000000;
      MD960 AT %MD960 : UDINT := 16#00000000;
      MD961 AT %MD961 : UDINT := 16#00000000;
      MD962 AT %MD962 : UDINT := 16#00000000;
      MD963 AT %MD963 : UDINT := 16#00000000;
      MD964 AT %MD964 : UDINT := 16#00000000;
      MD965 AT %MD965 : UDINT := 16#00000000;
      MD966 AT %MD966 : UDINT := 16#00000000;
      MD967 AT %MD967 : UDINT := 16#00000000;
      MD968 AT %MD968 : UDINT := 16#00000000;
      MD969 AT %MD969 : UDINT := 16#00000000;
      MD970 AT %MD970 : UDINT := 16#00000000;
      MD971 AT %MD971 : UDINT := 16#00000000;
      MD972 AT %MD972 : UDINT := 16#00000000;
      MD973 AT %MD973 : UDINT := 16#00000000;
      MD974 AT %MD974 : UDINT := 16#00000000;
      MD975 AT %MD975 : UDINT := 16#00000000;
      MD976 AT %MD976 : UDINT := 16#00000000;
      MD977 AT %MD977 : UDINT := 16#00000000;
      MD978 AT %MD978 : UDINT := 16#00000000;
      MD979 AT %MD979 : UDINT := 16#00000000;
      MD980 AT %MD980 : UDINT := 16#00000000;
      MD981 AT %MD981 : UDINT := 16#00000000;
      MD982 AT %MD982 : UDINT := 16#00000000;
      MD983 AT %MD983 : UDINT := 16#00000000;
      MD984 AT %MD984 : UDINT := 16#00000000;
      MD985 AT %MD985 : UDINT := 16#00000000;
      MD986 AT %MD986 : UDINT := 16#00000000;
      MD987 AT %MD987 : UDINT := 16#00000000;
      MD988 AT %MD988 : UDINT := 16#00000000;
      MD989 AT %MD989 : UDINT := 16#00000000;
      MD990 AT %MD990 : UDINT := 16#00000000;
      MD991 AT %MD991 : UDINT := 16#00000000;
      MD992 AT %MD992 : UDINT := 16#00000000;
      MD993 AT %MD993 : UDINT := 16#00000000;
      MD994 AT %MD994 : UDINT := 16#00000000;
      MD995 AT %MD995 : UDINT := 16#00000000;
      MD996 AT %MD996 : UDINT := 16#00000000;
      MD997 AT %MD997 : UDINT := 16#00000000;
      MD998 AT %MD998 : UDINT := 16#00000000;
      MD999 AT %MD999 : UDINT := 16#00000000;
      MD1000 AT %MD1000 : UDINT := 16#00000000;
      MD1001 AT %MD1001 : UDINT := 16#00000000;
      MD1002 AT %MD1002 : UDINT := 16#00000000;
      MD1003 AT %MD1003 : UDINT := 16#00000000;
      MD1004 AT %MD1004 : UDINT := 16#00000000;
      MD1005 AT %MD1005 : UDINT := 16#00000000;
      MD1006 AT %MD1006 : UDINT := 16#00000000;
      MD1007 AT %MD1007 : UDINT := 16#00000000;
      MD1008 AT %MD1008 : UDINT := 16#00000000;
      MD1009 AT %MD1009 : UDINT := 16#00000000;
      MD1010 AT %MD1010 : UDINT := 16#00000000;
      MD1011 AT %MD1011 : UDINT := 16#00000000;
      MD1012 AT %MD1012 : UDINT := 16#00000000;
      MD1013 AT %MD1013 : UDINT := 16#00000000;
      MD1014 AT %MD1014 : UDINT := 16#00000000;
      MD1015 AT %MD1015 : UDINT := 16#00000000;
      MD1016 AT %MD1016 : UDINT := 16#00000000;
      MD1017 AT %MD1017 : UDINT := 16#00000000;
      MD1018 AT %MD1018 : UDINT := 16#00000000;
      MD1019 AT %MD1019 : UDINT := 16#00000000;
      MD1020 AT %MD1020 : UDINT := 16#00000000;
      MD1021 AT %MD1021 : UDINT := 16#00000000;
      MD1022 AT %MD1022 : UDINT := 16#00000000;
      MD1023 AT %MD1023 : UDINT := 16#00000000;
    END_VAR
    VAR_GLOBAL
      ML0 AT %ML0 : ULINT := 16#0123456789ABCDEF;
      ML1 AT %ML1 : ULINT := 16#0123456789ABCDEF;
      ML2 AT %ML2 : ULINT := 16#0123456789ABCDEF;
      ML3 AT %ML3 : ULINT := 16#0123456789ABCDEF;
      ML4 AT %ML4 : ULINT := 16#0123456789ABCDEF;
      ML5 AT %ML5 : ULINT := 16#0123456789ABCDEF;
      ML6 AT %ML6 : ULINT := 16#0123456789ABCDEF;
      ML7 AT %ML7 : ULINT := 16#0123456789ABCDEF;
      ML8 AT %ML8 : ULINT := 16#0123456789ABCDEF;
      ML9 AT %ML9 : ULINT := 16#0123456789ABCDEF;
      ML10 AT %ML10 : ULINT := 16#0123456789ABCDEF;
      ML11 AT %ML11 : ULINT := 16#0123456789ABCDEF;
      ML12 AT %ML12 : ULINT := 16#0123456789ABCDEF;
      ML13 AT %ML13 : ULINT := 16#0123456789ABCDEF;
      ML14 AT %ML14 : ULINT := 16#0123456789ABCDEF;
      ML15 AT %ML15 : ULINT := 16#0123456789ABCDEF;
      ML16 AT %ML16 : ULINT := 16#0123456789ABCDEF;
      ML17 AT %ML17 : ULINT := 16#0123456789ABCDEF;
      ML18 AT %ML18 : ULINT := 16#0123456789ABCDEF;
      ML19 AT %ML19 : ULINT := 16#0123456789ABCDEF;
      ML20 AT %ML20 : ULINT := 16#0123456789ABCDEF;
      ML21 AT %ML21 : ULINT := 16#0123456789ABCDEF;
      ML22 AT %ML22 : ULINT := 16#0123456789ABCDEF;
      ML23 AT %ML23 : ULINT := 16#0123456789ABCDEF;
      ML24 AT %ML24 : ULINT := 16#0123456789ABCDEF;
      ML25 AT %ML25 : ULINT := 16#0123456789ABCDEF;
      ML26 AT %ML26 : ULINT := 16#0123456789ABCDEF;
      ML27 AT %ML27 : ULINT := 16#0123456789ABCDEF;
      ML28 AT %ML28 : ULINT := 16#0123456789ABCDEF;
      ML29 AT %ML29 : ULINT := 16#0123456789ABCDEF;
      ML30 AT %ML30 : ULINT := 16#0123456789ABCDEF;
      ML31 AT %ML31 : ULINT := 16#0123456789ABCDEF;
      ML32 AT %ML32 : ULINT := 16#0123456789ABCDEF;
      ML33 AT %ML33 : ULINT := 16#0123456789ABCDEF;
      ML34 AT %ML34 : ULINT := 16#0123456789ABCDEF;
      ML35 AT %ML35 : ULINT := 16#0123456789ABCDEF;
      ML36 AT %ML36 : ULINT := 16#0123456789ABCDEF;
      ML37 AT %ML37 : ULINT := 16#0123456789ABCDEF;
      ML38 AT %ML38 : ULINT := 16#0123456789ABCDEF;
      ML39 AT %ML39 : ULINT := 16#0123456789ABCDEF;
      ML40 AT %ML40 : ULINT := 16#0123456789ABCDEF;
      ML41 AT %ML41 : ULINT := 16#0123456789ABCDEF;
      ML42 AT %ML42 : ULINT := 16#0123456789ABCDEF;
      ML43 AT %ML43 : ULINT := 16#0123456789ABCDEF;
      ML44 AT %ML44 : ULINT := 16#0123456789ABCDEF;
      ML45 AT %ML45 : ULINT := 16#0123456789ABCDEF;
      ML46 AT %ML46 : ULINT := 16#0123456789ABCDEF;
      ML47 AT %ML47 : ULINT := 16#0123456789ABCDEF;
      ML48 AT %ML48 : ULINT := 16#0123456789ABCDEF;
      ML49 AT %ML49 : ULINT := 16#0123456789ABCDEF;
      ML50 AT %ML50 : ULINT := 16#0123456789ABCDEF;
      ML51 AT %ML51 : ULINT := 16#0123456789ABCDEF;
      ML52 AT %ML52 : ULINT := 16#0123456789ABCDEF;
      ML53 AT %ML53 : ULINT := 16#0123456789ABCDEF;
      ML54 AT %ML54 : ULINT := 16#0123456789ABCDEF;
      ML55 AT %ML55 : ULINT := 16#0123456789ABCDEF;
      ML56 AT %ML56 : ULINT := 16#0123456789ABCDEF;
      ML57 AT %ML57 : ULINT := 16#0123456789ABCDEF;
      ML58 AT %ML58 : ULINT := 16#0123456789ABCDEF;
      ML59 AT %ML59 : ULINT := 16#0123456789ABCDEF;
      ML60 AT %ML60 : ULINT := 16#0123456789ABCDEF;
      ML61 AT %ML61 : ULINT := 16#0123456789ABCDEF;
      ML62 AT %ML62 : ULINT := 16#0123456789ABCDEF;
      ML63 AT %ML63 : ULINT := 16#0123456789ABCDEF;
      ML64 AT %ML64 : ULINT := 16#0123456789ABCDEF;
      ML65 AT %ML65 : ULINT := 16#0123456789ABCDEF;
      ML66 AT %ML66 : ULINT := 16#0123456789ABCDEF;
      ML67 AT %ML67 : ULINT := 16#0123456789ABCDEF;
      ML68 AT %ML68 : ULINT := 16#0123456789ABCDEF;
      ML69 AT %ML69 : ULINT := 16#0123456789ABCDEF;
      ML70 AT %ML70 : ULINT := 16#0123456789ABCDEF;
      ML71 AT %ML71 : ULINT := 16#0123456789ABCDEF;
      ML72 AT %ML72 : ULINT := 16#0123456789ABCDEF;
      ML73 AT %ML73 : ULINT := 16#0123456789ABCDEF;
      ML74 AT %ML74 : ULINT := 16#0123456789ABCDEF;
      ML75 AT %ML75 : ULINT := 16#0123456789ABCDEF;
      ML76 AT %ML76 : ULINT := 16#0123456789ABCDEF;
      ML77 AT %ML77 : ULINT := 16#0123456789ABCDEF;
      ML78 AT %ML78 : ULINT := 16#0123456789ABCDEF;
      ML79 AT %ML79 : ULINT := 16#0123456789ABCDEF;
      ML80 AT %ML80 : ULINT := 16#0123456789ABCDEF;
      ML81 AT %ML81 : ULINT := 16#0123456789ABCDEF;
      ML82 AT %ML82 : ULINT := 16#0123456789ABCDEF;
      ML83 AT %ML83 : ULINT := 16#0123456789ABCDEF;
      ML84 AT %ML84 : ULINT := 16#0123456789ABCDEF;
      ML85 AT %ML85 : ULINT := 16#0123456789ABCDEF;
      ML86 AT %ML86 : ULINT := 16#0123456789ABCDEF;
      ML87 AT %ML87 : ULINT := 16#0123456789ABCDEF;
      ML88 AT %ML88 : ULINT := 16#0123456789ABCDEF;
      ML89 AT %ML89 : ULINT := 16#0123456789ABCDEF;
      ML90 AT %ML90 : ULINT := 16#0123456789ABCDEF;
      ML91 AT %ML91 : ULINT := 16#0123456789ABCDEF;
      ML92 AT %ML92 : ULINT := 16#0123456789ABCDEF;
      ML93 AT %ML93 : ULINT := 16#0123456789ABCDEF;
      ML94 AT %ML94 : ULINT := 16#0123456789ABCDEF;
      ML95 AT %ML95 : ULINT := 16#0123456789ABCDEF;
      ML96 AT %ML96 : ULINT := 16#0123456789ABCDEF;
      ML97 AT %ML97 : ULINT := 16#0123456789ABCDEF;
      ML98 AT %ML98 : ULINT := 16#0123456789ABCDEF;
      ML99 AT %ML99 : ULINT := 16#0123456789ABCDEF;
      ML100 AT %ML100 : ULINT := 16#0123456789ABCDEF;
      ML101 AT %ML101 : ULINT := 16#0123456789ABCDEF;
      ML102 AT %ML102 : ULINT := 16#0123456789ABCDEF;
      ML103 AT %ML103 : ULINT := 16#0123456789ABCDEF;
      ML104 AT %ML104 : ULINT := 16#0123456789ABCDEF;
      ML105 AT %ML105 : ULINT := 16#0123456789ABCDEF;
      ML106 AT %ML106 : ULINT := 16#0123456789ABCDEF;
      ML107 AT %ML107 : ULINT := 16#0123456789ABCDEF;
      ML108 AT %ML108 : ULINT := 16#0123456789ABCDEF;
      ML109 AT %ML109 : ULINT := 16#0123456789ABCDEF;
      ML110 AT %ML110 : ULINT := 16#0123456789ABCDEF;
      ML111 AT %ML111 : ULINT := 16#0123456789ABCDEF;
      ML112 AT %ML112 : ULINT := 16#0123456789ABCDEF;
      ML113 AT %ML113 : ULINT := 16#0123456789ABCDEF;
      ML114 AT %ML114 : ULINT := 16#0123456789ABCDEF;
      ML115 AT %ML115 : ULINT := 16#0123456789ABCDEF;
      ML116 AT %ML116 : ULINT := 16#0123456789ABCDEF;
      ML117 AT %ML117 : ULINT := 16#0123456789ABCDEF;
      ML118 AT %ML118 : ULINT := 16#0123456789ABCDEF;
      ML119 AT %ML119 : ULINT := 16#0123456789ABCDEF;
      ML120 AT %ML120 : ULINT := 16#0123456789ABCDEF;
      ML121 AT %ML121 : ULINT := 16#0123456789ABCDEF;
      ML122 AT %ML122 : ULINT := 16#0123456789ABCDEF;
      ML123 AT %ML123 : ULINT := 16#0123456789ABCDEF;
      ML124 AT %ML124 : ULINT := 16#0123456789ABCDEF;
      ML125 AT %ML125 : ULINT := 16#0123456789ABCDEF;
      ML126 AT %ML126 : ULINT := 16#0123456789ABCDEF;
      ML127 AT %ML127 : ULINT := 16#0123456789ABCDEF;
      ML128 AT %ML128 : ULINT := 16#0123456789ABCDEF;
      ML129 AT %ML129 : ULINT := 16#0123456789ABCDEF;
      ML130 AT %ML130 : ULINT := 16#0123456789ABCDEF;
      ML131 AT %ML131 : ULINT := 16#0123456789ABCDEF;
      ML132 AT %ML132 : ULINT := 16#0123456789ABCDEF;
      ML133 AT %ML133 : ULINT := 16#0123456789ABCDEF;
      ML134 AT %ML134 : ULINT := 16#0123456789ABCDEF;
      ML135 AT %ML135 : ULINT := 16#0123456789ABCDEF;
      ML136 AT %ML136 : ULINT := 16#0123456789ABCDEF;
      ML137 AT %ML137 : ULINT := 16#0123456789ABCDEF;
      ML138 AT %ML138 : ULINT := 16#0123456789ABCDEF;
      ML139 AT %ML139 : ULINT := 16#0123456789ABCDEF;
      ML140 AT %ML140 : ULINT := 16#0123456789ABCDEF;
      ML141 AT %ML141 : ULINT := 16#0123456789ABCDEF;
      ML142 AT %ML142 : ULINT := 16#0123456789ABCDEF;
      ML143 AT %ML143 : ULINT := 16#0123456789ABCDEF;
      ML144 AT %ML144 : ULINT := 16#0123456789ABCDEF;
      ML145 AT %ML145 : ULINT := 16#0123456789ABCDEF;
      ML146 AT %ML146 : ULINT := 16#0123456789ABCDEF;
      ML147 AT %ML147 : ULINT := 16#0123456789ABCDEF;
      ML148 AT %ML148 : ULINT := 16#0123456789ABCDEF;
      ML149 AT %ML149 : ULINT := 16#0123456789ABCDEF;
      ML150 AT %ML150 : ULINT := 16#0123456789ABCDEF;
      ML151 AT %ML151 : ULINT := 16#0123456789ABCDEF;
      ML152 AT %ML152 : ULINT := 16#0123456789ABCDEF;
      ML153 AT %ML153 : ULINT := 16#0123456789ABCDEF;
      ML154 AT %ML154 : ULINT := 16#0123456789ABCDEF;
      ML155 AT %ML155 : ULINT := 16#0123456789ABCDEF;
      ML156 AT %ML156 : ULINT := 16#0123456789ABCDEF;
      ML157 AT %ML157 : ULINT := 16#0123456789ABCDEF;
      ML158 AT %ML158 : ULINT := 16#0123456789ABCDEF;
      ML159 AT %ML159 : ULINT := 16#0123456789ABCDEF;
      ML160 AT %ML160 : ULINT := 16#0123456789ABCDEF;
      ML161 AT %ML161 : ULINT := 16#0123456789ABCDEF;
      ML162 AT %ML162 : ULINT := 16#0123456789ABCDEF;
      ML163 AT %ML163 : ULINT := 16#0123456789ABCDEF;
      ML164 AT %ML164 : ULINT := 16#0123456789ABCDEF;
      ML165 AT %ML165 : ULINT := 16#0123456789ABCDEF;
      ML166 AT %ML166 : ULINT := 16#0123456789ABCDEF;
      ML167 AT %ML167 : ULINT := 16#0123456789ABCDEF;
      ML168 AT %ML168 : ULINT := 16#0123456789ABCDEF;
      ML169 AT %ML169 : ULINT := 16#0123456789ABCDEF;
      ML170 AT %ML170 : ULINT := 16#0123456789ABCDEF;
      ML171 AT %ML171 : ULINT := 16#0123456789ABCDEF;
      ML172 AT %ML172 : ULINT := 16#0123456789ABCDEF;
      ML173 AT %ML173 : ULINT := 16#0123456789ABCDEF;
      ML174 AT %ML174 : ULINT := 16#0123456789ABCDEF;
      ML175 AT %ML175 : ULINT := 16#0123456789ABCDEF;
      ML176 AT %ML176 : ULINT := 16#0123456789ABCDEF;
      ML177 AT %ML177 : ULINT := 16#0123456789ABCDEF;
      ML178 AT %ML178 : ULINT := 16#0123456789ABCDEF;
      ML179 AT %ML179 : ULINT := 16#0123456789ABCDEF;
      ML180 AT %ML180 : ULINT := 16#0123456789ABCDEF;
      ML181 AT %ML181 : ULINT := 16#0123456789ABCDEF;
      ML182 AT %ML182 : ULINT := 16#0123456789ABCDEF;
      ML183 AT %ML183 : ULINT := 16#0123456789ABCDEF;
      ML184 AT %ML184 : ULINT := 16#0123456789ABCDEF;
      ML185 AT %ML185 : ULINT := 16#0123456789ABCDEF;
      ML186 AT %ML186 : ULINT := 16#0123456789ABCDEF;
      ML187 AT %ML187 : ULINT := 16#0123456789ABCDEF;
      ML188 AT %ML188 : ULINT := 16#0123456789ABCDEF;
      ML189 AT %ML189 : ULINT := 16#0123456789ABCDEF;
      ML190 AT %ML190 : ULINT := 16#0123456789ABCDEF;
      ML191 AT %ML191 : ULINT := 16#0123456789ABCDEF;
      ML192 AT %ML192 : ULINT := 16#0123456789ABCDEF;
      ML193 AT %ML193 : ULINT := 16#0123456789ABCDEF;
      ML194 AT %ML194 : ULINT := 16#0123456789ABCDEF;
      ML195 AT %ML195 : ULINT := 16#0123456789ABCDEF;
      ML196 AT %ML196 : ULINT := 16#0123456789ABCDEF;
      ML197 AT %ML197 : ULINT := 16#0123456789ABCDEF;
      ML198 AT %ML198 : ULINT := 16#0123456789ABCDEF;
      ML199 AT %ML199 : ULINT := 16#0123456789ABCDEF;
      ML200 AT %ML200 : ULINT := 16#0123456789ABCDEF;
      ML201 AT %ML201 : ULINT := 16#0123456789ABCDEF;
      ML202 AT %ML202 : ULINT := 16#0123456789ABCDEF;
      ML203 AT %ML203 : ULINT := 16#0123456789ABCDEF;
      ML204 AT %ML204 : ULINT := 16#0123456789ABCDEF;
      ML205 AT %ML205 : ULINT := 16#0123456789ABCDEF;
      ML206 AT %ML206 : ULINT := 16#0123456789ABCDEF;
      ML207 AT %ML207 : ULINT := 16#0123456789ABCDEF;
      ML208 AT %ML208 : ULINT := 16#0123456789ABCDEF;
      ML209 AT %ML209 : ULINT := 16#0123456789ABCDEF;
      ML210 AT %ML210 : ULINT := 16#0123456789ABCDEF;
      ML211 AT %ML211 : ULINT := 16#0123456789ABCDEF;
      ML212 AT %ML212 : ULINT := 16#0123456789ABCDEF;
      ML213 AT %ML213 : ULINT := 16#0123456789ABCDEF;
      ML214 AT %ML214 : ULINT := 16#0123456789ABCDEF;
      ML215 AT %ML215 : ULINT := 16#0123456789ABCDEF;
      ML216 AT %ML216 : ULINT := 16#0123456789ABCDEF;
      ML217 AT %ML217 : ULINT := 16#0123456789ABCDEF;
      ML218 AT %ML218 : ULINT := 16#0123456789ABCDEF;
      ML219 AT %ML219 : ULINT := 16#0123456789ABCDEF;
      ML220 AT %ML220 : ULINT := 16#0123456789ABCDEF;
      ML221 AT %ML221 : ULINT := 16#0123456789ABCDEF;
      ML222 AT %ML222 : ULINT := 16#0123456789ABCDEF;
      ML223 AT %ML223 : ULINT := 16#0123456789ABCDEF;
      ML224 AT %ML224 : ULINT := 16#0123456789ABCDEF;
      ML225 AT %ML225 : ULINT := 16#0123456789ABCDEF;
      ML226 AT %ML226 : ULINT := 16#0123456789ABCDEF;
      ML227 AT %ML227 : ULINT := 16#0123456789ABCDEF;
      ML228 AT %ML228 : ULINT := 16#0123456789ABCDEF;
      ML229 AT %ML229 : ULINT := 16#0123456789ABCDEF;
      ML230 AT %ML230 : ULINT := 16#0123456789ABCDEF;
      ML231 AT %ML231 : ULINT := 16#0123456789ABCDEF;
      ML232 AT %ML232 : ULINT := 16#0123456789ABCDEF;
      ML233 AT %ML233 : ULINT := 16#0123456789ABCDEF;
      ML234 AT %ML234 : ULINT := 16#0123456789ABCDEF;
      ML235 AT %ML235 : ULINT := 16#0123456789ABCDEF;
      ML236 AT %ML236 : ULINT := 16#0123456789ABCDEF;
      ML237 AT %ML237 : ULINT := 16#0123456789ABCDEF;
      ML238 AT %ML238 : ULINT := 16#0123456789ABCDEF;
      ML239 AT %ML239 : ULINT := 16#0123456789ABCDEF;
      ML240 AT %ML240 : ULINT := 16#0123456789ABCDEF;
      ML241 AT %ML241 : ULINT := 16#0123456789ABCDEF;
      ML242 AT %ML242 : ULINT := 16#0123456789ABCDEF;
      ML243 AT %ML243 : ULINT := 16#0123456789ABCDEF;
      ML244 AT %ML244 : ULINT := 16#0123456789ABCDEF;
      ML245 AT %ML245 : ULINT := 16#0123456789ABCDEF;
      ML246 AT %ML246 : ULINT := 16#0123456789ABCDEF;
      ML247 AT %ML247 : ULINT := 16#0123456789ABCDEF;
      ML248 AT %ML248 : ULINT := 16#0123456789ABCDEF;
      ML249 AT %ML249 : ULINT := 16#0123456789ABCDEF;
      ML250 AT %ML250 : ULINT := 16#0123456789ABCDEF;
      ML251 AT %ML251 : ULINT := 16#0123456789ABCDEF;
      ML252 AT %ML252 : ULINT := 16#0123456789ABCDEF;
      ML253 AT %ML253 : ULINT := 16#0123456789ABCDEF;
      ML254 AT %ML254 : ULINT := 16#0123456789ABCDEF;
      ML255 AT %ML255 : ULINT := 16#0123456789ABCDEF;
      ML256 AT %ML256 : ULINT := 16#0123456789ABCDEF;
      ML257 AT %ML257 : ULINT := 16#0123456789ABCDEF;
      ML258 AT %ML258 : ULINT := 16#0123456789ABCDEF;
      ML259 AT %ML259 : ULINT := 16#0123456789ABCDEF;
      ML260 AT %ML260 : ULINT := 16#0123456789ABCDEF;
      ML261 AT %ML261 : ULINT := 16#0123456789ABCDEF;
      ML262 AT %ML262 : ULINT := 16#0123456789ABCDEF;
      ML263 AT %ML263 : ULINT := 16#0123456789ABCDEF;
      ML264 AT %ML264 : ULINT := 16#0123456789ABCDEF;
      ML265 AT %ML265 : ULINT := 16#0123456789ABCDEF;
      ML266 AT %ML266 : ULINT := 16#0123456789ABCDEF;
      ML267 AT %ML267 : ULINT := 16#0123456789ABCDEF;
      ML268 AT %ML268 : ULINT := 16#0123456789ABCDEF;
      ML269 AT %ML269 : ULINT := 16#0123456789ABCDEF;
      ML270 AT %ML270 : ULINT := 16#0123456789ABCDEF;
      ML271 AT %ML271 : ULINT := 16#0123456789ABCDEF;
      ML272 AT %ML272 : ULINT := 16#0123456789ABCDEF;
      ML273 AT %ML273 : ULINT := 16#0123456789ABCDEF;
      ML274 AT %ML274 : ULINT := 16#0123456789ABCDEF;
      ML275 AT %ML275 : ULINT := 16#0123456789ABCDEF;
      ML276 AT %ML276 : ULINT := 16#0123456789ABCDEF;
      ML277 AT %ML277 : ULINT := 16#0123456789ABCDEF;
      ML278 AT %ML278 : ULINT := 16#0123456789ABCDEF;
      ML279 AT %ML279 : ULINT := 16#0123456789ABCDEF;
      ML280 AT %ML280 : ULINT := 16#0123456789ABCDEF;
      ML281 AT %ML281 : ULINT := 16#0123456789ABCDEF;
      ML282 AT %ML282 : ULINT := 16#0123456789ABCDEF;
      ML283 AT %ML283 : ULINT := 16#0123456789ABCDEF;
      ML284 AT %ML284 : ULINT := 16#0123456789ABCDEF;
      ML285 AT %ML285 : ULINT := 16#0123456789ABCDEF;
      ML286 AT %ML286 : ULINT := 16#0123456789ABCDEF;
      ML287 AT %ML287 : ULINT := 16#0123456789ABCDEF;
      ML288 AT %ML288 : ULINT := 16#0123456789ABCDEF;
      ML289 AT %ML289 : ULINT := 16#0123456789ABCDEF;
      ML290 AT %ML290 : ULINT := 16#0123456789ABCDEF;
      ML291 AT %ML291 : ULINT := 16#0123456789ABCDEF;
      ML292 AT %ML292 : ULINT := 16#0123456789ABCDEF;
      ML293 AT %ML293 : ULINT := 16#0123456789ABCDEF;
      ML294 AT %ML294 : ULINT := 16#0123456789ABCDEF;
      ML295 AT %ML295 : ULINT := 16#0123456789ABCDEF;
      ML296 AT %ML296 : ULINT := 16#0123456789ABCDEF;
      ML297 AT %ML297 : ULINT := 16#0123456789ABCDEF;
      ML298 AT %ML298 : ULINT := 16#0123456789ABCDEF;
      ML299 AT %ML299 : ULINT := 16#0123456789ABCDEF;
      ML300 AT %ML300 : ULINT := 16#0123456789ABCDEF;
      ML301 AT %ML301 : ULINT := 16#0123456789ABCDEF;
      ML302 AT %ML302 : ULINT := 16#0123456789ABCDEF;
      ML303 AT %ML303 : ULINT := 16#0123456789ABCDEF;
      ML304 AT %ML304 : ULINT := 16#0123456789ABCDEF;
      ML305 AT %ML305 : ULINT := 16#0123456789ABCDEF;
      ML306 AT %ML306 : ULINT := 16#0123456789ABCDEF;
      ML307 AT %ML307 : ULINT := 16#0123456789ABCDEF;
      ML308 AT %ML308 : ULINT := 16#0123456789ABCDEF;
      ML309 AT %ML309 : ULINT := 16#0123456789ABCDEF;
      ML310 AT %ML310 : ULINT := 16#0123456789ABCDEF;
      ML311 AT %ML311 : ULINT := 16#0123456789ABCDEF;
      ML312 AT %ML312 : ULINT := 16#0123456789ABCDEF;
      ML313 AT %ML313 : ULINT := 16#0123456789ABCDEF;
      ML314 AT %ML314 : ULINT := 16#0123456789ABCDEF;
      ML315 AT %ML315 : ULINT := 16#0123456789ABCDEF;
      ML316 AT %ML316 : ULINT := 16#0123456789ABCDEF;
      ML317 AT %ML317 : ULINT := 16#0123456789ABCDEF;
      ML318 AT %ML318 : ULINT := 16#0123456789ABCDEF;
      ML319 AT %ML319 : ULINT := 16#0123456789ABCDEF;
      ML320 AT %ML320 : ULINT := 16#0123456789ABCDEF;
      ML321 AT %ML321 : ULINT := 16#0123456789ABCDEF;
      ML322 AT %ML322 : ULINT := 16#0123456789ABCDEF;
      ML323 AT %ML323 : ULINT := 16#0123456789ABCDEF;
      ML324 AT %ML324 : ULINT := 16#0123456789ABCDEF;
      ML325 AT %ML325 : ULINT := 16#0123456789ABCDEF;
      ML326 AT %ML326 : ULINT := 16#0123456789ABCDEF;
      ML327 AT %ML327 : ULINT := 16#0123456789ABCDEF;
      ML328 AT %ML328 : ULINT := 16#0123456789ABCDEF;
      ML329 AT %ML329 : ULINT := 16#0123456789ABCDEF;
      ML330 AT %ML330 : ULINT := 16#0123456789ABCDEF;
      ML331 AT %ML331 : ULINT := 16#0123456789ABCDEF;
      ML332 AT %ML332 : ULINT := 16#0123456789ABCDEF;
      ML333 AT %ML333 : ULINT := 16#0123456789ABCDEF;
      ML334 AT %ML334 : ULINT := 16#0123456789ABCDEF;
      ML335 AT %ML335 : ULINT := 16#0123456789ABCDEF;
      ML336 AT %ML336 : ULINT := 16#0123456789ABCDEF;
      ML337 AT %ML337 : ULINT := 16#0123456789ABCDEF;
      ML338 AT %ML338 : ULINT := 16#0123456789ABCDEF;
      ML339 AT %ML339 : ULINT := 16#0123456789ABCDEF;
      ML340 AT %ML340 : ULINT := 16#0123456789ABCDEF;
      ML341 AT %ML341 : ULINT := 16#0123456789ABCDEF;
      ML342 AT %ML342 : ULINT := 16#0123456789ABCDEF;
      ML343 AT %ML343 : ULINT := 16#0123456789ABCDEF;
      ML344 AT %ML344 : ULINT := 16#0123456789ABCDEF;
      ML345 AT %ML345 : ULINT := 16#0123456789ABCDEF;
      ML346 AT %ML346 : ULINT := 16#0123456789ABCDEF;
      ML347 AT %ML347 : ULINT := 16#0123456789ABCDEF;
      ML348 AT %ML348 : ULINT := 16#0123456789ABCDEF;
      ML349 AT %ML349 : ULINT := 16#0123456789ABCDEF;
      ML350 AT %ML350 : ULINT := 16#0123456789ABCDEF;
      ML351 AT %ML351 : ULINT := 16#0123456789ABCDEF;
      ML352 AT %ML352 : ULINT := 16#0123456789ABCDEF;
      ML353 AT %ML353 : ULINT := 16#0123456789ABCDEF;
      ML354 AT %ML354 : ULINT := 16#0123456789ABCDEF;
      ML355 AT %ML355 : ULINT := 16#0123456789ABCDEF;
      ML356 AT %ML356 : ULINT := 16#0123456789ABCDEF;
      ML357 AT %ML357 : ULINT := 16#0123456789ABCDEF;
      ML358 AT %ML358 : ULINT := 16#0123456789ABCDEF;
      ML359 AT %ML359 : ULINT := 16#0123456789ABCDEF;
      ML360 AT %ML360 : ULINT := 16#0123456789ABCDEF;
      ML361 AT %ML361 : ULINT := 16#0123456789ABCDEF;
      ML362 AT %ML362 : ULINT := 16#0123456789ABCDEF;
      ML363 AT %ML363 : ULINT := 16#0123456789ABCDEF;
      ML364 AT %ML364 : ULINT := 16#0123456789ABCDEF;
      ML365 AT %ML365 : ULINT := 16#0123456789ABCDEF;
      ML366 AT %ML366 : ULINT := 16#0123456789ABCDEF;
      ML367 AT %ML367 : ULINT := 16#0123456789ABCDEF;
      ML368 AT %ML368 : ULINT := 16#0123456789ABCDEF;
      ML369 AT %ML369 : ULINT := 16#0123456789ABCDEF;
      ML370 AT %ML370 : ULINT := 16#0123456789ABCDEF;
      ML371 AT %ML371 : ULINT := 16#0123456789ABCDEF;
      ML372 AT %ML372 : ULINT := 16#0123456789ABCDEF;
      ML373 AT %ML373 : ULINT := 16#0123456789ABCDEF;
      ML374 AT %ML374 : ULINT := 16#0123456789ABCDEF;
      ML375 AT %ML375 : ULINT := 16#0123456789ABCDEF;
      ML376 AT %ML376 : ULINT := 16#0123456789ABCDEF;
      ML377 AT %ML377 : ULINT := 16#0123456789ABCDEF;
      ML378 AT %ML378 : ULINT := 16#0123456789ABCDEF;
      ML379 AT %ML379 : ULINT := 16#0123456789ABCDEF;
      ML380 AT %ML380 : ULINT := 16#0123456789ABCDEF;
      ML381 AT %ML381 : ULINT := 16#0123456789ABCDEF;
      ML382 AT %ML382 : ULINT := 16#0123456789ABCDEF;
      ML383 AT %ML383 : ULINT := 16#0123456789ABCDEF;
      ML384 AT %ML384 : ULINT := 16#0123456789ABCDEF;
      ML385 AT %ML385 : ULINT := 16#0123456789ABCDEF;
      ML386 AT %ML386 : ULINT := 16#0123456789ABCDEF;
      ML387 AT %ML387 : ULINT := 16#0123456789ABCDEF;
      ML388 AT %ML388 : ULINT := 16#0123456789ABCDEF;
      ML389 AT %ML389 : ULINT := 16#0123456789ABCDEF;
      ML390 AT %ML390 : ULINT := 16#0123456789ABCDEF;
      ML391 AT %ML391 : ULINT := 16#0123456789ABCDEF;
      ML392 AT %ML392 : ULINT := 16#0123456789ABCDEF;
      ML393 AT %ML393 : ULINT := 16#0123456789ABCDEF;
      ML394 AT %ML394 : ULINT := 16#0123456789ABCDEF;
      ML395 AT %ML395 : ULINT := 16#0123456789ABCDEF;
      ML396 AT %ML396 : ULINT := 16#0123456789ABCDEF;
      ML397 AT %ML397 : ULINT := 16#0123456789ABCDEF;
      ML398 AT %ML398 : ULINT := 16#0123456789ABCDEF;
      ML399 AT %ML399 : ULINT := 16#0123456789ABCDEF;
      ML400 AT %ML400 : ULINT := 16#0123456789ABCDEF;
      ML401 AT %ML401 : ULINT := 16#0123456789ABCDEF;
      ML402 AT %ML402 : ULINT := 16#0123456789ABCDEF;
      ML403 AT %ML403 : ULINT := 16#0123456789ABCDEF;
      ML404 AT %ML404 : ULINT := 16#0123456789ABCDEF;
      ML405 AT %ML405 : ULINT := 16#0123456789ABCDEF;
      ML406 AT %ML406 : ULINT := 16#0123456789ABCDEF;
      ML407 AT %ML407 : ULINT := 16#0123456789ABCDEF;
      ML408 AT %ML408 : ULINT := 16#0123456789ABCDEF;
      ML409 AT %ML409 : ULINT := 16#0123456789ABCDEF;
      ML410 AT %ML410 : ULINT := 16#0123456789ABCDEF;
      ML411 AT %ML411 : ULINT := 16#0123456789ABCDEF;
      ML412 AT %ML412 : ULINT := 16#0123456789ABCDEF;
      ML413 AT %ML413 : ULINT := 16#0123456789ABCDEF;
      ML414 AT %ML414 : ULINT := 16#0123456789ABCDEF;
      ML415 AT %ML415 : ULINT := 16#0123456789ABCDEF;
      ML416 AT %ML416 : ULINT := 16#0123456789ABCDEF;
      ML417 AT %ML417 : ULINT := 16#0123456789ABCDEF;
      ML418 AT %ML418 : ULINT := 16#0123456789ABCDEF;
      ML419 AT %ML419 : ULINT := 16#0123456789ABCDEF;
      ML420 AT %ML420 : ULINT := 16#0123456789ABCDEF;
      ML421 AT %ML421 : ULINT := 16#0123456789ABCDEF;
      ML422 AT %ML422 : ULINT := 16#0123456789ABCDEF;
      ML423 AT %ML423 : ULINT := 16#0123456789ABCDEF;
      ML424 AT %ML424 : ULINT := 16#0123456789ABCDEF;
      ML425 AT %ML425 : ULINT := 16#0123456789ABCDEF;
      ML426 AT %ML426 : ULINT := 16#0123456789ABCDEF;
      ML427 AT %ML427 : ULINT := 16#0123456789ABCDEF;
      ML428 AT %ML428 : ULINT := 16#0123456789ABCDEF;
      ML429 AT %ML429 : ULINT := 16#0123456789ABCDEF;
      ML430 AT %ML430 : ULINT := 16#0123456789ABCDEF;
      ML431 AT %ML431 : ULINT := 16#0123456789ABCDEF;
      ML432 AT %ML432 : ULINT := 16#0123456789ABCDEF;
      ML433 AT %ML433 : ULINT := 16#0123456789ABCDEF;
      ML434 AT %ML434 : ULINT := 16#0123456789ABCDEF;
      ML435 AT %ML435 : ULINT := 16#0123456789ABCDEF;
      ML436 AT %ML436 : ULINT := 16#0123456789ABCDEF;
      ML437 AT %ML437 : ULINT := 16#0123456789ABCDEF;
      ML438 AT %ML438 : ULINT := 16#0123456789ABCDEF;
      ML439 AT %ML439 : ULINT := 16#0123456789ABCDEF;
      ML440 AT %ML440 : ULINT := 16#0123456789ABCDEF;
      ML441 AT %ML441 : ULINT := 16#0123456789ABCDEF;
      ML442 AT %ML442 : ULINT := 16#0123456789ABCDEF;
      ML443 AT %ML443 : ULINT := 16#0123456789ABCDEF;
      ML444 AT %ML444 : ULINT := 16#0123456789ABCDEF;
      ML445 AT %ML445 : ULINT := 16#0123456789ABCDEF;
      ML446 AT %ML446 : ULINT := 16#0123456789ABCDEF;
      ML447 AT %ML447 : ULINT := 16#0123456789ABCDEF;
      ML448 AT %ML448 : ULINT := 16#0123456789ABCDEF;
      ML449 AT %ML449 : ULINT := 16#0123456789ABCDEF;
      ML450 AT %ML450 : ULINT := 16#0123456789ABCDEF;
      ML451 AT %ML451 : ULINT := 16#0123456789ABCDEF;
      ML452 AT %ML452 : ULINT := 16#0123456789ABCDEF;
      ML453 AT %ML453 : ULINT := 16#0123456789ABCDEF;
      ML454 AT %ML454 : ULINT := 16#0123456789ABCDEF;
      ML455 AT %ML455 : ULINT := 16#0123456789ABCDEF;
      ML456 AT %ML456 : ULINT := 16#0123456789ABCDEF;
      ML457 AT %ML457 : ULINT := 16#0123456789ABCDEF;
      ML458 AT %ML458 : ULINT := 16#0123456789ABCDEF;
      ML459 AT %ML459 : ULINT := 16#0123456789ABCDEF;
      ML460 AT %ML460 : ULINT := 16#0123456789ABCDEF;
      ML461 AT %ML461 : ULINT := 16#0123456789ABCDEF;
      ML462 AT %ML462 : ULINT := 16#0123456789ABCDEF;
      ML463 AT %ML463 : ULINT := 16#0123456789ABCDEF;
      ML464 AT %ML464 : ULINT := 16#0123456789ABCDEF;
      ML465 AT %ML465 : ULINT := 16#0123456789ABCDEF;
      ML466 AT %ML466 : ULINT := 16#0123456789ABCDEF;
      ML467 AT %ML467 : ULINT := 16#0123456789ABCDEF;
      ML468 AT %ML468 : ULINT := 16#0123456789ABCDEF;
      ML469 AT %ML469 : ULINT := 16#0123456789ABCDEF;
      ML470 AT %ML470 : ULINT := 16#0123456789ABCDEF;
      ML471 AT %ML471 : ULINT := 16#0123456789ABCDEF;
      ML472 AT %ML472 : ULINT := 16#0123456789ABCDEF;
      ML473 AT %ML473 : ULINT := 16#0123456789ABCDEF;
      ML474 AT %ML474 : ULINT := 16#0123456789ABCDEF;
      ML475 AT %ML475 : ULINT := 16#0123456789ABCDEF;
      ML476 AT %ML476 : ULINT := 16#0123456789ABCDEF;
      ML477 AT %ML477 : ULINT := 16#0123456789ABCDEF;
      ML478 AT %ML478 : ULINT := 16#0123456789ABCDEF;
      ML479 AT %ML479 : ULINT := 16#0123456789ABCDEF;
      ML480 AT %ML480 : ULINT := 16#0123456789ABCDEF;
      ML481 AT %ML481 : ULINT := 16#0123456789ABCDEF;
      ML482 AT %ML482 : ULINT := 16#0123456789ABCDEF;
      ML483 AT %ML483 : ULINT := 16#0123456789ABCDEF;
      ML484 AT %ML484 : ULINT := 16#0123456789ABCDEF;
      ML485 AT %ML485 : ULINT := 16#0123456789ABCDEF;
      ML486 AT %ML486 : ULINT := 16#0123456789ABCDEF;
      ML487 AT %ML487 : ULINT := 16#0123456789ABCDEF;
      ML488 AT %ML488 : ULINT := 16#0123456789ABCDEF;
      ML489 AT %ML489 : ULINT := 16#0123456789ABCDEF;
      ML490 AT %ML490 : ULINT := 16#0123456789ABCDEF;
      ML491 AT %ML491 : ULINT := 16#0123456789ABCDEF;
      ML492 AT %ML492 : ULINT := 16#0123456789ABCDEF;
      ML493 AT %ML493 : ULINT := 16#0123456789ABCDEF;
      ML494 AT %ML494 : ULINT := 16#0123456789ABCDEF;
      ML495 AT %ML495 : ULINT := 16#0123456789ABCDEF;
      ML496 AT %ML496 : ULINT := 16#0123456789ABCDEF;
      ML497 AT %ML497 : ULINT := 16#0123456789ABCDEF;
      ML498 AT %ML498 : ULINT := 16#0123456789ABCDEF;
      ML499 AT %ML499 : ULINT := 16#0123456789ABCDEF;
      ML500 AT %ML500 : ULINT := 16#0123456789ABCDEF;
      ML501 AT %ML501 : ULINT := 16#0123456789ABCDEF;
      ML502 AT %ML502 : ULINT := 16#0123456789ABCDEF;
      ML503 AT %ML503 : ULINT := 16#0123456789ABCDEF;
      ML504 AT %ML504 : ULINT := 16#0123456789ABCDEF;
      ML505 AT %ML505 : ULINT := 16#0123456789ABCDEF;
      ML506 AT %ML506 : ULINT := 16#0123456789ABCDEF;
      ML507 AT %ML507 : ULINT := 16#0123456789ABCDEF;
      ML508 AT %ML508 : ULINT := 16#0123456789ABCDEF;
      ML509 AT %ML509 : ULINT := 16#0123456789ABCDEF;
      ML510 AT %ML510 : ULINT := 16#0123456789ABCDEF;
      ML511 AT %ML511 : ULINT := 16#0123456789ABCDEF;
      ML512 AT %ML512 : ULINT := 16#0123456789ABCDEF;
      ML513 AT %ML513 : ULINT := 16#0123456789ABCDEF;
      ML514 AT %ML514 : ULINT := 16#0123456789ABCDEF;
      ML515 AT %ML515 : ULINT := 16#0123456789ABCDEF;
      ML516 AT %ML516 : ULINT := 16#0123456789ABCDEF;
      ML517 AT %ML517 : ULINT := 16#0123456789ABCDEF;
      ML518 AT %ML518 : ULINT := 16#0123456789ABCDEF;
      ML519 AT %ML519 : ULINT := 16#0123456789ABCDEF;
      ML520 AT %ML520 : ULINT := 16#0123456789ABCDEF;
      ML521 AT %ML521 : ULINT := 16#0123456789ABCDEF;
      ML522 AT %ML522 : ULINT := 16#0123456789ABCDEF;
      ML523 AT %ML523 : ULINT := 16#0123456789ABCDEF;
      ML524 AT %ML524 : ULINT := 16#0123456789ABCDEF;
      ML525 AT %ML525 : ULINT := 16#0123456789ABCDEF;
      ML526 AT %ML526 : ULINT := 16#0123456789ABCDEF;
      ML527 AT %ML527 : ULINT := 16#0123456789ABCDEF;
      ML528 AT %ML528 : ULINT := 16#0123456789ABCDEF;
      ML529 AT %ML529 : ULINT := 16#0123456789ABCDEF;
      ML530 AT %ML530 : ULINT := 16#0123456789ABCDEF;
      ML531 AT %ML531 : ULINT := 16#0123456789ABCDEF;
      ML532 AT %ML532 : ULINT := 16#0123456789ABCDEF;
      ML533 AT %ML533 : ULINT := 16#0123456789ABCDEF;
      ML534 AT %ML534 : ULINT := 16#0123456789ABCDEF;
      ML535 AT %ML535 : ULINT := 16#0123456789ABCDEF;
      ML536 AT %ML536 : ULINT := 16#0123456789ABCDEF;
      ML537 AT %ML537 : ULINT := 16#0123456789ABCDEF;
      ML538 AT %ML538 : ULINT := 16#0123456789ABCDEF;
      ML539 AT %ML539 : ULINT := 16#0123456789ABCDEF;
      ML540 AT %ML540 : ULINT := 16#0123456789ABCDEF;
      ML541 AT %ML541 : ULINT := 16#0123456789ABCDEF;
      ML542 AT %ML542 : ULINT := 16#0123456789ABCDEF;
      ML543 AT %ML543 : ULINT := 16#0123456789ABCDEF;
      ML544 AT %ML544 : ULINT := 16#0123456789ABCDEF;
      ML545 AT %ML545 : ULINT := 16#0123456789ABCDEF;
      ML546 AT %ML546 : ULINT := 16#0123456789ABCDEF;
      ML547 AT %ML547 : ULINT := 16#0123456789ABCDEF;
      ML548 AT %ML548 : ULINT := 16#0123456789ABCDEF;
      ML549 AT %ML549 : ULINT := 16#0123456789ABCDEF;
      ML550 AT %ML550 : ULINT := 16#0123456789ABCDEF;
      ML551 AT %ML551 : ULINT := 16#0123456789ABCDEF;
      ML552 AT %ML552 : ULINT := 16#0123456789ABCDEF;
      ML553 AT %ML553 : ULINT := 16#0123456789ABCDEF;
      ML554 AT %ML554 : ULINT := 16#0123456789ABCDEF;
      ML555 AT %ML555 : ULINT := 16#0123456789ABCDEF;
      ML556 AT %ML556 : ULINT := 16#0123456789ABCDEF;
      ML557 AT %ML557 : ULINT := 16#0123456789ABCDEF;
      ML558 AT %ML558 : ULINT := 16#0123456789ABCDEF;
      ML559 AT %ML559 : ULINT := 16#0123456789ABCDEF;
      ML560 AT %ML560 : ULINT := 16#0123456789ABCDEF;
      ML561 AT %ML561 : ULINT := 16#0123456789ABCDEF;
      ML562 AT %ML562 : ULINT := 16#0123456789ABCDEF;
      ML563 AT %ML563 : ULINT := 16#0123456789ABCDEF;
      ML564 AT %ML564 : ULINT := 16#0123456789ABCDEF;
      ML565 AT %ML565 : ULINT := 16#0123456789ABCDEF;
      ML566 AT %ML566 : ULINT := 16#0123456789ABCDEF;
      ML567 AT %ML567 : ULINT := 16#0123456789ABCDEF;
      ML568 AT %ML568 : ULINT := 16#0123456789ABCDEF;
      ML569 AT %ML569 : ULINT := 16#0123456789ABCDEF;
      ML570 AT %ML570 : ULINT := 16#0123456789ABCDEF;
      ML571 AT %ML571 : ULINT := 16#0123456789ABCDEF;
      ML572 AT %ML572 : ULINT := 16#0123456789ABCDEF;
      ML573 AT %ML573 : ULINT := 16#0123456789ABCDEF;
      ML574 AT %ML574 : ULINT := 16#0123456789ABCDEF;
      ML575 AT %ML575 : ULINT := 16#0123456789ABCDEF;
      ML576 AT %ML576 : ULINT := 16#0123456789ABCDEF;
      ML577 AT %ML577 : ULINT := 16#0123456789ABCDEF;
      ML578 AT %ML578 : ULINT := 16#0123456789ABCDEF;
      ML579 AT %ML579 : ULINT := 16#0123456789ABCDEF;
      ML580 AT %ML580 : ULINT := 16#0123456789ABCDEF;
      ML581 AT %ML581 : ULINT := 16#0123456789ABCDEF;
      ML582 AT %ML582 : ULINT := 16#0123456789ABCDEF;
      ML583 AT %ML583 : ULINT := 16#0123456789ABCDEF;
      ML584 AT %ML584 : ULINT := 16#0123456789ABCDEF;
      ML585 AT %ML585 : ULINT := 16#0123456789ABCDEF;
      ML586 AT %ML586 : ULINT := 16#0123456789ABCDEF;
      ML587 AT %ML587 : ULINT := 16#0123456789ABCDEF;
      ML588 AT %ML588 : ULINT := 16#0123456789ABCDEF;
      ML589 AT %ML589 : ULINT := 16#0123456789ABCDEF;
      ML590 AT %ML590 : ULINT := 16#0123456789ABCDEF;
      ML591 AT %ML591 : ULINT := 16#0123456789ABCDEF;
      ML592 AT %ML592 : ULINT := 16#0123456789ABCDEF;
      ML593 AT %ML593 : ULINT := 16#0123456789ABCDEF;
      ML594 AT %ML594 : ULINT := 16#0123456789ABCDEF;
      ML595 AT %ML595 : ULINT := 16#0123456789ABCDEF;
      ML596 AT %ML596 : ULINT := 16#0123456789ABCDEF;
      ML597 AT %ML597 : ULINT := 16#0123456789ABCDEF;
      ML598 AT %ML598 : ULINT := 16#0123456789ABCDEF;
      ML599 AT %ML599 : ULINT := 16#0123456789ABCDEF;
      ML600 AT %ML600 : ULINT := 16#0123456789ABCDEF;
      ML601 AT %ML601 : ULINT := 16#0123456789ABCDEF;
      ML602 AT %ML602 : ULINT := 16#0123456789ABCDEF;
      ML603 AT %ML603 : ULINT := 16#0123456789ABCDEF;
      ML604 AT %ML604 : ULINT := 16#0123456789ABCDEF;
      ML605 AT %ML605 : ULINT := 16#0123456789ABCDEF;
      ML606 AT %ML606 : ULINT := 16#0123456789ABCDEF;
      ML607 AT %ML607 : ULINT := 16#0123456789ABCDEF;
      ML608 AT %ML608 : ULINT := 16#0123456789ABCDEF;
      ML609 AT %ML609 : ULINT := 16#0123456789ABCDEF;
      ML610 AT %ML610 : ULINT := 16#0123456789ABCDEF;
      ML611 AT %ML611 : ULINT := 16#0123456789ABCDEF;
      ML612 AT %ML612 : ULINT := 16#0123456789ABCDEF;
      ML613 AT %ML613 : ULINT := 16#0123456789ABCDEF;
      ML614 AT %ML614 : ULINT := 16#0123456789ABCDEF;
      ML615 AT %ML615 : ULINT := 16#0123456789ABCDEF;
      ML616 AT %ML616 : ULINT := 16#0123456789ABCDEF;
      ML617 AT %ML617 : ULINT := 16#0123456789ABCDEF;
      ML618 AT %ML618 : ULINT := 16#0123456789ABCDEF;
      ML619 AT %ML619 : ULINT := 16#0123456789ABCDEF;
      ML620 AT %ML620 : ULINT := 16#0123456789ABCDEF;
      ML621 AT %ML621 : ULINT := 16#0123456789ABCDEF;
      ML622 AT %ML622 : ULINT := 16#0123456789ABCDEF;
      ML623 AT %ML623 : ULINT := 16#0123456789ABCDEF;
      ML624 AT %ML624 : ULINT := 16#0123456789ABCDEF;
      ML625 AT %ML625 : ULINT := 16#0123456789ABCDEF;
      ML626 AT %ML626 : ULINT := 16#0123456789ABCDEF;
      ML627 AT %ML627 : ULINT := 16#0123456789ABCDEF;
      ML628 AT %ML628 : ULINT := 16#0123456789ABCDEF;
      ML629 AT %ML629 : ULINT := 16#0123456789ABCDEF;
      ML630 AT %ML630 : ULINT := 16#0123456789ABCDEF;
      ML631 AT %ML631 : ULINT := 16#0123456789ABCDEF;
      ML632 AT %ML632 : ULINT := 16#0123456789ABCDEF;
      ML633 AT %ML633 : ULINT := 16#0123456789ABCDEF;
      ML634 AT %ML634 : ULINT := 16#0123456789ABCDEF;
      ML635 AT %ML635 : ULINT := 16#0123456789ABCDEF;
      ML636 AT %ML636 : ULINT := 16#0123456789ABCDEF;
      ML637 AT %ML637 : ULINT := 16#0123456789ABCDEF;
      ML638 AT %ML638 : ULINT := 16#0123456789ABCDEF;
      ML639 AT %ML639 : ULINT := 16#0123456789ABCDEF;
      ML640 AT %ML640 : ULINT := 16#0123456789ABCDEF;
      ML641 AT %ML641 : ULINT := 16#0123456789ABCDEF;
      ML642 AT %ML642 : ULINT := 16#0123456789ABCDEF;
      ML643 AT %ML643 : ULINT := 16#0123456789ABCDEF;
      ML644 AT %ML644 : ULINT := 16#0123456789ABCDEF;
      ML645 AT %ML645 : ULINT := 16#0123456789ABCDEF;
      ML646 AT %ML646 : ULINT := 16#0123456789ABCDEF;
      ML647 AT %ML647 : ULINT := 16#0123456789ABCDEF;
      ML648 AT %ML648 : ULINT := 16#0123456789ABCDEF;
      ML649 AT %ML649 : ULINT := 16#0123456789ABCDEF;
      ML650 AT %ML650 : ULINT := 16#0123456789ABCDEF;
      ML651 AT %ML651 : ULINT := 16#0123456789ABCDEF;
      ML652 AT %ML652 : ULINT := 16#0123456789ABCDEF;
      ML653 AT %ML653 : ULINT := 16#0123456789ABCDEF;
      ML654 AT %ML654 : ULINT := 16#0123456789ABCDEF;
      ML655 AT %ML655 : ULINT := 16#0123456789ABCDEF;
      ML656 AT %ML656 : ULINT := 16#0123456789ABCDEF;
      ML657 AT %ML657 : ULINT := 16#0123456789ABCDEF;
      ML658 AT %ML658 : ULINT := 16#0123456789ABCDEF;
      ML659 AT %ML659 : ULINT := 16#0123456789ABCDEF;
      ML660 AT %ML660 : ULINT := 16#0123456789ABCDEF;
      ML661 AT %ML661 : ULINT := 16#0123456789ABCDEF;
      ML662 AT %ML662 : ULINT := 16#0123456789ABCDEF;
      ML663 AT %ML663 : ULINT := 16#0123456789ABCDEF;
      ML664 AT %ML664 : ULINT := 16#0123456789ABCDEF;
      ML665 AT %ML665 : ULINT := 16#0123456789ABCDEF;
      ML666 AT %ML666 : ULINT := 16#0123456789ABCDEF;
      ML667 AT %ML667 : ULINT := 16#0123456789ABCDEF;
      ML668 AT %ML668 : ULINT := 16#0123456789ABCDEF;
      ML669 AT %ML669 : ULINT := 16#0123456789ABCDEF;
      ML670 AT %ML670 : ULINT := 16#0123456789ABCDEF;
      ML671 AT %ML671 : ULINT := 16#0123456789ABCDEF;
      ML672 AT %ML672 : ULINT := 16#0123456789ABCDEF;
      ML673 AT %ML673 : ULINT := 16#0123456789ABCDEF;
      ML674 AT %ML674 : ULINT := 16#0123456789ABCDEF;
      ML675 AT %ML675 : ULINT := 16#0123456789ABCDEF;
      ML676 AT %ML676 : ULINT := 16#0123456789ABCDEF;
      ML677 AT %ML677 : ULINT := 16#0123456789ABCDEF;
      ML678 AT %ML678 : ULINT := 16#0123456789ABCDEF;
      ML679 AT %ML679 : ULINT := 16#0123456789ABCDEF;
      ML680 AT %ML680 : ULINT := 16#0123456789ABCDEF;
      ML681 AT %ML681 : ULINT := 16#0123456789ABCDEF;
      ML682 AT %ML682 : ULINT := 16#0123456789ABCDEF;
      ML683 AT %ML683 : ULINT := 16#0123456789ABCDEF;
      ML684 AT %ML684 : ULINT := 16#0123456789ABCDEF;
      ML685 AT %ML685 : ULINT := 16#0123456789ABCDEF;
      ML686 AT %ML686 : ULINT := 16#0123456789ABCDEF;
      ML687 AT %ML687 : ULINT := 16#0123456789ABCDEF;
      ML688 AT %ML688 : ULINT := 16#0123456789ABCDEF;
      ML689 AT %ML689 : ULINT := 16#0123456789ABCDEF;
      ML690 AT %ML690 : ULINT := 16#0123456789ABCDEF;
      ML691 AT %ML691 : ULINT := 16#0123456789ABCDEF;
      ML692 AT %ML692 : ULINT := 16#0123456789ABCDEF;
      ML693 AT %ML693 : ULINT := 16#0123456789ABCDEF;
      ML694 AT %ML694 : ULINT := 16#0123456789ABCDEF;
      ML695 AT %ML695 : ULINT := 16#0123456789ABCDEF;
      ML696 AT %ML696 : ULINT := 16#0123456789ABCDEF;
      ML697 AT %ML697 : ULINT := 16#0123456789ABCDEF;
      ML698 AT %ML698 : ULINT := 16#0123456789ABCDEF;
      ML699 AT %ML699 : ULINT := 16#0123456789ABCDEF;
      ML700 AT %ML700 : ULINT := 16#0123456789ABCDEF;
      ML701 AT %ML701 : ULINT := 16#0123456789ABCDEF;
      ML702 AT %ML702 : ULINT := 16#0123456789ABCDEF;
      ML703 AT %ML703 : ULINT := 16#0123456789ABCDEF;
      ML704 AT %ML704 : ULINT := 16#0123456789ABCDEF;
      ML705 AT %ML705 : ULINT := 16#0123456789ABCDEF;
      ML706 AT %ML706 : ULINT := 16#0123456789ABCDEF;
      ML707 AT %ML707 : ULINT := 16#0123456789ABCDEF;
      ML708 AT %ML708 : ULINT := 16#0123456789ABCDEF;
      ML709 AT %ML709 : ULINT := 16#0123456789ABCDEF;
      ML710 AT %ML710 : ULINT := 16#0123456789ABCDEF;
      ML711 AT %ML711 : ULINT := 16#0123456789ABCDEF;
      ML712 AT %ML712 : ULINT := 16#0123456789ABCDEF;
      ML713 AT %ML713 : ULINT := 16#0123456789ABCDEF;
      ML714 AT %ML714 : ULINT := 16#0123456789ABCDEF;
      ML715 AT %ML715 : ULINT := 16#0123456789ABCDEF;
      ML716 AT %ML716 : ULINT := 16#0123456789ABCDEF;
      ML717 AT %ML717 : ULINT := 16#0123456789ABCDEF;
      ML718 AT %ML718 : ULINT := 16#0123456789ABCDEF;
      ML719 AT %ML719 : ULINT := 16#0123456789ABCDEF;
      ML720 AT %ML720 : ULINT := 16#0123456789ABCDEF;
      ML721 AT %ML721 : ULINT := 16#0123456789ABCDEF;
      ML722 AT %ML722 : ULINT := 16#0123456789ABCDEF;
      ML723 AT %ML723 : ULINT := 16#0123456789ABCDEF;
      ML724 AT %ML724 : ULINT := 16#0123456789ABCDEF;
      ML725 AT %ML725 : ULINT := 16#0123456789ABCDEF;
      ML726 AT %ML726 : ULINT := 16#0123456789ABCDEF;
      ML727 AT %ML727 : ULINT := 16#0123456789ABCDEF;
      ML728 AT %ML728 : ULINT := 16#0123456789ABCDEF;
      ML729 AT %ML729 : ULINT := 16#0123456789ABCDEF;
      ML730 AT %ML730 : ULINT := 16#0123456789ABCDEF;
      ML731 AT %ML731 : ULINT := 16#0123456789ABCDEF;
      ML732 AT %ML732 : ULINT := 16#0123456789ABCDEF;
      ML733 AT %ML733 : ULINT := 16#0123456789ABCDEF;
      ML734 AT %ML734 : ULINT := 16#0123456789ABCDEF;
      ML735 AT %ML735 : ULINT := 16#0123456789ABCDEF;
      ML736 AT %ML736 : ULINT := 16#0123456789ABCDEF;
      ML737 AT %ML737 : ULINT := 16#0123456789ABCDEF;
      ML738 AT %ML738 : ULINT := 16#0123456789ABCDEF;
      ML739 AT %ML739 : ULINT := 16#0123456789ABCDEF;
      ML740 AT %ML740 : ULINT := 16#0123456789ABCDEF;
      ML741 AT %ML741 : ULINT := 16#0123456789ABCDEF;
      ML742 AT %ML742 : ULINT := 16#0123456789ABCDEF;
      ML743 AT %ML743 : ULINT := 16#0123456789ABCDEF;
      ML744 AT %ML744 : ULINT := 16#0123456789ABCDEF;
      ML745 AT %ML745 : ULINT := 16#0123456789ABCDEF;
      ML746 AT %ML746 : ULINT := 16#0123456789ABCDEF;
      ML747 AT %ML747 : ULINT := 16#0123456789ABCDEF;
      ML748 AT %ML748 : ULINT := 16#0123456789ABCDEF;
      ML749 AT %ML749 : ULINT := 16#0123456789ABCDEF;
      ML750 AT %ML750 : ULINT := 16#0123456789ABCDEF;
      ML751 AT %ML751 : ULINT := 16#0123456789ABCDEF;
      ML752 AT %ML752 : ULINT := 16#0123456789ABCDEF;
      ML753 AT %ML753 : ULINT := 16#0123456789ABCDEF;
      ML754 AT %ML754 : ULINT := 16#0123456789ABCDEF;
      ML755 AT %ML755 : ULINT := 16#0123456789ABCDEF;
      ML756 AT %ML756 : ULINT := 16#0123456789ABCDEF;
      ML757 AT %ML757 : ULINT := 16#0123456789ABCDEF;
      ML758 AT %ML758 : ULINT := 16#0123456789ABCDEF;
      ML759 AT %ML759 : ULINT := 16#0123456789ABCDEF;
      ML760 AT %ML760 : ULINT := 16#0123456789ABCDEF;
      ML761 AT %ML761 : ULINT := 16#0123456789ABCDEF;
      ML762 AT %ML762 : ULINT := 16#0123456789ABCDEF;
      ML763 AT %ML763 : ULINT := 16#0123456789ABCDEF;
      ML764 AT %ML764 : ULINT := 16#0123456789ABCDEF;
      ML765 AT %ML765 : ULINT := 16#0123456789ABCDEF;
      ML766 AT %ML766 : ULINT := 16#0123456789ABCDEF;
      ML767 AT %ML767 : ULINT := 16#0123456789ABCDEF;
      ML768 AT %ML768 : ULINT := 16#0123456789ABCDEF;
      ML769 AT %ML769 : ULINT := 16#0123456789ABCDEF;
      ML770 AT %ML770 : ULINT := 16#0123456789ABCDEF;
      ML771 AT %ML771 : ULINT := 16#0123456789ABCDEF;
      ML772 AT %ML772 : ULINT := 16#0123456789ABCDEF;
      ML773 AT %ML773 : ULINT := 16#0123456789ABCDEF;
      ML774 AT %ML774 : ULINT := 16#0123456789ABCDEF;
      ML775 AT %ML775 : ULINT := 16#0123456789ABCDEF;
      ML776 AT %ML776 : ULINT := 16#0123456789ABCDEF;
      ML777 AT %ML777 : ULINT := 16#0123456789ABCDEF;
      ML778 AT %ML778 : ULINT := 16#0123456789ABCDEF;
      ML779 AT %ML779 : ULINT := 16#0123456789ABCDEF;
      ML780 AT %ML780 : ULINT := 16#0123456789ABCDEF;
      ML781 AT %ML781 : ULINT := 16#0123456789ABCDEF;
      ML782 AT %ML782 : ULINT := 16#0123456789ABCDEF;
      ML783 AT %ML783 : ULINT := 16#0123456789ABCDEF;
      ML784 AT %ML784 : ULINT := 16#0123456789ABCDEF;
      ML785 AT %ML785 : ULINT := 16#0123456789ABCDEF;
      ML786 AT %ML786 : ULINT := 16#0123456789ABCDEF;
      ML787 AT %ML787 : ULINT := 16#0123456789ABCDEF;
      ML788 AT %ML788 : ULINT := 16#0123456789ABCDEF;
      ML789 AT %ML789 : ULINT := 16#0123456789ABCDEF;
      ML790 AT %ML790 : ULINT := 16#0123456789ABCDEF;
      ML791 AT %ML791 : ULINT := 16#0123456789ABCDEF;
      ML792 AT %ML792 : ULINT := 16#0123456789ABCDEF;
      ML793 AT %ML793 : ULINT := 16#0123456789ABCDEF;
      ML794 AT %ML794 : ULINT := 16#0123456789ABCDEF;
      ML795 AT %ML795 : ULINT := 16#0123456789ABCDEF;
      ML796 AT %ML796 : ULINT := 16#0123456789ABCDEF;
      ML797 AT %ML797 : ULINT := 16#0123456789ABCDEF;
      ML798 AT %ML798 : ULINT := 16#0123456789ABCDEF;
      ML799 AT %ML799 : ULINT := 16#0123456789ABCDEF;
      ML800 AT %ML800 : ULINT := 16#0123456789ABCDEF;
      ML801 AT %ML801 : ULINT := 16#0123456789ABCDEF;
      ML802 AT %ML802 : ULINT := 16#0123456789ABCDEF;
      ML803 AT %ML803 : ULINT := 16#0123456789ABCDEF;
      ML804 AT %ML804 : ULINT := 16#0123456789ABCDEF;
      ML805 AT %ML805 : ULINT := 16#0123456789ABCDEF;
      ML806 AT %ML806 : ULINT := 16#0123456789ABCDEF;
      ML807 AT %ML807 : ULINT := 16#0123456789ABCDEF;
      ML808 AT %ML808 : ULINT := 16#0123456789ABCDEF;
      ML809 AT %ML809 : ULINT := 16#0123456789ABCDEF;
      ML810 AT %ML810 : ULINT := 16#0123456789ABCDEF;
      ML811 AT %ML811 : ULINT := 16#0123456789ABCDEF;
      ML812 AT %ML812 : ULINT := 16#0123456789ABCDEF;
      ML813 AT %ML813 : ULINT := 16#0123456789ABCDEF;
      ML814 AT %ML814 : ULINT := 16#0123456789ABCDEF;
      ML815 AT %ML815 : ULINT := 16#0123456789ABCDEF;
      ML816 AT %ML816 : ULINT := 16#0123456789ABCDEF;
      ML817 AT %ML817 : ULINT := 16#0123456789ABCDEF;
      ML818 AT %ML818 : ULINT := 16#0123456789ABCDEF;
      ML819 AT %ML819 : ULINT := 16#0123456789ABCDEF;
      ML820 AT %ML820 : ULINT := 16#0123456789ABCDEF;
      ML821 AT %ML821 : ULINT := 16#0123456789ABCDEF;
      ML822 AT %ML822 : ULINT := 16#0123456789ABCDEF;
      ML823 AT %ML823 : ULINT := 16#0123456789ABCDEF;
      ML824 AT %ML824 : ULINT := 16#0123456789ABCDEF;
      ML825 AT %ML825 : ULINT := 16#0123456789ABCDEF;
      ML826 AT %ML826 : ULINT := 16#0123456789ABCDEF;
      ML827 AT %ML827 : ULINT := 16#0123456789ABCDEF;
      ML828 AT %ML828 : ULINT := 16#0123456789ABCDEF;
      ML829 AT %ML829 : ULINT := 16#0123456789ABCDEF;
      ML830 AT %ML830 : ULINT := 16#0123456789ABCDEF;
      ML831 AT %ML831 : ULINT := 16#0123456789ABCDEF;
      ML832 AT %ML832 : ULINT := 16#0123456789ABCDEF;
      ML833 AT %ML833 : ULINT := 16#0123456789ABCDEF;
      ML834 AT %ML834 : ULINT := 16#0123456789ABCDEF;
      ML835 AT %ML835 : ULINT := 16#0123456789ABCDEF;
      ML836 AT %ML836 : ULINT := 16#0123456789ABCDEF;
      ML837 AT %ML837 : ULINT := 16#0123456789ABCDEF;
      ML838 AT %ML838 : ULINT := 16#0123456789ABCDEF;
      ML839 AT %ML839 : ULINT := 16#0123456789ABCDEF;
      ML840 AT %ML840 : ULINT := 16#0123456789ABCDEF;
      ML841 AT %ML841 : ULINT := 16#0123456789ABCDEF;
      ML842 AT %ML842 : ULINT := 16#0123456789ABCDEF;
      ML843 AT %ML843 : ULINT := 16#0123456789ABCDEF;
      ML844 AT %ML844 : ULINT := 16#0123456789ABCDEF;
      ML845 AT %ML845 : ULINT := 16#0123456789ABCDEF;
      ML846 AT %ML846 : ULINT := 16#0123456789ABCDEF;
      ML847 AT %ML847 : ULINT := 16#0123456789ABCDEF;
      ML848 AT %ML848 : ULINT := 16#0123456789ABCDEF;
      ML849 AT %ML849 : ULINT := 16#0123456789ABCDEF;
      ML850 AT %ML850 : ULINT := 16#0123456789ABCDEF;
      ML851 AT %ML851 : ULINT := 16#0123456789ABCDEF;
      ML852 AT %ML852 : ULINT := 16#0123456789ABCDEF;
      ML853 AT %ML853 : ULINT := 16#0123456789ABCDEF;
      ML854 AT %ML854 : ULINT := 16#0123456789ABCDEF;
      ML855 AT %ML855 : ULINT := 16#0123456789ABCDEF;
      ML856 AT %ML856 : ULINT := 16#0123456789ABCDEF;
      ML857 AT %ML857 : ULINT := 16#0123456789ABCDEF;
      ML858 AT %ML858 : ULINT := 16#0123456789ABCDEF;
      ML859 AT %ML859 : ULINT := 16#0123456789ABCDEF;
      ML860 AT %ML860 : ULINT := 16#0123456789ABCDEF;
      ML861 AT %ML861 : ULINT := 16#0123456789ABCDEF;
      ML862 AT %ML862 : ULINT := 16#0123456789ABCDEF;
      ML863 AT %ML863 : ULINT := 16#0123456789ABCDEF;
      ML864 AT %ML864 : ULINT := 16#0123456789ABCDEF;
      ML865 AT %ML865 : ULINT := 16#0123456789ABCDEF;
      ML866 AT %ML866 : ULINT := 16#0123456789ABCDEF;
      ML867 AT %ML867 : ULINT := 16#0123456789ABCDEF;
      ML868 AT %ML868 : ULINT := 16#0123456789ABCDEF;
      ML869 AT %ML869 : ULINT := 16#0123456789ABCDEF;
      ML870 AT %ML870 : ULINT := 16#0123456789ABCDEF;
      ML871 AT %ML871 : ULINT := 16#0123456789ABCDEF;
      ML872 AT %ML872 : ULINT := 16#0123456789ABCDEF;
      ML873 AT %ML873 : ULINT := 16#0123456789ABCDEF;
      ML874 AT %ML874 : ULINT := 16#0123456789ABCDEF;
      ML875 AT %ML875 : ULINT := 16#0123456789ABCDEF;
      ML876 AT %ML876 : ULINT := 16#0123456789ABCDEF;
      ML877 AT %ML877 : ULINT := 16#0123456789ABCDEF;
      ML878 AT %ML878 : ULINT := 16#0123456789ABCDEF;
      ML879 AT %ML879 : ULINT := 16#0123456789ABCDEF;
      ML880 AT %ML880 : ULINT := 16#0123456789ABCDEF;
      ML881 AT %ML881 : ULINT := 16#0123456789ABCDEF;
      ML882 AT %ML882 : ULINT := 16#0123456789ABCDEF;
      ML883 AT %ML883 : ULINT := 16#0123456789ABCDEF;
      ML884 AT %ML884 : ULINT := 16#0123456789ABCDEF;
      ML885 AT %ML885 : ULINT := 16#0123456789ABCDEF;
      ML886 AT %ML886 : ULINT := 16#0123456789ABCDEF;
      ML887 AT %ML887 : ULINT := 16#0123456789ABCDEF;
      ML888 AT %ML888 : ULINT := 16#0123456789ABCDEF;
      ML889 AT %ML889 : ULINT := 16#0123456789ABCDEF;
      ML890 AT %ML890 : ULINT := 16#0123456789ABCDEF;
      ML891 AT %ML891 : ULINT := 16#0123456789ABCDEF;
      ML892 AT %ML892 : ULINT := 16#0123456789ABCDEF;
      ML893 AT %ML893 : ULINT := 16#0123456789ABCDEF;
      ML894 AT %ML894 : ULINT := 16#0123456789ABCDEF;
      ML895 AT %ML895 : ULINT := 16#0123456789ABCDEF;
      ML896 AT %ML896 : ULINT := 16#0123456789ABCDEF;
      ML897 AT %ML897 : ULINT := 16#0123456789ABCDEF;
      ML898 AT %ML898 : ULINT := 16#0123456789ABCDEF;
      ML899 AT %ML899 : ULINT := 16#0123456789ABCDEF;
      ML900 AT %ML900 : ULINT := 16#0123456789ABCDEF;
      ML901 AT %ML901 : ULINT := 16#0123456789ABCDEF;
      ML902 AT %ML902 : ULINT := 16#0123456789ABCDEF;
      ML903 AT %ML903 : ULINT := 16#0123456789ABCDEF;
      ML904 AT %ML904 : ULINT := 16#0123456789ABCDEF;
      ML905 AT %ML905 : ULINT := 16#0123456789ABCDEF;
      ML906 AT %ML906 : ULINT := 16#0123456789ABCDEF;
      ML907 AT %ML907 : ULINT := 16#0123456789ABCDEF;
      ML908 AT %ML908 : ULINT := 16#0123456789ABCDEF;
      ML909 AT %ML909 : ULINT := 16#0123456789ABCDEF;
      ML910 AT %ML910 : ULINT := 16#0123456789ABCDEF;
      ML911 AT %ML911 : ULINT := 16#0123456789ABCDEF;
      ML912 AT %ML912 : ULINT := 16#0123456789ABCDEF;
      ML913 AT %ML913 : ULINT := 16#0123456789ABCDEF;
      ML914 AT %ML914 : ULINT := 16#0123456789ABCDEF;
      ML915 AT %ML915 : ULINT := 16#0123456789ABCDEF;
      ML916 AT %ML916 : ULINT := 16#0123456789ABCDEF;
      ML917 AT %ML917 : ULINT := 16#0123456789ABCDEF;
      ML918 AT %ML918 : ULINT := 16#0123456789ABCDEF;
      ML919 AT %ML919 : ULINT := 16#0123456789ABCDEF;
      ML920 AT %ML920 : ULINT := 16#0123456789ABCDEF;
      ML921 AT %ML921 : ULINT := 16#0123456789ABCDEF;
      ML922 AT %ML922 : ULINT := 16#0123456789ABCDEF;
      ML923 AT %ML923 : ULINT := 16#0123456789ABCDEF;
      ML924 AT %ML924 : ULINT := 16#0123456789ABCDEF;
      ML925 AT %ML925 : ULINT := 16#0123456789ABCDEF;
      ML926 AT %ML926 : ULINT := 16#0123456789ABCDEF;
      ML927 AT %ML927 : ULINT := 16#0123456789ABCDEF;
      ML928 AT %ML928 : ULINT := 16#0123456789ABCDEF;
      ML929 AT %ML929 : ULINT := 16#0123456789ABCDEF;
      ML930 AT %ML930 : ULINT := 16#0123456789ABCDEF;
      ML931 AT %ML931 : ULINT := 16#0123456789ABCDEF;
      ML932 AT %ML932 : ULINT := 16#0123456789ABCDEF;
      ML933 AT %ML933 : ULINT := 16#0123456789ABCDEF;
      ML934 AT %ML934 : ULINT := 16#0123456789ABCDEF;
      ML935 AT %ML935 : ULINT := 16#0123456789ABCDEF;
      ML936 AT %ML936 : ULINT := 16#0123456789ABCDEF;
      ML937 AT %ML937 : ULINT := 16#0123456789ABCDEF;
      ML938 AT %ML938 : ULINT := 16#0123456789ABCDEF;
      ML939 AT %ML939 : ULINT := 16#0123456789ABCDEF;
      ML940 AT %ML940 : ULINT := 16#0123456789ABCDEF;
      ML941 AT %ML941 : ULINT := 16#0123456789ABCDEF;
      ML942 AT %ML942 : ULINT := 16#0123456789ABCDEF;
      ML943 AT %ML943 : ULINT := 16#0123456789ABCDEF;
      ML944 AT %ML944 : ULINT := 16#0123456789ABCDEF;
      ML945 AT %ML945 : ULINT := 16#0123456789ABCDEF;
      ML946 AT %ML946 : ULINT := 16#0123456789ABCDEF;
      ML947 AT %ML947 : ULINT := 16#0123456789ABCDEF;
      ML948 AT %ML948 : ULINT := 16#0123456789ABCDEF;
      ML949 AT %ML949 : ULINT := 16#0123456789ABCDEF;
      ML950 AT %ML950 : ULINT := 16#0123456789ABCDEF;
      ML951 AT %ML951 : ULINT := 16#0123456789ABCDEF;
      ML952 AT %ML952 : ULINT := 16#0123456789ABCDEF;
      ML953 AT %ML953 : ULINT := 16#0123456789ABCDEF;
      ML954 AT %ML954 : ULINT := 16#0123456789ABCDEF;
      ML955 AT %ML955 : ULINT := 16#0123456789ABCDEF;
      ML956 AT %ML956 : ULINT := 16#0123456789ABCDEF;
      ML957 AT %ML957 : ULINT := 16#0123456789ABCDEF;
      ML958 AT %ML958 : ULINT := 16#0123456789ABCDEF;
      ML959 AT %ML959 : ULINT := 16#0123456789ABCDEF;
      ML960 AT %ML960 : ULINT := 16#0123456789ABCDEF;
      ML961 AT %ML961 : ULINT := 16#0123456789ABCDEF;
      ML962 AT %ML962 : ULINT := 16#0123456789ABCDEF;
      ML963 AT %ML963 : ULINT := 16#0123456789ABCDEF;
      ML964 AT %ML964 : ULINT := 16#0123456789ABCDEF;
      ML965 AT %ML965 : ULINT := 16#0123456789ABCDEF;
      ML966 AT %ML966 : ULINT := 16#0123456789ABCDEF;
      ML967 AT %ML967 : ULINT := 16#0123456789ABCDEF;
      ML968 AT %ML968 : ULINT := 16#0123456789ABCDEF;
      ML969 AT %ML969 : ULINT := 16#0123456789ABCDEF;
      ML970 AT %ML970 : ULINT := 16#0123456789ABCDEF;
      ML971 AT %ML971 : ULINT := 16#0123456789ABCDEF;
      ML972 AT %ML972 : ULINT := 16#0123456789ABCDEF;
      ML973 AT %ML973 : ULINT := 16#0123456789ABCDEF;
      ML974 AT %ML974 : ULINT := 16#0123456789ABCDEF;
      ML975 AT %ML975 : ULINT := 16#0123456789ABCDEF;
      ML976 AT %ML976 : ULINT := 16#0123456789ABCDEF;
      ML977 AT %ML977 : ULINT := 16#0123456789ABCDEF;
      ML978 AT %ML978 : ULINT := 16#0123456789ABCDEF;
      ML979 AT %ML979 : ULINT := 16#0123456789ABCDEF;
      ML980 AT %ML980 : ULINT := 16#0123456789ABCDEF;
      ML981 AT %ML981 : ULINT := 16#0123456789ABCDEF;
      ML982 AT %ML982 : ULINT := 16#0123456789ABCDEF;
      ML983 AT %ML983 : ULINT := 16#0123456789ABCDEF;
      ML984 AT %ML984 : ULINT := 16#0123456789ABCDEF;
      ML985 AT %ML985 : ULINT := 16#0123456789ABCDEF;
      ML986 AT %ML986 : ULINT := 16#0123456789ABCDEF;
      ML987 AT %ML987 : ULINT := 16#0123456789ABCDEF;
      ML988 AT %ML988 : ULINT := 16#0123456789ABCDEF;
      ML989 AT %ML989 : ULINT := 16#0123456789ABCDEF;
      ML990 AT %ML990 : ULINT := 16#0123456789ABCDEF;
      ML991 AT %ML991 : ULINT := 16#0123456789ABCDEF;
      ML992 AT %ML992 : ULINT := 16#0123456789ABCDEF;
      ML993 AT %ML993 : ULINT := 16#0123456789ABCDEF;
      ML994 AT %ML994 : ULINT := 16#0123456789ABCDEF;
      ML995 AT %ML995 : ULINT := 16#0123456789ABCDEF;
      ML996 AT %ML996 : ULINT := 16#0123456789ABCDEF;
      ML997 AT %ML997 : ULINT := 16#0123456789ABCDEF;
      ML998 AT %ML998 : ULINT := 16#0123456789ABCDEF;
      ML999 AT %ML999 : ULINT := 16#0123456789ABCDEF;
      ML1000 AT %ML1000 : ULINT := 16#0123456789ABCDEF;
      ML1001 AT %ML1001 : ULINT := 16#0123456789ABCDEF;
      ML1002 AT %ML1002 : ULINT := 16#0123456789ABCDEF;
      ML1003 AT %ML1003 : ULINT := 16#0123456789ABCDEF;
      ML1004 AT %ML1004 : ULINT := 16#0123456789ABCDEF;
      ML1005 AT %ML1005 : ULINT := 16#0123456789ABCDEF;
      ML1006 AT %ML1006 : ULINT := 16#0123456789ABCDEF;
      ML1007 AT %ML1007 : ULINT := 16#0123456789ABCDEF;
      ML1008 AT %ML1008 : ULINT := 16#0123456789ABCDEF;
      ML1009 AT %ML1009 : ULINT := 16#0123456789ABCDEF;
      ML1010 AT %ML1010 : ULINT := 16#0123456789ABCDEF;
      ML1011 AT %ML1011 : ULINT := 16#0123456789ABCDEF;
      ML1012 AT %ML1012 : ULINT := 16#0123456789ABCDEF;
      ML1013 AT %ML1013 : ULINT := 16#0123456789ABCDEF;
      ML1014 AT %ML1014 : ULINT := 16#0123456789ABCDEF;
      ML1015 AT %ML1015 : ULINT := 16#0123456789ABCDEF;
      ML1016 AT %ML1016 : ULINT := 16#0123456789ABCDEF;
      ML1017 AT %ML1017 : ULINT := 16#0123456789ABCDEF;
      ML1018 AT %ML1018 : ULINT := 16#0123456789ABCDEF;
      ML1019 AT %ML1019 : ULINT := 16#0123456789ABCDEF;
      ML1020 AT %ML1020 : ULINT := 16#0123456789ABCDEF;
      ML1021 AT %ML1021 : ULINT := 16#0123456789ABCDEF;
      ML1022 AT %ML1022 : ULINT := 16#0123456789ABCDEF;
      ML1023 AT %ML1023 : ULINT := 16#0123456789ABCDEF;
    END_VAR
    TASK T_Conf(SINGLE := F_Conf,PRIORITY := 0);
    TASK T_Res(SINGLE := F_Res,PRIORITY := 0);
    TASK T_Prio0(INTERVAL := T#1000ms,PRIORITY := 0);
    TASK T_Prio1(INTERVAL := T#5s,PRIORITY := 1);
    TASK T_Prio2(INTERVAL := T#10s,PRIORITY := 2);
    TASK T_Prio3(INTERVAL := T#15s,PRIORITY := 3);
    TASK T_Prio4(INTERVAL := T#30s,PRIORITY := 4);
    PROGRAM IConf WITH T_Conf : P_CONF;
    PROGRAM IRes WITH T_Res : P_RES;
    PROGRAM IEval WITH T_Prio0 : P_EVAL;
    PROGRAM IMod1 WITH T_Prio1 : P_MOD1;
    PROGRAM IMod2 WITH T_Prio2 : P_MOD2;
  END_RESOURCE
END_CONFIGURATION
