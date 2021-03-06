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
 *   $Revision: 9657 $                                                         *
 *   $Author: moebius $                                                      *
 *   $Date: 2010-06-22 09:05:50 +0200 (Di, 22. Jun 2010) $                   *
 *                                                                           *
\*===========================================================================*/




//=============================================================================
//
//  CLASS Core
//
//=============================================================================

/**
 * \file Core.hh
 * This File contains the header of the frameworks system core
*/

#ifndef MVIEWWIDGET_HH
#define MVIEWWIDGET_HH


//== INCLUDES =================================================================

#include <OpenFlipper/widgets/glWidget/QtBaseViewer.hh>

// QT INCLUDES
#include <qvariant.h>
#include <qmainwindow.h>
#include <QToolBox>
#include <QStackedWidget>
#include <QSplashScreen>

#include <QDockWidget>
#include <QVector>
#include <QProgressDialog>

#include <QtScript/QScriptEngine>
#include <QtScript/QtScript>

#include "OpenFlipper/INIFile/INIFile.hh"

#include "OpenFlipper/Logging/Logging.hh"
#include "OpenFlipper/Scripting/Scripting.hh"

// Prototypes for scripting
#include "OpenFlipper/Scripting/scriptPrototypes/prototypeVec3d.hh"
#include "OpenFlipper/Scripting/scriptPrototypes/prototypeMatrix4x4.hh"
#include "OpenFlipper/Scripting/scriptPrototypes/prototypeDataType.hh"
#include <OpenFlipper/Scripting/scriptWrappers/vec3dWrapper.hh>
#include <OpenFlipper/Scripting/scriptWrappers/matrix4x4Wrapper.hh>
#include <OpenFlipper/Scripting/scriptWrappers/DataTypeWrapper.hh>
// #include <OpenFlipper/Scripting/scriptWrappers/ObjectIdWrapper.hh>

// Required Interface definition ( Some variables were defined there )
#include "OpenFlipper/BasePlugin/BaseInterface.hh"
#include "OpenFlipper/BasePlugin/FileInterface.hh"
#include "OpenFlipper/BasePlugin/TypeInterface.hh"
#include "OpenFlipper/BasePlugin/MenuInterface.hh"
#include "OpenFlipper/BasePlugin/ContextMenuInterface.hh"

#include <OpenFlipper/widgets/coreWidget/CoreWidget.hh>

// Process manager widget
#include <OpenFlipper/widgets/processManagerWidget/processManagerWidget.hh>

#include <OpenFlipper/common/GlobalOptions.hh>

#include <OpenFlipper/Core/PluginInfo.hh>

#include <ACG/Scenegraph/CoordsysNode.hh>
#include <ACG/Scenegraph/GridNode.hh>

#include <OpenFlipper/threads/JobInfo.hh>

//== CLASS DEFINITION =========================================================

struct fileTypes {
  QString name;
  DataType type;
  QString loadFilters;
  QString saveFilters;
  FileInterface* plugin;
  QObject* object;
  bool saveMultipleObjects;
};

struct dataTypes {
  QString name;
  DataType type;
  TypeInterface* plugin;
};

/** Core Widget of the Application
 */
class Core : public QObject
{
  Q_OBJECT

public:

  /// constructor
  Core();

  void init();

  /// destructor
  ~Core();

  /// Synchronise two viewers
  bool add_sync_host(const QString& _name);


private slots:

  /// Handle Mouse events when in Identifier mode
  void slotMouseEventIdentify( QMouseEvent* _event );

protected:

    //===========================================================================
    /** @name Signals send to Plugins
    * @{ */
   //===========================================================================
signals:
   /// Signal send to plugins when whole scene is cleared
   void allCleared();

   /// When this Signal is emitted all Plugins are informed that the object list changed
   void signalObjectUpdated(int);

   /// When this Signal is emitted all Plugins are informed that some type of update was performed on an object
   void signalObjectUpdated(int, const UpdateType);
   
   /// When this Signal is emitted when a Wheel Event occures
   void PluginWheelEvent(QWheelEvent * , const std::string & );

