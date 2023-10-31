#include "Front.h"
#include <string>

Window::Window() {
  this->create();
  this->setGeometry(100, 100, 800, 900);
  this->setWindowTitle("Notepad");

  this->addButtons();

  this->show();
};

void Window::addButtons() {
  // Вставка
  // {
  this->button_groups.push_back(new QGroupBox(this));
  this->button_groups[0]->setTitle("Вставка");

  this->button_layouts.push_back(new QVBoxLayout);
  this->button_groups[0]->setGeometry(10, 10, 150, 200);

  this->buttons.push_back(
      new QPushButton("Вставка\nодной строки", this->button_groups[0]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 20, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { insertLine(); });

  this->buttons.push_back(
      new QPushButton("Вставка\nнескольких строк", this->button_groups[0]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 80, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { insertLines(); });

  this->buttons.push_back(
      new QPushButton("Удаление\nстроки", this->button_groups[0]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 140, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { deleteLine(); });

  this->button_groups[0]->setLayout(this->button_layouts[0]);
  // }

  // Модификация
  // {
  this->button_groups.push_back(new QGroupBox(this));
  this->button_groups[1]->setTitle("Модификация");

  this->button_layouts.push_back(new QVBoxLayout);
  this->button_groups[1]->setGeometry(10, 210, 150, 200);

  this->buttons.push_back(
      new QPushButton("Вставка\nподстроки", this->button_groups[1]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 20, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { insertSubLine(); });

  this->buttons.push_back(
      new QPushButton("Замена\nсимвола", this->button_groups[1]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 80, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { setSymbol(); });

  this->buttons.push_back(
      new QPushButton("Контекстная\nзамена", this->button_groups[1]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 140, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { replaceText(); });

  this->button_groups[1]->setLayout(this->button_layouts[1]);
  // }

  // Обработка
  // {
  this->button_groups.push_back(new QGroupBox(this));
  this->button_groups[2]->setTitle("Обработка");

  this->button_layouts.push_back(new QVBoxLayout);
  this->button_groups[2]->setGeometry(10, 410, 150, 260);

  this->buttons.push_back(
      new QPushButton("Удаление\nведущих нулей", this->button_groups[2]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 20, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { deleteZeros(); });

  this->buttons.push_back(new QPushButton(
      "Удаление чисел\nс невозрастающими цифрами", this->button_groups[2]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 80, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { deleteNIncNum(); });

  this->buttons.push_back(new QPushButton("Удалить текст\nв фигурных скобках",
                                          this->button_groups[2]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 140, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { deleteParenthesis(); });

  this->buttons.push_back(
      new QPushButton("Заменить N *\nна N/2 +", this->button_groups[2]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 200, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { replaceStars(); });

  this->button_groups[2]->setLayout(this->button_layouts[2]);
  // }

  this->button_groups.push_back(new QGroupBox(this));
  this->button_groups[3]->setTitle("Файл");

  this->button_layouts.push_back(new QVBoxLayout);
  this->button_groups[3]->setGeometry(10, 670, 150, 200);

  this->buttons.push_back(new QPushButton("Открыть", this->button_groups[3]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 20, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { loadFile(); });

  this->buttons.push_back(new QPushButton("Сохранить", this->button_groups[3]));
  this->buttons[this->buttons.size() - 1]->setGeometry(0, 80, 150, 50);
  QObject::connect(this->buttons[this->buttons.size() - 1],
                   &QPushButton::clicked, [&]() { saveFile(); });

  this->button_groups[3]->setLayout(this->button_layouts[3]);

  this->text = new QTextEdit(this);
  text->setGeometry(170, 10, this->width() - 180, this->height() - 20);
  text->setReadOnly(true);

  this->updateText();
}

void Window::updateText() {
  this->text->setText("");
  for (std::wstring *curr_line : *this->data.getData()) {
    this->text->insertPlainText(QString::fromStdWString(*curr_line));
    this->text->insertPlainText("\n");
  }
}

void Window::blankWindow() {
  QWidget *wdg = new QWidget();

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  wdg->close();

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  input_layout->addWidget(cancel_button);

  wdg->show();
}

void Window::insertLine() {
  QWidget *wdg = new QWidget();

  QLabel *text_label = new QLabel(wdg);
  text_label->setFrameStyle(QFrame::Sunken);
  text_label->setText("Текст строки");
  // text_label->setGeometry(0, 0, 100, 30);

  QLineEdit *text_line = new QLineEdit(wdg);
  // text_line->setGeometry(10, 40, 200, 20);

  QLabel *num_label = new QLabel(wdg);
  num_label->setFrameStyle(QFrame::Sunken);
  num_label->setText("Номер строки");
  // text_label->setGeometry(0, 0, 100, 30);

  QSpinBox *num_line = new QSpinBox(wdg);
  num_line->setMinimum(0);
  num_line->setMaximum(this->data.getLinesNum());

  // text_line->setGeometry(10, 40, 200, 20);

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(
      done_button, &QPushButton::clicked, [&, wdg, text_line, num_line]() {
        data.insertLine(num_line->value(), text_line->text().toStdWString());
        data.splitText(this->text_edit_width);
        this->updateText();
        wdg->close();
      });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(text_label);
  input_layout->addWidget(text_line);
  input_layout->addWidget(num_label);
  input_layout->addWidget(num_line);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::insertLines() {
  QWidget *wdg = new QWidget();

  QLabel *text_label = new QLabel(wdg);
  text_label->setFrameStyle(QFrame::Sunken);
  text_label->setText("Текст");
  // text_label->setGeometry(0, 0, 100, 30);

  QTextEdit *text_edit = new QTextEdit(wdg);
  text_edit->setGeometry(10, 40, 200, 150);

  QLabel *num_label = new QLabel(wdg);
  num_label->setFrameStyle(QFrame::Sunken);
  num_label->setText("Номер строки");
  // text_label->setGeometry(0, 0, 100, 30);

  QSpinBox *num_line = new QSpinBox(wdg);
  num_line->setMinimum(0);
  num_line->setMaximum(this->data.getLinesNum());

  // text_line->setGeometry(10, 40, 200, 20);

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, text_edit, num_line]() {
                     data.insertLines(num_line->value(),
                                      text_edit->toPlainText().toStdWString());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(text_label);
  input_layout->addWidget(text_edit);
  input_layout->addWidget(num_label);
  input_layout->addWidget(num_line);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::deleteLine() {
  QWidget *wdg = new QWidget();

  QLabel *num_label = new QLabel(wdg);
  num_label->setFrameStyle(QFrame::Sunken);
  num_label->setText("Номер строки для удаления");

  QSpinBox *num_line = new QSpinBox(wdg);
  num_line->setMinimum(1);
  num_line->setMaximum(this->data.getLinesNum());

  // text_line->setGeometry(10, 40, 200, 20);

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked, [&, wdg, num_line]() {
    data.deleteLine(num_line->value());
    this->updateText();
    wdg->close();
  });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(num_label);
  input_layout->addWidget(num_line);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  // QObject::connect(this, &QPushButton::clicked, [&, wdg]() { wdg->close();
  // });

  wdg->show();
}

void Window::insertSubLine() {
  QWidget *wdg = new QWidget();

  QLabel *text_label = new QLabel(wdg);
  text_label->setFrameStyle(QFrame::Sunken);
  text_label->setText("Текст подстроки");

  QLineEdit *text_edit = new QLineEdit(wdg);
  text_edit->setGeometry(10, 40, 200, 150);

  QLabel *line_num_label = new QLabel(wdg);
  line_num_label->setFrameStyle(QFrame::Sunken);
  line_num_label->setText("Номер строки");

  QSpinBox *line_num_text = new QSpinBox(wdg);
  line_num_text->setMinimum(1);
  line_num_text->setMaximum(this->data.getLinesNum());

  QLabel *symbol_num_label = new QLabel(wdg);
  symbol_num_label->setFrameStyle(QFrame::Sunken);
  symbol_num_label->setText("Номер символа");

  QSpinBox *symbol_num_text = new QSpinBox(wdg);
  symbol_num_text->setMinimum(0);
  // symbol_num_text->setMaximum(
  // this->data.getData()[line_num_text->value() - 1].size());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, text_edit, line_num_text, symbol_num_text]() {
                     this->data.insertSubLine(line_num_text->value(),
                                              symbol_num_text->value(),
                                              text_edit->text().toStdWString());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(text_label);
  input_layout->addWidget(text_edit);
  input_layout->addWidget(line_num_label);
  input_layout->addWidget(line_num_text);
  input_layout->addWidget(symbol_num_label);
  input_layout->addWidget(symbol_num_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::setSymbol() {
  QWidget *wdg = new QWidget();

  QLabel *text_label = new QLabel(wdg);
  text_label->setFrameStyle(QFrame::Sunken);
  text_label->setText("Текст подстроки");

  QLineEdit *text_edit = new QLineEdit(wdg);
  text_edit->setGeometry(10, 40, 200, 150);

  QLabel *line_num_label = new QLabel(wdg);
  line_num_label->setFrameStyle(QFrame::Sunken);
  line_num_label->setText("Номер строки");

  QSpinBox *line_num_text = new QSpinBox(wdg);
  line_num_text->setMinimum(1);
  line_num_text->setMaximum(this->data.getLinesNum());

  QLabel *symbol_num_label = new QLabel(wdg);
  symbol_num_label->setFrameStyle(QFrame::Sunken);
  symbol_num_label->setText("Номер символа");

  QSpinBox *symbol_num_text = new QSpinBox(wdg);
  symbol_num_text->setMinimum(1);
  // symbol_num_text->setMaximum(
  // this->data.getData()[line_num_text->value() - 1].size());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, text_edit, line_num_text, symbol_num_text]() {
                     this->data.setSymbol(line_num_text->value(),
                                          symbol_num_text->value(),
                                          text_edit->text().toStdWString());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(text_label);
  input_layout->addWidget(text_edit);
  input_layout->addWidget(line_num_label);
  input_layout->addWidget(line_num_text);
  input_layout->addWidget(symbol_num_label);
  input_layout->addWidget(symbol_num_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::replaceText() {
  QWidget *wdg = new QWidget();

  QLabel *pattern_label = new QLabel(wdg);
  pattern_label->setFrameStyle(QFrame::Sunken);
  pattern_label->setText("Найти: ");

  QLineEdit *pattern_edit = new QLineEdit(wdg);

  QLabel *text_label = new QLabel(wdg);
  text_label->setFrameStyle(QFrame::Sunken);
  text_label->setText("Заменить на: ");

  QLineEdit *text_edit = new QLineEdit(wdg);

  QLabel *start_line_label = new QLabel(wdg);
  start_line_label->setFrameStyle(QFrame::Sunken);
  start_line_label->setText("Заменить между строками");

  QSpinBox *start_line_text = new QSpinBox(wdg);
  start_line_text->setMinimum(1);
  start_line_text->setMaximum(this->data.getData()->size());

  QLabel *end_line_label = new QLabel(wdg);
  end_line_label->setFrameStyle(QFrame::Sunken);
  end_line_label->setText("и");

  QSpinBox *end_line_text = new QSpinBox(wdg);
  end_line_text->setMinimum(1);
  end_line_text->setMaximum(this->data.getData()->size());
  end_line_text->setValue(this->data.getData()->size());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(
      done_button, &QPushButton::clicked,
      [&, wdg, pattern_edit, text_edit, start_line_text, end_line_text]() {
        this->data.replaceText(start_line_text->value(), end_line_text->value(),
                               pattern_edit->text().toStdWString(),
                               text_edit->text().toStdWString());
        data.splitText(this->text_edit_width);
        this->updateText();
        wdg->close();
      });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  input_layout->addWidget(pattern_label);
  input_layout->addWidget(pattern_edit);
  input_layout->addWidget(text_label);
  input_layout->addWidget(text_edit);
  input_layout->addWidget(start_line_label);
  input_layout->addWidget(start_line_text);
  input_layout->addWidget(end_line_label);
  input_layout->addWidget(end_line_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::deleteZeros() {
  QWidget *wdg = new QWidget();

  QLabel *first_line_label = new QLabel(wdg);
  first_line_label->setFrameStyle(QFrame::Sunken);
  first_line_label->setText("Убрать ведущие нули в строках с");

  QSpinBox *first_line_text = new QSpinBox(wdg);
  first_line_text->setMinimum(1);
  first_line_text->setMaximum(this->data.getLinesNum());

  QLabel *last_line_label = new QLabel(wdg);
  last_line_label->setFrameStyle(QFrame::Sunken);
  last_line_label->setText("по");

  QSpinBox *last_line_text = new QSpinBox(wdg);
  last_line_text->setMinimum(1);
  last_line_text->setMaximum(this->data.getLinesNum());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, first_line_text, last_line_text]() {
                     this->data.deleteZeros(first_line_text->value(),
                                            last_line_text->value());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(first_line_label);
  input_layout->addWidget(first_line_text);
  input_layout->addWidget(last_line_label);
  input_layout->addWidget(last_line_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::deleteNIncNum() {
  QWidget *wdg = new QWidget();

  QLabel *first_line_label = new QLabel(wdg);
  first_line_label->setFrameStyle(QFrame::Sunken);
  first_line_label->setText("Удалить цифры с невозрастающими цифрами в строке");

  QSpinBox *first_line_text = new QSpinBox(wdg);
  first_line_text->setMinimum(1);
  first_line_text->setMaximum(this->data.getLinesNum());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, first_line_text]() {
                     this->data.deleteNIncNum(first_line_text->value());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(first_line_label);
  input_layout->addWidget(first_line_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::deleteParenthesis() {
  QWidget *wdg = new QWidget();

  QLabel *first_line_label = new QLabel(wdg);
  first_line_label->setFrameStyle(QFrame::Sunken);
  first_line_label->setText("Удалить фигурные скобки в строке");

  QSpinBox *first_line_text = new QSpinBox(wdg);
  first_line_text->setMinimum(1);
  first_line_text->setMaximum(this->data.getLinesNum());

  QPushButton *cancel_button = new QPushButton("Отмена", wdg);
  cancel_button->setGeometry(10, 100, 100, 30);
  QObject::connect(cancel_button, &QPushButton::clicked,
                   [&, wdg]() { wdg->close(); });

  QPushButton *done_button = new QPushButton("Готово", wdg);
  done_button->setGeometry(120, 100, 100, 30);
  QObject::connect(done_button, &QPushButton::clicked,
                   [&, wdg, first_line_text]() {
                     this->data.deleteParenthesis(first_line_text->value());
                     data.splitText(this->text_edit_width);
                     this->updateText();
                     wdg->close();
                   });

  QVBoxLayout *input_layout = new QVBoxLayout(wdg);
  // input_layout->setGeometry(QRect(0, 0, 200, 80));
  input_layout->addWidget(first_line_label);
  input_layout->addWidget(first_line_text);
  input_layout->addWidget(cancel_button);
  input_layout->addWidget(done_button);

  wdg->show();
}

void Window::replaceStars() {
  this->data.replaceStars();
  data.splitText(this->text_edit_width);
  this->updateText();
}

void Window::loadFile() {
  QString file_name = QFileDialog::getOpenFileName(this, "Open File", "~", "*");
  data.loadFile(file_name.toStdWString());

  this->updateText();
}

void Window::saveFile() {
  QString file_name = QFileDialog::getSaveFileName(this, "Open File", "~", "*");
  data.saveFile(file_name.toStdWString());
  this->updateText();
}
