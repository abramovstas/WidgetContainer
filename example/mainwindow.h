#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widgetcontainer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_load_clicked();

    void on_btn_save_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