   /// When this Signal is emitted when a Mouse Event occures
   void PluginMouseEvent(QMouseEvent* );

   /// Emitted when an identify event occurs
   void PluginMouseEventIdentify( QMouseEvent* );

   /// This signal is emitted if the object has been changed (source/target)
   void objectSelectionChanged( int );

   /// This signal is emitted if one of the viewers updated its view
   void pluginViewChanged();

   /// The texture with the given name and filename has been added
   void addTexture( QString, QString , uint, int );

   /// The texture with the given name and filename has been added
   void addTexture( QString, QString , uint );

   /// The texture with the given name and filename has been added
   void addMultiTexture( QString _textureGroup , QString _name , QString _filename , int _id , int& _textureId );

   /// Tell the plugins to update the given texture
   void updateTexture( QString , int );

   /// Update all textures in the plugins
   void updateAllTextures( );

   /// This Signal is send to the plugins if a texture has been updated
   void updatedTextures( QString , int );

   /// A texture mode should be changed
   void setTextureMode(QString _textureName ,QString _mode, int _id);

   /// A texture mode should be changed
   void setTextureMode(QString _textureName ,QString _mode);

   /// Switch Texture Plugins to a given Mode
   void switchTexture( QString, int );

   /// Switch Texture Plugins to a given Mode
   void switchTexture( QString );

   /// Change the image for a given texture
   void textureChangeImage( QString _textureName , QImage& _image );

   /// Change the image for a given texture
   void textureChangeImage( QString _textureName , QImage& _image , int _id );

   ///fetch texture image
   void textureGetImage( QString _textureName , QImage& _image );

   ///fetch texture image
   void textureGetImage( QString _textureName , QImage& _image , int _id );

   /// get the texture index
   void textureIndex( QString _textureName, int _id, int& _index);
   
   /// get the texture name
   void textureName( int _id, int _textureIndex, QString& _textureName);

   ///get current texture
   void getCurrentTexture( int _id, QString& _textureName );

   /// get a multi-texture's sub textures
   void getSubTextures( int _id, QString _multiTextureName, QStringList& _subTextures );

   /// If an ini File is opened, this signal is send to Plugins capable of handling ini files
   void iniLoad( INIFile&, int );

   /// This signal is used to tell the plugins to save the data of _id to the given file
   void iniSave( INIFile& _ini ,int _id );

   /// This signal is used to tell the plugins to save their current status
   void iniSaveOptions(  INIFile& _ini );

   /// This signal is used to tell the plugins to load their new status
   void iniLoadOptions(  INIFile& _ini );

   /// This signal is used to tell the plugins to load their new status after objects are loaded
   void iniLoadOptionsLast(  INIFile& _ini );

   /// This signal is emitted before the core deletes its data and exits
   void saveOnExit( INIFile& _ini );

   /// Tell plugins to create a backup
   void createBackup( int _objectId , QString _name , int _internalId);
   
   /// Tell Plugins to make a backup persistent
   void makeBackupPersistent(int _objectid, int _internalId);
   
   /// Tell Backup Plugin to restore an object with the given backup id
   void restoreObject( int _objectId, int _internalId);
   
   
   /** \brief Backup Plugin tells other Plugins that a restore will happen
   */
   void aboutToRestore(int _objectId , int _internalId);
   
   /** \brief Backup Plugin tells other Plugins that they should restore their own data
   */
   void restore(int _objectId , int _internalId);
   
   /** \brief Backup Plugin tells other Plugins that a restore has happened
   */
   void restored( int _objectId , int _internalId);

   /// Tell the plugins that a file has been opened ( -> Database)
   void openedFile( int _id );

   /// Tell the plugins that an empty object has been added
   void emptyObjectAdded( int _id);

   /// Called after all plugins are loaded
   void pluginsInitialized();

   /// Tell plugins that the visibility of an object has changed
   void visibilityChanged(int _id);

   /// Tell plugins that object properties such as object names have been changed
   void objectPropertiesChanged( int _id );

