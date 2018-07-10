/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** VmErrors.h
*/

#pragma once

#include <exception>
#include <string>

namespace vm {

	class ArgsError : public std::exception {
	public:
		ArgsError(std::string const &binName) throw() :
		_msg("\nUSAGE :\t\n" + binName + " [ filename ]\n")
		{}
		char const *what() const throw() override {
			return (_msg.c_str());
		}
		virtual ~ArgsError() throw(){}

	private:
		std::string _msg;
	};

	class VMError : public std::exception {
	public:
		VMError(std::size_t line, std::string const &error) throw() :
		_msg("line " + std::to_string(line) + " : " + error)
		{}
		char const *what() const throw() override {
			return (_msg.c_str());
		}
		virtual ~VMError() throw(){}

	private:
		std::string _msg;
	};

	class ExecError : public std::exception {
	public:
		ExecError(std::string const &error) throw() :
		_msg("error : " + error)
		{}
		char const *what() const throw() override {
			return (_msg.c_str());
		}
		virtual ~ExecError() throw(){}

	private:
		std::string _msg;
	};

	// lexical or syntactical errors
	// instruction is unknown
	// overflow
	// underflow
	// pop instruction on an empty stack
	// division/modulo by 0
	// the program does not have an exit instruction
	// an assert instruction is not verified
	// the stack strictly has less than two values during the execution of an arithmetical instruction
	// use uninitialized register
	// access to unvalid register number
}