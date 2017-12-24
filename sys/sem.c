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
** file name:           sem.c
** data:                mm/dd/yy
** version:             1.x
** descriptions:        
**-----------------------------------------------------------------------------
** created by:          songg
** created date:        mm/dd/yy
** version:             1.x
** brief:        
******************************************************************************/

 #include "cr.h"
#ifdef _OSCUS_CR_SEM_

/******************************************************************************
 * type and variable
 *
 *
 *****************************************************************************/
 crTskSemType crTskSemTbl[CR_TASK_NUM] = {0};
 crSemType    crSemTbl[CR_SEM_NUM] = {0};


/******************************************************************************
 * sem pend
 *
 *
 *****************************************************************************/
 void crSemPend(crByte id, crWord ms)
 {
    //crAssert("crSemPend begin\r\n");

    if( id >= CR_SEM_NUM ){
      crPrintf("err:no such sem\r\n");
      return ;
    }
    
    crTskSemTbl[crRdyTskIdx].semid = id;
    crSemTbl[id].used++;
    CR_TASK_DELAY(ms);    
    
    CR_PEND_LOCK();
    CR_TASK_PEND();
    CR_PEND_UNLOCK();
     
    //crAssert("crSemPend end\r\n");
    return;    
 }
 
/******************************************************************************
 * sem post
 * FYI: resume all pend tasks
 *
 *****************************************************************************/
 void crSemPost(crByte id)
 {
    crByte BitX,BitY,BitZ;  
    crByte BitX0, BitY0;
    //crAssert("crSemPost begin\r\n");

    if( id >= CR_SEM_NUM ){
      crPrintf("err:no such sem\r\n");
      return ;
    }
    
    CR_PEND_LOCK();
    if( crSemTbl[id].used > 0 ){
      BitY = CR_DBIT_FSB(crPendTskGrp);
      do{
        BitZ = crPendTskRow[BitY];
        BitX = CR_DBIT_FSB(BitZ); 
        do{  
          crPendTskIdx = CR_BIT_OR(CR_BIT_LSHIFT(BitY,2), BitX);
          if( crTskSemTbl[crPendTskIdx].semid == id ){
            crTskSemTbl[crPendTskIdx].semid = CR_INVALID;
            CR_TASK_RESUME();
          }
          BitZ = crPendTskRow[BitY];
          BitX0 = BitX;
        }while( (BitZ != 0) && (BitX0 > (BitX = CR_DBIT_NXT(BitZ, BitX))) ); 
        BitY0 = BitY;
      }while( (crPendTskGrp != 0) && ( BitY0 > (BitY = CR_DBIT_NXT(crPendTskGrp, BitY))) );       
      crSemTbl[id].used = 0;
    }else{
      crSemTbl[id].cnt++;
    }
    CR_PEND_UNLOCK();
    
    //crAssert("crSemPost end\r\n");
    return;
 } 
 
#endif /*_OSCUS_CR_SEM_*/ 
/*************************************END*************************************/
