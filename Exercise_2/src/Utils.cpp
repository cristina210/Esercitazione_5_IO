#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
namespace PolygonalLibrary { //
bool ImportMesh(const string& filepath, PolygonalMesh& mesh){
    // call ImportCell0Ds
    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
    // check if markers from Cell0D have been stored correctly (comparing with "Cells0D.png")
        cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << (*it).first << "\t values:";
            for(const unsigned int id : (*it).second)
                cout << "\t" << id;
            cout << endl;
        }
    }
    // call ImportCell1Ds
    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
    // check if markers from Cell1D have been stored correctly (comparing with "Cells1D.png")
        cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << (*it).first << "\t values:";
            for(const unsigned int id : (*it).second)
                cout << "\t" << id;
            cout << endl;
        }
    }

    // call ImportCell2Ds
     if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",mesh))
     {
        return false;
     }
    else{
         // eventuale Test
     }

    return true;
}
/*-----------------------------------------------------------------------------------------------------------------------------*/
// definition of ImportCell0Ds
bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);
    if(file.fail())
        return false;
    list<string> listLines;
    string line;
    //  count the row in the file
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    // read and save information from Cell0D file
    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        char delimiter;
        Vector2d coord;

        converter >> id >> delimiter >> marker >> delimiter  >> coord(0) >> delimiter >> coord(1);

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)
        {
            auto ret = mesh.Cell0DMarkers.insert({marker, {id}});
            if(!ret.second)
            {
                (ret.first)->second.push_back(id);
            }
        }
    }
    file.close();
    return true;
}

// definition of ImportCell1Ds
bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh){
    ifstream file;
    file.open(filename);
    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;
        char delimiter;
        converter >>  id >> delimiter >> marker >> delimiter >> vertices(0) >> delimiter >> vertices(1);

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);


        if( marker != 0)
        {
            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
            {
                (ret.first)->second.push_back(id);
            }
        }
    }
    file.close();

    return true;
}

// definition of ImportCell2Ds
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh)
{   ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for (const string& line : listLines)
    {
        // Id;Marker;NumVertices;Vertices;NumEdges;Edges
        // 0;0;3;16;1;9;3;8;9;10
        istringstream converter(line);

        char delimiter;
        unsigned int id;
        unsigned int marker;
        unsigned int NumVertices;
        unsigned int vertice;
        unsigned int edge;
        vector<unsigned int> Vect_Vert;
        unsigned int NumEdges;
        vector<unsigned int> Vect_edg;

        converter >> id >> delimiter >> marker >> delimiter >> NumVertices;
        Vect_Vert.reserve(NumVertices);
        for(unsigned int i = 0; i < NumVertices; i++)
        {
            converter >> delimiter  >> vertice ;
            Vect_Vert.push_back(vertice);
        }
        converter >> NumEdges;
        for(unsigned int i = 0; i < NumEdges; i++)
        {
            converter >> delimiter >> edge ;
            Vect_edg.push_back(NumEdges);
        }
        mesh.Cell2DId.push_back(id);
        mesh.NumberVertices.push_back(NumVertices);
        mesh.Cell2DVertices.push_back(Vect_Vert);
        mesh.NumberEdges.push_back(NumEdges);
        mesh.Cell2DEdges.push_back(Vect_edg);
        Vect_Vert.clear();
        Vect_edg.clear();
        if( marker != 0)
        {
            auto ret = mesh.Cell2DMarkers.insert({marker, {id}});
            if(!ret.second){
                (ret.first)->second.push_back(id);
            }
        }
    }
    file.close();
    return true;
}

// definition of test 1:
bool test_on_edge(const PolygonalMesh& mesh, double tol)
{
    for (size_t i = 0; i < mesh.Cell1DId.size(); ++i) //mesh.Cell1Did contains edges ID
    {
        //extract Id of vertices at the ends of the edge
        int origin = mesh.Cell1DVertices[i][0];
        int end = mesh.Cell1DVertices[i][1];

        //trace back to the coordinates
        double X_Origin = mesh.Cell0DCoordinates[origin][0];
        double Y_Origin = mesh.Cell0DCoordinates[origin][1];
        double X_End = mesh.Cell0DCoordinates[end][0];
        double Y_End = mesh.Cell0DCoordinates[end][1];

        // test if the edge is degenerate using the tolerance and Euclidean distance
        double d = sqrt((X_Origin-X_End)*(X_Origin-X_End)+(Y_Origin-Y_End)*(Y_Origin-Y_End));
        if (d<tol)
        {
            return false;
        }
    }
    return true;
}

// definition of test 2:
bool test_on_triangle(const PolygonalMesh& mesh, double tol, double tolA)
{
    // find triangle
    unsigned int i = 0;
    for (auto it = mesh.NumberEdges.begin(); it != mesh.NumberEdges.end(); ++it) //mesh.NumberEdges contains the number of edges for each polygon
    {
        if(*it==3)
        {
            // calculate the lenght of each edge in order to use Eron Formula to calculate triangle's area
            int vertice1 = mesh.Cell2DVertices[i][0];
            double X1 = mesh.Cell0DCoordinates[vertice1][0];
            double Y1 = mesh.Cell0DCoordinates[vertice1][1];

            int vertice2 = mesh.Cell2DVertices[i][1];
            double X2 = mesh.Cell0DCoordinates[vertice2][0];
            double Y2 = mesh.Cell0DCoordinates[vertice2][1];

            int vertice3 = mesh.Cell2DVertices[i][2];
            double X3 = mesh.Cell0DCoordinates[vertice3][0];
            double Y3 = mesh.Cell0DCoordinates[vertice3][1];

            double len1_2 = sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
            double len2_3 = sqrt((X3-X2)*(X3-X2)+(Y3-Y2)*(Y3-Y2));
            double len1_3 = sqrt((X3-X1)*(X3-X1)+(Y3-Y1)*(Y3-Y1));

            double p = (len2_3+len1_2+len1_3)*0.5;
            double A = sqrt(p*(p-len1_2)*(p-len1_3)*(p-len2_3));  // Eron formula
            if (A<max(tol,tolA))
            {
                return false;
            }
        }
        i++;
    }
    return true;
}

// definition of test 3:
bool find_isolated_vertice(const PolygonalMesh& mesh)
{
    for (size_t i=0; i<mesh.Cell0DId.size(); i++) //mesh.Cello0Did contains vertices ID
    {
        bool found = false;
        unsigned int Id_Vertice = mesh.Cell0DId[i];
        for( unsigned int j=0; j<mesh.Cell2DVertices.size(); j++) //mesh.Cell2DVertices is a vector which contains vectors of vertices
        {
            vector<unsigned int> vec_vertices = mesh.Cell2DVertices[j];
            auto findVertice = find(vec_vertices.begin(), vec_vertices.end(), Id_Vertice);
            if(*findVertice == Id_Vertice)
            {
                found = true;
                break;
            }
        }
        if (found == false)
        {
            return false;
        }
    }
    return true;
}
}

