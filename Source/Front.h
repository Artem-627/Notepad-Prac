#pragma once

#include <QApplication>
#include <QBoxLayout>
#include <QDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QSpinBox>
#include <QTextEdit>
#include <QWidget>
#include <iostream>
#include <string>
#include <vector>

#include "Back.h"

class Window : QMainWindow {
public:
  Window();

private:
  QWidget *window;
  std::vector<QPushButton *> buttons;
  std::vector<QGroupBox *> button_groups;
  std::vector<QVBoxLayout *> button_layouts;
  Content data;
  QTextEdit *text;
  const int text_edit_width = 100;

  void addButtons();

  void blankWindow();

  void insertLine();
  void insertLines();
  void deleteLine();

  void insertSubLine();
  void setSymbol();
  void replaceText();

  void deleteZeros();
  void deleteNIncNum();
  void deleteParenthesis();
  void replaceStars();

  void saveFile();
  void loadFile();

  void updateText();
};
