#include "RaycastingHiddenEdgesRemoval.h"

#include <iostream>

struct Plane
{
    Vec3<double> normal;
    double d_coeff;

    Plane(const Vertex &pA, const Vertex &pB, const Vertex &pC)
    {
        Vec3<double> vec1 = pA - pB;
        Vec3<double> vec2 = pA - pC;
        normal = vec1.cross(vec2);
        normal = normal.normalized();
        d_coeff = -normal.dot(pA);
    }
};

void RaycastingHiddenEdgesRemovalStrategy::prepare(const std::vector<Vertex> &vertices,
                                                   const std::vector<Edge> &edges,
                                                   std::shared_ptr<const BaseCamera> camera)
{
    calculateFaces(vertices);

    // for (const auto &face : m_faces)
    // {
    //     std::cout << "[ " << face.vertices[0] << " " << face.vertices[1] << " " << face.vertices[2] << " "
    //               << face.vertices[3] << "]\n";
    // }

    double x1, x2;
    bool visible = true;

    for (const auto &edge : edges)
    {
        auto p1 = vertices[edge.getStart()];
        auto p2 = vertices[edge.getEnd()];

        p1.setX(((p1.getX() - 430) / 430) * p1.getW() + 430);
        p1.setY(((p1.getY() - 430) / 430) * p1.getW() + 430);
        p1.setZ(p1.getZ() * p1.getW());

        p2.setX(((p2.getX() - 430) / 430) * p2.getW() + 430);
        p2.setY(((p2.getY() - 430) / 430) * p2.getW() + 430);
        p2.setZ(p2.getZ() * p2.getW());

        visible = true;

        std::cout << "checking edge ( " << p1 << ", " << p2 << ")\n";

        for (const auto &face : m_faces)
        {
            auto i1 = intersectLineWithPlane(camera->getCenter(), p1, face, x1);
            auto i2 = intersectLineWithPlane(camera->getCenter(), p2, face, x2);

            if (i1 && i2)
            {

                if (isPointInPolygon(i1.value(), face))
                {
                    std::cout << "intersection found with: " << "[ " << face.vertices[0] << " "
                              << face.vertices[1] << " " << face.vertices[2] << " " << face.vertices[3]
                              << "]\n";
                    std::cout << "i1: " << i1.value() << std::endl;

                    visible = false;
                    break;
                }
            }
            // if (i2)
            // {

            //     if (isPointInPolygon(i2.value(), face))
            //     {
            //         std::cout << "intersection found with: " << "[ " << face.vertices[0] << " "
            //                   << face.vertices[1] << " " << face.vertices[2] << " " << face.vertices[3]
            //                   << "]\n";
            //         std::cout << "i2: " << i2.value() << std::endl;

            //         visible = false;
            //         break;
            //     }
            // }
        }
        if (visible)
            m_visibleEdges.push_back({ p1, p2 });
    }
}

std::vector<BaseHiddenEdgesRemovalStrategy::Edge2D> RaycastingHiddenEdgesRemovalStrategy::getVisibleEdges()
{
    return m_visibleEdges;
}

bool RaycastingHiddenEdgesRemovalStrategy::arePointsCoplanar(const Vertex &a, const Vertex &b,
                                                             const Vertex &c, const Vertex &d)
{
    Vec3<double> ab = b - a;
    Vec3<double> ac = c - a;
    Vec3<double> ad = d - a;

    Vec3<double> cross_ab_ac = ab.cross(ac);
    double volume = cross_ab_ac.dot(ad);

    return abs(volume) < 1e-9;
}

