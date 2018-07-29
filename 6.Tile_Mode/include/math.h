// All things arithmetic
// JJM 051109

#ifndef _MATH_H_
#define _MATH_H_

// 2D Matrix
typedef struct _M2
{
    int nX1, nY1, nW1;
    int nX2, nY2, nW2;
    int nX3, nY3, nW3;
} M2;

// Math_M2Mult: Get the resulting 2d matrix from a 2d matrix multiply, the resulting matrix
//		    cannot be pointing to the same memory as the left or right matrix
// pResult      - resulting matrix
// pLeft        - the left matrix in the multiply
// pRight       - the right matrix in the multiply
void Math_M2Mult(M2* pResult, const M2* pLeft, const M2* pRight);

// Math_M2_FP_BitShift: Bit shift a 2d matrix's members to change their fixed point
// pMatrix      - the matrix to change
// nBitShift    - the number to bit shift by, pass a positive number to bit shift left and
//                a negative number to bit shift right
void Math_M2_FP_BitShift(M2* pMatrix, int nBitShift);

#endif

