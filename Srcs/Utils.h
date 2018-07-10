/*
** EPITECH PROJECT, 2018
** AbstractVM
** File description:
** Utils.h
*/

#pragma once

#include <algorithm>
#include <cstring>
#include <string>

static inline void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

static inline void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

static inline void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

static inline bool isend(std::string const &s)
{
	return (std::strncmp(s.c_str(), ";;", 2) == 0);
}

static inline void removeComment(std::string &s, bool end = false)
{
	trim(s);
	if (end && isend(s)) {
		s.erase(2);
	} else {
		auto pos = s.find(';');
		if (pos != std::string::npos) {
			s.erase(pos);
		}
	}
	trim(s);
}