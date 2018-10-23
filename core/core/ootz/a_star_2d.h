#pragma once

#include <queue>

#include "ootz/math/vector2.h"

namespace ootz
{

namespace pathfinder
{

// node's attribute in grid graph
enum class Attribute : uint8_t
{
    Reachable,
    Unreachable
};

// two-dimensional grid graph. each node has a attribute.
// this class is wrapping nested vector for secure random access.
class Grid2D
{
public:
    Grid2D(const size_t numX, const size_t numY);
    ~Grid2D();

    void setAttribute(const size_t x, const size_t y, const Attribute attribute);
    Attribute getAttribute(const size_t x, const size_t y);

    size_t getNumX() const;
    size_t getNumY() const;

private:
    Attribute& accessAttribute(const size_t x, const size_t y);

    std::vector<std::vector<Attribute>> _grid;
};

// this class is for A* algorithm.
// this is available adding (or removing) dynamically.
// if you are adding the same position, overwrite it.
class StreamGrid2D
{
    using Vector2 = math::Vector2;

    struct NodeInfo
    {
        Attribute            attribute;
        std::vector<Vector2> neighbors;

        NodeInfo();
    };

public:
    StreamGrid2D();
    StreamGrid2D(Grid2D& grid);
    ~StreamGrid2D();

    void add(const Vector2& position, const NodeInfo& nodeInfo);
    void add(Grid2D& grid);

    const std::vector<Vector2>& getNeighbors(const Vector2& node) const;
    float getCost(const Vector2& lhs, const Vector2& rhs) const;

private:
    std::unordered_map<Vector2, NodeInfo, Vector2::Hash> _streamGrid;
};

// this is A* algorithm implementation on 2D.
class AStar2D
{
    using Vector2 = math::Vector2;

    template<typename ValueType>
    using HashTable = std::unordered_map<Vector2, ValueType, Vector2::Hash>;

    // this is priority queue.
    // smallest priority value has highest priority.
    struct PriorityQueue
    {
        struct Element
        {
            Vector2 value;
            float   priority;

            Element(const Vector2& value, const float priority);
        };

        struct Compare
        {
            bool operator()(const Element& lhs, const Element& rhs);
        };

        void push(const Element& element);
        void push(const Vector2& value, const float priority);
        Element pop();
        bool isEmpty() const;

    private:
        std::priority_queue<Element, std::vector<Element>, decltype(Compare())> _queue;
    };

public:
    AStar2D();
    ~AStar2D();

    // return value is stack container. goal is in front and nearest position is in back.
    std::vector<Vector2> getPath(const StreamGrid2D& graph, const Vector2& start, const Vector2& goal);

private:

    // heuristic value is calculated from manhattan distance.
    float getHeuristic(const Vector2& lhs, const Vector2& rhs);

    // return value is stack container. goal is in front and nearest position is in back.
    std::vector<Vector2> constructPath(HashTable<Vector2>& cameFrom, const Vector2& start, const Vector2& goal);
};

} // namespace pathfinder

} // namespace ootz