   /// Called after an object has been deleted
   void objectDeleted( int );

   /** @} */

   //===========================================================================
    /** @name Slots called by the plugins
    * @{ */
   //===========================================================================
   private slots :

      /** Called by the plugins if they changed something in the object list (deleted, added,...)
       * @param _identifier Id of the object
       */
      void slotObjectUpdated(int _identifier, const UpdateType _type = UPDATE_ALL);

      /// Called when a plugin changes the visibility of an object
      void slotVisibilityChanged(int _id);

      /// Called by plugins if object properties like names have changed
      void slotObjectPropertiesChanged( int _id );

      /// Called by Plugins if they changed the active object
      void slotObjectSelectionChanged( int _id);

      /// Add a new picking mode to the examiner_widget_
      void slotAddPickMode( const std::string _mode );

      /// Add a new and invisible picking mode to the examiner_widget_
      void slotAddHiddenPickMode( const std::string _mode );

      /// Called by a plugin if it creates a texture
      void slotAddTexture( QString _textureName , QString _filename , uint _dimension , int _id );

      /// Called by a plugin if it creates a texture
      void slotAddTexture( QString _textureName , QString _filename , uint _dimension );

      /// Called by a plugin if it creates a multitexture
      void slotMultiTextureAdded( QString _textureGroup , QString _name , QString _filename , int _id , int& _textureId );

      /// Tell the plugins to update the given texture
      void slotUpdateTexture( QString _name , int _identifier);

      /// Update all textures in the plugins
      void slotUpdateAllTextures( );

      /// A Texture has been updated
      void slotTextureUpdated( QString _textureName , int _identifier );

      /// A texture mode should be changed
      void slotSetTextureMode(QString _textureName ,QString _mode, int _id);

      /// A texture mode should be changed
      void slotSetTextureMode(QString _textureName ,QString _mode);

      /// Tells Plugins to switch to the given Texture
      void slotSwitchTexture( QString _textureName, int _id );

      /// Tells Plugins to switch to the given Texture
      void slotSwitchTexture( QString _textureName );

      ///Called by plugins if texture image should be changed
      void slotTextureChangeImage( QString _textureName , QImage& _image );

      ///Called by plugins if texture image should be changed
      void slotTextureChangeImage( QString _textureName , QImage& _image , int _id );

      ///Called by plugins if texture image should be fetched
      void slotTextureGetImage( QString _textureName , QImage& _image );

      ///Called by plugins if texture image should be fetched
      void slotTextureGetImage( QString _textureName , QImage& _image , int _id );
      
      ///Called by plugins if texture index should be fetched
      void slotTextureIndex( QString _textureName, int _id, int& _index);
      
      ///Called by plugins if texture name should be fetched
      void slotTextureName( int _id, int _textureIndex, QString& _textureName);
      
      ///Called by plugins if current texture should be retrieved
      void slotGetCurrentTexture( int _id, QString& _textureName );

      ///Called by plugins if a multi-texture's sub textures should be fetched
      void slotGetSubTextures( int _id, QString _multiTextureName, QStringList& _subTextures );

      /// Called if a backup is requested by the plugins
      void slotBackup( int _objectId, QString _name, int& _internalId );
      
      /// Called if a backup is requested by the plugins
      void slotBackup( int _objectId, QString _name );
      
      /// Called if a backup is requested by the plugins
      void slotRestore( int _objectId, int _internalId = -1 );

      /// A plugin wants to load a given file
      void slotLoad(QString _filename, DataType _type, int& _id);

      /// the load widget wants to load a given file
      void slotLoad(QString _filename, int _pluginID);
      
      /// Called when a file has been opened
      void slotObjectOpened ( int _id );

      /// Called when an empty object has been Added
      void slotEmptyObjectAdded ( int _id );

      /** \brief Called when a plugin requests a list of file-filters
      *
      * This function collects all available load filters from the file Plugins.
      * It is normally called via the Load/Save interface ( LoadSaveInterface ).
      *
      * @param _list Returns a list of all available file load filters
      */ 
      void slotGetAllFilters ( QStringList& _list);

