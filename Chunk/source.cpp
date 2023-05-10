#include <iostream>
#include <cmath>
#include "Chunk/chunk.h"

const double NEARBY (0.01);
struct Point3D
{
public:
	double x, y, z;

public:
	Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	double CalcLength() const {
		return sqrt(x * x + y * y + z * z);
	}

	double CalcLength(const Point3D& other) const {
		return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z));
	}

	double CalcScalarMult(const Point3D& other) const {
		/* In algebraic interpretation, the scalar multiplication of two vectors will be a scalar value equal
		to the sum of the products of their corresponding coordinates */
		return (x * other.x + y * other.y + z * other.z);
	}

	double CalcCosine(const Point3D& other) const {
		/* Calculation of the angle between vectors
		Basically, the cosine of the angle between vectors is equal
		to the scalar multiplication of the vectors, divided by the product of their lengths */

		return (this->CalcScalarMult(other)) / (this->CalcLength() * other.CalcLength());
	}

	// Angle is small, if is less than 2 degrees = 0,0349066 radians, deg × π/180 = rad
	bool CheckAngleIsSmall(const Point3D& other) {
		return (std::acos(this->CalcCosine(other)) < 0.0349066);
	}

	void operator = (Point3D& B) {
		this->x = B.x;
		this->y = B.y;
		this->z = B.z;
	}

	bool operator == (const Point3D& other) {
		return this->x == other.x && this->y == other.y && this->z == other.z;
	}
};

struct Triangle3D
{
public:
	Point3D vert1, vert2, vert3, normal;

public:
	Triangle3D()
		: vert1(0, 0, 0), vert2(0, 0, 0), vert3(0, 0, 0), normal(0, 0, 0) {}

	Triangle3D(Point3D _vert1, Point3D _vert2, Point3D _vert3, Point3D _normal)
		: vert1(_vert1), vert2(_vert2), vert3(_vert3), normal(_normal) {}

	void operator = (Triangle3D& B) {
		this->vert1 = B.vert1;
		this->vert2 = B.vert2;
		this->vert1 = B.vert3;
		this->normal = B.normal;
	}

	bool operator == (const Triangle3D& other) {
		return this->vert1 == other.vert1 && this->vert2 == other.vert2 && this->vert1 == other.vert3 && this->normal == other.normal;
	}

	bool CheckVerticesAreNearby(const Triangle3D& other) {
		return ((this->vert1.CalcLength(other.vert1) < NEARBY &&
			this->vert2.CalcLength(other.vert2) < NEARBY &&
			this->vert3.CalcLength(other.vert3) < NEARBY) ||
			(this->vert1.CalcLength(other.vert1) < NEARBY &&
				this->vert2.CalcLength(other.vert3) < NEARBY &&
				this->vert3.CalcLength(other.vert2) < NEARBY) ||
			(this->vert1.CalcLength(other.vert2) < NEARBY &&
				this->vert2.CalcLength(other.vert1) < NEARBY &&
				this->vert3.CalcLength(other.vert3) < NEARBY) ||
			(this->vert1.CalcLength(other.vert2) < NEARBY &&
				this->vert2.CalcLength(other.vert3) < NEARBY &&
				this->vert3.CalcLength(other.vert1) < NEARBY) ||
			(this->vert1.CalcLength(other.vert3) < NEARBY &&
				this->vert2.CalcLength(other.vert2) < NEARBY &&
				this->vert3.CalcLength(other.vert1) < NEARBY) ||
			(this->vert1.CalcLength(other.vert3) < NEARBY &&
				this->vert2.CalcLength(other.vert1) < NEARBY &&
				this->vert3.CalcLength(other.vert2) < NEARBY));
	}
};

class ChunkParser
{
private:
	chunk::Chunk chunk;

public:
	ChunkParser(const std::string& filename)
	{
		chunk.LoadFrom(filename.c_str());
	}

