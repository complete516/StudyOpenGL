
#include <iostream>
#include"BaseExercise.h"
#include "exercise_02.h"
#include "exercise_01.h"

/*ϰ�����*/

int main() {
	
	BaseExercise* ex = new exercise_01();
	//BaseExercise * ex = new exercise_02();

	if (ex->Init()) {
		ex->run();
	}
	return 0;
}