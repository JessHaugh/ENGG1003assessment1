#include <stdio.h>

int main(void)
{
  char in[] = "ABC" //Enter in letter
  int out;       // change to 'char' when used in array, and then %d becomes %c
                                 // int temp;   added in by demonstrator?
                                 // temp = in;  added in by demonstrator?
  int k = 1 ;    //Enter shift, -25<k<25, but if k=0 or 26, no shift occurs
  int out2;
  char in2='B';
  int i;
  int size=sizeof (in);
  
  for (i=0; i<=size; i++){
    ascii = (int)array[i]
    
    out = (in+k - 13)%26;
    printf ("ASCII code for output is %d\n", out);
    out = out + 65;
    printf("%c\n", out);
      
      
  }
  
  
  
  
  
  
  /* printf ("ASCII code for %c is %d\n", in, in);
     printf ("Shift letter by: ");
     scanf ("%d", &k); 
     REMOVED 'SCANF' FROM CODE TO SAVE TIME GOING INTO TERMINAL */


  out = (in+k - 13)%26;
    printf ("ASCII code for output is %d\n", out);
    out = out + 65;
    printf("%c\n", out);
  /*NEXT I NEED TO DECRYPT THIS CODE BACK TO A LETTER 
    out = in + k;
    out = (((in-26)+ k)%26)+97; */


 out2 = (in2-k + 13)%26;
    printf ("ASCII code for output is %d\n", out2);
    out2 = out2 + 65;
    printf("%c", out2);

 /*char input[1000];   //{1,2,3...,100}
   THIS IS THE NEXT STEP AFTER USING FORMULA TO STOP Z BEING SHIFTED 1 AND NOT RETURNING A*/
  
 
 /* Formual to encrypt: e(x) = (m+k)(mod 26)
               decrypt: d(c) = (c-k)(mod 26) w/ mod meaning % to get remainder */
 
       /* Lab Week 7: Shown how to use stdin and stdout with complier
          Tasks:
             1. Encryption of a message with a rotation cipher given the message text and rotation amount
             2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount
             3. Encryption of a message with a substitution cipher given message text and alphabet substitution
             4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions
           To pass, i must create a code which encrypts a text with a key, then prints this message,
                     then decrypt this back using rotation 
                     i then must use rotation cipher and do the same thing 
           Brenton supplied notes on how to do this kinda....  */     
 
 //work in labs
 #include <stdio.h>

int main(void)
{
  char in[] = "ABCD EFGH IJKL";            //entering text
  char encrypted[sizeof(in)];      
  int k = 1 ;   
  char decrypted[sizeof(in)]; 
  int i;
  int size=sizeof (in);
  
  printf ("input message : %s\n", in);    //encrpt a message
  printf ("encrypted message : ");
  
  for (i=0; i<=size; i++){    
    encrypted[i] = in[i]+k;
    printf ("%c", encrypted[i]);
  } 
  
  printf ("\ndecrypted message : ");      //decrypt message
  
  int j = 0;
  for (j=0; j<=size; j++){
      // printf ("%d\n", in[i]);
     decrypted[j] = encrypted[j]-k;
     printf ("%c", decrypted[j]);
  } 
  
  
  
 } 
 //in a.out
  return 0;
}