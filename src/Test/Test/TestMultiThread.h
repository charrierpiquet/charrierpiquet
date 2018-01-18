#ifndef TEST__TESTMULTITHREAD__H
#define TEST__TESTMULTITHREAD__H
#include <thread>
#include <mutex>
#include "Engine.h"

namespace Test
{
    class TestMultiThread{
    private:
        std::mutex mtx;
        bool run = true, dosmth = false;
        void threadMoteur (std::shared_ptr<Engine::Moteur> moteur);
        
    public :
        void testThread();
        
        
    };
	
};
#endif /* TESTETAT_H */

