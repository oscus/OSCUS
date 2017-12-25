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
** file name:           cr.h
** data:                mm/dd/yy
** version:             1.x
** descriptions:        
**-----------------------------------------------------------------------------
** created by:          songg
** created date:        mm/dd/yy
** version:             0.0.1
** brief:        
******************************************************************************/

#ifndef _OSCUS_CR_H_
#define _OSCUS_CR_H_

 #include "config.h"
 
/******************************************************************************
 * arch-relative
 *
 *
 *****************************************************************************/
  
 #define crAssert printf
 #define crPrintf printf
 #define crMemcpy memcpy
 
 typedef unsigned char  crByte;
 typedef unsigned int   crWord; 
 
/******************************************************************************
 * const var
 *
 *
 *****************************************************************************/  
 #define CR_FALSE   0x00
 #define CR_TRUE    0x01
 #define CR_ERR_1   0xF1 
 #define CR_ERR_2   0xF2
 #define CR_EXP     0xFE
 #define CR_INVALID 0xFF
 
/******************************************************************************
 * co-operative routine
 *
 *
 *****************************************************************************/
 #define CR_BEGIN  static int scrLine = 0;\
                      switch(scrLine) { case 0:
 #define crReturn  do {\
            scrLine=__LINE__;\
            return; case __LINE__:;\
         }while(0)
 #define CR_END    } return
 
/******************************************************************************
 * logo
 *
 *
 *****************************************************************************/ 
 #ifdef _OSCUS_CR_LOGO_ 
 
 void crLogoPrint( void );
 
 #endif /*_OSCUS_CR_LOGO_*/  
 /******************************************************************************
 * DDB
 *
 *
 *****************************************************************************/ 
 #ifdef _OSCUS_CR_DSK_ 
 
 extern crByte const crDskTbl[][CR_RR_PPL_NUM];
 
 #define CR_DBIT_FSB(x) crDskTbl[x][0]
 #define CR_DBIT_NXT(x,y) crDskTbl[x][y]  
 
 #define CR_BIT_LSHIFT(x,y) (x << y)
 #define CR_BIT_RSHIFT(x,y) (x >> y)
 #define CR_BIT_AND(x,y) (x & y)
 #define CR_BIT_OR(x,y)  (x | y) 
 #define CR_BIT_SETH(x,y) (x |= 0x01<<y)
 #define CR_BIT_SETL(x,y) (x &= ~(0x01<<y)) 
 
 #endif /*_OSCUS_CR_DSK_*/  
/******************************************************************************
 * task
 *
 *
 *****************************************************************************/
 #ifdef _OSCUS_CR_TASK_
 
 typedef struct{
    #ifdef _OSCUS_CR_TASK_EX_
      crByte   argc;
      crByte  *argv;     
      void (*entry)(crByte argc, crByte* argv);     
    #else
      void (*entry)();  
    #endif
 }crTskType;
 
 extern  crByte const crMskTbl[][CR_RR_PPL_NUM];
 extern  crByte crRdyTskIdx;
 extern  crByte crPendTskGrp;
 extern  crByte crPendTskRow[CR_RR_PPL_NUM];
 extern  crByte crPendTskCol[CR_RR_PPL_NUM];
 extern  crByte crPendTskIdx; 
 extern  crByte crPendLock; 
 
 #define CR_PEND_LOCK()     (crPendLock = CR_TRUE)
 #define CR_PEND_UNLOCK()   (crPendLock = CR_FALSE)
 #define CR_PEND_LOCKED     (crPendLock == CR_TRUE) 
 
 void   crStart (void);
 #ifdef _OSCUS_CR_TASK_EX_
   crByte crTaskCreate (void (*entry)(crByte,crByte*), crByte argc, crByte *argv, crByte prio);
 #else
   crByte crTaskCreate (void (*entry)(), crByte prio); 
 #endif 
 crByte crTaskResume (crByte prio);
 crByte crTaskSuspend (crByte prio);
 void   crTaskTimer();

 #define CR_TASK_RESUME() crTaskResume( crPendTskIdx )
 #define CR_TASK_PEND()   crTaskSuspend(crRdyTskIdx)

 #endif /*_OSCUS_CR_TASK_*/
/******************************************************************************
 * timer
 *
 *
 *****************************************************************************/
 #ifdef _OSCUS_CR_TIMER_ 
 
 typedef struct{
    crWord  timeout;     
 }crTskDlyType;
 extern  crTskDlyType crTskDlyTbl[CR_TASK_NUM];
 
 #define CR_TASK_DELAY(x) (crTskDlyTbl[crRdyTskIdx].timeout = x)
 
 void crSysDelay( crWord ms );
 #define crDelay(ms) \
 do{ \
    crSysDelay( ms ); \
    crReturn; \
 }while(0)
 void crSysTimer( void);
 
 #endif /*_OSCUS_CR_TIMER_*/  
/******************************************************************************
 * sem
 *
 *
 *****************************************************************************/
 #ifdef _OSCUS_CR_SEM_ 
 
 typedef struct{
    crByte  semid;     
 }crTskSemType;
 extern crTskSemType crTskSemTbl[CR_TASK_NUM];
 
 typedef struct{
    crByte   used;     
    crByte   cnt;
 }crSemType;
 extern  crSemType  crSemTbl[CR_SEM_NUM];
 
 void crSemPend(crByte id, crWord ms);    
 #define crSemWait(id,ms) \
 do{ \
   if( crSemTbl[id].cnt ){ \
     crSemTbl[id].cnt--; \
   }else{ \
     crSemPend(id, ms); \
     crReturn; \
   } \
 }while(0)
 void crSemPost(crByte id);
 
 #endif /*_OSCUS_CR_SEM_*/
 
/******************************************************************************
 * mq
 *
 *
 *****************************************************************************/
 #ifdef _OSCUS_CR_MQ_ 
 
 typedef struct{ 
    crByte  mqid;
    crByte  *msg;
    crWord  *len;     
 }crTskMQType;
 extern crTskMQType crTskMQTbl[CR_TASK_NUM];
 
 typedef struct{
    crByte   tskid;
    crByte   cnt;     
    crByte   head;
    crByte   tail;
 }crMQType;
 extern  crMQType  crMQTbl[CR_MQ_NUM];
 
 typedef struct{
    crByte   msg[CR_MQ_B_LEN];    
    crByte   len;     
    crByte   idx;
 }crMQBType; 

 #define CR_ALIST_IDX(x) (crMQBTbl[x].idx)
 #define CR_ALIST_LINK(x,y) (crMQBTbl[x].idx = y)

 void crMQInit( void); 
 void crMQPick(crByte id, crByte *msg, crWord *len);   
 void crMQPend(crByte id, crByte *msg, crWord *len, crWord ms);    
 #define crMQWait(id,msg,len,ms) \
 do{ \
   if( crMQTbl[id].cnt ){ \
     crMQPick(id,msg,len); \
     crMQTbl[id].cnt--; \
   }else{ \
     crMQPend(id,msg,len,ms); \
     crReturn; \
   } \
 }while(0) 
 void crMQPost(crByte id, crByte *msg, crWord len);
 
 #endif /*_OSCUS_CR_MQ_*/ 
#endif /*_OSCUS_CR_H_*/
/*************************************END*************************************/
