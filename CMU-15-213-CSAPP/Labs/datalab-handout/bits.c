/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int a = ~x & y; 
  int b = x & ~y; 
  return ~(~a & ~b); 
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
// 0 0 1
// 1 1 0
// 01111 + 1 = 
// 1000000
// 10000001
int isTmax(int x) {
    int plusOne = x + 1;
    int negX = ~x;
    
    // Check if x is Tmax by checking if x + 1 becomes Tmin after wrapping around
    // Also, check if x is not Tmin (since Tmin + 1 becomes Tmax)
    return !(plusOne ^ negX) & !!plusOne;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int bit_mask = 0x55555555;
  return !((x | bit_mask) ^ 0xFFFFFFFF);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { // Mechanism Unclear
  return ~x + 1;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int upperCheck = !(x >> 4 ^ 0x3);  
  int lowerCheck = (x & 0xF) + (~0xA + 1); 
  return upperCheck & (lowerCheck >> 31);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mask = !!x; // mask is 1 if non-zero, 0 if zero
  
  // mask = 0xFFFFFFFF if x is non-zero 
  // mask = 0x00000000 if x is zero
  mask = ~mask + 1; 
  return (mask & y) | (~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // Compute the sign bits of x and y
    int signX = x >> 31 & 1;
    int signY = y >> 31 & 1;

    // Compute the difference between y and x
    int diff = y + ~x + 1; // This is equivalent to y - x

    // Compute the sign bit of the difference
    int signDiff = diff >> 31 & 1;

    // Determine if x and y have different signs
    int differentSigns = signX ^ signY;

    // If x and y have different signs, return 1 if x is negative
    // If x and y have the same sign, return 1 if diff is non-negative
    return (differentSigns & signX) | (!differentSigns & !signDiff);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // if x = 0, return 1
  // if x = 0
  int neg_x = ~x + 1;
  int combined = neg_x | x;
  int signBit = combined >> 31 & 1;
  return signBit ^ 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1 0x0
 *            howManyBits(-1) = 1 -
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
       /*
     * We first bit invert all negative numbers and
     * use binary search to find out the log2(n).
     * Then we add 1 to the final result since we need
     * the MSB to represent the sign.
     * Note: finding the following things are equal:
     * 1. find the most significant bit of 1 for positive numbers
     * 2. find the most significant bit of 0 for negative numbers
     */
    
    /* I hate this, but I have to avoid parse error */
    int sign, bit0, bit1, bit2, bit4, bit8, bit16;

    sign = x >> 31;
    
    /* Bit invert x as needed */
    x = (sign & ~x) | (~sign & x);
    
    /* Binary Search on bit level */
    bit16 = !!(x >> 16) << 4;
    x = x >> bit16;
    
    bit8 = !!(x >> 8) << 3;
    x = x >> bit8;
    
    bit4 = !!(x >> 4) << 2;
    x = x >> bit4;
    
    bit2 = !!(x >> 2) << 1;
    x = x >> bit2;
    
    bit1 = !!(x >> 1);
    x = x >> bit1;
    
    bit0 = x;

    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}

/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) {
    return uf;
  }

  if (exp == 0) { // denormalized
    frac <<= 1;
    if (frac & 0x80000000) {
      frac &= 0x7FFFFF;
      exp = 1;
    }
  } else {
    exp += 1;
    if (exp == 0xFF) {
      frac = 0;
    }
  }
  return sign | (exp << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
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
int floatFloat2Int(unsigned uf) {
    unsigned sign = uf >> 31;
    int exp = ((uf >> 23) & 0xFF) - 127; // Get the exponent and adjust by the bias
    unsigned frac = (uf & 0x7FFFFF) | 0x800000; // Add the implicit leading 1 for the mantissa

    // Handle out of range cases
    if (exp >= 31) {
        return 0x80000000; // Return out of range indicator
    }
    if (exp < 0) {
        return 0; // Numbers less than 1 truncate to 0
    }

    // Adjust the mantissa according to the exponent
    if (exp > 23) {
        frac <<= (exp - 23);
    } else {
        frac >>= (23 - exp);
    }

    // Apply the sign
    if (sign) {
        frac = -frac;
    }

    return frac;
}

/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int exp = x + 127;
  if (exp <= 0) {
    return 0;
  }
  if (exp >= 255) {
    return 0x7F800000;
  }
  return exp << 23;
}