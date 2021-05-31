/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"
#include <cstdlib>
#include <fstream>
#include "TLibCommon/TComDataCU.h"

//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"

// ====================================================================================================================
// Main function
// ====================================================================================================================

Int** samplesMatrix;
IntraData m64[mSizeY][mSizeX];
IntraData m32[mSizeY][mSizeX];
IntraData m16[mSizeY][mSizeX];
IntraData m8[mSizeY][mSizeX];
IntraData m4[mSizeY][mSizeX];
ofstream intraDataFile;

int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;

  intraDataFile.open("intraDataFile.csv");
  intraDataFile << "Frame,PosY,PosX,Size,BestMode,BestModeCost,Variance,coCost,AboveCost,LeftCost,AboveLeftCost,AboveRightCost,"
                     "MPM1,MPM2,MPM3,RMD1,RMD2,RMD3,RMD4,RMD5,RMD6,RMD7,RMD8,Cost0,Cost1,Cost2,Cost3,Cost4,Cost5,Cost6,Cost7,Cost8,"
                     "Cost9,Cost10,Cost11,Cost12,Cost13,Cost14,Cost15,Cost16,Cost17,Cost18,Cost19,Cost20,Cost21,Cost22,Cost23,"
                     "Cost24,Cost25,Cost26,Cost27,Cost28,Cost29,Cost30,Cost31,Cost32,Cost33,Cost34" << endl;

    // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );

  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

  // starting time
  Double dResult;
  clock_t lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);

  // destroy application encoder class
  cTAppEncTop.destroy();

  intraDataFile.close();

  return 0;
}

//! \}
