#pragma once

#include "Function.hpp"

Function::Function() : Surface(20, 20) { positionFormula = "0"; }

Function::Function(unsigned int N, unsigned int M) : Surface(N, M) { positionFormula = "sin(3.14*x)+cos(3.14*y)"; }

void Function::eval(float x, float y, glm::vec3& pos, glm::vec3& norm) {
	Dnum X = Dnum(x, glm::vec3(1.0f, 0.0f, 0.0f));
	Dnum Y = Dnum(y, glm::vec3(0.0f, 0.0f, 1.0f));
	Dnum Z = evaluateFormula(X, Y, positionFormula);
	pos = glm::vec3(x, Z.val, y);
	norm = glm::normalize(glm::vec3(normalSign * Z.der));
}

void Function::trimBrackets(std::string& formula) {
	unsigned int size = formula.size();

	if (formula[0] == '(' && formula[size - 1] == ')') {
		std::string newFormula;
		for (int i = 1; i < size - 1; ++i) {
			newFormula += formula[i];
		}
		formula = newFormula;
	}
}

bool Function::isOperation(std::string operation, std::string formula) {
	for (int i = 0; i < 3; ++i) {
		if (operation[i] != formula[i])
			return false;
	}
	return true;
}

bool Function::isNumber(const std::string& formula) {
	bool isFloat = false;

	for (int i = 0; i < formula[i]; ++i) {
		if (!std::isdigit(formula[i])) {
			if (formula[i] == '.' && !isFloat) {
				isFloat = true;
			}
			else if (i == 0 && formula[i] == '-') {
				continue;
			}
			else return false;
		}
	}
	return true;
}

float Function::toNumber(const std::string& number) {
	float result = 0;
	bool integer = true;
	unsigned int integerPartLength = 0;
	unsigned int size = number.size();

	std::string n;

	for (int i = 0; i < size; ++i) {
		if (number[i] == '.') {
			integer = false;
			integerPartLength = i;
		}
		else {
			n += number[i];
		}
	}
	
	size = n.size();
	for (int i = 0; i < size; ++i) {
		result += glm::pow(10, size - 1 - i) * (n[i] - '0');
	}

	if(!integer) {
		result = (float)result / (float)(glm::pow(10, size - integerPartLength));
	}

	return result;
}

void Function::removeSpaces(std::string& formula) {
	std::string result;
	for (char c : formula) {
		if (c != ' ')
			result += c;
	}
	formula = result;
}

std::string Function::trimOperation(std::string& operation) {
	unsigned int size = operation.size();
	std::string result;
	for (int i = 4; i < size - 1; ++i) {
		result += operation[i];
	}
	return result;
}

std::string Function::leftOperand(unsigned int index, std::string operation) {
	std::string result;
	for (int i = 0; i < index; ++i)
		result += operation[i];

	trimBrackets(result);
	return result;
}

std::string Function::rightOperand(unsigned int index, std::string operation) {
	std::string result;
	for (int i = index + 1; i < operation.size(); ++i)
		result += operation[i];

	trimBrackets(result);
	return result;
}

Dnum Function::evaluateFormula(Dnum x, Dnum y, std::string formula) {
	unsigned int bracketCount = 0;
	std::string operation;

	trimBrackets(formula);
	removeSpaces(formula);

	if (formula == std::string("x"))
		return x;

	if (formula == std::string("y"))
		return y;

	if (isNumber(formula))
		return toNumber(formula);

	for (int i = 0; i < formula.size(); ++i) {
		if (formula[i] == '(')
			bracketCount++;

		if (formula[i] == ')')
			bracketCount--;

		if (formula[i] == '+' && bracketCount == 0) {
			std::string left = leftOperand(i, formula);
			std::string right = rightOperand(i, formula);
			return evaluateFormula(x, y, left) + evaluateFormula(x, y, right);
		}
	}

	for (int i = 0; i < formula.size(); ++i) {
		operation += formula[i];

		if (formula[i] == '(')
			bracketCount++;

		if (formula[i] == ')')
			bracketCount--;

		if (formula[i] == '*' && bracketCount == 0) {
			std::string left = leftOperand(i, formula);
			std::string right = rightOperand(i, formula);
			return evaluateFormula(x, y, left) * evaluateFormula(x, y, right);
		}
	}

	if (isOperation("sin", formula))
		return _Sin(evaluateFormula(x, y, trimOperation(formula)));

	if (isOperation("cos", formula))
		return _Cos(evaluateFormula(x, y, trimOperation(formula)));

	if (isOperation("log", formula))
		return _Log(evaluateFormula(x, y, trimOperation(formula)));

	if (isOperation("exp", formula)) 
		return _Exp(evaluateFormula(x, y, trimOperation(formula)));

	if (isOperation("sqr", formula))
		return _Sqr(evaluateFormula(x, y, trimOperation(formula)));

	return Dnum(0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

