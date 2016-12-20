#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "intrinsics.h"
#include "fpmath.h"
#include "fft.h"

#define trace(...)      printf("[FFT] "__VA_ARGS__)

#define TEST_LENGTH_SAMPLES 2048
#define FFT_SIZE            1024

/* External Input and Output buffer Declarations */
extern float f32in[TEST_LENGTH_SAMPLES];
static fft_complex_t input[FFT_SIZE];

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, maxIndex = 0;

void cmplx_float_to_int(float *in, fft_complex_t * out, int size, int scaling)
{
    for (int i=0; i<size; i++) {
        out[i].r = in[i*2+0]*scaling;
        out[i].i = in[i*2+1]*scaling;
    }
}

void cmplx_float_to_real_int(float *in, fft_complex_t * out, int size, int scaling)
{
    for (int i=0; i<size/2; i++) {
        out[i].r = (int32_t)(scaling * in[i*4 + 0]);
        out[i].i = (int32_t)(scaling * in[i*4 + 2]);
    }
}

int32_t find_max_value_location(fft_complex_t *in, int size)
{
    int32_t maxIndex = 0;
    int32_t max = 0;

    for (int i = 0; i < size; i++)
    {
        int32_t val = (int32_t)abs(in[i].r);
        //printf("%d,%d\n", (int)i, val);
        if (val > max) {
            max = val;
            maxIndex = i;
        }
    }
    return maxIndex;
}

void fft_complex(void)
{
  /* COMPLEX INT INPUT */
  cmplx_float_to_int(f32in, input, FFT_SIZE, 1000);
  fft_fft(input, 10);

  /* find max */
  maxIndex = find_max_value_location(input, FFT_SIZE/2);

  trace("COMPLEX INPUT: maxIndex: %d vs. refIndex: %d\r\n", maxIndex, refIndex);
}

void fft_real(void)
{
  /* REAL INT INPUT */
  cmplx_float_to_real_int(f32in, input, FFT_SIZE, 1000);
  fft_fftr(input, 9); // 9 for 512

  /* find max */
  maxIndex = find_max_value_location(input, FFT_SIZE/2);

  trace("REAL INPUT: maxIndex: %d vs. refIndex: %d\r\n", maxIndex, refIndex);
}

int32_t main(void)
{
    fft_complex();
    fft_real();
    return 0;
}

