 /* Formual to encrypt: e(x) = (m+k)(mod 26)
               decrypt: d(c) = (c-k)(mod 26) w/ mod meaning % to get remainder */
 
 //Worked on in Labs 10/04/19

#include <stdio.h>

int main(void)                                 //ROTATION CIPHER
{
  char in[] = "ABCD EFGH IJKL";                //Text is enetered here 
  char encrypted[sizeof(in)];      
  int k = 1 ;                                  //The key for rotation is +1
  char decrypted[sizeof(in)]; 
  int i;                                       //'i' is the counter for 1st for-loop 
  int size=sizeof (in);
  int j = 0;                                   //'j' is the counter for 2nd for-loop
  
  printf ("    Input message : %s\n", in);     //Prints the input message
  printf ("Encrypted message : ");             //Print statement for encrypted message
  
  for (i=0; i<=size; i++){                     //For-loop to encrypt message by key
    encrypted[i] = (in[i]+k);                    //DO I NEED TO ADD MOD 26?       
    printf ("%c", encrypted[i]); 
  } 
  
  printf ("\nDecrypted message : ");           //Print statement for decrypted message
  
  for (j=0; j<=size; j++){                     //For-loop to decrpyt message by key
      // printf ("%d\n", in[i]);
     decrypted[j] = encrypted[j]-k;
     printf ("%c", decrypted[j]);
  } 
 } 

////////////////////////////////////////////////////////////////////////////////////   
 
 int main(void)                                    //SUBSTITUTION CIPHER
{
  char in[] = "PLEASE GET MILK AT THE SHOPS";      //Text is entered here
  char encrypted[sizeof(in)];                      //Array for encryption
  //char decrypted[sizeof(in)];                      //Array for decryption
  int i;                                           //'i' is the counter for 1st for-loop     
  int size=sizeof (in);
  char cipher[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
  //int j = 0;                                       //'j' is the counter for 2nd for-loop
  
  printf ("    Input message : %s\n", in);         //Prints the input message
  printf ("Encrypted message : ");                 //Print statement for encrypted message
  
  for (i=0; i<=size; i++){                         //For-loop to encrypt input message
    if (in[i]==32){                                //If message has a space, ASCII 32
       encrypted[i]= 32;                           //Keep encryption of a space the same
       printf ("%c", encrypted[i]);                //Print spaces
    }
    else {                                         //Else, subsitute values accordingly
        int p = in[i]-65;
        encrypted[i]=cipher[p];
        printf ("%c", encrypted[i]);               //Print substituion back to console
    }
  } 
  
  char decrypted[sizeof(in)];           //WHERE I NEED HELP
  int j = 0; 
  
    for (j=0; j<=size; j++){    
    if (in[j]==32){
        encrypted[j]= 32;                //j or i?, change encrypt to decrypt
        printf ("%c", encrypted[j]); 
    }
    else {
        int p = in[i]+65;                //i or j?
    decrypted[j]=+cipher[p];
    printf ("%c", decrypted[j]);
    }
  } 
  printf ("\nDecrypted message : ");      //decrypt message
   
 /* int j = 0;
  for (j=0; j<=size; j++){
      // printf ("%d\n", in[i]);
     decrypted[j] = encrypted[j]-k;
     printf ("%c", decrypted[j]);
  } */ 
 } 
 