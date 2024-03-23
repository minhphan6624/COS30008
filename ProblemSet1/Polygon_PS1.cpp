#include "Polygon.h"

float Polygon::getSignedArea() const noexcept {
	float lResult = 0.0f;

	lResult += (fVertices[fNumberOfVertices - 1] - fVertices[0]).x() * (fVertices[fNumberOfVertices - 1] + fVertices[0]).y();

	for (int i = 0; i < fNumberOfVertices - 1; i++) {
		lResult += (fVertices[i] - fVertices[i+1]).x() * (fVertices[i] + fVertices[i+1]).y();
	}

	return lResult * 0.5;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
	Polygon lResult = *this;

	for (int i = 0; i < fNumberOfVertices; i++) {
		Vector3D lTempVec = Vector3D(aMatrix * fVertices[i]);

		lResult.fVertices[i] = static_cast<Vector2D>(lTempVec);
	}

	return lResult;
}