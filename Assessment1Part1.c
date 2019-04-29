#include <stdio.h>
#include <ctype.h>

/*A cipher is an algorithm allowing a text to be transformed to a concealed language. This language can not be converted by an untrained eye, and requires a
  mathematical program to both encrypt and decrypt a message. This procedure has been implemented since ancient times, and allows a secret message to be 
  transported with the safety of confidentiality.*/

void encrypt_rotation(char *encrypted, char *in, int size, int k, FILE*output);             //Lines 6-10 are function prototypes    
void decrypt_rotation(char *decrypted, char *in, int size, int k, FILE*output);             //They are of type void and named based on operation
void encrypt_substitution(char *encrypted, char *in, int size, char *cipher, FILE*output);  //Arguments are inside the brackets and include the major variables
void decrypt_substitution(char *decrypted, char *in, int size, char *cipher, FILE*output);  //'FILE*output' allows the result to be printed in output.txt file
void decrypt_unseen(char *in, int size, FILE*output);

int main(void)
{
  FILE*input;                                                  //This calls the file input.txt, where the codes operation is selected and key value entered
  input=fopen("input.txt","r");                                //The file is now opened and any information entered is read and implemented into the code
  
  if(input==NULL)                                              //If an operation is not selected...
  {
      perror("input fopen()");                                 //The program will print an error message, requiring the user to enter a valid number (1-5)
      return 0;                                                //The 'if statement' is then exited
  }
  
   /* int sizef=0;                                             //This was used to count the number of characters in the input file
      char o;                                                  //The size of the file and the string was declared, and a value was calculated  
      while ((fscanf(input, "%c", &o))!=EOF)                   //This value allowed the user to determine where the input file starts reading from       
      {
          sizef++;                                             //This increments 'sizef' (0 to 1 to 2 to 3...)
      }
      printf("\n\n%d\n\n", sizef);*/                           //The numbers printed from this code are on lines 31 && 38
  
  fseek(input, 480, SEEK_SET);                                 //Input.txt is set to start being read from character 480 (operation selection)
  
  int select;                                                  //'Select' is initialised as an integer, as the user has to choose from 1-5 operations
  int k;                                                       //'k' = key used for rotation cipher, the 2nd value processed in the input.txt file
  char cipher[26];                                             //'cipher' = key for substitution cipher, with a size limit of 26 characters (alphabet)
  fscanf(input, "%d", &select);                                //Selection entered in input.txt is stored and implemented in the switch statement
  
  fseek(input, 511, SEEK_SET);                                 //Input.txt is set to start being read from character 511 (key selection)
    
  if(select==1 || select==2)                                   //If the operation selected is rotation cipher...
  {
      fscanf(input, "%d", &k);                                 //The second value entered is stored as the key for rotation
  }
  else if (select!=3)                                          //If the operation is not 1, 2 or 3 (3 doesn't need a key)...
  {
      fscanf(input, "%s", cipher);                             //The second value entered is stored as the key for substitution
  }
  
  FILE*message;                                                //This calls the file message.txt, where the codes input message is entered and stored
  message=fopen("message.txt","r");                            //The file is now opened and any information entered is read and implemented into the code
  
  if(message==NULL)                                            //If a message is not entered...
  {
      perror("message fopen()");                               //The program will print an error message, requiring the user to enter a valid message
      return 0;                                                //The 'if statement' is then exited
  }
  
  char in[1024];                                               //The message is stored as an array (in) with a maximum size of 1024 characters
  int size=sizeof (in);                                        //The size of the text is set to the size of input message
  char encrypted[sizeof(in)];                                  //Encryption outputs are initialised as ASCII values
  char decrypted[sizeof(in)];                                  //Decryption outputs are initialised as ASCII values
  int i;                                                       //'i' initialised as an integer becuase it is a counter for the for-loops
  char storage;                                                //Storage is initialised to store the characters from the message
  
  for(i=0; i<size; i++)                                        //For-loop increments 'i' to validate the message so it can be implemented in the code
  {
      fscanf(message, "%c", &storage);                         //The message entered is stored as ASCII characters
      if(feof(message)==0)                                     //If the message file ends with '0' characters...(feof=function-end-of-file)
      {
          if(islower(storage))                                 //Lower-case characters in 'storage' are converted to UPPER-case
          {
              storage=storage-32;                              //ASCII lower-case (97-122) - 32 = (65-90) ASCII UPPER-case
          }
          in[i]=storage;                                       //New ASCII values replace old message input and become the array (in)
      }
      else                                                     //If these requirements are not met...
      {
          in[i]=0;                                             //The array (in) is filled with NULL characters, in order to fill length of 1024 
      }
  }
 
  FILE*output;                                                 //This calls the file output.txt, where the codes output message is printed
  output=fopen("output.txt","w");                              //The file is now opened and any information resulting from the code is written to the file
  
 if(output==NULL)                                              //If an output is not printed...
  {
      perror("output fopen()");                                //The program will print an error message
      return 0;                                                //The 'if statement' is then exited
  }
 
  printf ("Message from file : %s\n", in);                     //Prints the users message for encryption/decryption to the screen
  fprintf (output,"Message from file : %s\n", in);             //Prints the users message for encryption/decryption to the output.txt file
   
 switch (select)                                               //When the selection value is entered in input.txt, the according case executes...
  {
      case 1:                                                  //When operation 1 is selected...
      printf ("\nRotation Cipher with KEY : %d\n", k);         //The operation (rotation) and key is printed to the screen 
      printf ("\nEncrypted message : ");                       //The encrypted message is also printed to the screen
      fprintf (output,"\nRotation Cipher with KEY : %d\n", k); //The operation (rotation) and key is printed to the output.txt file     
      fprintf (output,"\nEncrypted message : ");               //The encrypted message is also printed to the output.txt file   
      encrypt_rotation(encrypted,in,size,k,output);            //The function to encrypt/rotate this message is called here
      break;                                                   //The swich case is then exited/broken
      
      case 2:                                                  //When operation 2 is selected...
      printf ("\nRotation Cipher with KEY : %d\n", k);         //The operation (rotation) and key is printed to the screen 
      printf ("\nDecrypted message : ");                       //The decrypted message is also printed to the screen
      fprintf (output,"\nRotation Cipher with KEY : %d\n", k); //The operation (rotation) and key is printed to the output.txt file
      fprintf (output,"\nDecrypted message : ");               //The decrypted message is also printed to the output.txt file
      decrypt_rotation(decrypted,in,size,k,output);            //The function to decrypt/rotate this message is called here
      break;                                                   //The swich case is then exited/broken
      
      case 3:                                                                                             //When operation 3 is selected...
      printf("\nDecryption of Unseen Cipher Rotation\n\n(ALL possible results are printed)\n\n");         //UNSEEN cipher decryption is printed to the screen
      fprintf(output,"\nDecryption of Unseen Cipher Rotation\n\n(ALL possible results are printed)\n\n"); //UNSEEN cipher decryption is printed to output.txt
      decrypt_unseen(in,size,output);                                                                     //The function to decrypt message is called here
      break;                                                                                              //The swich case is then exited/broken
            
      case 4:                                                           //When operation 4 is selected...
      printf ("\nSubstitution Cipher with KEY : %s\n", cipher);         //The operation (substitution) and key is printed to the screen 
      printf ("\nEncrypted message : ");                                //The encrypted message is also printed to the screen
      fprintf (output,"\nSubstitution Cipher with KEY : %s\n", cipher); //The operation (substitution) and key is printed to the output.txt file 
      fprintf (output,"\nEncrypted message : ");                        //The encrypted message is also printed to the output.txt file 
      encrypt_substitution(encrypted,in,size,cipher,output);            //The function to encrypt/substitute this message is called here
      break;                                                            //The swich case is then exited/broken
      
      case 5:                                                           //When operation 5 is selected...
      printf ("\nSubstitution Cipher with KEY : %s\n", cipher);         //The operation (substitution) and key is printed to the screen
      printf ("\nDecrypted message : ");                                //The decrypted message is also printed to the screen
      fprintf (output,"\nSubstitution Cipher with KEY : %s\n", cipher); //The operation (substitution) and key is printed to the output.txt file
      fprintf (output,"\n Decrypted message : ");                       //The decrypted message is also printed to the output.txt file   
      decrypt_substitution(decrypted,in,size,cipher,output);            //The function to decrypt/substitute this message is called here
      break;                                                            //The swich case is then exited/broken
      
      default:
      printf("\nOperation UNKNOWN\n\nPlease select again (1, 2, 3, 4, or 5)");         //The operation is unknown and a warning is printed to the screen
      fprintf(output,"\nOperation UNKNOWN\n\nPlease select again (1, 2, 3, 4, or 5)"); //The operation is unknown and a warning is printed to output.txt
  }
} 
  
