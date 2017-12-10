#ifndef COMPUTEENTITY_H
#define COMPUTEENTITY_H

#include <Qt3DCore/QEntity>

class ComputeEffect;

/*!
 * \brief Сущность для навешивания ComputeEffect
 */
class ComputeEntity : public Qt3DCore::QEntity
{
public:
    explicit ComputeEntity(QNode* parent = nullptr);
    ComputeEffect* effect() const;

private:
    ComputeEffect* m_computeEffect;
};

#endif // COMPUTEENTITY_H
