#include "stdafx.h"
#include "AStar2D.h"

/* assert() */
#include <cassert>

/* ootz::IsOutOfRange() */
#include "Utility.h"

namespace ootz
{

Grid2D::Grid2D(const std::size_t numX, const std::size_t numY)
    : grid_(numY, std::vector<Attribute>(numX, Attribute::Reachable))
{
}

Grid2D::~Grid2D()
{
}

Attribute& Grid2D::AccessAttribute_(const std::size_t x, const std::size_t y)
{
    const bool isOutOfRangeRow = IsOutOfRange(grid_, y);
    assert( ! isOutOfRangeRow && "y is out of range.");

    const bool isOutOfRangeCol = IsOutOfRange(grid_.front(), x);
    assert( ! isOutOfRangeCol && "x is out of range.");

    const std::size_t row = (grid_.size() - 1) - y;

    return grid_[row][x];
}

void Grid2D::SetAttribute(const std::size_t x, const std::size_t y, const Attribute attribute)
{
    AccessAttribute_(x, y) = attribute;
}

Attribute Grid2D::GetAttribute(const std::size_t x, const std::size_t y)
{
    return AccessAttribute_(x, y);
}

std::size_t Grid2D::GetNumX() const
{
    assert(grid_.size() > 0 && "grid 2d's size is zero.");

    return grid_.front().size();
}

std::size_t Grid2D::GetNumY() const
{
    return grid_.size();
}

StreamGrid2D::NodeInfo::NodeInfo()
    : attribute(Attribute::Reachable)
{
}

StreamGrid2D::StreamGrid2D()
{
}

StreamGrid2D::StreamGrid2D(Grid2D& grid)
{
    Add(grid);
}

StreamGrid2D::~StreamGrid2D()
{
}

void StreamGrid2D::Add(const Vector2& position, const NodeInfo& nodeInfo)
{
    stream_grid_.insert_or_assign(position, nodeInfo);
}

void StreamGrid2D::Add(Grid2D& grid)
{
    using IntPair = std::pair<int32_t, int32_t>;

    const std::vector<IntPair> eightDirections =
    {
        std::make_pair(0,  1),
        std::make_pair(1,  1),
        std::make_pair(1,  0),
        std::make_pair(1, -1),
        std::make_pair(0, -1),
        std::make_pair(-1, -1),
        std::make_pair(-1,  0),
        std::make_pair(-1,  1)
    };

    const std::size_t ySize = grid.GetNumY();
    for (std::size_t y = 0; y < ySize; ++y)
    {
        const std::size_t xSize = grid.GetNumX();
        for (std::size_t x = 0; x < xSize; ++x)
        {
            NodeInfo nodeInfo;
            nodeInfo.attribute = grid.GetAttribute(x, y);

            // if neighbor is reachable then add to neighbors
            for (const auto& dir : eightDirections)
            {
                const int32_t nx = x + dir.first;
                const int32_t ny = y + dir.second;

                const bool isOutOfRangeX = IsOutOfRange(xSize, nx);
                const bool isOutOfRangeY = IsOutOfRange(ySize, ny);

                if (isOutOfRangeX ||
                    isOutOfRangeY)
                    continue;

                if (grid.GetAttribute(nx, ny) == Attribute::Unreachable)
                    continue;

                nodeInfo.neighbors.emplace_back(
                    Vector2(static_cast<float>(nx),
                            static_cast<float>(ny)));
            }

            Add(Vector2(static_cast<float>(x),
                        static_cast<float>(y)),
                nodeInfo);
        }
    }
}

const std::vector<Vector2>& StreamGrid2D::GetNeighbors(const Vector2& node) const
{
    const auto found = stream_grid_.find(node);

    assert(found != stream_grid_.end() && "node does not exist.");

    return found->second.neighbors;
}

float StreamGrid2D::GetCost(const Vector2& lhs, const Vector2& rhs) const
{
    const Vector2 dif = lhs - rhs;

    return std::sqrt(dif.x * dif.x + dif.y * dif.y);
}

float AStar2D::GetHeuristic_(const Vector2& lhs, const Vector2& rhs)
{
    return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}

std::vector<Vector2> AStar2D::ConstructPath_(HashTable<Vector2>& cameFrom, const Vector2& start, const Vector2& goal)
{
    Vector2 current = goal;

    std::vector<Vector2> pathStack;
    while (!IsEqual(current, start))
    {
        pathStack.emplace_back(current);
        current = cameFrom[current];
    }

    return pathStack;
}

AStar2D::AStar2D()
{
}

AStar2D::~AStar2D()
{
}

std::vector<Vector2> AStar2D::GetPath(const StreamGrid2D& graph, 
                                      const Vector2& start, 
                                      const Vector2& goal)
{
    PriorityQueue frontier;

    HashTable<Vector2> cameFrom;
    HashTable<float> costSoFar;
    HashTable<float> priority;

    priority[start] = 0.0f;
    frontier.Push(start, 0.0f);
    costSoFar[start] = 0.0f;

    while ( ! frontier.IsEmpty())
    {
        // get smallest cost node.
        const Vector2 current = frontier.Pop().value;

        // if you reached to goal, construct path.
        if (IsEqual(current, goal))
            break;

        for (const Vector2& next : graph.GetNeighbors(current))
        {
            // new path
            const float newCost = costSoFar[current] + graph.GetCost(current, next);

            const bool isFound = costSoFar.find(next) != costSoFar.end();

            // if first visit or new path is better, write(overwrite) it.
            if ( ! isFound || newCost < costSoFar[next])
            {
                costSoFar[next] = newCost;

                const float nextPriority = newCost + GetHeuristic_(goal, next);
                priority[next] = nextPriority;
                frontier.Push(next, nextPriority);

                // update the path.
                cameFrom[next] = current;
            }
        }
    }

    // if the goal is not reached, return empty vector.
    const bool isFound = cameFrom.find(goal) != cameFrom.end();
    if ( ! isFound)
        return std::vector<Vector2>();

    // else, construct path.
    return ConstructPath_(cameFrom, start, goal);
}

AStar2D::PriorityQueue::Element::Element(const Vector2& value, const float priority)
    : value(value)
    , priority(priority)
{
}

bool AStar2D::PriorityQueue::Compare::operator()(const Element& lhs, const Element& rhs)
{
    return lhs.priority > rhs.priority;
}

void AStar2D::PriorityQueue::Push(const Element& element)
{
    queue_.push(element);
}

void AStar2D::PriorityQueue::Push(const Vector2& value, const float priority)
{
    Push(Element(value, priority));
}

AStar2D::PriorityQueue::Element AStar2D::PriorityQueue::Pop()
{
    assert(!queue_.empty() && "queue is empty.");

    const Element top = queue_.top();
    queue_.pop();

    return top;
}

bool AStar2D::PriorityQueue::IsEmpty() const
{
    return queue_.empty();
}

} // namespace ootz