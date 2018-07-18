/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Factory.h
*/

#pragma once

#include <array>
#include <memory>

#include "OperandType.h"

class IOperand;

class Factory {
public:
	static IOperand *createOperand(eOperandType type, std::string const &value);
	static std::unique_ptr<IOperand> createOperandPtr(eOperandType type, std::string const &value);

private:
	static IOperand *createInt8(std::string const &value);
	static IOperand *createInt16(std::string const &value);
	static IOperand *createInt32(std::string const &value);
	static IOperand *createFloat(std::string const &value);
	static IOperand *createDouble(std::string const &value);
	static IOperand *createBigDecimal(std::string const &value);

	static const std::array<IOperand *(*)(std::string const &), nOperandType> creator;
};