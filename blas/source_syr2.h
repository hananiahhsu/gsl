/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

  size_t i, j;
  size_t ix, iy;
  size_t jx = 0;
  size_t jy = 0;

  if(Uplo == CblasUpper) {
    for(j=0; j<N; j++) {
      const BASE_TYPE tmp1 = alpha * Y[jy];
      const BASE_TYPE tmp2 = alpha * X[jx];
      ix = jx;
      iy = jy;
      for(i=j; i<N; i++) {
        A[lda*j + i] += X[ix]*tmp1 + Y[iy]*tmp2;
	ix += incX;
	iy += incY;
      }
      jx += incX;
      jy += incY;
    }
  }
  else {
    for(j=0; j<N; j++) {
      const BASE_TYPE tmp1 = alpha * Y[jy];
      const BASE_TYPE tmp2 = alpha * X[jx];
      ix = 0;
      iy = 0;
      for(i=0; i<=j; i++) {
        A[lda*j + i] += X[ix]*tmp1 + Y[iy]*tmp2;
        ix += incX;
        iy += incY;
      }
      jx += incX;
      jy += incY;
    }
  }
