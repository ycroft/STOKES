#include"testsuite.h"
#include<UI/plot.h>
#include<UI/application.h>

#define TEST_INTERVAL 50

void __sleep()
{
    boost::this_thread::sleep(boost::posix_time::millisec(TEST_INTERVAL));
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Application mw;
    
    return app.exec();
}