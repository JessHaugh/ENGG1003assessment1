#include <stdio.h>

//ROTATION CIPHER

int main(void)
{
  char in[] = "abcdefg / HIJKLMN =+ oP";             //User enters the text to be rotated here
  int size=sizeof (in);                              //The size of the text is set to the size of input message
  char encrypted[sizeof(in)];                        //Encryption is initialised as ASCII values
  char decrypted[sizeof(in)];                        //Decryption is initialised as ASCII values
  int k = 1;                                         //The key for rotation is +1
  int i;                                             //'i' is the counter for 1st for-loop 
 
  printf ("    Input message : %s\n", in);           //Prints the input message to the screen
  printf ("Encrypted message : ");                   //Prints the encrypted message to the screen, after the 2nd loop
    
  for (i=0; i<=size; i++)                            //1st For-LOOP: Converts lower-case values to UPPER-case values
  {
    if (in[i]>=97 && in[i]<=122)                     //If lower-case based on ASCII value...
    {
     in[i]=in[i]-32;                                 //The ASCII values has 32 subtracted, to convert to UPPER-case
    }                                                //E.g. 'a' = ASCII 97, but (97-32)=65, which is 'A' 
  }
  
  for (i=0; i<=size; i++)                            //2nd For-LOOP: Encrypt message by rotating UPPER-case values per a key
  {
    if (in[i]>= 65 && in[i]<=90)                     //If input message, once converted to UPPER-case, falls between ASCII 65-90...
    {
     encrypted[i] = (in[i] - 65 + k)%26 + 65;        //Message is encrypted per a key, then taken as a modulus to reomove outliers    
     printf ("%c", encrypted[i]);                    //Then returned and printed to the 'Encrypted message' print statement
    }
    else                                             //If input message does not fall between ASCII 65-90...
    {
     encrypted[i] = in[i];                           //Content (white space, punctuation, or numerals etc.) are copied unmodified
     printf ("%c", encrypted[i]);                    //Content is printed to the 'Encrypted message' print statement unmodified
    }
  }
  
  printf ("\nDecrypted message : ");                 //Prints the decrypted message to the screen, after the 3rd loop
 
 for (i=0; i<=size; i++)                             //3rd For-LOOP: Decrpyt message by rotating UPPER-case values per a key
 {
   if (encrypted[i]>=65 && encrypted[i]<=90)         //If encrypted message falls between ASCII 65-90...
   {
    decrypted[i] = (encrypted[i] - 13 - k)%26 + 65;  //Message is decrypted per a key, then taken as a modulus to reomove outliers
    printf ("%c", decrypted[i]);                     //Then returned and printed to the 'Decrypted message' print statement
   }
   else                                              //If input message does not fall between ASCII 65-90...
   {
    decrypted[i] = encrypted[i];                     //Content (white space, punctuation, or numerals etc.) are copied unmodified
    printf ("%c", decrypted[i]);                     //Content is printed to the 'Decrypted message' print statement unmodified
   }
 }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SUBSTITUTION CIPHER

int main(void)
{
  char cipher[] = "QWERTYUIOPASDFGHJKLZXCVBNM";      //This cipher array is the key for substitution
  char in[] = "PLEASE, get milk @ the shops!";       //User enters the text to be substituted here
  int size=sizeof (in);                              //The size of the text is set to the size of input message
  char encrypted[sizeof(in)];                        //Encryption is initialised as ASCII values
  char decrypted[sizeof(in)];                        //Decryption is initialised as ASCII values
  int i;                                             //'i' is the counter for 1st for-loop     
    
  printf ("    Input message : %s\n", in);           //Prints the input message to the screen
  printf ("Encrypted message : ");                   //Prints the encrypted message to the screen, after the 2nd loop
  
  for (i=0; i<=size; i++)                            //1st For-LOOP: Converts lower-case values to UPPER-case values
  {
    if (in[i]>=97 && in[i]<=122)                     //If lower-case based on ASCII value...
    {
     in[i]=in[i]-32;                                 //The ASCII values has 32 subtracted, to convert to UPPER-case
    }
  }
    
  for (i=0; i<=size; i++)                            //2nd For-LOOP: Encrypt message by substituting UPPER-case values per a key
  {
    if(in[i]>=65 && in[i]<=90)                       //If input message, once converted to UPPER-case, falls between ASCII 65-90...                   
    {
     int p = in[i]-65;                               //???????????????????????????????????????????????????????????????????????????
     encrypted[i]=cipher[p];                         //Message is encrypted per the key 'cipher'
     printf ("%c", encrypted[i]);                    //Then returned and printed to the 'Encrypted message' print statement
    } 
    else                                             //If input message does not fall between ASCII 65-90...
    {
     encrypted[i] = in [i];                          //Content (white space, punctuation, or numerals etc.) are copied unmodified
     printf ("%c", encrypted[i]);                    //Content is printed to the 'Encrypted message' print statement unmodified
    }
  }                   
  
  printf ("\nDecrypted message : ");                 //Prints the decrypted message to the screen, after the 3rd loop          
    
  for (i=0; i<=size; i++)                            //3rd For-LOOP: Decrpyt message by substituting UPPER-case values per a key    
  {
    if(encrypted[i]>=65 && encrypted[i]<=90)         //If encrypted message falls between ASCII 65-90...
    {
     switch (encrypted[i])                           //The values which make up the message are put inside a SWITCH statement
     {  
      case 'Q' : decrypted [i] = 'A'; break;         //If values match the case, the decrypted value assigned is returned
      case 'W' : decrypted [i] = 'B'; break;         //E.g. If encrypted message was 'QWE'; switch statements would return 'ABC'
      case 'E' : decrypted [i] = 'C'; break;         //This process is repeated throughout the entire encrypted message
      case 'R' : decrypted [i] = 'D'; break;
      case 'T' : decrypted [i] = 'E'; break;
      case 'Y' : decrypted [i] = 'F'; break;
      case 'U' : decrypted [i] = 'G'; break;
      case 'I' : decrypted [i] = 'H'; break;
      case 'O' : decrypted [i] = 'I'; break;
      case 'P' : decrypted [i] = 'J'; break;
      case 'A' : decrypted [i] = 'K'; break;
      case 'S' : decrypted [i] = 'L'; break;
      case 'D' : decrypted [i] = 'M'; break;
      case 'F' : decrypted [i] = 'N'; break;
      case 'G' : decrypted [i] = 'O'; break;
      case 'H' : decrypted [i] = 'P'; break;
      case 'J' : decrypted [i] = 'Q'; break;
      case 'K' : decrypted [i] = 'R'; break;
      case 'L' : decrypted [i] = 'S'; break;
      case 'Z' : decrypted [i] = 'T'; break;
      case 'X' : decrypted [i] = 'U'; break;
      case 'C' : decrypted [i] = 'V'; break;
      case 'V' : decrypted [i] = 'W'; break;
      case 'B' : decrypted [i] = 'X'; break;
      case 'N' : decrypted [i] = 'Y'; break;
      case 'M' : decrypted [i] = 'Z'; break;
     }
     printf ("%c", decrypted[i]);                    //Then returned and printed to the 'Decrypted message' print statement
    }
    else                                             //If input message does not fall between ASCII 65-90...
    {
     decrypted[i] = encrypted[i];                    //Content (white space, punctuation, or numerals etc.) are copied unmodified
     printf ("%c", decrypted[i]);                    //Content is printed to the 'Decrypted message' print statement unmodified
    }
  }
}