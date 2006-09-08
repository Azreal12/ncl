#include <stdio.h>
#include "wrapper.h"

extern void NGCALLF(dimavgwgt,DIMAVGWGT)(int *, double *, double *, 
					 double *, int *, double *);
extern void NGCALLF(dimsumwgt,DIMSUMWGT)(int *, double *, double *, 
					 double *, int *, double *);

NhlErrorTypes dim_avg_wgt_W( void )
{

/*
 * Input variables
 */
/*
 * Argument # 0
 */
  void *x;
  double *tmp_x;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS];
  int has_missing_x;
  NclScalar missing_x, missing_flt_x, missing_dbl_x;
  NclBasicDataTypes type_x;

/*
 * Argument # 1
 */
  void *w;
  double *tmp_w;
  int dsizes_w[1];
  NclBasicDataTypes type_w;

/*
 * Argument # 2
 */
  int *opt;
/*
 * Return variable
 */
  void *xavg;
  double tmp_xavg[1];
  int ndims_xavg, *dsizes_xavg;
  NclBasicDataTypes type_xavg;
  NclScalar missing_xavg;

/*
 * Various
 */
  int nx, index_x;
  int i, ndims_leftmost, size_output;

/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value.
 */
/*
 * Get argument # 0
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x,
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);

/*
 * Coerce missing value to double if necessary.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,
                 &missing_dbl_x,&missing_flt_x);

  nx = dsizes_x[ndims_x-1];
/*
 * Get argument # 1
 */
  w = (void*)NclGetArgValue(
           1,
           3,
           NULL,
           dsizes_w,
           NULL,
           NULL,
           &type_w,
           2);

  if(dsizes_w[0] != nx) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_avg_wgt: The rightmost argument of w must be length nx");
    return(NhlFATAL);
  }
/*
 * Get argument # 2
 */
  opt = (int*)NclGetArgValue(
           2,
           3,
           NULL,
           NULL,
           NULL,
           NULL,
           NULL,
           2);

/*
 * Calculate size of leftmost dimensions.
 */
  size_output  = 1;
  ndims_leftmost = ndims_x-1;
  for(i = 0; i < ndims_leftmost; i++) {
    size_output *= dsizes_x[i];
  }

/*
 * The output type defaults to float, unless this input array is double.
 */
  type_xavg = NCL_float;

/* 
 * Allocate space for coercing input arrays.  If any of the input
 * is already double, then we don't need to allocate space for
 * temporary arrays, because we'll just change the pointer into
 * the void array appropriately.
 */
/*
 * Allocate space for tmp_x.
 */
  if(type_x != NCL_double) {
    tmp_x = (double *)calloc(nx,sizeof(double));
    if(tmp_x == NULL) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_avg_wgt: Unable to allocate memory for coercing input array to double");
      return(NhlFATAL);
    }
  }
  else {
    type_xavg = NCL_double;
  }
/*
 * Allocate space for tmp_w.
 */
  tmp_w = coerce_input_double(w,type_w,nx,0,NULL,NULL);
  if(tmp_w == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_avg_wgt: Unable to allocate memory for coercing input array to double");
    return(NhlFATAL);
  }

/* 
 * Allocate space for output array.
 */
  if(type_xavg != NCL_double) {
    xavg = (void *)calloc(size_output, sizeof(float));
  }
  else {
    xavg = (void *)calloc(size_output, sizeof(double));
  }
  if(xavg == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_avg_wgt: Unable to allocate memory for output array");
    return(NhlFATAL);
  }

/* 
 * Allocate space for output dimension sizes and set them.
 */
  ndims_xavg = max(ndims_leftmost,1);
  dsizes_xavg = (int*)calloc(ndims_xavg,sizeof(int));  
  if( dsizes_xavg == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_avg_wgt: Unable to allocate memory for holding dimension sizes");
    return(NhlFATAL);
  }
  if(ndims_leftmost > 0) {
    for(i = 0; i < ndims_leftmost; i++) dsizes_xavg[i] = dsizes_x[i];
  }
  else {
    dsizes_xavg[0] = 1;
  }

/*
 * Loop across leftmost dimensions and call the Fortran routine for each
 * one-dimensional subsection.
 */
  index_x = 0;

  for(i = 0; i < size_output; i++) {
/*
 * Coerce subsection of x (tmp_x) to double if necessary.
 */
    if(type_x != NCL_double) {
      coerce_subset_input_double(x,tmp_x,index_x,type_x,nx,0,NULL,NULL);
    }
    else {
      tmp_x = &((double*)x)[index_x];
    }

/*
 * Call the Fortran routine.
 */
    NGCALLF(dimavgwgt,DIMAVGWGT)(&nx, tmp_x, &missing_dbl_x.doubleval, 
				 tmp_w, opt, &tmp_xavg[0]);

/*
 * Coerce output back to float or double.
 */
    coerce_output_float_or_double(xavg,&tmp_xavg[0],type_x,1,i);

    index_x += nx;
  }

/*
 * Free unneeded memory.
 */
  if(type_x != NCL_double) NclFree(tmp_x);
  if(type_w != NCL_double) NclFree(tmp_w);

/*
 * Return value back to NCL script.
 */
  if(has_missing_x) {
    if(type_xavg == NCL_double) {
      return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,&missing_dbl_x,
			    type_xavg,0));
    }
    else {
      return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,&missing_flt_x,
			    type_xavg,0));
    }
  }
  else {
    return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,NULL,type_xavg,0));
  }
}

