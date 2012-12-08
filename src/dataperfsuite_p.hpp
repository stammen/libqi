/*
** Author(s):
**  - Nicolas Cornu <ncornu@aldebaran-robotics.com>
**
** Copyright (C) 2012 Aldebaran Robotics
*/

#pragma once
#ifndef _QI_PERF_DATAPERFSUITE_P_HPP_
#define _QI_PERF_DATAPERFSUITE_P_HPP_

#include <qiperf/dataperfsuite.hpp>

#include <fstream>
#include <iostream>

namespace qi
{
  class DataPerfSuitePrivate
  {
  public:
    //! The file where output is written.
    /**
     * If this file is not open (bool std::ofstream::is_open()) output in std::cout.
     */
    std::ofstream out;

    DataPerfSuite::OutputData outputData;

    //! Name of the project.
    std::string projectName;

    //! Name of the executable.
    std::string executableName;
  };
}

#endif  // _QI_PERF_DATAPERFSUITE_P_HPP_
