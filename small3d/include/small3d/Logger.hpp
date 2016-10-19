/*
 *  Logger.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

/**
 * Logging is accessed through macros so that it can be completely
 * omitted if deactivated.
 */

#define LOGERROR(MESSAGE) logger->append(loggererror, MESSAGE)

#define LOGINFO(MESSAGE) logger->append(loggerinfo, MESSAGE)

#if defined(DEBUG) || defined(_DEBUG)
#define LOGDEBUG(MESSAGE) logger->append(debug, MESSAGE)
#else
#define LOGDEBUG(MESSAGE)
#endif

#include <ostream>
#include <memory>

using namespace std;


namespace small3d {

  /**
   * @brief Possible logging levels.
   */

  enum LogLevel {
    loggerinfo, loggerdebug, loggererror
  };

  /**
   * @class Logger
   * @brief The standard logging class for small3d.
   */

  class Logger {
  private:
    ostream *logStream;
  public:

    /**
     * @brief Constructor with stream for output.
     *
     * @param [in,out]	stream	The stream to which events will be logged.
     */

    Logger(ostream &stream);

    /**
     * @brief Destructor.
     */

    ~Logger();

    /**
     * @brief Appends a message to the logger.
     *
     * @param	level  	The logging level (debug, info, etc).
     * @param	message	The message.
     */

    void append(const LogLevel level, const string &message);
  };

  void initLogger();

  void initLogger(ostream &stream);

  void deleteLogger();
}

extern shared_ptr<small3d::Logger> logger;
