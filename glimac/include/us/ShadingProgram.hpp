#pragma once

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <us/Actor.hpp>
#include <us/FreeflyCamera.hpp>
#include <us/Scene.hpp>

#include <memory>
#include <vector>

class ShadingProgram
{
public:
    ShadingProgram() = delete;
    ShadingProgram(const glimac::FilePath& applicationPath);

    void use() const { m_Program.use(); }

    void render(const Scene& scene) const;

private:

    void sendMaterial(const Material& material) const;
    void sendDirectionalLights(const DirectionalLightsManager& directionalLights, const FreeflyCamera& camera) const;
    void sendPointLights(const PointLightsManager& pointLights, const FreeflyCamera& camera) const;
    void draw(const FreeflyCamera& camera, const Actor& actor) const;

    void setMVMatrix(glm::mat4 mvMatrix) const;
    void setMVPMatrix(glm::mat4 mvpMatrix) const;
    void setNormalMatrix(glm::mat4 normalMatrix) const;
    void setKd(glm::vec3 kd) const;
    void setKs(glm::vec3 ks) const;
    void setShininess(float shininess) const;

    void setTexture(unsigned slot) const;
    void setHasTexture(bool hasTexture) const;

    void setNormalMap(unsigned slot) const;
    void setHasNormalMap(bool hasNormalMap) const;

    void setDirectionalLightsDirections(int count, const std::vector<glm::vec3>& pDirections) const;
    void setDirectionalLightsIntensities(int count, const std::vector<glm::vec3>& pIntensities) const;
    void setDirectionalLightCount(int count) const;

    void setPointLightsPositions(int count, const std::vector<glm::vec3>& pPositions) const;
    void setPointLightsIntensities(int count, const std::vector<glm::vec3>& pIntensities) const;
    void setPointLightsAttenuations(int count, const std::vector<float>& pAttenuations) const;
    void setPointLightCount(int count) const;

private:
    glimac::Program m_Program;

	GLuint mvUniform;
	GLuint mvpUniform;
	GLuint normalUniform;
	GLuint kdUniform;
	GLuint ksUniform;
	GLuint shininessUniform;

    GLuint textureUniform;
    GLuint hasTextureUniform;

    GLuint normalMapUniform;
    GLuint hasNormalMapUniform;

	GLuint directionalLightsDirectionsUniform;
	GLuint directionalLightsIntensitiesUniform;
	GLuint directionalLightCountUniform;

	GLuint pointLightsPositionsUniform;
	GLuint pointLightsIntensitiesUniform;
	GLuint pointLightsAttenuationsUniform;
	GLuint pointLightCountUniform;
};
using ShadingProgramPtr = std::shared_ptr<ShadingProgram>;