      /// Called when a plugin wants to delete an object
      void slotDeleteObject( int _id );

      /// Called when a plugin wants to delete all objects
      void slotDeleteAllObjects( );

      /// Get a Pointer to the Plugin with given _name (if it is loaded)
//       void slotGetPlugin(QString _name, QObject* & _plugin );

   /** @} */

    //===========================================================================
    /** @name scriptable slots
    * @{ */
   //===========================================================================
public slots:

    /// Called when a  plugin requests an update in the viewer
    void updateView();

    /// Clear all data objects
    void clearAll();

    /// exit the current application
    void exitApplication();

    /// set fullscreen mode
    void fullscreen( bool _state );

    /// Change the logging window state
    void loggerState(int _state);

    /// Show or hide toolbox
    void showToolbox( bool _state );

    /// Switch the multiView Mode
    void multiViewMode( int _mode );

    /// Enable or disable framerate restriction
    void restrictFrameRate( bool _enable );

    /// set the maximal framerate ( automatically enables framerate restriction )
    void setMaxFrameRate( int _rate );

    /// set the baseFilename for snapshots (a counter is automatically increased when
    /// snapshot() is called)
    void snapshotBaseFileName(const QString& _fname, unsigned int _viewerId = 0);

    /** Trigger a snapshot and increase the snapshot counter.
      Save snapshot to file determined by snapshotBaseFileName() and
      the current snapshot counter. The \a back buffer will be saved.
    */
    void snapshot(unsigned int _viewerId = 0);

    /// Take a snapshot from the whole app
    void applicationSnapshot();

    /// Set the baseName for the application snapshot
    void applicationSnapshotName(QString _name);

    /// Take a snapshot from all viewers
    void viewerSnapshot();

    /// resize the examinerViewer
    void resizeViewers(int _width, int _height );

    /// resize the whole Application
    void resizeApplication(int _width, int _height );

    /// write the current versions of all plugins to ini file
    void writeVersionNumbers(QString _filename);

    /// return the list of available object that has the given selection and type
    QList<int> objectList (QString _selection, QStringList _types);

   //===========================================================================
    /** @name Scripting functions for controlling view modes
    * @{ */
   //===========================================================================

public slots:
    /** \brief Scripting function to set toolboxes in a view mode

      @param _modeName Name of the View Mode
      @param _toolboxList ; seperated list of toolboxes in the view mode
    */
    void addViewModeToolboxes(QString _modeName, QString _toolboxList);
    
    /** \brief Scripting function to set toolbars in a view mode
    
    @param _modeName Name of the View Mode
    @param _toolboxList ; seperated list of toolbars in the view mode
    */
    void addViewModeToolbars(QString _modeName, QString _toolbarList);
    
    /** \brief Scripting function to set context menus in a view mode
    
    @param _modeName Name of the View Mode
    @param _toolboxList ; seperated list of context menus in the view mode
    */
    void addViewModeContextMenus(QString _modeName, QString _contextMenuList);
    
    /** \brief Scripting function to set an icon for a view mode
    
    @param _modeName Name of the View Mode
    @param _toolboxList Name of the Icon File. Will be taken from OpenFlippers Icon directory
    */
    void addViewModeIcon(QString _modeName, QString _iconName);    

    /** @} */

   //===========================================================================
    /** @name Basic functions
    * @{ */
   //===========================================================================
public slots:
  /** \brief Load a new Object ( this may also be an ini or ofs file )
   *
   * This function tries to get the type of data to be loaded from the filename 
   * and then load the file.
   *
   *  @param _filename Filename of the data
   *  @return id of object otherwise -1
   */
  int loadObject ( QString _filename );
  
private slots:
  /** Do a reset of the scenegraph (bounding box update,...)
   *
   * @param _resetTrackBall Should the rotation center of the trackball be reset to the scene center?
   */
  void resetScenegraph( bool _resetTrackBall );

 public :

