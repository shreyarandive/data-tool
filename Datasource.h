#pragma once
#include<map>
using namespace std;

class Datasource
{
	private:

	int total;
	int total_columns = 0;
	vector<string> filename;
	vector<int>rows;
	vector<int>columns;
	vector<vector<int>> data;
	bool allColumnsEqual = true;
	bool allRowsEqual = true;

	bool readData(string name)
	{
		ifstream fin;
		fin.open(name);
		vector<int> dataArray;
		int row = 0, number = 0;
        
		fin >> row;

		while (fin >> number)
		{
			dataArray.push_back(number);
		}
        
		if (!checkRowColumnValid(row, int(dataArray.size())))
			return false;

		data.push_back(dataArray);

		return true;
	}

	void appendData(int columns)
	{
		for (int i = 0 ; i < data.size() ; i++)
		{
			int n = 1;
			for (int j = 0 ; j < data[i].size() ; j++)
			{
				cout << data[i][j] << "\t";

				if (n == columns)
				{
					cout << endl;
					n = 0;
				}
				n++;
			}
		}
		cout << endl;
	}

	void combineData(int column)
	{
		for (int i = 0; i < rows[0]; i++)
		{
			for (int j = 0; j < columns.size(); j++)
			{
				for (int k = 0; k < columns[j]; k++)
					cout << data[j][k + (columns[j] * i)] << "\t";
			}
			cout << endl;
		}
		
		cout << endl;
	}

	void sumData(int rows, int columns)
	{
		vector<int>sum(rows*columns, 0);

		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].size(); j++)
			{
				sum[j] += data[i][j];
			}
		}

		int n = 1;
		for (int j = 0; j < sum.size(); j++)
		{
			cout << sum[j] << "\t";

			if (n == columns)
			{
				cout << endl;
				n = 0;
			}
			n++;
		}
		cout << endl;
	}

	bool checkRowColumnValid(int row, int size)
	{
		if (row <= 0)
		{
			cout << "Invalid File!" << endl;
			return false;
		}
		else
		{
			if(rows.empty() || !allRowsEqual)
				rows.push_back(row);
			else
			{
				if (row != rows.back())
					allRowsEqual = false;
				rows.push_back(row);
			}
		}

		if (size == 0 || size % row != 0)
		{
			cout << "Invalid data!" << endl;
			return false;
		}
		else
		{
			int column = size / row;
			if (columns.empty() || !allColumnsEqual)
				columns.push_back(column);
			else
			{
				if (column != columns.back())
					allColumnsEqual = false;
				columns.push_back(column);
			}

			total_columns += column;
		}
        return true;
	}

	public:

	bool addFilename(string name)
	{
		filename.push_back(name);
		return readData(name);
	}

	void executeOperation(string command)
	{
		if (command == "APPEND")
		{
			if (!allColumnsEqual)
				cout << "Cannot execute this operations, columns not equal" << endl;
			else
			{
				appendData(columns[0]);
			}
		}
		else if (command == "COMBINE")
		{
			if (!allRowsEqual)
				cout << "Cannot execute this operations, rows not equal" << endl;
			else
				combineData(total_columns);
		}
		else if (command == "SUM")
		{
			if (!allColumnsEqual || !allRowsEqual)
				cout << "Cannot execute this operations, rows and columns not equal" << endl;
			else
				sumData(rows[0], columns[0]);
		}
		else
		{
			cout << "Invalid Operation!" << endl;
			return;
		}
	}
};
