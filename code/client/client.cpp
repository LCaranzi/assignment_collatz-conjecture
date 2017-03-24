#include <cstdio>
#include <yarp/os/all.h>

using namespace std;
using namespace yarp::os;

int main()
{   
    int id;
    int n = 0, N,T;

    Network yarp;
    
    Port p;
    p.open("/client");
    printf("Inserire ID Cliente: ");
    scanf("%d",&id);
    printf("\nID Cliente: %d\n",id);

    Bottle req,rep;
    req.addInt(id);
    req.addInt(n);

    printf("Request: %s \n",req.toString().c_str());
    
    while(true)
    {   p.write(req,rep);
    
        printf("Reply: %s\n",rep.toString().c_str());
        
        N = rep.get(1).asInt();
        T = rep.get(2).asInt();
    
        n = N;
        while(n>T)
        {   
            if(n%2==0)
                n = n/2;
            else
                n = 3*n + 1;
        }
        req.addInt(id);
        req.addInt(N);
    }

    p.close();
    return 0;
     
}
