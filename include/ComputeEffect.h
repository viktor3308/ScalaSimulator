#ifndef COMPUTEEFFECT_H
#define COMPUTEEFFECT_H

#include <Qt3DRender/QEffect>

namespace Qt3DRender
{
    class QRenderPass;
    class QFilterKey;
}

class ComputeEffect : public Qt3DRender::QEffect
{
public:
    explicit ComputeEffect(Qt3DCore::QNode *parent = 0);

    QList<Qt3DRender::QFilterKey*> computePassCriteria() const;

private:
    Qt3DRender::QTechnique *m_technique;
    Qt3DRender::QRenderPass *m_computePass;
    Qt3DRender::QFilterKey *m_computeCriterion;

};

#endif // COMPUTEEFFECT_H
