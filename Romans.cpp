#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Console.h"

using namespace std;

#define VERSION "1.1"
#define MAXN 3999
#define SHOW 10

int inputNumber(int max, int min);

void parse(int* data, int number);
string convert(int number, const char ena, const char pet, const char deset);
string IntToRoman(int number);
int RomanToInt(string number);
bool evaluate(string input, vector<int>& vals);
int reduceZero(int number);
void compact(vector<int>& data);
int summarize(vector<int>& data);

int main()
{
	cout << "\n\n * Integer to Roman and (vice versa) numerals v" << VERSION << " * " << endl;
	cout << "(Max number is " << MAXN << ")\n" << endl;
	srand((unsigned int)time(0));
	for (int i = 0; i < SHOW; i++) {
		int x = rand() % MAXN + 1;
		string solution = IntToRoman(x);
		int n = RomanToInt(solution);
		cout << "\n" << x << " is Roman: " << solution;
		cout << " is Integer: " << n << " ";
		bool check = (x == n);
		cout << "Pass: " << boolalpha << check;
		cout << endl;
	}
}

int RomanToInt(string number) {
	char romans[] = "IVXLCDM";
	int len = number.length();
	vector<int> values(len, 0);
	bool error = evaluate(number, values);
	if (error) {
		return -1;
	}
	int sum = summarize(values);
	return sum;
}

bool evaluate(string input, vector<int>& vals) {
	int len = vals.size();
	bool error = false;
	for (int i = 0; i < input.length(); ++i) {
		int value = 0;
		switch (input[i]) {
		case 'I':
			value = 1;
			break;
		case 'V':
			value = 5;
			break;
		case 'X':
			value = 10;
			break;
		case 'L':
			value = 50;
			break;
		case 'C':
			value = 100;
			break;
		case 'D':
			value = 500;
			break;
		case 'M':
			value = 1000;
			break;
		default:
			//ERROR
			value = -1;
			break;
		}
		vals[i] = value;
	}


	if (len > 1)
	{
		vector<int> delta(len - 1, 0);
		for (int j = 1; j < len; j++)
		{
			delta[j - 1] = vals[j] - vals[j - 1];
			if (delta[j - 1] > 0)
			{
				delta[j - 1] = reduceZero(delta[j - 1]);
			}
		}

		//check for illegal substraction
		for (int i = 0; i < len - 1; i++)
		{
			if (delta[i] > 0)
			{
				if (delta[i] != 9 && delta[i] != 4)
				{
					cout << "Ilegal sequence error: " << input[i] << input[i + 1] << endl;
					error = true;
				}
			}
		}
		//check for illegal xYx
		if (len > 2)
		{
			for (int i = 2; i < len; i++)
			{
				if (input[i] == input[i - 2] && vals[i - 1] > vals[i - 2])
				{
					cout << "Ilegal sequence error: " << input[i - 2] << input[i - 1] << input[i] << endl;
					error = true;
				}
			}
		}

		// check for too many V's, L's, D'
		int V = 0;
		int L = 0;
		int D = 0;
		for (int i = 0; i < len; i++)
		{
			if (input[i] == 'V') V++;
			else if (input[i] == 'L') L++;
			else if (input[i] == 'D') D++;
		}
		if (D > 1)
		{
			cout << "Too many D's error" << endl;
			error = true;
		}
		if (L > 1)
		{
			cout << "Too many L's error" << endl;
			error = true;
		}
		if (V > 1)
		{
			cout << "Too many V's error" << endl;
			error = true;
		}
		// check for four consecutive
		if (len > 3)
		{
			for (int i = 3; i < len; i++)
				if (input[i] == input[i - 1] && input[i] == input[i - 2] && input[i] == input[i - 3])
				{
					cout << "Four " << input[i] << "'s in a row error" << endl;
					error = true;
				}
		}
		//check for larger number after smaller
		compact(vals);
		if (!error) {
			for (int i = 0; i < len - 1; i++) {
				for (int j = i + 1; j < len; j++) {
					if (vals[i] > 0) {
						if (vals[i] < vals[j]) {
							cout << "Illegal use of smaller roman number before bigger number error on position " << (i + 1) << endl;
							error = true;
						}
					}
				}
			}
		}

		//check for double substraction
		for (int i = 0; i < len - 2; i++) {
			if (vals[i] < 0 && vals[i + 1] < 0) {
				cout << "Doule substraction error in sequence " << input[i] << input[i + 1] << input[i + 2] << endl;
				error = true;
			}
		}
	}
	return error;
}
void compact(vector<int>& data) {
	for (int i = 0; i < data.size() - 1; i++) {
		if (data[i] < data[i + 1]) {
			data[i] = -data[i];
		}
	}
}
int reduceZero(int number) {
	if (number % 10 == 0)
	{
		number = number / 10;
		return reduceZero(number);
	}
	else
	{
		return number;
	}
}

int summarize(vector<int>& data) {
	int sum = 0;
	for (int i = 0; i < data.size(); i++) {
		sum += data[i];
	}
	return sum;
}


string IntToRoman(int number) {
	int parsed[4] = { 0 };
	parse(parsed, number);
	string solution = "";
	solution += convert(parsed[0], 'M', '#', '#');
	solution += convert(parsed[1], 'C', 'D', 'M');
	solution += convert(parsed[2], 'X', 'L', 'C');
	solution += convert(parsed[3], 'I', 'V', 'X');
	return solution;
}

void parse(int* data, int number)
{
	int* p = data;
	int divisor = 1000;
	while (divisor >= 1)
	{
		*p = number / divisor;
		number = number % divisor;
		p++;
		divisor = divisor / 10;
	}
}


string convert(int number, const char ena, const char pet, const char deset)
{
	if (number == 0) return "";
	string result = "";
	switch (number)
	{
	case 1:
	case 2:
	case 3:
		for (int x = 0; x < number; x++)
		{
			result += ena;
		}
		break;
	case 4:
		result = ena;
		result += pet;
		break;
	case 5:
		result = pet;
		break;
	case 6:
	case 7:
	case 8:
		result = pet;
		for (int x = 0; x < (number - 5); x++)
		{
			result += ena;
		}
		break;
	case 9:
		result = ena;
		result += deset;
		break;
	}
	return result;
}
int inputNumber(int max, int min)
{
	int x = 0;
	while (true)
	{
		cout << "Enter number to convert: ";
		cin >> x;
		if (x > max || x < min)
		{
			cout << "You entered invalid number. Try again!\n";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
			}
			cin.ignore(32767, '\n');
		}
		else break;

	}
	cin.ignore(32767, '\n');
	return (x);
}

