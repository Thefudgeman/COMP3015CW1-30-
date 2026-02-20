#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
#include <sstream>
using std::cerr;
using std::endl;
#include "helper/glutils.h"

using glm::mat4;

using glm::vec3;
using glm::vec4;




SceneBasic_Uniform::SceneBasic_Uniform() : plane(30.0f,30.0f, 1, 1), teapot(14,glm::mat4(1.0f)), torus(1.75f*0.75f, 0.75f*0.75f, 50,50), angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>()/8.0f), sky(300.0f)
{
    mesh = ObjMesh::load("media/pig_triangulated.obj", true);
    barrel = ObjMesh::load("media/barrel.obj", true);
    ogre = ObjMesh::load("media/bs_ears.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();

    glEnable(GL_DEPTH_TEST);
    
    
    view = glm::lookAt(vec3(5.0f, 5.0f, 7.5f), vec3(0.0f, 0.75f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    float x, z;
    rotateModel = mat4(1.0f);
    rotateModel = glm::translate(rotateModel, vec3(0.0f, 0.26f, 0.0f));

    barrelModel = mat4(1.0f);
    barrelModel = glm::translate(barrelModel, vec3(-10.0f, 2.0f, 0.0f));
    barrelModel = glm::scale(barrelModel, vec3(0.1f));


    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "lights[" << i << "].Position";
        x = 2.0f * cosf(glm::two_pi<float>() / 3 * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.use();
        prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, -1.0f));
        mixShader.use();
        mixShader.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, -1.0f));
        normalShader.use();
        normalShader.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, -1.0f));
    }
    prog.use();
    prog.setUniform("Light.L", vec3(1.0f, 1.0f, 1.0f) /1.5f);
    prog.setUniform("lights[1].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);
    prog.setUniform("lights[2].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);

    prog.setUniform("Spot.L", vec3(0.9f));
    prog.setUniform("Spot.La", vec3(0.5f));
    prog.setUniform("Spot.Exponent", 10.0f);
    prog.setUniform("Spot.Cutoff", glm::radians(120.0f));

    prog.setUniform("Fog.MaxDist", 30.0f);
    prog.setUniform("Fog.MinDist", 1.0f);
    prog.setUniform("Fog.Colour", vec3(0.5f,0.5f,0.5f));

    mixShader.use();

    mixShader.setUniform("lights[0].L", vec3(1.0f, 1.0f, 1.0f) / 1.5f);
    mixShader.setUniform("lights[1].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);
    mixShader.setUniform("lights[2].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);

    mixShader.setUniform("Spot.L", vec3(0.9f));
    mixShader.setUniform("Spot.La", vec3(0.5f));
    mixShader.setUniform("Spot.Exponent", 10.0f);
    mixShader.setUniform("Spot.Cutoff", glm::radians(120.0f));

    mixShader.setUniform("Fog.MaxDist", 30.0f);
    mixShader.setUniform("Fog.MinDist", 1.0f);
    mixShader.setUniform("Fog.Colour", vec3(0.5f, 0.5f, 0.5f));

    normalShader.use();

    normalShader.setUniform("Light.L", vec3(1.0f));
    normalShader.setUniform("Light.La", vec3(0.05));
  //  normalShader.setUniform("lights[1].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);
    //normalShader.setUniform("lights[2].L", vec3(1.0f, 1.0f, 1.0f) / 2.0f);

    normalShader.setUniform("Spot.L", vec3(0.9f));
    normalShader.setUniform("Spot.La", vec3(0.5f));
    normalShader.setUniform("Spot.Exponent", 10.0f);
    normalShader.setUniform("Spot.Cutoff", glm::radians(120.0f));

    normalShader.setUniform("Fog.MaxDist", 30.0f);
    normalShader.setUniform("Fog.MinDist", 1.0f);
    normalShader.setUniform("Fog.Colour", vec3(0.5f, 0.5f, 0.5f));

    skyBoxShader.use();
    skyBoxShader.setUniform("Fog.MaxDist", 30.0f);
    skyBoxShader.setUniform("Fog.MinDist", 0.1f);
    skyBoxShader.setUniform("Fog.Colour", vec3(0.5f, 0.5f, 0.5f));

}

void SceneBasic_Uniform::compile()
{
    try {
        prog.compileShader("shader/basic_uniform.vert");
        prog.compileShader("shader/basic_uniform.frag");
        prog.link();
        prog.use();

        mixShader.compileShader("shader/texture_mixing.vert");
        mixShader.compileShader("shader/texture_mixing.frag");
        mixShader.link();
        mixShader.use();

        normalShader.compileShader("shader/normalShader.vert");
        normalShader.compileShader("shader/normalShader.frag");
        normalShader.link();
        normalShader.use();

        skyBoxShader.compileShader("shader/skybox.vert");
        skyBoxShader.compileShader("shader/skybox.frag");
        skyBoxShader.link();
        skyBoxShader.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void SceneBasic_Uniform::update(float t)
{
    //update your angle here

    float deltaT = t - tPrev;
    if (tPrev == 0.0f)
    {
        deltaT = 0.0f;
    }

    tPrev = t;
    angle += rotSpeed * deltaT;
    if (angle > glm::two_pi<float>())
    {
        angle -= glm::two_pi<float>();
    }

    rotateModel = glm::rotate(rotateModel, glm::radians(-1.0f), vec3(1.0f,0.0f,0.0f));
    barrelModel = glm::rotate(barrelModel, glm::radians(-0.3f), vec3(0.0f, 1.0f, 0.0f));

}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //vec4 lightPosT = vec4(10.0f*cos(angle), 10.0f, 10.0f*cos(angle), 1.0f);

    prog.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ogreDiffuse);

    prog.setUniform("Material.Kd", 0.1f, 0.8f, 0.1f);
    prog.setUniform("Material.Ks", vec3(0.0f));
    prog.setUniform("Material.Ka", vec3(0.1f));
    prog.setUniform("Material.Shinniness", 180.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));

    setMatrices();
    plane.render();

    vec4 lightPos = vec4(10.0f , 10.0f, 10.0f, 1.0f);
    prog.setUniform("Spot.Position", vec3(view * lightPos));

    glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));

    prog.setUniform("Material.Kd", 1.0f, 0.4f, 0.72f);
    prog.setUniform("Material.Ks", vec3(1.0f));
    prog.setUniform("Material.Ka", vec3(0.5f));
    prog.setUniform("Material.Shinniness", 180.0f);
    prog.setUniform("Fog.MaxDist", 30.0f * fogScale);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cement);


  //  rotateModel = glm::rotate(rotateModel, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
 //   rotateModel += glm::translate(rotateModel, vec3(-0.9f, 0.0f, -0.9f));
    rotateModel = glm::translate(rotateModel, vec3(-0.0f, 0.26f, -0.0f));

    rotateModelMMM();
    mesh->render();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, flower);


    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));

    setMatrices();
    torus.render();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ogreDiffuse);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(-4.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(270.0f), vec3(1.0f, 0.0f, 0.0f));

    setMatrices();
    teapot.render();

    skyBoxShader.use();
    skyBoxShader.setUniform("Fog.MaxDist", 30.0f * fogScale);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);

    model = mat4(1.0f);
    setMatricesSkyBox();
    sky.render();


 //   normalShader.use();
 //   normalShader.setUniform("Spot.Position", vec3(view * lightPos));
 //   normalShader.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));

 //   normalShader.setUniform("Light.Position", vec4(1.0f,1.0f,1.0f,1.0f));

 //   normalShader.setUniform("Material.Kd", 1.0f, 0.4f, 0.72f);
 //   normalShader.setUniform("Material.Ks", vec3(1.0f));
 //   normalShader.setUniform("Material.Ka", vec3(0.5f));
 //   normalShader.setUniform("Material.Shinniness", 180.0f);

 //   glActiveTexture(GL_TEXTURE0);
 //   glBindTexture(GL_TEXTURE_2D, barrelTex);

 //   glActiveTexture(GL_TEXTURE1);
 //   glBindTexture(GL_TEXTURE_2D, barrelNorm);

 ////   barrelModel = mat4(1.0f);
 ////   barrelModel = glm::translate(barrelModel, vec3(-10.0f, 2.0f, 0.0f));
 //   model = mat4(1.0f);
 //   model = glm::translate(model, vec3(-10.0f, 2.0f, 0.0f));
 //   model = glm::scale(model, vec3(0.1f));

 //   setMatricesNorm();
 //   barrel->render();

 //   glActiveTexture(GL_TEXTURE0);
 //   glBindTexture(GL_TEXTURE_2D, ogreDiffuse);

 //   glActiveTexture(GL_TEXTURE1);
 //   glBindTexture(GL_TEXTURE_2D, ogreNorm);

 //   model = mat4(1.0f);
 //   model = glm::translate(model, vec3(-0.0f, 2.0f, 0.0f));
 //   model = glm::rotate(model, glm::radians(270.0f), vec3(1.0f, 0.0f, 0.0f));

 //   setMatricesNorm();
 //   ogre->render();

    mixShader.use();
    mixShader.setUniform("Spot.Position", vec3(view* lightPos));
    mixShader.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));

    mixShader.setUniform("Material.Kd", 1.0f, 0.4f, 0.72f);
    mixShader.setUniform("Material.Ks", vec3(0.5f));
    mixShader.setUniform("Material.Ka", vec3(0.5f));
    mixShader.setUniform("Material.Shinniness", 180.0f);
    mixShader.setUniform("Fog.MaxDist", 30.0f * fogScale);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, brick);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, moss);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(-4.0f, 4.0f, 0.0f));
    model = glm::rotate(model, glm::radians(270.0f), vec3(1.0f, 0.0f, 0.0f));

    setMatricesMix();
    cube.render();


}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view*model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::setMatricesMix()
{
    mat4 mv = view * model;
    mixShader.setUniform("ModelViewMatrix", mv);
    mixShader.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    mixShader.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::setMatricesNorm()
{
    mat4 mv = view * model;
    normalShader.setUniform("ModelViewMatrix", mv);
    normalShader.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    normalShader.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::rotateModelMMM()
{
    mat4 mv = view * rotateModel;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::rotateBarrelModelMMM()
{
    mat4 mv = view * barrelModel;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::setMatricesSkyBox()
{
    mat4 mv = view * model;
    skyBoxShader.setUniform("ModelViewMatrix", mv);
    skyBoxShader.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    skyBoxShader.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 300.0f);
}

