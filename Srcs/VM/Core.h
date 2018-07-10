/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Core.h
*/

#pragma once

#include <vector>
#include <sstream>
#include <string>

#include "VMTools.h"
#include "VMErrors.h"

namespace vm {

	class Core {
	public:
		Core() = default;
		~Core() = default;

		void exec(std::string const & = "");

	private:
		void readAllLines(std::istream &, bool end = false);
		void execCmd(std::string const &);
		IOperand::ptr parsValue(std::stringstream &);

		void	push(IOperand::ptr);
		void	pop();
		void	dump();
		void	clear();
		void	dup();
		void	swap();
		void	assert(IOperand::ptr);
		void	add();
		void	sub();
		void	mul();
		void	div();
		void	mod();
		void	sqrt();
		void	load(IOperand::ptr);
		void	store(IOperand::ptr);
		void	print();
		void	exit();

		bool				_exit = false;
		long				_head;
		std::vector<Command>		_cmds;
		VMStack				_stack;
		std::array<IOperand::ptr, 16>	_regs;

	private:
		struct VMCmd {
			std::string	str;
			bool		arg;
			void		(Core::*f1)();
			void		(Core::*f2)(IOperand::ptr);
		};
		static const std::array<VMCmd, 17>	arrCmds;

	};

}