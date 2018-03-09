//
// Created by njgro on 3/9/2018.
//
#include "window.h"
#include "utf8_manip.h"

#ifndef SENTIMENTANALYSIS_WINDOW_DELIMS_H
#define SENTIMENTANALYSIS_WINDOW_DELIMS_H

#define WINDOW_LEN 3

class window_delims : protected window
{
public:
    window_delims();
    explicit window_delims(const char *sentence_delims);
    window_delims(const window_delims &obj);
    window_delims(window_delims &&rhs);
    ~window_delims();
    // For every word that is added, its delimiter must also be added
    // Can be empty string to indicate end of text
    void add_word(const std::string &word, const std::string &delim);
    void set_sentence_delimiters(const char *delims);
    // Split the main window by the sentence delimiters (ignores all others)
    // Return all the windows in a vector of smaller windows
    std::vector<window> sentence_windows() const;
    // Like sentence windows, only the first word of each vector is the target word, surrounded by
    // its other context words, limited by the length of the window
    std::vector<window> full_windows(int len=WINDOW_LEN) const;
protected:
private:
    window delims;
    char *sentence_delims;
    utf8_manip manip;

    window make_window(window &win, int index) const;
};


#endif //SENTIMENTANALYSIS_WINDOW_DELIMS_H
