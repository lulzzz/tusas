//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Los Alamos National Security, LLC.  This file is part of the
//  Tusas code (LA-CC-17-001) and is subject to the revised BSD license terms
//  in the LICENSE file found in the top-level directory of this distribution.
//
//////////////////////////////////////////////////////////////////////////////



#ifndef POST_PROCESS_H
#define POST_PROCESS_H

#include "Mesh.h"

//teuchos support
#include <Teuchos_RCP.hpp>

// Epetra support
#include "Epetra_Vector.h"
#include "Epetra_Map.h"

//template<class Scalar>
/// Creates a nodal post process variable as a function of the solution and gradient. 
class post_process
{
public:
  /// Constructor
  /** Creates a post process variable with name ="pp"+std::to_string(index_) */
  post_process(const Teuchos::RCP<const Epetra_Comm>& comm, Mesh *mesh, const int index);
  /// Destructor
  ~post_process();
  /// Write the post process variable to exodus.
  void update_mesh_data();
  /// Compute the post process variable with index i
  void process(const int i,const double *u, const double *gradu);
  /// Pointer to the post process function.
  double (*postprocfunc_)(const double *u, const double *gradu);

private:
  /// Mesh object.
  Mesh *mesh_;
  /// This post process variable index.
  int index_;
  /// MPI comm object.
  const Teuchos::RCP<const Epetra_Comm>  comm_;
  /// Node map object.
  Teuchos::RCP<const Epetra_Map>   node_map_;
  /// Vector of the nodal values.
  Teuchos::RCP<Epetra_Vector> ppvar_;

};

#endif
