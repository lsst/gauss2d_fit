#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "lsst/gauss2d/to_string.h"
#include "lsst/gauss2d/type_name.h"

#include "lsst/gauss2d/fit/linearsersicmixinterpolator.h"

namespace lsst::gauss2d::fit {

std::vector<IntegralSize> LinearSersicMixInterpolator::get_integralsizes(double sersicindex) const {
    if (!((sersicindex >= sersicindex_min) && (sersicindex <= sersicindex_max))) {
        throw std::invalid_argument("sersicindex=" + to_string_float(sersicindex)
                                    + " !(>=" + to_string_float(sersicindex_min)
                                    + "&& <=" + to_string_float(sersicindex_max));
    }

    if (sersicindex == sersicindex_min)
        return knots[0].values;
    else if (sersicindex == sersicindex_max)
        return knots.back().values;

    auto found = std::lower_bound(knots.begin(), knots.end(), sersicindex);
    auto high = *found;
    auto low = *(--found);

    if (sersicindex == high.sersicindex) return high.values;
    double frac_low = (high.sersicindex - sersicindex) / (high.sersicindex - low.sersicindex);
    if (!((frac_low >= 0) && (frac_low <= 1))) {
        throw std::logic_error("Got invalid frac_low=" + std::to_string(frac_low)
                               + " with n, lo, hi=" + to_string_float(sersicindex) + ","
                               + to_string_float(low.sersicindex) + "," + to_string_float(high.sersicindex));
    }
    double frac_high = 1 - frac_low;

    std::vector<IntegralSize> result;
    result.reserve(_order);
    for (size_t i = 0; i < _order; ++i) {
        result.push_back({frac_low * low.values[i].integral + frac_high * high.values[i].integral,
                          frac_low * low.values[i].sigma + frac_high * high.values[i].sigma});
    }

    return result;
}

std::vector<IntegralSize> LinearSersicMixInterpolator::get_integralsizes_derivs(double sersicindex) const {
    if (!((sersicindex >= sersicindex_min) && (sersicindex <= sersicindex_max))) {
        throw std::invalid_argument("sersicindex=" + to_string_float(sersicindex)
                                    + " !(>=" + to_string_float(sersicindex_min)
                                    + "&& <=" + to_string_float(sersicindex_max));
    }

    auto found = sersicindex == sersicindex_min
                         ? ++knots.begin()
                         : ((sersicindex == sersicindex_max)
                                    ? --knots.end()
                                    : std::upper_bound(knots.begin(), knots.end(), sersicindex));
    auto& high = *found;
    auto& low = *(--found);

    double dn_inv = 1. / (high.sersicindex - low.sersicindex);

    std::vector<IntegralSize> result;
    result.reserve(_order);
    for (size_t i = 0; i < _order; ++i) {
        result.push_back({(high.values[i].integral - low.values[i].integral) * dn_inv,
                          (high.values[i].sigma - low.values[i].sigma) * dn_inv});
    }

    return result;
}

InterpType LinearSersicMixInterpolator::get_interptype() const { return InterpType::linear; }

unsigned short LinearSersicMixInterpolator::get_order() const { return _order; }

std::string LinearSersicMixInterpolator::repr(bool name_keywords,
                                              std::string_view namespace_separator) const {
    return type_name_str<LinearSersicMixInterpolator>(false, namespace_separator) + "("
           + (name_keywords ? "order=" : "") + std::to_string(_order) + ")";
}

std::string LinearSersicMixInterpolator::str() const {
    return type_name_str<LinearSersicMixInterpolator>(true) + "(order=" + std::to_string(_order) + ")";
}

LinearSersicMixInterpolator::LinearSersicMixInterpolator(unsigned short order)
        : _order(order),
          knots(get_sersic_mix_knots(order)),
          sersicindex_min(knots[0].sersicindex),
          sersicindex_max(knots.back().sersicindex) {}

LinearSersicMixInterpolator::~LinearSersicMixInterpolator(){};

}  // namespace lsst::gauss2d::fit
