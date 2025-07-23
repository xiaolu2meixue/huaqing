#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Stu{
	private:

	public:
        int math;
        int chi;
        int eng;

        Stu() {}

        Stu(int _math, int _chi, int _eng)
        :math(_math), chi(_chi), eng(_eng)
        {

        }
};

int main(int argc,const char** argv)
{
    Stu stu(100, 110, 120);
    cout << stu.math << endl;
    cout << stu.chi << endl;
    cout << stu.eng << endl;

	return 0;
}

