

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


bool addUp(int k, vector <int> numbers)
{
	
	sort(numbers.begin(), numbers.end());
	int count = 0;
	int checkNum = 0;
	while (checkNum != k)
	{
		if (count == numbers.size())
		{
			string message;
			cout << "No two numbers in the list added up to " << k << endl;
			cin >> message;
			return false;
		}
		checkNum = numbers[count];
		for (int i = count + 1; i < numbers.size();i++)
		{

			if (numbers[i] > k)
			{
				continue;
			}
			else if (checkNum + numbers[i] == k)
			{
				string message;
				cout << checkNum << " and " << numbers[i] << " equals: " << k << endl;
				cin >> message;
				return true;
			}


		}
		count = count + 1;
	}

}

int main()
{

	int k = 17;
	vector <int> x = { 10, 15, 3, 14};
	addUp(k, x);
	return 0;
}

