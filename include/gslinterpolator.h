#ifndef GAUSS2D_FIT_GSLINTERPOLATOR_H
#define GAUSS2D_FIT_GSLINTERPOLATOR_H

#ifdef GAUSS2D_FIT_HAS_GSL

#include "gsl.h"
#include "interpolation.h"

#include "gauss2d/object.h"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

namespace gauss2d::fit {

/**
 * A wrapper for GSL 1D interpolators.
 */
class GSLInterpolator : public Object {
private:
    gsl_interp_accel * _acc;
    gsl_spline * _spline;
    size_t _n_knots;
    std::vector<double> _x;
    std::vector<double> _y;

public:
    const InterpType interp_type;
    static constexpr InterpType INTERPTYPE_DEFAULT = InterpType::cspline;

    /// Get the interpolant value for a knot of the given index
    double get_knot_x(size_t idx) const;
    /// Get the interpolated function value for a knot of the given index
    double get_knot_y(size_t idx) const;

    /// Get the interpolated function value for a given interpolant value
    double eval(double x) const;
    /// Get the derivative of the interpolated function value for a given interpolant value
    double eval_deriv(double x) const;
    /// Get the number of knots
    size_t size() const;

    std::string repr(bool name_keywords = false) const override;
    std::string str() const override;

    explicit GSLInterpolator(
        std::vector<double> x, std::vector<double> y,
        InterpType interp_type = INTERPTYPE_DEFAULT);
    ~GSLInterpolator();
};

}  // namespace gauss2d::fit

#endif // GAUSS2D_FIT_HAS_GSL
#endif // GAUSS2D_FIT_GSLINTERPOLATOR_H