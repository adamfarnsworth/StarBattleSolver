#pragma once
#include<vector>
#include<iostream>

class StarSystem
{
public:
	void insertRow();
	StarSystem(int size, int stars);
	~StarSystem();

private:
	int size;
	int stars;
	std::vector<int> collumns;

	struct row {
		row* previous;
		row* next;
		std::vector<int> rows;
	};
};