  /** \brief Load an object from the commandline on application start
  *
  * This function is called before the event queue is executed. The filename and parameters
  * are stored. After the event queue is started, all files in this list will be opened.
  * This is necessary as the event queue has to run to schedule the events emitted 
  * during open operations.
  *
  * @param _filename filename of the file to be opened. If it does not contain a full path,
  *                  the current path will be prepended.
  * @param _asPolyMesh Load as a polymesh ( yes/no)
  */
  void commandLineOpen(const char* _filename, bool _asPolyMesh );

  /** \brief Load a script from the commandline on application start
  *
  * This function is called before the event queue is executed. The filename 
  * is stored. After the event queue is started, all files in this list will be opened.
  * This is necessary as the event queue has to run to schedule the events emitted 
  * during open operations.
  *
  * @param _filename filename of the script to be opened. If it does not contain a full path,
  *                  the current path will be prepended.
  */
  void commandLineScript(const char* _filename );

  private slots:

  /** \brief Executed after loading core completly to load files from commandline
  *
  * This slot is automatically called after application startup. All files from the commandline
  * will be loaded by this slot. This is required as the core and the event queue need to be running
  * to emit the required signals to the plugins.
  */
  void slotExecuteAfterStartup();

  private:
    /// Vector storing filenames from commandline to be opened after application startup (objects)
    std::vector< std::pair < std::string , bool >  > commandLineFileNames_;
    
    /// Vector storing filenames from commandline to be opened after application startup (script files)
    std::vector< std::string > commandLineScriptNames_;

  public:

  /** Add an empty Object of the given Type
  * @return id of the new object or -1 if unsupported
  */
  int addEmptyObject( DataType _type );

  /** \brief Load object of the given Type with given filename
   *
   * This function should not be used anymore. \n
   * The extension is now used to check for the plugin handling the given types.
   *
   * @return id of the new object or -1 if unsupported
   */
  int loadObject( DataType _type, QString _filename);

  /** @} */

  //===========================================================================
  /** @name  Video Stream creation
  * @{ */
  //===========================================================================
  private slots:
    /// Slot called everytime the view is updated
    void viewUpdated();

    /// Function called for every frame when capturing video
    void captureVideo();

  public slots:

    /// Start video capturing
    void startVideoCapture(QString _baseName, int _fps, bool _captureViewers);

    /// Stop video capturing
    void stopVideoCapture();

  private:
    QTimer videoTimer_;
    QTime  lastVideoTime_;

    int captureType_;

    bool capture_;

    int lastWidth_;
    int lastHeight_;

  /** @} */
  //===========================================================================
    /** @name Load / Save slots
    * @{ */
  //===========================================================================

  public slots:

    /** Save object with given id
      * @param _id id of the object
      */
    bool saveObject( int _id, QString _filename );
    
    void saveObject( int _id, QString _filename, int _pluginID );
    
    void saveObjects( IdList _ids, QString _filename, int _pluginID );

    /** Show dialog for saving an object to a new location
      * @param _id id of the object
      * @param _filename current filename of the object
      */
    bool saveObjectTo( int _id, QString _filename );

    bool saveObjectsTo( IdList _ids, QString _filename );
      
    /// Slot for saving objects from Menu
    void saveAllObjects();

    /// Slot for saving objects to a new location
    void saveAllObjectsTo();

    /// Save current status to a settings file
    void saveSettings();

    /// Open Load Widget
    void loadObject();

    /// Load status from file
    void loadSettings();

    /// Load status from file
    void loadSettings(QString _filename);

    /// Get object id from filename
    int getObjectId(QString _filename);

  /** @} */

  //===========================================================================
    /** @name Basic slots
    * @{ */
  //===========================================================================
   private slots :

      /// Gets called by examiner widget when mouse is moved in picking mode
      void slotMouseEvent( QMouseEvent* _event );

      /// Gets called by examiner widget when Wheel is moved in picking mode
      void slotWheelEvent( QWheelEvent * _event, const std::string & _mode);

      /** \brief Open the add Empty dialog
      *
      * This slot shows the addEmpty dialog which is used to add empty objects of supported dataTypes
      */
      void slotAddEmptyObjectMenu();

