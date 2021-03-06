/*===========================================================================*\
 *                                                                           *
 *                              OpenFlipper                                  *
 *      Copyright (C) 2001-2010 by Computer Graphics Group, RWTH Aachen      *
 *                           www.openflipper.org                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 *  This file is part of OpenFlipper.                                        *
 *                                                                           *
 *  OpenFlipper is free software: you can redistribute it and/or modify      *
 *  it under the terms of the GNU Lesser General Public License as           *
 *  published by the Free Software Foundation, either version 3 of           *
 *  the License, or (at your option) any later version with the              *
 *  following exceptions:                                                    *
 *                                                                           *
 *  If other files instantiate templates or use macros                       *
 *  or inline functions from this file, or you compile this file and         *
 *  link it with other files to produce an executable, this file does        *
 *  not by itself cause the resulting executable to be covered by the        *
 *  GNU Lesser General Public License. This exception does not however       *
 *  invalidate any other reasons why the executable file might be            *
 *  covered by the GNU Lesser General Public License.                        *
 *                                                                           *
 *  OpenFlipper is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU Lesser General Public License for more details.                      *
 *                                                                           *
 *  You should have received a copy of the GNU LesserGeneral Public          *
 *  License along with OpenFlipper. If not,                                  *
 *  see <http://www.gnu.org/licenses/>.                                      *
 *                                                                           *
\*===========================================================================*/

/*===========================================================================*\
 *                                                                           *
 *   $Revision: 9595 $                                                         *
 *   $Author: moebius $                                                      *
 *   $Date: 2010-06-17 12:48:23 +0200 (Do, 17. Jun 2010) $                   *
 *                                                                           *
\*===========================================================================*/

//
// C++ Interface: ToolbarInterface
//
// Description:
//
//
// Author: Jan Moebius <jan_moebius@web.de>, (C) 2007
//

#ifndef TOOLBARINTERFACE_HH
#define TOOLBARINTERFACE_HH

 #include <QtGui>
 #include <QMenuBar>
 #include <QStringList>
 #include <OpenFlipper/common/Types.hh>
 #include <QToolBar>

 /**
 * This Interface should be used by plugins which will provide a toolbar.
 * Each Plugin can create own Toolbars. Emit
 */
class ToolbarInterface {

   private slots :

   public :

      /// Destructor
      virtual ~ToolbarInterface() {};

    signals :

      /** \brief Adds a Toolbar to the main widget
      *
      * To create your own Toolbar, emit this signal with a pointer to your Toolbar.
      * @param _toolbar Your Toolbar
      */
      virtual void addToolbar(QToolBar* /*_toolbar*/) {};


      /** \brief Remove a Toolbar from the main widget
      *
      * @param _toolbar Toolbar to be removed
      */
      virtual void removeToolbar(QToolBar* /*_toolbar*/) {};


      /** \brief Get a pointer to a Toolbar of the given name or 0 if it does not exist.
      *
      * @param _name Name of the Toolbar
      * @param _toolbar requested Toolbar or 0
      */
      virtual void getToolBar( QString /*_name*/, QToolBar*& /*_toolbar*/ ) {};


};

Q_DECLARE_INTERFACE(ToolbarInterface,"OpenFlipper.ToolbarInterface/1.1")

#endif // TOOLBARINTERFACE_HH
