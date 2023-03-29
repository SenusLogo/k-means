#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>

using namespace std;

void Problem_1()
{
	int n;
	cout << "Enter size matrix NxN: "; cin >> n;

	int** A = new int* [n];
	for (int i(0); i < n; i++)
		A[i] = new int[n];

	for (int i(0); i < n; i++)
		for (int j(0); j < n; j++)
			cin >> A[i][j];

	for (int i(0), l(n - 1); i < n; i++, l--)
		for (int j(0), m(n - 1); j < n; j++, m--)
		{
			if (A[i][j] != A[m][l])
			{
				cout << "Matrix not symmetrical!" << endl;
				cin.get();
				return;
			}

			if (i + j == n - 1)
				continue;
		}

	cout << "Matrix symmetrical!" << endl;
}

void Problem_2()
{
	int n; 
	cout << "Enter size matrix NxN: "; cin >> n;

	int** Matrix = new int* [n];
	vector<int> check_row, check_column;

	cout << "Enter matrix:" << endl;
	for (int i(0); i < n; i++)
	{
		Matrix[i] = new int[n];
		for (int j(0); j < n; j++)
			cin >> Matrix[i][j];
	}

	for (int i(0); i < n; i++)
	{
		for (int i(1); i <= n; i++)
		{
			check_row.push_back(i);
			check_column.push_back(i);
		}

		for (int j(0); j < n; j++)
		{
			check_row.erase(remove(check_row.begin(), check_row.end(), Matrix[i][j]), check_row.end());
			check_column.erase(remove(check_column.begin(), check_column.end(), Matrix[j][i]), check_column.end());
		}

		if (check_column.size() != 0 || check_row.size() != 0)
		{
			cout << "Matrix not a latin square!\n";
			return;
		}
	}

	cout << "Matrix a latin square!" << endl;
}

void Problem_3()
{
	string pos;
	cout << "Enter position: ";
	getline(cin, pos);

	int i_1 = 56 - int(pos[1]);
	int i_2 = int(pos[0]) - 97;

	char A[8][8] = { { '.', '.', '.', '.', '.', '.', '.', '.', },  { '.', '.', '.', '.', '.', '.', '.', '.', }, { '.', '.', '.', '.', '.', '.', '.', '.', }, { '.', '.', '.', '.', '.', '.', '.', '.', },
	{ '.', '.', '.', '.', '.', '.', '.', '.', } , { '.', '.', '.', '.', '.', '.', '.', '.', } , { '.', '.', '.', '.', '.', '.', '.', '.', }, { '.', '.', '.', '.', '.', '.', '.', '.', } };

	A[i_1][i_2] = 'Q';

	for (int j(1); j < 8; j++)
	{
		if(i_1 + j < 8)
			A[i_1 + j][i_2] = '*';
		if(i_1 - j >= 0)
			A[i_1 - j][i_2] = '*';
		if (i_2 + j < 8)
			A[i_1][i_2 + j] = '*';
		if (i_2 - j >= 0)
			A[i_1][i_2 - j] = '*';

		if (i_1 - j >= 0 && i_2 - j >= 0)
			A[i_1 - j][i_2 - j] = '*';
		if (i_1 + j < 8 && i_2 + j < 8)
			A[i_1 + j][i_2 + j] = '*';

		if (i_1 + j < 8 && i_2 - j >= 0)
			A[i_1 + j][i_2 - j] = '*';
		if (i_1 - j >= 0 && i_2 + j < 8)
			A[i_1 - j][i_2 + j] = '*';
	}

	for (int i(0); i < 8; i++)
	{
		for (int j(0); j < 8; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}


}

int main()
{
	Problem_3();
	
	system("pause");
	return 1;
}