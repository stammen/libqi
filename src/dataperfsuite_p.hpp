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

    //! The type of output.
    DataPerfSuite::OutputType outputType;

    //! Name of the project.
    std::string projectName;

    //! Name of the executable.
    std::string executableName;

    //! Give the stream where output.
    /**
     * Always use that as out may not be open.
     * If the file is closed getOut return std::cout.
     */
    std::ostream& getOut();

    //! Give the stream to output normal.
    /**
     * The normal way is always output.
     * If user ask for normal_way it is output to getOut().
     * Otherwise it is output to std::cout
     */
    std::ostream& getNormalOut();
  };
}

#endif  // _QI_PERF_DATAPERFSUITE_P_HPP_
