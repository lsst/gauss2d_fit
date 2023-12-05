/*
 * This file is part of gauss2dfit.
 *
 * Developed for the LSST Data Management System.
 * This product includes software developed by the LSST Project
 * (https://www.lsst.org).
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef GAUSS2D_FIT_HAS_GSL

#include <pybind11/attr.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <memory>

#include "pybind11.h"

#include "gauss2d/fit/gsl.h"
#include "gauss2d/fit/gslinterpolator.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace g2f = gauss2d::fit;

void bind_gslsersicmixinterpolator(py::module &m) {
    auto _e = py::class_<g2f::GSLSersicMixInterpolator, std::shared_ptr<g2f::GSLSersicMixInterpolator>,
                         g2f::SersicMixInterpolator>(m, "GSLSersicMixInterpolator")
                      .def(py::init<short, const g2f::GSLInterpType>(),
                           "order"_a = g2f::SERSICMIX_ORDER_DEFAULT,
                           "interp_type"_a = g2f::GSLInterpType::cspline)
                      .def_readwrite("correct_final_integral",
                                     &g2f::GSLSersicMixInterpolator::correct_final_integral)
                      .def_property_readonly("final_correction",
                                             &g2f::GSLSersicMixInterpolator::get_final_correction)
                      .def("integralsizes", &g2f::GSLSersicMixInterpolator::get_integralsizes)
                      .def("integralsizes_derivs",
                           &g2f::GSLSersicMixInterpolator::get_integralsizes_derivs)
                      .def_property_readonly("interp_type", &g2f::GSLSersicMixInterpolator::interp_type)
                      .def_property_readonly("order", &g2f::GSLSersicMixInterpolator::get_order)
                      .def("__repr__",
                           [](const g2f::GSLSersicMixInterpolator &self) { return self.repr(true); })
                      .def("__str__", &g2f::GSLSersicMixInterpolator::str);
}

#endif  // GAUSS2D_FIT_HAS_GSL
