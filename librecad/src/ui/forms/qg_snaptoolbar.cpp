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
#include <QContextMenuEvent>
#include <QToolBar>

#include "qg_snaptoolbar.h"
#include "rs_settings.h"
#include "qg_actionhandler.h"
#include "lc_actiongroupmanager.h"
#include "QDebug"

/*
 *  Constructs a QG_CadToolBarSnap as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_SnapToolBar::QG_SnapToolBar(QWidget* parent, QG_ActionHandler* ah, LC_ActionGroupManager* agm)
	: QToolBar(parent)
    , actionHandler(ah)
{
    /*往右撑开*/
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   //toolBar is a pointer to an existing toolbar
    this->addWidget(spacer);

    this->addSeparator();
    grid_status = new TwoStackedLabels(this);
    grid_status->setStyleSheet("font-size:16px;color:white;");
    this->addWidget(grid_status);
    this->addSeparator();
    auto action = new QAction(tr("Exclusive Snap Mode"), agm->snap_extras);
    tool_button = new QToolButton;
    action->setIcon(QIcon(":/icons/2044.png"));
    action->setCheckable(true);
    connect(action, SIGNAL(toggled(bool)),
            agm, SLOT(toggleExclusiveSnapMode(bool)));
    action->setObjectName("ExclusiveSnapMode");
    tool_button->setDefaultAction(action);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(30,30));
    this->addWidget(tool_button);
//    addAction(action);


    tool_button = new QToolButton;
    snapFree = new QAction(QIcon(":/icons/2045.png"), tr("Free Snap"), agm->snap_extras);
    snapFree->setCheckable(true);
    snapFree->setObjectName("SnapFree");
    connect(snapFree, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapFree);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(30,30));
    this->addWidget(tool_button);
//    this->addAction(snapFree);

    tool_button = new QToolButton;
    snapGrid = new QAction(QIcon(":/icons/2046.png"), tr("Snap on grid"), agm->snap);
    snapGrid->setObjectName("SnapGrid");
    snapGrid->setCheckable(true);
    connect(snapGrid, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapGrid);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(30,30));
    this->addWidget(tool_button);
//    this->addAction(snapGrid);

    tool_button = new QToolButton;
    snapEnd = new QAction(QIcon(":/icons/2047.png"), tr("Snap on Endpoints"), agm->snap);
    snapEnd->setObjectName("SnapEnd");
    snapEnd->setCheckable(true);
    connect(snapEnd, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapEnd);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(30,30));
    this->addWidget(tool_button);
//    this->addAction(snapEnd);

    tool_button = new QToolButton;
    snapOnEntity = new QAction(QIcon(":/icons/2048.png"), tr("Snap on Entity"), agm->snap);
    snapOnEntity->setObjectName("SnapEntity");
    snapOnEntity->setCheckable(true);
    connect(snapOnEntity, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapOnEntity);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(30,30));
    this->addWidget(tool_button);
//    this->addAction(snapOnEntity);

    snapCenter = new QAction(QIcon(":/icons/2049.png"), tr("Snap Center"), agm->snap);
    snapCenter->setObjectName("SnapCenter");
    snapCenter->setCheckable(true);
    connect(snapCenter, SIGNAL(triggered()), this, SLOT(actionTriggered()));
//    this->addAction(snapCenter);

    tool_button = new QToolButton;
    snapMiddle = new QAction(QIcon(":/icons/2049.png"), tr("Snap Middle"), agm->snap);
    snapMiddle->setObjectName("SnapMiddle");
    snapMiddle->setCheckable(true);
    connect(snapMiddle, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapMiddle);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(35,35));
    this->addWidget(tool_button);
//    this->addAction(snapMiddle);

    tool_button = new QToolButton;
    snapDistance = new QAction(QIcon(":/icons/2050.png"), tr("Snap Distance"), agm->snap);
    snapDistance->setObjectName("SnapDistance");
    snapDistance ->setCheckable(true);
    connect(snapDistance, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapDistance);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(35,35));
    this->addWidget(tool_button);
