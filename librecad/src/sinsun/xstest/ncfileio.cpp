#include "ncfileio.h"
#include "ncfileprocesscommon.h"
#include "ncsolidprocesscommon.h"

std::string ncFileIo::generate_g_code()
{
    //��ȡ���ݷָ���������
    std::string resultGCode;
    ncFileProcessCommon commonProcesser(&m_file);
    QList<ncSolidData> cutSegments=commonProcesser.get_segments();

    //���Ƶ�λָ��
    resultGCode+="G21\n";

    //���������������ָ��

    if(m_commad==CRELATIVE)
    {
        resultGCode+="G91\n";
    }
    else
    {
        resultGCode+="G90\n";
    }

    //�������
    std::string onLaser="M07\n";
    std::string offLaser="M08\n";
    if(m_repairCommand==LEFT_TOOL_REPAIR)
    {
        onLaser="\nG41\nM07\n";
    }
    else if(m_repairCommand==RIGHT_TOOL_REPAIR)
    {
        onLaser="\nG42\nM07\n";
    }

    for(int i=0;i<cutSegments.size();++i)
    {
        //���ٶ�λ��
        resultGCode+="G00";
        RS_Vector g00EndPoint=cutSegments[i].m_g0_line->getEndpoint();
        RS_Vector g00StartPoint=cutSegments[i].m_g0_line->getStartpoint();

        if(m_commad==CRELATIVE)
        {
            std::string detaX="",detaY="";
            if(g00StartPoint.x!=g00EndPoint.x)
            {
                detaX+=(" X"+std::to_string(g00EndPoint.x-g00StartPoint.x));
            }
            if(g00StartPoint.y!=g00EndPoint.y)
            {
                detaY+=(" Y"+std::to_string(g00EndPoint.y-g00StartPoint.y));
            }

            resultGCode+=(detaX+detaY+"\n");
        }
        //���������ʽ
        else
        {
            resultGCode+=(" X"+std::to_string(g00EndPoint.x)+" Y"+std::to_string(g00EndPoint.y)+"\n");
        }

        //������(���ܴ�����)
        resultGCode+=onLaser;

        RS_Vector lastRecord=g00EndPoint;

        //�ӹ���,�������Ͻ��˵���һ����
        ncSolidProcessCommon tempProcess(cutSegments[i]);
        vector<shared_ptr<RS_Entity>> keySegments=tempProcess.caculate_data_segmentation();

        for(int j=0;j<keySegments.size();++j)
        {
            if(keySegments[j]->rtti()==RS2::EntityCircle)//Բ
            {
                shared_ptr<RS_Circle> tempCircle=dynamic_pointer_cast<RS_Circle>(keySegments[j]);

                if(1)//ԲĬ��Ϊ˳ʱ��
                {
                    resultGCode+="G02";
                }
                else
                {
                    resultGCode+="G03";
                }

                RS_Vector tempStartPoint=lastRecord;
                RS_Vector tempEndPoint=lastRecord;
                RS_Vector tempCenter=tempCircle->getCenter();
                //��������ʽ
                if(m_commad==CRELATIVE)
                {
                    std::string detaX="",detaY="";
                    if(tempEndPoint.x!=tempStartPoint.x)
                    {
                        detaX+=(" X"+std::to_string(tempEndPoint.x-tempStartPoint.x));
                    }
                    if(tempEndPoint.y!=tempStartPoint.y)
                    {
                        detaY+=(" Y"+std::to_string(tempEndPoint.y-tempStartPoint.y));
                    }
                    resultGCode+=(detaX+detaY);
                    resultGCode+=(" I"+std::to_string(tempCenter.x-tempStartPoint.x)+" J"+std::to_string(tempCenter.y-tempStartPoint.y)+"\n");
                }
                //���������ʽ
                else
                {
                    resultGCode+=(" X"+std::to_string(tempEndPoint.x)+" Y"+std::to_string(tempEndPoint.y));
                    resultGCode+=(" I"+std::to_string(tempCenter.x-tempStartPoint.x)+" J"+std::to_string(tempCenter.y-tempStartPoint.y)+"\n");
                }
            }
            else if(keySegments[j]->rtti()==RS2::EntityLine)//ֱ��
               {
                   resultGCode+="G01";
                   shared_ptr<RS_Line> tempLine=dynamic_pointer_cast<RS_Line>(keySegments[j]);
                   //��������ʽ
                   if(m_commad==CRELATIVE)
                   {
                       RS_Vector g01StartPoint=tempLine->getStartpoint();
                       RS_Vector g01EndPoint=tempLine->getEndpoint();

                       std::string detaX="",detaY="";
                       if(g01StartPoint.x!=g01EndPoint.x)
                       {
                           detaX+=(" X"+std::to_string(g01EndPoint.x-g01StartPoint.x));
                       }
                       if(g01StartPoint.y!=g01EndPoint.y)
                       {
                           detaY+=(" Y"+std::to_string(g01EndPoint.y-g01StartPoint.y));
                       }

                       resultGCode+=(detaX+detaY+"\n");
                   }
                   //���������ʽ
                   else
                   {
                       RS_Vector g01EndPoint=tempLine->getEndpoint();
                       resultGCode+=(" X"+std::to_string(g01EndPoint.x)+" Y"+std::to_string(g01EndPoint.y)+"\n");
                   }

                   lastRecord=tempLine->getEndpoint();
               }
               else if(keySegments[j]->rtti()==RS2::EntityArc)//Բ��
               {
                   shared_ptr<RS_Arc> tempArc=dynamic_pointer_cast<RS_Arc>(keySegments[j]);

                   if(tempArc->isReversed())//˳ʱ��Ϊ��
                   {
                       resultGCode+="G02";
                   }
                   else
                   {
                       resultGCode+="G03";
                   }

                   RS_Vector tempStartPoint=tempArc->getStartpoint();
                   RS_Vector tempEndPoint=tempArc->getEndpoint();
                   RS_Vector tempCenter=tempArc->getCenter();
                   //��������ʽ
                   if(m_commad==CRELATIVE)
                   {
                       std::string detaX="",detaY="";
                       if(tempEndPoint.x!=tempStartPoint.x)
                       {
                           detaX+=(" X"+std::to_string(tempEndPoint.x-tempStartPoint.x));
                       }
                       if(tempEndPoint.y!=tempStartPoint.y)
                       {
                           detaY+=(" Y"+std::to_string(tempEndPoint.y-tempStartPoint.y));
                       }
                       resultGCode+=(detaX+detaY);
                       resultGCode+=(" I"+std::to_string(tempCenter.x-tempStartPoint.x)+" J"+std::to_string(tempCenter.y-tempStartPoint.y)+"\n");
                   }
                   //���������ʽ
                   else
                   {
                       resultGCode+=(" X"+std::to_string(tempEndPoint.x)+" Y"+std::to_string(tempEndPoint.y));
                       resultGCode+=(" I"+std::to_string(tempCenter.x-tempStartPoint.x)+" J"+std::to_string(tempCenter.y-tempStartPoint.y)+"\n");
                   }
                   lastRecord=tempArc->getEndpoint();
               }
            else if(keySegments[j]->rtti()==RS2::EntityPoint)
            {

            }
        }
        //�ؼ���(���ܴ�����)
        resultGCode+=offLaser;
    }

    //�������
    resultGCode+="M02";

    return resultGCode;
}

