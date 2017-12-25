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
** file name:           mq.c
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
#ifdef _OSCUS_CR_MQ_

/******************************************************************************
 * type and variable
 *
 *
 *****************************************************************************/
 crTskMQType crTskMQTbl[CR_TASK_NUM] = {0};
 crMQType    crMQTbl[CR_MQ_NUM] = {0};
 crMQBType   crMQBTbl[CR_MQ_B_NUM] = {0};
 crByte      crMQBHead;
 crByte      crMQBUsed;
 
 /******************************************************************************
 * mq pick
 *
 *
 *****************************************************************************/
 void crMQPick(crByte id, crByte *msg, crWord *len)
 {
    crByte mqbid;
    //crAssert("crMQPick begin\r\n");
    
    if( id >= CR_MQ_NUM ){
      *len = 0;
      return ;
    }
    
    if( msg == 0 || *len < crMQBTbl[crMQTbl[id].head].len ){
      *len = 0;
      return ;
    }
     
    mqbid = crMQTbl[id].head;
    *len = crMQBTbl[mqbid].len;
    crMemcpy( msg, crMQBTbl[mqbid].msg, *len );
    
    crMQTbl[id].head = CR_ALIST_IDX( mqbid );
	CR_ALIST_LINK( mqbid, crMQBHead );
    crMQBHead = mqbid;
    crMQBUsed--;
    
    //crAssert("crMQPick end\r\n");
    return;    
 }
 
 /******************************************************************************
 * mq pend
 *
 *
 *****************************************************************************/
 void crMQPend(crByte id, crByte *msg, crWord *len, crWord ms)
 {
    //crAssert("crMQPend begin\r\n");
 
    if( id >= CR_MQ_NUM ){
      *len = 0;
      return ;
    }
    
    if( msg == 0 ){
      *len = 0;
      return ;
    }

    crMQTbl[id].tskid = crRdyTskIdx;   
    crTskMQTbl[crRdyTskIdx].mqid = id;
    crTskMQTbl[crRdyTskIdx].msg = msg;
    crTskMQTbl[crRdyTskIdx].len = len; 
    CR_TASK_DELAY(ms);
    
    CR_PEND_LOCK();
    CR_TASK_PEND();
	CR_PEND_UNLOCK();
     
    //crAssert("crMQPend end\r\n");
    return;    
 }
 
/******************************************************************************
 * mq post
 *
 *
 *****************************************************************************/
 void crMQPost(crByte id, crByte *msg, crWord len)
 {  
    crByte mqbid;
    //crAssert("crMQPost begin\r\n");
 
    if(id >= CR_MQ_NUM || crMQBUsed >= CR_MQ_B_NUM){
      return;
    }

    if( msg == 0 || len >= CR_MQ_B_LEN){
      return;
    }

    if( (crPendTskIdx = crMQTbl[id].tskid) == CR_INVALID ){  
      mqbid = crMQBHead;
      crMQBHead = CR_ALIST_IDX(crMQBHead);   	
	  CR_ALIST_LINK( mqbid, CR_INVALID );
      crMemcpy( crMQBTbl[mqbid].msg, msg, len); 
      crMQBTbl[mqbid].len = len;

      if( crMQTbl[id].head == CR_INVALID ){
    	crMQTbl[id].head = mqbid;
      }else{
		CR_ALIST_LINK( crMQTbl[id].tail, mqbid );
      }
      crMQTbl[id].tail = mqbid; 
      crMQTbl[id].cnt++;  	    
      crMQBUsed++;
    }else{  
      crMemcpy( crTskMQTbl[crPendTskIdx].msg, msg, len);
      *crTskMQTbl[crPendTskIdx].len = len;
      crMQTbl[id].tskid = CR_INVALID;
      
      CR_PEND_LOCK(); 
      CR_TASK_RESUME(); 
      CR_PEND_UNLOCK();
    }
    
    //crAssert("crMQPost end\r\n");
    return;
 } 
 
 /******************************************************************************
 * mq init
 *
 *
 *****************************************************************************/
 void crMQInit( void)
 {
 	  crByte i;
    //crAssert("crMQInit begin\r\n"); 	  

    for( i=0; i<CR_MQ_NUM; i++ )
    {
      crMQTbl[i].tskid = CR_INVALID;
      crMQTbl[i].head = CR_INVALID;
      crMQTbl[i].tail = CR_INVALID;
    }
     	  
    for( i=0; i<(CR_MQ_B_NUM - 1); i++ )
    {
	  CR_ALIST_LINK( i, i+1 );
    }
	CR_ALIST_LINK( i, CR_INVALID );
    crMQBHead = 0;
    crMQBUsed = 0;
    
    //crAssert("crMQInit end\r\n");
    return;    
 }
 
#endif /*_OSCUS_CR_MQ_*/ 
/*************************************END*************************************/
