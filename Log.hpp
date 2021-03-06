#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <memory>

using std::shared_ptr;
using std::string;
using std::map;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::chrono::system_clock;

namespace bf {
	class Log {
		public:
			enum class Target : short {
				DISABLED = 1,
				STDOUT = 2,
				STDERR = 4,
				LOG_FILE = 8
			};

			enum class Level : short {
				DEBUG = 1,
				INFO = 2,
				NOTICE = 3,
				WARNING = 4,
				ERR = 5,
				CRIT = 6,
				ALERT = 7,
				EMERG = 8
			};

			/**
			 * Get singleton instance.
			 *
			 * \return	Log*	Pointer to Log instance
			 */
			static shared_ptr<Log> getInstance();

			/**
			 * Set the location to log messages.
			 *
			 * \param	Target	The log target
			 */
			void setTarget( Target target );

			/**
			 * Set the severity of messages to log.
			 *
			 * \param	Level	The log level to set
			 */
			void setLevel( Level level );

			/**
			 * Set a file to log to if the target is LOG_FILE.
			 *
			 * \param	string	The file to which we will log
			 */
			int setFile( string fileName );

			/**
			 * Get the current log level. Only messages
			 * with equal or higher severity will be written.
			 *
			 * \return	Log::Level	The current log level
			 */
			Level getLevel();

			/**
			 * Convert the Log::Level enum to a string.
			 *
			 * \param	Log::Level	The level to convert
			 * \return	string	The converted level
			 */
			string levelToString( Level level );

			/**
			 * Log a message.
			 *
			 * \param	Level	The severity of the message
			 * \param	string	The message to write
			 */
			void write( Level level, string message );

			/**
			 * Date and time will no longer be printed with each log message.
			 */
			void excludeTimestamp() {
				this->timestampEnabled = false;
			}

			/**
			 * Date and time will be printed with each log message.
			 */
			void includeTimestamp() {
				this->timestampEnabled = true;
			}

			/**
			 * Log level will no longer be printed with each log message.
			 */
			void excludeLogLevel() {
				this->levelEnabled = false;
			}

			/**
			 * Log level will be printed with each log message.
			 */
			void includeLogLevel() {
				this->levelEnabled = true;
			}

		protected:
			Log() {}

		private:
			// Our single instance of the class
			static shared_ptr<Log> log;

			// write() uses these variables to determine which messages should be written where.
			Level logLevel = Level::INFO;
			Target logTarget = Target::STDOUT;
			string logFile = "";

			// Flags that change log style
			bool timestampEnabled = true;
			bool levelEnabled = true;

			// String representations of log levels
			map< Level, string > levelMap = {
				{ Level::DEBUG, "DEBUG" },
				{ Level::INFO, "INFO" },
				{ Level::NOTICE, "NOTICE" },
				{ Level::WARNING, "WARNING" },
				{ Level::ERR, "ERROR" },
				{ Level::CRIT, "CRITICAL" },
				{ Level::ALERT, "ALERT" },
				{ Level::EMERG, "EMERGENCY" }
			};
	};

	////////////////////////
	// Bit-wise operators //
	////////////////////////
	inline Log::Target operator&( Log::Target a, Log::Target b ){
		return static_cast<Log::Target>( static_cast<short>( a ) & static_cast<short>( b ) );
	}
	inline Log::Target operator|( Log::Target a, Log::Target b ){
		return static_cast<Log::Target>( static_cast<short>( a ) | static_cast<short>( b ) );
	}
}
