/*
** EPITECH PROJECT, 2018
** abstractVM
** File description:
** Operand.tpp
*/

#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "Factory.h"
#include "VMErrors.h"

/* Float */

// template<>
// Operand<eOperandType::Float, float>::Operand(std::string const &str)
// {
// 	std::string::size_type pos;
// 	_nb = std::stof(str, &pos);

// 	if (pos != str.size())
// 		throw vm::ExecError{"bad number formation"};
// }

template<>
IOperand *Operand<eOperandType::Float, float>::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(_etype, std::to_string(std::fmod(_nb, std::stod(rhs.toString()))));
}

/* Double */

// template<>
// Operand<eOperandType::Double, double>::Operand(std::string const &str)
// {
// 	std::string::size_type pos;
// 	_nb = std::stod(str, &pos);

// 	if (pos != str.size())
// 		throw vm::ExecError{"bad number formation"};
// }

template<>
IOperand *Operand<eOperandType::Double, double>::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(_etype, std::to_string(std::fmod(_nb, std::stod(rhs.toString()))));
}

/* bigDecimal */

template<>
Operand<eOperandType::BigDecimal, std::string>::Operand(std::string const &str)
{
	_nb = str;
	// verif number is -?[0-9]*.?[0-9]*
	if (false)
		throw vm::ExecError{"bad number formation"};
}
template<>
std::string Operand<eOperandType::BigDecimal, std::string>::toString() const
{
	return _nb;
}
template<>
IOperand *Operand<eOperandType::BigDecimal, std::string>::operator+(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
template<>
IOperand *Operand<eOperandType::BigDecimal, std::string>::operator-(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
template<>
IOperand *Operand<eOperandType::BigDecimal, std::string>::operator*(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
template<>
IOperand *Operand<eOperandType::BigDecimal, std::string>::operator/(IOperand const &rhs) const
{
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
template<>
IOperand *Operand<eOperandType::BigDecimal, std::string>::operator%(IOperand const &rhs) const
{
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}

/* Default */

template<eOperandType eType, typename T>
Operand<eType, T>::Operand(std::string const &str)
{
	std::string::size_type pos;
	long n;
	try {
		n = std::stol(str, &pos);
	} catch (std::exception const &e) {
		if (str[0] == '-')
			throw vm::ExecError{"underflow"};
		throw vm::ExecError{"overflow"};
	}
	if (pos != str.size())
		throw vm::ExecError{"bad number formation"};

	int typeidx = static_cast<int>(eType);
	if (typeidx >= 0 && typeidx < 3) {
		if (n < limits_g[typeidx].first)
			throw vm::ExecError{"underflow"};
		if (n > limits_g[typeidx].second)
			throw vm::ExecError{"overflow"};
	}
	_nb = static_cast<T>(n);
}

template<eOperandType eType, typename T>
std::string Operand<eType, T>::toString() const
{
	return std::to_string(_nb);
}
template<eOperandType eType, typename T>
eOperandType Operand<eType, T>::getType () const
{
	return _etype;
}
template<eOperandType eType, typename T>
IOperand *Operand<eType, T>::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(_etype, std::to_string(_nb + std::stod(rhs.toString())));
}
template<eOperandType eType, typename T>
IOperand *Operand<eType, T>::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(_etype, std::to_string(_nb - std::stod(rhs.toString())));
}
template<eOperandType eType, typename T>
IOperand *Operand<eType, T>::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(_etype, std::to_string(_nb * std::stod(rhs.toString())));
}
template<eOperandType eType, typename T>
IOperand *Operand<eType, T>::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(_etype, std::to_string(_nb / std::stod(rhs.toString())));
}
template<eOperandType eType, typename T>
IOperand *Operand<eType, T>::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(_etype, std::to_string(_nb % std::stol(rhs.toString())));
}