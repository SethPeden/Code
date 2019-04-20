#pragma once
#include <iostream>
#include <string>
#include "pattern.h"
#include "complex.h"

typedef struct Expression {
	std::string expression;
	Complex value;
	Expression(std::string expression = "") : expression(expression) { 
		this->value = this->evaluate(this->expression);
	}
	Complex evaluate(std::string expression) {
		// Value
		if (Patterns::Value.matches(expression)) {
			return Complex(expression);
		} 
		// (Value)
		else if (enclose(Patterns::Value).matches(expression)) {
			return Complex(expression.substr(1, expression.size() - 2));
		} 
		// Value Op Value
		else if ((Patterns::Value + " ?" + Patterns::Operator + " ?" + Patterns::Value).matches(expression)) { 
			int i = 0;
			while (i < expression.size()) {
				if (expression.at(i) == 'x') {
					if ((" ?" + Patterns::Value + " ?").matches(expression.substr(0, i)) and (" ?" + Patterns::Value + " ?").matches(expression.substr(i + 1))) {
						return Complex(expression.substr(0, i)) * Complex(expression.substr(i + 1));
					}
				} else if (expression.at(i) == '/') {
					if ((" ?" + Patterns::Value + " ?").matches(expression.substr(0, i)) and (" ?" + Patterns::Value + " ?").matches(expression.substr(i + 1))) {
						return Complex(expression.substr(0, i)) / Complex(expression.substr(i + 1));
					}
				}
				++i;
			}
		}


		return Complex();
	}
} Expression;

std::ostream &operator <<(std::ostream &os, Expression expression) {
	return (os << expression.value);
}