	void SplitString(const std::string& str, const char delim, std::vector<std::string>& out) {
		size_t start;
		size_t end = 0;

		while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = str.find(delim, start);
			out.push_back(str.substr(start, end - start));
		}
	}

	template <typename t>
	//std::vector<t> StrToVector(const std::string& str, const char delim) {
	//	std::vector <std::string> strVector;
	//	SplitString(str, delim, strVector);
	//
	//	std::vector<t> out;
	//	out.reserve(strVector.size());
	//	switch (t) {
	//	case double:
	//		for (auto s : str) {
	//			out.pushback(std::stod(s));
	//		}
	//		break;
	//	case int:
	//		for (auto s : str) {
	//			out.pushback(std::stoi(s));
	//		}
	//		break;
	//	default:
	//		throw std::exception("Unexpected datatype");
	//	}
	//}

	Triangle3D makeTriangle(const std::vector <double>& dblVertices, const std::vector <int>& intIndices, const std::vector <double>& dblNormals, size_t triangleNum) {
		double vertCoords[9];
		for (size_t i = 0; i < 9; i++)
		{
			size_t vertIndex = intIndices[triangleNum * 9 + i];
			vertCoords[i] = dblVertices[vertIndex];
		}
		double normalCoords[3];
		for (size_t i = 0; i < 3; i++)
		{
			size_t normalIndex = triangleNum * 9 + i;
			normalCoords[i] = dblNormals[normalIndex];
		}
		Point3D A(vertCoords[0], vertCoords[1], vertCoords[2]);
		Point3D B(vertCoords[3], vertCoords[4], vertCoords[5]);
		Point3D C(vertCoords[6], vertCoords[7], vertCoords[8]);
		Point3D normal(normalCoords[0], normalCoords[1], normalCoords[2]);
		return Triangle3D(A, B, C, normal);
	}

	std::vector<std::vector<Triangle3D>> GetTriangles()
	{
		int lodsNuber = chunk.GetTopNode()->GetNodeCount();
		std::vector<std::vector<Triangle3D>> triangles(lodsNuber);
		for (size_t lodNum = 0; lodNum < triangles.size(); lodNum++)
		{
			std::string verticesPath = "lod" + std::to_string(lodNum);
			verticesPath += "/meshGeometry/vertices";
			chunk::ChunkNode const* node_vertices = chunk.GetTopNode()->GetNodeByPath(verticesPath);
			std::vector <std::string> strVertices;
			SplitString(node_vertices->GetItem("values")->GetString(), ' ', strVertices);

			if ((strVertices.size() % 3) != 0)
				throw std::exception(std::string("The number of vertex coordinates in a lod ").append(std::to_string(lodNum)).append(" is not divisible by 3").c_str());

			std::string indicesPath = "lod" + std::to_string(lodNum);
			indicesPath += "/meshGeometry/indices";
			chunk::ChunkNode const* nodeIndices = chunk.GetTopNode()->GetNodeByPath(indicesPath);
			std::vector <std::string> strIndices;
			SplitString(nodeIndices->GetItem("values")->GetString(), ' ', strIndices);

			triangles[lodNum] = std::vector<Triangle3D>(strIndices.size() / 3);

			std::string normalsPath = "lod" + std::to_string(lodNum);
			normalsPath += "/meshGeometry/normals";
			chunk::ChunkNode const* nodeNormals = chunk.GetTopNode()->GetNodeByPath(normalsPath);
			std::vector <std::string> strNormals;
			SplitString(nodeNormals->GetItem("values")->GetString(), ' ', strNormals);

			for (size_t triangleNum = 0; triangleNum < triangles[lodNum].size(); triangleNum++) {
				float vertCoords[9];
				for (int i = 0; i < 3; i++)
				{
					int vertIndex = std::stoi(strIndices[triangleNum * 3 + i]);
					
					for (int j = 0; j < 3; j++)
					{
						vertCoords[i*3 + j] = std::stof(strVertices[vertIndex + j]);
					}
				}
				float normalCoords[3];
				for (int i = 0; i < 3; i++)
				{
					int normalIndex = triangleNum * 3 + i;
					normalCoords[i] = std::stof(strNormals[normalIndex]);
				}
				Point3D A(vertCoords[0], vertCoords[1], vertCoords[2]);
				Point3D B(vertCoords[3], vertCoords[4], vertCoords[5]);
				Point3D C(vertCoords[6], vertCoords[7], vertCoords[8]);
				Point3D normal(normalCoords[0], normalCoords[1], normalCoords[2]);
				Triangle3D triangle(A, B, C, normal);
				triangles[lodNum][triangleNum] = triangle;
			}

			//for (size_t triangleNum = 0; triangleNum < triangles[lodNum].size(); triangleNum++) {
			//	triangles[lodNum][triangleNum] = makeTriangle(dblVertices, intIndices, dblNormals, triangleNum);
			//}
		}

		return triangles;
	}


	//std::vector<std::vector<Triangle3D>> GetTriangles()
	//{
	//	size_t lodsNumber = chunk.GetTopNode()->GetNodeCount();
	//	std::vector<std::vector<Triangle3D>> triangles(lodsNumber);
	//	for (size_t lodNum = 0; lodNum < triangles.size(); lodNum++)
	//	{
	//		std::string verticesPath = "lod" + lodNum;
	//		verticesPath += "/meshGeometry/vertices";
	//		chunk::ChunkNode const* nodeVertices = chunk.GetTopNode()->GetNodeByPath(verticesPath);
	//		//std::vector <std::string> strVertices;
	//		std::vector <double> dblVertices;
	//		StrToVector(nodeVertices->GetItem("values")->GetString(), ' ', dblVertices);
	//		//SplitString(node_vertices->GetItem("values")->GetString(), ' ', strVertices);
	//
	//		if ((dblVertices.size() % 3) != 0)
	//			throw std::exception(std::string("The number of vertex coordinates in a lod ").append(std::to_string(lodNum)).append(" is not divisible by 3").c_str());
	//
	//		triangles[lodNum] = std::vector<Triangle3D>(dblVertices.size() / 3);
	//
	//		std::string indicesPath = "lod" + lodNum;
	//		indicesPath += "/meshGeometry/indices";
	//		chunk::ChunkNode const* nodeIndices = chunk.GetTopNode()->GetNodeByPath(indicesPath);
	//		//std::vector <std::string> strIndices;
	//		std::vector <int> intIndices;
	//		StrToVector(nodeIndices->GetItem("values")->GetString(), ' ', intIndices);
	//		//SplitString(nodeIndices->GetItem("values")->GetString(), ' ', strIndices);
	//
	//		std::string normalsPath = "lod" + lodNum;
	//		normalsPath += "/meshGeometry/normals";
	//		chunk::ChunkNode const* nodeNormals = chunk.GetTopNode()->GetNodeByPath(normalsPath);
	//		//std::vector <std::string> strNormals;
	//		std::vector <double> dblNormals;
	//		StrToVector(nodeNormals->GetItem("values")->GetString(), ' ', dblNormals);
	//		//SplitString(nodeNormals->GetItem("values")->GetString(), ' ', strNormals);
	//
	//		//for (size_t triangleNum = 0; triangleNum < triangles[lodNum].size(); triangleNum++) {
	//		//	double vertCoords[9];
	//		//	for (size_t i = 0; i < 9; i++)
	//		//	{
	//		//		size_t vertIndex = std::stoi(strIndices[triangleNum * 9 + i]);
	//		//		vertCoords[i] = std::stod(strVertices[vertIndex]);
	//		//	}
	//		//	double normalCoords[3];
	//		//	for (size_t i = 0; i < 3; i++)
	//		//	{
	//		//		size_t normalIndex = triangleNum * 9 + i;
	//		//		normalCoords[i] = std::stod(strNormals[normalIndex]);
	//		//	}
	//		//	Point3D A(vertCoords[0], vertCoords[1], vertCoords[2]);
	//		//	Point3D B(vertCoords[3], vertCoords[4], vertCoords[5]);
	//		//	Point3D C(vertCoords[6], vertCoords[7], vertCoords[8]);
	//		//	Point3D normal(normalCoords[0], normalCoords[1], normalCoords[2]);
	//		//	Triangle3D triangle(A, B, C, normal);
	//		//	triangles[lodNum][triangleNum] = triangle;
	//		//}
	//		for (size_t triangleNum = 0; triangleNum < triangles[lodNum].size(); triangleNum++) {
	//			triangles[lodNum][triangleNum] = makeTriangle(dblVertices, intIndices, dblNormals, triangleNum);
	//		}
	//	}
	//
	//	return triangles;
	//}
};

