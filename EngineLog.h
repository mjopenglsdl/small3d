/*
*  EngineLog.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#pragma once

/**
* Logging is accessed through macros so that it can be completely
* omitted if deactivated.
*/

#define LOGERROR(MESSAGE) log->append(error, MESSAGE)

#define LOGINFO(MESSAGE) log->append(info, MESSAGE)

#if defined(DEBUG) || defined(_DEBUG)
#define LOGDEBUG(MESSAGE) log->append(debug, MESSAGE)
#else
#define LOGDEBUG(MESSAGE)
#endif

#include <ostream>

using namespace std;


namespace small3d {

	/**
	* @enum	EngineLogLevel
	*
	* @brief	Possible logging levels.
	*/

	enum EngineLogLevel {
		info, debug, error
	};

	/**
	* @class	EngineLog
	*
	* @brief	The standard logging class for small3d.
	*
	*/

	class EngineLog {
	private:
		ostream *logStream;
	public:

		/**
		* @fn	EngineLog::EngineLog(ostream &stream);
		*
		* @brief	Constructor with stream for output.
		*
		*
		* @param [in,out]	stream	The stream to which events will be logged.
		*/

		EngineLog(ostream &stream);

		/**
		* @fn	EngineLog::~EngineLog();
		*
		* @brief	Destructor.
		*
		*/

		~EngineLog();

		/**
		* @fn	void EngineLog::append(const EngineLogLevel level, const string message);
		*
		* @brief	Appends a message to the log.
		*
		* @param	level  	The logging level (debug, info, etc).
		* @param	message	The message.
		*/

		void append(const EngineLogLevel level, const string message);
	};
}

