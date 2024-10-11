/*Copyright [year] <Copyright Owner>*/
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::invalid_argument;
using std::map;
using std::string;
using std::vector;

map<string, int> commandMap = {
    {"add", 1}, {"rem", 2}, {"print", 3}, {"help", 4}};

struct Supply {
  string type = "";
  float price = 0;
  string phone_number = "";
  vector<string> attributes;
};

vector<Supply> supplies;

void displayInfo(const Supply &supply);
void processCommand(string command);

int main() {
  setlocale(LC_ALL, "RU");
  string console_trash;
  string command;
  string filename;
  ifstream file;
  cout << "1 - консольный режим, 2 - режим файла" << endl;
  int option;
  cin >> option;
  getline(cin, console_trash);
  switch (option) {
  case 1:
    while (true) {
      getline(cin, command);
      if (command == "exit") {
        cout << "Завершаю работу";
        break;
      }
      processCommand(command);
    }
    break;
  case 2:
    cout << "Введите название файла (/ConsoleApplication5/command_input.txt - "
            "по умолчанию)";
    getline(cin, filename);
    if (filename.empty())
      filename = "command_input.txt";
    file.open(filename);
    if (!file.is_open()) {
      cerr << "Ошибка: не удалось открыть файл \"" << filename << "\"" << endl;
      return 1;
    }
    while (getline(file, command)) {
      if (command == "exit") {
        cout << "Завершаю работу" << endl;
        break;
      }
      processCommand(command);
    }
    break;
  default:
    cout << "Нет такого варианта." << endl;
  }
  return 0;
}

void displayInfo(const Supply &supply) {
  cout << "Тип: " << supply.type << " | Цена: " << supply.price
       << "р | Владелец: " << supply.phone_number;
  if (supply.type == "pencil") {
    cout << " | Плотность: " << supply.attributes[0]
         << " | Цвет: " << supply.attributes[1];
  }
  if (supply.type == "pen") {
    cout << " | Тип: " << supply.attributes[0]
         << " | Диаметр: " << supply.attributes[1] << "мм";
  }
  if (supply.type == "paper") {
    cout << " | Плотность: " << supply.attributes[0]
         << "г/м2 | Ширина листа: " << supply.attributes[1]
         << "мм | Высота листа : " << supply.attributes[2] << "мм";
  }
  cout << endl;
}

void processCommand(string command) {
  vector<string> parameters;
  size_t start = 0;
  size_t end = command.find(' ');

  while (end != std::string::npos) {
    parameters.push_back(command.substr(start, end - start));
    start = end + 1;
    end = command.find(' ', start);
  }
  parameters.push_back(command.substr(start));
  for (int j = 0; j < parameters.size(); j++)
    for (int i = 0; i < size(parameters[j]); i++) {
      parameters[j][i] = tolower(parameters[j][i]);
    }
  switch (commandMap[parameters[0]]) {
  case 1:  // add
  {
    if (parameters.size() < 3) {
      cout << "Не указаны параметры" << endl;
      return;
    }
    Supply newSupply;
    newSupply.type = parameters[1];
    try {
      newSupply.price = stof(parameters[2]);
    } catch (invalid_argument &) {
      cout << "Некорректная цена: " << parameters[2] << endl;
      return;
    }
    newSupply.phone_number = parameters[3];
    if (newSupply.type == "pencil") {
      if (parameters.size() != 6) {
        cout << "Неверное количество параметров" << endl;
        return;
      }
      int param_density;
      try {
        param_density = stoi(parameters[4]);
      } catch (invalid_argument &) {
        cout << "Некорректная плотность: " << parameters[4] << endl;
        return;
      }
      newSupply.attributes.push_back(std::to_string(param_density));
      newSupply.attributes.push_back(parameters[5]);
      supplies.push_back(newSupply);
      cout << "Добавлен ";
      displayInfo(newSupply);
    } else if (newSupply.type == "pen") {
      if (parameters.size() != 6) {
        cout << "Неверное количество параметров" << endl;
        return;
      }
      if (!(parameters[4] == "ballpoint" || parameters[4] == "gel")) {
        cout << "Некорректный тип ручки: " << parameters[4] << endl;
        return;
      }
      float param_diam;
      try {
        param_diam = stof(parameters[5]);
      } catch (invalid_argument &) {
        cout << "Некорректный диаметр: " << parameters[5] << endl;
        return;
      }
      newSupply.attributes.push_back(parameters[4]);
      newSupply.attributes.push_back(std::to_string(param_diam));
      supplies.push_back(newSupply);
      cout << "Добавлен ";
      displayInfo(newSupply);
    } else if (newSupply.type == "paper") {
      if (parameters.size() != 7) {
        cout << "Неверное количество параметров" << endl;
        return;
      }
      int param_density, param_width, param_length;

      try {
        param_density = stoi(parameters[4]);
        param_width = stoi(parameters[5]);
        param_length = stoi(parameters[6]);
      } catch (invalid_argument &) {
        cout << "Некорректные параметры бумаги." << endl;
        return;
      }
      newSupply.attributes.push_back(std::to_string(param_density));
      newSupply.attributes.push_back(std::to_string(param_width));
      newSupply.attributes.push_back(std::to_string(param_length));
      supplies.push_back(newSupply);
      cout << "Добавлен ";
      displayInfo(newSupply);
    } else {
      cout << "Неправильно указан класс предмета" << endl;
      return;
    }
    break;
  }
  case 2: {   // rem
    int id;
    try {
      id = stoi(parameters[1]);
    } catch (invalid_argument &) {
      cout << "Некорректный ID: " << parameters[1] << endl;
      return;
    }
    if (id >= supplies.size()) {
      cout << "Попытка удаления несуществующего предмета" << endl;
      break;
    }
    cout << "Предмет под номером " << id << " будет удалён." << endl
         << "Удаление ";
    displayInfo(supplies[id]);
    supplies.erase(supplies.begin() + id);
    break;
  }
  case 3:  // print
  {
    cout << "Вывод:" << endl;
    for (int i = 0; i < supplies.size(); i++) {
      displayInfo(supplies[i]);
    }
    cout << endl;
    break;
  }
  case 4: // help
  {
    cout << "Редактор списка канцелярских принадлежностей." << endl
         << "Используются 4 комманды: add (Добавить), rem (Удалить), print "
            "(Вывести), exit (Выход)."
         << endl
         << "Имеется 3 типа принадлежностей: Pencil (Карандаш), Pen (Ручка), "
            "Paper (Бумага)."
         << endl
         << "Синтаксис комманд:" << endl
         << "add Pencil <Цена> <Владелец> <Плотность грифеля> <Цвет>" << endl
         << "add Pen <Цена> <Владелец> <Тип ручки> <Диаметр стержня>" << endl
         << "add Paper <Цена> <Владелец> <Плотность> <Ширина> <Высота>" << endl
         << "rem <Индекс элемента>" << endl
         << "print" << endl;
    break;
  }
  default: {
    cout << "Неправильная комманда." << endl;
  }
  }
}
