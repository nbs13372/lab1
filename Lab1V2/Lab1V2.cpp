#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


/*!
	\brief Класс, задающий книгу в библиотеке
*/
class Book
{
public:

	std::string authorName; ///< Имя автора
	std::string bookName; ///< Название книги
	int year; ///< Год публикации
	int pages; ///< Число страниц


	/*!
		Создает объект Book
		\param[in] authorName Имя автора
		\param[in] bookName Название книги
		\param[in] year Год публикации
		\param[in] pages Число страниц
		\return Возвращает объект Book
	*/
	Book(std::string authorName = "", std::string bookName = "", int year = 1970, int pages = 300)
	{
		this->authorName = authorName;
		this->bookName = bookName;
		this->year = year;
		this->pages = pages;
	}

	/*!
		Оператор сравнения меньше
		\param[in] right правое сравниваемое значение
		\return Возвращает true, если левый объект строго меньше, false - иначе
	*/
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

	/*!
		Оператор сравнения больше
		\param[in] right правое сравниваемое значение
		\return Возвращает true, если левый объект строго больше, false - иначе
	*/
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

	/*!
		Оператор сравнения меньше или равно
		\param[in] right правое сравниваемое значение
		\return Возвращает true, если левый объект меньше или равен, false - иначе
	*/
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

	/*!
		Оператор сравнения больше или равно
		\param[in] right правое сравниваемое значение
		\return Возвращает true, если левый объект больше или равен, false - иначе
	*/
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


/*!
	\brief Класс, содержащий реализуемые сортировки
*/
class Sorting
{
public:

	/*!
		Сортировка пузырьком	
		\param[in] data Сортируемый массив
		\param[in] n Число элементов в массиве
	*/
	static void bubbleSort(Book* data, int n)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (data[j] > data[j + 1])
					std::swap(data[j], data[j + 1]);
			}
		}

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Bubble sort, " << n << " elements, " << (double)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())/1000 << "ms\n";

	}

	/*!
		Пирамидальная сортировка
		\param[in] data Сортируемый массив
		\param[in] n Число элементов в массиве
	*/
	static void heapSort(Book* data, int n)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		for (int i = n / 2 - 1; i >= 0; i--)
		{
			downHeap(data, i, n);
		}

		for (int i = n - 1; i > 0; i--)
		{
			std::swap(data[i], data[0]);
			downHeap(data, 0, i);
		}

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Heap sort, " << n << " elements, " << (double)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000 << "ms\n";
	}

	/*!
		Оболочка для быстрой сортировки
		\param[in] data Сортируемый массив
		\param[in] n Число элементов в массиве
	*/
	static void quickSort(Book* data, int n)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		quickSortHandler(data, 0, n - 1);

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Quick sort, " << n << " elements, " << (double)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000 << "ms\n";
	}

private:

	/*!
		Просеивание элементов для создания кучи
		\param[in] data Сортируемый массив
		\param[in] start Индекс просеиваемого элемента
		\param[in] n Число элементов в массиве
	*/
	static void downHeap(Book* data, int start, int n)
	{
		Book now_elem = data[start];
		int child = 2 * start + 1;
		if (child < n - 1 && data[child] < data[child + 1])
			child++;

		if (now_elem < data[child])
		{
			data[start] = data[child];
			data[child] = now_elem;

			if (2 * child + 1 < n)
				downHeap(data, child, n);
		}
	}

	/*!
		Просеивание элементов для создания кучи
		\param[in] data Сортируемый массив
		\param[in] start Индекс начала сортировки
		\param[in] end Индекс конца сортировки
	*/
	static void quickSortHandler(Book* data, int start, int end)
	{
		int i = start, j = end;

		Book p = data[(start + end) / 2];

		while (i < j)
		{
			while (data[i] < p) i++;
			while (data[j] > p) j--;

			if (i < j)
				std::swap(data[i], data[j]);
		}

		if (j > start) quickSortHandler(data, start, j - 1);
		if (i < end) quickSortHandler(data, i + 1, end);
	}
};


/*!
		Основной метод программы
		\return Код завершения программы
*/
int main()
{
	int sizes[9] = {100, 1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};

	for (int size : sizes)
	{
		std::ifstream in;
		in.open("data_" + std::to_string(size) + ".txt");
		Book* data = new Book[size];

		for (int i = 0; i < size; i++)
		{
			std::string authorName, bookName;
			int year, pages;
			in >> authorName >> bookName >> year >> pages;

			data[i] = Book(authorName, bookName, year, pages);
		}

		in.close();

		Sorting::bubbleSort(data, size);

		std::ofstream out;
		out.open("BubbleData\\data_" + std::to_string(size) + ".csv");

		for (int i = 0; i < size; i++)
		{
			out << data[i].authorName << ";" << data[i].bookName << ";" << data[i].year << ";" << data[i].pages << "\n";
		}

		out.close();

		in.open("data_" + std::to_string(size) + ".txt");

		for (int i = 0; i < size; i++)
		{
			std::string authorName, bookName;
			int year, pages;
			in >> authorName >> bookName >> year >> pages;

			data[i] = Book(authorName, bookName, year, pages);
		}

		in.close();

		Sorting::heapSort(data, size);

		out.open("HeapData\\data_" + std::to_string(size) + ".csv");

		for (int i = 0; i < size; i++)
		{
			out << data[i].authorName << ";" << data[i].bookName << ";" << data[i].year << ";" << data[i].pages << "\n";
		}

		out.close();

		in.open("data_" + std::to_string(size) + ".txt");

		for (int i = 0; i < size; i++)
		{
			std::string authorName, bookName;
			int year, pages;
			in >> authorName >> bookName >> year >> pages;

			data[i] = Book(authorName, bookName, year, pages);
		}

		in.close();

		Sorting::quickSort(data, size);

		out.open("QuickData\\data_" + std::to_string(size) + ".csv");

		for (int i = 0; i < size; i++)
		{
			out << data[i].authorName << ";" << data[i].bookName << ";" << data[i].year << ";" << data[i].pages << "\n";
		}

		out.close();
	}
}


//Создание файлов с данными
/*std::string genString()
{
	int i = std::rand() % 50 + 10;

	std::string result = "";

	for (int k = 0; k < i; k++)
	{
		char l = std::rand() % 26 + 0x41;
		result.append(std::string(1, l));
	}

	return result;
}

std::string creatOne()
{
	return genString() + " " + genString() + " " + std::to_string(std::rand() % 50 + 1970) + " " + std::to_string(std::rand() % 999 + 1) + "\n";
}*/
