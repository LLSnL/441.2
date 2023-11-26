#include "Edge.h"

Edge::Edge() : size(NULL) {};

Edge::Edge(size_t size) : size(size) {};

void Edge::setInfo(size_t newSize) {
	this->size = newSize;
}

size_t Edge::getInfo() {
	return this->size;
}
