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




#include "SelectionPlugin.hh"

#include <iostream>

#include <MeshTools/MeshSelectionT.hh>
#include <OpenFlipper/BasePlugin/PluginFunctions.hh>


//=========================================================
//==== Face selections
//=========================================================

void SelectionPlugin::selectFaces( int objectId , IdList _faceList ) {
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("selectFaces : unable to get object") ); 
    return;
  }
  
  if ( _faceList.size() == 0 )
    return;
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::selectFaces(PluginFunctions::triMesh(object), _faceList);
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::selectFaces(PluginFunctions::polyMesh(object), _faceList);
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::selectFaces(PluginFunctions::tsplineMesh(object), _faceList);
#endif
  else{
      emit log(LOGERR,tr("selectFaces : Unsupported object Type") ); 
      return;
  }
  
  QString selection = "selectFaces( ObjectId , [ " + QString::number(_faceList[0]);
  
  for ( uint i = 1 ; i < _faceList.size(); ++i) {
    selection +=  " , " + QString::number(_faceList[i]);
  }
  
  selection += " ] )";
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( selection );
}

//=========================================================

void SelectionPlugin::unselectFaces( int objectId , IdList _faceList ) {
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("unselectFaces : unable to get object") ); 
    return;
  }
  
  if ( _faceList.size() == 0 )
    return;
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::unselectFaces(PluginFunctions::triMesh(object), _faceList);
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::unselectFaces(PluginFunctions::polyMesh(object), _faceList);
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::unselectFaces(PluginFunctions::tsplineMesh(object), _faceList);
#endif
  else{
      emit log(LOGERR,tr("unselectFaces : Unsupported object Type") ); 
      return;
  }
  
  QString selection = "unselectFaces( ObjectId , [ " + QString::number(_faceList[0]);
  
  for ( uint i = 1 ; i < _faceList.size(); ++i) {
    selection +=  " , " + QString::number(_faceList[i]);
  }
  
  selection += " ] )";
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( selection );
}

//=========================================================

void SelectionPlugin::selectAllFaces( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("selectAllFaces : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::selectAllFaces(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::selectAllFaces(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::selectAllFaces(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("selectAllFaces : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "selectAllFaces( ObjectId )" );
}

//=========================================================

void SelectionPlugin::clearFaceSelection( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("clearFaceSelection : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::clearFaceSelection(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::clearFaceSelection(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::clearFaceSelection(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("clearFaceSelection : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "clearFaceSelection( ObjectId )" );
}

//=========================================================

void SelectionPlugin::invertFaceSelection( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("invertFaceSelection : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::invertFaceSelection(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::invertFaceSelection(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::invertFaceSelection(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("invertFaceSelection : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "invertFaceSelection( ObjectId )" );
}

//=========================================================

void SelectionPlugin::selectBoundaryFaces( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("selectBoundaryFaces : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::selectBoundaryFaces(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::selectBoundaryFaces(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::selectBoundaryFaces(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("selectBoundaryFaces : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "selectBoundaryFaces( ObjectId )" );
}


//=========================================================

void SelectionPlugin::shrinkFaceSelection( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("shrinkFaceSelection : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::shrinkFaceSelection(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::shrinkFaceSelection(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::shrinkFaceSelection(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("shrinkFaceSelection : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "shrinkFaceSelection( ObjectId )" );
}

//=========================================================

void SelectionPlugin::growFaceSelection( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("growFaceSelection : unable to get object") ); 
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      MeshSelection::growFaceSelection(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      MeshSelection::growFaceSelection(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      MeshSelection::growFaceSelection(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("growFaceSelection : Unsupported object Type") ); 
      return;
  }
  
  emit updatedObject(object->id(), UPDATE_SELECTION_FACES);
  emit scriptInfo( "growFaceSelection( ObjectId )" );
}
  
//=========================================================

IdList SelectionPlugin::getFaceSelection( int objectId )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,tr("getFaceSelection : unable to get object") ); 
    return IdList(0);
  }
  
  emit scriptInfo( "getFaceSelection( ObjectId )" );
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      return MeshSelection::getFaceSelection(PluginFunctions::triMesh(object));
  else if ( object->dataType() == DATA_POLY_MESH )
      return MeshSelection::getFaceSelection(PluginFunctions::polyMesh(object));
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      return MeshSelection::getFaceSelection(PluginFunctions::tsplineMesh(object));
#endif
  else{
      emit log(LOGERR,tr("getFaceSelection : Unsupported object Type") ); 
      return IdList(0);
  }
  

}

//=========================================================

/// colorize the face selection
void SelectionPlugin::colorizeFaceSelection(int objectId, int r, int g, int b )
{
  BaseObjectData* object;
  if ( ! PluginFunctions::getObject(objectId,object) ) {
    emit log(LOGERR,"colorizeFaceSelection : unable to get object" );
    return;
  }
  
  if ( object->dataType() == DATA_TRIANGLE_MESH )
      colorizeSelection(PluginFunctions::triMesh(object), FACE, r, g, b);
  else if ( object->dataType() == DATA_POLY_MESH )
      colorizeSelection(PluginFunctions::polyMesh(object), FACE, r, g, b);
#ifdef ENABLE_TSPLINEMESH_SUPPORT
  else if ( object->dataType() == DATA_TSPLINE_MESH )
      colorizeSelection(PluginFunctions::tsplineMesh(object), FACE, r, g, b);
#endif
  else {
      emit log(LOGERR,"colorizeFaceSelection : Unsupported object Type" );
      return;
  }
  
  
  emit scriptInfo( "colorizeFaceSelection( ObjectId, "
                  + QString::number(r) + ", " + QString::number(g) + ", " + QString::number(b) + " )" );
                  
  emit updatedObject(objectId, UPDATE_COLOR);

}
  


