/*
 * This file is part of gauss2d_fit.
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

#include <pybind11/attr.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <memory>
#include <string>

#include "lsst/gauss2d/ellipse.h"
#include "lsst/gauss2d/fit/ellipticalcomponent.h"
#include "lsst/gauss2d/fit/parametric.h"
#include "pybind11.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace g2f = lsst::gauss2d::fit;

void bind_ellipticalcomponent(py::module &m) {
    auto _e = py::class_<g2f::EllipticalComponent, std::shared_ptr<g2f::EllipticalComponent>, g2f::Component>(
                      m, "EllipticalComponent")
                      .def_property_readonly("centroid", &g2f::EllipticalComponent::get_centroid)
                      .def_property_readonly("ellipse", &g2f::EllipticalComponent::get_ellipse)
                      .def_property_readonly("integralmodel", &g2f::EllipticalComponent::get_integralmodel);
}
