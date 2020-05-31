#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QFtp;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void ftpCommandFinished(int commandId, bool error);
private slots:
    void on_toolButton_clicked();

private:
    Ui::Dialog *ui;
    QFtp *ftp;
};

#endif // DIALOG_H
