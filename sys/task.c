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
** file name:           task.c
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
#ifdef _OSCUS_CR_TASK_

/******************************************************************************
 * type and variable
 *
 *
 *****************************************************************************/
 crTskType crTskTbl[CR_TASK_NUM] = {0x00};
 crByte crRdyTskGrp = 0x00;
 crByte crRdyTskRow[CR_RR_PPL_NUM] = {0x00};
 crByte crRdyTskCol[CR_RR_PPL_NUM] = {0x00};
 crByte crRdyTskIdx = 0x00;  
 crByte crPendTskGrp = 0x00;
 crByte crPendTskRow[CR_RR_PPL_NUM] = {0x00};
 crByte crPendTskCol[CR_RR_PPL_NUM] = {0x00};
 crByte crPendTskIdx = 0x00;  
 crByte crRunning = CR_FALSE;
 crByte crPendLock = CR_FALSE;

/******************************************************************************
 * task schedule
 *
 *
 *****************************************************************************/
 void crTaskSched()
 {
    crByte BitX,BitY;    
    //crAssert("crTskSched begin:0x%02x\r\n", crRdyTskGrp != 0x00);

    BitY = CR_DBIT_FSB(crRdyTskGrp);
    BitX = CR_DBIT_NXT(crRdyTskRow[BitY], crRdyTskCol[BitY]);
    crRdyTskCol[BitY] = BitX;  
    crRdyTskIdx = CR_BIT_OR(CR_BIT_LSHIFT(BitY,2), BitX);
     
    //crAssert("crTskSched end:%d\r\n", crTskTbl[crRdyTskIdx].entry != (void*)0x00 );
 }
  
/******************************************************************************
 * start oscus
 *
 *
 *****************************************************************************/
 void  crStart (void)
 {            
    crTskType *ptcb; 
  
    #ifdef _OSCUS_CR_LOGO_ 
      crLogoPrint();
    #endif /*_OSCUS_CR_LOGO_*/
  
    if(!(crRdyTskRow[0] & 0x01)){
      crPrintf("no idle task\r\n");
      while(1);
    }
    
    crMQInit(); 
    crRunning = CR_TRUE;   
    do{
      crTaskSched();
      ptcb = &(crTskTbl[crRdyTskIdx]);
      #ifdef _OSCUS_CR_TASK_EX_
        ptcb[0].entry(ptcb[0].argc, ptcb[0].argv);
      #else
        ptcb[0].entry();
      #endif
    }while(1); 
 }

/******************************************************************************
 * task create
 *
 *
 *****************************************************************************/
 #ifdef _OSCUS_CR_TASK_EX_
   crByte crTaskCreate (void (*entry)(crByte,crByte*), crByte argc, crByte *argv, crByte prio)
 #else
   crByte crTaskCreate (void (*entry)(), crByte prio) 
 #endif
 {
    crByte BitX,BitY;    
    //crAssert("crTaskCreate begin:%d\r\n", prio < CR_TASK_NUM );
    
    crTskTbl[prio].entry = entry;
    #ifdef _OSCUS_CR_TASK_EX_
      crTskTbl[prio].argc = argc;
      crTskTbl[prio].argv = argv;
    #endif
    
    BitY = CR_BIT_RSHIFT(prio, 2);
    BitX = CR_BIT_AND(prio, 3);
    CR_BIT_SETH(crRdyTskGrp, BitY);
    if(crRdyTskRow[BitY] == 0x00){
      crRdyTskCol[BitY] = 0;
    }
    CR_BIT_SETH(crRdyTskRow[BitY], BitX);
    
    //crAssert("crTaskCreate end:%d\r\n", prio );
    return prio;
 }

/******************************************************************************
 * task delete
 *
 *
 *****************************************************************************/
 //crByte crTaskDelete (crByte prio)
 //{
 //}

