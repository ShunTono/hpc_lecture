#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <immintrin.h>

int main() {
  const int N = 8;
  float x[N], y[N], m[N], fx[N], fy[N], a[N];
  for(int i=0; i<N; i++) {
    a[i] = i;
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
  }
  __m256 ivec = _mm256_load_ps(a);
  __m256 xivec = _mm256_load_ps(x);
  __m256 yivec = _mm256_load_ps(y);
  __m256 mivec = _mm256_load_ps(m);
  __m256 fxivec = _mm256_setzero_ps();
  __m256 fyivec = _mm256_setzero_ps();

  for(int i=0; i<N; i++) {
    float b[N];
    for(int j=0; j<N; j++){
	b[j] = j;
	
	__m256 jvec = _mm256_load_ps(b);
	__m256 xjvec = _mm256_setzero_ps();
	__m256 yjvec = _mm256_setzero_ps();
	__m256 mjvec = _mm256_setzero_ps();
	__m256 mask = _mm256_cmp_ps(jvec, ivec, _CMP_NEQ_OQ);

	xjvec = _mm256_blendv_ps(xjvec, xivec, mask);
	yjvec = _mm256_blendv_ps(yjvec, yivec, mask);
	mjvec = _mm256_blendv_ps(mjvec, mivec, mask);
	
        __m256 rxvec = _mm256_sub_ps(xivec, xjvec);//float rx = x[i] - x[j];
        __m256 ryvec = _mm256_sub_ps(yivec, yjvec);//float ry = y[i] - y[j];

	__m256 rx2vec = _mm256_mul_ps(rxvec, rxvec);
	__m256 ry2vec = _mm256_mul_ps(ryvec, ryvec);
	__m256 prervec = _mm256_setzero_ps();
	prervec = _mm256_sub_ps(rx2vec, ry2vec);

        __m256 rvec = _mm256_rsqrt_ps(prervec);//float r = std::sqrt(rx * rx + ry * ry);
	__m256 r2vec = _mm256_mul_ps(rvec, rvec);
	__m256 r3vec = _mm256_mul_ps(r2vec, rvec);
	__m256 rxmjvec = _mm256_mul_ps(rxvec, mjvec);
	__m256 rymjvec = _mm256_mul_ps(ryvec, mjvec);
	__m256 prefxvec = _mm256_mul_ps(rxmjvec, r3vec);
	__m256 prefyvec = _mm256_mul_ps(rymjvec, r3vec);

	fxivec = _mm256_sub_ps(fxivec, prefxvec);
	fyivec = _mm256_sub_ps(fyivec, prefyvec);

	_mm256_store_ps(fx, fxivec);
	_mm256_store_ps(fy, fyivec);
    }
    printf("%d %g %g \n",i,fx[i],fy[i]);
  }
}
