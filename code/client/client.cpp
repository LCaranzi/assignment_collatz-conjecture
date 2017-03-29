#include <cstdio>
#include <yarp/os/all.h>
#include <sstream>

using namespace std;
using namespace yarp::os;

int main()
{   
    

    int id;
    int n = 0, N,T;
    
    std::ostringstream portName;
    
    Network yarp;
    
    printf("Inserire ID Cliente: ");
    scanf("%d",&id);
    printf("\nID Cliente: %d\n",id);
    portName<<"/client_"<<id;
    
    printf("\n client ID: %s",portName.str().c_str());

    Port p;
    p.open(portName.str().c_str());

    while(true)
    {   
        Bottle req,rep;
        req.addInt(id);
        req.addInt(n);  
          
        p.write(req,rep);
        printf("Request:  %s\n",req.toString().c_str());
        printf("Received: %s\n\n",rep.toString().c_str());
        
        N = rep.get(1).asInt();
        T = rep.get(2).asInt();
    
        n = N;
        while(n>T)
        {   if(n%2==0)
                n = n/2;
            else
                n = 3*n + 1;
        }
        n = N;
        
       Time::delay(3);
    }

    p.close();
    return 0;
     
}