//    this->addAction(snapDistance);

    tool_button = new QToolButton;
    snapIntersection = new QAction(QIcon(":/icons/2051.png"), tr("Snap Intersection"), agm->snap);
    snapIntersection->setObjectName("SnapIntersection");
    snapIntersection->setCheckable(true);
    connect(snapIntersection, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    tool_button->setDefaultAction(snapIntersection);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(35,35));
    this->addWidget(tool_button);
//	this->addAction(snapIntersection);

//    this->addSeparator();

    restrictHorizontal = new QAction(QIcon(":/icons/restr_hor.svg"),
                                     tr("Restrict Horizontal"), agm->restriction);
    restrictHorizontal->setObjectName("RestrictHorizontal");
    restrictHorizontal->setCheckable(true);
    connect(restrictHorizontal, SIGNAL(triggered()), this, SLOT(actionTriggered()));
//    this->addAction(restrictHorizontal);
    restrictVertical = new QAction(QIcon(":/icons/restr_ver.svg"),
                                   tr("Restrict Vertical"), agm->restriction);
    restrictVertical->setObjectName("RestrictVertical");
    restrictVertical->setCheckable(true);
    connect(restrictVertical, SIGNAL(triggered()), this, SLOT(actionTriggered()));
//    this->addAction(restrictVertical);

    restrictOrthogonal = new QAction(QIcon(":/icons/restr_ortho.svg"),
                                   tr("Restrict Orthogonal"), agm->restriction);
    restrictOrthogonal->setObjectName("RestrictOrthogonal");
    restrictOrthogonal->setCheckable(true);
    connect(restrictOrthogonal, SIGNAL(triggered(bool)), this,
            SLOT(slotRestrictOrthogonal(bool)));
//	this->addAction(restrictOrthogonal);

    restrictNothing = new QAction(QIcon(":/extui/restrictnothing.png"),
                                   tr("Restrict Nothing"), agm->restriction);
    restrictNothing->setObjectName("RestrictNothing");
    restrictNothing->setCheckable(true);
    connect(restrictNothing, SIGNAL(triggered(bool)), this,
            SLOT(slotRestrictNothing(bool)));

    this->addSeparator();
//    this->setStyleSheet("QG_SnapToolBar::separator{background-color:black;height:1px}");

    tool_button = new QToolButton;
    bRelZero = new QAction(QIcon(":/icons/2052.png"), tr("Set relative zero position"), agm->other);
    bRelZero->setObjectName("SetRelativeZero");
    bRelZero->setCheckable(false);
    connect(bRelZero, SIGNAL(triggered()), actionHandler, SLOT(slotSetRelativeZero()));
    //connect(bRelZero, SIGNAL(triggered()), this, SLOT(slotSetRelativeZero()));
    tool_button->setDefaultAction(bRelZero);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(35,35));
    this->addWidget(tool_button);
//    this->addAction(bRelZero);


    tool_button = new QToolButton;
    bLockRelZero = new QAction(QIcon(":/icons/2053.png"), tr("Lock relative zero position"), agm->other);
    bLockRelZero->setObjectName("LockRelativeZero");
    bLockRelZero->setCheckable(true);
    connect(bLockRelZero, SIGNAL(toggled(bool)),actionHandler, SLOT(slotLockRelativeZero(bool)));
    tool_button->setDefaultAction(bLockRelZero);
    tool_button->setFixedSize(35,35);
    tool_button->setIconSize(QSize(35,35));
    this->addWidget(tool_button);
    this->addSeparator();
//    this->addAction(bLockRelZero);
    //restore snapMode from saved preferences
    RS_SETTINGS->beginGroup("/Snap");
    setSnaps( RS_SnapMode::fromInt( RS_SETTINGS->readNumEntry( "/SnapMode", 0)));
    mouseWidget = new QG_MouseWidget(this, "mouse info");
    mouseWidget->setFixedWidth(380);
    this->addWidget(mouseWidget);
    this->addSeparator();
}

