#ifndef PTSHOWNCFILE_H
#define PTSHOWNCFILE_H

#include <QThread>
#include <QEventLoop>
#include <QCloseEvent>
#include "qc_applicationwindow.h"
#include "rs_document.h"
#include "ncfile.h"
#include  "QTimer"
#include "pt_algcommon.h"

class QC_ApplicationWindow;

class ptShowNcFile
{
public:
    ptShowNcFile();
    ptShowNcFile(RS_Graphic* _Graphic);

public:
    //׼��ͼ��
    void prepare_layers();

    //���»�������
    void redraw_ncfile();

    void set_plank(double,double);

    //����������Ϣ
    //void reshow_all();

    //��ʾ����,32������
     void set_show_or_hide(int controlSingal);

private:
     //����һ����graphc�йܵ�copy
     RS_Entity* get_entity_copy(std::shared_ptr<RS_Entity> in);


private:
    RS_Graphic* m_graphic;


public:
    std::shared_ptr<ncFileData> m_ncFile;
};


class ptAnimationThread : public QThread
{
public:
     ptAnimationThread()
     {
     };

    ~ptAnimationThread()
     {
//         graphic->removeEntity(m_cross_line1);
//         graphic->removeEntity(m_cross_line2);
     };

public:
    //��ʼ����
    void run();

public:

    //��ʼ
    void start(){m_time_out=false;m_stopFlag=false;};

    //��ͣ
    void time_out(){m_time_out=true;};

    //ֹͣ
    void stop(){m_stopFlag=true;m_time_out=true;};

    //���ý���,ֻ������Ϊ0~1
    //TODO
    void set_schedule(double _radio);

    //�����ٶ�0~10��
    void set_speed(int _speed);

public:
    //���ô���ʾ�ļ�
    void set_nc_file(const ncFileData& inPut);

    //���ncFileɾ���ڴ�
    void clear_nc_file();

public:
    RS_Line* m_cross_line1=nullptr;
    RS_Line* m_cross_line2=nullptr;

private:
    //���̲߳���
    QEventLoop m_event;

    //�ٶ�
    int  m_speed=4;

    //ֹͣ��ʶ
    bool m_stopFlag=true;

    //��ͣ��ʶ
    bool m_time_out=true;

    //��ʼ��
    bool isin=false;

    //��������
    RS_Vector m_start_point;

    //����ʾ��ֱ�߶Σ����е����ݶ������߶�������
    QList<RS_Line*> m_show_line_pack;

    //��ͼָ��
    RS_Graphic* graphic;

};

#endif // PTSHOWNCFILE_H
