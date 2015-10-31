//sort frobnicated words

#include <stdio.h>
#include <stdlib.h>

//first I encoutered a bug that returns 1 when
//a is actually smaller than b
//I used gdb to look at the value of both a and b
//and also the machine codes, then I found out
//that in line "if (*a^42 > *b^42)", the order
//of comparison is wrong.
//I fixed the bug by adding parenthesises before
//each logical comparisons
int frobcmp(char const * a, char const * b)
{
  //iterate through both arrays
  while ((*a != 32) && (*b != 32))
    {
      if ((*a^42) > (*b^42))
	return 1;
      else if ((*a^42) < (*b^42))
	return -1;
      a++;
      b++;
    }

  //if the program executes to this point
  //it means that either one frobnicated word might
  //be a prefix of another or both are equal

  //a is a prefix of b
  if ((*a == 32) && (*b != 32))
    return -1;
  //b is a prefix of a
  else if ((*a != 32) && (*b == 32))
    return 1;

  //both are equal
  return 0;
}

int wrap_frobcmp(const void * a, const void * b)
{
  char const * firstw = *(char const **)a;
  char const * secondw = *(char const **)b;
  return frobcmp(firstw, secondw);
}

/*
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
} 
*/

int main()
{

  /*
  //char temp = '*';
  //char arrayA[7] = {'*','`','_','C','I','A',' '};
  //char arrayB[7] = {'*','{','_','C','I','A',' '};
  char arrayC[2]={'A',' '};
  char arrayD[1]={' '};

  char const * a = arrayC;
  char const * b = arrayD;
  if (frobcmp(a,b) == 1)
    printf ("a is greater than b\n");
  else if (frobcmp(a,b) == -1)
    printf ("a is smaller than b\n");
  else
    printf ("a is equal to b\n");
  */

  //////////////////////////////////////////////////////////////
  /////////////////main body of this program////////////////////
  //////////////////////////////////////////////////////////////



  
  //pre-allocate a chunk of memory
  int pre_allocate = 1024;
  char *char_input_array = (char*)malloc(sizeof(char)*pre_allocate);
  
  //report error when memory allocation fails
  if (char_input_array == NULL)
    {
      fprintf(stderr,"Array of chars: memory allocation failed.");
      exit(1);
    }

  int char_in;
  int i;
  int countWord=0;
  
  for(i=0;(char_in = getchar()) != EOF;++i)
    {
      
      //reach the end of the memory chunk, need to reallocate memory
      if(i == pre_allocate)
	{
	  char_input_array = (char*)realloc(char_input_array, pre_allocate*2);

	  //report error when memory reallocation fails
	  if (char_input_array ==NULL)
	    {
	      fprintf(stderr, "Memory reallocation failed.");
	      exit(1);
	    }

	  //update allocation size
	  pre_allocate *=2;
	}

      
      //count how many words seperated by space in the array
      if((char)char_in == ' ')
	countWord++;

      //avoid adding a newline at the end of input
      if((char)char_in == '\n')
	break;
      
      //store char into the array
      char_input_array[i]=(char)char_in;

    }


  //standard input ends with nonspace
  if(char_input_array[i] != ' ')
    {
      countWord++;

      //append a trailing space at the end of the array
      char_input_array[i] = ' ';
    }
  
  //count size of the array
  int arraySize = i;
  
  //error flag is set during input
  if (ferror(stdin))
    {
      fprintf(stderr,"An error occured while reading from stdin.");
      exit(1);
    }

  //create an array of pointers pointing to frobnicated words
  char ** ptrToWord = (char**)malloc(sizeof(char*)*countWord);

  if (ptrToWord == NULL)
    {
      fprintf(stderr, "Array of char pointers: memory allocation failed.");
      exit(1);
    }

  int k;

  //create a pointer pointing to the beginning of the char array
  char * voyager = char_input_array; 

  for (k=0; k < countWord; ++k)
    {
      ptrToWord[k] = voyager;

      //reach the end of the array of char pointers
      if (k == (countWord -1))
	break;

      //voyager keep moving forward till next space
      while(*voyager != ' ')
	{
	  voyager++;
	}
      
      voyager++;
    }


  //sort char pointers
  qsort(ptrToWord, countWord, sizeof(char*), wrap_frobcmp);

  //output sorted frobnicated words
  int m;
  char * extractor;
  for (m=0; m < countWord; ++m)
    {
      extractor = ptrToWord[m];

      putchar(*extractor);

      while (*extractor != ' ')
	{
	  extractor++;
	  putchar(*extractor);
	}
    }


  
  //printf ("%d", countWord);

  
  /*
  //test obove code
  int j;
  for (j=0; j < arraySize; ++j)
    {
      putchar(char_input_array[j]);
    }
  */







  
  /*
  while(true){

    //reach the end of the memory chunk, need to reallocate memory
    if(i == pre_allocate)
      {
	char_input_array = (char*)realloc(char_input_array, pre_allocate*2);

	//report error when memory reallocation fails
	if (char_input_array ==NULL)
	  {
	    fprintf(stderr, "Memory reallocation failed.");
	    exit(1);
	  }

	//update allocation size
	pre_allocate *=2;
      }
    
    char_in = getchar();

    //getchar till the end of file
    if(char_in == EOF)
      break;

    //count how many words seperated by space in the array
    if((char)char_in == ' ')
      countWord++;
    
    //store char into the array
    char_input_array[i]=(char)char_in;  
    i++;
  }
    


  //error flag is set during input  
  if (ferror(stdin))
    {
      fprintf(stderr,"An error occured while reading from stdin.");
      exit(1);
    }
  
  
  char arrayMerge[]={'*','`','_','C','I','A',' ','*','{','_','C','I','A',' '};


  int allocatedspace = 1000;
  char *input = (char*)malloc(sizeof(char) * allocatedspace);

  int i=0;
  bool empty = true;
  while(1)
    {
      int in_char;
      in_char = getchar();
      if (in_char == EOF)
	break;
      empty = false;
      input[i] = (char)in_char;
      i++;
      if (i==allocatedspace)
	{
	  allocatedspace

  if (input == NULL)
    {
      exit(1);
    }

  
  
  //void * base;
  //base = &arrayMerge[0];
  int array[]={1,3,5,4,2,6};
  qsort(array, 6, sizeof(int), compare);

  for (int n=0;n<6;n++)
    {
       printf ("%d ",array[n]);
    }

  
  for (int i=0; i < 14; i++)
    {
      char *temp = arrayMerge[i];
      printf ("%c",*temp);
    }
  */  
}


