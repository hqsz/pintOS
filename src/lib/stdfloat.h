#ifndef __LIB_STDFLOAT_H
#define __LIB_STDFLOAT_H

#include "stdint.h"

typedef int32_t float32_t;
typedef int64_t float64_t;

#define F (1 << 14)
#define SIGN(X) ((X) >> (31))

float32_t int_to_float(int32_t);
int32_t float_to_int(float32_t);
float32_t float_add(float32_t, float32_t);
float32_t float_sub(float32_t, float32_t);
float32_t float_mul(float32_t, float32_t);
float32_t float_div(float32_t, float32_t);
float32_t float_add_int(float32_t, int32_t);
float32_t float_sub_int(float32_t, int32_t);
float32_t float_mul_int(float32_t, int32_t);
float32_t float_div_int(float32_t, int32_t);

#endif
