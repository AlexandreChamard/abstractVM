/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Operand.cpp
*/

#include <iomanip>
#include <sstream>
#include <cmath>

#include "Factory.h"
#include "Operand.h"

IOperand *IOperand::sub(eOperandType type, IOperand const &op1, IOperand const &op2)
{
	switch (type) {
		case eOperandType::Int8:
			return *Factory::createOperandPtr(eOperandType::Int8, op1.toString()) - op2;
		case eOperandType::Int16:
			return *Factory::createOperandPtr(eOperandType::Int16, op1.toString()) - op2;
		case eOperandType::Int32:
			return *Factory::createOperandPtr(eOperandType::Int32, op1.toString()) - op2;
		case eOperandType::Float:
			return *Factory::createOperandPtr(eOperandType::Float, op1.toString()) - op2;
		case eOperandType::Double:
			return *Factory::createOperandPtr(eOperandType::Double, op1.toString()) - op2;
		case eOperandType::BigDecimal:
			return op1 - op2;
	}
	throw vm::ExecError{"invalid operand"};
	return nullptr;
}
IOperand *IOperand::div(eOperandType type, IOperand const &op1, IOperand const &op2)
{
	switch (type) {
		case eOperandType::Int8:
			return *Factory::createOperandPtr(eOperandType::Int8, op1.toString()) / op2;
		case eOperandType::Int16:
			return *Factory::createOperandPtr(eOperandType::Int16, op1.toString()) / op2;
		case eOperandType::Int32:
			return *Factory::createOperandPtr(eOperandType::Int32, op1.toString()) / op2;
		case eOperandType::Float:
			return *Factory::createOperandPtr(eOperandType::Float, op1.toString()) / op2;
		case eOperandType::Double:
			return *Factory::createOperandPtr(eOperandType::Double, op1.toString()) / op2;
		case eOperandType::BigDecimal:
			return op1 / op2;
	}
	throw vm::ExecError{"invalid operand"};
	return nullptr;
}
IOperand *IOperand::mod(eOperandType type, IOperand const &op1, IOperand const &op2)
{
	switch (type) {
		case eOperandType::Int8:
			return *Factory::createOperandPtr(eOperandType::Int8, op1.toString()) % op2;
		case eOperandType::Int16:
			return *Factory::createOperandPtr(eOperandType::Int16, op1.toString()) % op2;
		case eOperandType::Int32:
			return *Factory::createOperandPtr(eOperandType::Int32, op1.toString()) % op2;
		case eOperandType::Float:
			return *Factory::createOperandPtr(eOperandType::Float, op1.toString()) % op2;
		case eOperandType::Double:
			return *Factory::createOperandPtr(eOperandType::Double, op1.toString()) % op2;
		case eOperandType::BigDecimal:
			return op1 % op2;
	}
	throw vm::ExecError{"invalid operand"};
	return nullptr;
}
IOperand *IOperand::sqrt(IOperand const &op)
{
	switch (op.getType()) {
		case eOperandType::Int8:
			return Factory::createOperand(eOperandType::Int8, std::to_string(static_cast<long>(::sqrt(std::stod(op.toString())))));
		case eOperandType::Int16:
			return Factory::createOperand(eOperandType::Int16, std::to_string(static_cast<long>(::sqrt(std::stod(op.toString())))));
		case eOperandType::Int32:
			return Factory::createOperand(eOperandType::Int32, std::to_string(static_cast<long>(::sqrt(std::stod(op.toString())))));
		case eOperandType::Float:
			return Factory::createOperand(eOperandType::Float, std::to_string(::sqrt(std::stod(op.toString()))));
		case eOperandType::Double:
			return Factory::createOperand(eOperandType::Double, std::to_string(::sqrt(std::stod(op.toString()))));
		case eOperandType::BigDecimal:
			return Factory::createOperand(eOperandType::BigDecimal, "0");
	}
	throw vm::ExecError{"invalid operand"};
	return nullptr;
}

Int8::Int8(std::string const &str)
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
	if (n < INT8_MIN)
		throw vm::ExecError{"underflow"};
	if (n > INT8_MAX)
		throw vm::ExecError{"overflow"};
	_nb = static_cast<int8_t>(n);
}
IOperand *Int8::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(eOperandType::Int8, std::to_string(_nb + std::stol(rhs.toString())));
}
IOperand *Int8::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(eOperandType::Int8, std::to_string(_nb - std::stol(rhs.toString())));
}
IOperand *Int8::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(eOperandType::Int8, std::to_string(_nb * std::stol(rhs.toString())));
}
IOperand *Int8::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int8, std::to_string(_nb / std::stol(rhs.toString())));
}
IOperand *Int8::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int8, std::to_string(_nb % std::stol(rhs.toString())));
}