class Optimizer {
public:
	static void OptimizeTriangles(std::vector<Triangle3D>& triangles) {

		// Delete the vertex indices and the normal vectors of triangles with collinear normal vectors by DeleteCollinearNormals
		DeleteCollinearNormals(triangles);

		// Delete vertices and update indices for nearby vertices by DeleteNearbyVertices
		//DeleteNearbyVertices(triangles);

		// Delete vertex indices for degenerate triangles by DeleteDegenerateTriangles
		DeleteDegenerateTriangles(triangles);
	}

private:
	//static void DeleteNearbyVertices(std::vector<Triangle3D>& triangles) {
	//	for (size_t cur_triangle = 0; cur_triangle < triangles.size(); cur_triangle++) {
	//		for (size_t comparing_triangle = cur_triangle + 1; comparing_triangle < triangles.size(); comparing_triangle++)
	//		{
	//			if (triangles[cur_triangle].CheckVerticesAreNearby(triangles[comparing_triangle])) {
	//				triangles.erase(std::next(triangles.begin(), comparing_triangle));
	//			}
	//		}
	//	}
	//}
	....
	static void DeleteCollinearNormals(std::vector<Triangle3D>& triangles) {
		for (size_t cur_triangle = 0; cur_triangle < triangles.size(); cur_triangle++) {
			for (size_t comparing_triangle = cur_triangle + 1; comparing_triangle < triangles.size(); comparing_triangle++)
			{
				// Delete triangles w/ collinear normals & nearby vertices 
				if ((triangles[cur_triangle].normal.CheckAngleIsSmall(triangles[comparing_triangle].normal)) &&
					(triangles[cur_triangle].CheckVerticesAreNearby(triangles[comparing_triangle]))) {
					triangles.erase(std::next(triangles.begin(), comparing_triangle));
				}
			}
		}
	}

