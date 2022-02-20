#pragma once

#include <GL/glew.h>
#include <glimac/common.hpp>
#include <us/VertexArray.hpp>
#include <us/Material.hpp>

#include <memory>

struct Mesh
{
	VertexArrayPtr array;
	MaterialPtr material;

	Mesh() = delete;
	Mesh(const Mesh& pOther);
	Mesh& operator=(const Mesh& pOther);
	Mesh(VertexArrayPtr array, MaterialPtr pMaterial);
};
using MeshPtr = std::shared_ptr<Mesh>;