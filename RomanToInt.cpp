#include <iostream>
#include <string>
#define VERSION "1.0"
using namespace std;

int inputNumber(int max, int min);
string inputString(void);
void printArray(int* data, int length);
bool evaluate(string input, int* vals, int len);
int reduceZero(int number);
void compact(int* data, int length);
int summarize(int* data, int length);

/*int main()
{
	cout << " \n\n* RomanNumber to integer v" << VERSION << " * " << endl;
	string input = inputString();
	int len = input.length();
	char romans[] = "IVXLCDM";
	int* values = new int[len]();
	bool error = evaluate(input, values, len);

	if (error)
	{
		cout << "Aborting ... " << endl;
		printArray(values, len);
		delete[] values;
		return 0;
	}

	//printArray(values, len);
	int sum = summarize(values, len);
	cout << "Roman number " << input << " is " << sum << endl;
	delete[] values;
	cout << "\n" << endl;
	return 0;
}*/

bool evaluate(string input, int* vals, int len)
{
	bool error = false;
	for (string::size_type i = 0; i < input.length(); ++i)
	{
		int value = 0;
		switch (input[i])
		{
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
	//cont
	if (len > 1)
	{
		int* delta = new int[len - 1];
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
		compact(vals, len);
		if (!error)
		{
			for (int i = 0; i < len - 1; i++)
			{
				for (int j = i + 1; j < len; j++)
				{
					if (vals[i] > 0)
					{
						if (vals[i] < vals[j])
						{
							cout << "Illegal use of smaller roman number before bigger number error on position " << (i + 1) << endl;
							error = true;
						}
					}
				}
			}
		}

		//check for double substraction
		for (int i = 0; i < len - 2; i++)
		{
			if (vals[i] < 0 && vals[i + 1] < 0)
			{
				cout << "Doule substraction error in sequence " << input[i] << input[i + 1] << input[i + 2] << endl;
				error = true;
			}
		}
		//
		delete[] delta; //cleanup
	}
	return error;
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

string inputString(void)
{
	string input = "";
	char romans[] = "IVXLCDM";
	bool ok = false;
	while (true)
	{
		cout << "\n\nEnter Roman number to convert: ";
		getline(cin, input);
		for (string::iterator it = input.begin(); it != input.end(); ++it)
		{
			ok = false;
			for (int i = 0; romans[i] != '\0'; i++)
			{
				if (*it == romans[i])
				{
					ok = true;
					break;
				}
			}
			if (!ok) {
				break;
			}
		}
		if (ok)
		{
			break;
		}
		else
		{
			cout << "Not a valid roman numeral!" << endl;
		}
	}
	return (input);
}
void printArray(int* data, int length)
{
	cout << "\nDebug output array:" << endl;
	int* p = data;
	for (int x = 0; x < length; x++)
	{
		cout << p << " --> cell[" << x << "]\t= " << *p << endl;
		p++;
	}
	cout << endl;
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
void compact(int* data, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (data[i] < data[i + 1])
		{
			data[i] = -data[i];
		}
	}
}
int summarize(int* data, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += data[i];
	}
	return sum;
}