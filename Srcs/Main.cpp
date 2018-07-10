/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Main.cpp
*/

#include <iostream>
#include <fstream>
#include <memory>
#include "Factory.h"
#include "Core.h"

int main(int ac, char **av)
{
	try {
		vm::Core core;
		if (ac > 1)
			core.exec(av[1]);
		else
			core.exec();
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
}