/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_LINES_H
#define GOKSTAD_LINES_H

#include "../Functions/functions.h"
#include "../Functions/functions.hh"
#include "points.h"
#include "points.hh"

namespace gokstad {

  template<typename Point>
    class Line : 
    public Function1D<Point, typename bgGokstad::detail::param< Point >::type >
  {
  protected:
    typedef typename bgGokstad::detail::param< Point >::type T; 
  public:
    //// it is assumed that the line can be extended beyond [s0,s1]
    virtual void getParameterRange
      (typename bgGokstad::default_distance_result<Point,Point>::type & s0,
       typename bgGokstad::default_distance_result<Point,Point>::type & s1) const = 0;
    virtual Point evaluate(T x, int d) const = 0; 
    virtual void getBoundingBox(Point & x0, Point & x1 ) const = 0; 
    virtual Point pointOnLine(T x) const;
    virtual Point tangentialOnLine(T x) const;
    virtual bool isStraight() const; 
    //// when the lines partially or fully coincide, size of vector = 0
    /*
      virtual std::vector< std::pair<T,T> > 
      computeIntersections(const Line<U> *const line) const; 
      virtual std::vector< std::pair<T,T> > 
      computeIntersections(const Line<U> *const line, T sini) const; 
      virtual std::vector< std::pair<T,T> > 
      computeIntersections(const Line<U> *const line, T s0, T s1) const; 
      virtual std::vector< std::pair<T,T> > 
      computeClosestPoint(const Line<U> *const line) const; 
    */
  }; 

  template<typename Point>
    class Segment : public Line<Point>
    {
    public:
      /// two points define a segment
      Segment(Point x0, Point x1); 
      void getParameterRange
	(typename bgGokstad::default_distance_result<Point,Point>::type & s0,
	 typename bgGokstad::default_distance_result<Point,Point>::type & s1) const;
      //      virtual void getParameterRange(typename Line<Point>::T &  s0 , 
      //				     typename Line<Point>::T & s1 ) const; 
      virtual Point evaluate(typename Line<Point>::T x, int d) const; 
      virtual void getBoundingBox(Point & x0, Point & x1) const; 
      virtual bool isStraight() const; 
    private:
      typename Line<Point>::T l; 
      Point x0;
      Point vec; 
    }; 


} // namespace gokstad

#endif
