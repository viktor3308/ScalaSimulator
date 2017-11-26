#include "SimulatorSceneEntity.h"
#include "RayCastEffect.h"

#include <Qt3DRender/QSceneLoader>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <QUrl>

SimulatorSceneEntity::SimulatorSceneEntity(Qt3DCore::QNode* parent):
    Qt3DCore::QEntity(parent),
    m_sceneLoader(new Qt3DRender::QSceneLoader(this)),
    m_effect(new RayCastEffect(this))
{
    connect(m_sceneLoader, &Qt3DRender::QSceneLoader::statusChanged, this, &SimulatorSceneEntity::onLoaderStatusChanged);
    addComponent(m_sceneLoader);
    m_sceneLoader->setSource(QUrl(QStringLiteral("qrc:/scene.fbx")));
}

RayCastEffect* SimulatorSceneEntity::effect() const
{
    return m_effect;
}

void SimulatorSceneEntity::onLoaderStatusChanged()
{
    if(m_sceneLoader->status() != Qt3DRender::QSceneLoader::Ready)
        return;

    QVector<Qt3DCore::QEntity*> entities = m_sceneLoader->entities();
    if (entities.isEmpty())
        return;

    Qt3DCore::QEntity *root = entities[0];
    walkEntity(root);
}

void SimulatorSceneEntity::walkEntity(Qt3DCore::QEntity* e, int depth)
{
    Qt3DCore::QNodeVector nodes = e->childNodes();
    for (int i = 0; i < nodes.count(); ++i)
    {
        Qt3DCore::QNode *node = nodes[i];
        Qt3DCore::QEntity *entity = qobject_cast<Qt3DCore::QEntity *>(node);
        if (entity)
        {
            Qt3DCore::QComponentVector comps = entity->components();
            for(int j = 0; j < comps.size(); ++j)
            {
                Qt3DExtras::QPhongMaterial* material = qobject_cast<Qt3DExtras::QPhongMaterial*>(comps[j]);
                if(material)
                {
                    material->setEffect(m_effect);
                }
            }
            walkEntity(entity, depth + 1);
        }
    }
}