/*ENCRYPTION : ROTATION CIPHER ~ where a messages’ text is rotated along the alphabet based on a key  
  This function encrypts a message using rotation cipher and a key. The key has a range of 0-26; with the values 0 and 26 returning 
  an unmodified message as no shift has occurred. If the ASCII values of the input message fall between 65-90 (UPPER-case English),
  the message is converted based on the key. If the message possesses ASCII values beyond the range 65-90, content (such as white 
  space, punctuation, or numerals etc) are copied and printed unmodified. This is to allow the correct spacing and punctuation to 
  remain untouched. This returns an encrypted message to the screen with a given key.*/
void encrypt_rotation(char *encrypted, char *in, int size, int k, FILE*output)         //Function to encrypt via rotation is defined
 {
   int i;                                                               //'i' initialised as an integer becuase it is a counter for the for-loop
   for (i=0; i<=size; i++)                                              //For-LOOP encrypts message by rotating UPPER-case values per a key
   {
       if (in[i]>= 65 && in[i]<=90)                                     //If message, once converted to UPPER-case, falls between ASCII 65-90...
       {
           encrypted[i] = (in[i] - 65 + k)%26 + 65;                     //Message is encrypted per a key, then taken as a modulus to reomove outliers                      
       }
       else                                                             //If input message does not fall between ASCII 65-90...
       {
           encrypted[i] = in[i];                                        //Content (white space, punctuation, or numerals etc.) is copied unmodified
       }
   }
   printf ("%s", encrypted);                                            //Encrypted message with 'unmodified content' is then printed to the screen
   fprintf (output,"%s", encrypted);                                    //Encrypted message with 'unmodified content' is then printed to output.txt
 }
 
