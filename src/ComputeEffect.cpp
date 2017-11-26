#include "ComputeEffect.h"

#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QShaderProgram>
#include <QUrl>

ComputeEffect::ComputeEffect(Qt3DCore::QNode* parent):
    Qt3DRender::QEffect(parent),
    m_technique(new Qt3DRender::QTechnique()),
    m_computePass(new Qt3DRender::QRenderPass()),
    m_computeCriterion(new Qt3DRender::QFilterKey(this))
{
    m_technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    m_technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    m_technique->graphicsApiFilter()->setMajorVersion(4);
    m_technique->graphicsApiFilter()->setMinorVersion(3);

    m_computeCriterion->setName(QStringLiteral("pass"));
    m_computeCriterion->setValue(QStringLiteral("compute"));

    m_computePass->addFilterKey(m_computeCriterion);
    Qt3DRender::QShaderProgram* computeShader = new Qt3DRender::QShaderProgram();
    computeShader->setComputeShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Compute.comp"))));

    m_computePass->setShaderProgram(computeShader);
    m_technique->addRenderPass(m_computePass);

    addTechnique(m_technique);
}

QList<Qt3DRender::QFilterKey*> ComputeEffect::computePassCriteria() const
{
    return QList<Qt3DRender::QFilterKey*>() << m_computeCriterion;
}
