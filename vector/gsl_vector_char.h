#ifndef GSL_VECTOR_CHAR_H
#define GSL_VECTOR_CHAR_H

#include <stdlib.h>
#include <gsl_errno.h>

struct gsl_matrix_char_struct;

struct gsl_vector_char_struct
{
  size_t size;
  size_t stride;
  struct gsl_matrix_char_struct * parent;
  char *data;
};

typedef struct gsl_vector_char_struct gsl_vector_char;

gsl_vector_char *gsl_vector_char_alloc (size_t n);
gsl_vector_char *gsl_vector_char_calloc (size_t n);
void gsl_vector_char_free (gsl_vector_char * v);

char *gsl_vector_char_ptr (const gsl_vector_char * v, const size_t i);
char gsl_vector_char_get (const gsl_vector_char * v, const size_t i);
void gsl_vector_char_set (gsl_vector_char * v, const size_t i, char c);

int gsl_vector_char_fread (FILE * stream, gsl_vector_char * v);
int gsl_vector_char_fwrite (FILE * stream, const gsl_vector_char * v);
int gsl_vector_char_fscanf (FILE * stream, gsl_vector_char * v);
int gsl_vector_char_fprintf (FILE * stream, const gsl_vector_char * v,
			     const char *format);

int gsl_block_char_fread (FILE * stream, char *data, size_t n, size_t stride);
int gsl_block_char_fwrite (FILE * stream, const char *data, size_t n,
			   size_t stride);
int gsl_block_char_fscanf (FILE * stream, char *data, size_t n, size_t stride);
int gsl_block_char_fprintf (FILE * stream, const char *data, size_t n,
			    size_t stride, const char *format);

extern int gsl_check_range;

#ifdef HAVE_INLINE
extern inline
char *
gsl_vector_char_ptr (const gsl_vector_char * v, const size_t i)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size)	/* size_t is unsigned, can't be negative */
    {
      GSL_ERROR_RETURN ("index out of range", GSL_EINVAL, 0);
    }
#endif
  return v->data + i * v->stride;
}

extern inline
char
gsl_vector_char_get (const gsl_vector_char * v, const size_t i)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size)	/* size_t is unsigned, can't be negative */
    {
      GSL_ERROR_RETURN ("index out of range", GSL_EINVAL, 0);
    }
#endif
  return v->data[i * v->stride];
}

extern inline
void
gsl_vector_char_set (gsl_vector_char * v, const size_t i, char c)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size)	/* size_t is unsigned, can't be negative */
    {
      GSL_ERROR_RETURN_NOTHING ("index out of range", GSL_EINVAL);
    }
#endif
  v->data[i * v->stride] = c;
}
#endif /* HAVE_INLINE */

#endif /* GSL_VECTOR_CHAR_H */
