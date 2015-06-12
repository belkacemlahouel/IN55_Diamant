#include <iostream>
#include "Vector3.h"
#include "Quaternion.h"
#include "Camera.h"

using namespace std;

void testVector()
{
	// Vector3* v1 = new Vector3(2.0f, 0.0f, 0.0f);
	// Vector3* v2 = new Vector3(1.0f, 0.0f, 0.0f);
	// Vector3* v3 = new Vector3();

	// v1->print(); cout << endl;

	// for (int i = 0; i < 5; ++i)
	// {
	// 	*v3 = Vector3::plus(*v1, *v2);
	// }

	// v3->print(); cout << endl;

	// cout << v1->dot(*v2) << endl;

	// ((*v2)*10.0f).print(); cout << endl;

	/***/

	cout << "Hello Vector3!" << endl;
	Vector3 v1(2.0f, 10.0f, -2.0f);
	Vector3 v2(3.0f, -5.0f, 30.0f);

	v1.print(); cout << endl;
	v2.print(); cout << endl;

	(Vector3::cross(v1, v2)).print(); cout << endl;

	cout << "Bye Vector3!" << endl;
}

void testQuaternion()
{
	// Quaternion* q1 = new Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	// Quaternion* q2 = new Quaternion(2.0f, 2.0f, -30.0f, 40.0f);
	// Quaternion* q3 = new Quaternion();

	// q1->print(); cout << endl;
	// q2->print(); cout << endl;
	// cout << q1->dot(*q2) << endl;
	// q2->normalize();
	// q2->print(); cout << endl;
	// cout << Quaternion::angle(*q1, *q2) << endl;

	// q2->print2(); cout << endl;

	/***/

	cout << "Hello Quaternion!" << endl;

	Quaternion q1(1.0f, 2.0f, 3.0f, 0.0f);
	Quaternion q2(-8.0f, 9.0f, 10.0f, 5.0f);
	Quaternion q3(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3 p(12.0f, 11.0f, 17.0f);

	q1.print2(); cout << endl;
	q2.print2(); cout << endl;

	q2.normalize();
	q1.normalize();

	q1.print2(); cout << endl;
	q2.print2(); cout << endl;

	(q2.inverseNew()).print2(); cout << "?" << endl;
	(q1*q2).print2(); cout << " < " << endl;
	(q1+q2).print2(); cout << endl;
	(q2.conjugateNew()).print2(); cout << endl;
	(q2.normalized()).print2(); cout << endl;
	
	q2.printRotationMatrix(); cout << endl;

	q3.print2(); cout << endl;
	(Quaternion::image(q3, p)).print(); cout << endl;

	cout << "Bye Quaternion!" << endl;
}

void testCamera()
{
	cout << "Hello World!" << endl;
	
	Camera c;
}

int main(int argc, char** argv)
{
	// testVector();
	// testQuaternion();
	testCamera();
	return 0;
}