template<typename R, typename A>
queue_base<R,A>::queue_base() :
    thread_count(std::thread::hardware_concurrency()),
    jobs(),
    finished()
{
}

template<typename R, typename A>
queue_base<R,A>::queue_base(std::vector<deRef<A>> && _args, size_t _thread_count) :
    thread_count(_thread_count),
    jobs(),
    finished()
{
    for (auto a : _args)
        jobs.enqueue(std::move(a));
}

template<typename R, typename A>
queue_base<R,A>::queue_base(const queue_base<R,A> &rhs)
{

}

template<typename R, typename A>
queue_base<R,A>::queue_base(queue_base<R,A> &&rhs)
{

}

template<typename R, typename A>
queue_base<R,A>::~queue_base()
{

}

template<typename R, typename A>
void queue_base<R,A>::add_job(job<R,A> &&j)
{

}

template<typename R, typename A>
void queue_base<R,A>::add_arg(deRef<A> &&a)
{

}

template<typename R, typename A>
size_t queue_base<R,A>::choose_thread_count(size_t arg_size)
{
    
}
