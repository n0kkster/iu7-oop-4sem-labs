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
    findFaces(vertices, edges);

    std::cout << "\n\n\n";

    for (const auto &face : m_faces)
    {
        std::cout << "[ " << face.vertices[0] << " " << face.vertices[1] << " " << face.vertices[2] << " "
                  << face.vertices[3] << "]\n";
    }

    std::cout << "##\n";
    double t1, t2;
    bool startVisible = true, endVisible = true;

    auto viewpoint = camera->getCenter();
    viewpoint.setX(viewpoint.getX() + 430);
    viewpoint.setY(-viewpoint.getY() + 415);
    viewpoint.setZ(viewpoint.getZ() - 1200);

    std::cout << "viewpoint: " << viewpoint << "\n##\n";

    for (const auto &edge : edges)
    {
        auto start = vertices[edge.getStart()];
        auto end = vertices[edge.getEnd()];

        startVisible = true;
        endVisible = true;

        std::cout << "#\nchecking edge [" << start << ", " << end << "]\n";
        std::cout << "ray 1: " << viewpoint - start << std::endl;
        std::cout << "ray 2: " << viewpoint - end << std::endl;

        for (const auto &face : m_faces)
        {
            if (std::ranges::find(face.vertices, start) == face.vertices.end())
            {
                auto i1 = intersectLineWithPlane(viewpoint, start, face, t1);
                if (i1 && t1 < 0 && (std::abs(t1) > 0 && std::abs(t1) < 1))
                {
                    std::cout << "intersection found with: " << "[ " << face.vertices[0] << " "
                              << face.vertices[1] << " " << face.vertices[2] << " " << face.vertices[3]
                              << "]\n";
                    std::cout << "i1: " << i1.value() << " t1: " << t1 << std::endl;

                    if (isPointInPolygon(i1.value(), face))
                    // if (std::abs(t1) > 0 && std::abs(t1) < 1)
                    {
                        // std::cout << "in face, breaking!\n";
                        startVisible = false;
                        // break;
                    }
                }
            }

            if (std::ranges::find(face.vertices, end) == face.vertices.end())
            {
                auto i2 = intersectLineWithPlane(viewpoint, end, face, t2);
                if (i2 && t2 < 0 && (std::abs(t2) > 0 && std::abs(t2) < 1))
                {

                    std::cout << "intersection found with: " << "[ " << face.vertices[0] << " "
                              << face.vertices[1] << " " << face.vertices[2] << " " << face.vertices[3]
                              << "]\n";
                    std::cout << "i2: " << i2.value() << " t2: " << t2 << std::endl;

                    if (isPointInPolygon(i2.value(), face))
                    // if (std::abs(t2) > 0 && std::abs(t2) < 1)
                    {
                        // std::cout << "in face, breaking!\n";
                        endVisible = false;
                        // break;
                    }
                }
            }
        }
        if (startVisible && endVisible)
            m_visibleEdges.push_back({ start, end });
    }
}

std::vector<BaseHiddenEdgesRemovalStrategy::Edge2D> RaycastingHiddenEdgesRemovalStrategy::getVisibleEdges()
{
    return m_visibleEdges;
}

void RaycastingHiddenEdgesRemovalStrategy::findFaces(const std::vector<Vertex> &vertices,
                                                     const std::vector<Edge> &edges)
{
    m_faces.clear();

    // Создаем словарь смежности: для каждой вершины храним отсортированный вектор индексов смежных вершин
    std::map<int, std::vector<int>> adj; // Ключ - индекс вершины, значение - индексы смежных вершин
    for (const auto &edge : edges)
    {
        adj[edge.getStart()].push_back(edge.getEnd());
        adj[edge.getEnd()].push_back(edge.getStart());
    }
    // Сортируем списки смежности для упрощения поиска
    for (auto &pair : adj)
        std::sort(pair.second.begin(), pair.second.end());

    // Вектор для хранения уже обработанных граней
    std::vector<std::vector<int>> processed_faces;

    // Перебираем все ребра как возможное первое ребро цикла
    for (const auto &edge : edges)
    {
        int v1_idx = edge.getStart();
        int v2_idx = edge.getEnd();

        // Для каждой вершины v3, смежной с v2
        for (int v3_idx : adj[v2_idx])
        {
            if (v3_idx == v1_idx)
                continue; // Пропускаем v1

            // Для каждой вершины v4, смежной с v3
            for (int v4_idx : adj[v3_idx])
            {
                if (v4_idx == v2_idx || v4_idx == v1_idx)
                    continue; // Пропускаем v1 и v2

                // Проверяем, есть ли ребро между v4 и v1
                if (std::binary_search(adj[v4_idx].begin(), adj[v4_idx].end(), v1_idx))
                {
                    // Нашли потенциальный цикл v1-v2-v3-v4-v1
                    // Сортируем ID вершин для уникальности
                    std::vector<int> face_ids = { v1_idx, v2_idx, v3_idx, v4_idx };
                    std::sort(face_ids.begin(), face_ids.end());

                    // Проверяем, не была ли грань уже обработана
                    bool is_new = true;
                    for (const auto &processed : processed_faces)
                    {
                        if (processed == face_ids)
                        {
                            is_new = false;
                            break;
                        }
                    }

                    if (is_new)
                    {
                        processed_faces.push_back(face_ids);

                        // Создаем новую грань
                        Face face;
                        face.vertices = { vertices[v1_idx], vertices[v2_idx], vertices[v3_idx],
                                          vertices[v4_idx] };
                        m_faces.push_back(face);
                    }
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
                crossings++; // Увеличиваем счетчик пересечений
        }
    }
    return (crossings % 2) == 1; // Нечетное -> внутри, четное -> снаружи
}
