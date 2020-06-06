#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

const auto nelem = 1200000;
const auto maxrand = 100;
const auto nruns = 10;

using vectype = double;
using vec_t = std::vector<vectype>;

#ifdef _DEBUG
std::mutex mutex;
#endif

class thread_raii {
public:
    thread_raii(std::thread&& _t): t{std::move(_t)}{ }
    thread_raii(thread_raii &&thr_raii): t{std::move(thr_raii.t)}{ }

    ~thread_raii()
    {
        if(t.joinable())
        {
            t.join();
        }
    }
    std::thread& get(){return t;}
private:
    std::thread t;
};

static auto rand_gen()
{
    static std::random_device rnd_device;
    static std::mt19937 mersenne_engine{rnd_device()};
    static std::uniform_int_distribution<int> dist{1,maxrand};
    return dist(mersenne_engine);
}

static void genrandvec(vec_t &vec)
{
    std::generate(begin(vec), end(vec), rand_gen);
}

#ifdef _DEBUG
static void printvec(vec_t &vec)
{
    for(auto elem: vec)
        std::cout<< elem << " ";
    std::cout<< std::endl;
}
#endif
static void mult_k_chunk(int thr_id, int nthreads, vec_t &vec, vectype k)
{
    const auto chunk_size = vec.size() / nthreads;
    const auto chunk_low = chunk_size * thr_id;
    const auto chunk_high = chunk_size * (thr_id + 1);

#ifdef _DEBUG
    std::unique_lock<std::mutex> lock(mutex);
    std::cout<<" i'm a thread "<<thr_id <<std::endl;
    lock.unlock();
#endif
    auto vec_data = vec.data();

    for(auto i = chunk_low; i < chunk_high; i++)
        vec_data[i] *=k;
}

static void parallel_mult_k(vec_t &vec, int max_threads, vectype k)
{
    std::vector<thread_raii>threads;

    for(auto thr_id = 0; thr_id < max_threads; thr_id++)
        threads.emplace_back(thread_raii{std::thread{mult_k_chunk,
        thr_id, max_threads, std::ref(vec), k}});    
}

int main()
{
    vec_t vec(nelem);

    genrandvec(vec);

#ifdef _DEBUG
    printvec(vec);
#endif
    const auto max_threads = std::thread::hardware_concurrency();

    auto get_time = std::chrono::steady_clock::now;
    decltype(get_time()) start, end;

    start = get_time();

    for(auto i = 0; i < nruns; i++)
    {
        auto k = rand_gen();
        mult_k_chunk(0,1,vec,k);
    }

    end = get_time();

    auto elapsed = std::chrono::duration_cast <std::chrono::milliseconds>(end - start).count();
    auto ser_time = double(elapsed) / nruns;
    
    std::cout << "serial time: " << ser_time <<std::endl;

    //Parallel 
    std::ofstream speedupfile{"speedup_example"};

    if(!speedupfile.is_open())
    {
        std::cerr<< "can't open file"<< std::endl;
        return 1;
    }

    for (auto nthr = 2u; nthr <= max_threads; nthr++) 
    {
        start = get_time();
        for(auto i = 0; i < nruns; i++)
        {
            auto k = rand_gen();
            parallel_mult_k(vec, nthr, k);
        }
        end  = get_time();

        elapsed = std::chrono::duration_cast <std::chrono::milliseconds>(end - start).count();
        auto par_time = double(elapsed) / nruns;

        std::cout<< " threads: " << nthr << " elapsed time "
        << par_time <<" speedup "<< ser_time / par_time << std::endl;
        speedupfile << nthr << "\t" << ser_time / par_time <<std::endl;
    } 

    speedupfile.close();

#ifdef _DEBUG
    printvec(vec);
#endif 

    return 0;

}



