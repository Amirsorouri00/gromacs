/*
 * This source file is part of the Alexandria program.
 *
 * Copyright (C) 2014-2019
 *
 * Developers:
 *             Mohammad Mehdi Ghahremanpour,
 *             Paul J. van Maaren,
 *             David van der Spoel (Project leader)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*! \internal \brief
 * Implements part of the alexandria program.
 * \author Mohammad Mehdi Ghahremanpour <mohammad.ghahremanpour@icm.uu.se>
 * \author David van der Spoel <david.vanderspoel@icm.uu.se>
 */

#include "gmxpre.h"

#include "composition.h"

namespace alexandria
{

CompositionSpecs::CompositionSpecs()
{
    cs_.push_back(CompositionSpec(iCalexandria, (const char *)"Alexandria", (const char *)"Spoel2016a", (const char *)"AX"));
    cs_.push_back(CompositionSpec(iCbosque, (const char *)"Bosque", (const char *)"Bosque2002a", (const char *)"BS"));
    cs_.push_back(CompositionSpec(iCmiller, (const char *)"Miller", (const char *)"Miller1990a", (const char *)"MK"));
}

}
