#ifndef NCFILE_H
#define NCFILE_H

#include <vector>
#include <set>
#include "rs_block.h"
#include "rs_graphic.h"
#include "rs_arc.h"
#include "rs_circle.h"
#include "rs_insert.h"
#include "rs_math.h"
#include "rs_ellipse.h"
#include "rs_polyline.h"
#include "rs_line.h"
#include "rs_point.h"
#include "rs_vector.h"


enum COORDINATE_COMMAND {CABSOLUTE,CRELATIVE};
enum TOOL_REPAIR {NULL_TOOL_REPAIR,LEFT_TOOL_REPAIR,RIGHT_TOOL_REPAIR};


struct guideLineData
{
    bool m_is_exist=false;//�Ƿ����
    QList<RS_Entity*> m_guide_entities;//���������ӹ��Σ�����ε�һ��ʵ������ǿ����г̵��յ㣬���������һ��ʵ���յ��ǿ����г��յ�
};


//�ӹ�ʵ��
struct ncSolidData
{
    //�Ų�ǰ
    RS_Entity* m_polyline;//�ӹ���
    bool m_is_closed;//�Ƿ�Ϊ���ͼ��
    bool m_is_inner_membrane;//�Ƿ�Ϊ��Ĥͼ��,true����Ĥ

    //�����
    RS_Vector m_cutin_point;//�����
    RS_Line* m_g0_line;//g00��

    //����
    guideLineData m_in_transition_line;//������
    guideLineData m_out_transition_line;//�г���
    std::set<RS_Vector> m_cold_points;//��ȴ��
};

//ncFile����
struct ncFileData
{
    QList<ncSolidData> m_segment_file;//�ӹ���,�ӹ��ΰ����ӹ���QList<ncSolidData>���ӹ�������ӹ�ʵ��ncSolidData
    RS_Vector m_coordinate_origin;//����ԭ��
    RS_Polyline* m_back_groud;//���
};





#endif // NCFILE_H
