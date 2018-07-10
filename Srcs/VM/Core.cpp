/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Core.cpp
*/

#include <iostream>
#include <sstream>
#include <fstream>

#include "Utils.h"
#include "Core.h"
#include "Factory.h"

namespace vm {

	void Core::exec(std::string const &filename)
	{

		if (filename != "") {
			std::ifstream file{filename};
			if (file.fail())
				throw vm::ExecError{"Error to open file"};
			readAllLines(file);
		} else {
			readAllLines(std::cin, true);
		}
		try {
			_head = -1;
			for (auto const &cmd : _cmds) {
				// std::cerr << cmd.line << " " << cmd.cmd << std::endl;
				++_head;
				execCmd(cmd.cmd);
				if (_exit == true)
					return;
			}
			throw ExecError{"the program has quit without exit instruction"};
		} catch (ExecError const &e) {
			if (_head < 0)
				throw VMError{0, e.what()};
			throw VMError{_cmds[_head].line, e.what()};
		}
	}

	void Core::readAllLines(std::istream &is, bool end)
	{
		std::string line;
		std::size_t i = 0;

		while (std::getline(is, line)) {
			++i;
			removeComment(line, end);
			if (end == true && line == ";;") {
				break;
			}
			if (line != "")
				_cmds.emplace_back(i, line);
		}
	}

	void Core::execCmd(std::string const &str)
	{
		std::stringstream sstr{str};
		std::string cmd;

		sstr >> cmd;
		// std::cerr << "cmd : [" << cmd << "]" << std::endl;
		for (auto const &e : Core::arrCmds) {
			if (e.str == cmd) {
				if (e.arg == false) {
					if (sstr.rdbuf()->in_avail() != 0)
						throw ExecError{"lexical or syntactical errors"};
					(this->*(e.f1))();
				} else {
					(this->*(e.f2))(parsValue(sstr));
				}
				return;
			}
		}
		throw ExecError{"lexical or syntactical errors"};
	}

	IOperand::ptr Core::parsValue(std::stringstream &sstr)
	{
		std::string type;
		std::getline(sstr, type, '(');
		trim(type);
		std::string value;
		std::getline(sstr, value, ')');
		trim(value);
		// std::cerr << "type : [" << type << "]" << std::endl;
		// std::cerr << "value: [" << value << "]" << std::endl;
		if (sstr.rdbuf()->in_avail() != 0)
			throw ExecError{"lexical or syntactical errors"};
		return Factory::createOperandPtr(toOperandType(type), value);
	}

	void Core::push(IOperand::ptr op)
	{
		_stack.push(*op);
	}
	void Core::pop()
	{
		_stack.pop();
	}
	void Core::dump()
	{
		_stack.dump();
	}
	void Core::clear()
	{
		_stack.clear();
	}
	void Core::dup()
	{
		_stack.push(Factory::createOperand(_stack.front().getType(), _stack.front().toString()));
	}
	void Core::swap()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op1);
		_stack.push(*op2);
	}
	void Core::assert(IOperand::ptr op)
	{
		if (_stack.front().getType() != op->getType()
		|| _stack.front().toString() != op->toString())
			throw ExecError{"assert not verified"};
	}
	void Core::add()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op1 + *op2);
	}
	void Core::sub()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op2 - *op1);
	}
	void Core::mul()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op1 * *op2);
	}
	void Core::div()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op2 / *op1);
	}
	void Core::mod()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		IOperand::ptr op2 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(*op2 % *op1);
	}
	void Core::sqrt()
	{
		IOperand::ptr op1 = Factory::createOperandPtr(_stack.front().getType(), _stack.front().toString());
		_stack.pop();
		_stack.push(IOperand::sqrt(*op1));
	}
	void Core::load(IOperand::ptr op)
	{
		int n = stoi(op->toString(), nullptr);

		if (n > 15 || n < 0)
			throw ExecError{"access to unvalid register number"};
		if (_regs[n])
			_stack.push(*_regs[n]);
		else
			throw ExecError{"use uninitialized register"};
	}
	void Core::store(IOperand::ptr op)
	{
		int n = std::stoi(op->toString(), nullptr);

		if (n > 15 || n < 0)
			throw ExecError{"access to unvalid register number"};
		_regs[n] = Factory::createOperandPtr(_regs[n]->getType(), _regs[n]->toString());
	}
	void Core::print()
	{
		if (_stack.front().getType() != eOperandType::Int8)
			throw ExecError{"assert not verified"};
		std::cout << static_cast<char>(std::stoi(_stack.front().toString())) << std::endl;
	}
	void Core::exit()
	{
		_exit = true;
	}

	const std::array<Core::VMCmd, 17> Core::arrCmds = {
		Core::VMCmd{"push", true, nullptr, &Core::push},
		Core::VMCmd{"pop", false, &Core::pop, nullptr},
		Core::VMCmd{"dump", false, &Core::dump, nullptr},
		Core::VMCmd{"clear", false, &Core::clear, nullptr},
		Core::VMCmd{"dup", false, &Core::dup, nullptr},
		Core::VMCmd{"swap", false, &Core::swap, nullptr},
		Core::VMCmd{"assert", true, nullptr, &Core::assert},
		Core::VMCmd{"add", false, &Core::add, nullptr},
		Core::VMCmd{"sub", false, &Core::sub, nullptr},
		Core::VMCmd{"mul", false, &Core::mul, nullptr},
		Core::VMCmd{"div", false, &Core::div, nullptr},
		Core::VMCmd{"mod", false, &Core::mod, nullptr},
		Core::VMCmd{"sqrt", false, &Core::sqrt, nullptr},
		Core::VMCmd{"load", true, nullptr, &Core::load},
		Core::VMCmd{"store", true, nullptr, &Core::store},
		Core::VMCmd{"print", false, &Core::print, nullptr},
		Core::VMCmd{"exit", false, &Core::exit, nullptr}
	};

}