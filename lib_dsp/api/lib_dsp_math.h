// Copyright (c) 2016, XMOS Ltd, All rights reserved

#ifndef LIB_DSP_MATH
#define LIB_DSP_MATH

/**  Scalar multipliplication
 * 
 *  This function multiplies two scalar values and produces a result according
 *  to fixed-point format specified by the ``q_format`` parameter.
 * 
 *  The two operands are multiplied to produce a 64-bit result which is tested for overflow,
 *  and shifted right by ``q_format`` bits.
 *
 *  Algorithm:
 * 
 *  \code
 *  1) Y = X1 * X2
 *  3) Y = Y >> q_format
 *  \endcode
 *
 *  Example:
 * 
 *  \code
 *  int result;
 *  result = lib_dsp_math_multiply( Q28(-0.33), sample, 28 );
 *  \endcode
 * 
 *  \param  input1_value  Multiply operand #1.
 *  \param  input2_value  Multiply operand #2.
 *  \param  q_format      Fixed point format (i.e. number of fractional bits).
 *  \returns              input1_value * input2_value.
 */

int lib_dsp_math_multiply
(
    int input1_value,
    int input2_value,
    int q_format
);

/**  Scalar saturated multipliplication
 *
 *  This function multiplies two scalar values and produces a result according
 *  to fixed-point format specified by the ``q_format`` parameter.
 *
 *  The two operands are multiplied to produce a 64-bit result which is tested for overflow,
 *  clamped at the minimum/maximum value given the fixed-point format if overflow occurs,
 *  and finally shifted right by ``q_format`` bits.
 *
 *  Algorithm:
 *
 *  \code
 *  1) Y = X1 * X2
 *  2) Y = min( max( Q_FORMAT_MIN, Y ), Q_FORMAT_MAX, Y )
 *  3) Y = Y >> q_format
 *  \endcode
 *
 *  Example:
 *
 *  \code
 *  int result;
 *  result = lib_dsp_math_multiply( Q28(-0.33), sample, 28 );
 *  \endcode
 *
 *  While saturation is employed after multiplication an overflow condition when preparing the final
 *  result must still be considered when specifying a Q-format whose fixed-point numerical range do
 *  not accomodate the final result of multiplication and saturation (if applied).
 *
 *  \param  input1_value  Multiply operand #1.
 *  \param  input2_value  Multiply operand #2.
 *  \param  q_format      Fixed point format (i.e. number of fractional bits).
 *  \returns              input1_value * input2_value.
 */
int lib_dsp_math_multiply_sat(
        int input1_value,
        int input2_value,
        int q_format );


/** Scalar reciprocal
 * 
 *  This function computes the reciprocal of the input value using an iterative
 *  approximation method as follows:
 * 
 *  \code
 *  1) result = 1.0
 *  2) result = result + result * (1 - input * result)
 *  3) Repeat step #2 until desired precision is achieved
 *  \endcode
 * 
 *  Example:
 * 
 *  \code
 *  int result;
 *  result = lib_dsp_math_reciprocal( sample, 28 );
 *  \endcode
 * 
 *  \param  input_value  Input value for computation.
 *  \param  q_format     Fixed point format (i.e. number of fractional bits).
 *  \returns             The reciprocal of the input value.
 */

int lib_dsp_math_reciprocal( int input_value, int q_format );

/** Scalar inverse square root
 * 
 *  This function computes the reciprocal of the square root of the input value
 *  using an iterative approximation method as follows:
 * 
 *  \code
 *  1) result = 1.0
 *  2) result = result + result * (1 - input * result^2) / 2
 *  3) Repeat step #2 until desired precision is achieved
 *  \endcode
 * 
 *  Example:
 * 
 *  \code
 *  int result;
 *  result = lib_dsp_math_invsqrroot( sample, 28 );
 *  \endcode
 * 
 *  \param  input_value  Input value for computation.
 *  \param  q_format     Fixed point format (i.e. number of fractional bits).
 *  \returns             The inverse square root of the input value.
 */

int lib_dsp_math_invsqrroot( int input_value, int q_format );

/** Scalar square root
 * 
 *  This function computes the square root of the input value using the
 *  following steps:
 * 
 *  \code
 *  int result;
 *  result = lib_dsp_math_invsqrroot( input )
 *  result = lib_dsp_math_reciprocal( result )
 *  \endcode
 * 
 *  Example:
 * 
 *  \code
 *  int result;
 *  result = lib_dsp_math_squareroot( sample, 28 );
 *  \endcode
 * 
 *  \param  input_value  Input value for computation.
 *  \param  q_format     Fixed point format (i.e. number of fractional bits).
 *  \returns             The square root of the input value.
 */

int lib_dsp_math_squareroot( int input_value, int q_format );



// Note: This was ported from mathf8_24.h (

/** This constant defines the smallest number that is defined in the fixed
 * point range, which is -128.
 */
#define MINint (0x80000000)

/** This constant defines the biggest number that is defined in the fixed
 * point range, which is 127.999999940395355224609375
 */
#define MAXint (0x7FFFFFFF)

/** This constant is the fixed point representation of the number 0.5
 */
#define HALF    (1<<(MATHint_BITS-1))

/** This constant is the fixed point representation of the number 1.0
 */
#define ONE     (HALF * 2)

/** This constant is the closest fixed point representation of 2 PI.
 */
#define PI2     (105414357)

/** This constant is the fixed point representation of PI/2
 */
#define PIHALF   (26353589)


/** This function returns the sine of a fixed point number in radians. The
 * input number has to be in the range -MAXint + PI and MAXint - PI.
 *
 * \param x input value in radians
 * \returns sine(x)
 **/
int lib_dsp_math_sin(int rad, int q_format);

/** This function returns the cosine of a fixed point number in radians. The
 * input number has to be in the range -MAXint + PI and MAXint - PI.
 *
 * \param x input value in radians
 * \returns cosine(x)
 **/
inline int lib_dsp_math_cos(int x, int q_format) {
    return lib_dsp_math_sin(x+PIHALF, q_format);
}


#endif
