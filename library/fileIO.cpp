#include "../includes_usr/fileIO.h"

#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	fstream fin;
	fin.open(filename);

	if (fin.is_open()) {
		std::string line;
		bool bookLoaded = false;

		while (std::getline(fin, line)) {
			book currentBook;
			stringstream ss(line);
			string id = "";
			string state = "";
			string loaned = "";

			getline(ss, id, ',');
			getline(ss, currentBook.title, ',');
			getline(ss, currentBook.author, ',');
			getline(ss, state, ',');
			getline(ss, loaned, ',');

			currentBook.book_id = std::stoi(id);
			int mystate = std::stoi(state);

			switch (mystate) {
			case 1:
				currentBook.state = IN;
				break;
			case 2:
				currentBook.state = OUT;
				break;
			default:
				currentBook.state = UNKNOWN;
			}
			currentBook.loaned_to_patron_id = std::stoi(loaned);

			books.push_back(currentBook);
			bookLoaded = true;
		}
		fin.close();
		if (bookLoaded) {
			return SUCCESS;
		}
		return NO_BOOKS_IN_LIBRARY;
	}
	return COULD_NOT_OPEN_FILE;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	if (books.size() == 0)
		return NO_BOOKS_IN_LIBRARY;

	fstream fout;
	fout.open(filename, fstream::out);

	if (!fout.is_open())
		return COULD_NOT_OPEN_FILE;

	for (book x : books) {
		fout << x.book_id << "," << x.title << "," << x.author << ","
				<< x.state << "," << x.loaned_to_patron_id << endl;
	}
	fout.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	fstream fin;
	fin.open(filename);
	if (fin.is_open()) {
		std::string line;
		bool patronsLoaded = false;
		while (std::getline(fin, line)) {
			patron currentPatron;
			stringstream ss(line);
			string id = "";
			string checkedBooks = "";

			getline(ss, id, ',');
			getline(ss, currentPatron.name, ',');
			getline(ss, checkedBooks, ',');

			currentPatron.patron_id = std::stoi(id);
			currentPatron.number_books_checked_out = std::stoi(checkedBooks);

			patrons.push_back(currentPatron);
			patronsLoaded = true;
		}
		fin.close();

		if (patronsLoaded) {
			return SUCCESS;
		}
		return NO_PATRONS_IN_LIBRARY;
	}
	return COULD_NOT_OPEN_FILE;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	if (patrons.size() == 0)
		return NO_PATRONS_IN_LIBRARY;

	fstream fout;
	fout.open(filename, fstream::out);

	if (!fout.is_open())
		return COULD_NOT_OPEN_FILE;

	for (patron x : patrons) {
		fout << x.patron_id << "," << x.name << ","
				<< x.number_books_checked_out << endl;
	}
	fout.close();
	return SUCCESS;
}
