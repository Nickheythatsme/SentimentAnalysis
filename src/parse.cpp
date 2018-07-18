#include "parse.h"

// Assign the default delimiters
s_vector parse::default_delims = {"?"," ",".",",","\"","'","<br>","</br>","< /br>","< br>"};

// CONSTRUCTOR
parse::parse() :
	s_vector(),
    delims(parse::default_delims)
{
}

// CONSTRUCTOR with arguments 
parse::parse(s_vector _delims) :
	s_vector(),
    delims(std::move(_delims))
{
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj) :
    s_vector(obj),
    delims(obj.delims)
{
}

// Move constructor
parse::parse(parse && rhs) :
    s_vector(std::move(rhs)),
    delims(std::move(rhs.delims))
{
}


/*
 * Parenthesis operator.
 * Parses the string inside the parenthesis and adds the parsed words to this
 * object (in it's vector)
 */
std::string parse::operator()(const std::string &str)
{
    return _parse(str.c_str());
}

/*
 * Assignment operator
 */
parse& parse::operator=(const parse &obj)
{
    s_vector::operator=(obj);
    delims = obj.delims;
	return *this;
}

/*
 * Assignment move operator
 */
parse& parse::operator=(parse &&rhs)
{
    s_vector::operator=(std::move(rhs));
    delims = std::move(rhs.delims);
    return *this;
}

// Parse the UTF8 string and split it based on the delimiters
std::string parse::_parse(const char *str)
{

    // TODO make global config file for thread count and other data
    //auto thread_count = std::thread::hardware_concurrency() * 2;
    auto thread_count = 1;
    std::thread identify_threads[thread_count];

    // Clear the sections that will be trimmed
    to_trim_mut.lock();
    to_trim.clear();
    to_trim_mut.unlock();

    auto delim_current = delims.begin();
    while(delim_current != delims.end())
    {
        // Launch all threads available
        for (size_t i=0; i<thread_count && delim_current != delims.end(); ++i)
        {
            // Launch a thread to identify all locations of the current delimiter in the string
            identify_threads[i] = std::thread(&parse::identify, 
                    this,
                    (const char*)str,
                    delim_current->c_str(), 
                    strnlen(delim_current->c_str(), STRING_MAX),
                    0);

            ++delim_current; // increment to next deimiter
        }
        for (auto & to_launch : identify_threads)
        {
            // Join the threads again but check to make sure they can be joined
            if (to_launch.joinable())
            {
                to_launch.join();
            }
        }
    }
    return make_string(str);
}

size_t parse::identify(const char *str, const char *delim, size_t delim_len, size_t i)
{

    while (*str)
    {
        // Only string compare if the first bytes are the same 
        if (*str == *delim)
        {
            // If they match then add them to the vector
            if (!strncmp(str, delim, delim_len))
            {
                delim_location loc;
                loc.start = i;
                loc.end = i+delim_len;
                insert_sorted(std::move(loc));
                return identify(++str, delim, delim_len, ++i) + delim_len;
            }
        }
        ++str;
        ++i;
    }
    return 0;
}

// Insert a new delimiter location into the vecotor in sorted order
void parse::insert_sorted(delim_location &&to_insert)
{
    std::lock_guard<std::mutex> guard(to_trim_mut);
    if (to_trim.empty())
    {
        to_trim.emplace_back(std::move(to_insert));
        return;
    }

    auto current = to_trim.begin();
    while (current != to_trim.end() && current->start < to_insert.start)
    {
        ++current;
    }
    to_trim.insert(current, std::move(to_insert));
}

// Copy all of the non marked spots of the string into the new string dest
std::string parse::make_string(const char *str)
{
    std::string dest;
    std::lock_guard<std::mutex> guard(to_trim_mut);
    auto to_trim_current = to_trim.begin();

    size_t i=0;
    while (to_trim_current != to_trim.end())
    {
        while (i < to_trim_current->start)
        {
            dest += str[i];
            ++i;
        }
        while (i >= to_trim_current->start && i < to_trim_current->end)
        {
            ++i;
        }
        ++to_trim_current;
    }
    while(str[i])
    {
        dest += str[i];
        ++i;
    }
    return dest;
}
