#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<thread>
#include<mutex>
#include<chrono>
#include<fstream>

#define V 4

#define INF 10000

const auto exec = 10;

std::mutex mutex;


void printSolution(int dist[][V]);

void floydWarshall (int graph[][V]);

void floydWarshall (int graph[][V])
{
    int dist[V][V], i, j, k;
    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;
    auto elapsed =  std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

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
          // to get time
           get_time = std::chrono::steady_clock::now;
           //to lock mutex
           std::unique_lock<std::mutex> lock(mutex);

           start = get_time();

           for (i = 0; i < V; i++){
                for (j = 0; j < V; j++){
                //If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
            }
          //  unlock mutex
            lock.unlock();
            end = get_time();
            // "elapse" difference between "start"  and  "end"
            elapsed = std::chrono::duration_cast <std::chrono::milliseconds>(end - start).count();
            auto par_time = double(elapsed) / exec;

            std::cout<< "elapsed time: "<< par_time<<"\nGraph N."<<k <<std::endl;
           //  "speedupfile" file which stores the results of the execution
            speedupfile<< k + 1 <<"\t"<<ser_time/par_time<<"\t"<<par_time<<std::endl;  //ser_time/par_time I've only "-nan" values
            printSolution(dist);
         }
         speedupfile.close();
         printSolution(dist);

        }

    void printSolution(int dist[][V])
    {
        printf ("The shortest distance between two nodes:\n\n      ");
        for(int n = 1 ; n  <= V; n++ )
                std::cout<< "col:"<<n<<"|";
        std::cout<<"\n";
        for (int i = 0; i < V; i++)
        {
            std::cout<<"row:"<<i + 1<<"|";
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INF)
                    printf("%s", "<INF>|");
                else
                    printf ("<-%d->|", dist[i][j]);
            }
            printf("\n");
        }
    }

    int main()
    {
        int graph[][V] = { {0, 5, 9, 3},
                        {INF , 0, 3, 1},
                        {7, 3, 0, 1},
                        {2 ,INF, 6, 0}
                      };

        std::thread thread(floydWarshall, graph);
        thread.join();

        return 0;
    }
