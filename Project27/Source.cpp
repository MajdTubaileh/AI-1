#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;
class Init
{
public:
	void read(const std::string& string)
	{
		std::string temp;
		std::string a;


		int x, y;
		int count = 0;
		x = y = 0;
		std::ifstream o_file;
		o_file.open(string);
		std::getline(o_file, temp);
		size = temp[0] - '0';

		init = new char*[size];
		for (int i = 0; i < size; i++)
			init[i] = new char[size];
		goal = new char*[size];
		for (int i = 0; i < size; i++)
			goal[i] = new char[size];

		while (std::getline(o_file, temp))
		{

			int length = temp.length();
			while (count < length) {

				init[x][y] = temp[count];
				y++;
				count++;

			}

			y = 0; x++;
			count = 0;
			if (x == size)break;
		}
		x = 0;
		while (std::getline(o_file, temp))
		{
			int length = temp.length();
			while (count < length) {

				goal[x][y] = temp[count];
				y++;
				count++;

			}

			y = 0; x++;
			count = 0;
			if (x == size)break;
		}
		born();
	}
	double findPositions()
	{
		double hd = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (goal[i][j] != '-')
				{
					for (int x = 0; x < size; x++)
					{
						for (int k = 0; k < size; k++)
						{
							if (init[x][k] == goal[i][j])
								hd += hDistance(i, j, x, k);
						}

					}
				}
			}

		}
		return hd;
	}
	double checkForLeft(int x, int y, int val)
	{
		char atX = init[x][y];
		char atY = init[x][y + val];
		init[x][y] = atY;
		init[x][y + val] = atX;
		double hd = findPositions();
		init[x][y] = atX;
		init[x][y + val] = atY;
		return hd;

	}
	double checkForUp(int x, int y, int val)
	{
		char atX = init[x][y];
		char atY = init[x + val][y];
		init[x][y] = atY;
		init[x + val][y] = atX;
		double hd = findPositions();
		init[x][y] = atX;
		init[x + val][y] = atY;
		return hd;

	}
	bool notEqual()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (goal[i][j] != init[i][j])
					return false;
			}

		}
		return true;
	}
	void born()
	{
		while (!notEqual())
		{
			double less = findPositions();
			for (int i = 0; i < size; i++)
			{
				double hd = 0;
				for (int j = 0; j < size; j++)
				{
					if (init[i][j] != '-')
					{

						if (i > 0) {
							hd = checkForUp(i, j, -1);
							if (less > hd) {
								less = hd;
								id = 0;
								xId = i;
								yId = j;

							}
						}
						if (j > 0) {
							hd = checkForLeft(i, j, -1);
							if (less > hd) {
								less = hd;
								id = 1;
								xId = i;
								yId = j;

							}
						}
						if (i < size - 1) {
							hd = checkForUp(i, j, 1);
							if (less > hd) {
								less = hd;
								id = 2;
								xId = i;
								yId = j;

							}
						}
						if (j < size - 1) {
							hd = checkForLeft(i, j, 1);
							if (less > hd) {
								less = hd;
								id = 3;
								xId = i;
								yId = j;
							}
						}
					}

				}
			}
			char atX = init[xId][yId];
			if (id == 0)
			{
				char atY = init[xId - 1][yId];
				init[xId][yId] = atY;
				init[xId - 1][yId] = atX;
			}
			if (id == 1)
			{
				char atY = init[xId][yId - 1];
				init[xId][yId] = atY;
				init[xId][yId - 1] = atX;
			}
			if (id == 2)
			{
				char atY = init[xId + 1][yId];
				init[xId][yId] = atY;
				init[xId + 1][yId] = atX;
			}
			if (id == 3)
			{
				char atY = init[xId][yId + 1];
				init[xId][yId] = atY;
				init[xId][yId + 1] = atX;
			}

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					std::cout << init[i][j];
				}std::cout << std::endl;

			}
			std::cout << std::endl<< "----------------" <<std::endl <<std::endl;
		}
	}

private:
	char** init;
	char** goal;
	int size;
	int id;
	int xId, yId;
private:
	double hDistance(int x1, int y1, int x2, int y2)
	{
		return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}

};

int main()
{
	Init init;
	string string;
	cout << "file name: "; std::cin >> string; cout << std::endl;
	init.read(string);
	system("pause");
}
//EXAMPLES OF THE FILE HOW IT SHOULD BE 
/*
3 3
---
-B-
-CD
BDC
---
---
*/
//==============================================================
/*
4 4
C-D-
B---
--A-
----
----
A-D-
-BC-
----
*/
//==============================================================

//AND SO ON ..