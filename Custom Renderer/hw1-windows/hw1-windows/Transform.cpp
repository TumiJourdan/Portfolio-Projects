// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>
using namespace std;


//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	// brute force
	/*
	float xSquared = pow(axis.x, 2);
	float ySquared = pow(axis.y, 2);
	float zSquared = pow(axis.z, 2);
	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;
	glm::outer
	glm::mat3 myIdentityMatrix = glm::mat3(1.0f);	
	glm::mat3 myCustomMatrix1 = glm::mat3(xSquared,xy,xz,xy,ySquared,yz,xz,yz,zSquared);// am sick and tired of this. I dont know how to express 3x1*1x3
	*/
	// Comsci masters student showed me the ways of outer product <3

	glm::mat3 myIdentityMatrix = glm::mat3(1.0f);
	glm::mat3 myCustomMatrix1 = glm::outerProduct(axis, axis);

	glm::mat3 myCustomMatrix2 = glm::mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);
	
	glm::mat3 outPutMatrix = cos(degrees * pi / 180)*myIdentityMatrix + (1 - cos(degrees * pi / 180))*myCustomMatrix1 + sin(degrees*pi/180)*myCustomMatrix2;


  // You will change this return call
  return outPutMatrix;
}
//checking code
void displayVector3(glm::vec3 vector3)
{
	cout << "Vector3 = ";
	for (int i = 0; i < 3; i++)
	{
		cout << vector3[i];
	}
	cout << endl;
}

void displayVector4(glm::vec4 vector4)
{
	cout << "Vector4 = ";
	for (int i = 0; i < 4; i++)
	{
		cout << vector4[i];
		cout << " ";
	}
	cout << endl;
}

void displayMatrix3(mat3 matrix3)
{
	cout << "Mat3 = " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix3[j][i];//column row
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

}

void displayMatrix4(mat4 matrix4)
{
	cout << "Mat4 = " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << matrix4[j][i];//column row
		}
		cout << endl;
	}
	cout << endl;
}
//end of checking code
// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	mat3 matrix3;
	matrix3 = rotate(degrees, up);
	cout << "Rotated matrix)" << endl;
	displayMatrix3(matrix3);

	//quick and dir'y
	float radians = degrees * pi / 180;
	vec3 v = eye;
	vec3 k = up;

	v = v * glm::cos(radians) + (glm::cross(k, v)) * glm::sin(radians) + k * (glm::dot(k, v)) * (1 - glm::cos(radians));

	eye = v;

}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
// we need to rotate along an axis that is 90* to the look and 

	vec3 axisOfRotation = glm::cross(eye, up);
	vec3 v = eye;
	vec3 v2 = up;
	vec3 k = axisOfRotation;
	float radians = degrees * pi / 180;

	v = v * glm::cos(radians) + (glm::cross(k, v)) * glm::sin(radians) + k * (glm::dot(k, v)) * (1 - glm::cos(radians));
	v2 = v2 * glm::cos(radians) + (glm::cross(k, v2)) * glm::sin(radians) + k * (glm::dot(k, v2)) * (1 - glm::cos(radians));
	eye = v;
	up = v2;
}



// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

	vec3 a = eye;
	vec3 b = up;
	vec3 w;
	vec3 u;
	vec3 v;
	cout << "a and b" << endl;
	displayVector3(a);
	displayVector3(b);
	//code helpers
	vec3 crossed;
	//w,u,v co-ord system
	w = glm::normalize(a);	
	u = glm::normalize(glm::cross(b, w));
	v = glm::cross(w, u);
	
	//checking  uvw
	cout << "UVW:" << endl;
	displayVector3(u);
	displayVector3(v);
	displayVector3(w);
	//end of checking

	//we now have ortho normal basis, now we construct rotation matrix
	// this is messy
	/*
	mat4 rotationMatrix = glm::mat4(u.x, u.y, u.z,0, v.x, v.y, v.z, 0,  w.x, w.y, w.z , 0, 0 , 0 , 0 ,1);//This is messy

	rotationMatrix = glm::transpose(rotationMatrix);
	mat4 eyeMatrix = glm::mat4(1, 0, 0, -a.x, 0, 1, 0, a.y, 0, 0, 1, a.z, 0, 0, 0, 1);

	rotationMatrix = rotationMatrix * eyeMatrix;
	*/
	//attempt to clean
	mat3 uvwMatrix;
	uvwMatrix[0] = u;
	uvwMatrix[1] = v;
	uvwMatrix[2] = w;
	uvwMatrix = glm::transpose(uvwMatrix);

	// checking uvw matrix
	cout << "UVW MATRIX:" << endl;
	displayMatrix3(uvwMatrix);
	//end of checking
	
	mat4 rotationMatrix = glm::mat4(uvwMatrix);

	// check rotation matrix
	cout << "Rotation Matrix" << endl;
	displayMatrix4(rotationMatrix);
	//end of checking

	glm::mat4 myIdentityEyeMatrix = glm::mat4(1.0f);
	
	myIdentityEyeMatrix[3] = glm::vec4(-a, 1);

	rotationMatrix = rotationMatrix * myIdentityEyeMatrix;


	cout << "final lookat = " << endl;
	displayMatrix4(rotationMatrix);
	// output matrix to myself


  // You will change this return call
  return rotationMatrix;
}



Transform::Transform()
{

}

Transform::~Transform()
{

}