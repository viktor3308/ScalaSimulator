#include "RayCastEffect.h"

#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QParameter>
#include <QUrl>
#include <QColor>

RayCastEffect::RayCastEffect(Qt3DCore::QNode* parent):
    Qt3DRender::QEffect(parent),
    m_technique(new Qt3DRender::QTechnique()),
    m_rayCastPass(new Qt3DRender::QRenderPass()),
    m_renderPass(new Qt3DRender::QRenderPass()),
    m_rayCastCriterion(new Qt3DRender::QFilterKey(this)),
    m_renderCriterion(new Qt3DRender::QFilterKey(this)),

    m_ambientParameter(new Qt3DRender::QParameter(QStringLiteral("ka"), QColor::fromRgbF(0.05f, 0.05f, 0.05f, 1.0f))),
    m_diffuseParameter(new Qt3DRender::QParameter(QStringLiteral("kd"), QColor::fromRgbF(0.7f, 0.7f, 0.7f, 1.0f))),
    m_specularParameter(new Qt3DRender::QParameter(QStringLiteral("ks"), QColor::fromRgbF(0.01f, 0.01f, 0.01f, 1.0f))),
    m_shininessParameter(new Qt3DRender::QParameter(QStringLiteral("shininess"), 150.0f))
{
    m_technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    m_technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    m_technique->graphicsApiFilter()->setMajorVersion(3);
    m_technique->graphicsApiFilter()->setMinorVersion(4);

    m_rayCastCriterion->setName(QStringLiteral("pass"));
    m_rayCastCriterion->setValue(QStringLiteral("raycast"));

    m_rayCastPass->addFilterKey(m_rayCastCriterion);
    Qt3DRender::QShaderProgram* rayCastShader = new Qt3DRender::QShaderProgram();
    rayCastShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/RayCast.vert"))));
    rayCastShader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/RayCast.frag"))));
    rayCastShader->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/RayCast.geom"))));

    m_rayCastPass->setShaderProgram(rayCastShader);
    m_technique->addRenderPass(m_rayCastPass);

    m_renderCriterion->setName(QStringLiteral("pass"));
    m_renderCriterion->setValue(QStringLiteral("render"));

    m_renderPass->addFilterKey(m_renderCriterion);
    Qt3DRender::QShaderProgram* renderShader = new Qt3DRender::QShaderProgram();
    renderShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Render.vert"))));
    renderShader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Render.frag"))));
    renderShader->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Render.geom"))));

    m_renderPass->setShaderProgram(renderShader);
    m_technique->addRenderPass(m_renderPass);

    addTechnique(m_technique);

    addParameter(m_ambientParameter);
    addParameter(m_diffuseParameter);
    addParameter(m_specularParameter);
    addParameter(m_shininessParameter);
}

QList<Qt3DRender::QFilterKey*> RayCastEffect::rayCastPassCriteria() const
{
    return QList<Qt3DRender::QFilterKey*>() << m_rayCastCriterion;
}

QList<Qt3DRender::QFilterKey*> RayCastEffect::renderPassCriteria() const
{
    return QList<Qt3DRender::QFilterKey*>() << m_renderCriterion;
}
