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
** file name:           oscus.h
** data:                mm/dd/yy
** version:             1.x
** descriptions:        
**-----------------------------------------------------------------------------
** created by:          songg
** created date:        mm/dd/yy
** version:             1.x
** brief:
**=============================================================================
** OSCUS is an open source OS.
**
** Features:
**    - Co-operative multitasking, without complex stack management
**    - Two-level scheduling mechanics, priority-based(maximum eq 0x04)
**    - and round-robin in each priority level(maximum eq 0x04)
**    - Maximum task number eq 16
**    - Rapid task switch, time complexity O(1)
**     
**
** Model:
**    - Task priority ranges from 0x00 to 0x0F
**    - When there are no tasks in the higher priority level group,
**      controller will be give to tasks in the lower priority
**    - When two or more tasks have the same priority, 
**      controller will be given to the next after the previous run-to-completion
**    - Task 0 as idle routine, must be defined
**
**      Round-robing scheduling in each group
**      --->
**      | F | E | D | C |    - priority level 3  - highest    | Priority-based 
**      | B | A | 9 | 8 |    - priority level 2               V scheduling
**      | 7 | 6 | 5 | 4 |    - priority level 1               
**      | 3 | 2 | 1 | 0 |    - priority level 0  - lowest   
**
**
** Examples:
**
** To define a coroutine, a task function looks like these.
**
** void crTask1st(crByte argc, crByte *argv)
** {
**    static crByte i = 0;
**    CR_BEGIN;
**   
**    if( i++ == 0xFF ){
**        crPrintf( "crTask1st i: %d\r\n", i);
**        crReturn;
**    } 
**     
**    CR_END;   
** }
**
** void crTask2nd(crByte argc, crByte *argv)
** {
**    static crByte i = 0;
**    CR_BEGIN;
**   
**    while( 1 )
**    {
**        i++;
**        crPrintf( "crTask2nd begin: %d\r\n", i);
**        crDelay( 5000 );
**        crPrintf( "crTask2nd end\r\n");
**        crDelay( 5000 );
**    }
**     
**    CR_END;   
** }
**    
** The main functon call all of the above croutine task, 
** then start oscus.
** 
** void main( void ){
**    
**    crTaskCreate( crTask1st, 0, 0, 1 );
**    crTaskCreate( crTask2nd, 0, 0, 2 );
**
**    crStart();
** }
**
** Otherwise, crSysTimer() should be called in a SYSTEM TIMER ISR.
**
**=============================================================================
**    THE BIRD IS FLYING,
**    THE MONKEY IS JUMPING,
**    THE BOY IS SLEEPING,
**    THE PHONE IS RINGING,           
**    THE SAW IS DRILLING,
**    THE STRANGERS ARE TALKING,
**    THE LIFE GOES ON.
**
**    SOMEONE NEED MORE TIME,
**    SOMEONE NEED A PLACE,
**    SOMEONE NEED TO BE ALONE.
**=============================================================================
**
** IF ALL OF THESE ARE HELPFUL TO YOU, PLEASE R.
**
******************************************************************************/
#ifndef _OSCUS_H_
#define _OSCUS_H_

 #include "./sys/cr.h"

#endif /*_OSCUS_H_*/
/*************************************END*************************************/
