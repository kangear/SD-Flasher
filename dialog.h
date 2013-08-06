#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setQTabeWadget();
    void setScanItems();
    
private slots:
    void on_pBut_Fuse_clicked();

    void on_pBut_Scan_clicked();

    void on_pBut_Brose_clicked();

    void on_tWid_scan_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
