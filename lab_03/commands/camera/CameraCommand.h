#pragma once

#include "../BaseCommand.h"

class CameraCommand : public BaseCommand
{
public:
    CameraCommand() = default;
    virtual ~CameraCommand() = default;
};

class AddCameraCommand : public CameraCommand
{
private:
    using Action = void (CameraManager::*)(const CameraId &);

    Action m_action;
    CameraId m_id;

public:
    AddCameraCommand(const CameraId &id);
    virtual ~AddCameraCommand() override = default;

    void execute() override;
};

class DeleteCameraCommand : public CameraCommand
{
private:
    using Action = void (CameraManager::*)(size_t);

    Action m_action;
    size_t m_cameraId;

public:
    DeleteCameraCommand(const size_t cameraId);
    virtual ~DeleteCameraCommand() override = default;

    void execute() override;
};

class SetActiveCameraCommand : public CameraCommand
{
private:
    using Action = void (CameraManager::*)(size_t);

    Action m_action;
    size_t m_cameraId;

public:
    SetActiveCameraCommand(const size_t cameraId);
    virtual ~SetActiveCameraCommand() override = default;

    void execute() override;
};

class MoveCameraCommand : public CameraCommand
{
private:
    using Action = void (TransformManager::*)(size_t, const MoveParams &);

    Action m_action;
    size_t m_cameraId;
    MoveParams m_params;

public:
    MoveCameraCommand(const size_t cameraId, const MoveParams &params);
    virtual ~MoveCameraCommand() override = default;

    void execute() override;
};

class RotateCameraCommand : public CameraCommand
{
private:
    using Action = void (TransformManager::*)(size_t, const RotationParams &);

    Action m_action;
    size_t m_cameraId;
    RotationParams m_params;

public:
    RotateCameraCommand(const size_t cameraId, const RotationParams &params);
    virtual ~RotateCameraCommand() override = default;
    
    void execute() override;
};
