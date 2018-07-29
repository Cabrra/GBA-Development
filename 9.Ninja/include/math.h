// All things arithmetic
// JJM 100826

#ifndef _MATH_H_
#define _MATH_H_

// 2D Matrix
typedef struct _M2
{
    int nX1, nY1, nW1;
    int nX2, nY2, nW2;
    int nX3, nY3, nW3;
} M2;

// Identity: Set to an identity matrix
// pMatrix      - the matrix to set
void Identity(M2* pMatrix);

// Identity_FP_24_8: Set to an identity matrix with fixed point 24.8
// pMatrix      - the matrix to set
void Identity_FP_24_8(M2* pMatrix);

// Identity_FP_16_16: Set to an identity matrix with fixed point 16.16
// pMatrix      - the matrix to set
void Identity_FP_16_16(M2* pMatrix);

// Math_M2Mult: Get the resulting 2d matrix from a 2d matrix multiply, the resulting matrix cannot be pointing to the same memory as the left or right matrix
// pResult      - resulting matrix
// pLeft        - the left matrix in the multiply
// pRight       - the right matrix in the multiply
void Math_M2Mult(M2* pResult, const M2* pLeft, const M2* pRight);

// Translation: Set new translation to matrix
// pMatrix      - the matrix to set
// nX           - the x coordinate
// nY           - the y coordinate
void Translation(M2* pMatrix, int nX, int nY);

// Scale_FP_24_8: Set new scale to matrix fixed point 24.8
// pMatrix      - the matrix to set
// nX           - the x coordinate fixed point 24.8
// nY           - the y coordinate fixed point 24.8
void Scale_FP_24_8(M2* pMatrix, int nX, int nY);

// Rotation_FP_16_16: Set new rotation to matrix fixed point 16.16
// pMatrix      - the matrix to set
// nDegree      - the degree of rotation
void Rotation_FP_16_16(M2* pMatrix, int nDegree);

// Math_M2_FP_BitShift: Bit shift a 2d matrix's members to change their fixed point
// pMatrix      - the matrix to change
// nBitShift    - the number to bit shift by, pass a positive number to bit shift left and
//                a negative number to bit shift right
void Math_M2_FP_BitShift(M2* pMatrix, int nBitShift);

// Transform: Transform the background during vertical blank period
// pMatrix      - the matrix to write to the hardware
void Transform(const M2* pMatrix);

#endif

