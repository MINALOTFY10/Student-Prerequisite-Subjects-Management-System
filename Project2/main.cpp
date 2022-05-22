#include"Start.h"
using namespace std;

int main() {
	sqlite sq;
	sq.createDB(sq.address);
	sq.CreateAll(sq.address);

	Start s1;
	s1.start_program();

}