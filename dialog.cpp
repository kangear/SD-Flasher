#include "dialog.h"
#include "ui_dialog.h"
#include "datastruct.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include <QTableWidget>
#include <QScrollBar>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    init();
    ui->setupUi(this);
    setQTabeWadget();


}

Dialog::~Dialog()
{
    free(upan);
    delete ui;
}

void Dialog::on_pBut_Fuse_clicked()
{
    char buf2[100]={0};
    if(!ui->lineEdit_path->text().length())
    {
      sprintf(buf2, "Fusing...\nError: Cannot Access Image File\n----");
    }
    else
    {
        ui->textEdit_fush->clear();
        ui->textEdit_fush->setTextColor(QColor("black"));
        const char* dir = NULL;
        QByteArray ba = ui->lineEdit_path->text().toLocal8Bit();
        dir=ba.data();
        fuse(upan, dir, buf2);
    }

    ui->textEdit_fush->append(QString(buf2));

    //scrollbar to end!
    QScrollBar* scrollbar = ui->textEdit_fush->verticalScrollBar();
    scrollbar->setSliderPosition(scrollbar->maximum());
}

void Dialog::on_pBut_Scan_clicked()
{
    char buf[50]={0};
    ui->tWid_scan->clear();
    if(scan(upan))
    {
        setScanItems();
    }
    sprintf(buf, "Scanning...\nFound %d Disk(s)\n----", usb_num);
    ui->textEdit_fush->setTextColor(QColor("black"));
    ui->textEdit_fush->setText(QString(buf));

}

void Dialog::on_pBut_Brose_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setDirectory(".");
    fileDialog->setFilter(tr("Image Files(*.*)"));
    if(fileDialog->exec() == QDialog::Accepted)
    {
           QString path = fileDialog->selectedFiles()[0];
           ui->lineEdit_path->setText(path);
    }
}

void Dialog::setQTabeWadget()
{
    int i = 0;

    for(i=0; i<6; i++)
        ui->tWid_scan->header()->setResizeMode(i, QHeaderView::Fixed);

    ui->tWid_scan->header()->setMovable(FALSE);
    ui->tWid_scan->setColumnWidth(0, 100);
    ui->tWid_scan->setColumnWidth(1, 100);
    ui->tWid_scan->setColumnWidth(2, 70);
    ui->tWid_scan->setColumnWidth(3, 100);
    ui->tWid_scan->setColumnWidth(4, 70);
    ui->tWid_scan->setColumnWidth(5, 30);

    ui->tWid_scan->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
    ui->tWid_scan->setSelectionMode(QAbstractItemView::SingleSelection);//只能单选

    ui->tWid_scan->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条


}

void Dialog::setScanItems()
{
    int i = 0;
    char buf[6] = {0};
    for(i=0; i<usb_num; i++)
    {
        sprintf(buf, "Disk%d", i);
        QTreeWidgetItem* disk=new QTreeWidgetItem(ui->tWid_scan);
        disk->setText(0,upan[i].dev_node);
        disk->setText(1, buf);

        sc[i] = (unsigned int)disk;
    }
}

void Dialog::on_tWid_scan_itemClicked(QTreeWidgetItem *item, int column)
{
    int i = 0;
    for (i=0; i<usb_num; i++)
    {
        if ((unsigned int)item == sc[i])
            choose_num = i;
    }
    qDebug("choose_num = %d", choose_num);
}
