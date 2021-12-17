//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshGenerator.h"

/**
 * Generates a pin-like structure for a square grid with the option to be 2- or 3-D.
 */
class CoreMeshGenerator : public MeshGenerator
{
public:
  static InputParameters validParams();

  CoreMeshGenerator(const InputParameters & parameters);

  std::unique_ptr<MeshBase> generate() override;

protected:
  ///The names of the assemblies that compose the core
  std::vector<MeshGeneratorName> _inputs;
  
  ///The name of "filler" assembly given in the input to represent an empty space in the core pattern
  MeshGeneratorName _empty_key;
  
  ///Whether empty positions are to be used in the pattern 
  bool empty_pos = false;
  
  ///The 2D assembly layout of the core
  std::vector<std::vector<unsigned int>> _pattern;
  
  ///Whether this mesh should be extruded to 3-D, the core is always assumed to be the last 
  bool _extrude;
  
  ///The ReactorMeshParams object that is storing the reactor global information for this reactor geometry mesh
  MeshGeneratorName _reactor_params;
  
  ///The geometry type for the reactor that is stored on the ReactorMeshParams object
  std::string _geom_type;
  
  ///The heights of the axial regions that are stored on the ReactorMeshParams object
  std::vector<Real> _axial_boundaries;
  
  ///The number of mesh divisions in each axial region that are stored on the ReactorMeshParams object
  std::vector<unsigned int> _axial_intervals;
  
  ///A mapping of region IDs and pin-type IDs that are used to allow for extrusion in an ReactorGeometry MeshGenerator
  std::map<subdomain_id_type, std::vector<std::vector<subdomain_id_type>>> _id_map;
  
  ///A mapping of region IDs and assembly-type IDs that are used to allow for extrusion of the assembly ducts in an ReactorGeometry MeshGenerator
  std::map<subdomain_id_type, std::vector<std::vector<subdomain_id_type>>> _duct_id_map;
  
  ///A mapping of region IDs and assembly-type IDs that are used to allow for extrusion of the assembly backgrounds in an ReactorGeometry MeshGenerator
  std::map<subdomain_id_type, std::vector<subdomain_id_type>> _background_id_map;
  

  ///The ultimate name of the mesh for generation. The value of this string depends on whether the mesh is extruded.
  std::string mesh_name;  
  
  /// The final mesh that is generated by the subgenerators; 
  /// This mesh is generated by the subgenerators with only element and boundary IDs changed.
  std::unique_ptr<MeshBase> * _build_mesh;
};