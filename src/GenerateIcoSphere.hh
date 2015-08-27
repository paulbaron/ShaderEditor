#ifndef GENERATEICOSPHERE_H
#define GENERATEICOSPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

void generateIcoSphere(std::size_t recursion, std::vector<glm::vec3> &vertex, std::vector<glm::uvec1> &indices);

#endif // GENERATEICOSPHERE_H
