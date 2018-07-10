/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** VMTools.cpp
*/

#include "VMTools.h"
#include "Factory.h"

namespace vm {

	void VMStack::push(IOperand const &op)
	{
		_stack.emplace_front(Factory::createOperandPtr(op.getType(), op.toString()));
	}

	void VMStack::push(IOperand *op)
	{
		if (op != nullptr)
			_stack.emplace_front(IOperand::ptr{op});
	}

	void VMStack::pop()
	{
		if (_stack.size() == 0)
			throw vm::ExecError{"pop instruction on an empty stack"};
		_stack.pop_front();
	}

	void VMStack::clear()
	{
		_stack.clear();
	}

	IOperand const &VMStack::front() const
	{
		if (_stack.size() == 0)
			throw vm::ExecError{"the stack is empty"};
		return *_stack.front();
	}

	std::size_t VMStack::size() const
	{
		return _stack.size();
	}

	void VMStack::dump() const
	{
		for (auto const &e : _stack) {
			// std::cout << e->getType() << "  " << *e << std::endl;
			std::cout << *e << std::endl;
		}
	}

}