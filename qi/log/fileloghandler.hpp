/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#pragma once
#ifndef _LIBQI_QI_LOG_FILELOGHANDLER_HPP_
#define _LIBQI_QI_LOG_FILELOGHANDLER_HPP_

# include <qi/log.hpp>
# include <string>

namespace qi {
  namespace log {
    class PrivateFileLogHandler;

    /// Log messages to a file.
    class QI_API FileLogHandler
    {
    public:
      /// \brief Initialize the file handler on the file. File is opened
      ///        directly on construction.
      explicit FileLogHandler(const std::string& filePath);

      /// Closes the file.
      virtual ~FileLogHandler();

      /// Writes a log message to the file.
      void log(const qi::log::LogLevel verb,
               const qi::os::timeval   date,
               const char              *category,
               const char              *msg,
               const char              *file,
               const char              *fct,
               const int               line);

    private:
      QI_DISALLOW_COPY_AND_ASSIGN(FileLogHandler);
      PrivateFileLogHandler* _private;
    }; // !FileLogHandler

  }; // !log
}; // !qi

#endif  // _LIBQI_QI_LOG_FILELOGHANDLER_HPP_
