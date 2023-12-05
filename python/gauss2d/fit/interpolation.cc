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

#include <pybind11/attr.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pybind11.h"

#include "gauss2d/fit/interpolation.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace g2f = gauss2d::fit;

void bind_interpolation(py::module &m) {
    auto _e = py::enum_<g2f::InterpType>(m, "InterpType")
                      .value("linear", g2f::InterpType::linear)
                      .value("polynomial", g2f::InterpType::polynomial)
                      .value("cspline", g2f::InterpType::cspline)
                      .value("akima", g2f::InterpType::akima)
    ;
}