#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <pthread.h>

pthread_barrier_t barrier;
const auto nruns = 10;
const auto noper = 100;

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

static void FirstMatrix(std::vector<std::vector<int>> &Mymatrix, int vec_mul){
    for(int i = 0; i < vec_mul; i++ )
        for(int j = 0; j < vec_mul ; j++){
            if(i == j){
                Mymatrix[i][j] = 0;
            }else
                Mymatrix[i][j] = (rand()%9 + 1);
        }
#ifdef _DEBUG 
    std::cout<< "\nYour first matrix :\n";
    for(auto& elem: Mymatrix){
    
       for(auto& elem2: elem)
           std::cout<<elem2<<" ";
       std::cout<<std::endl;
    }
#endif 
}

static void mult_k_chunk(int thr_id, int nthreads, std::vector<std::vector<int>> &Mymatrix)
{
    const auto chunk_size = Mymatrix.size() / nthreads;
    const auto chunk_low = chunk_size * thr_id;
    const auto chunk_high = chunk_size * (thr_id + 1);
    for(auto k = chunk_low; k < chunk_high ;k++)
    {
        pthread_barrier_init(&barrier, NULL, nthreads);
        for (auto i = 0u; i < Mymatrix.size() ; i++)
        {
            for(auto j = 0u; j < Mymatrix.size(); j++)
            {
                if(Mymatrix[i][k] + Mymatrix[k][j] < Mymatrix[i][j])
                    Mymatrix[i][j] = Mymatrix[i][k] + Mymatrix[k][j];
            }
        }
        pthread_barrier_destroy(&barrier);
    }
}

static void parallel_mult_k(std::vector<std::vector<int>> &Mymatrix, int max_threads)
{
    std::vector<thread_raii> threads;
    for (auto thr_id = 0; thr_id < max_threads; thr_id++)
        threads.emplace_back(thread_raii{
                std::thread{mult_k_chunk,thr_id, max_threads , std::ref(Mymatrix)}});
}
#ifdef _DEBUG 
static void PrintVector(std::vector<std::vector<int>> &Mymatrix)
{
    std::cout<< "Last matrix :\n";
    for(auto& elem: Mymatrix){
       for(auto& elem2: elem)
           std::cout<<elem2<<" ";
       std::cout<<std::endl;
    }
}
#endif 

int main()
{
    int MaxT = std::thread::hardware_concurrency();
    int vec_mul = MaxT * noper; 
    std::vector<std::vector<int>> Mymatrix(vec_mul, std::vector<int>(vec_mul));
    FirstMatrix(Mymatrix, vec_mul);
    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;

    start = get_time();

    for (auto i = 0; i < nruns; i++) {
        mult_k_chunk( 0 , 1 , Mymatrix);
    }

    end = get_time();

    auto elapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(end - start).count();
    auto ser_time = double(elapsed) / nruns;

    std::cout << "Serial time: " << ser_time << std::endl;

    // Parallel
    
    std::ofstream speedupfile{"speedupFloyd"};
    if (!speedupfile.is_open()) {
        std::cerr << "can't open file" << std::endl;
        return 1;
    }

    for (auto nthr = 2; nthr <=MaxT ; nthr++) {
        start = get_time();

        for (auto i = 0; i < nruns; i++) {
            parallel_mult_k(Mymatrix, nthr);
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
#ifdef _DEBUG 
    PrintVector(Mymatrix);
#endif 
    return 0;
}
