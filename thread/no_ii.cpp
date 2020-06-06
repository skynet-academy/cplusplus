#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <algorithm>
#include <mutex>


using namespace std;

const auto nelem = 16;
const auto maxrand = 100;

using vectype = double;
using vec_t = vector<vectype>;

#define _DEBUG
#ifdef _DEBUG
mutex mutex;
#endif // _DEBUG

static auto rand_gen()
{
    static random_device rnd_device;
    static mt19937 mersenne_twister_engine{rnd_device()};
    static uniform_int_distribution<int> dist{1, maxrand};
    return dist(mersenne_twister_engine);
}

static void print_vec(vec_t & vec)
{
    for (auto elem: vec)
        cout<<elem<<" ";
    cout<<endl;
}

static void genrandvec(vec_t &vec)
{
    generate(begin(vec), end(vec), rand_gen);
}

static void mult_k_chunk(int thr_id, int nthreads, vec_t &vec, vectype k)
{
    const auto chunk_size = vec.size() / nthreads;
    const auto chunk_low = chunk_size * thr_id;
    const auto chunk_high = chunk_size * (thr_id + 1);

#ifdef _DEBUG
    unique_lock<mutex> lock(mutex);
    cout<<"I am thread "<<thr_id<<endl;
    lock.unlock();
#endif
    auto vec_data = vec.data();

    for (auto i = chunk_low; i<chunk_high; i++)
        vec_data[i] *= k;
}

static void parallel_mult_k(vec_t &vec, int max_threads, vectype k)
{
    vector<thread> threads;
    for (auto thr_id = 0; thr_id < max_threads; thr_id++)
        threads.emplace_back(thread(mult_k_chunk, thr_id, max_threads, ref(vec), k));
    for (auto &thr: threads)
        thr.join();
}

int main()
{
    vec_t vec(nelem);
    genrandvec(vec);
    print_vec(vec);
    const auto max_threads = thread::hardware_concurrency();
    cout<<"max_thr: "<<max_threads<<endl;
    const auto k = 10;
    parallel_mult_k(vec, max_threads, k);
    print_vec(vec);
    return 0;
}