Int16::Int16(std::string const &str)
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
	if (n < INT16_MIN)
		throw vm::ExecError{"underflow"};
	if (n > INT16_MAX)
		throw vm::ExecError{"overflow"};
	_nb = static_cast<int16_t>(n);
}
IOperand *Int16::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(eOperandType::Int16, std::to_string(_nb + std::stol(rhs.toString())));
}
IOperand *Int16::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(eOperandType::Int16, std::to_string(_nb - std::stol(rhs.toString())));
}
IOperand *Int16::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(eOperandType::Int16, std::to_string(_nb * std::stol(rhs.toString())));
}
IOperand *Int16::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int16, std::to_string(_nb / std::stol(rhs.toString())));
}
IOperand *Int16::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int16, std::to_string(_nb % std::stol(rhs.toString())));
}

Int32::Int32(std::string const &str)
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
	if (n < INT32_MIN)
		throw vm::ExecError{"underflow"};
	if (n > INT32_MAX)
		throw vm::ExecError{"overflow"};
	_nb = static_cast<int32_t>(n);
}
IOperand *Int32::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(eOperandType::Int32, std::to_string(_nb + std::stol(rhs.toString())));
}
IOperand *Int32::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(eOperandType::Int32, std::to_string(_nb - std::stol(rhs.toString())));
}
IOperand *Int32::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(eOperandType::Int32, std::to_string(_nb * std::stol(rhs.toString())));
}
IOperand *Int32::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int32, std::to_string(_nb / std::stol(rhs.toString())));
}
IOperand *Int32::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stol(rhs.toString()) == 0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Int32, std::to_string(_nb % std::stol(rhs.toString())));
}

Float::Float(std::string const &str)
{
	std::string::size_type pos;
	_nb = std::stof(str, &pos);

	if (pos != str.size())
		throw vm::ExecError{"bad number formation"};
}
std::string Float::toString() const
{
	std::stringstream sstr;

	sstr << std::fixed << std::setprecision(2) << _nb;
	return sstr.str();
}
IOperand *Float::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(eOperandType::Float, std::to_string(_nb + std::stof(rhs.toString())));
}
IOperand *Float::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(eOperandType::Float, std::to_string(_nb - std::stof(rhs.toString())));
}
IOperand *Float::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(eOperandType::Float, std::to_string(_nb * std::stof(rhs.toString())));
}
IOperand *Float::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stof(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Float, std::to_string(_nb / std::stof(rhs.toString())));
}
IOperand *Float::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stof(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Float, std::to_string(std::fmod(_nb, std::stof(rhs.toString()))));
}

Double::Double(std::string const &str)
{
	std::string::size_type pos;
	_nb = std::stod(str, &pos);

	if (pos != str.size())
		throw vm::ExecError{"bad number formation"};
}
std::string Double::toString() const
{
	std::stringstream sstr;

	sstr << std::fixed << std::setprecision(2) << _nb;
	return sstr.str();
}
IOperand *Double::operator+(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs + *this;
	return Factory::createOperand(eOperandType::Double, std::to_string(_nb + std::stod(rhs.toString())));
}
IOperand *Double::operator-(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return sub(rhs.getType(), *this, rhs);
	return Factory::createOperand(eOperandType::Double, std::to_string(_nb - std::stod(rhs.toString())));
}
IOperand *Double::operator*(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return rhs * *this;
	return Factory::createOperand(eOperandType::Double, std::to_string(_nb * std::stod(rhs.toString())));
}
IOperand *Double::operator/(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return div(rhs.getType(), *this, rhs);
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Double, std::to_string(_nb / std::stod(rhs.toString())));
}
IOperand *Double::operator%(IOperand const &rhs) const
{
	if (getType() < rhs.getType())
		return mod(rhs.getType(), *this, rhs);
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::Double, std::to_string(std::fmod(_nb, std::stod(rhs.toString()))));
}

BigDecimal::BigDecimal(std::string const &str):
_nb{str}
{
	/* verif number is -?[0-9]*.?[0-9]* */
	if (false)
		throw vm::ExecError{"bad number formation"};
}
IOperand *BigDecimal::operator+(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
IOperand *BigDecimal::operator-(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
IOperand *BigDecimal::operator*(IOperand const &rhs) const
{
	(void)rhs;
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
IOperand *BigDecimal::operator/(IOperand const &rhs) const
{
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}
IOperand *BigDecimal::operator%(IOperand const &rhs) const
{
	if (std::stod(rhs.toString()) == 0.0)
		throw vm::ExecError{"floating point exception"};
	return Factory::createOperand(eOperandType::BigDecimal, "0");
}

std::ostream &operator<<(std::ostream &os, eOperandType type)
{
	switch (type) {
		case eOperandType::Int8:
			return os << "Int8";
		case eOperandType::Int16:
			return os << "Int16";
		case eOperandType::Int32:
			return os << "Int32";
		case eOperandType::Float:
			return os << "Float";
		case eOperandType::Double:
			return os << "Double";
		case eOperandType::BigDecimal:
			return os << "BigDecimal";
	};
	return os;
}
std::ostream &operator<<(std::ostream &os, IOperand *ope)
{
	if (ope == nullptr)
		return os << "nullptr";
	return os << *ope;
}

std::ostream &operator<<(std::ostream &os, IOperand const &ope)
{
	return os << ope.toString();
}