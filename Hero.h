#ifndef LAB05_PLANE_H
#define LAB05_PLANE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class Hero {
public:
    /// \desc creates a simple plane that gives the appearance of flight
    /// \param shaderProgramHandle shader program handle that the plane should be drawn using
    /// \param mvpMtxUniformLocation uniform location for the full precomputed MVP matrix
    /// \param normalMtxUniformLocation uniform location for the precomputed Normal matrix
    /// \param materialColorUniformLocation uniform location for the material diffuse color
    Hero(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation );

    /// \desc draws the model plane for a given MVP matrix
    /// \param modelMtx existing model matrix to apply to plane
    /// \param viewMtx camera view matrix to apply to plane
    /// \param projMtx camera projection matrix to apply to plane
    /// \note internally uses the provided shader program and sets the necessary uniforms
    /// for the MVP and Normal Matrices as well as the material diffuse color
    void drawHero( glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx );

    GLfloat getBodyAngle() const { return _bodyAngle; }

    void turnRight();
    void turnLeft();

private:
    /// \desc handle of the shader program to use when drawing the plane
    GLuint _shaderProgramHandle;
    /// \desc stores the uniform locations needed for the plan information
    struct ShaderProgramUniformLocations {
        /// \desc location of the precomputed ModelViewProjection matrix
        GLint mvpMtx;
        /// \desc location of the precomputed Normal matrix
        GLint normalMtx;
        /// \desc location of the material diffuse color
        GLint materialColor;
    } _shaderProgramUniformLocations;

    glm::vec3 _transWholeBody;
    glm::vec3 _scaleWholeBody;
    GLfloat _bodyAngle;
    GLfloat _bodyAngleRotationFactor;

    glm::vec3 _colorHead;
    glm::vec3 _scaleHead;
    glm::vec3 _transHead;

    glm::vec3 _colorLeftEye;
    glm::vec3 _scaleLeftEye;
    glm::vec3 _transLeftEye;

    glm::vec3 _colorRightEye;
    glm::vec3 _scaleRightEye;
    glm::vec3 _transRightEye;

    glm::vec3 _colorLegs;
    glm::vec3 _scaleLegs;
    glm::vec3 _transLegs;

    /// \desc color the hero's body
    glm::vec3 _colorBody;
    /// \desc amount to scale the hero's body by
    glm::vec3 _scaleBody;
    glm::vec3 _transBody;

    /// \desc color the hero's arm
    glm::vec3 _colorArm;
    /// \desc amount to scale the hero's by
    glm::vec3 _scaleArm;

    const GLfloat _PI = glm::pi<float>();

    void _drawHeroHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _drawHeroLeftEye(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _drawHeroRightEye(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _drawHeroBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _drawHeroLegs(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _drawHeroArm(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;

    /// \desc precomputes the matrix uniforms CPU-side and then sends them
    /// to the GPU to be used in the shader for each vertex.  It is more efficient
    /// to calculate these once and then use the resultant product in the shader.
    /// \param modelMtx model transformation matrix
    /// \param viewMtx camera view matrix
    /// \param projMtx camera projection matrix
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //LAB05_PLANE_H
