
#include <iostream>
#include"BaseExercise.h"
#include "exercise_02.h"
#include "exercise_01.h"

/*Ï°Ìâ²âÊÔ*/

int main() {
	
	BaseExercise* ex = new exercise_01();
	//BaseExercise * ex = new exercise_02();

	if (ex->Init()) {
		ex->run();
	}
	return 0;
}