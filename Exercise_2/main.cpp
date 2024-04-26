#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;
int main()
{
   PolygonalMesh mesh;
   string filepath = "PolygonalMesh";
   if(!ImportMesh(filepath,mesh))
       {
           cerr << "error";
           return 1;
       }
   double tolEdge= 100 * numeric_limits<double>::epsilon();

   /// first test: degenerate edge
   if(test_on_edge(mesh, tolEdge))
       {
       cout << "there are no degenerate edges " << endl;
       }
   else
       {
       cerr << "there are some degenerate edges " << endl;
       }

   /// second test: degenerate edge
   double tolArea = std::pow(10, -9);
   if(test_on_triangle(mesh, tolEdge, tolArea))
       {
        cout << "there are no degenerate triangles" << endl;
       }
   else
       {
       cerr << "there are some degenerate triangles" << endl;
       }
   /// third test: isolated vertice
   if (find_isolated_vertice(mesh))
       {
           cout << "There are no isolated vertices" << endl;
       }
    else
       {
       cerr << "there are some isolated vertices" << endl;
       }
  return 0;
}
