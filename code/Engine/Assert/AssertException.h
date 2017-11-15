#pragma once

#ifndef _ENGINE_ASSERTEXCEPTION_H_
#define _ENGINE_ASSERTEXCEPTION_H_

#include "EngineException.h"

namespace engine::assert
{
	class exception : public engine::exception
	{
		const std::string m_message;
		const std::string m_function;
		const std::string m_file;
		unsigned int m_line;

		exception operator=(const exception &) = delete;

	public:

		exception(const std::string &message, const std::string &function, const std::string &file, unsigned int line)
			: engine::exception("Message: " + message + "\nFunction: " + function + "\nFile: " + file + "\nLine: " + std::to_string(line)),
				m_message(message), m_function(function), m_file(file), m_line(line)
		{ }
	};
}

#if defined ENGINE_DEBUG
	#define ENGINE_ASSERT_EXCEPTION(message) throw engine::assert::exception(message, __FUNCTION__, __FILE__, __LINE__)
	#define ENGINE_ASSERT_EXCEPTION_IF(expression, message) ((expression) ? ENGINE_ASSERT_EXCEPTION(message) : (void)0)
#else
	#define ENGINE_ASSERT_EXCEPTION(message) (void)0
	#define ENGINE_ASSERT_EXCEPTION_IF(expression, message) (void)0
#endif

#endif