/*DECRYPTION : ROTATION CIPHER ~ where a messages’ text is rotated along the alphabet based on a key
  This function decrypts a message using rotation cipher and a key. The LOOP uses a key and the encrypted message as an input to 
  convert back to the original message. The value of the key must be identical to the previous value, otherwise, another form of 
  encryption will occur. If a constant key is used, and subtracted from the previous encryption, the users original input message
  will be returned. Again, values outside the ASCII range 65-90 will be copied and printed unmodified.*/
void decrypt_rotation(char *decrypted, char *in, int size, int k, FILE*output)         //Function to decrypt via rotation is defined
 {
   int i;                                                               //'i' initialised as an integer becuase it is a counter for the for-loop
   for (i=0; i<=size; i++)                                              //For-LOOP decrypts message by rotating UPPER-case values per a key
   {
       if (in[i]>=65 && in[i]<=90)                                      //If input message falls between ASCII 65-90...
       {
           decrypted[i] = (in[i] - 13 - k)%26 + 65;                     //Message is decrypted per a key, then taken as a modulus to reomove outliers
       }
       else                                                             //If input message does not fall between ASCII 65-90...
       {
           decrypted[i] = in[i];                                        //Content (white space, punctuation, or numerals etc.) is copied unmodified
       }
   }
   printf ("%s", decrypted);                                            //Decrypted message with 'unmodified content' is then printed to the screen
   fprintf (output,"%s", decrypted);                                    //Decrypted message with 'unmodified content' is then printed to output.txt
 }
 
 /*DECRYPTION : ROTATION CIPHER ~ where a messages’ text is rotated along the alphabet based on a key
   This function decrypts an encrypted message using rotation cipher and an UNKNOWN key. The LOOP decrypts the message with every
   possible key with the range 0-26. Values outside the ASCII range 65-90 will be copied and printed unmodified. The user must
   then manually identify the correctly decrypted message from the 26 decryptions printed.*/ 
void decrypt_unseen(char *in, int size, FILE*output)                    //Function to decrypt via rotation is defined
 {
   int j = 0;                                                           //'j' initialised as an integer becuase it is a counter for the while-loop
   while(j<=25)                                                         //While 0<=j<=25...
   {
       for (int i=0; i<=size; i++)                                      //'i' initialised as an integer becuase it is a counter for the for-loop
       {
           if(in[i]>= 65 && in[i]<=90)                                  //If input message falls between ASCII 65-90...
           {
               in[i] = 26 + in[i] - 65;                                 //Input message is decrypted via rotation
               in[i] = (in[i]- 1)%26;                                   //Any outliers from the modulus are ignored
               in[i] = in[i] + 65;                                      //ALL possible decrypted messages are printed
           }
       }
       j++;                                                             //'j' increments to allow the loop to continue until it reaches 25 keys
       printf("Decrypted message with KEY %d : %s\n\n", j, in);         //Decrypted message with 'unmodified content' is then printed to the screen
       fprintf(output,"Decrypted message with KEY %d : %s\n\n", j, in); //Decrypted message with 'unmodified content' is then printed to output.txt
    }
 }
 