void QG_SnapToolBar::saveSnapMode()
{
    //@write default snap mode from prefrences.
    unsigned int snapFlags {RS_SnapMode::toInt( getSnaps())};
    RS_SETTINGS->beginGroup("/Snap");
    RS_SETTINGS->writeEntry("/SnapMode",QString::number(snapFlags));
    RS_SETTINGS->endGroup();
    // no need to delete child widgets, Qt does it all for us
}

void QG_SnapToolBar::setSnaps ( RS_SnapMode const& s )
{
	if(getSnaps()==s) return;
    snapFree->setChecked(s.snapFree);
    snapGrid->setChecked(s.snapGrid);
    snapEnd->setChecked(s.snapEndpoint);
    snapOnEntity->setChecked(s.snapOnEntity);
    snapCenter->setChecked(s.snapCenter);
    snapMiddle->setChecked(s.snapMiddle);
    snapDistance->setChecked(s.snapDistance);
    snapIntersection->setChecked(s.snapIntersection);
    restrictHorizontal->setChecked(s.restriction==RS2::RestrictHorizontal ||  s.restriction==RS2::RestrictOrthogonal);
    restrictVertical->setChecked(s.restriction==RS2::RestrictVertical ||  s.restriction==RS2::RestrictOrthogonal);
    restrictOrthogonal->setChecked(s.restriction==RS2::RestrictOrthogonal);
    restrictNothing->setChecked(s.restriction==RS2::RestrictNothing);
}

RS_SnapMode QG_SnapToolBar::getSnaps ( void ) const
{
    RS_SnapMode s;

    s.snapFree         = snapFree->isChecked();
    s.snapGrid         = snapGrid->isChecked();
    s.snapEndpoint     = snapEnd->isChecked();
    s.snapOnEntity     = snapOnEntity->isChecked();
    s.snapCenter       = snapCenter->isChecked();
    s.snapMiddle       = snapMiddle->isChecked();
    s.snapDistance       = snapDistance->isChecked();
    s.snapIntersection = snapIntersection->isChecked();
    // removed Restrict Othogonal button
    // todo simplify internal restrict rules
	int const rH = (restrictHorizontal && restrictHorizontal->isChecked())? 1:0;
	int const rV = (restrictVertical && restrictVertical->isChecked())? 2: 0;
	switch (rH + rV) {
	case 3:
		s.restriction = RS2::RestrictOrthogonal;
		break;
	case 2:
		s.restriction = RS2::RestrictVertical;
		break;
	case 1:
		s.restriction = RS2::RestrictHorizontal;
		break;
	default:
		s.restriction = RS2::RestrictNothing;
	}

    return s;
}

bool QG_SnapToolBar::lockedRelativeZero() const
{
    return bLockRelZero->isChecked();
}

void QG_SnapToolBar::setLockedRelativeZero(bool on)
{
    bLockRelZero->setChecked(on);
}

void QG_SnapToolBar::setActionHandler(QG_ActionHandler* ah){
    actionHandler=ah;
}

/* Slots */

void QG_SnapToolBar::slotRestrictNothing(bool checked)
{
	if( restrictVertical) restrictVertical->setChecked(!checked);
	if( restrictHorizontal) restrictHorizontal->setChecked(!checked);
	if( restrictOrthogonal) restrictOrthogonal->setChecked(!checked);
    actionTriggered();
}

void QG_SnapToolBar::slotRestrictOrthogonal(bool checked)
{
	if( restrictVertical) restrictVertical->setChecked(checked);
	if( restrictHorizontal) restrictHorizontal->setChecked(checked);
	if( restrictNothing) restrictNothing->setChecked(checked);
    actionTriggered();
}

void QG_SnapToolBar::actionTriggered()
{

    actionHandler->slotSetSnaps(getSnaps());

}
