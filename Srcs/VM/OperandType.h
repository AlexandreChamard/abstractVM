/*
** EPITECH PROJECT, 2018
** abstractVM
** File description:
** OperandType.h
*/

#pragma once

#include <string>
#include <array>

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

