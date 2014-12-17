/*
 *  Logger.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Logger.h"
#include <sstream>
#include <ctime>
#include <iostream>

using namespace std;

shared_ptr<small3d::Logger> logger;

namespace small3d {

  Logger::Logger(ostream &stream) {
    logStream = &stream;
  }

  Logger::~Logger() {
    this->append(info, "Logger getting destroyed");

  }

  void Logger::append(const LogLevel &level, const string &message) {

    ostringstream dateTimeOstringstream;

    time_t now;

    time(&now);

    tm *t;

#if defined(_WIN32) && !defined(__MINGW32__)
    t = new tm();
    localtime_s(t, &now);

#else
    t = localtime(&now);
#endif
    char buf[20];

    strftime(buf, 20,"%Y-%m-%d %H:%M:%S", t);

    // localtime (used on Linux) does not allocate memory, but
    // returns a pointer to a pre-existing location. Hence,
    // we should not delete it.
#ifdef _WIN32
    delete t;
#endif

    dateTimeOstringstream << buf;

    string indicator;
    switch (level) {
    case info:
      indicator = "INFO";
      break;
    case debug:
      indicator = "DEBUG";
      break;
    case error:
      indicator = "ERROR";
      break;
    default:
      indicator = "";
      break;
    }

    *logStream << dateTimeOstringstream.str().c_str() << " - " << indicator << ": " << message.c_str() << endl;
  }

  void initLogger() {
    if (!logger) logger = shared_ptr<Logger>(new Logger(cout));
  }

  void initLogger(ostream &stream) {
    if (!logger) logger = shared_ptr<Logger>(new Logger(stream));
  }
} 
