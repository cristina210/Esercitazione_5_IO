#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
// Import the polygonal mesh and test if the mesh is correct
// mesh: a PolygonalMesh struct
// return a boolean value, true if the mesh is correcly built, false otherwise
bool ImportMesh(const string &filepath,PolygonalMesh& mesh);

// Import the Cell0D properties from Cell0Ds.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(const string &filename,PolygonalMesh& mesh);

// Import the Cell1D properties from Cell1Ds.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(const string &filename,PolygonalMesh& mesh);

// Import the Cell2D properties from Cell2Ds.csv file
// mesh: a PolygonalMesh struct
// return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh);

// Checks if the edges in mesh are degenerate (lenght = 0)
// mesh: a PolygonalMesh struct
// return a boolean value, true if the mesh does not contain degenerate edges, false otherwise
bool test_on_edge(const PolygonalMesh& mesh, double tol);

// Checks if the triangle in mesh are degenerate (area = 0)
// mesh: a PolygonalMesh struct
// return a boolean value, true if the mesh does not contain degenerate triangle, false otherwise
bool test_on_triangle(const PolygonalMesh& mesh, double tol,  double tolA);

// Checks if there is some isolated point in the mesh
// mesh: a PolygonalMesh struct
// return a boolean value, true if the mesh does not contain isolated point, false otherwise
bool find_isolated_vertice(const PolygonalMesh& mesh);
}
