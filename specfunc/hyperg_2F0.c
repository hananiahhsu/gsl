/* Author:  G. Jungman
 * RCS:     $Id$
 */
#include <math.h>
#include <gsl_math.h>
#include <gsl_errno.h>
#include "gsl_sf_hyperg.h"


/* [Carlson, p.109] says the error in truncating this asymptotic series
 * is less than the absolute value of the first neglected term
 */
static int hyperg_2F0_series(const double a, const double b, const double x,
                             double * result, double * prec
			     )
{
  double an = a;
  double bn = b;  
  double n   = 1.0;
  double sum = 1.0;
  double del = 1.0;
  double abs_del = 1.0;
  double max_abs_del = 1.0;
  double last_abs_del = 1.0;
  double err;
  
  while(abs_del/fabs(sum) > GSL_MACH_EPS && n < 200.0) {

    double u = an * (bn/n * x);
    double abs_u = fabs(u);

    if(abs_u > 1.0 && (max_abs_del > DBL_MAX/abs_u)) {
      *prec = 1.0;
      *result = sum;
      return GSL_EOVRFLW;
    }

    del *= u;
    sum += del;

    abs_del      = fabs(del);

    

    last_abs_del = abs_del;
    max_abs_del  = locMAX(abs_del, max_abs_del);

    an += 1.0;
    bn += 1.0;
    n  += 1.0;
    
    if(an == 0.0 || bn == 0.0) break;  /* terminating series */
  }
  
  max_abs_del *= GSL_MACH_EPS;
  err     = fabs(GSL_MACH_EPS * n + max_abs_del);
  *prec   = err/(err + fabs(sum));
  *result = sum;
  if(*prec > locEPS)
    return GSL_ELOSS;
  else
    return GSL_SUCCESS;
}


