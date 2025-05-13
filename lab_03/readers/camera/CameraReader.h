#pragma once

#include "../BaseReader.h"
#include "../../matrix/matrix.h"
#include "../../component/primitive/visible/model/vertex/Vertex.h"

class CameraReader : public BaseReader
{
protected:
    Matrix<double> m_orientation;
    Vertex m_viewpoint;

    virtual std::shared_ptr<Matrix<double>> readOrientation() = 0;
    virtual std::shared_ptr<Vertex> readViewpoint() = 0;

public:
    CameraReader() = delete;
    CameraReader(const std::string &filename) : BaseReader(filename), m_orientation(4, 0, 0) { };

    virtual ~CameraReader() override = default;

    virtual void read(BaseBuilder &builder, size_t part) override;

    std::shared_ptr<Matrix<double>> getOrientation() const;
    std::shared_ptr<Vertex> getViewpoint() const;
};
