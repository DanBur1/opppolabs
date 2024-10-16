/*COPYRIGHT YEAR NO COPYRIGHT*/
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
