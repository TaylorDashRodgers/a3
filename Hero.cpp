#include "Hero.h"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

Hero::Hero(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {
    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;

    _transWholeBody = glm::vec3( 0.0f, 2.2f, 0.0f);
    _scaleWholeBody = glm::vec3( 10.0f, 10.0f, 10.0f);
    _bodyAngle = 0.0f;
    _bodyAngleRotationFactor = _PI / 32;

    _colorHead = glm::vec3( 0.0f,0.5451f,0.5451f );
    _scaleHead = glm::vec3( 0.1f, 0.1f, 0.1f );
    _transHead = glm::vec3( 0.0f, 0.13f, 0.0f );

    _colorLeftEye = glm::vec3( 1.0f,1.0f,1.0f );
    _scaleLeftEye = glm::vec3( 0.1f, 0.1f, 0.1f );
    _transLeftEye = glm::vec3( 0.06f, 0.15f, 0.03f );

    _colorRightEye = glm::vec3( 1.0f,1.0f,1.0f );
    _scaleRightEye = glm::vec3( 0.1f, 0.1f, 0.1f );
    _transRightEye = glm::vec3( 0.06f, 0.15f, -0.03f );

    _colorBody = glm::vec3( 0.0f,0.5451f,0.5451f );
    _scaleBody = glm::vec3( 1.0f, 2.5f, 1.0f );
    _transBody = glm::vec3( 0.0f, -0.04f, 0.0f );

    _colorLegs = glm::vec3( 0.2f,0.2f,0.2f );
    _scaleLegs = glm::vec3( 1.1f, 2.0f, 1.1f );
    _transLegs = glm::vec3( 0.0f, -0.12f, 0.0f );

    _colorArm = glm::vec3( 0.8f, 0.8f, 0.8f );
    _scaleArm = glm::vec3(0.5f, 1.0f, 1.0f );
}

void Hero::drawHero(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transWholeBody );
    modelMtx1 = glm::rotate( modelMtx1, _bodyAngle, CSCI441::Y_AXIS );
    modelMtx1 = glm::scale( modelMtx1, _scaleWholeBody );
    _drawHeroBody(modelMtx1, viewMtx, projMtx);
    _drawHeroArm(modelMtx1, viewMtx, projMtx);
    _drawHeroLegs(modelMtx1, viewMtx, projMtx);
    _drawHeroHead(modelMtx1, viewMtx, projMtx);
    _drawHeroLeftEye(modelMtx1, viewMtx, projMtx);
    _drawHeroRightEye(modelMtx1, viewMtx, projMtx);
}

void Hero::turnRight() {
    _bodyAngle -= _bodyAngleRotationFactor;
}

void Hero::turnLeft() {
    _bodyAngle += _bodyAngleRotationFactor;
}

void Hero::_drawHeroHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transHead );
    modelMtx1 = glm::scale( modelMtx1, _scaleHead );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorHead[0]);

    CSCI441::drawSolidSphere( 0.8f, 10, 10);
}

void Hero::_drawHeroLeftEye(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transLeftEye );
    modelMtx1 = glm::scale( modelMtx1, _scaleLeftEye );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorLeftEye[0]);

    CSCI441::drawSolidSphere( 0.2f, 10, 10);
}

void Hero::_drawHeroRightEye(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transRightEye );
    modelMtx1 = glm::scale( modelMtx1, _scaleRightEye );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorRightEye[0]);

    CSCI441::drawSolidSphere( 0.2f, 10, 10);
}

void Hero::_drawHeroBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transBody );
    modelMtx1 = glm::scale( modelMtx1, _scaleBody );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorBody[0]);

    CSCI441::drawSolidCube( 0.1f );
}

void Hero::_drawHeroLegs(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transLegs );
    modelMtx1 = glm::scale( modelMtx1, _scaleLegs );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorLegs[0]);

    CSCI441::drawSolidCube( 0.1f );
}

void Hero::_drawHeroArm(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::scale(modelMtx, _scaleArm );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorArm[0]);

    CSCI441::drawSolidCube( 0.17f );
}

void Hero::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}
