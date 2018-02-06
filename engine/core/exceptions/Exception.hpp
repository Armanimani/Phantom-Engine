#pragma once

#include <exception>
#include <string>

namespace phantom::core
{

	class IException : public std::exception
	{
	public:
		IException(const std::string message = "Unknown exception", const std::string type = "Exception");
		virtual ~IException() {}
		const char* what() const noexcept override;

	private:
		std::string type_;
		std::string stack_;
		std::string message_;
		std::string what_;
		void calculateStack_() noexcept;
	};

	class RuntimeException : public IException
	{
	public:
		RuntimeException(const std::string message = "A runtime exception has occurred") : IException(message, "Runtime Exception") {}
	};

	class InvalidArgumentException : public IException
	{
	public:
		InvalidArgumentException(const std::string message = "An invalid argument has passed") : IException(message, "Invalid Argument Exception") {}
	};

	class OutOfRangeException : public IException
	{
	public:
		OutOfRangeException(const std::string message = "An out of range exception has occurred") : IException(message, "Out Of Range Exception") {}
	};

	class NotImplementedException : public IException
	{
	public:
		NotImplementedException(const std::string message = "The method is not implemented yet") : IException(message, "Not Implemented Exception") {}
	};

	class OutOfMemoryException : public IException
	{
	public:
		OutOfMemoryException(const std::string message = "Not enough memory") : IException(message, "Out Of Memory Exception") {}
	};

	class FileNotFoundException : public IException
	{
	public:
		FileNotFoundException(const std::string message = "Unable to locate the file") : IException(message, "File Not Found Exception") {}
	};
}