#pragma once

#include <exception>
#include <string>

namespace phantom::core
{

	class IException : public std::exception
	{
	public:
		explicit IException(std::string message = "Unknown exception", std::string type = "Exception");
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
		explicit RuntimeException(const std::string message = "A runtime exception has occurred") : IException(message, "Runtime Exception") {}
	};

	class InvalidArgumentException : public IException
	{
	public:
		explicit InvalidArgumentException(const std::string message = "An invalid argument has passed") : IException(message, "Invalid Argument Exception") {}
	};

	class OutOfRangeException : public IException
	{
	public:
		explicit OutOfRangeException(const std::string message = "An out of range exception has occurred") : IException(message, "Out Of Range Exception") {}
	};

	class NotImplementedException : public IException
	{
	public:
		explicit NotImplementedException(const std::string message = "The method is not implemented yet") : IException(message, "Not Implemented Exception") {}
	};

	class OutOfMemoryException : public IException
	{
	public:
		explicit OutOfMemoryException(const std::string message = "Not enough memory") : IException(message, "Out Of Memory Exception") {}
	};

	class FileNotFoundException : public IException
	{
	public:
		explicit FileNotFoundException(const std::string message = "Unable to locate the file") : IException(message, "File Not Found Exception") {}
	};
}