// Упорядочивает 4 точки в порядке обхода (по часовой стрелке, если смотреть снаружи)
void RaycastingHiddenEdgesRemovalStrategy::createFace(const Vertex &p1, const Vertex &p2, const Vertex &p3,
                                                      const Vertex &p4)
{
    // Находим нормаль плоскости (через векторное произведение)
    Vec3<double> v1 = p2 - p1;
    Vec3<double> v2 = p3 - p1;
    // Vec3<double> normal = v1.cross(v2);

    // Центр масс (усредняем координаты)
    Vec3<double> center((p1.getX() + p2.getX() + p3.getX() + p4.getX()) / 4.0,
                        (p1.getY() + p2.getY() + p3.getY() + p4.getY()) / 4.0,
                        (p1.getZ() + p2.getZ() + p3.getZ() + p4.getZ()) / 4.0);

    // Угол между вектором (точка - центр) и опорной осью
    auto getAngle = [&](const Vec3<double> &p) {
        Vec3<double> dir = p - center;
        dir = dir.normalized();
        return atan2(dir.getY(), dir.getX()); // Угол в плоскости XY (можно адаптировать под другие плоскости)
    };

    std::vector<Vec3<double>> points = { p1, p2, p3, p4 };

    // Сортируем точки по углу относительно центра
    std::ranges::sort(
        points, [&](const Vec3<double> &a, const Vec3<double> &b) { return getAngle(a) < getAngle(b); });

    Face f;
    f.vertices[0] = { points[0].getX(), points[0].getY(), points[0].getZ() };
    f.vertices[1] = { points[1].getX(), points[1].getY(), points[1].getZ() };
    f.vertices[2] = { points[2].getX(), points[2].getY(), points[2].getZ() };
    f.vertices[3] = { points[3].getX(), points[3].getY(), points[3].getZ() };
    m_faces.push_back(f);
}

void RaycastingHiddenEdgesRemovalStrategy::calculateFaces(const std::vector<Vertex> &points)
{
    size_t n = points.size();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            for (size_t k = j + 1; k < n; ++k)
            {
                for (size_t l = k + 1; l < n; ++l)
                {
                    Vertex p1 = points[i];
                    Vertex p2 = points[j];
                    Vertex p3 = points[k];
                    Vertex p4 = points[l];

                    p1.setX(((p1.getX() - 430) / 430) * p1.getW() + 430);
                    p1.setY(((p1.getY() - 430) / 430) * p1.getW() + 430);
                    p1.setZ(p1.getZ() * p1.getW());

                    p2.setX(((p2.getX() - 430) / 430) * p2.getW() + 430);
                    p2.setY(((p2.getY() - 430) / 430) * p2.getW() + 430);
                    p2.setZ(p2.getZ() * p2.getW());

                    p3.setX(((p3.getX() - 430) / 430) * p3.getW() + 430);
                    p3.setY(((p3.getY() - 430) / 430) * p3.getW() + 430);
                    p3.setZ(p3.getZ() * p3.getW());

                    p4.setX(((p4.getX() - 430) / 430) * p4.getW() + 430);
                    p4.setY(((p4.getY() - 430) / 430) * p4.getW() + 430);
                    p4.setZ(p4.getZ() * p4.getW());

                    if (!arePointsCoplanar(p1, p2, p3, p4))
                        continue;

                    createFace(p1, p2, p3, p4);
                }
            }
        }
    }
}

