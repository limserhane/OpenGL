#include <us/ShadingProgram.hpp>

#include <GL/glew.h>

using namespace glm;

ShadingProgram::ShadingProgram(const glimac::FilePath& applicationPath):
    m_Program(glimac::loadProgram(
        applicationPath.dirPath() + "shaders/shading.vs.glsl",
        applicationPath.dirPath() + "shaders/shading.fs.glsl"
    ))
{
	mvUniform = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
	mvpUniform = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
	normalUniform = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
	kdUniform = glGetUniformLocation(m_Program.getGLId(), "uKd");
	ksUniform = glGetUniformLocation(m_Program.getGLId(), "uKs");
	shininessUniform = glGetUniformLocation(m_Program.getGLId(), "uShininess");

	textureUniform = glGetUniformLocation(m_Program.getGLId(), "uTexture");
	hasTextureUniform = glGetUniformLocation(m_Program.getGLId(), "uHasTexture");
	
	normalMapUniform = glGetUniformLocation(m_Program.getGLId(), "uNormalMap");
	hasNormalMapUniform = glGetUniformLocation(m_Program.getGLId(), "uHasNormalMap");

	directionalLightsDirectionsUniform = glGetUniformLocation(m_Program.getGLId(), "uDirectionalLightsDirections_vs");
	directionalLightsIntensitiesUniform = glGetUniformLocation(m_Program.getGLId(), "uDirectionalLightsIntensities");
	directionalLightCountUniform = glGetUniformLocation(m_Program.getGLId(), "uDirectionalLightCount");

	pointLightsPositionsUniform = glGetUniformLocation(m_Program.getGLId(), "uPointLightsPositions_vs");
	pointLightsIntensitiesUniform = glGetUniformLocation(m_Program.getGLId(), "uPointLightsIntensities");
	pointLightsAttenuationsUniform = glGetUniformLocation(m_Program.getGLId(), "uPointLightsAttenuations");
	pointLightCountUniform = glGetUniformLocation(m_Program.getGLId(), "uPointLightCount");
}

void ShadingProgram::setMVMatrix(glm::mat4 mvMatrix) const
{
	glUniformMatrix4fv(mvUniform, 1, false, glm::value_ptr(mvMatrix));
}

void ShadingProgram::setMVPMatrix(glm::mat4 mvpMatrix) const
{
	glUniformMatrix4fv(mvpUniform, 1, false, glm::value_ptr(mvpMatrix));
}

void ShadingProgram::setNormalMatrix(glm::mat4 normalMatrix) const
{
	glUniformMatrix4fv(normalUniform, 1, false, glm::value_ptr(normalMatrix));
}

void ShadingProgram::setKd(glm::vec3 kd) const
{
    glUniform3f(kdUniform, kd.r, kd.g, kd.b);
}
void ShadingProgram::setKs(glm::vec3 ks) const
{
    glUniform3f(ksUniform, ks.r, ks.g, ks.b);
}

void ShadingProgram::setShininess(float shininess) const
{
    glUniform1f(shininessUniform, shininess);
}

void ShadingProgram::setTexture(unsigned slot) const
{
	glUniform1i(textureUniform, slot);
}

void ShadingProgram::setHasTexture(bool hasTexture) const
{
	glUniform1i(hasTextureUniform, hasTexture);
}


void ShadingProgram::setNormalMap(unsigned slot) const
{
	glUniform1i(normalMapUniform, slot);
}

void ShadingProgram::setHasNormalMap(bool hasNormalMap) const
{
	glUniform1i(hasNormalMapUniform, hasNormalMap);
}

void ShadingProgram::setDirectionalLightsDirections(int count, const std::vector<glm::vec3>& pDirections) const
{
	glUniform3fv(directionalLightsDirectionsUniform, count, glm::value_ptr(*pDirections.data()));
}
void ShadingProgram::setDirectionalLightsIntensities(int count, const std::vector<glm::vec3>& pIntensities) const
{
	glUniform3fv(directionalLightsIntensitiesUniform, count, glm::value_ptr(*pIntensities.data()));
}
void ShadingProgram::setDirectionalLightCount(int count) const
{
	glUniform1i(directionalLightCountUniform, count);
}

