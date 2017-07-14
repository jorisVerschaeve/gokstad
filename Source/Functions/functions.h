/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_FUNCTIONS_H
#define GOKSTAD_FUNCTIONS_H

namespace gokstad {

struct FunctionIndexingHelper2D
{
public:
  static int getDerivativeSize(int Dtot);
  static int getDerivativeIndex(int dx, int dy); 
}; 

template<typename U, typename T>
class Function1D
{
 public:
  virtual U evaluate(T x, int d) const = 0;
  virtual void evaluate(const T *const x, int n, U *const f, int d) const;
}; 

template<typename U, typename T>
class Function2D
{
 public:
  virtual U evaluate(T x, T y, int dx, int dy) const = 0;
  virtual void evaluate(const T *const x, 
			const T *const y, 
			int n, int dx, int dy,U *const f) const;
  //  virtual void evaluateTensorProduct(const T *const x, 
  //				     int nx,
  //				     const T *const y, 
  //				     int ny, 
  //				     int dx, int dy,U *const f) const;
  virtual void evaluateAllDerivatives(T x, T y, int Dtot, U *const f) const;
}; 

} // namespace gokstad

#endif
