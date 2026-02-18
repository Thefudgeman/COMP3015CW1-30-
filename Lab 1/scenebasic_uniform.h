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
#include <iostream>

using glm::vec3;

class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog, mixShader;
    glm::mat4 rotationMatrix;
    Torus torus;
    Teapot teapot;
    Plane plane;
    std::unique_ptr<ObjMesh> mesh;
    std::unique_ptr<ObjMesh> barrel;
    Cube cube;
    glm::mat4 rotateModel;
    glm::mat4 barrelModel;

    GLuint brick = Texture::loadTexture("media/texture/brick1.jpg");
    GLuint moss = Texture::loadTexture("media/texture/moss.png");
    GLuint ogreDiffuse = Texture::loadTexture("media/texture/ogre_diffuse.png");
    GLuint flower = Texture::loadTexture("media/texture/flower.png");
    GLuint fire = Texture::loadTexture("media/texture/fire.png");
    GLuint cement = Texture::loadTexture("media/texture/cement.jpg");
    GLuint barrelTex = Texture::loadTexture("media/texture/WoodenBarrel/Barrel_Lowpoly_DefaultMaterial_AlbedoTransparency.png");
    GLuint barrelNorm = Texture::loadTexture("media/texture/WoodenBarrel/Barrel_Lowpoly_DefaultMaterial_Normal.png");

    float tPrev = 0.0f;
    float angle =0.0f;

    //Transformations
//Relative position within world space
    glm::vec3 cameraPosition = vec3(0.0f, 0.0f, 3.0f);
    //The direction of travel
    vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
    //Up position within world space
    vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

    //Camera sidways rotation
    float cameraYaw = -90.0f;
    //Camera vertical rotation
    float cameraPitch = 0.0f;
    //Determines if first entry of mouse into window
    bool mouseFirstEntry = true;
    //Positions of camera from given last frame
    float cameraLastXPos = 800.0f / 2.0f;
    float cameraLastYPos = 600.0f / 2.0f;

    float deltaTime = 0.0f;
    //Last value of time change
    float lastFrame = 0.0f;

    void compile();

public:
    SceneBasic_Uniform();
    void rotateModelMMM();
    void setMatrices();
    void setMatricesMix();
    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
    void rotateBarrelModelMMM();
  //  void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif // SCENEBASIC_UNIFORM_H
