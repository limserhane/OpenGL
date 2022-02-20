#pragma once

#include <us/Mesh.hpp>
#include <glimac/Geometry.hpp>

#include <unordered_map>
#include <string>
#include <memory>

class Geometry
{
public:
    std::unordered_map<std::string, MeshPtr> meshes;

public:
    Geometry() = default;
    Geometry(const Geometry& pOpher);
    Geometry& operator=(const Geometry& pOther);

    Geometry(const glimac::Geometry& base);

    Mesh& get(std::string name);
};
using GeometryPtr = std::shared_ptr<Geometry>;

GeometryPtr loadGeometry(const char* filepath);
GeometryPtr copyGeometry(GeometryPtr geometry);