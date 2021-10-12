#include "ncfile.h"
#include "pt_algcommon.h"

//ncFile����
class ncFileIo
{
public:
    ncFileData m_file;
    COORDINATE_COMMAND m_commad=CRELATIVE;          //���λ��
    TOOL_REPAIR m_repairCommand=NULL_TOOL_REPAIR;   //�����е���

public:
    //����G����
    std::string generate_g_code();

    //����ԭʼ����,�ú�����϶�����γ�polyline��ʶ��Ƿ��ͼ�Ρ�������������ϳɿ�QList<ncSolidData>�����ncFileData m_file�С��ж�����ģ
    shared_ptr<ncFileData> generate_nc_file(const vector<int>& afterSort,shared_ptr<ncFileData> afterFile);

    //    bool static read_nc_file(const QString & File_path/*I*/, ncFile & Nc_file/*O*/);
    shared_ptr<ncFileData> generate_nc_file(const QList<RS_Entity *> &inPutEntities);
};
