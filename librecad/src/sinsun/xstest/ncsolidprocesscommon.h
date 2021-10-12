#ifndef NCSOLID_H
#define NCSOLID_H

#include <vector>
#include <memory>
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
#include "ncfile.h"

using std::vector;
using std::set;
using std::shared_ptr;
using std::make_shared;

class ncSolidProcessCommon
{
private:
    ncSolidData m_solid;
public:
    ncSolidProcessCommon();
    ncSolidProcessCommon(ncSolidData val){m_solid=val;}

    //���������,��ԭ�����������޸�
    ncSolidData caculate_left_refpoints();

    //Ѱ�ҳ��ߵ��е���Ϊ�ο���
    ncSolidData caculate_long_middle_refpoints();

    //Ѱ�Ҷ�����Ϊ�����
    ncSolidData caculate_coner_refpoints();

    //����ͼ���ܳ��ı������������
    ncSolidData caculate_proportion_refpoints(double proporte);

    //������ȴ��ȶ����ݽ��зָ�,trueΪ˳ʱ��
    vector<shared_ptr<RS_Entity>> caculate_data_segmentation(bool direction=true);

    //�������е�
    vector<RS_Vector> get_all_rsvector();
};

#endif // NCSOLID_H