/******************************************************************************
 * task resume
 *
 *
 *****************************************************************************/
 crByte  crTaskResume (crByte prio)
 {  
    crByte BitX,BitY;    
    //crAssert("crTskResume begin:%d\r\n", (prio < CR_TASK_NUM)&&(prio != 0X00) );

    if( prio == 0x00 ){
      crPrintf( "crTaskResume err:idle task\r\n" );
      return CR_FALSE;
    }
    
    if( crTskTbl[prio].entry == 0x00 ){
      crPrintf( "crTaskResume err:invalid prio\r\n" );
      return CR_FALSE;
    }
    
    BitY = CR_BIT_RSHIFT(prio, 2);
    BitX = CR_BIT_AND(prio, 0x03);
    
    CR_BIT_SETH(crRdyTskGrp, BitY);
    if(crRdyTskRow[BitY] == 0x00){
      crRdyTskCol[BitY] = 0;
    }
    CR_BIT_SETH(crRdyTskRow[BitY], BitX);  

    CR_BIT_SETL(crPendTskRow[BitY], BitX);
    if( crPendTskRow[BitY] == 0x00 ){
      CR_BIT_SETL(crPendTskGrp, BitY); 
    }    
    
    //crAssert("crTaskResume end:0x%02x\r\n", prio );
    return CR_TRUE;    
 }

/******************************************************************************
 * suspend task
 *
 *
 *****************************************************************************/
 crByte  crTaskSuspend (crByte prio)
 { 
    crByte BitX,BitY;    
    //crAssert("crTskSuspend begin:%d\r\n", (prio < CR_TASK_NUM)&&(prio != 0X00) );

    if( prio == 0x00 ){
      crPrintf( "crTaskSuspend err:idle task\r\n" );
      return CR_FALSE;
    }
    
    if( crTskTbl[prio].entry == 0x00 ){
      crPrintf( "crTaskSuspend err:invalid prio\r\n");
      return CR_FALSE;
    }
    
    BitY = CR_BIT_RSHIFT(prio, 2);
    BitX = CR_BIT_AND(prio, 0x03);    


    CR_BIT_SETH(crPendTskGrp, BitY);
    if(crPendTskRow[BitY] == 0x00){
      crPendTskCol[BitY] = BitX;
    }
    CR_BIT_SETH(crPendTskRow[BitY], BitX);
    
    CR_BIT_SETL(crRdyTskRow[BitY], BitX);
    if( crRdyTskRow[BitY] == 0x00 ){
      CR_BIT_SETL(crRdyTskGrp, BitY); 
    }      
    
    //crAssert("crTskSuspend end:0x%02x\r\n", prio );
    return CR_TRUE;
 }
 
/******************************************************************************
 * task timer
 *
 *
 *****************************************************************************/
 void crTaskTimer( void)
 {
    crByte BitX,BitY,BitZ;  
    crByte BitX0, BitY0;
    //crAssert("crTaskTimer begin\r\n");

    if( CR_PEND_LOCKED ){
      crAssert("pend locked\r\n");
      return;    
    }
    
    if( crPendTskGrp == 0x00 ){
      crAssert("no pend task\r\n");
      return;
    }
      
    BitY = CR_DBIT_FSB(crPendTskGrp);    
    do{
      BitZ = crPendTskRow[BitY];
      BitX = CR_DBIT_FSB(BitZ);      
      do{  
        crPendTskIdx = CR_BIT_OR(CR_BIT_LSHIFT(BitY,2), BitX);
        if( crTskDlyTbl[crPendTskIdx].timeout ){
          if(--crTskDlyTbl[crPendTskIdx].timeout == 0){
            crTskSemTbl[crPendTskIdx].semid = CR_INVALID;
            crMQTbl[crTskMQTbl[crPendTskIdx].mqid].tskid = CR_INVALID;
            crTskMQTbl[crPendTskIdx].msg = 0;
            crTskMQTbl[crPendTskIdx].len = 0;
            CR_TASK_RESUME();
          }
        }
        BitZ = crPendTskRow[BitY];
        BitX0 = BitX;
      }while( (BitZ != 0) && (BitX0 > (BitX = CR_DBIT_NXT(BitZ, BitX))) );   
      BitY0 = BitY;
    }while( (crPendTskGrp != 0) && ( BitY0 > (BitY = CR_DBIT_NXT(crPendTskGrp, BitY))) );    
    
    //crAssert("crTaskTimer end:0x%02x\r\n", crPendTskGrp != 0x00);
    return;
 }
 
#endif /*_OSCUS_CR_TASK_*/ 
/*************************************END*************************************/
