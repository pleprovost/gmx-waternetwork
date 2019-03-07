
#include "Cgal.hpp"
#include "AnalysisNeighbors.hpp"


void AnalysisNeighbor::initialize(Config config)
{
    
}

void AnalysisNeighbor::execute(const Frame &frame)
{

    /*
     *Converstion of positions set to cgal point vectors
     */
    std::vector<cgal::Point_3> points = fromGmxtoCgalPosition<cgal::Point_3>(frame.points.coordinates());
    std::vector<cgal::Point_3> proteins = fromGmxtoCgalPosition<cgal::Point_3>(frame.proteins.coordinates());
    std::vector<cgal::Point_3> waters = fromGmxtoCgalPosition<cgal::Point_3>(frame.waters.coordinates());
    std::vector<cgal::Point_3> oxygens = fromGmxtoCgalPosition<cgal::Point_3>(frame.waters.coordinates(), 3);

    cgal::Alpha_shape_3 alphaShape(points.begin(), points.end());
    alphaShape.set_alpha(1.0);
    std::vector<int> selected = cgal::searchPoints(alphaShape, oxygens);

    cgal::DelaunayWithInfo DTI;
    for (auto id : selected)
    {
    	cgal::DelaunayWithInfo::Vertex_handle vertex =  DTI.insert(oxygens.at(id));
    	vertex->info() = cgal::Node{3*id, waters.at(3*id+1), waters.at(3*id+2)}; 	
    }
    
    std::vector<edge> edges = cgal::analyseEdges(DTI);
    std::cout << "Vertex : " << DTI.number_of_vertices()
	      << ", Edges : " << edges.size() << std::endl;
}