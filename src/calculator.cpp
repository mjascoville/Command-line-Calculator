//============================================================================
// Name        : calculator.cpp
// Author      : Michael Scoville
// Version     : 1.0
// Copyright   : 2024
// Description : Simple command-line calculator
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <memory>

//This is my base class
class Operation {
public:
    virtual ~Operation() = default;
    virtual double calculate(double operand1, double operand2) const = 0;
};

//Here are the classes for each operator; they inherit from the base class
class Addition : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return operand1 + operand2;
    }
};

class Subtraction : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return operand1 - operand2;
    }
};

class Multiplication : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return operand1 * operand2;
    }
};

class Division : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
    	//Check for division by zero
        if (operand2 == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }
        return operand1 / operand2;
    }
};

std::unique_ptr<Operation> createOperation(char operation) {
    switch (operation) {
        case '+': return std::make_unique<Addition>();
        case '-': return std::make_unique<Subtraction>();
        case '*': return std::make_unique<Multiplication>();
        case '/': return std::make_unique<Division>();
        //Here we return null for unsupported operators
        default:
            return nullptr;
    }
}

int main() {
	std::cout << "*---------------------*\n";
	std::cout << "Command-line Calculator\n";
    std::cout << "*---------------------*\n";
    std::cout << "Enter your operation in the format: [number] [+,-,*,/] [number] \n(example: 3 + 4)\n";
    std::cout << "Type 'quit' to end the program.\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
        }

        std::istringstream stream(input);
        double operand1, operand2;
        char operationChar;

        if (stream >> operand1 >> operationChar >> operand2) {
            try {
                std::unique_ptr<Operation> operation = createOperation(operationChar);
                if (operation) {
                    double result = operation->calculate(operand1, operand2);
                    std::cout << "Result: " << result << "\n";
                } else {
                    std::cout << "Error: Unsupported operation.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else {
            std::cout << "Error: Invalid input format. Please try again.\n";
        }
    }

    std::cout << "The program is now ending. Goodnight.\n";
    return 0;
}
