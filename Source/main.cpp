#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow window;
  window.setWindowTitle("Пример окна Qt");
  window.setGeometry(100, 100, 400,
                     200); // Устанавливаем размер и положение окна
  window.show();

  return app.exec();
}
