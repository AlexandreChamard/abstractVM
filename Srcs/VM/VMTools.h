/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** VMStack.h
*/

#pragma once

#include <list>
#include <string>

#include "Operand.h"

namespace vm {

	struct Command {
		Command(std::size_t line, std::string const &cmd):
		line{line},
		cmd{cmd}
		{}
		std::size_t line;
		std::string cmd;
	};

	class VMStack {
	public:
		void push(IOperand const &);
		void push(IOperand *);
		void pop();
		void clear();
		IOperand const &front() const;
		std::size_t size() const;
		void dump() const;

	private:
		std::list<IOperand::ptr> _stack;
	};

}