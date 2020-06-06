#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

class thread_raii{
public:
    thread_raii(std::thread&& _t): t{std::move(_t)}{ }
    thread_raii(thread_raii &&thr_raii): t{std::move(thr_raii.t)} { }
    ~thread_raii() {
        if (t.joinable()) {
            t.join();
        }
    }

    std::thread& get() { return t; }

private:
    std::thread t;
};

static void FirstMatrix(std::vector<std::vector<int>> &Mymatrix, int MaxT){
    for(int i = 0; i < MaxT; i++ )
        for(int j = 0; j < MaxT ; j++){
            if(i == j){
                Mymatrix[i][j] = 0;
            }else
                Mymatrix[i][j] = (rand()%9 + 1);
        }
    std::cout<< "\nYour first matrix :\n";
    for(auto& elem: Mymatrix){
    
       for(auto& elem2: elem)
           std::cout<<elem2<<" ";
       std::cout<<std::endl;
    }
}
static void FloydAlgorithm(std::vector<std::vector<int>> &Mymatrix, int MaxT){
    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::ofstream speedupfile{"speedupFloyd"};
    if(!speedupfile.is_open())
    
        std::cerr<< "Can't open file" << std::endl;
    for (int k = 0; k < MaxT; k++) 
    {
        get_time = std::chrono::steady_clock::now;

        start = get_time();
        //thread_init
        for (int i = 0; i < MaxT; i++)
        {
            for (int j = 0; j < MaxT; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (Mymatrix[i][k] + Mymatrix[k][j] < Mymatrix[i][j]) 
                    Mymatrix[i][j] = Mymatrix[i][k] + Mymatrix[k][j]; 
            } 
        }
        end = get_time();
        elapsed = std::chrono::duration_cast
            <std::chrono::milliseconds>(end - start).count();
        auto par_time = double(elapsed);

        std::cout<< "elapsed time: "<< par_time<<"\n Graph N.: "<<k <<std::endl;
        for(auto& elem: Mymatrix){
           for(auto& elem2: elem)
               std::cout<<elem2<<" ";
        std::cout<<std::endl;
        speedupfile<< k  <<"\t"<< elapsed <<"\t"<<std::endl;
        }

    } 
    speedupfile.close();
} 

static void PrintVector(std::vector<std::vector<int>> &Mymatrix)
{
    std::cout<< "Last matrix :\n";
    for(auto& elem: Mymatrix){
       for(auto& elem2: elem)
           std::cout<<elem2<<" ";
       std::cout<<std::endl;
    }

}
int main()
{
    int MaxT = std::thread::hardware_concurrency();
    std::vector<std::vector<int>> Mymatrix(MaxT, std::vector<int>(MaxT));
    FirstMatrix(Mymatrix,  MaxT);
    FloydAlgorithm( Mymatrix,  MaxT);
    PrintVector(Mymatrix);

    return 0;
}
