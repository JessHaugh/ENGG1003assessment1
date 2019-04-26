#include <stdio.h>
#include <ctype.h>

/*A cipher is an algorithm allowing a text to be transformed to a concealed language. This language can not be converted by an untrained
  eye, and requires a mathematical program to both encrypt and decrypt a message. This procedure has been implemented since ancient times,
  and allows a secret message to be transported with the safety of confidentiality.*/


void encrypt_rotation(char *encrypted, char *in, int size, int k, FILE*output);
void decrypt_rotation(char *decrypted, char *in, int size, int k, FILE*output);   //encrypted atm but should be in?
void encrypt_substitution(char *encrypted, char *in, int size, char *cipher, FILE*output);
void decrypt_substitution(char *decrypted, char *in, int size, char *cipher, FILE*output); //encrypted atm but should be in?
void decrypt_unseen(char *in, int size, FILE*output);

int main(void)
{
  FILE*input;
  input=fopen("input.txt","r");
  
  if(input==NULL)
  {
      perror("input fopen()");
      return 0;
  }
  
  //int sizef=0;
  //char o;
  //while ((fscanf(input, "%c", &o))!=EOF)
 // {
  //    sizef++;
  //}
  //printf("\n\n%d\n\n", sizef);
  fseek(input, 480, SEEK_SET);   //sets beginning of input message to select operation
  
  int select;
  int k;
  char cipher[26];
  fscanf(input, "%d", &select);
  fseek(input, 511, SEEK_SET);
  if(select==1 || select==2)
  {
      fscanf(input, "%d", &k); //k=key
  }
  else if (select!=3)
  {
      fscanf(input, "%s", cipher);
  }
  
  FILE*message;
  message=fopen("message.txt","r");
  
  if(message==NULL)
  {
      perror("message fopen()");
      return 0;
  }
  
  char in[1024];
  //char in[] = "abcdefg / HIJKLMN =+ oP";             //User enters the text to be rotated/substituted here
  int size=sizeof (in);                              //The size of the text is set to the size of input message
  char encrypted[sizeof(in)];                        //Encryption is initialised as ASCII values
  char decrypted[sizeof(in)];                        //Decryption is initialised as ASCII values
  //int k = 1;                                         //The key for rotation is +1
  //char cipher[] = "QWERTYUIOPASDFGHJKLZXCVBNM";      //This cipher array is the key for substitution
  int i;                                             //'i' is the counter for 1st for-loop 
  char storage;
  
  for(i=0; i<size; i++)
  {
      fscanf(message, "%c", &storage);
      if(feof(message)==0)
      {
          if(islower(storage))  //lower to upper
          {
              storage=storage-32;
          }
          in[i]=storage;
      }
      else
      {
          in[i]=0;
      }
  }
 
  FILE*output;
  output=fopen("output.txt","w");
  
 if(output==NULL)
  {
      perror("output fopen()");
      return 0;
  }
 
  printf ("Input message from file : %s\n", in);          //Prints the input message to the screen
  fprintf (output,"Input message from file : %s\n", in);   //prints to output file
  //printf ("\nRotation Cipher with key %d\n", k);     //Print the rotation key to the screen
  //printf (" Encrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
  
 
/*This for-LOOP reads the ASCII values of the user’s input message. If the values are lower-case (ASCII 97-122), the LOOP converts the 
  message into UPPER-case (ASCII 65-90). This procedure repeats until the entire string is UPPER-case. This new message is returned to 
  the program. This allows the following encryptions/decryptions to compile efficiently.*/

    
  switch (select)
  {
      case 1: 
      printf ("\nRotation Cipher with key %d\n", k);     //Print the rotation key to the screen
      printf ("\nEncrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
      fprintf (output,"\nRotation Cipher with key %d\n", k);     //Print the rotation key to the screen
      fprintf (output,"\nEncrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
      encrypt_rotation(encrypted,in,size,k,output);
      break;
      
      case 2:
      printf ("\nRotation Cipher with key %d\n", k);
      printf ("\nDecrypted message : ");                 //Prints the decrypted message to the screen, after the 3rd loop
      fprintf (output,"\nRotation Cipher with key %d\n", k);
      fprintf (output,"\nDecrypted message : ");                 //Prints the decrypted message to the screen, after the 3rd loop
      decrypt_rotation(decrypted,in,size,k,output);
      break;
      
      case 3:
      printf("\nDecryption of Unseen Cipher Rotation\n(ALL possible results are printed)\n\n");
      fprintf(output,"\nDecryption of Unseen Cipher Rotation\n(ALL possible results are printed)\n\n");
      decrypt_unseen(in,size,output);
      break;
            
      case 4:
      printf ("\nSubstitution Cipher with key given in input\n");  
      printf ("\nEncrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
      fprintf (output,"\nSubstitution Cipher with key given in input\n");  
      fprintf (output,"\nEncrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
      encrypt_substitution(encrypted,in,size,cipher,output); 
      break;
      
      case 5:
      printf ("\nSubstitution Cipher with key given in input\n"); 
      printf ("\nDecrypted message : ");                //Prints the decrypted message to the screen, UPPER-case         
      fprintf (output,"\nSubstitution Cipher with key given in input\n"); 
      fprintf (output,"\n Decrypted message : ");                //Prints the decrypted message to the screen, UPPER-case         
      decrypt_substitution(decrypted,in,size,cipher,output); 
      break;
      
      default:
      printf("\nUnknown option, please select again (1, 2, 3, 4, 5)");
      fprintf(output,"\nUnknown option, please select again (1, 2, 3, 4, 5)");
  }
 } 
  
  
  
   //encrypt_rotation(encrypted,in,size,k);
   
/*ROTATION CIPHER ~ where a messages’ text is rotated along the alphabet based on a key  
  This for-LOOP encrypts a message using rotation cipher and a key. The key has a range of 0-26; with the values 0 and 26 returning an 
  unmodified message as no shift has occurred. If the ASCII values of the input message fall between 65-90 (UPPER-case English), the 
  message is converted based on the key. If the message possesses ASCII values beyond the range 65-90, content (such as white space,
  punctuation, or numerals etc) are copied and printed unmodified. This is to allow the correct spacing and punctuation to remain
  untouched. This returns an encrypted message to the screen with a given key.*/
 
 
  
/*This for-LOOP decrypts a message using rotation cipher and a key. This LOOP uses a key and the encrypted message as an input to convert 
  back to the original message. The value of the key must be identical to the previous value, otherwise, another form of encryption will 
  occur. If a constant key is used, and subtracted from the previous encryption, the users original input message will be returned. Again,
  values outside the ASCII range 65-90 will be copied and printed unmodified.*/
 
 
  //printf ("\n Decrypted message : ");                 //Prints the decrypted message to the screen, after the 3rd loop
  //decrypt_rotation(decrypted,encrypted,size,k);
 

 
/*SUBSTITUTION CIPHER ~ where a messages’ text is allocated a new value in the alphabet based on a key
  This for-LOOP encrypts a message using substitution cipher and a key. The key is known as CIPHER and reallocates the ASCII values of the
  alphabet to the ASCII string values. If the ASCII values of the input message fall between 65-90 (UPPER-case English), the message is 
  converted based on the key. If the message possesses ASCII values beyond the range 65-90, content (such as white space, punctuation, or 
  numerals etc) are copied and printed unmodified. This returns an encrypted message to the screen based on the key.*/


  //printf ("\n\nSubstitution Cipher with QWERTY key\n");  
  //printf (" Encrypted message : ");                  //Prints the encrypted message to the screen, after the 2nd loop
  //encrypt_substitution(encrypted,in,size,cipher); 
  
                 
    
  
  /*This for-LOOP decrypts a message using substitution cipher and a key. This LOOP uses the CIPHER key and the encrypted message as an
    input to convert back to the original message. The value of the key must be identical to the previous value, otherwise, another form
    of encryption will occur. If the encrypted message holds text with ASCII values between 65-90, a switch statement is performed. This
    operation allows the encrypted values to be reassigned to their original values, to therefore return a decrypted message. Again, 
    values outside the ASCII range 65-90 will be copied and printed unmodified.*/
  
  
  //printf ("\n Decrypted message : ");                //Prints the decrypted message to the screen, UPPER-case         
  //decrypt_substitution(decrypted,encrypted,size,cipher); 
   
  //printf("\n\nDecryption of Unseen Cipher Rotation\n");
  //decrypt_unseen(in,size);


void encrypt_rotation(char *encrypted, char *in, int size, int k, FILE*output)
 {
    int i;
    for (i=0; i<=size; i++)                          //2nd For-LOOP: Encrypt message by rotating UPPER-case values per a key
  {
    if (in[i]>= 65 && in[i]<=90)                     //If input message, once converted to UPPER-case, falls between ASCII 65-90...
    {
     encrypted[i] = (in[i] - 65 + k)%26 + 65;        //Message is encrypted per a key, then taken as a modulus to reomove outliers    
     //printf ("%c", encrypted[i]);                    //Then returned and printed to the 'Encrypted message' print statement
    }
    else                                             //If input message does not fall between ASCII 65-90...
    {
     encrypted[i] = in[i];                           //Content (white space, punctuation, or numerals etc.) is copied unmodified
     //printf ("%c", encrypted[i]);                    //Content is printed to the 'Encrypted message' print statement unmodified
    }
  }
   printf ("%s", encrypted);
   fprintf (output,"%s", encrypted);
 }
 
 void decrypt_rotation(char *decrypted, char *in, int size, int k, FILE*output)
 {
    int i;
    for (i=0; i<=size; i++)                             //3rd For-LOOP: Decrpyt message by rotating UPPER-case values per a key
  {
    if (in[i]>=65 && in[i]<=90)         //If encrypted message falls between ASCII 65-90...
    {
     decrypted[i] = (in[i] - 13 - k)%26 + 65;  //Message is decrypted per a key, then taken as a modulus to reomove outliers
     //printf ("%c", decrypted[i]);                     //Then returned and printed to the 'Decrypted message' print statement
    }
    else                                              //If input message does not fall between ASCII 65-90...
    {
     decrypted[i] = in[i];                     //Content (white space, punctuation, or numerals etc.) is copied unmodified
     //printf ("%c", decrypted[i]);                     //Content is printed to the 'Decrypted message' print statement unmodified
    }
  }
    printf ("%s", decrypted);
    fprintf (output,"%s", decrypted);
 }
 
 void encrypt_substitution(char *encrypted, char *in, int size, char *cipher, FILE*output)
 {
   int i;
   for (i=0; i<=size; i++)                            //4th For-LOOP: Encrypt message by substituting UPPER-case values per a key
  {
    if(in[i]>=65 && in[i]<=90)                       //If input message, once converted to UPPER-case, falls between ASCII 65-90...                   
    {
     int p = in[i]-65;                               //This is the conversion betweeen the normal alphabet and the cipher substitution
     encrypted[i]=cipher[p];                         //Message is encrypted per the key 'cipher'
     //printf ("%c", encrypted[i]);                    //Then returned and printed to the 'Encrypted message' print statement
    } 
    else                                             //If input message does not fall between ASCII 65-90...
    {
     encrypted[i] = in [i];                          //Content (white space, punctuation, or numerals etc.) is copied unmodified
     //printf ("%c", encrypted[i]);                    //Content is printed to the 'Encrypted message' print statement unmodified
    }
  }
   printf ("%s", encrypted);
   fprintf (output,"%s", encrypted);
 }
 
 void decrypt_substitution(char *decrypted, char *in, int size, char *cipher, FILE*output)
 {
     int i;
     for (i=0; i<=size; i++)                            //5th For-LOOP: Decrpyt message by substituting UPPER-case values per a key    
  {
    if(in[i]>=65 && in[i]<=90)         //If encrypted message falls between ASCII 65-90...
    {
     switch (in[i])                           //The values which make up the message are put inside a SWITCH statement
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
     //printf ("%c", decrypted[i]);                    //Then returned and printed to the 'Decrypted message' print statement
    }
    else                                             //If input message does not fall between ASCII 65-90...
    {
     decrypted[i] = in[i];                    //Content (white space, punctuation, or numerals etc.) is copied unmodified
     //printf ("%c", decrypted[i]);                    //Content is printed to the 'Decrypted message' print statement unmodified
    }
  }
   printf ("%s", decrypted);
   fprintf (output,"%s", decrypted);
 }
 
 void decrypt_unseen(char *in, int size, FILE*output)
  {
    int j = 0;
    while(j<=25)
 {
     for (int i=0; i<=size; i++)
     {
         if(in[i]>= 65 && in[i]<=90)
         {
             in[i] = 26 + in[i] -65;
             in[i] = (in[i]- 1)%26;
             in[i] = in[i] + 65;
         }
     }
     j++;  
     printf("Decrypted message with key %d : %s\n", j, in);
     fprintf(output,"Decrypted message with key %d : %s\n", j, in);
 }
 }