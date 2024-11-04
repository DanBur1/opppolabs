/*COPYRIGHT YEAR NO COPYRIGHT*/

#include "pch.h"

map<string, int> commandMap = {
    {"add", 1}, {"rem", 2}, {"print", 3}, {"help", 4}};
map<color, string> colorMap = {
    {red, "red"},     {orange, "orange"}, {yellow, "yellow"},
    {green, "green"}, {blue, "blue"},     {purple, "purple"},
    {pink, "pink"},   {white, "white"},   {black, "black"},
    {brown, "brown"}, {gray, "gray"},     {none, "non-colored"}};
map<penType, string> typeMap = {{ball, "ballpoint"}, {gel, "gel"}};

void Pencil::displayInfo() const {
  OfficeSupplies::displayInfo();
  cout << " �������� | ��������� �������: " << density
       << " | ����: " << colorMap[pencil_color] << endl;
}

void Pen::displayInfo() const {
  OfficeSupplies::displayInfo();
  cout << " ����� | ��� �����: " << typeMap[type]
       << " | ������� �������: " << diam << "�� " << endl;
}

void Paper::displayInfo() const {
  OfficeSupplies::displayInfo();
  cout << " ������ | ���������: " << density << "�/�2 | ������ : " << width
       << "�� | ����� : " << length << "��" << endl;
}

color stringToColor(const string &str);
void processCommand(const string &command);

color stringToColor(const string &str) {
  for (const auto &pair : colorMap)
    if (pair.second == str) {
      return pair.first;
    }

  return none;
}

vector<OfficeSupplies *> supplies;

void processCommand(const string &command) {
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
      cout << "�� ������� ���������" << endl;
      return;
    }

    float param_price;

    try {
      param_price = stof(parameters[2]);
    } catch (invalid_argument &) {
      cout << "������������ ����: " << parameters[2] << endl;
      return;
    }

    if (parameters[1] == "pencil") {
      if (parameters.size() != 6) {
        cout << "�������� ���������� ����������" << endl;
        return;
      }

      int param_density;

      try {
        param_density = stoi(parameters[4]);
      } catch (invalid_argument &) {
        cout << "������������ ���������: " << parameters[4] << endl;
        return;
      }

      color param_color = stringToColor(parameters[5]);

      Pencil *sup =
          new Pencil(param_price, parameters[3], param_density, param_color);

      supplies.push_back(sup);

      cout << "�������� ";
      sup->displayInfo();

    } else if (parameters[1] == "pen") {
      if (parameters.size() != 6) {
        cout << "�������� ���������� ����������" << endl;
        return;
      }

      penType param_type;

      if (parameters[4] == "ballpoint") {
        param_type = ball;
      } else if (parameters[4] == "gel") {
        param_type = gel;
      } else {
        cout << "������������ ��� �����: " << parameters[4] << endl;
        return;
      }

      float param_diam;

      try {
        param_diam = stof(parameters[5]);
      } catch (invalid_argument &) {
        cout << "������������ �������: " << parameters[5] << endl;
        return;
      }

      Pen *sup = new Pen(param_price, parameters[3], param_type, param_diam);

      supplies.push_back(sup);

      cout << "�������� ";

      sup->displayInfo();

    } else if (parameters[1] == "paper") {
      if (parameters.size() != 7) {
        cout << "�������� ���������� ����������" << endl;
        return;
      }

      int param_density, param_width, param_length;

      try {
        param_density = stoi(parameters[4]);
        param_width = stoi(parameters[5]);
        param_length = stoi(parameters[6]);
      } catch (invalid_argument &) {
        cout << "������������ ��������� ������." << endl;
        return;
      }

      Paper *sup = new Paper(param_price, parameters[3], param_density,
                             param_width, param_length);

      supplies.push_back(sup);

      cout << "�������� ";

      sup->displayInfo();

    } else {
      cout << "����������� ������ ����� ��������" << endl;
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
      cout << "������������ ID: " << parameters[1] << endl;
      return;
    }

    if (id >= supplies.size()) {
      cout << "������� �������� ��������������� ��������" << endl;
      break;
    }

    cout << "������� ��� ������� " << id << " ����� �����." << endl
         << "�������� ";

    supplies[id]->displayInfo();

    supplies.erase(supplies.begin() + id);

    break;
  }

  // print
  case 3: {
    cout << "�����:" << endl;

    for (int i = 0; i < supplies.size(); i++) {
      supplies[i]->displayInfo();
    }

    cout << endl;

    break;
  }

  // help
  case 4: {
    cout << "�������� ������ ������������ ���������������." << endl
         << "������������ "
         << "4 ��������: add (��������), rem (�������), print "
            "(�������), exit (�����)."
         << endl
         << "������� "
         << "3 ���� ���������������: Pencil (��������), Pen (�����), "
         << "Paper (������)." << endl
         << "��������� �������:" << endl
         << "add Pencil <����> <��������> <��������� �������> <����>" << endl
         << "add Pen <����> <��������> <��� �����> <������� �������>" << endl
         << "add Paper <����> <��������> <���������> <������> <������>" << endl
         << "rem <������ ��������>" << endl
         << "print" << endl;

    break;
  }

  default: {
    cout << "������������ �������." << endl;
  }
  }
}
