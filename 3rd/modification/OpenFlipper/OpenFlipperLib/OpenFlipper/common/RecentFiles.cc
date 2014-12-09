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




//=============================================================================
//
//  Options used throughout the System
//
//=============================================================================

#include <QDir>

#include "RecentFiles.hh"

#include <OpenFlipper/common/GlobalOptions.hh>
#include <OpenFlipper/common/Types.hh>

namespace OpenFlipper {
namespace Options {
  

void addRecentFile(QString _file, DataType _type) {
  
  
  QStringList recentFiles = OpenFlipperSettings().value("Core/File/RecentFiles").toStringList();
  QStringList recentTypes = OpenFlipperSettings().value("Core/File/RecentTypes").toStringList();
  
  QString type = typeName(_type);
  
  // Check if file already in recent list
  for ( int i = 0 ; i < recentFiles.size() ; ++i)
    if ( _file == recentFiles[i] && type == recentTypes[i] ){
      recentFiles.removeAt(i);
      recentTypes.removeAt(i);
    }
  
  // Erase if too many files in list
  if ( recentFiles.size() >= OpenFlipperSettings().value("Core/File/MaxRecent",10).toInt() ) {
    recentFiles.pop_back();
    recentTypes.pop_back();
  }

  recentFiles.push_front(_file);
  recentTypes.push_front(type);
  
  OpenFlipperSettings().setValue("Core/File/RecentFiles", recentFiles);
  OpenFlipperSettings().setValue("Core/File/RecentTypes", recentTypes); 
}

}
}

//=============================================================================
