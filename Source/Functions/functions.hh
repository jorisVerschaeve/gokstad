/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_FUNCTIONS_HH
#define GOKSTAD_FUNCTIONS_HH

namespace gokstad {

  //////////////////////FunctionIndexingHelper////////////////////////

  int FunctionIndexingHelper2D::getDerivativeSize(int Dtot)
  {
    return (Dtot+1)*(Dtot+2)/2; 
  }

  int FunctionIndexingHelper2D::getDerivativeIndex(int dx, int dy)
  {
    int Dtot = dx+dy;
    return (Dtot+1)*(Dtot+2)/2 - Dtot + dy - 1;
  }

  ///////////////////////Function1D///////////////////////////////////

template<typename U, typename T>
void Function1D<U,T>::evaluate(const T *const x, int n, U *const f, int d) const
{
  for(int i = 0; i < n ; ++i){
    f[i] = this->evaluate(x[i],d); 
  }
}

  ///////////////////////Function2D///////////////////////////////////

template<typename U, typename T>
void Function2D<U,T>::
evaluate(const T *const x, const T *const y, 
	 int n, int dx, int dy,U *const f) const
{
  for(int i = 0; i < n ; ++i){
    f[i] = this->evaluate(x[i],y[i],dx,dy); 
  }
}

template<typename U, typename T>
void Function2D<U,T>::
evaluateAllDerivatives(T x, T y, int Dtot, U *const f) const
{
  /// f[DerivativeSize(Dtot)]
  for(int d = 0; d <= Dtot ; ++d){ 
    for(int dx = 0; dx <= d ; ++dx){
      for(int dy = d-dx; dy >= 0 ; --dy){
	f[FunctionIndexingHelper2D::getDerivativeIndex(dx,dy)] =
	  this->evaluate(x,y,dx,dy); 
      }
    }
  }
}

} // namespace gokstad

#endif
