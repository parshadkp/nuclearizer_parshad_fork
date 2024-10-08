/*
 * MGUIExpoEnergyCalibration.cxx
 *
 *
 * Copyright (C) by Andreas Zoglauer.
 * All rights reserved.
 *
 *
 * This code implementation is the intellectual property of
 * Andreas Zoglauer.
 *
 * By copying, distributing or modifying the Program (or any work
 * based on the Program) you indicate your acceptance of this statement,
 * and all its terms.
 *
 */


// Include the header:
#include "MGUIExpoEnergyCalibration.h"

// Standard libs:

// ROOT libs:
#include <TSystem.h>
#include <TString.h>
#include <TGLabel.h>
#include <TGResourcePool.h>
#include <TCanvas.h>

// MEGAlib libs:
#include "MStreams.h"



////////////////////////////////////////////////////////////////////////////////


#ifdef ___CLING___
ClassImp(MGUIExpoEnergyCalibration)
#endif


////////////////////////////////////////////////////////////////////////////////


MGUIExpoEnergyCalibration::MGUIExpoEnergyCalibration(MModule* Module) : MGUIExpo(Module)
{
  // standard constructor

  // Set the new title of the tab here:
  m_TabTitle = "Energy Calibration";

  // Add all histograms and canvases below
  m_Energy = new TH1D("", "Spectrum combined hits", 200, 0, 1000);
  m_Energy->SetXTitle("Energy [keV]");
  m_Energy->SetYTitle("counts");
  m_Energy->SetFillColor(kAzure+7);

  m_EnergyCanvas = 0;

  // use hierarchical cleaning
  SetCleanup(kDeepCleanup);
}


////////////////////////////////////////////////////////////////////////////////


MGUIExpoEnergyCalibration::~MGUIExpoEnergyCalibration()
{
  // kDeepCleanup is activated 
}


////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::Reset()
{
  //! Reset the data in the UI

  m_Mutex.Lock();

  m_Energy->Reset();
  
  m_Mutex.UnLock();
}
  

////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::SetEnergyHistogramParameters(int NBins, double Min, double Max)
{
  // Set the energy histogram parameters 

  m_Mutex.Lock();

  m_Energy->SetBins(NBins, Min, Max);
  
  m_Mutex.UnLock();
}


////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::AddEnergy(double Energy)
{
  // Add data to the energy histogram

  m_Mutex.Lock();

  m_Energy->Fill(Energy);
  
  m_Mutex.UnLock();
}


////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::Export(const MString& FileName)
{
  // Add data to the energy histogram

  m_Mutex.Lock();

  m_EnergyCanvas->GetCanvas()->SaveAs(FileName);
  
  m_Mutex.UnLock();
}


////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::Create()
{
  // Add the GUI options here

  // Do not create it twice!
  if (m_IsCreated == true) return;

  m_Mutex.Lock();
  
  TGLayoutHints* CanvasLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY,
                                                  2, 2, 2, 2);

  TGHorizontalFrame* HFrame = new TGHorizontalFrame(this);
  AddFrame(HFrame, CanvasLayout);

  
  m_EnergyCanvas = new TRootEmbeddedCanvas("Energy", HFrame, 100, 100);
  HFrame->AddFrame(m_EnergyCanvas, CanvasLayout);

  m_EnergyCanvas->GetCanvas()->cd();
  m_EnergyCanvas->GetCanvas()->SetGridy();
  m_EnergyCanvas->GetCanvas()->SetGridx();
  m_Energy->Draw();
  m_EnergyCanvas->GetCanvas()->Update();
  
  m_IsCreated = true;
  
  m_Mutex.UnLock();
}


////////////////////////////////////////////////////////////////////////////////


void MGUIExpoEnergyCalibration::Update()
{
  //! Update the frame

  m_Mutex.Lock();

  if (m_EnergyCanvas != 0) {
    m_EnergyCanvas->GetCanvas()->Modified();
    m_EnergyCanvas->GetCanvas()->Update();
  }
  
  m_Mutex.UnLock();
}


// MGUIExpoEnergyCalibration: the end...
////////////////////////////////////////////////////////////////////////////////
