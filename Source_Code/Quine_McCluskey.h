#ifndef QUINE_MCCLUSKEY_H
#define QUINE_MCCLUSKEY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

char **_2DPointer(int Rows, int Col);
void _2DFreeArray(char **Array, int Rows);
void Dec_to_Bin(char const *MinC, int sor, int soc, char **MinB);
int CC(char const *MinC, int sor, char ch0, char ch1);
bool DE(char **MinB, int soc, int M, int diff_posi);
int DC(char **MinB, int soc, int M, int N, int *diff_posi);
int PT_Generator(char **MinB, int sor, int soc, int *PP, char Tick[]);
int Prime_Implicant(char **MinB, char *PI, int soc, char Tick[], int soT);

//----------------Decimal to Binary Coverter-------------------//
void Dec_to_Bin(char const *MinC, int sor, int soc, char **MinB)
{
  int Bit;
  for (int i = 0, Row = 0; i < sor; i++)
  {
    if ((MinC[i] == '1') || (MinC[i] == 'X'))
    {
      Bit = i;
      for (int j = (soc - 1); j >= 0; j--)
      {
        MinB[Row][j] = (char)(48 + (Bit % 2));
        Bit >>= 1;
      }
      Row++;
    }
  }
}

//----------------Character-Counter--------------------------//
int CC(char const *MinC, int sor, char ch0, char ch1)
{
  int count = 0;
  for (int i = 0; i < sor; i++)
    if (MinC[i] == ch0 || MinC[i] == ch1)
      count++;
  return count;
}

//--------------2D-Pointer Array Display Function(Temporary)------------//
void _2D_Ptr_Display(char **Arr, int sor, int soc, char ArrName[])
{
  for (int i = 0; i < sor; i++)
  {
    for (int j = 0; j < soc; j++)
    {
      printf("%s[%d][%d] = %c, ", ArrName, i, j, Arr[i][j]);
    }
    printf("\n");
  }
}

//-------------------Duplication_Eliminator----------------//
bool DE(char **MinB, int soc, int M, int diff_posi)
{
  for (int i = 0; i < soc; i++)
  {
    if (MinB[M][i] == '_')
    {
      if (diff_posi > i)
        return false;
    }
  }
  return true;
}

//-----------------------Diffs_Counter-------------------------//
int DC(char **MinB, int soc, int M, int N, int *diff_posi)
{
  int diff_count = 0;
  for (int i = 0; i < soc; i++)
  {
    if (MinB[M][i] != MinB[N][i])
    {
      diff_count++;
      *diff_posi = (int)i;
    }
  }
  return diff_count;
}

//------------------------Pair & Tick Generator--------------------------//
int PT_Generator(char **MinB, int sor, int soc, int *PP, char Tick[])
{
  int PProw = 0, diff_posi;
  for (int M = 0; M < sor; M++)
  {
    for (int N = (M + 1); N < sor; N++)
    {
      if (DC(MinB, soc, M, N, &diff_posi) == 1)
      {
        if (DE(MinB, soc, M, diff_posi))
        {
          *(PP + (PProw * 2)) = M;
          *(PP + (PProw * 2) + 1) = N;
          PProw++;
        }
        Tick[M] = '1';
        Tick[N] = '1';
      }
    }
  }
  return PProw;
}

//-------------------Prime_Implicant_Collector------------------//
int Prime_Implicant(char **MinB, char *PI, int soc, char Tick[], int soT)
{
  static int Line = 0;
  int i = 0;
  while ((Tick[i] != '$') && (i != soT))
  {
    if (Tick[i] == '0')
    {
      strncpy(&PI[Line * soc], &MinB[i][0], sizeof(char) * soc);
      Line++;
    }
    i++;
  }
  return Line;
}

//---Initializing Dynamic_2D-Array----//
char **_2DPointer(int Rows, int Col)
{

  char **Array;
  Array = (char **)malloc(Rows * sizeof(char *));

  for (int i = 0; i < Rows; i++)
    Array[i] = (char *)malloc(Col * sizeof(char));

  return Array;
}

//--------Free The Allocated Array-------//
void _2DFreeArray(char **Array, int Rows)
{
  for (int i = 0; i < Rows; i++)
    free(Array[i]);

  free(Array);
}
//________________END__________________//

#endif