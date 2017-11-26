#include "ComputeEntity.h"
#include "ComputeEffect.h"

#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QComputeCommand>

ComputeEntity::ComputeEntity(Qt3DCore::QNode* parent):
    Qt3DCore::QEntity(parent),
    m_computeEffect(new ComputeEffect(this))
{
    Qt3DRender::QMaterial* material = new Qt3DRender::QMaterial();
    material->setEffect(m_computeEffect);
    addComponent(material);

    Qt3DRender::QComputeCommand* computeCommand = new Qt3DRender::QComputeCommand();
    addComponent(computeCommand);
}

ComputeEffect*ComputeEntity::effect() const
{
    return m_computeEffect;
}
