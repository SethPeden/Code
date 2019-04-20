#pragma once
#include <iostream>
#include <regex>
#include <string>

typedef struct Pattern {
	std::string pattern;
	std::regex reg;
	Pattern(std::string pattern = "") {
		this->pattern = pattern;
		this->reg = std::regex(this->pattern);
	}
	Pattern(const char *pattern) {
		*this = std::string(pattern);
	}
	Pattern operator +(Pattern pattern) const {
		return Pattern("(" + this->pattern + ")" + "(" + pattern.pattern + ")");
	}
	Pattern operator +(const char *pattern) const {
		return Pattern("(" + this->pattern + ")" + "(" + std::string(pattern) + ")");
	}
	Pattern operator |(Pattern pattern) const {
		return Pattern("(" + this->pattern + ")" + "|" + "(" + pattern.pattern + ")");
	}
	Pattern operator |(const char *pattern) const {
		return Pattern("(" + this->pattern + ")" + "|" + "(" + std::string(pattern) + ")");
	}
	bool matches(std::string input) const {
		return regex_match(input, this->reg);
	}
	bool matches(char *input) const {
		return regex_match(std::string(input), this->reg);
	}
} Pattern;

Pattern operator +(const char *pattern, Pattern other) {
	return Pattern("(" + std::string(pattern) + ")" + "(" + other.pattern + ")");
}

Pattern operator |(const char *pattern, Pattern other) {
	return Pattern("(" + std::string(pattern) + ")" + "|" + "(" + other.pattern + ")");
}

Pattern optional(Pattern pattern) {
	return Pattern("(" + pattern.pattern + ")" + "?");
}

Pattern onePlus(Pattern pattern) {
	return Pattern("(" + pattern.pattern + ")" + "+");
}

Pattern zeroPlus(Pattern pattern) {
	return Pattern("(" + pattern.pattern + ")" + "*");
}

Pattern enclose(Pattern pattern) {
	return Pattern("\\((" + pattern.pattern + ")\\)");
}

// Useful Patterns
namespace Patterns {
	const static Pattern Number = "\\d+";
	const static Pattern Integer = "-?" + Number;
	const static Pattern Exponent = "(e|E)" + (Integer | ("\\(" + Integer + "\\)"));
	const static Pattern UReal = Number + "(\\.\\d*)?" + optional(Exponent);
	const static Pattern Real = Integer + "(\\.\\d*)?" + optional(Exponent);
	const static Pattern UImaginary = (UReal + " ?i") | "i";
	const static Pattern Imaginary = (Real + " ?i") | "-?i";
	const static Pattern Complex = Real + " ?(\\+|-) ?" + UImaginary;
	const static Pattern Value = Real | Imaginary | Complex;
	const static Pattern Operator = "\\+|-|x|/";
}