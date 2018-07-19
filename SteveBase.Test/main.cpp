#include <bandit/bandit.h>

int main(int argc, char* argv[]) {
	auto ret = bandit::run(argc, argv);
	system("pause");
	return ret;
}