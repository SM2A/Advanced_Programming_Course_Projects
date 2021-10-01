#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#define DEFAULT_VALUE 0
#define FIRST_INDEX 0
#define GET_INPUT '?'
#define ASSIGN '='
#define OUTPUT '!'
#define INPUT '$'

using namespace std;

class Variable {

	typedef pair<string, int> variable;

public:

	Variable() {}

	void update(string name, int value = DEFAULT_VALUE) {

		auto itr = variables.find(name);
		if (itr == variables.end()) variables.insert(variable(name, value));
		else itr->second = value;
	}

	void print(string name) {

		auto itr = variables.find(name);
		if (itr == variables.end()) cout << DEFAULT_VALUE << endl;
		else cout << itr->second << endl;
	}

	int get_value(string name) {

		auto itr = variables.find(name);
		if (itr == variables.end()) return DEFAULT_VALUE;
		else return itr->second;
	}

private:

	map<string, int> variables;
};

class Operation {

	typedef int (*operation)(int, int);

public:

	Operation() {

		operations.insert(pair<char, operation>('+', add));
		operations.insert(pair<char, operation>('*', mult));
		operations.insert(pair<char, operation>('-', sub));
		operations.insert(pair<char, operation>('/', divide));
	}

	int apply(char op, int a, int b) {

		return operations[op](a, b);
	}

private:

	map<char, operation> operations;

	static int add(int a, int b) { return a + b; }
	static int mult(int a, int b) { return a * b; }
	static int sub(int a, int b) { return a - b; }
	static int divide(int a, int b) { return a / b; }
};

class Expression {

public:

	Expression() {
		operation = new Operation();
		variable = new Variable();
	}

	void read_input() {

		string expression;
		while (getline(cin, expression)) {
			if (expression[FIRST_INDEX] == INPUT) {
				stringstream stream(expression);
				int input_num;
				char input_sign;
				stream >> input_sign;
				while (stream >> input_num) inputs.push_back(input_num);
				break;
			}
			expressions.push_back(expression);
		}
	}

	void process() {

		for (string expression : expressions) {

			stringstream stream(expression);
			stringstream assign_stream(expression);
			char input_sign;
			stream >> input_sign;

			if (input_sign == GET_INPUT) {
				string name;
				stream >> name;
				input(name);
			} else if (input_sign == OUTPUT) {
				string expression_;
				getline(stream, expression_);
				output(expression_);
			} else {
				string name, expression_;
				getline(assign_stream, name, ASSIGN);
				getline(assign_stream, expression_);
				assign(name, expression_);
			}
		}
	}

private:

	vector<string> expressions;
	vector<int> inputs;
	Variable *variable;
	Operation *operation;

	void input(string name) {

		remove_spaces(name);
		if (inputs.size() == 0) variable->update(name, DEFAULT_VALUE);
		else {
			variable->update(name, inputs[FIRST_INDEX]);
			inputs.erase(inputs.begin());
		}
	}

	void output(string expression) {

		remove_spaces(expression);
		if (is_number(expression)) cout << expression << endl;
		else if (is_single_variable(expression)) variable->print(expression);
		else {
			vector<string> expression_ = parse_expression(expression);
			reverse(expression_.begin(), expression_.end());
			cout << evaluate(expression_) << endl;
		}
	}

	int evaluate(vector<string> expression) {

		int result = 0;
		if (is_number(expression[FIRST_INDEX])) result = stoi(expression[FIRST_INDEX]);
		else result = variable->get_value(expression[FIRST_INDEX]);

		for (int i = 1; i < expression.size(); i += 2) {

			char operator_ = expression[i].c_str()[FIRST_INDEX];
			int value;
			if (is_number(expression[i + 1])) value = stoi(expression[i + 1]);
			else value = variable->get_value(expression[i + 1]);
			result = operation->apply(operator_, value, result);
		}

		return result;
	}

	bool is_number(string expression) {

		for (char i : expression) if (!isdigit(i)) return false;
		return true;
	}

	bool is_single_variable(string expression) {

		auto add = expression.find('+');
		auto sub = expression.find('-');
		auto mult = expression.find('*');
		auto div = expression.find('/');

		return !((add != string::npos) || (sub != string::npos) || (mult != string::npos) || (div != string::npos));
	}

	vector<string> parse_expression(string expression) {

		vector<string> expression_;
		int i = 0;

		while (i != expression.size()) {
			string phrase = "";
			for (i; i != expression.size(); i++) {
				if ((expression[i] == '+') || (expression[i] == '-')
				    || (expression[i] == '*') || (expression[i] == '/'))
					break;
				phrase += (expression[i]);
			}
			expression_.push_back(phrase);
			if (i == expression.size()) break;
			expression_.push_back(string(1, expression[i]));
			if (i != expression.size())i++;
		}
		for (string &i : expression_) remove_spaces(i);
		return expression_;
	}

	void assign(string name, string expression) {

		name.erase(remove(name.begin(), name.end(), '='), name.end());
		remove_spaces(name);
		vector<string> expression_ = parse_expression(expression);
		reverse(expression_.begin(), expression_.end());
		int value = evaluate(expression_);
		variable->update(name, value);
	}

	void remove_spaces(string &str) {

		str.erase(remove(str.begin(), str.end(), ' '), str.end());
	}
};

int main() {

	Expression expression;
	expression.read_input();
	expression.process();

	return 0;

}
