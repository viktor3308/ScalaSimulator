#ifndef SIMULATORSCENEENTITY_H
#define SIMULATORSCENEENTITY_H

#include <Qt3DCore/QEntity>

class RayCastEffect;

namespace Qt3DRender
{
    class QSceneLoader;
}

/*!
 * \brief Сущность, представляющая загружаемую сцену
 */
class SimulatorSceneEntity: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit SimulatorSceneEntity(QNode* parent = nullptr);

    RayCastEffect* effect() const;
    void onLoaderStatusChanged();

private:
    void walkEntity(Qt3DCore::QEntity *e, int depth = 0);

    Qt3DRender::QSceneLoader* m_sceneLoader;
    RayCastEffect* m_effect;
};

#endif // SIMULATORSCENEENTITY_H