// Функция для нахождения пересечения прямой (заданной двумя точками) и плоскости
// Возвращает std::optional<Vertex>. Если пересечения нет или их бесконечно много, возвращает std::nullopt.
// Если пересечение есть, возвращает точку пересечения.
// Также возвращает параметр t через out_param_t, если пересечение найдено.
std::optional<Vertex> RaycastingHiddenEdgesRemovalStrategy::intersectLineWithPlane(const Vertex &line_p1,
                                                                                   const Vertex &line_p2,
                                                                                   const Plane &plane,
                                                                                   double &out_param_t)
{
    const double epsilon = 1e-9; // Маленькое значение для сравнения с нулем

    Vec3<double> line_dir = line_p1 - line_p2; // Направляющий вектор прямой (dx, dy, dz)

    // Скалярное произведение нормали плоскости и направляющего вектора прямой
    // dot_N_Dir = Nx*dx + Ny*dy + Nz*dz
    double dot_N_Dir = plane.normal.dot(line_dir);

    if (std::abs(dot_N_Dir) < epsilon)
    {
        // Прямая параллельна плоскости
        // Проверим, лежит ли прямая в плоскости: подставим первую точку прямой в уравнение плоскости
        // val_P1_in_PlaneEq = Nx*x1 + Ny*y1 + Nz*z1 + D_plane
        double val_P1_in_PlaneEq = plane.normal.dot(line_p1) + plane.d_coeff;
        if (std::abs(val_P1_in_PlaneEq) < epsilon)
        {
            // Прямая лежит в плоскости. Бесконечно много точек пересечения.
            // В этом случае можно вернуть, например, line_p1 и t=0, но это условно.
            // Для данной задачи лучше считать, что "уникального" пересечения нет.
            out_param_t = 0.0;   // Условно
            return std::nullopt; // Или line_p1, в зависимости от требуемой семантики
        }
        else
        {
            // Прямая параллельна и не лежит в плоскости. Нет точек пересечения.
            return std::nullopt;
        }
    }

    // Прямая пересекает плоскость в одной точке.
    // t = - (Nx*x1 + Ny*y1 + Nz*z1 + D_plane) / (Nx*dx + Ny*dy + Nz*dz)
    // t = - (plane.normal.dot(line_p1) + plane.d_coeff) / dot_N_Dir
    double val_P1_in_PlaneEq = plane.normal.dot(line_p1) + plane.d_coeff;
    out_param_t = -val_P1_in_PlaneEq / dot_N_Dir;

    // Вычисляем координаты точки пересечения
    Vertex intersection_point;
    intersection_point.setX(line_p1.getX() + out_param_t * line_dir.getX());
    intersection_point.setY(line_p1.getY() + out_param_t * line_dir.getY());
    intersection_point.setZ(line_p1.getZ() + out_param_t * line_dir.getZ());

    return intersection_point;
}

// Обертка, если плоскость задана 4-мя точками
std::optional<Vertex> RaycastingHiddenEdgesRemovalStrategy::intersectLineWithPlane(const Vertex &line_p1,
                                                                                   const Vertex &line_p2,
                                                                                   const Face &f,
                                                                                   double &out_param_t)
{
    Plane p(f.vertices[0], f.vertices[1], f.vertices[2]);
    return intersectLineWithPlane(line_p1, line_p2, p, out_param_t);
}

bool RaycastingHiddenEdgesRemovalStrategy::isPointInPolygon(const Vertex &point, const Face &f)
{
    int crossings = 0;        // Счетчик пересечений
    double px = point.getX(); // Координаты нашей тестовой точки
    double py = point.getY();

    // Проходим по всем ребрам многоугольника
    // Ребро определяется вершинами polygon_vertices[i] и polygon_vertices[j]
    for (size_t i = 0, j = f.vertices.size() - 1; i < f.vertices.size(); j = i++)
    {
        // j - это предыдущая вершина, i - текущая. Таким образом мы обходим все ребра (p[j], p[i])
        const Vertex &p_i = f.vertices[i];
        const Vertex &p_j = f.vertices[j];

        double p_i_x = p_i.getX();
        double p_i_y = p_i.getY();
        double p_j_x = p_j.getX();
        double p_j_y = p_j.getY();

        // Условие 1: Горизонтальный луч, идущий из (px, py) вправо, должен лежать
        // между y-координатами конечных точек ребра.
        // (p_i_y <= py && py < p_j_y)  - луч пересекает ребро "снизу вверх" относительно py
        // (p_j_y <= py && py < p_i_y)  - луч пересекает ребро "сверху вниз" относительно py
        // Строгое неравенство py < p_j_y (или py < p_i_y) важно для обработки горизонтальных ребер
        // и вершин, где луч может коснуться вершины.
        if (((p_i_y <= py && py < p_j_y) || (p_j_y <= py && py < p_i_y)))
        {

            // Условие 2: Точка пересечения луча с продолжением ребра должна быть справа от px.
            // Вычисляем x-координату точки пересечения горизонтального луча (y = py)
            // с линией, проходящей через p_i и p_j.
            // Формула для x_intersection: x = (py - p_i_y) * (p_j_x - p_i_x) / (p_j_y - p_i_y) + p_i_x
            // Мы проверяем, что px < x_intersection
            double x_intersection = (p_j_x - p_i_x) * (py - p_i_y) / (p_j_y - p_i_y) + p_i_x;

            if (px < x_intersection)
            {
                crossings++; // Увеличиваем счетчик пересечений
            }
        }
    }
    return (crossings % 2) == 1; // Нечетное -> внутри, четное -> снаружи
}
