#include "View/Windows/MainWindow.h"
#include "Handler/Handler.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Handler handler(9, 3);
  MainWindow main_window(&handler);
  main_window.show();

  return app.exec();
}
