/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

  size_t i, j;
  size_t ix, iy, jx, jy;

  iy = 0;
  for(i=0; i<N; i++) {
    Y[iy] *= beta;
    iy += incY;
  }

  if(Uplo == CblasUpper) {
    jx = 0;
    jy = 0;
    for(j=0; j<N; j++) {
      BASE_TYPE tmp1 = alpha * X[jx];
      BASE_TYPE tmp2 = 0.0;
      Y[jy] += tmp1*A[lda*j + j];
      ix = jx;
      iy = jy;
      for(i=j+1; i<N; i++) {
        ix += incX;
        iy += incY;
        Y[iy] += tmp1 * A[lda*j + i];
	tmp2  += A[lda*j + i] * X[ix];
      }
      Y[jy] += alpha * tmp2;
      jx += incX;
      jy += incY;
    }
  }
  else {
    jx = 0;
    jy = 0;
    for(j=0; j<N; j++) {
      BASE_TYPE tmp1 = alpha * X[jx];
      BASE_TYPE tmp2 = 0.0;
      ix = 0;
      iy = 0;
      for(i=0; i<j; i++) {
        Y[iy] += tmp1 * A[lda*j + i];
	tmp2  += A[lda*j + i] * X[ix];
	ix += incX;
        iy += incY;
      }
      Y[jy] += tmp1*A[lda*j + j] + alpha * tmp2;
      jx += incX;
      jy += incY;
    }
  }