      /// Slot adding empty object of a given type
      void slotAddEmptyObject( DataType _type , int& _id );

      /// Slot copying an object
      void slotCopyObject( int _oldId , int& _newId );

      /// Exit Application
      void slotExit();

      /// Open Recent file
      void slotRecentOpen(QAction* _action);

   public slots:

    /// Add a Toolbox from a plugin or from scripting
     void addToolbox(QString _name ,QWidget* _widget);

   private :

   //===========================================================================
    /** @name Scenegraph
    * @{ */
   //===========================================================================

   private:
      /// Scenegraphs root node
      SeparatorNode* root_node_scenegraph_;
      
      /// Seperator node for global nodes
      SeparatorNode* root_node_scenegraph_global_;

      /// Separator Node holding all core scenegraph nodes
      SeparatorNode* core_nodes_;
      
      
      ///Toplevel Nodes for data objects
      SeparatorNode* dataSeparatorNode_;
      
      /// Root Node for data objects
      SeparatorNode*  dataRootNode_;

      /// Node for coordsys Material
      ACG::SceneGraph::MaterialNode* coordsysMaterialNode_;

      /// Node for the coordinate system
      ACG::SceneGraph::CoordsysNode* coordsysNode_;

      /// Node for the grid
//       ACG::SceneGraph::GridNode* gridNode_;

   /** @} */

   //===========================================================================
    /** @name IniFile and Options Handling
    * @{ */
   //===========================================================================

   /// Get all ini files and set basic paths and options
   void setupOptions();

   /// Read Options that needs the GUI to be set up completely
   void readGUIOptions(INIFile& _ini);

   /// Read recent files from ini-file
   void readRecentFiles(QString _filename);

   /// Get and set Application options from ini file
   void readApplicationOptions(INIFile& _ini);

   /// Write Application options to ini file
   void writeApplicationOptions(INIFile& _ini);

   /// Restore key assignments from configs files
   void restoreKeyBindings();

  public slots:

   /// Save the current options to the standard ini file
   void saveOptions();

   /// after ini-files have been loaded and core is up or if options have been changed -> apply Options
   void applyOptions();

   /** \brief Load information from an ini file
    *
    * This function will open an ini file and load the information in it.
    *
    * @param _filename Name of the ini file
    * @param _coreSettings      Load core settings from the file
    * @param _perPluginSettings Load per plugin settings from the file
    * @param _loadObjects       Load objects defined in the ini file
    *
    */
   void openIniFile( QString _filename,
                     bool    _coreSettings ,
                     bool    _perPluginSettings,
                     bool    _loadObjects );

  private:

   /** \brief Write current status to ini file (Application and File Options)
    *
    *  Writes the complete status to an ini file ( All open objects and their Information )
    *
    * @param _filename filename of the ini file to write with full path
    * @param _relativePaths This defines if the paths to the objects should be made relative
    * @param _targetOnly Select if we want all open objects or only the ones which are selected as target.
    * @param _saveSystemSettings Choose if you also want to save system settings into the ini file.
    * @param _savePluginSettings Choose if you want to save per Plugin global settings into the ini file.
    * @param _saveObjectInfo If you want to store information about all open objects this has to be true
    */
   void writeIniFile( QString _filename,
                      bool    _relativePaths,
                      bool    _targetOnly,
                      bool    _saveSystemSettings,
                      bool    _savePluginSettings ,
                      bool    _saveObjectInfo );

   /** \brief Write current status to obj file (Application and File Options)
    *
    *  Writes the complete status to an obj file ( All open objects and their Information )
    */
   void writeObjFile(QString _filename, bool _relativePaths, bool _targetOnly);

   /// Called if app is closed and writes all information to ini file
   void writeOnExit();

   /** @} */

   
  //===========================================================================
  /** @name Logging
  * @{ */
  //===========================================================================

  signals:
    /// Logg with OUT,WARN or ERR as type
    void log(Logtype _type , QString _message );

    /// Default logging as OUT
    void log(QString _message );

    /// Logging signal for ScriptEngine
    void scriptLog(QString _message);

