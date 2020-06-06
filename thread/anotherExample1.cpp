//#include <iostream>
//#include <vector>
//#include <random>
//#include <algorithm>
//#include <thread>
//#include <mutex>
//#include <chrono>
//#include <fstream>
//using vectype = double;
//const auto nlem = 10;
//const auto maxrand = 100;
//using vec_t = std::vector<vectype>;
// static auto rand_gen() 
//{
//    static std::random_device rnd_device;
//    static std::mt19937 mersenne_engine{rnd_device()};
//    static std::uniform_int_distribution<int> dist{1, maxrand};

//    return dist(mersenne_engine);
//}

//static void genrandvec(vec_t &vec)
//{
//    std::generate(begin(vec), end(vec), rand_gen);
//}

//static void printvec(vec_t &vec){
//    for(int i = 0; i < nlem; i++ )
//        for(int j =0; j < nlem; j++){
//            std::cout<<vec[i][j] <<" ";
//        }
//    std::cout<<std::endl;
//}
//int main(){
//    vec_t vec(nlem, std::vector<int>nlem);
//    genrandvec(vec);
//    printvec(vec);
    
//    return 0;
//}


#include <iostream>
#include <vector>
#include <thread>
int main()
{
    int MaxT = std::thread::hardware_concurrency();
    std::vector<std::vector<int>> arr(MaxT, std::vector<int>(MaxT));
    for(int i = 0; i < MaxT; i++ )
        for(int j = 0; j < MaxT ; j++){
            if(i == j){
                arr[i][j] = 0;
                
            }else
                arr[i][j] = (rand()%10 + 1);
        }
    for(auto& elem: arr){
    
       for(auto& elem2: elem)
           std::cout<<elem2<<" ";
       std::cout<<std::endl;
    }
    return 0;
}
