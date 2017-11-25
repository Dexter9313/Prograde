/*
    Copyright (C) 2016 Florian Cabot

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <gsl/gsl_const.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_nan.h>

/*! \ingroup math
 * Contains all mathematical and physical constants
 */
namespace constant
{
/*! [Pi](https://en.wikipedia.org/wiki/Pi)
 */
static const double pi = M_PI;

/*! [Gravitationnal
 * constant](https://en.wikipedia.org/wiki/Gravitational_constant)
 */
static const double G = GSL_CONST_MKSA_GRAVITATIONAL_CONSTANT;

/*! [Not a number](https://en.wikipedia.org/wiki/NaN), result of invalid
 * mathematical operations
 */
static const double NaN = GSL_NAN;
}

#endif // CONSTANTS_H
