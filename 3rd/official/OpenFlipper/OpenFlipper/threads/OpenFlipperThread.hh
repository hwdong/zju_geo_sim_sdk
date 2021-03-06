//=============================================================================
//
//                               OpenFlipper
//        Copyright (C) 2008 by Computer Graphics Group, RWTH Aachen
//                           www.openflipper.org
//
//-----------------------------------------------------------------------------
//
//                                License
//
//  OpenFlipper is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  OpenFlipper is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with OpenFlipper.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
//
//   $Revision: 9251 $
//   $Author: kremer $
//   $Date: 2010-05-10 15:26:35 +0200 (Mo, 10. Mai 2010) $
//
//=============================================================================


#ifndef OPENFLIPPERTHREAD_HH
#define OPENFLIPPERTHREAD_HH

#include <QThread>
#include <QSemaphore>

#include <OpenFlipper/common/GlobalDefines.hh>

/**
\class OpenFlipperThread

    Instanciate this class in order to provide a thread
    to a plugin. Unless you don't need a specialized
    run() or cancel() function, it won't be necessary to
    reimplement this class. Just connect the signals
    for the thread to work properly.
        
    Note: Updating GUI elements of the main window from
    within a thread which is not the main thread can
    cause unexpected crashes to OpenFlipper. This introduces
    some major limitations to the usage of threads
    in plugins. These include avoiding the creation
    of new objects and generally every function that
    produces logging messages.

    The following code fragment shows a simple example
    of how to use this class from within a plugin:

\code
void MyPlugin::launchThread() {

    OpenFlipperThread* myThread = new OpenFlipperThread("MyPluginsThread");

    // Connect the appropriate signals
    connect(myThread, SIGNAL(function()), this, SLOT(myPluginsThreadFunction()), Qt::DirectConnection);

    // Tell core about my thread
    // Note: The last parameter determines whether the thread should be blocking
    emit startJob( "MyPluginsThread", "Thread Description" , 0 , 100 , true);

    // Start internal QThread
    myThread->start();

    // Start actual processing of job
    myThread->startProcessing();

}

void MyPlugin::myPluginsThreadFunction() {
   
   emit setJobState("MyPluginsThread", 0);
   
   // Do something...
   for(int i = 0; i < 100; ++i) {
   
       // Do something...
       
       // Update process' progress bar status
       emit setJobState("MyPluginsThread", i);
   }
   
   emit finishJob("MyPluginsThread");
}
\endcode
*/

class OpenFlipperJob;

class DLLEXPORT OpenFlipperThread : public QThread
{
  Q_OBJECT
  
  public:
    OpenFlipperThread( QString _jobId );
    ~OpenFlipperThread();
    
  //===========================================================================
  /** @name Advanced job processing
  * @{ */
  //===========================================================================
  public:
    
    /** \brief Main processing
    *
    * Either reimplement this function or connect the function()
    * signal.
    */
    virtual void run();
    
    /** \brief Cancel the job
    *
    * Reimplement this function to correctly terminate your job.
    * If your job is able to terminate correctly then you can reimplement this function
    * and stop your process.
    */
    virtual void cancel();   
    
  public slots:
    /** Call this slot with the correct job id to abort processing
    * This directly calls cancel()
    * This is only usefull when you derived from this class, as other jobs might not react on this slot
    */
    void slotCancel( QString _jobId);
    
  signals:
    /** \brief Tell core about job state
    *
    * Emit this signal to tell the core about your job status. You have to create a new run function for
    * this. In simple mode, this signal is not emitted at all!
    */
    void state( QString _jobId, int _state );
    
  /** @} */
    
    
  //===========================================================================
  /** @name Simple job processing
  * @{ */
  //===========================================================================
    