    /// This signal is emitted to send log data to a plugin
    void externalLog(Logtype _type , QString _message);

  private slots:

    /// Console logger
    void slotLog(Logtype _type, QString _message);

    /// log to file
    void slotLogToFile(Logtype _type, QString _message);

  private:
    ///stream for logging to file
    QTextStream* logStream_;

    ///logfile
    QFile* logFile_;

  public :
    void scriptLogFunction( QString _output);

  /** @} */


  //===========================================================================
  /** @name Signal and Slot processing for Plugins
  * @{ */
  //===========================================================================

  private :
    /// Check if a plugin has a slot
    bool checkSlot(QObject* _plugin , const char* _slotSignature);

    /// Check if a plugin has a signal
    bool checkSignal(QObject* _plugin , const char* _signalSignature);

  /** @} */

  //===========================================================================
    /** @name Plugin Management
      * @{ */
  //===========================================================================

  private:
    /// List of all loaded plugins
    std::vector<PluginInfo> plugins;

    /// Index of Plugins toolbox widget
    int toolboxindex_;

    /// Function for loading Plugins
    void loadPlugin(QString filename, bool silent, QObject* _plugin = 0 );

    /// Load all plugins from default plugin directory and from INI-File
    void loadPlugins();
  private slots:
    /// Show Plugins Dialog
    void slotShowPlugins();

    /// Function for unloading Plugins
    void unloadPlugin(QString name);

    /// Load Plugins from menu
    void slotLoadPlugin();

  /** @} */


  //===========================================================================
    /** @name Scripting support
      * @{ */
  //===========================================================================

  signals:

    void scriptInfo( QString _pluginName , QString _functionName  );

    void executeScript( QString _script );

    void executeFileScript( QString _filename );

    void setSlotDescription(QString     _slotName,   QString     _slotDescription,
                            QStringList _parameters, QStringList _descriptions);

  public slots:
    /** \brief Create an script object from a ui file
     *
     * This function will load an ui file, set up a qwidget from that and makes it available
     * under _objectName for scripting.
     * @param _objectName The name in scripting environment used for the new object
     * @param _uiFilename ui file to load
     */
    void createWidget(QString _objectName, QString _uiFilename);

    /// Set the active ViewMode
    void setViewMode(QString _viewMode);

    /// Set the icon of a viewMode
    void setViewModeIcon(QString _mode, QString _iconName);

  private :
    /// Core scripting engine
    QScriptEngine scriptEngine_;

    /// Wrappers for plugin scripting
    std::vector<ScriptingWrapper*> scriptingWrappers_;

    /// List of all registered scripting functions
    QStringList scriptingFunctions_;

    /// Prototype for the Vector type
    prototypeVec3d vec3dPrototype_;
    
    /// Prototype for the DataType
    prototypeDataType DataTypePrototype_;

    /// Prototype for the Matrix type
    prototypeMatrix4x4 matrix4x4Prototype_;


  private slots:
    void slotScriptInfo( QString _pluginName , QString _functionName  );

    void slotExecuteScript( QString _script );

    void slotGetScriptingEngine( QScriptEngine*& _engine  );

    void slotGetAllAvailableFunctions( QStringList& _functions  );

    /// set a description for one of the plugin's public slots
    void slotSetSlotDescription(QString     _slotName,   QString _slotDescription,
                                QStringList _parameters, QStringList _descriptions);
    /// get available descriptions for a given public slot
    void slotGetDescription(QString _function, QString& _fnDescription,
                                QStringList& _parameters, QStringList& _descriptions );

  private:

    QList< SlotInfo > coreSlots_;

    void setDescriptions();

  /** @} */

  //===========================================================================
    /** @name RPC ( Remote procedure Call) support
      * @{ */
  //===========================================================================
  private slots:
    void slotPluginExists( QString _pluginName , bool& _exists );


    void slotFunctionExists( QString _pluginName , QString _functionName , bool& _exists  );

