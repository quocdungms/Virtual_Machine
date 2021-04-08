#include "VM.h"
//#include "VM.cpp"
using namespace std;


//void test(string filename) {
//    VM *vm = new VM();
//    try {
//        vm->run(filename);
//    }
//    catch (exception& e) {
//        cout << e.what();
//    }
//    delete vm;
//}
//
//int main(int argc, char **argv)
//{
//  if (argc < 2)
//    return 1;
//  test(argv[1]);
//  return 0;
//}


int main()
{
    string filename = "intput.txt";
    VM* vm = new VM();
	try
	{
		vm->run(filename);
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	delete vm;
    system("pause");
    return 0;
}