#ifndef PTDLGCOLDPOINTS_H
#define PTDLGCOLDPOINTS_H

#include <QDialog>
#include "sinsun/xstest/ncfile.h"

namespace Ui {
class ptdlgcoldpoints;
}

class ptdlgcoldpoints : public QDialog
{
    Q_OBJECT

public:
    explicit ptdlgcoldpoints(QWidget *parent = nullptr);
    ~ptdlgcoldpoints();

    //�´��ڷ��й�ģʽ
    void prepare_date();

private slots:
    //��ʼѡ��ť
    void on_pushButtonSelectColdPointsManually_clicked();

    //����ѡ��ť
    void on_pushButtonFinishSelectColdPointsManually_clicked();

    //�Զ�ѡ��ť
    void on_pushButtonSelectColdPointsAutoly_clicked();

    //�����ȴ��
    void on_pushButtonDeleteColdPoints_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ptdlgcoldpoints *ui;

private:
    QList<ncSolidData*> m_processedNcFile;

public:
    std::shared_ptr<ncFileData> m_ncFile;
};

#endif // PTDLGCOLDPOINTS_H
