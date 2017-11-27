#ifndef RAYCASTEFFECT_H
#define RAYCASTEFFECT_H

#include <Qt3DRender/QEffect>

namespace Qt3DRender
{
    class QRenderPass;
    class QFilterKey;
}

class RayCastEffect : public Qt3DRender::QEffect
{
public:
    explicit RayCastEffect(Qt3DCore::QNode *parent = 0);

    QList<Qt3DRender::QFilterKey*> rayCastPassCriteria() const;

    QList<Qt3DRender::QFilterKey*> renderPassCriteria() const;

private:
    Qt3DRender::QTechnique *m_technique;
    Qt3DRender::QRenderPass *m_rayCastPass;
    Qt3DRender::QRenderPass *m_renderPass;
    Qt3DRender::QRenderPass *m_renderRayPass;
    Qt3DRender::QFilterKey *m_rayCastCriterion;
    Qt3DRender::QFilterKey *m_renderCriterion;

    Qt3DRender::QParameter *m_ambientParameter;
    Qt3DRender::QParameter *m_diffuseParameter;
    Qt3DRender::QParameter *m_specularParameter;
    Qt3DRender::QParameter *m_shininessParameter;
};

#endif // RAYCASTEFFECT_H
