#include "../pch.h"
#include <Windows.h>
#include <gtest/gtest.h>

//Создание через конструктор и вывод через метод
TEST(OfficeSuppliesTest, PencilCreation) {
  Pencil pencil(10.0f, "1234567890", 2, red);

  testing::internal::CaptureStdout();
  pencil.displayInfo();

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Карандаш"), std::string::npos);
}

TEST(OfficeSuppliesTest, PenCreation) {
  Pen pen(15.0f, "0987654321", ball, 0.5f);

  testing::internal::CaptureStdout();
  pen.displayInfo();

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Ручка"), std::string::npos);
}

TEST(OfficeSuppliesTest, PaperCreation) {
  Paper paper(20.0f, "1122334455", 80, 210, 297);

  testing::internal::CaptureStdout();
  paper.displayInfo();

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Бумага"), std::string::npos);
}

//Цвета

TEST(stringToColorTest, redTest) {
  color res=stringToColor("red");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST(stringToColorTest, orangeTest) {
  color res = stringToColor("orange");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("1"), std::string::npos);
}

TEST(stringToColorTest, yellowTest) {
  color res = stringToColor("yellow");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("2"), std::string::npos);
}

TEST(stringToColorTest, greenTest) {
  color res = stringToColor("green");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("3"), std::string::npos);
}

TEST(stringToColorTest, blueTest) {
  color res = stringToColor("blue");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("4"), std::string::npos);
}

TEST(stringToColorTest, purpleTest) {
  color res = stringToColor("purple");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("5"), std::string::npos);
}

TEST(stringToColorTest, pinkTest) {
  color res = stringToColor("pink");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("6"), std::string::npos);
}

TEST(stringToColorTest, whiteTest) {
  color res = stringToColor("white");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("7"), std::string::npos);
}

TEST(stringToColorTest, blackTest) {
  color res = stringToColor("black");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("8"), std::string::npos);
}

TEST(stringToColorTest, brownTest) {
  color res = stringToColor("brown");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("9"), std::string::npos);
}

TEST(stringToColorTest, grayTest) {
  color res = stringToColor("gray");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("10"), std::string::npos);
}

TEST(stringToColorTest, noncoloredTest) {
  color res = stringToColor("non-colored");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("11"), std::string::npos);
}

//Неправильные цвета

TEST(stringToColorTest, otherColorTest) {
  color res = stringToColor("cyan");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("11"), std::string::npos);
}

TEST(stringToColorTest, RedTest) {
  color res = stringToColor("Red");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("11"), std::string::npos);
}

TEST(stringToColorTest, REDTest) {
  color res = stringToColor("RED");

  testing::internal::CaptureStdout();
  cout << res;

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("11"), std::string::npos);
}

//Команды

TEST(ProcessCommandTests, AddPaper) {

  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Paper 370,5 555-4823 72 210 297");

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Бумага | Плотность: 72г/м2 | Ширина : 210мм | Длина : 297мм"),
            std::string::npos);
}

TEST(ProcessCommandTests, AddPencilNonColored) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pencil 15 555-3485 4 Non-colored");

  string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Карандаш | Плотность грифеля: 4 | Цвет: non-colored"),
            std::string::npos);
}

TEST(ProcessCommandTests, AddPenBallpoint) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pen 20 555-2106 Ballpoint 2");

  string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Ручка | Тип ручки: ballpoint | Диаметр стержня: 2мм"),
            std::string::npos);
}

TEST(ProcessCommandTests, AddPencilRed) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pencil 15.55 555-3485 2 Red");

  string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Карандаш | Плотность грифеля: 2 | Цвет: red"),
            std::string::npos);
}

TEST(ProcessCommandTests, AddPenGel) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pen 20 555-2106 Gel 2");

  string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Ручка | Тип ручки: gel | Диаметр стержня: 2мм"),
            std::string::npos);
}

TEST(ProcessCommandTests, AddMultiplePencils) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pencil 15 555-3485 4 Orange");
  processCommand("add Pencil 15 555-3485 1 Yellow");

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Карандаш | Плотность грифеля: 4 | Цвет: orange"),
            std::string::npos);
  EXPECT_NE(output.find("Карандаш | Плотность грифеля: 1 | Цвет: yellow"),
            std::string::npos);
}

TEST(ProcessCommandTests, RemoveItem) {
  supplies.clear();
  processCommand("add Paper 300 555-4823 80 210 297");
  processCommand("rem 0");
  testing::internal::CaptureStdout();

  processCommand("print");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output.find("Бумага | Плотность: "), std::string::npos); 
}


TEST(ProcessCommandTests, PrintEmptyList) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("print");

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Вывод:"), std::string::npos);
}

TEST(ProcessCommandTests, ExitCommand) {
  ASSERT_NO_THROW(processCommand("exit"));
}

//Неправильные команды

TEST(ProcessCommandTests, WrongCommand) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("ad Pencil 15,5 555-3463 1 Red");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Неправильная команда."), std::string::npos);
}

TEST(ProcessCommandTests, WrongClass) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pnecil 15,5 555-3463 1 Red");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Неправильно указан класс предмета"), std::string::npos);
}

TEST(ProcessCommandTests, WrongNumParameters) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pencil 15,5 1 Red");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Неверное количество параметров"),
            std::string::npos);
}

TEST(ProcessCommandTests, WrongPen) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pen 20,5 555-2353 Ballpoin 3,5");

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Некорректный тип ручки:"),
            std::string::npos);
}

TEST(ProcessCommandTests, WrongDiameter) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pen 20,5 555-2353 Ballpoint З,5");

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Некорректный диаметр:"),
            std::string::npos);
}

TEST(ProcessCommandTests, WrongDensity) {
  supplies.clear();
  testing::internal::CaptureStdout();
  processCommand("add Pencil 15,5 555-3463 l Red");

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Некорректная плотность:"),
            std::string::npos);
}

TEST(ProcessCommandTests, RemoveNE) {
  supplies.clear();
  processCommand("add Paper 300 555-4823 80 210 297");
  testing::internal::CaptureStdout();
  processCommand("rem 1");

  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Попытка удаления несуществующего предмета"),
            std::string::npos);
}

TEST(ProcessCommandTests, RemoveWrongId) {
  supplies.clear();
  processCommand("add Paper 300 555-4823 80 210 297");
  testing::internal::CaptureStdout();
  processCommand("rem paper");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("Некорректный ID:"),
            std::string::npos);
}

int main(int argc, char **argv) {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
