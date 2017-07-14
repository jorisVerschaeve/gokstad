/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_POINTS_HH
#define GOKSTAD_POINTS_HH

#include "points.h"

namespace gokstad {

  /////////////////////operator*////////////////////////////

  template<typename Point, int I, int Count>
  struct multiplyCoordinate
  {
    static inline void apply(Point & p, 
			     typename bgGokstad::detail::param< Point >::type value) 
    {
      bgGokstad::set<I>(p,bgGokstad::get<I>(p)*value); 
      multiplyCoordinate<Point,I+1,Count>::apply(p,value); 
    }
  }; 

  template<typename Point, int Count>
  struct multiplyCoordinate<Point,Count,Count>
  {
    static inline void apply(Point & p, 
			     typename bgGokstad::detail::param< Point >::type value) 
    { }
  }; 

  template<typename Point>
  Point multiply(const Point & p,
		 typename bgGokstad::detail::param< Point >::type value) 
  {
    Point q(p); 
    multiplyCoordinate<Point,0,bgGokstad::dimension<Point>::type::value>::
      apply(q,value);
    return q; 
  }

  /*
  template<typename Point>
  Point operator*(const Point & p, 
		  typename bgGokstad::detail::param< Point >::type value) 
  {
    return multiply(p,value);
  }

  template<typename Point>
  Point operator/(const Point & p, typename bgGokstad::detail::param< Point >::type value) 
  {
    typename bgGokstad::detail::param< Point >::type value0(1);
    return multiply(p,value0/value); 
  }
  */

  Point2D operator/(const Point2D & p, double value) 
  {
    return multiply(p,1./value); 
  }

  Point2D operator*(const Point2D & p, double value) 
  {
    return multiply(p,value); 
  }

  Point2D operator*(double value, const Point2D & p) 
  {
    return multiply(p,value); 
  }

  template<typename Point, int I, int Count>
  struct sumCoordinate
  {
    static inline void apply(Point & q, Point const& p)
    {
      bgGokstad::set<I>(q,bgGokstad::get<I>(q)+bgGokstad::get<I>(p));
      sumCoordinate<Point,I+1,Count>::apply(q,p); 
    }
  };

  template<typename Point, int Count>
  struct sumCoordinate<Point,Count,Count>
  {
    static inline void apply(Point & q, Point const& p)
    {}
  }; 

  template<typename Point>
  Point sum(const Point & q, const Point & p) 
  {
    Point r(q); 
    sumCoordinate<Point,0,bgGokstad::dimension<Point>::type::value>::
      apply(r,p);
    return r; 
  }
  /*
  template<typename Point>
  Point operator+(const Point & q, const Point & p) 
  {
    return sum(q,p); 
  }
  */
  //  template<>
  Point2D operator+(const Point2D & q, const Point2D & p) 
  {
    return sum(q,p); 
  }

  //////////////////////subtract//////////////////////////////////

  template<typename Point, int I, int Count>
  struct subtractCoordinate
  {
    static inline void apply(Point & q, Point const& p)
    {
      bgGokstad::set<I>(q,bgGokstad::get<I>(q)-bgGokstad::get<I>(p));
      subtractCoordinate<Point,I+1,Count>::apply(q,p); 
    }
  };

  template<typename Point, int Count>
  struct subtractCoordinate<Point,Count,Count>
  {
    static inline void apply(Point & q, Point const& p)
    {}
  }; 

  template<typename Point>
  Point subtract(const Point & q, const Point & p) 
  {
    Point r(q); 
    subtractCoordinate<Point,0,bgGokstad::dimension<Point>::type::value>::
      apply(r,p);
    return r; 
  }

  Point2D operator-(const Point2D & q, const Point2D & p) 
  {
    return subtract(q,p); 
  }

  ////////////////////////setPointValue/////////////////////////////////

  template<typename Point, int I, int Count>
  struct setCoordinateValue
  {
    static inline void apply(Point & p, typename bgGokstad::detail::param< Point >::type value)
    {
      bgGokstad::set<I>(p,value); 
      setCoordinateValue<Point,I+1,Count>::apply(p,value); 
    }
  }; 

  template<typename Point, int Count>
  struct setCoordinateValue<Point,Count,Count>
  {
    static inline void apply(Point & p, typename bgGokstad::detail::param< Point >::type value)
    {}
  }; 

  template<typename Point>
  void setPointValue(Point & p, typename bgGokstad::detail::param< Point >::type value)
  {
    setCoordinateValue<Point,0,bgGokstad::dimension<Point>::type::value>::apply(p,value);  
  }

  template<typename Point>
  typename bgGokstad::default_distance_result<Point,Point>::type distance(Point const& p, Point const& q)
  {
    return bgGokstad::distance(p,q); 
  }


  template<typename Point>
  typename bgGokstad::default_distance_result<Point,Point>::type length(Point const& q)
  {
    Point orig;
    typename bgGokstad::detail::param< Point >::type value(0); 
    setPointValue(orig,value); 
    return bgGokstad::distance(q,orig); 
  }

  /////////////////////////////operator<</////////////////////////////////
  
  template<typename Point, int I, int Count>
  struct nextCoordinate
  {
    static inline void apply(std::ostream & os, Point const& p)
    {
      double x = bgGokstad::get<I>(p);
      os << x << " "; 
      nextCoordinate<Point,I+1,Count>::apply(os,p); 
    }
  }; 

  template<typename Point, int Count>
  struct nextCoordinate<Point,Count,Count>
  {
    static inline void apply(std::ostream & os, Point const& p)
    {}
  }; 

  template<typename Point>
  void display(std::ostream& os, Point const& p)
  {
    nextCoordinate<Point,0,bgGokstad::dimension<Point>::type::value>::apply(os,p); 
  }

  std::ostream& operator<<(std::ostream& os, Point2D const& p)
  {
    display(os,p); 
    return os; 
  }

} // namespace gokstad

#endif
