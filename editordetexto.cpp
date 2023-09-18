#include "editordetexto.h"
#include "ui_editordetexto.h"

EditorDeTexto::EditorDeTexto(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorDeTexto)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);//para o Text Edit ter tamaanho dinamico e pegar o tamanho da janela certinho
}

EditorDeTexto::~EditorDeTexto()
{
    delete ui;
}


void EditorDeTexto::on_actionNovo_triggered(){
    localfilename = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();//pro cursor vir certinho pro inicio do ponto 0
}


void EditorDeTexto::on_actionAbrir_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Abrir", QDir::homePath(), all_files);
    QFile file(filename);
    localfilename = filename;

    if (file.exists()){
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this, "Erro ao Abrir Arquivo", "Arquivo nao pode ser aberto");
            return;
        }

        QTextStream enter_file(&file);//o arquivo entra na area de transferencia (buffer)
        QString text = enter_file.readAll();
        ui->textEdit->setText(text);
    }

    file.close();
}


void EditorDeTexto::on_actionSalvar_como_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, "Salvar Como", QDir::homePath(), all_files);
    localfilename = filename;

    if(localfilename == ""){
        return;
    }

    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text)){
        if(file.exists()){
            QMessageBox::warning(this, "Erro ao Salvar Arquivo", "Arquivo nao pode ser Salvo");
        }
        return;
    }

    QTextStream out_file(&file);//o arquivo entra na area de transferencia (buffer)
    QString text = ui->textEdit->toPlainText();
    out_file << text << '\n';//para concatenar os valores ao arquivo presente

    file.flush();//limpa o conteudo
    file.close();
}


void EditorDeTexto::on_actionSalvar_triggered(){

    QFile file(localfilename);

    if(file.exists()){
            if(!file.open(QFile::WriteOnly | QFile::Text)){
                QMessageBox::warning(this, "Erro", "Arquivo não pode ser Salvo");
                return;
            }

        QTextStream out_file(&file);
        QString text = ui->textEdit->toPlainText();
        out_file << text << '\n';

        file.flush();
        file.close();
    }else{
        on_actionSalvar_como_triggered();
    }

}


void EditorDeTexto::on_actionSair_triggered(){
    close();
}


void EditorDeTexto::on_actionCopiar_triggered(){
    ui->textEdit->copy();
}


void EditorDeTexto::on_actionColar_triggered(){
    ui->textEdit->paste();
}


void EditorDeTexto::on_actionRecortar_triggered(){
    ui->textEdit->cut();
}


void EditorDeTexto::on_actionRefazer_triggered(){
    ui->textEdit->redo();
}


void EditorDeTexto::on_actionDesfazer_triggered(){
    ui->textEdit->undo();
}


void EditorDeTexto::on_actionCor_triggered(){
    QColor color = QColorDialog::getColor(Qt::black, this, "Escolha uma Cor");
    if (color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}


void EditorDeTexto::on_actionBackground_triggered(){
    QColor color = QColorDialog::getColor(Qt::black, this, "Escolha uma Cor");
    if (color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void EditorDeTexto::on_actionFonte_triggered(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }else{
        return;
    }
}


void EditorDeTexto::on_actionSobre_triggered(){
    QMessageBox::about(this, "Sobre esse Programa", "Desenvolvido no Curso de Qt Moderno com C++.<br>"
                                                    "<a href='https://google.com.br/'>Acesse</a><br>");
}


void EditorDeTexto::on_actionImprimir_triggered(){
    QPrinter printer;//impressora
    QPrintDialog dialog_printer;

    if(dialog_printer.exec() == QDialog::Rejected){
        return;
    }

    ui->textEdit->print(&printer);
}

