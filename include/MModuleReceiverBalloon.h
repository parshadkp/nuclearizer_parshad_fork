/*
 * MModuleReceiverBalloon.h
 *
 * Copyright (C) by Alex Lowell & Andreas Zoglauer.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MModuleReceiverBalloon__
#define __MModuleReceiverBalloon__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:
#include <list>
#include <fstream>
using namespace std;

// ROOT libs:

// MEGAlib libs:
#include "MGlobal.h"
#include "MTransceiverTcpIpBinary.h"

// Nuclearizer libs
#include "MModule.h"
#include "MBinaryFlightDataParser.h"
#include "MGUIExpoAspectViewer.h"
#include "MGUIExpoReceiver.h"

// Forward declarations:

  
////////////////////////////////////////////////////////////////////////////////


class MModuleReceiverBalloon : public MModule, public MBinaryFlightDataParser
{
  // public interface:
 public:
   
  //! Default constructor
  MModuleReceiverBalloon();
  //! Default destructor
  virtual ~MModuleReceiverBalloon();
  
  //! Create a new object of this class 
  virtual MModuleReceiverBalloon* Clone() { return new MModuleReceiverBalloon(); }
  
  //! Return the name of the transmitting computer
  MString GetDistributorName() const { return m_DistributorName; }
  //! Set the name of the transmitting computer
  void SetDistributorName(MString DistributorName) { m_DistributorName = DistributorName; }
  
  //! Return the port of the transmitting computer
  int GetDistributorPort() const { return m_DistributorPort; }
  //! Set the port of the transmitting computer
  void SetDistributorPort(int DistributorPort) { m_DistributorPort = DistributorPort; }

  //! Return the stream ID to be transmitted
  MString GetDistributorStreamID() const { return m_DistributorStreamID; }
  //! Set the ID of the stream which should be transmitted
  void SetDistributorStreamID(MString DistributorStreamID) { m_DistributorStreamID = DistributorStreamID; }

  //! Return the local receiving host name
  MString GetLocalReceivingHostName() const { return m_LocalReceivingHostName; }
  //! Set the name of the local receiveing host
  void SetLocalReceivingHostName(MString LocalReceivingHostName) { m_LocalReceivingHostName = LocalReceivingHostName; }
  
  //! Return the port of the local receiving host computer
  int GetLocalReceivingPort() const { return m_LocalReceivingPort; }
  //! Set the port of the local receiving host computer
  void SetLocalReceivingPort(int LocalReceivingPort) { m_LocalReceivingPort = LocalReceivingPort; }
 
  //! Get the file name
  MString GetRoaFileName() const { return m_RoaFileName; }
  //! Set the file name
  void SetRoaFileName(const MString& Name) { m_RoaFileName = Name; }
 
  //! Return if the module is ready to analyze events
  virtual bool IsReady();
  
  //! Create the expos
  virtual void CreateExpos();
  
  //! Initialize the module
  virtual bool Initialize();

  //! Finalize the module --- can be overwritten
  virtual void Finalize();

  //! Main data analysis routine, which updates the event to a new level 
  virtual bool AnalyzeEvent(MReadOutAssembly* Event);

  //! Show the options GUI
  virtual void ShowOptionsGUI();

  //! Read the configuration data from an XML node
  virtual bool ReadXmlConfiguration(MXmlNode* Node);
  //! Create an XML node tree from the configuration
  virtual MXmlNode* CreateXmlConfiguration();



  // protected methods:
 protected:
  //! Request connection
  bool RequestConnection();
  //! End connection
  bool EndConnection();

  // private methods:
 private:


  // protected members:
 protected:


  // private members:
 private:
 
  //! A GUI to display the aspect data 
  MGUIExpoAspectViewer* m_ExpoAspectViewer;
  //! A GUI to display the received data statistics 
  MGUIExpoReceiver* m_ExpoReceiver;
 
 
  //! The name of the computer from which we receive the data
  MString m_DistributorName;
  //! The port on the computer from which we receive the data
  int m_DistributorPort;
  //! The stream ID which we want to receive
  MString m_DistributorStreamID;

  //! Request an host and port from the distributor
  bool m_RequestConnection;
  //! Where to send the data to
  MString m_LocalReceivingHostName;
  //! Port to send the data to
  int m_LocalReceivingPort;

  //! ROA save file name
  MString m_RoaFileName;
  
  //! The transceiver
  MTransceiverTcpIpBinary* m_Receiver;

  //! The total received data
  long m_ReceivedData;
  //! Timer whne the last update summary was shown
  
  //! Output stream for roa file
  ofstream m_Out;

  
#ifdef ___CLING___
 public:
  ClassDef(MModuleReceiverBalloon, 0) // no description
#endif

};

#endif



////////////////////////////////////////////////////////////////////////////////