shared_ptr<ncFileData> ncFileIo::generate_nc_file(const vector<int>& afterSort,shared_ptr<ncFileData> afterFile)
{
    //����˳��
    ncFileProcessCommon a(afterFile.get());
    auto tempOriEntities=a.get_entities();

    if(afterSort.size()!=tempOriEntities.size())
    {

    }

    //�޸�����
    RS_Line* tempToModify=afterFile->m_segment_file[afterSort[0]].m_g0_line;
    tempToModify->setStartpoint(afterFile->m_coordinate_origin);

    for(int i=1;i<afterSort.size();++i)
    {
        tempToModify=afterFile->m_segment_file[afterSort[i]].m_g0_line;
        //�����ߴ���
        if(afterFile->m_segment_file[afterSort[i-1]].m_out_transition_line.m_is_exist)
        {
            auto tempOutLines=afterFile->m_segment_file[afterSort[i-1]].m_out_transition_line.m_guide_entities;
            auto tempOutPoint=tempOutLines.back()->getEndpoint();
            tempToModify->setStartpoint(tempOutPoint);
        }
        else
        {
            auto tempOutPoint=afterFile->m_segment_file[afterSort[i-1]].m_cutin_point;
            tempToModify->setStartpoint(tempOutPoint);
        }
    }

    return afterFile;
}

