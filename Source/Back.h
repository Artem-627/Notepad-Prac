#include <sstream>
#include <string>
#include <strstream>
#include <vector>

class Content {
public:
  Content();

  std::vector<std::wstring *> *getData() { return &this->data; }

  void insertLine(int index, std::wstring line);
  void insertLines(int index, std::wstring line);
  void deleteLine(int index);

  void insertSubLine(int line_index, int symbol_index, std::wstring text);
  void setSymbol(int line_index, int symbol_index, std::wstring text);
  void replaceText(int first_line_index, int last_line_index,
                   std::wstring pattern, std::wstring text);

  void deleteZeros(int first_line_index, int last_line_index);
  void deleteNIncNum(int line_index);

  void deleteParenthesis(int line_index);
  void replaceStars();

  void loadFile(std::wstring file);
  void saveFile(std::wstring file);

  int getLinesNum();

  void splitText(int line_width);

private:
  std::vector<std::wstring *> data;
};
