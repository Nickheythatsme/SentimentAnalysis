import sys
import networkx as nx
from parse_text import Window
import math
import logging

G = nx.Graph()

def Sigmoid(x):
    return 1/(1+math.e**-(x))

def MakeGraph(window, G):
    G.add_node(window[0])
    for word in window[1]:
        w = 1
        if word in G[window[0]]:
            w = G[window[0]][word]['weight']+1
        G.add_edge(window[0], word, weight=w)
    return G;

def WriteGraph(G,filename):
    fout = open(filename,'w')
    for node in G.nodes():
        fout.write(node + ',')
    fout.write('\n')
    for i,node in enumerate(G.nodes()):
        if i % 100 == 0:
            logging.debug("writing files {}%".format(i/len(G.nodes)))
        fout.write("{}:".format(node))
        for edge in G.nodes():
            num_to_write = 0.0
            if edge in G[node]:
                num_to_write = Sigmoid(G[node][edge]['weight'])
            fout.write(str(num_to_write) + ',')
        fout.write('\n')
    return


def main():
    logging.basicConfig(level=logging.DEBUG)
    if len(sys.argv) < 2:
        print("Usage: ./[exec] [file to parse]")
        sys.exit()
    text = ''
    for i in range(1,len(sys.argv)):
        text += open(sys.argv[i],'r').read()
    window_text = Window(text)

    for window in window_text.windows:
        MakeGraph(window,G)
    WriteGraph(G,'vectorized_words.csv')


main()
