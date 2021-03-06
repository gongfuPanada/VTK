/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPSurfaceLICInterface.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPSurfaceLICInterface - parallel parts of the vtkSurfaceLICInterface
//
// .SECTION Description
// Parallel parts of the vtkSurfaceLICInterface, see that class for
// documentation.

#ifndef vtkPSurfaceLICInterface_h
#define vtkPSurfaceLICInterface_h

#include "vtkSurfaceLICInterface.h"
#include "vtkRenderingParallelLICModule.h" // For export macro
#include <string> // for string

class vtkPainterCommunicator;

class VTKRENDERINGPARALLELLIC_EXPORT vtkPSurfaceLICInterface : public vtkSurfaceLICInterface
{
public:
  static vtkPSurfaceLICInterface* New();
  vtkTypeMacro(vtkPSurfaceLICInterface, vtkSurfaceLICInterface);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Methods used for parallel benchmarks. Use cmake to define
  // vtkSurfaceLICInterfaceTIME to enable benchmarks. During each
  // update timing information is stored, it can be written to
  // disk by calling WriteLog.
  virtual void WriteTimerLog(const char *fileName);

protected:
  vtkPSurfaceLICInterface();
  ~vtkPSurfaceLICInterface();

  // Description:
  // Get the min/max across all ranks. min/max are in/out.
  // In serial operation this is a no-op, in parallel it
  // is a global collective reduction.
  virtual void GetGlobalMinMax(
        vtkPainterCommunicator *comm,
        float &min,
        float &max);

  // Description:
  // Creates a new communicator with/without the calling processes
  // as indicated by the passed in flag, if not 0 the calling process
  // is included in the new communicator. In parallel this call is mpi
  // collective on the world communicator. In serial this is a no-op.
  virtual vtkPainterCommunicator *CreateCommunicator(int include);

  // Description:
  // Ensure that if any rank udpates the communicator they all
  // do. This is a global collective operation.
  virtual bool NeedToUpdateCommunicator();

  // Description:
  // Methods used for parallel benchmarks. Use cmake to define
  // vtkSurfaceLICInterfaceTIME to enable benchmarks. During each
  // update timing information is stored, it can be written to
  // disk by calling WriteLog.
  virtual void StartTimerEvent(const char *name);
  virtual void EndTimerEvent(const char *name);

private:
  std::string LogFileName;

private:
  vtkPSurfaceLICInterface(const vtkPSurfaceLICInterface&); // Not implemented.
  void operator=(const vtkPSurfaceLICInterface&); // Not implemented.
};

#endif
