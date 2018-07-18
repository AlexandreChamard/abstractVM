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

#include "Factory.h"
#include "OperandType.h"

#include "VMErrors.h"

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

template<eOperandType eType, typename T>
class Operand : public IOperand {
public:
	Operand<eType, T>(std::string const &);
	std::string toString() const override;
	eOperandType getType () const override;
	IOperand *operator+(IOperand const &rhs) const override;
	IOperand *operator-(IOperand const &rhs) const override;
	IOperand *operator*(IOperand const &rhs) const override;
	IOperand *operator/(IOperand const &rhs) const override;
	IOperand *operator%(IOperand const &rhs) const override;

private:
	static const eOperandType _etype = eType;
	T	_nb;
};

class Int8 : public Operand<eOperandType::Int8, int8_t> {
public:
	Int8(std::string const &nb = "0"): Operand{nb} {};
};

class Int16 : public Operand<eOperandType::Int16, int16_t> {
public:
	Int16(std::string const &nb = "0"): Operand{nb} {};
};

class Int32 : public Operand<eOperandType::Int32, int32_t> {
public:
	Int32(std::string const &nb = "0"): Operand{nb} {};
};

class Float : public Operand<eOperandType::Float, float> {
public:
	Float(std::string const &nb = "0"): Operand{nb} {};
};

class Double : public Operand<eOperandType::Double, double> {
public:
	Double(std::string const &nb = "0"): Operand{nb} {};
};

class BigDecimal : public Operand<eOperandType::BigDecimal, std::string> {
public:
	BigDecimal(std::string const &nb = "0"): Operand{nb} {};
};

static const std::pair<long, long> limits_g[] = {
	{INT8_MIN, INT8_MAX},
	{INT16_MIN, INT16_MAX},
	{INT32_MIN, INT32_MAX}
};

// class Int8 : public IOperand {
// public:
// 	Int8(std::string const & = "0");
// 	virtual ~Int8(){}
// 	std::string toString() const override { return std::to_string(_nb); }
// 	eOperandType getType () const override { return eOperandType::Int8; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	int8_t _nb;
// };

// class Int16 : public IOperand {
// public:
// 	Int16(std::string const & = "0");
// 	virtual ~Int16(){}
// 	std::string toString() const override { return std::to_string(_nb); }
// 	eOperandType getType () const override { return eOperandType::Int16; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	int16_t _nb;
// };

// class Int32 : public IOperand {
// public:
// 	Int32(std::string const & = "0");
// 	virtual ~Int32(){}
// 	std::string toString() const override { return std::to_string(_nb); }
// 	eOperandType getType () const override { return eOperandType::Int32; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	int32_t _nb;
// };

// class Float : public IOperand {
// public:
// 	Float(std::string const & = "0");	
// 	virtual ~Float(){}
// 	std::string toString() const override;
// 	eOperandType getType () const override { return eOperandType::Float; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	float _nb;
// };

// class Double : public IOperand {
// public:
// 	Double(std::string const & = "0");
// 	virtual ~Double(){}
// 	std::string toString() const override;
// 	eOperandType getType () const override { return eOperandType::Double; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	double _nb;
// };

// class BigDecimal : public IOperand {
// public:
// 	BigDecimal(std::string const & = "0");
// 	virtual ~BigDecimal(){}
// 	std::string toString() const override { return _nb; }
// 	eOperandType getType () const override { return eOperandType::BigDecimal; }
// 	IOperand *operator+(IOperand const &rhs) const override;
// 	IOperand *operator-(IOperand const &rhs) const override;
// 	IOperand *operator*(IOperand const &rhs) const override;
// 	IOperand *operator/(IOperand const &rhs) const override;
// 	IOperand *operator%(IOperand const &rhs) const override;
// private:
// 	std::string _nb;
// };

std::ostream &operator<<(std::ostream &, eOperandType);
std::ostream &operator<<(std::ostream &, IOperand *);
std::ostream &operator<<(std::ostream &, IOperand const &);

#include "Operand.tpp"