/*************************************************
* Lowest Level MPI Algorithms Header File        *
* (C) 1999-2006 The Botan Project                *
*************************************************/

#ifndef BOTAN_MP_ASM_INTERNAL_H__
#define BOTAN_MP_ASM_INTERNAL_H__

#include <botan/mp_asm.h>

namespace Botan {

extern "C" {

/*************************************************
* Word Addition                                  *
*************************************************/
inline word word_add(word x, word y, word* carry)
   {
   word z = x + y;
   word c1 = (z < x);
   z += *carry;
   *carry = c1 | (z < *carry);
   return z;
   }

/*************************************************
* Eight Word Block Addition, Two Argument        *
*************************************************/
inline word word8_add2(word x[8], const word y[8], word carry)
   {
   x[0] = word_add(x[0], y[0], &carry);
   x[1] = word_add(x[1], y[1], &carry);
   x[2] = word_add(x[2], y[2], &carry);
   x[3] = word_add(x[3], y[3], &carry);
   x[4] = word_add(x[4], y[4], &carry);
   x[5] = word_add(x[5], y[5], &carry);
   x[6] = word_add(x[6], y[6], &carry);
   x[7] = word_add(x[7], y[7], &carry);
   return carry;
   }

/*************************************************
* Eight Word Block Addition, Three Argument      *
*************************************************/
inline word word8_add3(word z[8], const word x[8],
                       const word y[8], word carry)
   {
   z[0] = word_add(x[0], y[0], &carry);
   z[1] = word_add(x[1], y[1], &carry);
   z[2] = word_add(x[2], y[2], &carry);
   z[3] = word_add(x[3], y[3], &carry);
   z[4] = word_add(x[4], y[4], &carry);
   z[5] = word_add(x[5], y[5], &carry);
   z[6] = word_add(x[6], y[6], &carry);
   z[7] = word_add(x[7], y[7], &carry);
   return carry;
   }

/*************************************************
* Word Subtraction                               *
*************************************************/
inline word word_sub(word x, word y, word* carry)
   {
   word t0 = x - y;
   word c1 = (t0 > x);
   word z = t0 - *carry;
   *carry = c1 | (z > t0);
   return z;
   }

/*************************************************
* Eight Word Block Subtraction, Two Argument     *
*************************************************/
inline word word8_sub2(word x[4], const word y[4], word carry)
   {
   x[0] = word_sub(x[0], y[0], &carry);
   x[1] = word_sub(x[1], y[1], &carry);
   x[2] = word_sub(x[2], y[2], &carry);
   x[3] = word_sub(x[3], y[3], &carry);
   x[4] = word_sub(x[4], y[4], &carry);
   x[5] = word_sub(x[5], y[5], &carry);
   x[6] = word_sub(x[6], y[6], &carry);
   x[7] = word_sub(x[7], y[7], &carry);
   return carry;
   }

/*************************************************
* Eight Word Block Subtraction, Three Argument   *
*************************************************/
inline word word8_sub3(word z[8], const word x[8],
                       const word y[8], word carry)
   {
   z[0] = word_sub(x[0], y[0], &carry);
   z[1] = word_sub(x[1], y[1], &carry);
   z[2] = word_sub(x[2], y[2], &carry);
   z[3] = word_sub(x[3], y[3], &carry);
   z[4] = word_sub(x[4], y[4], &carry);
   z[5] = word_sub(x[5], y[5], &carry);
   z[6] = word_sub(x[6], y[6], &carry);
   z[7] = word_sub(x[7], y[7], &carry);
   return carry;
   }

/*************************************************
* Eight Word Block Linear Multiplication         *
*************************************************/
inline word word8_linmul2(word x[4], word y, word carry)
   {
   x[0] = word_madd2(x[0], y, carry, &carry);
   x[1] = word_madd2(x[1], y, carry, &carry);
   x[2] = word_madd2(x[2], y, carry, &carry);
   x[3] = word_madd2(x[3], y, carry, &carry);
   x[4] = word_madd2(x[4], y, carry, &carry);
   x[5] = word_madd2(x[5], y, carry, &carry);
   x[6] = word_madd2(x[6], y, carry, &carry);
   x[7] = word_madd2(x[7], y, carry, &carry);
   return carry;
   }

/*************************************************
* Eight Word Block Linear Multiplication         *
*************************************************/
inline word word8_linmul3(word z[8], const word x[8], word y, word carry)
   {
   z[0] = word_madd2(x[0], y, carry, &carry);
   z[1] = word_madd2(x[1], y, carry, &carry);
   z[2] = word_madd2(x[2], y, carry, &carry);
   z[3] = word_madd2(x[3], y, carry, &carry);
   z[4] = word_madd2(x[4], y, carry, &carry);
   z[5] = word_madd2(x[5], y, carry, &carry);
   z[6] = word_madd2(x[6], y, carry, &carry);
   z[7] = word_madd2(x[7], y, carry, &carry);
   return carry;
   }

/*************************************************
* Eight Word Block Multiply/Add                  *
*************************************************/
inline word word8_madd3(word z[8], const word x[8], word y, word carry)
   {
   z[0] = word_madd3(x[0], y, z[0], carry, &carry);
   z[1] = word_madd3(x[1], y, z[1], carry, &carry);
   z[2] = word_madd3(x[2], y, z[2], carry, &carry);
   z[3] = word_madd3(x[3], y, z[3], carry, &carry);
   z[4] = word_madd3(x[4], y, z[4], carry, &carry);
   z[5] = word_madd3(x[5], y, z[5], carry, &carry);
   z[6] = word_madd3(x[6], y, z[6], carry, &carry);
   z[7] = word_madd3(x[7], y, z[7], carry, &carry);
   return carry;
   }

}

}

#endif
