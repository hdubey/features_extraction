#define TYPEDEPARGS 0, 1
#define SINGLEARGS
#define COMPLEXARGS
#define OCTFILENAME comp_idgt_fac // change to filename
#define OCTFILEHELP "This function calls the C-library\n\
                     c=comp_idgt_fac(c,gf,L,a,M);\n\
                     Yeah.\n"


#include "ltfat_oct_template_helper.h"
// octave_idx_type is 32 or 64 bit signed integer

static inline void fwd_idgt_fac(const Complex *coef, const Complex *gf,
                              const octave_idx_type L, const octave_idx_type W,
							  const octave_idx_type a, const octave_idx_type M,
							  Complex *f)
{
   idgt_fac_d(reinterpret_cast<const double _Complex*>(coef),
              reinterpret_cast<const double _Complex*>(gf),
              L,W,a,M,
			  reinterpret_cast<double _Complex*>(f));
}

static inline void fwd_idgt_fac(const FloatComplex *coef, const FloatComplex *gf,
                              const octave_idx_type L, const octave_idx_type W, 
							  const octave_idx_type a, const octave_idx_type M,
							  FloatComplex *f)
{
   idgt_fac_s(reinterpret_cast<const float _Complex*>(coef),
              reinterpret_cast<const float _Complex*>(gf),
              L,W,a,M,
			  reinterpret_cast<float _Complex*>(f));
}

template <class LTFAT_TYPE, class LTFAT_REAL, class LTFAT_COMPLEX>
octave_value_list octFunction(const octave_value_list& args, int nargout)
{
     DEBUGINFO;
	 
	 MArray<LTFAT_TYPE> coef = ltfatOctArray<LTFAT_TYPE>(args(0));
	 MArray<LTFAT_TYPE> gf = ltfatOctArray<LTFAT_TYPE>(args(1));
	 const octave_idx_type L = args(2).int_value();
     const octave_idx_type a = args(3).int_value();
     const octave_idx_type M = args(4).int_value();
     const octave_idx_type N = L/a;
     const octave_idx_type W = coef.rows()*coef.columns()/(M*N);


     MArray<LTFAT_COMPLEX> f(dim_vector(L,W)); 
     f.fill(0);
	 
	 fwd_idgt_fac(coef.data(),gf.data(),L,W,a,M,f.fortran_vec());
	 
     return octave_value(f);
}
/*
#include <octave/oct.h>
#include "config.h"
#include "ltfat.h"

DEFUN_DLD (comp_idgt_fac, args, ,
  "This function calls the C-library\n\
  c=comp_idgt_fac(c,gf,L,a,M);\n\
  Yeah.\n")
{

  const ComplexMatrix coef = args(0).complex_matrix_value();
  const ComplexMatrix gf = args(1).complex_matrix_value();
  const int L = args(2).int_value();
  const int a = args(3).int_value();
  const int M = args(4).int_value();
  const int N = L/a;
  const int W = coef.rows()*coef.columns()/(M*N);

  ComplexMatrix f(L,W);  
  
  idgt_fac((ltfat_complex*)coef.data(),(ltfat_complex*)gf.data(),L,W,a,M,
	  (ltfat_complex*)f.data());

  return octave_value (f);
}
*/
