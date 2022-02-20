#include <us/Mesh.hpp>


Mesh::Mesh(const Mesh& pOther):
	array(pOther.array),
	material(std::make_shared<Material>(*pOther.material)) // DEEP COPY
{}

Mesh& Mesh::operator=(const Mesh& pOther)
{
	array = pOther.array;
	material = std::make_shared<Material>(*pOther.material);

	return *this;
}

Mesh::Mesh(VertexArrayPtr pArray, MaterialPtr pMaterial):
	array(pArray),
	material(pMaterial)
{}