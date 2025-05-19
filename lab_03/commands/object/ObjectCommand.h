#pragma once

#include "../BaseCommand.h"
#include "../../managers/scene/SceneManager.h"
#include "../../managers/transform/TransformManager.h"

class ObjectCommand : public BaseCommand
{
public:
    ObjectCommand() = default;
    virtual ~ObjectCommand() = default;
};

class AddObjectCommand : public ObjectCommand
{
private:
    using Action = void (SceneManager::*)(std::shared_ptr<BaseObject>);

    Action m_action;
    std::shared_ptr<BaseObject> m_object;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    AddObjectCommand(std::shared_ptr<BaseObject> obj);
    virtual ~AddObjectCommand() override = default;

    void execute() override;
};

class RemoveObjectCommand : public ObjectCommand
{
private:
    using Action = void (SceneManager::*)(const size_t);

    Action m_action;
    size_t m_objectid;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    RemoveObjectCommand(const size_t objId);
    virtual ~RemoveObjectCommand() override = default;

    void execute() override;
};

class MoveObjectCommand : public ObjectCommand
{
private:
    using Action = void (TransformManager::*)(size_t, const MoveParams &);

    Action m_action;
    MoveParams m_params;
    size_t m_objectId;

    std::shared_ptr<TransformManager> m_transformManager;

public:
    MoveObjectCommand(size_t objId, const MoveParams &params);
    virtual ~MoveObjectCommand() = default;

    void execute() override;
};


class ScaleObjectCommand : public ObjectCommand
{
private:
    using Action = void (TransformManager::*)(size_t, const ScaleParams &);

    Action m_action;
    ScaleParams m_params;
    size_t m_objectId;

    std::shared_ptr<TransformManager> m_transformManager;

public:
    ScaleObjectCommand(size_t objId, const ScaleParams &params);
    virtual ~ScaleObjectCommand() override = default;

    void execute() override;
};

class RotateObjectCommand : public ObjectCommand
{
private:
    using Action = void (TransformManager::*)(size_t, const RotationParams &);

    Action m_action;
    RotationParams m_params;
    size_t m_objectId;

    std::shared_ptr<TransformManager> m_transformManager;

public:
    RotateObjectCommand(size_t objId, const RotationParams &params);
    virtual ~RotateObjectCommand() override = default;

    void execute() override;
};

class ComposeCommand : public ObjectCommand
{
private:
    using Action = void (SceneManager::*)(std::vector<size_t>);

    Action m_action;
    std::vector<size_t> m_objectIds;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    ComposeCommand(std::vector<size_t> objectIds);
    virtual ~ComposeCommand() override = default; 
    void execute() override;
};

class GetObjectCenterCommand : public ObjectCommand
{
private:
    using Action = void (SceneManager::*)(size_t, Vertex &) const;

    Action m_action;
    size_t m_id;
    Vertex &m_center;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    GetObjectCenterCommand(size_t id, Vertex &center);
    virtual ~GetObjectCenterCommand() override = default;
    void execute() override;
};