void ShadingProgram::setPointLightsPositions(int count, const std::vector<glm::vec3>& pPositions) const
{
	glUniform3fv(pointLightsPositionsUniform, count, glm::value_ptr(*pPositions.data()));
}
void ShadingProgram::setPointLightsIntensities(int count, const std::vector<glm::vec3>& pIntensities) const
{
	glUniform3fv(pointLightsIntensitiesUniform, count, glm::value_ptr(*pIntensities.data()));
}
void ShadingProgram::setPointLightsAttenuations(int count, const std::vector<float>& pAttenuations) const
{
	glUniform1fv(pointLightsAttenuationsUniform, count, pAttenuations.data());
}
void ShadingProgram::setPointLightCount(int count) const
{
	glUniform1i(pointLightCountUniform, count);
}

void ShadingProgram::sendMaterial(const Material& material) const
{
    setKd(material.Kd);
    setKs(material.Ks);
    setShininess(material.Shininess);

    if(!material.NormalMap)
    {
        setHasNormalMap(false);
    }
    else
    {
        setHasNormalMap(true);
        material.NormalMap->bind(0);
        setNormalMap(0);
    }

    if(!material.Tex)
    {
        setHasTexture(false);
    }
    else
    {
        setHasTexture(true);
        material.Tex->bind(1);
        setTexture(1);
    }
}

void ShadingProgram::sendDirectionalLights(const DirectionalLightsManager& directionalLights, const FreeflyCamera& camera) const
{
    std::vector<vec3> directions_vs;
    directions_vs.reserve(directionalLights.getCount());// déplacer les allocations vector vers un buffer initialisé à la création dans le ctor

    for(vec3 direction_ws : directionalLights.directions) 
    {
        vec4 direction_vs = camera.getViewMatrix() * vec4(direction_ws, 0);
        directions_vs.push_back(vec3(direction_vs.x, direction_vs.y, direction_vs.z));
    }
    
    setDirectionalLightsDirections(directionalLights.getCount(), directions_vs);
    setDirectionalLightsIntensities(directionalLights.getCount(), directionalLights.intensities);
    setDirectionalLightCount(directionalLights.getCount());
}

void ShadingProgram::sendPointLights(const PointLightsManager& pointLights, const FreeflyCamera& camera) const
{
    std::vector<vec3> positions_vs;
    positions_vs.reserve(pointLights.getCount());// déplacer les allocations vector vers un buffer initialisé à la création dans le ctor

    for(vec3 position_ws : pointLights.positions) 
    {
        vec4 position_vs = camera.getViewMatrix() * vec4(position_ws, 1);
        positions_vs.push_back(vec3(position_vs.x, position_vs.y, position_vs.z));
    }
    
    setPointLightsPositions(pointLights.getCount(), positions_vs);
    setPointLightsIntensities(pointLights.getCount(), pointLights.intensities);
    setPointLightsAttenuations(pointLights.getCount(), pointLights.attenuations);
    setPointLightCount(pointLights.getCount());
}


void ShadingProgram::render(const Scene& scene) const
{
    use();

    if(!scene.camera) return;

    sendDirectionalLights(scene.directionalLights, *scene.camera);
    sendPointLights(scene.pointLights, *scene.camera);

    for(ActorPtr actor : scene.actors)
    {
        if(!actor) throw new std::runtime_error("Actor cannot be nullptr");

        draw(*scene.camera, *actor);
    }
}

void ShadingProgram::draw(const FreeflyCamera& camera, const Actor& actor) const
{
    setMVMatrix(camera.getViewMatrix() * actor.transform.getModelMatrix());
    setNormalMatrix(transpose(inverse(camera.getViewMatrix() * actor.transform.getModelMatrix())));
    setMVPMatrix(camera.getProjectionMatrix() * camera.getViewMatrix() * actor.transform.getModelMatrix());

	for(const auto& mesh : actor.geometry->meshes)
	{
		sendMaterial(*mesh.second->material);
		mesh.second->array->draw();
	}
}