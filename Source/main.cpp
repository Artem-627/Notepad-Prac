#include "Front.h"
#include <QApplication>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QWidget>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // std::cout << "hello" << '\n';
  // Window window(argc, argv, 100, 100, 100, 400, QString("Notepad"));
  Window window;
  // QApplication app(argc, argv);

  // QWidget window;
  // window.setWindowTitle("Notepad");
  // window.setGeometry(100, 100, 800, 600);
  //
  // QPushButton button("Button 1", &window);
  // button.setGeometry(0, 0, 100, 30);
  // QObject::connect(&button, &QPushButton::clicked,
  //                  [&]() { std::cout << "Pressed on button 1" << std::endl;
  //                  });
  // QPushButton button2("Button 2", &window);
  // button2.setGeometry(0, 30, 100, 30);
  // QObject::connect(&button2, &QPushButton::clicked,
  //                  [&]() { std::cout << "Pressed on button 2" << std::endl;
  //                  });
  //
  // QGroupBox button_group_1(&window);
  // button_group_1.setTitle("Group 1");
  //
  // QVBoxLayout layout_1(&window);
  // layout_1.addWidget(&button);
  // layout_1.addWidget(&button2);
  //
  // button_group_1.setLayout(&layout_1);
  // window.show();
  //
  return app.exec();
}
