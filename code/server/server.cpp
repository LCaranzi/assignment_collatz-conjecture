#include <cstdio>
#include <yarp/os/all.h>
#include <deque>

using namespace std;
using namespace yarp::os;

int main()
{   
    std::deque<int> fifo;
    std::deque<int>::iterator it;    

    Network yarp;

    Bottle cmd,rep;

    int n,t,cnt = 1, code;
    
    Port p;
    p.open("/server");

    while(true)
    {   Bottle cmd;
        p.read(cmd,true);
     
        
        cnt++;        
        fifo.push_back(cnt);        
        //printf("Request: %s \n",cmd.toString().c_str());
        
        t = *fifo.begin()-1;
        //printf("Begin: %d",n);
        
        code = cmd.get(0).asInt();
   
        Bottle rep;     
        rep.addInt(code);
        rep.addInt(cnt);
        rep.addInt(t);

        p.reply(rep);
        //printf("Reply: %s\n",rep.toString().c_str());

        it = fifo.begin();
        
        while (it != fifo.end())
        {   if(*it == cmd.get(1).asInt())
                fifo.erase (it);
            it++;
        }
        
    }

    p.close();
    return 0;
}
