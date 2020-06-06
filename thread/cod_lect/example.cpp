#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
const auto nelem = 64000000;
const auto maxrand = 100;
const auto nruns = 10;

//#define _DEBUG


std::mutex mutex;

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


static void FloydAlgorithm(std::vector<std::vector<int>> &Mymatrix, int MaxT);
static void FloydAlgorithm(std::vector<std::vector<int>> &Mymatrix, int MaxT){
    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    auto ser_time = double(elapsed) /nruns;
    
    std::ofstream speedupfile{"speedupFloyd"};
    if(!speedupfile.is_open())
    {
        std::cerr<< "Can't open file" << std::endl;
    }
    for (int k = 0; k < MaxT; k++) 
    {
        get_time = std::chrono::steady_clock::now;
        std::unique_lock<std::mutex> lock(mutex);

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
        lock.unlock();
        end = get_time();
        elapsed = std::chrono::duration_cast
            <std::chrono::milliseconds>(end - start).count();
        auto par_time = double(elapsed) / nruns;

        std::cout<< "elapsed time: "<< par_time<<"\nGraph N."<<k <<std::endl;
        speedupfile<< k + 1 <<"\t"<<ser_time/par_time<<"\t"<<par_time<<std::endl;
    } 
    speedupfile.close();

} 



static void parallel_mult_k( std::vector<std::vector<int>> &Mymatrix, int max_threads, double k);

static void parallel_mult_k( std::vector<std::vector<int>> &Mymatrix, int max_threads, double k)
{
    std::vector<thread_raii> threads;
    for (auto thr_id = 0; thr_id < max_threads; thr_id++)
        threads.emplace_back(thread_raii{std::thread{
               FloydAlgorithm , thr_id, max_threads, std::ref(Mymatrix), k}});

}

int main(){
    int MaxT = std::thread::hardware_concurrency();
    std::vector<std::vector<int>> Mymatrix(MaxT, std::vector<int>(MaxT));
    for(int i = 0; i < MaxT; i++ ){
        for(int j = 0; j < MaxT ; j++){
            if(i == j)
                Mymatrix[i][j] = 0;
            else
                Mymatrix[i][j] = (rand()%9 + 1);
        }
    }
     std::cout<< "Your first matrix :\n";
    for(auto& elem: Mymatrix){
       for(auto& elem2: elem)
           std::cout<<"| "<<elem2<<" |";
       std::cout<<std::endl;
    }

    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;

    end = get_time();

    auto elapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(end - start).count();
    auto ser_time = double(elapsed) / nruns;

    std::cout << "Serial time: " << ser_time << std::endl;
    std::ofstream speedupfile{"speedup"};
    if (!speedupfile.is_open()) {
        std::cerr << "can't open file" << std::endl;
        return 1;
    }

    for (auto nthr = 2; nthr <=MaxT ; nthr++) {
        start = get_time();

        for (auto i = 0; i < nruns; i++) {
            auto k = (rand()%10);
            parallel_mult_k(Mymatrix, nthr, k);
        }

        end = get_time();

        elapsed = std::chrono::duration_cast
            <std::chrono::milliseconds>(end - start).count();
        auto par_time = double(elapsed) / nruns;

        std::cout << "Threads: " << nthr << " elapsed time " 
                  << par_time << " speedup " << ser_time / par_time << std::endl;
        speedupfile << nthr << "\t" << ser_time / par_time << std::endl;
    }

    speedupfile.close();
} 
