#include "Hero.h"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

Hero::Hero(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {
    _propAngle = 0.0f;
    _propAngleRotationSpeed = _PI / 16.0f;

    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;

    _rotatePlaneAngle = _PI / 2.0f;

    _scaleWholeBody = glm::vec3( 10.0f, 10.0f, 10.0f);

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

    _rotateWingAngle = _PI / 2.0f;

    _colorNose = glm::vec3( 0.0f,0.5451f,0.5451f );
    _rotateNoseAngle = _PI / 2.0f;

    _colorProp = glm::vec3( 1.0f, 1.0f, 1.0f );
    _scaleProp = glm::vec3( 1.1f, 1.0f, 0.025f );
    _transProp = glm::vec3( 0.1f, 0.0f, 0.0f );

    _colorTail = glm::vec3( 0.0f,0.5451f,0.5451f );
}

void Hero::drawPlane(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    modelMtx = glm::rotate( modelMtx, -_rotatePlaneAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate( modelMtx, _rotatePlaneAngle, CSCI441::Z_AXIS );
    _drawHeroBody(modelMtx, viewMtx, projMtx);
//    _drawHeroArm(true, modelMtx, viewMtx, projMtx); // the left arm
//    _drawHeroArm(false, modelMtx, viewMtx, projMtx); // the right arm
    _drawPlaneNose(modelMtx, viewMtx, projMtx);        // the nose
    _drawPlanePropeller(modelMtx, viewMtx, projMtx);   // the propeller
    _drawPlaneTail(modelMtx, viewMtx, projMtx);        // the tail
}

void Hero::drawHero(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    modelMtx = glm::rotate( modelMtx, -_rotatePlaneAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate( modelMtx, _rotatePlaneAngle, CSCI441::Z_AXIS );
    modelMtx = glm::scale( modelMtx, _scaleWholeBody );
    _drawHeroBody(modelMtx, viewMtx, projMtx);
    _drawHeroArm(modelMtx, viewMtx, projMtx);
    _drawHeroLegs(modelMtx, viewMtx, projMtx);
    _drawHeroHead(modelMtx, viewMtx, projMtx);
    _drawHeroLeftEye(modelMtx, viewMtx, projMtx);
    _drawHeroRightEye(modelMtx, viewMtx, projMtx);
}

void Hero::flyForward() {
    _propAngle += _propAngleRotationSpeed;
    if( _propAngle > _2PI ) _propAngle -= _2PI;
}

void Hero::flyBackward() {
    _propAngle -= _propAngleRotationSpeed;
    if( _propAngle < 0.0f ) _propAngle += _2PI;
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

void Hero::_drawPlaneNose(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::rotate( modelMtx, _rotateNoseAngle, CSCI441::Z_AXIS );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorNose[0]);

    CSCI441::drawSolidCone( 0.025f, 0.3f, 16, 16 );
}

void Hero::_drawPlanePropeller(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transProp );
    modelMtx1 = glm::rotate( modelMtx1, _propAngle, CSCI441::X_AXIS );
    modelMtx1 = glm::scale( modelMtx1, _scaleProp );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorProp[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::mat4 modelMtx2 = glm::translate( modelMtx, _transProp );
    modelMtx2 = glm::rotate( modelMtx2, _PI_OVER_2 + _propAngle, CSCI441::X_AXIS );
    modelMtx2 = glm::scale( modelMtx2, _scaleProp );

    _computeAndSendMatrixUniforms(modelMtx2, viewMtx, projMtx);

    CSCI441::drawSolidCube( 0.1f );
}

void Hero::_drawPlaneTail(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorTail[0]);

    CSCI441::drawSolidCone( 0.02f, 0.1f, 16, 16 );
}

void Hero::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}
