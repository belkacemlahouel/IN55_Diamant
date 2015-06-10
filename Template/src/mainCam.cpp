#include <iostream>
#include "Vector3.h"
#include "Quaternion.h"
#include "Camera.h"

using namespace std;

void testVector()
{
	Vector3* v1 = new Vector3(2.0f, 0.0f, 0.0f);
	Vector3* v2 = new Vector3(1.0f, 0.0f, 0.0f);
	Vector3* v3 = new Vector3();

	v1->print(); cout << endl;

	for (int i = 0; i < 5; ++i)
	{
		*v3 = Vector3::plus(*v1, *v2);
	}

	v3->print(); cout << endl;

	cout << v1->dot(*v2) << endl;

	((*v2)*10.0f).print(); cout << endl;
}

void testQuaternion()
{
	Quaternion* q1 = new Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	Quaternion* q2 = new Quaternion(2.0f, 2.0f, 0.0f, 0.0f);
	Quaternion* q3 = new Quaternion();

	q1->print(); cout << endl;
	q2->print(); cout << endl;
	cout << q1->dot(*q2) << endl;
	q2->normalize();
	q2->print(); cout << endl;
	cout << Quaternion::angle(*q1, *q2) << endl;
}

void testCamera()
{
	// TODO
}

int main(int argc, char** argv)
{
	// testVector();
	testQuaternion();
	// testCamera();
	return 0;
}