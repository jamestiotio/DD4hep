//==========================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : A. Sailer
//
//==========================================================================
#ifndef DDCAD_UTILITIES_H
#define DDCAD_UTILITIES_H

#include <vector>

#include <TGeoTessellated.h>
#include <TGeoVector3.h>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  /// Namespace for implementation details of the AIDA detector description toolkit
  namespace cad  {

    inline std::stringstream streamFacet(TGeoFacet const& facet,
					 TGeoTessellated const& shape) {
      using ::operator<<;
      std::stringstream str;
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,31,1)
      str << "{";
      for (int i = 0; i < facet.GetNvert(); ++i) {
	str << shape.GetVertex(facet[i]);
	if (i != facet.GetNvert() - 1)
	  str << ", ";
      }
      str << "}";
#else
      str << facet;
#endif
      return str;
    }

    inline std::stringstream streamVertices(ROOT::Geom::Vertex_t const& v1,
					    ROOT::Geom::Vertex_t const& v2,
					    ROOT::Geom::Vertex_t const& v3) {
      using ::operator<<;
      std::stringstream str;
      str << "{" << v1 << ", " << v2 <<  ", " << v3 << "}";
      return str;
    }

    // Determine if the facet is degenerated by calculating its determinant
    inline bool facetIsDegenerated(std::vector<ROOT::Geom::Vertex_t> const& vertices){
      const ROOT::Geom::Vertex_t& v1 = vertices[0];
      const ROOT::Geom::Vertex_t& v2 = vertices[1];
      const ROOT::Geom::Vertex_t& v3 = vertices[2];
      constexpr double epsilon = 1.e-20;
      // v1.x v2.x v3.x v1.x v2.x
      //
      // v1.y v2.y v3.y	v1.y v2.y
      //
      // v1.z v2.z v3.z	v1.z v2.z
      double det =  0.0
	+ v1.x() * v2.y() * v3.z()
	+ v2.x() * v3.y() * v1.z()
	+ v3.x() * v1.y() * v2.z()
	- v1.z() * v2.y() * v3.x()
	- v2.z() * v3.y() * v1.x()
	- v3.z() * v1.y() * v2.x();
      return det < epsilon;
    }
  }
}
#endif
