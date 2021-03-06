#ifdef CH_LANG_CC
/*
 *      _______              __
 *     / ___/ /  ___  __ _  / /  ___
 *    / /__/ _ \/ _ \/  V \/ _ \/ _ \
 *    \___/_//_/\___/_/_/_/_.__/\___/
 *    Please refer to Copyright.txt, in Chombo's root directory.
 */
#endif

#ifndef _SCALARFUNCTION_H_
#define _SCALARFUNCTION_H_

#include "REAL.H"
#include "RealVect.H"
#include "IntVect.H"
#include "NamespaceHeader.H"

//! \class ScalarFunction
//! This base class represents a scalar function \f$F: \mathbf{R}^D \rightarrow \mathbf{R}\f$.
class ScalarFunction
{
  public:

  //! Base class constructor. Must be called by subclasses.
  //! \param a_homogeneous This flag indicates whether the scalar function
  //!                      is constant in space.
  //! \param a_constant This flag indicates whether the scalar function
  //!                   is constant in time.
  ScalarFunction(bool a_homogeneous,
                 bool a_constant);

  //! Destructor.
  virtual ~ScalarFunction();

  //! Override this method to evaluate this function at the given
  //! point in space and time.
  //! \param a_x A point in \f$D\f$-dimensional space.
  //! \param a_t The time at which the function is to be evaluated.
  virtual Real operator()(const RealVect& a_x,
                          Real a_t) const = 0;

  //! Override this method to evaluate the given partial derivative of the
  //! function at the given point in space and time.
  //! \param a_order A multi-index identifying the order(s) of the
  //!                partial derivative of the function to be evaluated.
  //! \param a_x A point in \f$D\f$-dimensional space.
  //! \param a_t The time at which the derivative is to be evaluated.
  virtual Real derivative(const IntVect& a_order,
                          const RealVect& a_x,
                          Real a_t) const;

  //! Override this method to return true if the derivative of the
  //! requested order exists and is available, false if it is not.
  //! This must be implemented in a way that is consistent with the
  //! derivative method.
  //! \param a_order A multi-index identifying the order(s) of the
  //!                desired partial derivative of the function.
  virtual bool hasDerivative(const IntVect& a_order) const;

  //! This evaluates the function at time 0.
  //! \param a_x A point in \f$D\f$-dimensional space.
  Real operator()(const RealVect& a_x) const
  {
    return operator()(a_x, 0.0);
  }

  //! This evaluates the given partial derivative of the function at time 0.
  //! \param a_order A multi-index identifying the order(s) of the
  //!                partial derivative of the function to be evaluated.
  //! \param a_x A point in \f$D\f$-dimensional space.
  Real derivative(const IntVect& a_order,
                  const RealVect& a_x) const
  {
    return derivative(a_order, a_x, 0.0);
  }

  //! Returns true if this function is homogeneous, false otherwise.
  bool isHomogeneous() const
  {
    return m_isHomogeneous;
  }

  //! Returns true if this function is constant, false otherwise.
  bool isConstant() const
  {
    return m_isConstant;
  }

  protected:

  bool m_isHomogeneous, m_isConstant;

  private:

  // Disallowed!
  ScalarFunction();
  ScalarFunction(const ScalarFunction&);
  ScalarFunction& operator=(const ScalarFunction&);
};

#include "NamespaceFooter.H"
#endif
