#include "stdafx.h"
#include "a_star_2d.h"

// ootz::IsOutOfRange()
#include "Utility.h"

namespace ootz
{

namespace pathfinder
{

using Vector2 = math::Vector2;

Grid2D::Grid2D(const size_t numX, const size_t numY)
    : _grid(numY, std::vector<Attribute>(numX, Attribute::Reachable))
{
}

Grid2D::~Grid2D()
{
}

Attribute& Grid2D::accessAttribute(const size_t x, const size_t y)
{
    assert(false == IsOutOfRange(_grid, y) && "y is out of range.");
    assert(false == IsOutOfRange(_grid.front(), x) && "x is out of range.");

    const size_t row = (_grid.size() - 1) - y;

    return _grid[row][x];
}

void Grid2D::setAttribute(const size_t x, const size_t y, const Attribute attribute)
{
    accessAttribute(x, y) = attribute;
}

Attribute Grid2D::getAttribute(const size_t x, const size_t y)
{
    return accessAttribute(x, y);
}

size_t Grid2D::getNumX() const
{
    assert(_grid.size() > 0 && "grid 2d's size is zero.");

    return _grid.front().size();
}

size_t Grid2D::getNumY() const
{
    return _grid.size();
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
    add(grid);
}

StreamGrid2D::~StreamGrid2D()
{
}

void StreamGrid2D::add(const Vector2& position, const NodeInfo& nodeInfo)
{
    _streamGrid.insert_or_assign(position, nodeInfo);
}

void StreamGrid2D::add(Grid2D& grid)
{
    using std::pair;
    using std::make_pair;

    using IntPair = pair<int32_t, int32_t>;

    const std::vector<IntPair> eightDirections =
    {
        make_pair(0,  1),
        make_pair(1,  1),
        make_pair(1,  0),
        make_pair(1, -1),
        make_pair(0, -1),
        make_pair(-1, -1),
        make_pair(-1,  0),
        make_pair(-1,  1)
    };

    const size_t ySize = grid.getNumY();
    for (size_t y = 0; y < ySize; ++y)
    {
        const size_t xSize = grid.getNumX();
        for (size_t x = 0; x < xSize; ++x)
        {
            NodeInfo nodeInfo;
            nodeInfo.attribute = grid.getAttribute(x, y);

            // if neighbor is reachable then add to neighbors
            for (const auto& dir : eightDirections)
            {
                const int32_t nx = x + dir.first;
                const int32_t ny = y + dir.second;

                if (IsOutOfRange(xSize, nx) ||
                    IsOutOfRange(ySize, ny))
                    continue;

                if (grid.getAttribute(nx, ny) == Attribute::Unreachable)
                    continue;

                nodeInfo.neighbors.emplace_back(
                    Vector2(static_cast<float>(nx),
                            static_cast<float>(ny)));
            }

            add(Vector2(static_cast<float>(x),
                        static_cast<float>(y)),
                nodeInfo);
        }
    }
}

const std::vector<Vector2>& StreamGrid2D::getNeighbors(const Vector2& node) const
{
    const auto found = _streamGrid.find(node);
    assert(found != _streamGrid.end() && "node does not exist.");
    return found->second.neighbors;
}

float StreamGrid2D::getCost(const Vector2& lhs, const Vector2& rhs) const
{
    const Vector2 dif = lhs - rhs;

    return std::sqrt(dif.x * dif.x + dif.y * dif.y);
}

float AStar2D::getHeuristic(const Vector2& lhs, const Vector2& rhs)
{
    return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}

std::vector<Vector2> AStar2D::constructPath(HashTable<Vector2>& cameFrom, const Vector2& start, const Vector2& goal)
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

std::vector<Vector2> AStar2D::getPath(const StreamGrid2D& graph,
                                      const Vector2& start,
                                      const Vector2& goal)
{
    PriorityQueue frontier;

    HashTable<Vector2> cameFrom;
    HashTable<float> costSoFar;
    HashTable<float> priority;

    priority[start] = 0.0f;
    frontier.push(start, 0.0f);
    costSoFar[start] = 0.0f;

    while (!frontier.isEmpty())
    {
        // get smallest cost node.
        const Vector2 current = frontier.pop().value;

        // if you reached to goal, construct path.
        if (IsEqual(current, goal))
            break;

        for (const Vector2& next : graph.getNeighbors(current))
        {
            // new path
            const float newCost = costSoFar[current] + graph.getCost(current, next);

            const bool isFound = costSoFar.find(next) != costSoFar.end();

            // if first visit or new path is better, write(overwrite) it.
            if (!isFound || newCost < costSoFar[next])
            {
                costSoFar[next] = newCost;

                const float nextPriority = newCost + getHeuristic(goal, next);
                priority[next] = nextPriority;
                frontier.push(next, nextPriority);

                // update the path.
                cameFrom[next] = current;
            }
        }
    }

    // if the goal is not reached, return empty vector.
    const bool isFound = cameFrom.find(goal) != cameFrom.end();
    if (!isFound)
        return std::vector<Vector2>();

    // else, construct path.
    return constructPath(cameFrom, start, goal);
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

void AStar2D::PriorityQueue::push(const Element& element)
{
    _queue.push(element);
}

void AStar2D::PriorityQueue::push(const Vector2& value, const float priority)
{
    push(Element(value, priority));
}

AStar2D::PriorityQueue::Element AStar2D::PriorityQueue::pop()
{
    assert(!_queue.empty() && "queue is empty.");
    const Element top = _queue.top();
    _queue.pop();
    return top;
}

bool AStar2D::PriorityQueue::isEmpty() const
{
    return _queue.empty();
}

} // namespace pathfinder

} // namespace ootz