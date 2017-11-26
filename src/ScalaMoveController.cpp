#include "ScalaMoveController.h"
#include "ScalaEntity.h"

#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QAnalogAxisInput>
#include <Qt3DInput/QAxis>
#include <Qt3DInput/QButtonAxisInput>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DInput/QKeyboardDevice>
#include <Qt3DInput/QLogicalDevice>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QMouseEvent>
#include <Qt3DRender/QCamera>

ScalaMoveController::ScalaMoveController(ScalaEntity* scala, Qt3DCore::QNode* parent):
    Qt3DCore::QEntity(parent),
    m_scala(scala),
    m_camera(nullptr),
    m_viewXAxis(new Qt3DInput::QAxis()),
    m_viewYAxis(new Qt3DInput::QAxis()),
    m_linearMoveAxis(new Qt3DInput::QAxis()),
    m_rotateAxis(new Qt3DInput::QAxis()),
    m_mouseXInput(new Qt3DInput::QAnalogAxisInput()),
    m_mouseYInput(new Qt3DInput::QAnalogAxisInput()),
    m_keyboardForwardInput(new Qt3DInput::QButtonAxisInput()),
    m_keyboardBackwardInput(new Qt3DInput::QButtonAxisInput()),
    m_keyboardLeftInput(new Qt3DInput::QButtonAxisInput()),
    m_keyboardRightInput(new Qt3DInput::QButtonAxisInput()),
    m_mouseDevice(new Qt3DInput::QMouseDevice()),
    m_keyboardDevice(new Qt3DInput::QKeyboardDevice()),
    m_logicalDevice(new Qt3DInput::QLogicalDevice()),
    m_frameAction(new Qt3DLogic::QFrameAction()),
    m_linearSpeed(10.0f),
    m_rotationSpeed(10.0f),
    m_lookSpeed(180.0f)
{
    m_mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
    m_mouseXInput->setSourceDevice(m_mouseDevice);
    m_viewXAxis->addInput(m_mouseXInput);

    m_mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
    m_mouseYInput->setSourceDevice(m_mouseDevice);
    m_viewYAxis->addInput(m_mouseYInput);

    m_keyboardForwardInput->setButtons(QVector<int>() << Qt::Key_Up);
    m_keyboardForwardInput->setScale(1.0f);
    m_keyboardForwardInput->setSourceDevice(m_keyboardDevice);
    m_linearMoveAxis->addInput(m_keyboardForwardInput);

    m_keyboardBackwardInput->setButtons(QVector<int>() << Qt::Key_Down);
    m_keyboardBackwardInput->setScale(-1.0f);
    m_keyboardBackwardInput->setSourceDevice(m_keyboardDevice);
    m_linearMoveAxis->addInput(m_keyboardBackwardInput);

    m_keyboardLeftInput->setButtons(QVector<int>() << Qt::Key_Left);
    m_keyboardLeftInput->setScale(-1.0f);
    m_keyboardLeftInput->setSourceDevice(m_keyboardDevice);
    m_rotateAxis->addInput(m_keyboardLeftInput);

    m_keyboardRightInput->setButtons(QVector<int>() << Qt::Key_Right);
    m_keyboardRightInput->setScale(1.0f);
    m_keyboardRightInput->setSourceDevice(m_keyboardDevice);
    m_rotateAxis->addInput(m_keyboardRightInput);

    m_logicalDevice->addAxis(m_viewXAxis);
    m_logicalDevice->addAxis(m_viewYAxis);
    m_logicalDevice->addAxis(m_linearMoveAxis);
    m_logicalDevice->addAxis(m_rotateAxis);

    QObject::connect(m_frameAction, SIGNAL(triggered(float)),
                     this, SLOT(onTriggered(float)));

    QObject::connect(this, &Qt3DCore::QEntity::enabledChanged,
                     m_logicalDevice, &Qt3DInput::QLogicalDevice::setEnabled);

    addComponent(m_frameAction);
    addComponent(m_logicalDevice);
}

void ScalaMoveController::onTriggered(float dt)
{
    if(m_camera == nullptr)
        return;

    if(m_linearMoveAxis->value() != 0.0f)
    {
        const QVector3D& viewVector = m_camera->viewVector();

        QVector3D moveVector(viewVector.x(), 0.0f, viewVector.z());
        QVector3D normalizedMoveVector(moveVector.normalized());

        if(normalizedMoveVector.isNull())
            return;

        //m_camera->translateWorld(normalizedMoveVector * m_linearMoveAxis->value() * m_linearSpeed * dt);
        m_scala->move(m_linearMoveAxis->value() * m_linearSpeed * dt);
    }

    if(m_rotateAxis->value() != 0.0f)
    {
        m_scala->rotate(m_rotateAxis->value() * m_rotationSpeed * dt);
    }

    static const QVector3D upVector(0.0f, 1.0f, 0.0f);

    m_camera->pan(m_viewXAxis->value() * m_lookSpeed * dt, upVector);
    m_camera->tilt(m_viewYAxis->value() * m_lookSpeed * dt);
}

void ScalaMoveController::setCamera(Qt3DRender::QCamera* camera)
{
    m_scala->setViewCamera(camera);
    m_camera = camera;
}
