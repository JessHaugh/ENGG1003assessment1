#include <stdio.h>

int main(void)
{
  char in = 'a'; //Enter in letter
  int out;       // change to 'char' when used in array, and then %d becomes %c
                                 // int temp;   added in by demonstrator?
                                 // temp = in;  added in by demonstrator?
  int k = -24;   //Enter shift, -25<k<25, but if k=0 or 26, no shift occurs
  
  
  /* printf ("Enter your letter\n");
     scanf ("%c", &in);
  
     printf ("ASCII code for %c is %d\n", in, in);
     printf ("Shift letter by: ");
     scanf ("%d", &k); 
     REMOVED 'SCANF' FROM CODE TO SAVE TIME GOING INTO TERMINAL */


  out = (in+k)%26;
    printf ("ASCII code for output is %d\n", out);
    
    
  /*NEXT I NEED TO DECRYPT THIS CODE BACK TO A LETTER 
    out = in + k;
    out = (((in-26)+ k)%26)+97; */


 /*char input[1000];   //{1,2,3...,100}
   THIS IS THE NEXT STEP AFTER USING FORMULA TO STOP Z BEING SHIFTED 1 AND NOT RETURNING A*/
  
 
 /* Formual to encrypt: e(x) = (m+k)(mod 26)
               decrypt: d(c) = (c-k)(mod 26) w/ mod meaning % to get remainder */
 
 
  return 0;
}