#include "dialog.h"
#include "ui_dialog.h"
#include "qftp.h"
#include <QDirIterator>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(ftpCommandFinished(int,bool)));
    //登录
    ftp->connectToHost("", 21);
    ftp->login("spygg", "");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_toolButton_clicked()
{
    QString ftpPath = "d:/qt-everywhere-src-5.15.0/";

    QDir dir(ftpPath);
    if(!dir.exists()){
        return;
    }

    //获取所选文件类型过滤器
    QStringList filters;
    filters << QString("*.*");

    qint64 maxUpload = 0;
    //定义迭代器并设置过滤器
    QDirIterator dirIter(ftpPath, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirIter.hasNext()){
        dirIter.next();

        QFileInfo fi = dirIter.fileInfo();
        QString fileName = fi.absoluteFilePath();
        QString dFileName = fi.fileName();
        QFile *file = new QFile(fileName, ftp);
        ftp->put(file, dFileName);


    }
}


void Dialog::ftpCommandFinished(int commandId, bool error)
{
    Q_UNUSED(commandId);

    QFtp *ftp = qobject_cast<QFtp *>(sender());

    if(ftp->currentCommand() == QFtp::Login){
        if (error) {
            qDebug() << "ftp登录失败" << ftp->errorString();

            ftp->abort();
            ftp->deleteLater();
            ftp = Q_NULLPTR;
        }
    }
    else if (ftp->currentCommand() == QFtp::Put) {
        if (!error) {
            //关闭文件,删除指针
            QFile *file =  qobject_cast<QFile*>(ftp->currentDevice());
            if(file){
                QString fileName = file->fileName();

                file->close();
                file->deleteLater();

                qDebug() << "" << fileName;
            }
        }
        else{
            QFile *file =  qobject_cast<QFile*>(ftp->currentDevice());
            if(file){
                file->close();
                file->deleteLater();
            }

            qDebug() <<  QString("上传发生错误, ip: %1, 错误原因: %2")
                         .arg(ftp->property("ip").toString())
                         .arg(ftp->errorString());
        }
    }
    else if (ftp->currentCommand() == QFtp::Get) {
        if (!error) {
            QFile *file =  qobject_cast<QFile*>(ftp->currentDevice());
            if(file){
                qDebug() << file->fileName() << "下载文件传输完毕";
                file->close();
                file->deleteLater();
            }
        }
    }
}
