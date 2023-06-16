#include <string>

class Book
{
	std::string authorName;
	std::string bookName;
	int year;
	int pages;

public:

	Book(std::string authorName = "", std::string bookName = "", int year = 1970, int pages = 300)
	{
		this->authorName = authorName;
		this->bookName = bookName;
		this->year = year;
		this->pages = pages;
	}


	bool operator<(Book& right)
	{
		if (this->authorName == right.authorName)
		{
			if (this->bookName == right.bookName)
			{
				if (this->year == right.year)
					return false;

				return this->year < right.year;
			}

			return this->bookName < right.bookName;
		}

		return this->authorName < right.authorName;
	}

	bool operator>(Book& right)
	{
		if (this->authorName == right.authorName)
		{
			if (this->bookName == right.bookName)
			{
				if (this->year == right.year)
					return false;

				return this->year > right.year;
			}

			return this->bookName > right.bookName;
		}

		return this->authorName > right.authorName;
	}

	bool operator<=(Book& right)
	{
		if (this->authorName == right.authorName)
		{
			if (this->bookName == right.bookName)
			{
				if (this->year == right.year)
					return true;

				return this->year < right.year;
			}

			return this->bookName < right.bookName;
		}

		return this->authorName < right.authorName;
	}

	bool operator>=(Book& right)
	{
		if (this->authorName == right.authorName)
		{
			if (this->bookName == right.bookName)
			{
				if (this->year == right.year)
					return true;

				return this->year > right.year;
			}

			return this->bookName > right.bookName;
		}

		return this->authorName > right.authorName;
	}
};