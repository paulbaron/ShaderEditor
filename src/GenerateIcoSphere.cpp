#include "GenerateIcoSphere.hh"

#include <map>
#include <cstring>
#include <stdint.h>

// Generate an icosphere
typedef std::pair<std::size_t, std::size_t>				idxPair_t;

class IndexPairHash
{
public:
    std::size_t operator ()(const idxPair_t &idxpair1, const idxPair_t &idxpair2) const
    {
        std::size_t a = idxpair1.first;
        std::size_t b = idxpair1.second;
        std::size_t hash1 = a >= b ? a * a + a + b : a + b * b;
        a = idxpair2.first;
        b = idxpair2.second;
        std::size_t hash2 = a >= b ? a * a + a + b : a + b * b;
        return (hash1 < hash2);
    }
};

typedef std::map<idxPair_t, std::size_t, IndexPairHash> idxHash_t;

static std::size_t getMiddlePoint(std::vector<glm::vec3> &vertexTab, idxHash_t &middlePoints, std::size_t p1, std::size_t p2)
{
    // first check if we have it already
    bool firstIsSmaller = p1 < p2;
    std::size_t smallerIndex = firstIsSmaller ? p1 : p2;
    std::size_t greaterIndex = firstIsSmaller ? p2 : p1;
    idxPair_t key;

    key.first = smallerIndex;
    key.second = greaterIndex;

    std::size_t ret;

    idxHash_t::iterator it = middlePoints.find(key);
    if (it != middlePoints.end())
    {
        return (it->second);
    }

    // not in cache, calculate it
    glm::vec3 point1 = vertexTab[p1];
    glm::vec3 point2 = vertexTab[p2];
    glm::vec3 middle = (point1 + point2) / 2.0f;

    // add vertex makes sure point is on unit sphere
    vertexTab.push_back(glm::normalize(glm::vec3(middle)));

    ret = vertexTab.size() - 1;

    // store it, return index
    middlePoints[key] = ret;
    return (ret);
}

void generateIcoSphere(std::size_t recursion, std::vector<glm::vec3> &vertex, std::vector<glm::uvec1> &indices)
{
    idxHash_t					middlePoints;
    std::size_t					currentIdx = 0;

    // create 12 vertices of a icosahedron
    const float t = (1.0f + (float)std::sqrt(5.0f)) / 2.0f;

    vertex.push_back(glm::normalize(glm::vec3(-1, t, 0)));
    vertex.push_back(glm::normalize(glm::vec3(1, t, 0)));
    vertex.push_back(glm::normalize(glm::vec3(-1, -t, 0)));
    vertex.push_back(glm::normalize(glm::vec3(1, -t, 0)));
    vertex.push_back(glm::normalize(glm::vec3(0, -1, t)));
    vertex.push_back(glm::normalize(glm::vec3(0, 1, t)));
    vertex.push_back(glm::normalize(glm::vec3(0, -1, -t)));
    vertex.push_back(glm::normalize(glm::vec3(0, 1, -t)));
    vertex.push_back(glm::normalize(glm::vec3(t, 0, -1)));
    vertex.push_back(glm::normalize(glm::vec3(t, 0, 1)));
    vertex.push_back(glm::normalize(glm::vec3(-t, 0, -1)));
    vertex.push_back(glm::normalize(glm::vec3(-t, 0, 1)));

    indices.push_back(glm::uvec1(0));
    indices.push_back(glm::uvec1(11));
    indices.push_back(glm::uvec1(5));
    indices.push_back(glm::uvec1(0));
    indices.push_back(glm::uvec1(5));
    indices.push_back(glm::uvec1(1));
    indices.push_back(glm::uvec1(0));
    indices.push_back(glm::uvec1(1));
    indices.push_back(glm::uvec1(7));
    indices.push_back(glm::uvec1(0));
    indices.push_back(glm::uvec1(7));
    indices.push_back(glm::uvec1(10));
    indices.push_back(glm::uvec1(0));
    indices.push_back(glm::uvec1(10));
    indices.push_back(glm::uvec1(11));
    indices.push_back(glm::uvec1(1));
    indices.push_back(glm::uvec1(5));
    indices.push_back(glm::uvec1(9));
    indices.push_back(glm::uvec1(5));
    indices.push_back(glm::uvec1(11));
    indices.push_back(glm::uvec1(4));
    indices.push_back(glm::uvec1(11));
    indices.push_back(glm::uvec1(10));
    indices.push_back(glm::uvec1(2));
    indices.push_back(glm::uvec1(10));
    indices.push_back(glm::uvec1(7));
    indices.push_back(glm::uvec1(6));
    indices.push_back(glm::uvec1(7));
    indices.push_back(glm::uvec1(1));
    indices.push_back(glm::uvec1(8));
    indices.push_back(glm::uvec1(3));
    indices.push_back(glm::uvec1(9));
    indices.push_back(glm::uvec1(4));
    indices.push_back(glm::uvec1(3));
    indices.push_back(glm::uvec1(4));
    indices.push_back(glm::uvec1(2));
    indices.push_back(glm::uvec1(3));
    indices.push_back(glm::uvec1(2));
    indices.push_back(glm::uvec1(6));
    indices.push_back(glm::uvec1(3));
    indices.push_back(glm::uvec1(6));
    indices.push_back(glm::uvec1(8));
    indices.push_back(glm::uvec1(3));
    indices.push_back(glm::uvec1(8));
    indices.push_back(glm::uvec1(9));
    indices.push_back(glm::uvec1(4));
    indices.push_back(glm::uvec1(9));
    indices.push_back(glm::uvec1(5));
    indices.push_back(glm::uvec1(2));
    indices.push_back(glm::uvec1(4));
    indices.push_back(glm::uvec1(11));
    indices.push_back(glm::uvec1(6));
    indices.push_back(glm::uvec1(2));
    indices.push_back(glm::uvec1(10));
    indices.push_back(glm::uvec1(8));
    indices.push_back(glm::uvec1(6));
    indices.push_back(glm::uvec1(7));
    indices.push_back(glm::uvec1(9));
    indices.push_back(glm::uvec1(8));
    indices.push_back(glm::uvec1(1));

    // refine triangles
    for (int i = 0; i < recursion; i++)
    {
        std::vector<glm::uvec3>			idTab2;

        for (int i = 0; i < indices.size(); i += 3)
        {
            // replace triangle by 4 triangles

            uint32_t a = static_cast<uint32_t>(getMiddlePoint(vertex, middlePoints, indices[i + 0].x, indices[i + 1].x));
            uint32_t b = static_cast<uint32_t>(getMiddlePoint(vertex, middlePoints, indices[i + 1].x, indices[i + 2].x));
            uint32_t c = static_cast<uint32_t>(getMiddlePoint(vertex, middlePoints, indices[i + 2].x, indices[i + 0].x));

            idTab2.push_back(glm::u32vec3(indices[i + 0].x, a, c));
            idTab2.push_back(glm::u32vec3(indices[i + 1].x, b, a));
            idTab2.push_back(glm::u32vec3(indices[i + 2].x, c, b));
            idTab2.push_back(glm::u32vec3(a, b, c));
        }
        indices.resize(idTab2.size() * 3);
        memcpy(indices.data(), idTab2.data(), idTab2.size() * 3 * sizeof(unsigned int));
    }
}
