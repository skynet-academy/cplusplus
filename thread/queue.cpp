#include <iostream>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

const auto nruns = 10;
const auto nopers = 100000;

//A class for threads
class thread_raii{
public: 
    thread_raii(std::thread&& _t): t{std::move(_t)}{ }
    thread_raii(thread_raii &&thr_raii): t{std::move(thr_raii.t)}{ }
    //The destructor of threads
    ~thread_raii(){
        if(t.joinable())
            t.join();
    }
    std::thread& get(){return t;}

    void join(){
        if(t.joinable())
            t.join();
    }
private:
    std::thread t;
};
// A class for spinlocks, we can use mutex as well
//
class spinlock {
public: 
    spinlock(){pthread_spin_init(&slock, 0);}
    ~spinlock(){pthread_spin_destroy(&slock);}
    void lock(){pthread_spin_lock(&slock);}
    void unlock(){pthread_spin_unlock(&slock);}
private: 
    pthread_spinlock_t slock;
};

template<typename TItem, typename TLock>
class concurrent_queue {
public: 
   concurrent_queue(unsigned _capacity = concurrent_queue::def_capacity):
       capacity{_capacity}, items{new TItem[_capacity]}{}
   ~concurrent_queue(){delete[] items;}
   TItem dequeue();
   void enqueue(TItem &item);
   unsigned get_capacity(){
       return capacity;
   }
   void print();
private:
   static const unsigned def_capacity = nopers * 10;
   unsigned capacity = def_capacity;
   unsigned head = 0;
   unsigned tail = 0;
   TLock lock;
   TItem * items;
};
// function for dequeue 
template<typename TItem, typename TLock>
TItem concurrent_queue<TItem, TLock>::dequeue(){
    std::unique_lock<TLock> rlock(lock);
    if(head == tail)
        throw std::runtime_error(" queue is empty ");
    auto item = items[head % capacity];
    head++;
    return item;
}
// function for enqueue
template<typename TItem, typename TLock>
void concurrent_queue<TItem, TLock>::enqueue(TItem &item){
    std::unique_lock<TLock> rlock(lock);
    if(tail - head == capacity)
        throw std::runtime_error(" queue is full ");

    items[tail % capacity] = item;
    tail++;
}
//function to printing 
template<typename TItem, typename TLock>
void concurrent_queue<TItem, TLock>::print(){
    for(auto i = 0u; i < capacity; i++)
        std::cout<< items[i] <<" ";
    std::cout << std::endl;
}

static auto rand_gen(){
    static const auto maxrand = 100;
    static std::random_device rnd_device;
    static std::mt19937 mersenne_engine{rnd_device()};
    static std::uniform_int_distribution<int> dist{1,maxrand};

    return dist(mersenne_engine);
}

int main(int argc, const char *argv[]){
    try{
        const auto max_threads = std::thread::hardware_concurrency();
        std::ofstream speedupfile{" throughput: "};
        if(!speedupfile.is_open()){
            std::cerr << "can't open file"<< std::endl;
            return 1;
        }
        for(auto nthr = 2u; nthr <= max_threads; nthr++){
            auto get_time = std::chrono::steady_clock::now;
            decltype(get_time()) start, end;
            start = get_time();
            for(auto i = 0; i < nruns; i++){
                std::vector<thread_raii> threads;
                concurrent_queue<int, spinlock> cqueue;
                for(auto i = 0u; i < cqueue.get_capacity() / 2; i++){
                    auto item = rand_gen();
                    cqueue.enqueue(item);
                }
                auto thread_func = [&cqueue](){
                    for(auto i = 0u; i < nopers; i++){
                        auto oper = rand_gen();
                        if(oper<= 50){
                            auto item = rand_gen();
                            cqueue.enqueue(item);
                        }else{
                            cqueue.dequeue();
                        }
                    }
                };
                for(auto thr_id = 0u; thr_id < nthr ; thr_id++)
                    threads.emplace_back(thread_raii{std::thread{thread_func}});
                for(auto &thr: threads)
                    thr.join();
            }
            end = get_time();
            const auto elapsed = std::chrono::duration_cast
            <std::chrono::milliseconds> (end - start).count();
            const auto par_time = double(elapsed)/ nruns;
            const auto throughput = (nopers * nthr) / par_time * 1000;
            std::cout<< "threads: "<< nthr << " elapsed time "<< par_time<<" ms throughput "
            <<throughput<<std::endl;
            speedupfile <<nthr << "\t"<<throughput << std::endl;
        }
        speedupfile.close();
    }
    catch(std::runtime_error &e){
        std::cerr<< "Caught a runtime_error exception: "<<e.what()<<std::endl;
    }
    return 0;
}









