shared_ptr<ncFileData> ncFileIo::generate_nc_file(const QList<RS_Entity *> &inPutEntities)
{
    //���յĽ���ļ�
    shared_ptr<ncFileData> result(new ncFileData());

    //��ʱ����
    result->m_coordinate_origin=RS_Vector(0,0);

//    RS_Polyline* back=new RS_Polyline(nullptr);
//    result->m_back_groud=back;

    //�洢����
    for(size_t i=0;i<inPutEntities.size();++i)
    {
        ncSolidData tempSolidData;
        tempSolidData.m_is_closed=true;
        tempSolidData.m_is_inner_membrane=false;
        tempSolidData.m_polyline=inPutEntities[i];

        ncSolidProcessCommon tempProcess=ncSolidProcessCommon(tempSolidData);
        tempSolidData=tempProcess.caculate_left_refpoints();
        result->m_segment_file.push_back(tempSolidData);
    }

    //����g00��
    result->m_segment_file[0].m_g0_line=new RS_Line(result->m_coordinate_origin,result->m_segment_file[0].m_cutin_point);
    for(size_t i=0;i<result->m_segment_file.size()-1;++i)
    {
        RS_Vector p1=result->m_segment_file[i].m_cutin_point;
        RS_Vector p2=result->m_segment_file[i+1].m_cutin_point;
        result->m_segment_file[i+1].m_g0_line=new RS_Line(p1,p2);
    }

    return result;
}

//bool ncFileIo::read_nc_file(const QString & _filePath/*I*/,ncFile & _ncFile/*O*/)
//{
//    _ncFile.clear();
//    QFile file(_filePath);// ���ļ�

//    if (file.open(QIODevice::ReadOnly))
//	{
//        QTextStream fileContent(&file);

//        double tempFeedrate(0),tempX(0),tempY(0);//��ʱ���ݴ洢����Ҫ��Ϊ�����ʡ�Բ�����ֵ

//        ncPoint currentPoint;
//        ncLineCircleContainer tempPolyline;
//        ncMiniSegment tempSegment;
//        bool relativeCoordinatesFlag(false);

//        while(!fileContent.atEnd())
//        {
//            QByteArray tempBa = fileContent.readLine().toLatin1();
//            char* buffer=tempBa.data();

//            //�ֻ�ȡ����ת�ٺͽ���
//            if (strstr(buffer, "F") != NULL)  //��ȡ������
//            {
//                read_num_after_str(buffer, "F", tempFeedrate);
//            }

//            //�ж�M����
//            //if (strstr(buffer, "M07") != NULL)
//            if (strstr(buffer, "M08") != NULL)
//            {
//                tempSegment.set_polylines(tempPolyline);
//                tempPolyline.clear();
//                _ncFile.add_segment(tempSegment);
//                tempSegment.clear_polylines();
//            }
//            if (strstr(buffer, "G91") != NULL)//�������
//            {
//                relativeCoordinatesFlag=true;
//            }

