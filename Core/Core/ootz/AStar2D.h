#pragma once

/* std::uint8_t */
#include <cstdint>

/* std::unordered_map */
#include <unordered_map>

/* std::vector */
#include <vector>

/* std::priority_queue */
#include <queue>

/* ootz::Vector2 */
#include "Vector2.h"

namespace ootz
{

/* node's attribute in grid graph */
enum class Attribute : std::uint8_t
{
    Reachable,
    Unreachable
};

/*  two-dimensional grid graph. each node has a attribute.
    this class is wrapping nested vector for secure random access.
*/
class Grid2D
{
private:
    std::vector<std::vector<Attribute>> grid_;

    Attribute& AccessAttribute_(const std::size_t x, const std::size_t y);

public:
     Grid2D(const std::size_t numX, const std::size_t numY);
    ~Grid2D();

    void SetAttribute(const std::size_t x, const std::size_t y, const Attribute attribute);
    Attribute GetAttribute(const std::size_t x, const std::size_t y);

    std::size_t GetNumX() const;
    std::size_t GetNumY() const;
};

/*  this class is for A* algorithm.
    this is available adding (or removing) dynamically.
    if you are adding the same position, overwrite it.
*/
class StreamGrid2D
{
private:
    struct NodeInfo
    {
        Attribute            attribute;
        std::vector<Vector2> neighbors;

        NodeInfo();
    };

    std::unordered_map<Vector2, NodeInfo, Vector2::Hash> stream_grid_;

public:
    StreamGrid2D();
    StreamGrid2D(Grid2D& grid);
    ~StreamGrid2D();

    void Add(const Vector2& position, const NodeInfo& nodeInfo);
    void Add(Grid2D& grid);

    const std::vector<Vector2>& GetNeighbors(const Vector2& node) const;
    float GetCost(const Vector2& lhs, const Vector2& rhs) const;
};

/*  this is A* algorithm implementation on 2D.
*/
class AStar2D
{
private:
    template<typename ValueType>
    using HashTable = std::unordered_map<Vector2, ValueType, Vector2::Hash>;

    /*  this is priority queue.
        smallest priority value has highest priority.
    */
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

    private:
        std::priority_queue<Element, std::vector<Element>, decltype(Compare())> queue_;

    public:
        void Push(const Element& element);
        void Push(const Vector2& value, const float priority);
        Element Pop();
        bool IsEmpty() const;
    };

    /*  heuristic value is calculated from manhattan distance.
    */
    float GetHeuristic_(const Vector2& lhs, const Vector2& rhs);

    /*  return value is stack container. goal is in front and nearest position is in back.
    */
    std::vector<Vector2> ConstructPath_(HashTable<Vector2>& cameFrom, const Vector2& start, const Vector2& goal);

public:
    AStar2D();
    ~AStar2D();

    /*  return value is stack container. goal is in front and nearest position is in back.
    */
    std::vector<Vector2> GetPath(const StreamGrid2D& graph, const Vector2& start, const Vector2& goal);
};


} // namespace ootz