    /** This slot executes a function of a plugin.
     * If it does not exist, _success will be false
     * @param _pluginName Plugin where the function is implemented
     * @param _functionName name of the function ( Standard name, no parameters allowed!)
     * @param _success successfull execution?
     */
    void slotCall( QString _pluginName , QString _functionName , bool& _success  );

    /** This slot executes the given expression.
     * No checks are performed if the remote function is available.
     * @param _expression command to execute
     * @param _success successfull execution?
     */
    void slotCall( QString _expression , bool& _success  );

    /** This slot executes the given expression and returns the result
     *  No checks are performed if the remote function is available.
     *  if an error occurs the result contains an invalid QVariant
     *
     * ex. getValue("databaseplugin.tableExists(\"meshes\")", result) )
     *     result.toBool() == true
     *
     * @param _expression command to execute
     * @param _result The return value of the command
     */
    void slotGetValue(QString _expression, QVariant& _result );

  /** @} */

  //===========================================================================
    /** @name Scenegraph redraw handling
      * @{ */
  //===========================================================================

  private slots:

    /// Called to check if the scenegraph needs to be redrawn
    void checkScenegraphDirty();

  private:

    /// Timer that starts scenegraph check
    QTimer *scenegraphCheckTimer_;

    /// Holds the time since last redraw
    QTime *redrawTime_;

  /** @} */
  
  
  //===========================================================================
  /** @name Process Interface and Controls
  * @{ */
  //===========================================================================
  
  private:
    
    QList< JobInfo* >  currentJobs;
    
    ProcessManagerWidget* processManager_;
    
    /// Find a job in the jobslist
    bool getJob(QString _jobId, int& _index);
    
  private slots:

    /// A job has been started by a plugin
    void slotStartJob( QString _jobId, QString _description , int _min , int _max,bool _blocking );
    
    /// A job state has been updated by a plugin
    void slotSetJobState(QString _jobId, int _value );
    
    /// A job's widget caption has been updated by a plugin
    void slotSetJobName(QString _jobId, QString _name );
    
    /// A job's widget's status text has been updated by a plugin
    void slotSetJobDescription(QString _jobId, QString _text );
    
    /// A job state has been canceled by a plugin
    void slotCancelJob(QString _jobId );
    
    /// A job state has been finished by a plugin
    void slotFinishJob(QString _jobId );
    
    /// Called by dialogs if cancel button is pressed
    void slotJobCancelRequested(QString _jobId);
    
  signals:
    
    void jobCanceled( QString _jobId );
    
  /** @} */
  
  //===========================================================================
  /** @name Object Manager
  * @{ */
  //===========================================================================

  private slots:
    
    /// This slot is called by the object manager when a new object is created
    void newObject(int _objectId);
    
    /// This slot is called by the object manager when an object is deleted
    void deletedObject(int _objectId);    
    
  /** @} */
  
  
  private:
    /** \brief OpenGL capability check 
    *
    * Checks if the OpenGL Capabilities of the graphics card are sufficient and
    * prints an error message if not.
    */
    bool checkOpenGLCapabilities();
  
  
  private :

  /// Id for the next backup
  int nextBackupId_;

  /// Logger interfaces between plugins and core logger
  std::vector<PluginLogger*> loggers_;

  /// File-Plugins
  std::vector<fileTypes> supportedTypes_;
  
  /// Type-Plugins
  std::vector<dataTypes> supportedDataTypes_;

  private :
    ///Pointer to the data rootNode;
    BaseObject* objectRoot_;

    /// The main applications widget ( only created in gui mode )
    CoreWidget* coreWidget_;

    /// SplashScreen, only used in gui mode
    QSplashScreen* splash_;

    /// Last Splash message;
    QString splashMessage_;

    /// List of available draw modes
    QVector<ViewMode*> viewModes_;

    /// If enabled, this timer will block screen refresh if done more then 30 times per second.
    QTimer* redrawTimer_;


};

/// Special print function for core logger
QScriptValue myPrintFunction(QScriptContext *context, QScriptEngine *engine);

//=============================================================================
#endif // MVIEWWIDGET_HH defined
//=============================================================================

