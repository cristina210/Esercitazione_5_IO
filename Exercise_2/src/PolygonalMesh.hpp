#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    // from Cell0
    // number of cell0D
    unsigned int NumberCell0D = 0;
    // Id of each point in mesh
    std::vector<unsigned int> Cell0DId = {};
    // coordinates of each point
    std::vector<Vector2d> Cell0DCoordinates = {};
    // map for linking each marker (key) with the list of vertices Id associated with that marker
    std::map<unsigned int, list<unsigned int>> Cell0DMarkers = {};

    // from Cell1D
    // number of cell1D
    unsigned int NumberCell1D = 0;
    // Id of each edge in mesh
    std::vector<unsigned int> Cell1DId = {};
    // two vertices Id of each edge (origin and end)
    std::vector<Vector2i> Cell1DVertices = {};
    // map for linking each marker (key) with the list of edges Id associated with that marker
    std::map<unsigned int, list<unsigned int>> Cell1DMarkers = {};

    // from Cell2D
    // number of Cell2D
    unsigned int NumberCell2D= 0;
    // Id of each polygon in mesh
    std::vector<unsigned int> Cell2DId = {};
    // number of polygon's vertices
    std::list<unsigned int> NumberVertices = {};
    // vertices Id of each polygon
    /// the number of vertices and edges is not fixed. Therefore, instead of array,
    /// vectors from std library are exploited in order to easily access vector's elements.
    std::vector<vector<unsigned int>> Cell2DVertices = {};
    // number of polygon's edges
    std::list<unsigned int> NumberEdges  = {};
    // edges Id of each polygon
    std::vector<vector<unsigned int>> Cell2DEdges = {};
    // map for linking each marker (key) with the list of polygon Id associated with that marker
    std::map<unsigned int, list<unsigned int>> Cell2DMarkers = {};

};

}

