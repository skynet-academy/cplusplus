#include<iostream> 
#include<vector> 
#include<random> 
#include<algorithm> 
#include<thread> 
#include<mutex> 
#include<chrono> 
#include<fstream> 
 
#define V 4 
const auto exec = 10;  
#define INF 99999 



std::mutex mutex;


void printSolution(int dist[][MaxThreads]); 

void floydWarshall (int graph[][MaxThreads]); 


int main() 
{
    
    int MaxT = std::thread::hardware_concurrency();
    int graph[MaxT][MaxT]; 
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            graph[i][j] = 1 + (rand()% 20);
            std::cout<<" | "<<graph[i][j]<<" | ";
        }
        std::cout<<std::endl;
    }
    
    std::thread thread(floydWarshall, graph[MaxT][MaxT]); 
    thread.join();
    
    return 0; 
} 


void floydWarshall (int graph[][MaxThreads]) 
{ 
    int dist[V][V], i, j, k; 
    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;
    auto elapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(end - start).count();

    auto ser_time = double(elapsed) / exec;
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            dist[i][j] = graph[i][j]; 
    std::ofstream speedupfile{"speedup"};
    if(!speedupfile.is_open())
    {
        std::cerr<< "Can't open file" << std::endl;
    }
    for (k = 0; k < V; k++) 
    {
        get_time = std::chrono::steady_clock::now;
        std::unique_lock<std::mutex> lock(mutex);

        start = get_time();
        //thread_init
        for (i = 0; i < MaxThreads; i++)
        {
            for (j = 0; j < MaxThreads; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (dist[i][k] + dist[k][j] < dist[i][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j]; 
            } 
        }
        lock.unlock();
        end = get_time();
        elapsed = std::chrono::duration_cast
            <std::chrono::milliseconds>(end - start).count();
        auto par_time = double(elapsed) / exec;

        std::cout<< "elapsed time: "<< par_time<<"\nGraph N."<<k <<std::endl;
        speedupfile<< k + 1 <<"\t"<<ser_time/par_time<<"\t"<<par_time<<std::endl;
        printSolution(dist);
    } 
    speedupfile.close();
    printSolution(dist); 

} 

void printSolution(int dist[][MaxThreads]) 
{ 
    printf ("The shortest distance between two nodes:\n\n      ");
    for(int n = 1 ; n  <= V; n++ )
            std::cout<< "col:"<<n<<"|";
    std::cout<<"\n";
    for (int i = 0; i < MaxThreads; i++) 
    {
        std::cout<<"row:"<<i + 1<<"|";
        for (int j = 0; j < MaxThreads; j++) 
        { 
            if (dist[i][j] == INF) 
                printf("%s", "<INF>|"); 
            else
                printf ("<-%d->|", dist[i][j]); 
        } 
        printf("\n"); 
    } 
}  
 
