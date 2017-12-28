#include "stdfloat.h"

/* Define fixed-point arithmetic operations. */
float32_t int_to_float(int32_t n){
  return n * F;
}

int32_t float_to_int(float32_t x){
  if(SIGN(x)) return (x - F / 2) / F;
  else return (x + F / 2) / F;
}

float32_t float_add(float32_t x, float32_t y){
  return x + y;
}

float32_t float_sub(float32_t x, float32_t y){
  return x - y;
}

float32_t float_mul(float32_t x, float32_t y){
  return ((float64_t)x) * y / F;
}

float32_t float_div(float32_t x, float32_t y){
  return ((float64_t)x) * F / y;
}

float32_t float_add_int(float32_t x, int32_t n){ 
  return x + n * F; //float_add(x, int_to_float(n))
}

float32_t float_sub_int(float32_t x, int32_t n){
  return x - n * F; //float_sub(x, int_to_float(n))
}

float32_t float_mul_int(float32_t x, int32_t n){
  return x * n; //float_mul(x, int_to_float(n));
}

float32_t float_div_int(float32_t x, int32_t n){
  return x / n; //float_div(x, int_to_float(n));
}

