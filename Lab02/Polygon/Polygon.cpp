#include "Polygon.h"

#include <assert.h>

Polygon::Polygon() noexcept : fNumberOfVertices() {};

size_t Polygon::getNumberOfVertices() const noexcept {
	return fNumberOfVertices;
}

void Polygon::readData(std::istream& aIStream) {
	while (aIStream >> fVertices[fNumberOfVertices]) {
		fNumberOfVertices++;
	}
}

const Vector2D& Polygon::getVertex(size_t aIndex) const {
	assert(aIndex < fNumberOfVertices);
	return fVertices[aIndex];
}

float Polygon::getPerimeter() const noexcept {
	float result = 0.0f;

	if (fNumberOfVertices > 2) {
		for (int i = 0; i < fNumberOfVertices-1; i++) {
				result += (fVertices[i+1] - fVertices[i]).length();
		}
	
		result += (fVertices[0] - fVertices[fNumberOfVertices-1]).length();
	}

	return result;
}
	

Polygon Polygon::scale(float aScalar) const noexcept {
	Polygon Result = *this;

	for (int i = 0; i < fNumberOfVertices; i++) {
		Result.fVertices[i] = fVertices[i] * aScalar;
	}

	return Result;
}