NhlErrorTypes dim_sum_wgt_W( void )
{

/*
 * Input variables
 */
/*
 * Argument # 0
 */
  void *x;
  double *tmp_x;
  int ndims_x, dsizes_x[NCL_MAX_DIMENSIONS];
  int has_missing_x;
  NclScalar missing_x, missing_flt_x, missing_dbl_x;
  NclBasicDataTypes type_x;

/*
 * Argument # 1
 */
  void *w;
  double *tmp_w;
  int dsizes_w[1];
  NclBasicDataTypes type_w;

/*
 * Argument # 2
 */
  int *opt;
/*
 * Return variable
 */
  void *xavg;
  double tmp_xavg[1];
  int ndims_xavg, *dsizes_xavg;
  NclBasicDataTypes type_xavg;
  NclScalar missing_xavg;

/*
 * Various
 */
  int nx, index_x;
  int i, ndims_leftmost, size_output;

/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value.
 */
/*
 * Get argument # 0
 */
  x = (void*)NclGetArgValue(
           0,
           3,
           &ndims_x,
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);

/*
 * Coerce missing value to double if necessary.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,
                 &missing_dbl_x,&missing_flt_x);

  nx = dsizes_x[ndims_x-1];
/*
 * Get argument # 1
 */
  w = (void*)NclGetArgValue(
           1,
           3,
           NULL,
           dsizes_w,
           NULL,
           NULL,
           &type_w,
           2);

  if(dsizes_w[0] != nx) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_sum_wgt: The rightmost argument of w must be length nx");
    return(NhlFATAL);
  }
/*
 * Get argument # 2
 */
  opt = (int*)NclGetArgValue(
           2,
           3,
           NULL,
           NULL,
           NULL,
           NULL,
           NULL,
           2);

/*
 * Calculate size of leftmost dimensions.
 */
  size_output  = 1;
  ndims_leftmost = ndims_x-1;
  for(i = 0; i < ndims_leftmost; i++) {
    size_output *= dsizes_x[i];
  }

/*
 * The output type defaults to float, unless this input array is double.
 */
  type_xavg = NCL_float;

/* 
 * Allocate space for coercing input arrays.  If any of the input
 * is already double, then we don't need to allocate space for
 * temporary arrays, because we'll just change the pointer into
 * the void array appropriately.
 */
/*
 * Allocate space for tmp_x.
 */
  if(type_x != NCL_double) {
    tmp_x = (double *)calloc(nx,sizeof(double));
    if(tmp_x == NULL) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_sum_wgt: Unable to allocate memory for coercing input array to double");
      return(NhlFATAL);
    }
  }
  else {
    type_xavg = NCL_double;
  }
/*
 * Allocate space for tmp_w.
 */
  tmp_w = coerce_input_double(w,type_w,nx,0,NULL,NULL);
  if(tmp_w == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_sum_wgt: Unable to allocate memory for coercing input array to double");
    return(NhlFATAL);
  }

/* 
 * Allocate space for output array.
 */
  if(type_xavg != NCL_double) {
    xavg = (void *)calloc(size_output, sizeof(float));
  }
  else {
    xavg = (void *)calloc(size_output, sizeof(double));
  }
  if(xavg == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_sum_wgt: Unable to allocate memory for output array");
    return(NhlFATAL);
  }

/* 
 * Allocate space for output dimension sizes and set them.
 */
  ndims_xavg = max(ndims_leftmost,1);
  dsizes_xavg = (int*)calloc(ndims_xavg,sizeof(int));  
  if( dsizes_xavg == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"dim_sum_wgt: Unable to allocate memory for holding dimension sizes");
    return(NhlFATAL);
  }
  if(ndims_leftmost > 0) {
    for(i = 0; i < ndims_leftmost; i++) dsizes_xavg[i] = dsizes_x[i];
  }
  else {
    dsizes_xavg[0] = 1;
  }

/*
 * Loop across leftmost dimensions and call the Fortran routine for each
 * one-dimensional subsection.
 */
  index_x = 0;

  for(i = 0; i < size_output; i++) {
/*
 * Coerce subsection of x (tmp_x) to double if necessary.
 */
    if(type_x != NCL_double) {
      coerce_subset_input_double(x,tmp_x,index_x,type_x,nx,0,NULL,NULL);
    }
    else {
      tmp_x = &((double*)x)[index_x];
    }

/*
 * Call the Fortran routine.
 */
    NGCALLF(dimsumwgt,DIMSUMWGT)(&nx, tmp_x, &missing_dbl_x.doubleval, 
				 tmp_w, opt, &tmp_xavg[0]);

/*
 * Coerce output back to float or double.
 */
    coerce_output_float_or_double(xavg,&tmp_xavg[0],type_x,1,i);

    index_x += nx;
  }

/*
 * Free unneeded memory.
 */
  if(type_x != NCL_double) NclFree(tmp_x);
  if(type_w != NCL_double) NclFree(tmp_w);

/*
 * Return value back to NCL script.
 */
  if(has_missing_x) {
    if(type_xavg == NCL_double) {
      return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,&missing_dbl_x,
			    type_xavg,0));
    }
    else {
      return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,&missing_flt_x,
			    type_xavg,0));
    }
  }
  else {
    return(NclReturnValue(xavg,ndims_xavg,dsizes_xavg,NULL,type_xavg,0));
  }
}
