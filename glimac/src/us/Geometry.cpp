#include <us/Geometry.hpp>

#include <us/VertexArray.hpp>
#include <us/VertexBuffer.hpp>
#include <us/IndexBuffer.hpp>

#include <iostream>
#include <sstream>

Geometry::Geometry(const Geometry& pOther):
    meshes() // DEEP COPY
{
    for(auto& mesh : pOther.meshes)
    {
        meshes[mesh.first] = std::make_shared<Mesh>(*mesh.second);
    }
}

Geometry& Geometry::operator=(const Geometry& pOther)
{
    for(auto& mesh : pOther.meshes)
    {
        this->meshes[mesh.first] = std::make_shared<Mesh>(*mesh.second);
    }

    return *this;
}

Geometry::Geometry(const glimac::Geometry& base)
{
    VertexBufferPtr vertexBuffer = std::make_shared<VertexBuffer>(
        base.getVertexCount(), sizeof(glimac::ShapeVertex), (void*)base.getVertexBuffer()
    );

    for(const glimac::Geometry::Mesh& mesh : base.getMeshes())
    {
        MaterialPtr material = std::make_shared<Material>();
        if(mesh.m_nMaterialIndex != -1)
        {
            material->Kd = base.getMaterials()[mesh.m_nMaterialIndex].m_Kd;
            material->Ks = base.getMaterials()[mesh.m_nMaterialIndex].m_Ks;
            material->Shininess = base.getMaterials()[mesh.m_nMaterialIndex].m_Shininess;
        }

        IndexBufferPtr indexBuffer = std::make_shared<IndexBuffer>(
            mesh.m_nIndexCount, base.getIndexBuffer()+mesh.m_nIndexOffset
        );

        VertexArrayPtr vertexArray = std::make_shared<VertexArray>(vertexBuffer, indexBuffer);


        // std::cout << "name : " << mesh.m_sName << std::endl;
        
        meshes[mesh.m_sName] = std::make_shared<Mesh>(vertexArray, material);
    }
}

Mesh& Geometry::get(std::string name)
{
    auto mesh = meshes.find(name);
    if(mesh == meshes.end())
    {
        std::stringstream error;
        error << "Mesh " << name << " doesn't exist";
        std::cerr << error.str() << std::endl;
        throw new std::out_of_range(error.str());
    }

    return *mesh->second;
}

GeometryPtr loadGeometry(const char* filepath)
{
    glimac::Geometry base;
    if(!base.loadOBJ(filepath, glimac::FilePath(filepath).dirPath(), false))
    {
        std::stringstream error;
        error << "Could not load obj file at " << filepath;
        std::cerr << error.str() << std::endl;
        throw new std::invalid_argument(error.str());
    }
    
    return std::make_shared<Geometry>(base);
}

GeometryPtr copyGeometry(GeometryPtr geometry)
{
    return std::make_shared<Geometry>(*geometry);
}