//            //�������ݵĴ洢
//            if (strstr(buffer, "X") != NULL||strstr(buffer, "Y") != NULL||strstr(buffer, "I") != NULL||strstr(buffer, "J") != NULL)
//            {
//                //��ʼ����ʱ����
//                double x_coordinate = 0, y_coordinate = 0;

//                //��ʱ������һ����
//                ncPoint prePoint=currentPoint;

//                //������洢����
//                if(relativeCoordinatesFlag)
//                {
//                    strstr(buffer, "X") != NULL ? (read_num_after_str(buffer, "X", x_coordinate)) : x_coordinate = 0;
//                    strstr(buffer, "Y") != NULL ? (read_num_after_str(buffer, "Y", y_coordinate)) : y_coordinate = 0;
//                    currentPoint.set_position(prePoint.position().x+x_coordinate,prePoint.position().y+y_coordinate);
//                }
//                else
//                {
//                    //��ȡ�ַ���������֣�ʡ�ԵĻ���ʹ�������һ��
//                    strstr(buffer, "X") != NULL ? (read_num_after_str(buffer, "X", x_coordinate), tempX = x_coordinate) : x_coordinate = tempX;
//                    strstr(buffer, "Y") != NULL ? (read_num_after_str(buffer, "Y", y_coordinate), tempY = y_coordinate) : y_coordinate = tempY;
//                    currentPoint.set_position(x_coordinate, y_coordinate);
//                }
//                currentPoint.set_feedrate(tempFeedrate);

//                //�ж�G����
//                if (strstr(buffer, "G00") != NULL)//���ٲ岹
//                {
//                    tempSegment.set_g0_line(ncLine(prePoint,currentPoint));
//                    continue;
//                }
//                if (strstr(buffer, "G01") != NULL)//ֱ�߲岹
//                {
//                    std::shared_ptr<ncEntity> tempLine(new ncLine(prePoint,currentPoint));
//                    tempPolyline.add_line_or_circle(tempLine);
//                    continue;
//                }
//                if (strstr(buffer, "G02") != NULL||strstr(buffer, "G03") != NULL)//˳ʱ��Բ���岹
//                {
//                    std::shared_ptr<ncArc> temp_circle(new ncArc());
//                    double radius_i(0), radius_j(0);

//                    temp_circle->set_start_point(prePoint);
//                    temp_circle->set_end_point(currentPoint);           //����Բ���յ�����

//                     //����Բ�Ĳ��洢
//                     read_num_after_str(buffer, "I", radius_i);
//                     read_num_after_str(buffer, "J", radius_j);
//                     double ri = prePoint.position().x + radius_i, rj = prePoint.position().y + radius_j;

//                     temp_circle->set_center(vec2(ri,rj));

//                     if (strstr(buffer, "G02") != NULL)
//                     {
//                         temp_circle->set_rotation_direction(1);          //������ת����
//                     }
//                     else
//                     {
//                         temp_circle->set_rotation_direction(0);
//                     }
//                     temp_circle->generate_parameter();

//                     tempPolyline.add_line_or_circle(temp_circle);        //�洢
//                     continue;
//                }
//            }
//        }

//#ifdef debug_pt
//        std::ofstream debug("C:\\Users\\tongtong\\Desktop\\test.txt");
//        auto a = Nc_file.get_m_point_array();
//            for (int i = 0; i < a.size(); ++i)
//            {
//                debug << a[i].get_point().X<<" "<< a[i].get_point().Y << " " << a[i].get_point().Z << " " <<a[i].get_angle().X << " " <<a[i].get_angle().Y << " " <<a[i].get_feedrate() << " " <<a[i].get_spindl_speed() << " " <<std::endl;
//            }
//        debug.close();
//#endif

//        return true;
//	}
//	else
//	{
//        return false;

//	}

//}
