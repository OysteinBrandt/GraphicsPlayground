#pragma once

#ifndef _ENGINE_EXCEPTION_H_
#define _ENGINE_EXCEPTION_H_

#include <exception>
#include <string>

namespace engine
{
	class exception : public std::exception
	{
		const std::string m_what;

		exception operator=(const exception&) = delete;

	public:

		exception(const std::string &what) : m_what(what)
		{ }

		const char *what() const noexcept override
		{
			return m_what.c_str();
		}
	};
}

#endif