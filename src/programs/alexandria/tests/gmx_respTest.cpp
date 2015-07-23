/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 2014,2015, by the GROMACS development team, led by
 * Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
 * and including many others, as listed in the AUTHORS file in the
 * top-level source directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */
/*! \internal \file
 * \brief
 * Implements test of autocorrelation function routines
 *
 * \author Anders G&auml;rden&auml;s <anders.gardenas@gmail.com>
 * \author David van der Spoel <david.vanderspoel@icm.uu.se>
 * \ingroup module_correlationfunctions
 */
//#include "gmxpre.h"

#include <math.h>
#include <gtest/gtest.h>

#include "testutils/refdata.h"
#include "testutils/testasserts.h"
#include "testutils/testfilemanager.h"

#include "programs/alexandria/gmx_resp.h"


class RespTest : public ::testing::Test
{

  //using gmx::test::TestReferenceData;
protected:
  gmx::test::TestReferenceData                     refData_;
  gmx::test::TestReferenceChecker                  checker_;
  static alexandria::Resp resp;

  //init sett tolecrance
  RespTest ( )
    :refData_(gmx::test::erefdataCreateMissing), checker_(refData_.rootChecker())
  {
#ifdef GMX_DOUBLE
    checker_.setDefaultTolerance(gmx::test::relativeToleranceAsFloatingPoint(1, 1e-6));
#else
    checker_.setDefaultTolerance(gmx::test::relativeToleranceAsFloatingPoint(1, 1e-3));
#endif
  }

  // Static initiation, only run once every test.
  static void SetUpTestCase()
  {
    //    resp = new resp()
  }


  void setUp(){


  }
  static void TearDownTestCase()
  {
  }


  void test()
  {
  }
};





TEST_F (RespTest, test)
{
  test();
}
