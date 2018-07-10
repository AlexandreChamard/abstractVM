/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Operand.hpp
*/

#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "VMErrors.h"

enum class eOperandType {
	Int8		= 0,
	Int16		= 1,
	Int32		= 2,
	Float		= 3,
	Double		= 4,
	BigDecimal	= 5
};
constexpr int nOperandType = 6;

static inline eOperandType toOperandType(std::string const &type)
{
	static const std::array<std::string, nOperandType> arr = {"int8", "int16", "int32", "float", "double", "bigDecimal"};

	for (int i = 0; i < nOperandType; ++i) {
		if (arr[i] == type)
			return static_cast<eOperandType>(i);
	}
	throw vm::ExecError{"lexical or syntactical errors"};
}

class IOperand {
public:
	using ptr = std::unique_ptr<IOperand>;
	virtual std::string toString() const = 0; // string that represents the instance
	virtual eOperandType getType () const = 0; // returns the type of instance
	virtual IOperand *operator+(IOperand const &rhs) const = 0; // sum
	virtual IOperand *operator-(IOperand const &rhs) const = 0; // diff
	virtual IOperand *operator*(IOperand const &rhs) const = 0; // mul
	virtual IOperand *operator/(IOperand const &rhs) const = 0; // div
	virtual IOperand *operator%(IOperand const &rhs) const = 0; // mod
	virtual ~IOperand(){}

	static IOperand *sqrt(IOperand const &);
protected:
	static IOperand *sub(eOperandType, IOperand const &, IOperand const &);
	static IOperand *div(eOperandType, IOperand const &, IOperand const &);
	static IOperand *mod(eOperandType, IOperand const &, IOperand const &);
};

class Int8 : public IOperand {
public:
	Int8(std::string const & = "0");
	virtual ~Int8(){}
	std::string toString() const override { return std::to_string(_nb); }
	eOperandType getType () const override { return eOperandType::Int8; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	int8_t _nb;
};

class Int16 : public IOperand {
public:
	Int16(std::string const & = "0");
	virtual ~Int16(){}
	std::string toString() const override { return std::to_string(_nb); }
	eOperandType getType () const override { return eOperandType::Int16; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	int16_t _nb;
};

class Int32 : public IOperand {
public:
	Int32(std::string const & = "0");
	virtual ~Int32(){}
	std::string toString() const override { return std::to_string(_nb); }
	eOperandType getType () const override { return eOperandType::Int32; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	int32_t _nb;
};

class Float : public IOperand {
public:
	Float(std::string const & = "0");	
	virtual ~Float(){}
	std::string toString() const override;
	eOperandType getType () const override { return eOperandType::Float; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	float _nb;
};

class Double : public IOperand {
public:
	Double(std::string const & = "0");
	virtual ~Double(){}
	std::string toString() const override;
	eOperandType getType () const override { return eOperandType::Double; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	double _nb;
};

class BigDecimal : public IOperand {
public:
	BigDecimal(std::string const & = "0");
	virtual ~BigDecimal(){}
	std::string toString() const override { return _nb; }
	eOperandType getType () const override { return eOperandType::BigDecimal; }
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;
private:
	std::string _nb;
};

std::ostream &operator<<(std::ostream &, eOperandType);
std::ostream &operator<<(std::ostream &, IOperand *);
std::ostream &operator<<(std::ostream &, IOperand const &);