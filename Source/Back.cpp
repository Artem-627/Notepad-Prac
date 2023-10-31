#include "Back.h"
#include <fstream>
#include <iostream>
#include <string>

Content::Content() {}

int Content::getLinesNum() { return this->data.size(); }

void Content::insertLine(int index, std::wstring line) {
  this->data.insert(this->data.begin() + index, new std::wstring(line));
}

void Content::insertLines(int index, std::wstring line) {
  std::wstringstream line_stream;
  line_stream << line;
  std::wstring curr_line;
  int curr_index = 0;
  while (std::getline(line_stream, curr_line)) {
    this->data.insert(this->data.begin() + index + (curr_index++),
                      new std::wstring(curr_line));
  }
}

void Content::deleteLine(int index) {
  --index;
  delete this->data[index];
  this->data.erase(this->data.begin() + index);
}

void Content::insertSubLine(int line_index, int symbol_index,
                            std::wstring text) {
  --line_index;

  this->data[line_index]->insert(symbol_index, text);
}

void Content::setSymbol(int line_index, int symbol_index, std::wstring text) {
  --line_index;
  --symbol_index;

  *(this->data[line_index]->begin() + symbol_index) = *text.begin();
}

void Content::replaceText(int first_line_index, int last_line_index,
                          std::wstring pattern, std::wstring text) {
  --first_line_index;
  --last_line_index;

  for (int curr_line = first_line_index; curr_line <= last_line_index;
       ++curr_line) {
    int start_index;
    while (start_index = this->data[curr_line]->find(pattern),
           start_index != -1) {
      this->data[curr_line]->replace(start_index, pattern.length(), text);
    }
  }
}

void Content::deleteZeros(int first_line_index, int last_line_index) {
  --first_line_index;
  --last_line_index;

  for (int curr_line = first_line_index; curr_line <= last_line_index;
       ++curr_line) {
    for (int i = 0; i < this->data[curr_line]->size(); ++i) {
      if (*(this->data[curr_line]->begin() + i) == '0') {
        if (i + 1 == this->data[curr_line]->size()) {
          continue;
        } else if (*(this->data[curr_line]->begin() + i + 1) - 48 < 10) {
          if (*(this->data[curr_line]->begin() + i + 1) - 48 < 10) {
            this->data[curr_line]->erase(i, 1);
            --i;
          }
        } else {
          continue;
        }
      }
    }
  }
}

void Content::deleteNIncNum(int line_index) {
  --line_index;
  int curr_start_num = -1;
  int curr_length = 0;
  int prev_num = -1;
  bool is_erase = 0;
  for (int curr_symbol = 0; curr_symbol < this->data[line_index]->size();
       ++curr_symbol) {
    if (*(this->data[line_index]->begin() + curr_symbol) - 48 >= 10) {
      if (curr_start_num != -1 && is_erase) {
        this->data[line_index]->erase(curr_start_num, curr_length);
        curr_symbol -= curr_length;
      }
      curr_start_num = -1;
      curr_length = 0;
      prev_num = -1;
    } else {
      curr_start_num = (curr_start_num == -1) ? curr_symbol : curr_start_num;
    }
    std::cout << *(this->data[line_index]->begin() + curr_symbol) << '\n';
  }
}

void Content::deleteParenthesis(int line_index) {
  --line_index;
  bool is_erase = 0;
  for (int curr_symbol = 0; curr_symbol < this->data[line_index]->size();
       ++curr_symbol) {
    if (*(this->data[line_index]->begin() + curr_symbol) == wchar_t('{')) {
      is_erase = 1;
    }

    if (is_erase) {
      this->data[line_index]->erase(curr_symbol, 1);
      --curr_symbol;
    }

    if (*(this->data[line_index]->begin() + curr_symbol + 1) == wchar_t('}')) {
      this->data[line_index]->erase(curr_symbol + 1, 1);
      is_erase = 0;
    }
  }
}

void Content::replaceStars() {
  int curr_stars_long = 0;
  for (int curr_line = 0; curr_line < this->data.size(); ++curr_line) {
    for (int curr_symbol = 0; curr_symbol < this->data[curr_line]->length();
         ++curr_symbol) {
      // std::wcout << *(this->data[curr_line]->begin() + curr_symbol) << ' ';
      if (*(this->data[curr_line]->begin() + curr_symbol) == wchar_t('*') &&
          curr_symbol != this->data[curr_line]->length() - 1) {
        ++curr_stars_long;
      } else {
        if (curr_stars_long != 0) {
          int is_end = (curr_symbol == this->data[curr_line]->length() - 1);
          this->data[curr_line]->erase(curr_symbol - curr_stars_long,
                                       curr_stars_long + is_end);
          curr_symbol -= curr_stars_long;

          std::string str_plus = "+";
          std::wstring plus(str_plus.begin(), str_plus.end());
          for (int i = 0; i < (curr_stars_long + is_end) / 2; ++i) {
            this->data[curr_line]->insert(curr_symbol++, plus);
          }

          curr_stars_long = 0;
        }
      }
    }
    curr_stars_long = 0;
  }
}

void Content::splitText(int line_width) {
  for (int curr_line = 0; curr_line < this->data.size(); ++curr_line) {
    if (this->data[curr_line]->length() > line_width) {
      this->data.insert(
          this->data.begin() + curr_line + 1,
          new std::wstring(this->data[curr_line]->begin() + line_width,
                           this->data[curr_line]->end()));
      this->data[curr_line]->erase(line_width,
                                   this->data[curr_line]->size() - line_width);
    }
  }
}

void Content::loadFile(std::wstring file) {
  std::wcout << "Open: " << file << '\n';
  this->data.clear();

  std::wifstream fin(std::string(file.begin(), file.end()));

  std::wstring line;

  while (std::getline(fin, line)) {
    std::wcout << line << '\n';
    insertLine(this->data.size(), line);
  }

  fin.close();
}

void Content::saveFile(std::wstring file) {
  std::wcout << "Save: " << file << '\n';

  std::wofstream fout(std::string(file.begin(), file.end()));

  std::string str_endl = "\n";
  std::wstring endl(str_endl.begin(), str_endl.end());

  for (std::wstring *line : this->data) {
    fout << *line;
    fout << endl;
  }

  fout.close();
}
