#include "editordetexto.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorDeTexto w;
    w.show();
    return a.exec();
}
