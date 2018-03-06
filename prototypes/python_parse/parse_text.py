import sys
import logging

ignore_words = []
window_chars = '!?,.:;\'"()[]`{|}'
html_text = ['<br >','<br />','\85']

LOWER_BOUND = 0.10
UPPER_BOUND = 0.95
WINDOW_SIZE = 4

class Window:
    """ Class to make windows of words from text """

    def __init__(self, text):
        self.text         = text.lower()
        self.no_use_words = []
        self.windows      = []
        self.all_words    = {}

        logging.info("Cleaning text")
        self.cleanText()
        logging.info("Making no use words")
        self.makeNoUseWords()
        logging.info("Making windows")
        self.makeWindows()
        logging.info("Splitting windows")
        self.SplitWindows()

    def SplitWindows(self):
        new_windows = []
        for window in self.windows:
            self.SplitWindows_(window, new_windows)
        self.windows = new_windows
        return self.windows


    @staticmethod
    def SplitWindows_(window, new_windows):
        """ Split the windows based on each word. """
        j = 0
        k = 0
        words_window = []
        for i,word in enumerate(window):
            j = i - int(WINDOW_SIZE/2)
            if j < 0:
                j = 0
            k = i + int(WINDOW_SIZE/2)
            if k >= len(window):
                k = len(window) - 1
            temp_window = window[j:k + 1]
            while word in temp_window:
                temp_window.remove(word)
            new_windows.append( (word,temp_window) )
        return new_windows


    def makeWindows(self):
        """ parse the words in the text, then splits words into lists based on the 
        window_chars locations """
        text = self.text.split('|')
        for raw_window in text:
            temp_window = []
            for word in raw_window.split(' '):
                if len(word) > 2 and word not in self.no_use_words:
                    temp_window.append(word)
            if len(temp_window) > 1:
                self.windows.append(temp_window)
        return self.windows


    def cleanText(self):
        for obj in html_text:
            self.text = self.text.replace(obj,' ')
        for char in window_chars:
            self.text = self.text.replace(char,'|')
        sentences = self.text.split('|')
        words = []
        for sentence in sentences:
            for word in sentence.split(' '):
                self.wordCount(word)
        return
            

    def wordCount(self, word):
        """ Updates the dictionary of all words for the class """
        if word not in self.all_words.keys():
            self.all_words.update({word:1})
        else:
            self.all_words[word] += 1
        return len(self.all_words)


    def makeNoUseWords(self):
        """ Sort the dictionary of all words for the class """
        sorted_words = []
        for key in sorted(self.all_words, key=self.all_words.get):
            sorted_words.append(key)
        sorted_words

        lower_bound = int(LOWER_BOUND * len(sorted_words))
        upper_bound = int(UPPER_BOUND * len(sorted_words))

        self.no_use_words += sorted_words[:lower_bound]
        self.no_use_words += sorted_words[upper_bound:]
        return len(self.all_words)


def main():
    if len(sys.argv) < 2:
        print("Usage: ./[exec] [file to parse]")
        sys.exit()
    text = ''
    for i in range(1,len(sys.argv)):
        text += open(sys.argv[i],'r').read()
    window_text = Window(text)
    print(window_text.no_use_words)
    for window in window_text.windows:
        print(window)

if __name__ == "__main__":
    main()
