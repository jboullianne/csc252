/* 
 * CS:APP Data Lab 
 * 
 * Jean-Marc Boullianne
 * jboullia@u.rochester.edu
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int oddBits(void) {
  //Just a simple shift and add to build the number
  // 170 = (base 2) 1010 1010 = 0xAA 
  int result = 170;

  //0xAA << 8 == 0xAA00
  //0xAA00 + 0xAA = 0xAAAA
  result = (result << 8) + result;

  //0xAAAA << 16 = 0xAAAA0000
  //0xAAAA0000 + 0xAAAA = 0xAAAAAAAA == Odd bits
  result = (result << 16) + result;

  return result;
}
/* 
 * bitXor - x^y using only ~ and | 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ |
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
  // Expanded using simple logic rules
  // x^y == (x or y) and ~(x and y)
  //     == (x | y) & ~(x & y)
  //     == (x | y) & ~(~x | ~y)
  //     == ~(~(x | y) | ~(~x | ~y))
  return ~(~(x | y) | ~((~x) | (~y)));
}
/* 
 * swapBytes - swaps the first and last bytes of x
 *   Example: swapBytes(0x01020304) = 0x04020301
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int swapBytes(int x) {

  int byte1 = 255 & x; // copy byte1 bit pattern
  int byte2 = (255 << 8) & x; // copy byte2 bit pattern
  int byte3 = (255 << 16) & x; // copy byte3 bit pattern
  int byte4 = (255 << 24) & x; // copy byte4 bit pattern
  byte1 = byte1 << 24; //Shift LSB to most significant position
  byte4 = (byte4 >> 24) & 255; // Swap MSB to least significant position

  return byte1 | byte2 | byte3 | byte4;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {

  int leftBits, padding;
  int negN = ~n; // negN = (-n) -1;
  //negN <= -1 , therefore next statement will never shift more than 31
  int rightBits = x << (32 + negN);
  /* shift the last bit 
  couldn't shift a full 32 before because it causes unwanted behavior. */
  rightBits = rightBits << 1;
  //Need to mask only the amount of bits being shifted.
  //Dont want to have MSB to pad 1's and interfere with roatation
  padding = 1 << 31;
  padding = (padding >> n);
  padding = padding << 1;
  leftBits = (x >> n) & ~padding;
  
  //adds left shifted bits, and right bits that moved to the front
  return leftBits | rightBits;
}
/*
 * evenBitsCount - returns count of number of 1's in even numbered spaces in the word
 *   Examples: evenBitsCount(5) = 2, evenBitsCount(7) = 2, evenBitsCount(10)= 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int evenBitsCount(int x) {
  
  //Variable Declerations
  int setOne, setTwo, setThree, setFour, setFive;
  int partOne, partTwo, partTwo2, partThree, partThree2, partFour, partFour2, partFive, partFive2, final;
  int two, three, four;

  //MASKS
  setOne = 85 + (85 << 8); //0x5555
  setOne = (setOne << 16) + setOne; //0x55555555
  setTwo = 51 + (51 << 8); //0x3333
  setTwo = (setTwo << 16) + setTwo; //0x33333333
  setThree = 15 + (15 << 8); //0xF0F
  setThree = (setThree << 16) + setThree; //0xF0F0F0F
  setFour = (255 << 16) + 255; //0xFF00FF
  setFive = (255 << 8) + 255; //0xFFFF

  //Using masks from above you count the bits in a tree pattern
  partOne = x & (setOne);
  partTwo = partOne & setTwo;
  partTwo2 = (partOne >> 2) & setTwo;
  two = partTwo + partTwo2;
  partThree = two & setThree;
  partThree2 = (two >> 4) & setThree;
  three = partThree + partThree2;
  partFour = three & setFour;
  partFour2 = (three >> 8) & setFour;
  four = partFour + partFour2;
  partFive = four & setFive;
  partFive2 = (four >> 16) & setFive;
  final = partFive + partFive2;

  return final;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {

  int temp = 1 << 31; //setting temp to TMIN == 0xFFFFFFFF
  temp = ~temp; //flips the bits to == 0x7FFFFFFF
  return temp;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  
  int negY = ~y + 1; // == -y
  int sub = x + negY;// == x + (-y)

  int sign = x ^ y; //Sign bit will == 1 if x and y have different signs, 0 if same
  int sign2 = sub ^ x; //for cases such as (0x7FFFFFFF - 0x80000000)

  return !((sign & sign2)>>31);

  //return result;
}
/* 
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {

  

  int power = (1 << n) + ~0;  // 2^n - 1
  int signBit = x >> 31; //shift to get signbit in LSB position
  int result = x & power; 
  //takes 'N' amount of bytes from end of number to computer result
  result += ((~((!!result) << n)) + 1) & signBit; 
  return result;

}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  
  int TMIN = 1 << 31; // 0x80000000
  int result;  // 2 * x
  int sign; // sign bit
  int overflow; // Tells if there is overflow
  int saturate; //What number the result needs to be saturated to
  int mult;

  //If there's no overflow then result is calculated
  result = x ;
  mult = result + x;

  sign = x >> 31;
  overflow = ((x^result) | (x^mult)) >> 31;
  
  saturate = overflow & (sign ^ ~TMIN); //Calculates the saturated number if overflow

  // Returns the saturated number if there is overflow , if not then it returns the result
  return (saturate) | (~overflow & mult);
}
/* 
 * isGreaterOrEqual - if x >= y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreaterOrEqual(int x, int y) {

  int signY, signX, result;

  signY = (y >> 31) & 1; //sign Bit of y
  signX = (x >> 31) & 1; //sign Bit of X
  result = !(signY ^ signX); //checks to see whether x's and y's signs are equal to each other
  result &= ((~x + y) >> 31) & 1;
  result |=  (signY & !signX); 

  return result;
}
/*
 * multSevenSixteenths - multiplies by 7/16 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*7/16),
 *   including overflow behavior.
 *   Examples: multSevenSixteenths(77) = 33
 *             multSevenSixteenths(-22) = -9
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multSevenSixteenths(int x) {
  
  int sign = (x >> 31) & 15; //checks to see if negative sign, and if so add 15

  x = (x << 2) + x + x + x; //multiply by 7
  x += sign; //add sign number to make up for negative number
  x = x >> 4; //divide by 16

  return x;
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {

  int temp = ~x; //twos compliment of x
  int temp2 = temp + 1; // == negative x
  int sign = ~temp2 & temp; //if x == 0, sign will == 1. Else will == 0
  int result = ((sign >> 31) & 1) ^1; //returns the opposite of the sign bit
  return result;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {

  unsigned max = ~(1 << 31); // == 0x7FFFFFFF

  return (uf & max); //Sets Sign Bit to 0

}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return (int) uf;
}
/* 
 * float_quarter - Return bit-level equivalent of expression 0.25*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_quarter(unsigned uf) {
  /*
  int TMIN = 1<<31;
  unsigned expBits = 255 << 23;
  unsigned sign = TMIN & uf;
  unsigned exponent = expBits & uf;
  unsigned fraction = ~(TMIN | expBits) & uf;
  */
  int negmax = 0x80000000;//0x80000000;
  unsigned fractPadding = 0x007FFFFF;
  unsigned fractBits = uf & fractPadding;
  unsigned exponent = uf & ~(fractPadding | negmax);
  unsigned signBit = uf & negmax; 

  //Need to figure out when to add one after dividing by 4.
  //The last three bits decide. Such as... 010 == 0, 110 == 1, 111 == 1
  unsigned roundBit = 1 & (uf | (uf >> 2)) & ((uf & 2) >> 1);
  unsigned result;

  //If exponent bits are all 1's ( NaN )
  if(exponent == 0x7f800000)
  {
    return uf;
  }

  //If exponent bits are all 0 then you have to shift fractBits (Denormalized Values)
  if(!exponent)
  {
    fractBits >>= 2; //Division by 4
    fractBits += roundBit;
    result = signBit | exponent | fractBits;
    return result;
  }

  //Negative and Positive Zero is always zero
  if(uf == 0 || uf == 0x80000000)
  {
    return uf;
  }

  //For cases when exponent bits == 1. you cant just subtract 2.
  if(exponent == 0x800000){
    exponent >>= 2;
    fractBits >>=2;
    fractBits += roundBit;
    result = signBit | exponent | fractBits;
    return result;
  }

  //Normal case. Use Normalized Values
  exponent -= 0x1000000; //subtract 2 from the exponent bits. Division by 4
  result = signBit | exponent | fractBits;
  return result;
  
}
