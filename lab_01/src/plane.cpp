#include "plane.h"

// Конструктор
// ==================================================
Plane::Plane(QWidget *parent) : QGraphicsView(parent) {}
// ==================================================

void Plane::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());

    for (const auto &p : points)
        painter.drawPoint(realCoordToScreenCoord(p));
    
    for (const auto &e : edges)
        painter.drawLine(realCoordToScreenCoord(points[e.id1]), realCoordToScreenCoord(points[e.id2]));
}

QPointF Plane::realCoordToScreenCoord(QPointF point)
{
    return {point.x() + viewport()->size().width() / 2, -point.y() + viewport()->size().height() / 2};
}

void Plane::clearPoints()
{
    points.clear();
}

void Plane::clearEdges()
{
    edges.clear();
}

void Plane::addPoint(QPointF point)
{
    points.append(point);
}

void Plane::addEdge(edge_t edge)
{
    edges.append(edge);
}

// matrix_t Plane::multiplyMatrices(const matrix_t &matrix1, const matrix_t &matrix2) 
// {
//     matrix_t res;
//     res.push_back({0, 0, 0});
//     res.push_back({0, 0, 0});
//     res.push_back({0, 0, 0});

//     if (matrix1[0].size() != matrix2.size())
//     {
//         qDebug() << "matrix invalid dimensions:" << matrix1[0].size() << "; " << matrix2.size();
//         abort();
//     }

//     for (size_t i = 0; i < matrix1.size(); ++i)
//         for (size_t j = 0; j < matrix2[0].size(); ++j)
//             for (size_t k = 0; k < matrix1[0].size(); ++k)
//                 res[i][j] += matrix1[i][k] * matrix2[k][j];

//     return res;
// }

// void Plane::initTMatrix(matrix_t &m)
// {
//     m.clear();
//     m.push_back({1, 0, 0});
//     m.push_back({0, 1, 0});
//     m.push_back({0, 0, 1});
// }

// void Plane::addOffset(offset_t offset)
// {
//     matrix_t offsetM;
//     prev_transformation = curr_transformation;

//     initTMatrix(offsetM);
//     offsetM[0][2] = offset.x;
//     offsetM[1][2] = offset.y;
    
//     curr_transformation = multiplyMatrices(offsetM, curr_transformation);
// }

// void Plane::addScale(scale_t scale)
// {
//     matrix_t scaleM, offsetM;
//     prev_transformation = curr_transformation;

//     initTMatrix(scaleM);
//     initTMatrix(offsetM);

//     offsetM[0][2] = -scale.cx;
//     offsetM[1][2] = -scale.cy;

//     curr_transformation = multiplyMatrices(offsetM, curr_transformation);
    
//     scaleM[0][0] = scale.kx;
//     scaleM[1][1] = scale.ky;

//     curr_transformation = multiplyMatrices(scaleM, curr_transformation);

//     offsetM[0][2] = scale.cx;
//     offsetM[1][2] = scale.cy;

//     curr_transformation = multiplyMatrices(offsetM, curr_transformation);
// }

// void Plane::addRotation(rotation_t rotation)
// {
//     matrix_t rotationM, offsetM;
//     double c = cos(rotation.angle), s = sin(rotation.angle);
//     prev_transformation = curr_transformation;

//     initTMatrix(rotationM);
//     initTMatrix(offsetM);

//     offsetM[0][2] = -rotation.cx;
//     offsetM[1][2] = -rotation.cy;

//     curr_transformation = multiplyMatrices(offsetM, curr_transformation);
    
//     rotationM[0][0] = c;
//     rotationM[0][1] = -s;
//     rotationM[1][0] = s;
//     rotationM[1][1] = c;

//     curr_transformation = multiplyMatrices(rotationM, curr_transformation);

//     offsetM[0][2] = rotation.cx;
//     offsetM[1][2] = rotation.cy;

//     curr_transformation = multiplyMatrices(offsetM, curr_transformation);
// }