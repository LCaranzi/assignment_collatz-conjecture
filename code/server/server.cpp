#include <cstdio>
#include <yarp/os/all.h>
#include <deque>

using namespace std;
using namespace yarp::os;

int main()
{   
    Network yarp;
    
    
    deque<int> fifo;
    deque<int>::iterator it;
    
    Bottle cmd,rep;

    int n,t,cnt,code;
    cnt = 1;
    t = 1;

    Port p;
    p.open("/server");

    while(true)
    {   //printf("N: %d, T: %d \n",cnt,t);
        Bottle cmd;
        
        p.read(cmd,true);

        printf("Received: %s \n",cmd.toString().c_str());
        
        cnt++;        
        fifo.push_back(cnt);        
        
        //printf("Request: %s \n",cmd.toString().c_str());
        
        t = *(fifo.end()-1)-1;
                
        code = cmd.get(0).asInt();
   
        Bottle rep;     
        rep.addInt(code);
        rep.addInt(cnt);
        rep.addInt(t);

        p.reply(rep);
        printf("Reply:    %s\n\n",rep.toString().c_str());

        it = fifo.begin();
        while (it != fifo.end())                        //cancella elemento verificato
        {   if(*it == cmd.get(1).asInt())
               fifo.erase(it);
            it++;
        }
            
                      
        printf("Fifo: ");                             //stampa Fifo
        for (it = fifo.begin(); it!=fifo.end(); ++it)
            printf("%d ",*it);
        printf("\n\n");        
       
    }
    
    p.close();
    return 0;
}