	static void DeleteDegenerateTriangles(std::vector<Triangle3D>& triangles) {
		for (size_t cur_triangle = 0; cur_triangle < triangles.size(); cur_triangle++) {

			Point3D AB(triangles[cur_triangle].vert2.x - triangles[cur_triangle].vert1.x,
				triangles[cur_triangle].vert2.y - triangles[cur_triangle].vert1.y,
				triangles[cur_triangle].vert2.z - triangles[cur_triangle].vert1.z);
			Point3D BC(triangles[cur_triangle].vert3.x - triangles[cur_triangle].vert2.x,
				triangles[cur_triangle].vert3.y - triangles[cur_triangle].vert2.y,
				triangles[cur_triangle].vert3.z - triangles[cur_triangle].vert2.z);
			Point3D AC(triangles[cur_triangle].vert3.x - triangles[cur_triangle].vert1.x,
				triangles[cur_triangle].vert3.y - triangles[cur_triangle].vert1.y,
				triangles[cur_triangle].vert3.z - triangles[cur_triangle].vert1.z);
			double a = AB.CheckAngleIsSmall(BC), b = AB.CheckAngleIsSmall(AC), c = BC.CheckAngleIsSmall(AC);
			if (a == 1 || b == 1 || c == 1) {
				triangles.erase(std::next(triangles.begin(), cur_triangle));
			}
		}
	}