/*ENCRYPTION : SUBSTITUTION CIPHER ~ where a messages’ text is allocated a new value in the alphabet based on a key
  This function encrypts a message using substitution cipher and a key. The key is known as CIPHER and reallocates the ASCII values
  of the alphabet to the ASCII string values. If the ASCII values of the input message fall between 65-90 (UPPER-case English), the
  message is converted based on the key. If the message possesses ASCII values beyond the range 65-90, content (such as white space,
  punctuation, or numerals etc) are copied and printed unmodified. This returns an encrypted message to the screen based on the key.*/
void encrypt_substitution(char *encrypted, char *in, int size, char *cipher, FILE*output) //Function to encrypt via substitution is defined
 {
   int i;                                                               //'i' initialised as an integer becuase it is a counter for the for-loop
   for (i=0; i<=size; i++)                                              //For-LOOP encrypts message by substituting UPPER-case values per a key
   {
       if(in[i]>=65 && in[i]<=90)                                       //If input message (converted to UPPER-case), falls between ASCII 65-90...                   
       {
           int p = in[i]-65;                                            //The conversion betweeen the normal alphabet and the cipher key occur
           encrypted[i]=cipher[p];                                      //Message is encrypted per the key 'cipher'                   
       } 
       else                                                             //If input message does not fall between ASCII 65-90... 
       {
           encrypted[i] = in [i];                                       //Content (white space, punctuation, or numerals etc.) is copied unmodified
       }
   }
   printf ("%s", encrypted);                                            //Encrypted message with 'unmodified content' is then printed to the screen
   fprintf (output,"%s", encrypted);                                    //Encrypted message with 'unmodified content' is then printed to output.txt
 }
 
 /*DECRYPTION : SUBSTITUTION CIPHER ~ where a messages’ text is allocated a new value in the alphabet based on a key
   This function decrypts a message using substitution cipher and a key. This LOOP uses the CIPHER key and the encrypted message
   an input to convert back to the original message. The value of the key must be identical to the previous value, otherwise, 
   another form of encryption will occur. If the encrypted message holds text with ASCII values between 65-90, a switch statement
   is performed. This operation allows the encrypted values to be reassigned to their original values, to therefore return a 
   decrypted message. Again, values outside the ASCII range 65-90 will be copied and printed unmodified.*/
/*void decrypt_substitution(char *decrypted, char *in, int size, char *cipher, FILE*output) //Function to decrypt via substitution is defined
 {
   int i;                                                               //'i' initialised as an integer becuase it is a counter for the for-loop
   for (i=0; i<=size; i++)                                              //For-LOOP decrpyts message by substituting UPPER-case values per a key    
   {
       if(in[i]>=65 && in[i]<=90)                                       //If input message falls between ASCII 65-90...
       {
           switch (in[i])                                               //The values which make up the message are put inside a SWITCH statement
           {  
               case 'Q' : decrypted [i] = 'A'; break;                   //If values match the case, the decrypted value assigned is returned
               case 'W' : decrypted [i] = 'B'; break;                   //E.g. If input message was 'QWE'; switch statements would return 'ABC'
               case 'E' : decrypted [i] = 'C'; break;                   //This process is repeated throughout the entire encrypted message
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
       }   
       else                                                             //If input message does not fall between ASCII 65-90...
       {
           decrypted[i] = in[i];                                        //Content (white space, punctuation, or numerals etc.) is copied unmodified                  
       }
   }
   printf ("%s", decrypted);                                            //Decrypted message with 'unmodified content' is then printed to the screen
   fprintf (output,"%s", decrypted);                                    //Decrypted message with 'unmodified content' is then printed to output.txt
 }*/
 void decrypt_substitution(char *decrypted, char *in, int size, char *cipher, FILE*output) //Function to decrypt via substitution is defined
 {
   int i;                                                               //'i' initialised as an integer becuase it is a counter for the for-loop
   for (i=0; i<=size; i++)                                              //For-LOOP decrpyts message by substituting UPPER-case values per a key    
   {
       if(in[i]>=65 && in[i]<=90)                                       //If input message (converted to UPPER-case), falls between ASCII 65-90...                   
       {
           int p = in[i]-65;                                            //The conversion betweeen the normal alphabet and the cipher key occur
           for (int q = 0; p!=cipher[q]; q++)
           decrypted[i] = q + 65;                                     //Message is encrypted per the key 'cipher'                   
       } 
       else                                                             //If input message does not fall between ASCII 65-90... 
       {
           decrypted[i] = in [i];                                       //Content (white space, punctuation, or numerals etc.) is copied unmodified
       }
   }
   printf ("%s", encrypted);                                            //Encrypted message with 'unmodified content' is then printed to the screen
   fprintf (output,"%s", encrypted);                                    //Encrypted message with 'unmodified content' is then printed to output.txt
 }