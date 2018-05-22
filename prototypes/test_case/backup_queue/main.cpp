#include "queue.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/time.h>

using namespace std;

// Declare the type of arguments to be used
struct f_array
{
    f_array()
    {
        a = nullptr;
        len = 0;
    }
    f_array(uint _len)
    {
        len = _len;
        a = new float[len];
    }
    ~f_array() 
    {
        if(a) delete [] a;
    }
    float *a;
    uint len;
};

// Declare the type of function to be called
typedef void func(f_array *);

void test_func(f_array *s)
{
    for(uint j = 0; j < s->len; ++j)
        for(uint i = 0; i < s->len; ++i)
            s->a[i] *= 1000;
}


f_array* make_array(uint len)
{
    srand(clock());
    auto n = new f_array(len);

    for(uint i = 0; i < n->len; ++i)
    {
        n->a[i] = rand() % 1000;
    }
    return n;
}

std::vector<f_array*> make_arrays(uint len, uint count)
{
    std::vector<f_array*> ret;
    for(uint i = 0; i < count; ++i)
    {
        ret.emplace_back(make_array(len));
    }
    return ret;
}

void run_test(uint cores, uint len, uint iterations)
{
    printf("Running test with %u cores, %u length, %u iterations\n",
            cores,
            len,
            iterations);
    auto v = make_arrays(len, iterations);
    queue<func,f_array*> q(test_func, v, cores);

    struct timeval ts,tf;
    uint timems;

    gettimeofday(&ts, NULL);
    try{
        auto ret = q.start();
        for(auto &a : ret)
            delete a;
    }
    catch(queue_error e)
    {
        cout << e << endl;
    }
    gettimeofday(&tf, NULL);

    timems=(tf.tv_sec * 1000 + tf.tv_usec / 1000) - 
            (ts.tv_sec * 1000 + tf.tv_usec / 1000);
    /*
    printf("Cores: %u\nIterations: %u\nLength: %u\nTime (ms): %u\n",
            cores,
            iterations,
            len,
            timems);
    */
    printf("\n");
}

int main(int argc, char **argv)
{
    uint len = 503;
    uint iterations = 1003;
    for(uint i = 1; i < 10; ++i)
        run_test(i, len, iterations);
    return 0;
}
