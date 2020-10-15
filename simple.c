#include "coremark.h"
int putchar();

void
matrix_mul_matrix(ee_u32 N, MATRES *C, MATDAT *A, MATDAT *B)
{
  ee_u32 i, j, k;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      C[i * N + j] = 0;
      for (k = 0; k < N; k++)
      {
        C[i * N + j] += (MATRES)A[i * N + k] * (MATRES)B[k * N + j];
      }
    }
  }
}

/* Function: matrix_add_const
        Add a constant value to all elements of a matrix.
*/
void
matrix_add_const(ee_u32 N, MATDAT *A, MATDAT val)
{
  ee_u32 i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      A[i * N + j] += val;
    }
  }
}


/* Function: matrix_sum
        Calculate a function that depends on the values of elements in the
   matrix.

        For each element, accumulate into a temporary variable.

        As long as this value is under the parameter clipval,
        add 1 to the result if the element is bigger then the previous.

        Otherwise, reset the accumulator and add 10 to the result.
*/
ee_s16
matrix_sum(ee_u32 N, MATRES *C, MATDAT clipval)
{
  MATRES tmp = 0, prev = 0, cur = 0;
  ee_s16 ret = 0;
  ee_u32 i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      cur = C[i * N + j];
      tmp += cur;
      if (tmp > clipval)
      {
        ret += 10;
        tmp = 0;
      }
      else
      {
        ret += (cur > prev) ? 1 : 0;
      }
      prev = cur;
    }
  }
  return ret;
}


ee_s16
matrix_test(MATRES *C, MATDAT *A, MATDAT *B, MATDAT val)
{
  ee_u32 N = 10;
  A = (MATDAT*) malloc(1024);
  B = (MATDAT*) malloc(1024);
  C = (MATDAT*) malloc(1024);
  ee_u16 crc     = 0;
  MATDAT clipval = val; // matrix_big(val);

  matrix_add_const(N, A, val); /* make sure data changes  */
  matrix_mul_matrix(N, C, A, B);
  crc = 3; //crc16(matrix_sum(N, C, clipval), crc);

  putchar('a' + C[1]);
  matrix_add_const(N, A, -val); /* return matrix to initial value */
  return crc;
}


int main() {
    matrix_test(NULL, NULL, NULL, 20);
}