	static void CreateNewMeshGeometry(std::vector<Triangle3D>& triangles, std::vector <double>& dblVertices, std::vector <int>& intIndices, std::vector <double>& dblNormals) {		// DeleteDuplicateCoords
		
		// Initialization of the index array items with value that the real ID cannot store. This value is a flag for vertex IDs are not yet defined.
		for each (auto i in intIndices)
			i = triangles.size() * 3 + 1;

		for (size_t i = 0; i < triangles.size(); i++)
		{
			// If the ID of trio of coordinates for one of the vertices of the current triangle is NOT defined, then the necessary trio of coordinates should be added to the coordinate vector and the ID of the triple of coordinates  should be added to the index array
			if (intIndices[i] == triangles.size() * 3 + 1 && intIndices[i + 1] == triangles.size() * 3 + 1 && intIndices[i + 2] == triangles.size() * 3 + 1) {
				dblVertices.push_back(triangles[i].vert1.x);
				dblVertices.push_back(triangles[i].vert1.y);
				dblVertices.push_back(triangles[i].vert1.z);
				dblVertices.push_back(triangles[i].vert2.x);
				dblVertices.push_back(triangles[i].vert2.y);
				dblVertices.push_back(triangles[i].vert2.z);
				dblVertices.push_back(triangles[i].vert3.x);
				dblVertices.push_back(triangles[i].vert3.y);
				dblVertices.push_back(triangles[i].vert3.z);
				// The last trio of coordinates is the 3rd vertex coordinates for the current triangle, so ID of trio of the 3rd vertex coordinates is size / 3
				// Trio of coordinates of the 2nd vertex has previous ID, so ID of trio of the 2nd vertex coordinates is size / 3 - 1
				// Trio of coordinates of the 1st vertex has pre-previous ID, so ID of trio of the 1st vertex coordinates is size / 3 - 2
				// First, the ID of trio of the 1st vertex coordinates is added to the index array, then ID of trio of the 2nd & 3rd vertices coordinates
				intIndices[i * 3] = (dblVertices.size() / 3 - 2);
				intIndices[i * 3 + 1] = (dblVertices.size() / 3 - 1);
				intIndices[i * 3 + 2] = (dblVertices.size() / 3);
			}
			if (intIndices[i] == triangles.size() * 3 + 1) {
				dblVertices.push_back(triangles[i].vert1.x);
				dblVertices.push_back(triangles[i].vert1.y);
				dblVertices.push_back(triangles[i].vert1.z);
				intIndices[i * 3] = (dblVertices.size() / 3);
			}
			if (intIndices[i + 1] == triangles.size() * 3 + 1) {
				dblVertices.push_back(triangles[i].vert2.x);
				dblVertices.push_back(triangles[i].vert2.y);
				dblVertices.push_back(triangles[i].vert2.z);
				intIndices[i * 3 + 1] = (dblVertices.size() / 3);
			}
			if (intIndices[i + 2] == triangles.size() * 3 + 1) {
				dblVertices.push_back(triangles[i].vert3.x);
				dblVertices.push_back(triangles[i].vert3.y);
				dblVertices.push_back(triangles[i].vert3.z);
				intIndices[i * 3 + 2] = (dblVertices.size() / 3);
			}
			for (size_t j = 0; j < triangles.size(); j++) {
				// Nearby vertices of different triangles of the same lod must have the same ID in the index array
				if (triangles[j].vert1.CalcLength(triangles[i].vert1) < NEARBY) {
					intIndices[j * 3] = (dblVertices.size() / 3 - 2);
				}
				if (triangles[j].vert1.CalcLength(triangles[i].vert2) < NEARBY) {
					intIndices[j * 3 + 1] = (dblVertices.size() / 3 - 2);
				}
				if (triangles[j].vert1.CalcLength(triangles[i].vert3) < NEARBY) {
					intIndices[j * 3 + 2] = (dblVertices.size() / 3 - 2);
				}
				if (triangles[j].vert2.CalcLength(triangles[i].vert1) < NEARBY) {
					intIndices[j * 3] = (dblVertices.size() / 3 - 1);
				}
				if (triangles[j].vert2.CalcLength(triangles[i].vert2) < NEARBY) {
					intIndices[j * 3 + 1] = (dblVertices.size() / 3 - 1);
				}
				if (triangles[j].vert2.CalcLength(triangles[i].vert3) < NEARBY) {
					intIndices[j * 3 + 2] = (dblVertices.size() / 3 - 1);
				}
				if (triangles[j].vert3.CalcLength(triangles[i].vert1) < NEARBY) {
					intIndices[j * 3] = (dblVertices.size() / 3);
				}
				if (triangles[j].vert3.CalcLength(triangles[i].vert2) < NEARBY) {
					intIndices[j * 3 + 1] = (dblVertices.size() / 3);
				}
				if (triangles[j].vert3.CalcLength(triangles[i].vert3) < NEARBY) {
					intIndices[j * 3 + 2] = (dblVertices.size() / 3);
				}
			}
		}
	}
};

int main() {
	chunk::Chunk chunk;
	std::string test = "3710.385742 -976.1992188";
	std::vector <std::string> v;
	ChunkParser c("terrain_land_mesh_0_0.ivf_mesh");
	c.SplitString(test, ' ', v);
	

	std::string filename = "terrain_land_mesh_0_0.ivf_mesh";
	//chunk.LoadFrom(filename.c_str());
	//int count = chunk.GetTopNode()->GetNodeCount();
	std::vector<std::vector<Triangle3D>> triangles = c.GetTriangles();
	for (std::vector<Triangle3D>& t : triangles)
	{
		Optimizer::OptimizeTriangles(t);
	}
	//std::vector<Triangle3D> triangles;
	//triangles.push_back(Triangle3D(Point3D(1, 1, 1), Point3D(0, 0, -1), Point3D(-2, -2, -5), Point3D(1, 1, 1)));
	////triangles.push_back(Triangle3D(Point3D(1, 1, 1), Point3D(1, 1, 1), Point3D(1, 1, 0.5), Point3D(2, 2, 2)));
	//{
	//}

}