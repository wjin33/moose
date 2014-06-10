/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

//  "cut" van-Genuchten effective saturation as a function of single pressure, and its derivs wrt to that pressure
//
#ifndef RICHARDSSEFF1VGCUT_H
#define RICHARDSSEFF1VGCUT_H

#include "RichardsSeff1VG.h"

class RichardsSeff1VGcut;


template<>
InputParameters validParams<RichardsSeff1VGcut>();

/**
 * Effective saturation as a function of porepressure
 * using the van Genuchten formula, but when p<p_cut use a
 * linear instead, seff = a + b*p, which matches value and derivative at p=p_cut
 * This is so seff=0 at a finite value of p rather than p=-infinity.
 * Note effective saturation is not a function
 * of capillary pressure: i use porepressure instead, so
 * seff = 1 for p >= 0.
 */
class RichardsSeff1VGcut : public RichardsSeff1VG
{
 public:
  RichardsSeff1VGcut(const std::string & name, InputParameters parameters);

  /// just prints some (maybe) useful info to the console
  void initialSetup();

  /**
   * effective saturation as a function of porepressure
   * @param p porepressure in the element.  Note that (*p[0])[qp] is the porepressure at quadpoint qp
   * @param qp the quad point to evaluate effective saturation at
   */
  Real seff(std::vector<VariableValue *> p, unsigned int qp) const;

  /**
   * derivative of effective saturation wrt porepressure
   * @param p porepressure in the element.  Note that (*p[0])[qp] is the porepressure at quadpoint qp
   * @param qp the quad point to evaluate effective saturation at
   */
  std::vector<Real> dseff(std::vector<VariableValue *> p, unsigned int qp) const;

  /**
   * second derivative of effective saturation wrt porepressure
   * @param p porepressure in the element.  Note that (*p[0])[qp] is the porepressure at quadpoint qp
   * @param qp the quad point to evaluate effective saturation at
   */
  std::vector<std::vector<Real> > d2seff(std::vector<VariableValue *> p, unsigned int qp) const;

 protected:

  /// van Genuchten alpha parameter
  Real _al;

  /// van Genuchten m parameter
  Real _m;

  /// cutoff in pressure below which use a linear relationship instead of van-Genuchten expression.  _p_cut < 0
  Real _p_cut;

  /// effective saturation at p=_p_cut
  Real _s_cut;

  /// derivative of effective saturation wrt p at p=_p_cut
  Real _ds_cut;


};

#endif // RICHARDSSEFF1VGCUT_H