  signals:
    /**  \brief job function
    *
    * If you do not specialize the OpenFlipperThread, The function connected to this 
    * signal will be used as the processing function for your thread. When you call
    * OpenFlipper::startProcessing(); \n
    *
    * If you want to provide more feedback (% of runtime) or cancel the job,
    * you have to derive from OpenFlipperThread and emit the right signals.
    * 
    * You have connect one of your slot using \n
    * connect( OpenFlipperThread ,SIGNAL(function()),YourPlugin,SLOT(YourSlot(),Qt::DirectConnection) );\n
    * The default implementation will call your slot inside the given thread and the core will still respond.
    * However you should only use this function if you Dont know how long your job takes. Or when
    * you just want to keep the core responding.\n
    * Otherwise you should reimplement the run(), and cancel() function of OpenFlipperThread and emit the state signal.
    *
    * The optional parameter contains the job's id. In some cases the function that is to be called needs
    * the job's id for further processing (status updates, etc.)
    */
    void function(const QString _jobId = "");
    
    /** \brief job done
    *
    * This signal is emitted if your job has finished and should be used to tell the core that your job has finished.
    *
    */
    void finished( QString _jobId );
    
    
    
  public slots:
    /** \brief start processing
    *
    * This function will start the actuall processing of a job.
    */
    void startProcessing();
    
  /** @} */
    
    
  private slots:
    /** \brief job has finished
    * 
    * Called by the job wrapper, when the job is done.
    */
    void slotJobFinished();
  
  signals:
    /** \brief start processing of a function
    *
    * (INTERNAL!) \n
    * This signal is used to start the process execution through the wrapper
    */
    void startProcessingInternal();
    
  private: 
    /** \brief Internal job wrapper
    *
    * (INTERNAL!) \n
    * This wrapper is used to start slots inside the event queue of the current thread.
    * All slots defined in the QThread object live in the callers thread(The main thread).
    * All slots inside the wrapper live in the thread created by QThread. and therefore
    * do not lock the main event loop
    */
    OpenFlipperJob* job_;
    
    /** \brief Id of the current job
    *
    * This holds the id of the current job. Most functions only react if the correct id is passed
    * to the function.
    */
    QString jobId_;
    
    /** \brief Semaphore to control order of thread startup calls
    *
    * This variable is used to control the order of thread startup calls. The Thread itself is
    * started, and when it is up and running, the resource will be created. The core thread waits
    * for this resource and afterwards starts execution of the threads processing function.
    * Without this sync, the processing call of the main thread might get lost as the thread is
    * not online and listening for the signal.
    */
    QSemaphore startup_;

};


// ================================================================================
// Job wrapper
// ================================================================================

/** \brief Internal Job execution object
*
* This class is used to start a process within a thread. The thread object itself
* lives in the event queue of the object that crreated the thread. So every signal
* or slot within the qthread object will be dispatched in the core event loop and
* therefore lock the gui. 
* Objects created in the qthread will run in the threads event queue as well as their
* signals and slots. So qthread uses this object to actually run arbitrary threads 
* inside the threads event queue.
*/
class DLLEXPORT OpenFlipperJob : public QObject
{
  Q_OBJECT
  
  public:
    OpenFlipperJob(const QString _jobId) : jobId_(_jobId) {}
    ~OpenFlipperJob();
  
  signals:
    /** \brief connection to actual processing function
    *
    * This signal has to be connected via a Qt::DirectConnection to an
    * arbitrary slot. This slot will be executed in the local event queue.
    * If this object is created in a QThread, than the slot will be run 
    * inside this thread.
    */
    void process(const QString _jobId = "");
    
    /** \brief Job done
    *
    * This signal is emitted, when the job has finished
    */
    void finished();
    
  public slots:
    /** \brief slot to start processing
    *
    * If this slot is called, the slot connected to process() will be executed
    * in the current thread.
    */
    void startJobProcessing();
    
  public:
    /// Set job's id
    void jobId(const QString& _jobId) { jobId_ = _jobId; }
    
    /// Get job's id
    QString jobId() const { return jobId_; }   
    
  private:
    /// The job's id
    QString jobId_;
};



#endif //OPENFLIPPERTHREAD_HH
