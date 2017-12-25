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
** file name:           logo.c
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
#ifdef _OSCUS_CR_LOGO_

/******************************************************************************
 * logo
 *
 *
 *****************************************************************************/
 void crLogoPrint( void )
 {
    crByte crl[5][5] ={ 
      0x7c,0x7c,0x7c,0xe6,0x7c,
      0xe6,0xf0,0xe0,0xe6,0xf0,
      0xe6,0x78,0xe0,0xe6,0x78,
      0xe6,0x3c,0xe0,0xe6,0x3c,
      0x7c,0xf8,0x7c,0x7e,0xf8
    };
    crByte i=0,j=0,k=0,t=0;
    crByte crb = ' ';
    crByte crn = CR_LOGO_CHAR;
    
    #if (CR_LOGO_INVERT == 1)
      crb = CR_LOGO_CHAR;
      crn = ' ';
    #endif
    
    crPrintf("\r\n"); for( j=0; j<64; j++){ crPrintf("%c",crb); }
    crPrintf("\r\n"); for( j=0; j<64; j++){ crPrintf("%c",crb); }
    crPrintf("\r\n"); for( j=0; j<64; j++){ crPrintf("%c",crb); }
    crPrintf("\r\n"); for( j=0; j<64; j++){ crPrintf("%c",crb); }
    for( i=0; i<5; i++){
       crPrintf("\r\n");
       for( j=0; j<12; j++){ crPrintf("%c",crb); }
       for( j=0; j<5; j++){
          t = crl[i][j];
          for( k=0; k<8; k++){
           if( t & 0x80 ){ crPrintf("%c",crn); }
           else { crPrintf("%c",crb); }
           t = t<<1;
           //if((j==2)&&(k=6))continue;
         }
         crPrintf("%c",crb);
       }
       if(i==0) { for( j=0;j<8;j++) { crPrintf("%c",crb); } }
       else { for( j=0;j<9;j++) { crPrintf("%c",crb); } }
    }
    #if (CR_LOGO_INVERT == 1)
    crPrintf("\r\n"); for( j=0; j<66; j++){ crPrintf("%c",crb); } 
    crPrintf("\r\n"); for( j=0; j<66; j++){ crPrintf("%c",crb); } 
    crPrintf("\r\n"); for( j=0; j<65; j++){ crPrintf("%c",crb); }
    crPrintf("\r\n"); for( j=0; j<64; j++){ crPrintf("%c",crb); }
    #endif
    crPrintf("\r\n\r\nIS RUNNING...\r\n");
 }
 
#endif /*_OSCUS_CR_LOGO_*/ 
/*************************************END*************************************/
