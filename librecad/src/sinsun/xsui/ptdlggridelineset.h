#ifndef PTDLGGRIDELINESET_H
#define PTDLGGRIDELINESET_H

#include <QDialog>

#include "Qlist.h"
#include "sinsun/xstest/ncfile.h"

struct guidelineparameter
{
    guidelineparameter(int val0=0,double val1=0,double val2=0,double val3=-1){m_type=val0;m_lineLength=val1;m_Angle=val2;m_circleRadius=val3;};
    int m_type=0;//0��ʾ�ޣ�1��ʾֱ�ߣ�2��ʾԲ����3��ʾֱ��+Բ��
    double m_lineLength=0;//���߳���
    double m_Angle=0;//����Ƕ�
    double m_circleRadius=-1;//-1��ʾû��Բ
};

namespace Ui {
class ptdlggridelineset;
}

class ptdlggridelineset : public QDialog
{
    Q_OBJECT

public:
    explicit ptdlggridelineset(QWidget *parent = nullptr);
    ~ptdlggridelineset();
    int totalheight;

private slots:
    void on_buttonBox_accepted();

    void on_comboBoxInLineType_currentIndexChanged(int index);

    void on_comboBoxOutLineType_currentIndexChanged(int index);

    void button1Slot();
    void button2Slot();
    void button3Slot();
    void button4Slot();
//    void accept() override;
//    void reject() override;

private:
    //׼������
    void prepare_date();

    //��������
    QList<QList<RS_Entity*>> generate_guide_lines(const guidelineparameter& val);

private:
    Ui::ptdlggridelineset *ui;

private:
    //��Ӧ�������ļ�,i��ӦҪ�޸Ķε�λ��
    QList<ncSolidData*> m_processedNcFile;

    //������
    QList<ncSolidData*> m_processedNcFileNext;

public:

    std::shared_ptr<ncFileData> m_ncFile;

    //��������
    void set_yin_cut();

    //��������
    void set_yang_cut();
};

#endif // PTDLGGRIDELINESET_H
