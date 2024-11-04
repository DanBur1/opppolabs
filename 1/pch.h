#ifndef PCH_H
#define PCH_H

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

extern map<string, int> commandMap;
extern map<color, string> colorMap;
extern map<penType, string> typeMap;

class OfficeSupplies {
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

class Pencil : public OfficeSupplies {
private:
  int density;
  color pencil_color;

public:
  Pencil(float p, const string &phone, int d, color pc)
      : OfficeSupplies(p, phone), density(d), pencil_color(pc) {}
  void displayInfo() const override;
};

class Pen : public OfficeSupplies {
private:
  penType type;
  float diam;

public:
  Pen(float p, const string &phone, const penType &t, float d)
      : OfficeSupplies(p, phone), type(t), diam(d) {}
  void displayInfo() const override;
};

class Paper : public OfficeSupplies {
private:
  int density;
  int width;
  int length;

public:
  Paper(float p, const string &phone, int d, int w, int h)
      : OfficeSupplies(p, phone), density(d), width(w), length(h) {}
  void displayInfo() const override;
};

color stringToColor(const string &str);
void processCommand(const string &command);

extern vector<OfficeSupplies *> supplies;
#endif // PCH_H
