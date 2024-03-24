#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

struct Worker {
	std::string name;
	int id;
	bool shift; // true - дневная
	double salary;


};
bool operator<(const Worker& a, const Worker& b){
	return a.id < b.id;
}

void PrintWorker(const Worker& tmp)
{
	std::cout << "Name: " << tmp.name << '\t'
		<< "id: " << tmp.id << '\t'
		<< "shift: " << tmp.shift << '\t'
		<< "salary: " << tmp.salary << std::endl;
}


int main(){
	setlocale(LC_ALL, "ru");
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	const int quantity = 20;
	std::vector<Worker> workers;

	//Создаем случайных сотрудников
	for (int i = 0; i < quantity; i++)
	{
		Worker tmp;
		tmp.id = i + 1;
		tmp.name = "Сотрудник " + std::to_string(tmp.id);
		tmp.shift = rand() % 2 == 0;
		tmp.salary = rand() % 90000 + 10000;
		workers.push_back(tmp);
	}
	std::cout << "Все сотруники: \n";
	for (const auto& i : workers) 
	{
		PrintWorker(i);
	}
	
	// Разделяем ночных и дневных сотрудников 
	std::vector<Worker> dayShift;
	std::vector<Worker> nightShift;
	
	for (const auto& i : workers)
	{
		if (i.shift) { dayShift.push_back(i); }
		else { nightShift.push_back(i); }
	}

	std::cout << "Сотруники дневной смены: \n";
	for (const auto& i : dayShift)
	{
		PrintWorker(i);
	}

	std::cout << "Сотруники ночной смены: \n";
	for (const auto& i : nightShift)
	{
		PrintWorker(i);
	}
	std::cout << "\n\n";

	// Выводим топы сотрудников с макс ЗП
	// отсортируем списки для простоты вывода

	std::sort(workers.begin(), workers.end(), [](const Worker& a, Worker& b) 
		{return a.salary > b.salary; });

	std::sort(dayShift.begin(), dayShift.end(), [](const Worker& a, Worker& b)
		{return a.salary > b.salary; });

	std::sort(nightShift.begin(), nightShift.end(), [](const Worker& a, Worker& b)
		{return a.salary > b.salary; });

	std::cout << "3 сотрудника с самой высокой зарплатой из всего списка сотрудников: \n";
	for (int i = 0; i < 3; i++)
	{
		PrintWorker(workers[i]);
	}
	std::cout << "\n";

	std::cout << "3 сотрудника с самой высокой зарплатой из списка дневных сотрудников: \n";
	for (int i = 0; i < 3; i++)
	{
		PrintWorker(dayShift[i]);
	}
	std::cout << "\n";

	std::cout << "3 сотрудника с самой высокой зарплатой из списка ночных сотрудников: \n";
	for (int i = 0; i < 3; i++)
	{
		PrintWorker(nightShift[i]);
	}
	std::cout << "\n";

	//Записываем в файл топы сотрудников

	std::ofstream file("Top.txt");
	if (!file.is_open()) 
	{
		std::cerr << "Error!\n";
	}
	else
	{
		file << "3 сотрудника с самой высокой зарплатой из всего списка сотрудников: \n";
		for (int i = 0; i < 3; i++)
		{
			file << "Name: " << workers[i].name << '\t'
				<< "id: " << workers[i].id << '\t'
				<< "shift: " << workers[i].shift << '\t'
				<< "salary: " << workers[i].salary
				<< std::endl;
		}
		file << "========================================================================\n";

		file << "3 сотрудника с самой высокой зарплатой из списка дневных сотрудников: \n";
		for (int i = 0; i < 3; i++)
		{
			file << "Name: " << dayShift[i].name << '\t'
				<< "id: " << dayShift[i].id << '\t'
				<< "shift: " << dayShift[i].shift << '\t'
				<< "salary: " << dayShift[i].salary
				<< std::endl; 
		}
		file << "========================================================================\n";

		file << "3 сотрудника с самой высокой зарплатой из списка ночных сотрудников: \n";
		for (int i = 0; i < 3; i++)
		{
			file << "Name: " << nightShift[i].name << '\t'
				<< "id: " << nightShift[i].id << '\t'
				<< "shift: " << nightShift[i].shift << '\t'
				<< "salary: " << nightShift[i].salary 
				<< std::endl; 
		}
		file << "========================================================================\n";
		file.close();
	}


	// теперь топы  минимальными ЗП

	std::cout << "3 сотрудника с самой низкой зарплатой из списка всех сотрудников: \n";
	for (int i = workers.size() - 3; i < workers.size(); i++)
	{
		PrintWorker(workers[i]);
	}
	std::cout << "\n";


	std::cout << "3 сотрудника с самой низкой зарплатой из списка дневных сотрудников: \n";
	for (int i = dayShift.size() - 3; i < dayShift.size(); i++)
	{
		PrintWorker(dayShift[i]);
	}
	std::cout << "\n";


	std::cout << "3 сотрудника с самой низкой зарплатой из списка ночных сотрудников: \n";
	for (int i = nightShift.size() - 3; i < nightShift.size(); i++)
	{
		PrintWorker(nightShift[i]);
	}
	std::cout << "\n";

	//добавляем топ с низкими зп в существующий файл


	std::ofstream file2("Top.txt", std::ios::app);
	if (!file2.is_open())
	{
		std::cerr << "Error!\n";
	}
	else
	{
		file2 << "3 сотрудника с самой низкой зарплатой из всего списка сотрудников: \n";
		for (int i = workers.size() - 3; i < workers.size(); i++)
		{
			file2 << "Name: " << workers[i].name << '\t'
				<< "id: " << workers[i].id << '\t'
				<< "shift: " << workers[i].shift << '\t' 
				<< "salary: " << workers[i].salary
				<< std::endl;
		}
		file2 << "========================================================================\n";

		file2 << "3 сотрудника с самой низкой зарплатой из списка дневных сотрудников: \n";
		for (int i = dayShift.size() - 3; i < dayShift.size(); i++)
		{
			file2 << "Name: " << dayShift[i].name << '\t'
				<< "id: " << dayShift[i].id << '\t'
				<< "shift: " << dayShift[i].shift << '\t'
				<< "salary: " << dayShift[i].salary
				<< std::endl;
		}
		file2 << "========================================================================\n";

		file2 << "3 сотрудника с самой низкой зарплатой из списка ночных сотрудников: \n";
		for (int i = nightShift.size() - 3; i < nightShift.size(); i++)
		{
			file2 << "Name: " << nightShift[i].name << '\t'
				<< "id: " << nightShift[i].id << '\t'
				<< "shift: " << nightShift[i].shift << '\t'
				<< "salary: " << nightShift[i].salary
				<< std::endl;
		}
		file2.close();
	}

	//Считываем из нашего файла записи и оставляем только уникальные

	std::ifstream file3("Top.txt");
	if (!file3.is_open())
	{
		std::cerr << "Error!\n";
	}

	std::set<Worker> uniqueWorkers;
	std::string line;
	while (std::getline(file3, line))
	{
		std::istringstream ss(line);
		std::string temp;

		Worker emp;
		ss >> temp >> temp >> emp.name >> temp >> emp.id >> temp >> emp.shift >> temp >> emp.salary;
		uniqueWorkers.insert(emp);
	}
	file3.close();

	for (const auto& emp : uniqueWorkers) 
	{
		PrintWorker(emp);
	}	

	return 0; 
} 