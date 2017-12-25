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
** file name:           config.h
** data:                mm/dd/yy
** version:             1.x
** descriptions:        
**-----------------------------------------------------------------------------
** created by:          songg
** created date:        mm/dd/yy
** version:             0.0.1
** brief:        
******************************************************************************/
#ifndef _OSCUS_CONFIG_H_
#define _OSCUS_CONFIG_H_

/******************************************************************************
 * config
 *
 *
 *****************************************************************************/
 #define _OSCUS_CR_LOGO_
 #define _OSCUS_CR_DSK_
 #define _OSCUS_CR_TASK_
 #undef  _OSCUS_CR_TASK_EX_ 
 #undef  _OSCUS_CR_TASK_MON_ 
 #define _OSCUS_CR_TIMER_
 #define _OSCUS_CR_SEM_
 #define _OSCUS_CR_MQ_ 
 #define _OSCUS_CR_EXAM_ 

 #define CR_LOGO_CHAR   '['
 #define CR_LOGO_INVERT  0
 #define CR_PRIO_LEVEL_NUM 0x04
 #define CR_RR_PPL_NUM     0x04
 #define CR_TASK_NUM (CR_PRIO_LEVEL_NUM*CR_RR_PPL_NUM)
 #define CR_SEM_NUM   16
 #define CR_MQ_NUM    16
 #define CR_MQ_B_NUM  4
 #define CR_MQ_B_LEN  16 
 #define CR_SYS_TIMER_PERIOD  10 

#endif /*_OSCUS_CONFIG_H_*/
/*************************************END*************************************/
