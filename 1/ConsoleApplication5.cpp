/*COPYRIGHT YEAR NO COPYRIGHT*/

#include "pch.h"

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
