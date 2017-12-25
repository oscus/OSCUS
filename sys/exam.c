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
** file name:           exam.c
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
#ifdef _OSCUS_CR_EXAM_

/******************************************************************************
 * for test
 *
 *
 *****************************************************************************/
 void crTsk0()
 {
    CR_BEGIN;     
    //crPrintf( "crTsk0\r\n");
    CR_END;    
 }

  void crTsk1()
 {
    static crByte i = 0;
    CR_BEGIN;
     
    do{
        i++;
        crPrintf( "crTsk1 begin: %d\r\n", i);
        crDelay( 6 );
        crPrintf( "crTsk1 end\r\n");
    }while( 1 );       
    
    CR_END;   
 }
 
  void crTsk2()
 {
    static crByte i = 0;
    CR_BEGIN;
     
    do{
        i++;
        crPrintf( "crTsk2 begin: %d\r\n", i);
        crDelay( 6 );
        crPrintf( "crTsk2 end\r\n");
    }while( 1 );       
    
    CR_END;   
 }
 
 void crTsk4()
 {
    static crByte i = 0;     
    CR_BEGIN;
 
    do{
        i++;
        crPrintf( "crTsk4 begin: %d\r\n", i);        
        crSemPost( 6 );
        crPrintf( "crTsk4 end: %d\r\n", i);
        crDelay(100);
    }while( 1 );   

    CR_END;  
 }
 
 void crTsk5()
 {
    static crByte i = 0;     
    CR_BEGIN;
 
    do{
        i++;
        crPrintf( "crTsk5 begin: %d\r\n", i);        
        crSemWait( 6, 10);
        crPrintf( "crTsk5 end: %d\r\n", i);
    }while( 1 );  

    CR_END;  
 }

 void crTsk6()
 {
    static crByte i = 0;     
    CR_BEGIN;
 
    do{
        i++;
        crPrintf( "crTsk6 begin: %d\r\n", i);        
        crSemWait( 6, 10);
        crPrintf( "crTsk6 end: %d\r\n", i);
    }while( 1 );  

    CR_END;  
 }
 
 void crTsk8()
 {
    static crByte i = 0;     
    CR_BEGIN;
 
    do{
        i++;
        crPrintf( "crTsk8 begin: %d\r\n", i);        
        crSemWait( 6, 10);
        crPrintf( "crTsk8 end: %d\r\n", i);
    }while( 1 );  

    CR_END;  
 }
 
  void crTsk9()
 {
    static crByte i = 0;
    static crByte tsk9msg0[10] = "abcdefg123";
    static crByte tsk9msg1[10] = "abcdefg456";
    static crByte tsk9msg2[10] = "abcdefg789";     
    CR_BEGIN;  
     
    do{
        i++;
        crPrintf( "crTsk9 begin: %d\r\n", i);
        crDelay( 6 );
        crMQPost(1, tsk9msg0, 10);
        //crMQPost(1, tsk9msg1, 10);
        //crMQPost(1, tsk9msg2, 10);        
        crPrintf( "crTsk9 end\r\n");
        crDelay( 500 );  
    }while( 1 );     
    
    CR_END;     
 }

 void crTsk10()
 {
    static crByte i = 0;  
    static crByte tsk10msg[10] = {0xFF};     
    static crWord tsk10len = 10;
    CR_BEGIN;
 
    do{
        i++;
        crPrintf( "crTsk10 begin: %d\r\n", i);
        tsk10len = 10;
        crMQWait( 1, tsk10msg, &tsk10len, 3);
        if( tsk10len > 0){
            crPrintf( "crTsk10 getmsg: len %d\r\n", tsk10len);
        }
        crDelay(400);
        crPrintf( "crTsk10 end: %d\r\n", i);
    }while( 1 );   

    CR_END;  
 }
 
 
 
 void crTsk12()
 {
    CR_BEGIN;  
     
    crPrintf( "crTsk12\r\n");
    crTaskSuspend(12);
     
    CR_END;    
 }

 void crTsk13()
 {
    static crByte i = 0;
    CR_BEGIN;
     
    do{
        i++;
        crPrintf( "crTsk13 begin: %d\r\n", i);
        crDelay( 6 );
        crPrintf( "crTsk13 end\r\n");
    }while( 1 );       
    
    CR_END;   
 }

 void crTsk14()
 {
    static crByte i = 0;     
    CR_BEGIN;
    
    do{
        i++;
        crPrintf( "crTsk14 begin: %d\r\n", i);
        //crDelay( 3 );
        crSemWait( 6, 10 );
        crPrintf( "crTsk14 end\r\n");
    }while( 1 );

    CR_END;  
 }

 void crTsk15()
 {
    static crByte i = 0;
    static crByte tsk15msg0[10] = "abcdefg123";
    static crByte tsk15msg1[10] = "abcdefg456";
    static crByte tsk15msg2[10] = "abcdefg789";     
    CR_BEGIN;  
     
    do{
        i++;
        crPrintf( "crTsk15 begin: %d\r\n", i);
        crMQPost(1, tsk15msg0, 10);
        //crMQPost(1, tsk15msg1, 10);
        //crMQPost(1, tsk15msg2, 10);        
        crPrintf( "crTsk15 end\r\n");
        crDelay( 500 );  
    }while( 1 );     
    
    CR_END;     
 }

 void crExamTest()
 {
    #define _CR_TEST_SEM_

    crTaskCreate( crTsk0,  0);
     
    #ifdef _CR_TEST_SCHED_
      crTaskCreate( crTsk1, 1);
      crTaskCreate( crTsk2, 2);  
      //crTaskCreate( crTsk13, 13); 
    #endif     
     
    #ifdef _CR_TEST_SEM_
      crTaskCreate( crTsk4, 4);
      crTaskCreate( crTsk5, 5);  
      crTaskCreate( crTsk6, 6);           
      crTaskCreate( crTsk8, 8);      
      crTaskCreate( crTsk14, 14); 
    #endif
     
    #ifdef _CR_TEST_MQ_
      crTaskCreate( crTsk9, 9);
      crTaskCreate( crTsk10, 10);  
      //crTaskCreate( crTsk15, 15); 
    #endif 
     
 }

#endif /*_OSCUS_CR_EXAM_*/ 
/*************************************END*************************************/
