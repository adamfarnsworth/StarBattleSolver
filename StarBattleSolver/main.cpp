#include<iostream>
#include<vector>
#include <algorithm> 


int size = 1;
int stars = 0;

struct collumnCount {
	int place;
	int count;
};


void buildConsole(int &size, int &stars) {
	std::cout << "Enter Size of your star system:" << std::endl;
	std::cin >> size;

	while (!std::cin || size < 5) {	//making sure input is valid
		std::cin.clear();    // Restore input stream to working state
		std::cin.ignore(100, '\n'); // Get rid of any garbage that user might have entered

		std::cout << "Make sure your system is larger 4" << std::endl;
		std::cout << "Enter size of your star system: " << std::endl;
		std::cin >> size;
	}

	std::cout << std::endl << "Nice, that's a really good sized star system!" << std::endl;
	std::cout << "Enter the number of stars per row/collumn, make sure it's less than " << size / 5 + 1 << " : " << std::endl;

	std::cin >> stars;

	while (!std::cin || stars > size / 5 || stars == 0) {	//making sure input is valid
		std::cin.clear();    // Restore input stream to working state
		std::cin.ignore(100, '\n'); // Get rid of any garbage that user might have entered

		std::cout << "Make sure the amount of stars you want is less than " << size / 5 + 1 << " and you didnt enter 0" << std::endl;
		std::cout << "Enter the number of stars per row/collumn: " << std::endl;
		std::cin >> stars;
	}

}

int main() {

	buildConsole(size, stars);




	std::vector<collumnCount> collumns;
	std::vector<collumnCount> tempDeletedCollumns;
	std::vector<int> currentRow(size);
	std::vector<int> previousRow(size);

	for (int i = 0; i < size; i++) {
		collumns.push_back(collumnCount());
		collumns[i].count = stars;
		collumns[i].place = i;
	}

	std::random_shuffle(collumns.begin(), collumns.end());
	//std::cout << std::endl;
	//for (int c : collumns)
	//	std::cout << c;
	//std::cout << std::endl;

	int starCount = 0;

	// itteration though all the rows
	for (int r = 0; r < size; r++) {
		std::random_shuffle(collumns.begin(), collumns.end());

		previousRow = currentRow;
		std::fill(currentRow.begin(), currentRow.end(), 0);

		// itteration though the current row
		for (int i = 0; i < collumns.size(); i++) {
			// previous row has no star above
			if (previousRow[collumns[i].place] == 0) {
				// case: first in the row
				if (collumns[i].place == 0) {
					if (previousRow[1] == 0 && currentRow[1] == 0) {
						currentRow[0] = 1;
						starCount++;
						if (collumns[i].count > 1)
							collumns[i].count--;
						else {
							tempDeletedCollumns.push_back(collumns[i]);
							collumns.erase(collumns.begin() + i);
							i--;
						}
					}
				}
				// case: last in the row
				else if (collumns[i].place == size - 1) {
					if (previousRow[size - 2] == 0 && currentRow[size - 2] == 0) {
						currentRow[size - 1] = 1;
						starCount++;
						if (collumns[i].count > 1)
							collumns[i].count--;
						else {
							tempDeletedCollumns.push_back(collumns[i]);
							collumns.erase(collumns.begin() + i);
							i--;
						}
					}
				}
				// case: and "middle" places star can go
				else if (previousRow[collumns[i].place] == 0 && previousRow[collumns[i].place - 1] == 0 && previousRow[collumns[i].place + 1] == 0
					&& currentRow[collumns[i].place] == 0 && currentRow[collumns[i].place - 1] == 0 && currentRow[collumns[i].place + 1] == 0) {
					currentRow[collumns[i].place] = 1;
					starCount++;
					if (collumns[i].count > 1)
						collumns[i].count--;
					else {
						tempDeletedCollumns.push_back(collumns[i]);
						collumns.erase(collumns.begin() + i);
						i--;
					}
				}
			}

			// enough stars have been entered
			if (starCount == stars) {
				tempDeletedCollumns.clear();
				for (int j : currentRow)
					if (j == 0)
						std::cout << ".";
					else
						std::cout << "*";
				std::cout << std::endl;
				starCount = 0;
				break;
			}

			// forces it to find the correct positions, could cause infinite loop
			if (starCount != stars && i == collumns.size() - 1) {
				for (collumnCount x : tempDeletedCollumns)
					collumns.push_back(x);
				tempDeletedCollumns.clear();
				// reset and try again
				std::random_shuffle(collumns.begin(), collumns.end());
				std::fill(currentRow.begin(), currentRow.end(), 0);
				i = 0;
				starCount = 0;
			}
		}

	}
	std::cout <<"wow you made a really cool galaxy! "<< std::endl;
	system("pause");
}