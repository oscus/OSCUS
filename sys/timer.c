/******************************************************************************
**
**                  [[[[[    [[[[[    [[[[[   [[[  [[   [[[[[           
**                 [[[  [[  [[[[     [[[      [[[  [[  [[[[              
**                 [[[  [[   [[[[    [[[      [[[  [[   [[[[             
**                 [[[  [[    [[[[   [[[      [[[  [[    [[[[            
**                  [[[[[   [[[[[     [[[[[    [[[[[[  [[[[[  
**
**
**-----------------------------------------------------------------------------
** file name:           timer.c
** data:                mm/dd/yy
** version:             1.x
** descriptions:        
**-----------------------------------------------------------------------------
** created by:          songg
** created date:        mm/dd/yy
** version:             0.0.1
** brief:        
******************************************************************************/

 #include "cr.h"
#ifdef _OSCUS_CR_TIMER_

/******************************************************************************
 * type and variable
 *
 *
 *****************************************************************************/
 crTskDlyType crTskDlyTbl[CR_TASK_NUM] = {0};
 
/******************************************************************************
 * system timer
 *
 *
 *****************************************************************************/
 void crSysDelay( crWord ms )
 { 
    //crAssert("crSysDelay begin:%d\r\n", crRdyTskIdx);
     
    CR_TASK_DELAY(ms);
     
    CR_PEND_LOCK();
    CR_TASK_PEND();   
    CR_PEND_UNLOCK();
     
    //crAssert("crSysDelay end\r\n");     
 }
 
/******************************************************************************
 * system ticks
 *
 *
 *****************************************************************************/
 void crSysTicks( void)
 { 
    //crAssert("crSysTicks begin\r\n");

    crTaskTimer();
     
    //crAssert("crSysTicks end\r\n");
    return;
 }
 
#endif /*_OSCUS_CR_TIMER_*/ 
/*************************************END*************************************/
