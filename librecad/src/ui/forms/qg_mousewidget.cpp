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
#include "qg_mousewidget.h"

#include <QVariant>
#include "rs_settings.h"

/*
 *  Constructs a QG_MouseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_MouseWidget::QG_MouseWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
    setObjectName(name);
    setupUi(this);
    this->lineEdit->setText("");
    this->lineEdit->setReadOnly(true);
    this->lineEdit->setPlaceholderText("信息提示框");
    this->lineEdit->setStyleSheet("background-color:#AEAEAE;color:white;font-size:16px;border:1px solid black");
    this->pushButton->setStyleSheet("border-left:8px solid #5F5F5F;border-top:8px solid #303030;border-bottom:8px solid #303030;border-right:8px solid #303030;");
//    lLeftButton->setText("");
//    lRightButton->setText("");
//    lMousePixmap->setPixmap( QPixmap(":/icons/mouse.svg"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_MouseWidget::~QG_MouseWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_MouseWidget::languageChange()
{
    retranslateUi(this);
}

void QG_MouseWidget::setHelp(const QString& left, const QString& right) {
//    lLeftButton->setText(left);
//    lRightButton->setText(right);
    this->lineEdit->setText(left);
}
