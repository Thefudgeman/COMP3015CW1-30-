#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/torus.h"
#include "helper/teapot.h"
#include "helper/cube.h"
#include "helper/texture.h"


class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    glm::mat4 rotationMatrix;
    Torus torus;
    Teapot teapot;
    Plane plane;
    std::unique_ptr<ObjMesh> mesh;
    std::unique_ptr<ObjMesh> barrel;
    Cube cube;
    glm::mat4 rotateModel;
    glm::mat4 barrelModel;

    GLuint texID = Texture::loadTexture("media/texture/ao_ears.png");
    GLuint texID1 = Texture::loadTexture("media/texture/ogre_diffuse.png");
    GLuint texID2 = Texture::loadTexture("media/texture/flower.png");
    GLuint texID3 = Texture::loadTexture("media/texture/fire.png");
    GLuint texID4 = Texture::loadTexture("media/texture/cement.jpg");
    GLuint barrelTex = Texture::loadTexture("media/texture/WoodenBarrel/Barrel_Lowpoly_DefaultMaterial_AlbedoTransparency.png");
    GLuint barrelNorm = Texture::loadTexture("media/texture/WoodenBarrel/Barrel_Lowpoly_DefaultMaterial_Normal.png");

    float tPrev = 0.0f;
    float angle =0.0f;
    void compile();

public:
    SceneBasic_Uniform();
    void rotateModelMMM();
    void setMatrices();
    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
    void rotateBarrelModelMMM();
};

#endif // SCENEBASIC_UNIFORM_H
