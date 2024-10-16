/*COPYRIGHT YEAR NO COPYRIGHT*/
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

enum color {
  red,
  orange,
  yellow,
  green,
  blue,
  purple,
  pink,
  white,
  black,
  brown,
  gray,
  none
};
enum penType { ball, gel };

map<string, int> commandMap = {
    {"add", 1}, {"rem", 2}, {"print", 3}, {"help", 4}};
map<color, string> colorMap = {
    {red, "red"},     {orange, "orange"}, {yellow, "yellow"},
    {green, "green"}, {blue, "blue"},     {purple, "purple"},
    {pink, "pink"},   {white, "white"},   {black, "black"},
    {brown, "brown"}, {gray, "gray"},     {none, "non-colored"}};
map<penType, string> typeMap = {{ball, "ballpoint"}, {gel, "gel"}};

class OfficeSupplies
{
private:
  float price;
  string phone_number;

public:
  OfficeSupplies() : price(0), phone_number("") {}

  OfficeSupplies(float p, const string &phone)
      : price(p), phone_number(phone) {}

  virtual void displayInfo() const {
    cout << "Цена: " << price << "руб. | Номер владельца: " << phone_number
         << " |";
  }
};

class Pencil : public OfficeSupplies
{
private:
  int density;
  color pencil_color;

public:
  Pencil(float p, const string &phone, int d, color pc)
      : OfficeSupplies(p, phone), density(d), pencil_color(pc) {}
  void displayInfo() const override {
    OfficeSupplies::displayInfo();
    cout << " Карандаш | Плотность грифеля: " << density
         << " | Цвет: " << colorMap[pencil_color] << endl;
  }
};

class Pen : public OfficeSupplies
{
private:
  penType type;
  float diam;

public:
  Pen(float p, const string &phone, const penType &t, float d)
      : OfficeSupplies(p, phone), type(t), diam(d) {}
  void displayInfo() const override {
    OfficeSupplies::displayInfo();
    cout << " Ручка | Тип ручки: " << typeMap[type]
         << " | Диаметр стержня: " << diam << "мм " << endl;
  }
};

class Paper : public OfficeSupplies
{
private:
  int density;
  int width;
  int length;

public:
  Paper(float p, const string &phone, int d, int w, int h)
      : OfficeSupplies(p, phone), density(d), width(w), length(h) {}

  void displayInfo() const override {
    OfficeSupplies::displayInfo();
    cout << " Бумага | Плотность: " << density << "г/м2 | Ширина : " << width
         << "мм | Длина : " << length << "мм" << endl;
  }
};

vector<OfficeSupplies *> supplies;

color stringToColor(string str);
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

  for (auto ptr : supplies) {
    delete ptr;
  }

  return 0;
}

color stringToColor(string str) {
  for (const auto &pair : colorMap)
    if (pair.second == str) {
      return pair.first;
    }

  return none;
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
  // add
  case 1: {
    if (parameters.size() < 3) {
      cout << "Не указаны параметры" << endl;
      return;
    }

    float param_price;

    try {
      param_price = stof(parameters[2]);
    } catch (invalid_argument &) {
      cout << "Некорректная цена: " << parameters[2] << endl;
      return;
    }

    if (parameters[1] == "pencil") {
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

      color param_color = stringToColor(parameters[5]);

      Pencil *sup =
          new Pencil(param_price, parameters[3], param_density, param_color);

      supplies.push_back(sup);

      cout << "Добавлен ";
      sup->displayInfo();

    } else if (parameters[1] == "pen") {
      if (parameters.size() != 6) {
        cout << "Неверное количество параметров" << endl;
        return;
      }

      penType param_type;

      if (parameters[4] == "ballpoint")
        param_type = ball;
      else if (parameters[4] == "gel")
        param_type = gel;
      else {
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

      Pen *sup = new Pen(param_price, parameters[3], param_type, param_diam);

      supplies.push_back(sup);

      cout << "Добавлен ";

      sup->displayInfo();

    } else if (parameters[1] == "paper") {
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

      Paper *sup = new Paper(param_price, parameters[3], param_density,
                             param_width, param_length);

      supplies.push_back(sup);

      cout << "Добавлен ";

      sup->displayInfo();

    } else {
      cout << "Неправильно указан класс предмета" << endl;
      return;
    }

    break;
  }

  // rem
  case 2: {
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

    supplies[id]->displayInfo();

    supplies.erase(supplies.begin() + id);

    break;
  }

  // print
  case 3: {
    cout << "Вывод:" << endl;

    for (int i = 0; i < supplies.size(); i++) {
      supplies[i]->displayInfo();
    }

    cout << endl;

    break;
  }

  // help
  case 4: {
    cout << "Редактор списка канцелярских принадлежностей." << endl
         << "Используются "
         << "4 комманды: add (Добавить), rem (Удалить), print "
            "(Вывести), exit (Выход)."
         << endl
         << "Имеется "
         << "3 типа принадлежностей: Pencil (Карандаш), Pen (Ручка), "
         << "Paper (Бумага)." << endl
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
