/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

#ifndef RS_ACTIONMODIFYCUT_H
#define RS_ACTIONMODIFYCUT_H

#include "rs_actioninterface.h"
#include "sx_actiongroupexplode.h"

/**
 * This action class can handle user events to divide entities.
 *
 * @author Andrew Mustun
 */
class RS_ActionModifyCut : public RS_ActionInterface {
	Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
        ChooseCutEntity,      /**< Choosing the entity to cut in two. */
        SetCutCoord        /**< Choosing the cutting point. */
    };


    /**
     * Action States.
     */
    enum Status2 {
        SetStartpoint,   /**< Setting the startpoint.  */
        SetNextPoint      /**< Setting the endpoint. */
    };

    enum SegmentMode {
    Line=0,
    Tangential=1,
    TanRad=2,
    Ang=3,
    };

public:
    RS_ActionModifyCut(RS_EntityContainer& container,
                        RS_GraphicView& graphicView);
	~RS_ActionModifyCut() override;

	void init(int status=0) override;
	void trigger() override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void updateMouseButtonHints() override;
	void updateMouseCursor() override;

private:
    RS_Entity* cutEntity;
    RS_Entity* leftEntity;
    RS_Entity* rightEntity;
	std::unique_ptr<RS_Vector> cutCoord;
    RS_Vector *leftCoord;
    RS_Vector *rightCoord;
    RS_Vector *vector;
    double dist;
    sx_actionGroupExplode *blockexplode;
    int i;
    bool flag = false;
    bool isClose = false;
    RS_Vector *startPoint;
    RS_Vector *endPoint;
//    double solveBulge(RS_Vector mouse);
//    bool calculatedSegment;
//    SegmentMode Mode;
//    double Radius;
//    double Angle;
//    int m_Reversed;
    struct Points;
    std::unique_ptr<Points> pPoints;
    int entityNumber;
};

#endif
