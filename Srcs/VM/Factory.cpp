/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Factory.cpp
*/

#include "Factory.h"

const std::array<IOperand *(*)(std::string const &), 6> Factory::creator = {
	Factory::createInt8,
	Factory::createInt16,
	Factory::createInt32,
	Factory::createFloat,
	Factory::createDouble,
	Factory::createBigDecimal
};

IOperand *Factory::createOperand(eOperandType type, std::string const &value)
{
	return Factory::creator[static_cast<std::size_t>(type)](value);
}

IOperand::ptr Factory::createOperandPtr(eOperandType type, std::string const &value)
{
	return IOperand::ptr{Factory::creator[static_cast<std::size_t>(type)](value)};
}

IOperand *Factory::createInt8(std::string const &value)
{
	return new Int8(value);
}

IOperand *Factory::createInt16(std::string const &value)
{
	return new Int16(value);
}

IOperand *Factory::createInt32(std::string const &value)
{
	return new Int32(value);
}

IOperand *Factory::createFloat(std::string const &value)
{
	return new Float(value);
}

IOperand *Factory::createDouble(std::string const &value)
{
	return new Double(value);
}

IOperand *Factory::createBigDecimal(std::string const &value)
{
	return new BigDecimal(value);
}


