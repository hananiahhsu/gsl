void FUNCTION (test, func) (void);
void FUNCTION (test, binary) (void);
void FUNCTION (test, trap) (void);

void
FUNCTION (test, func) (void)
{
  size_t i;

  TYPE (gsl_block) * b = FUNCTION (gsl_block, alloc) (N);
  TYPE (gsl_vector) * v = FUNCTION (gsl_vector, alloc) (b,0,N,1);

  gsl_test (v->data == 0, NAME (gsl_vector) "_alloc returns valid pointer");
  gsl_test (v->size != N, NAME (gsl_vector) "_alloc returns valid size");
  gsl_test (v->stride != 1, NAME (gsl_vector) "_alloc returns unit stride");

  for (i = 0; i < N; i++)
    {
      BASE x;
      GSL_REAL (x) = i;
      GSL_IMAG (x) = i + 1234;
      FUNCTION (gsl_vector, set) (v, i, x);
    };

  status = 0;

  for (i = 0; i < N; i++)
    {
      if (v->data[2 * i] != (ATOMIC) i || v->data[2 * i + 1] != (ATOMIC) (i + 1234))
	status = 1;
    };
  
  gsl_test (status, NAME (gsl_vector) "_set writes into array correctly");

  status = 0;

  for (i = 0; i < N; i++)
    {
      BASE x, y;
      GSL_REAL (x) = i;
      GSL_IMAG (x) = i + 1234;
      y = FUNCTION (gsl_vector, get) (v, i);
      if (!GSL_COMPLEX_EQ (x, y))
	status = 1;
    };
  gsl_test (status, NAME (gsl_vector) "_get reads from array correctly");

  /* Now set stride to 2 */

  v->stride = 2 ;

  status = 0;

  for (i = 0; i < N / 2; i++)
    {
      BASE x, y;
      GSL_REAL (x) = 2 * i;
      GSL_IMAG (x) = 2 * i + 1234;
      y = FUNCTION (gsl_vector, get) (v, i);
      if (!GSL_COMPLEX_EQ (x, y))
	status = 1;
    };
  gsl_test (status, NAME (gsl_vector) "_get reads from array correctly with stride");

  for (i = 0; i < N / 2; i++)
    {
      BASE x;
      GSL_REAL (x) = i ;
      GSL_IMAG (x) = i + 1234;
      FUNCTION (gsl_vector, set) (v, i, x);
    };

  status = 0;

  for (i = 0; i < N / 2; i++)
    {
      if (v->data[2 * 2 * i] != (ATOMIC) i || v->data[2 * 2 * i + 1] != (ATOMIC) (i + 1234))
	status = 1;
    };
  
  gsl_test (status, NAME (gsl_vector) "_set writes into array correctly with stride");

  
  FUNCTION (gsl_vector, free) (v);	/* free whatever is in v */
  FUNCTION (gsl_block, free) (b);

}

void
FUNCTION (test, binary) (void)
{
  TYPE (gsl_block) * bv = FUNCTION (gsl_block, alloc) (N);
  TYPE (gsl_block) * bw = FUNCTION (gsl_block, alloc) (N);
  TYPE (gsl_vector) * v = FUNCTION (gsl_vector, alloc) (bv,0,N,1);
  TYPE (gsl_vector) * w = FUNCTION (gsl_vector, alloc) (bw,0,N,1);

  size_t i;

  {
    FILE *f = fopen ("test.dat", "w");

    for (i = 0; i < N; i++)
      {
	BASE x;
	GSL_REAL (x) = N - i;
	GSL_IMAG (x) = N - i + 1;
	FUNCTION (gsl_vector, set) (v, i, x);
      };

    FUNCTION (gsl_vector, fwrite) (f, v);

    fclose (f);
  }

  {
    FILE *f = fopen ("test.dat", "r");

    FUNCTION (gsl_vector, fread) (f, w);

    status = 0;
    for (i = 0; i < N; i++)
      {
	if (w->data[2 * i] != (ATOMIC) (N - i) || w->data[2 * i + 1] != (ATOMIC) (N - i + 1))
	  status = 1;
      };
    fclose (f);
  }

  FUNCTION (gsl_vector, free) (v);
  FUNCTION (gsl_vector, free) (w);
  FUNCTION (gsl_block, free) (bv);
  FUNCTION (gsl_block, free) (bw);

  gsl_test (status, NAME (gsl_vector) "_write and read work correctly");

}


void
FUNCTION (test, trap) (void)
{
  TYPE (gsl_block) * bc = FUNCTION (gsl_block, alloc) (N);
  TYPE (gsl_vector) * vc = FUNCTION (gsl_vector, alloc) (bc,0,N,1);

  BASE z = {{1.2, 3.4}};
  BASE z1 = {{4.5, 6.7}};

  size_t j = 0;

  status = 0;
  FUNCTION (gsl_vector, set) (vc, j - 1, z);
  gsl_test (!status,
	    NAME (gsl_vector) "_set traps index below lower bound");

  status = 0;
  FUNCTION (gsl_vector, set) (vc, N + 1, z);
  gsl_test (!status,
	    NAME (gsl_vector) "_set traps index above upper bound");

  status = 0;
  FUNCTION (gsl_vector, set) (vc, N, z);
  gsl_test (!status, NAME (gsl_vector) "_set traps index at upper bound");

  status = 0;
  z1 = FUNCTION (gsl_vector, get) (vc, j - 1);
  gsl_test (!status,
	    NAME (gsl_vector) "_get traps index below lower bound");

  gsl_test (GSL_REAL (z1) != 0,
	    NAME (gsl_vector) "_get returns zero real below lower bound");
  gsl_test (GSL_IMAG (z1) != 0,
	    NAME (gsl_vector) "_get returns zero imag below lower bound");

  status = 0;
  z1 = FUNCTION (gsl_vector, get) (vc, N + 1);
  gsl_test (!status,
	    NAME (gsl_vector) "_get traps index above upper bound");
  gsl_test (GSL_REAL (z1) != 0,
	    NAME (gsl_vector) "_get returns zero real above upper bound");
  gsl_test (GSL_IMAG (z1) != 0,
	    NAME (gsl_vector) "_get returns zero imag above upper bound");

  status = 0;
  z1 = FUNCTION (gsl_vector, get) (vc, N);
  gsl_test (!status, NAME (gsl_vector) "_get traps index at upper bound");
  gsl_test (GSL_REAL (z1) != 0,
	    NAME (gsl_vector) "_get returns zero real at upper bound");
  gsl_test (GSL_IMAG (z1) != 0,
	    NAME (gsl_vector) "_get returns zero imag at upper bound");

  FUNCTION (gsl_vector, free) (vc);
  FUNCTION (gsl_block, free) (bc);
}




