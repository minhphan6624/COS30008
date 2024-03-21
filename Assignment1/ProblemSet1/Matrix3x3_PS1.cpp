#include "Matrix3x3.h"

#include <math.h>
#include <assert.h>
#include <sstream>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
	Vector3D resRow1(
		row(0).dot(aOther.column(0)),
		row(0).dot(aOther.column(1)),
		row(0).dot(aOther.column(2))
		);

	Vector3D resRow2(
		(row(1).dot(aOther.column(0))),
		(row(1).dot(aOther.column(1))),
		(row(1).dot(aOther.column(2)))
		);

	Vector3D resRow3(
		row(2).dot(aOther.column(0)),
		row(2).dot(aOther.column(1)),
		row(2).dot(aOther.column(2))
		);

	return Matrix3x3(resRow1, resRow2, resRow3);
}

float Matrix3x3::det() const noexcept {
	float res = 0.0f;

	res += row(0)[0] * (row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1]);

	res -= row(0)[1] * (row(1)[0] * row(2)[2] - row(1)[2] * row(2)[0]);

	res += row(0)[2] * (row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0]);

	return res;
}

Matrix3x3 Matrix3x3::transpose() const noexcept {
	return Matrix3x3(column(0), column(1), column(2));
}

bool Matrix3x3::hasInverse() const noexcept {
	return (det() != 0) ? true : false;
}

Matrix3x3 Matrix3x3::inverse() const noexcept {
	assert(det() != 0);
	//First row of the result matrix
	Vector3D resRow1(
		row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1],
		row(0)[2] * row(2)[1] - row(0)[1] * row(2)[2],
		row(0)[1] * row(1)[2] - row(0)[2] * row(1)[1]
		);

	//Second row of the result matrix
	Vector3D resRow2(										
		row(1)[2] * row(2)[0] - row(1)[0] * row(2)[2],
		row(0)[0] * row(2)[2] - row(0)[2] * row(2)[0],
		row(0)[2] * row(1)[0] - row(0)[0] * row(1)[2]
		);
	//Third row of the result matrix
	Vector3D resRow3(
		row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0],
		row(0)[1] * row(2)[0] - row(0)[0] * row(2)[1],
		row(0)[0] * row(1)[1] - row(0)[1] * row(1)[0]
		);

	
	return Matrix3x3(resRow1, resRow2, resRow3) * (1/(det()));
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix) {
	return aOStream << "[" << aMatrix.row(0).toString()
		<< "," << aMatrix.row(1).toString()
		<< "," << aMatrix.row(2).toString() << "]";
}
