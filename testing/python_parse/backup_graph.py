
class vertex:
    pass

class edge:
    """ edges for the graph, which include a frequency and a vertex object """

    def __init__(self,vertex):
        """ Pointer to another vertex """
        self.vertex = vertex
        """ Indicates the frequency between the word that holds this edge and
            the word that this edge points to """
        self.freq = 1 

    def __str__(self):
        return str(self.vertex)

    def compare(self, obj):
        """ A convoluted compare function to help with relational operators """
        if obj.__class__ == edge:
            if self.vertex.word == obj.vertex.word:
                return 0
            elif self.vertex.word < obj.vertex.word:
                return -1
            else: #self.vertex.word > obj.vertex.word:
                return 1
        if obj.__class__ == vertex:
            if self.vertex.word == obj.word:
                return 0
            elif self.vertex.word < obj.word:
                return -1
            else: #self.vertex.word > obj.word:
                return 1
        if obj.__class__ == str:
            if self.vertex.word == obj:
                return 0
            elif self.vertex.word < obj:
                return -1
            else: #self.vertex.word > obj:
                return 1
        return None

    def __eq__(self, obj):
        return self.compare(obj) == 0

    def __ne__(self, obj):
        return self.compare(obj) != 0

    def __lt__(self, obj):
        return self.compare(obj) < 0

    def __le__(self, obj):
        return self.compare(obj) < 0 or self.compare(obj) == 0

    def __gt__(self, obj):
        return self.compare(obj) > 0

    def __ge__(self, obj):
        return self.compare(obj) > 0 or self.compare(obj) == 0


class vertex:
    """ vertex for the graph, which holds one word and links to other words"""

    def __init__(self,word=None):
        self.word = word
        self.freq = 0
        self.edges = []

    def __str__(self):
        return self.word

    def __iter__(self):
        """ Generator for the edges in this vertex """
        for index in range(0,len(self.edges)):
            yield self.edges[index]

    def __len__(self):
        return len(self.edges)

    def __contains__(self, x):
        if x in edges:
            return True
        return False

    def add_edge(self, new_edge):
        """ Add an edge to the list of edges. Sort after adding """
        for i in range(len(self.edges)):
            if i == len(self.edges) or self.edges[i] > new_edge:
                self.edges.insert(i, new_edge)
                return
        print("INSERTING" + str(new_edge))
        self.edges.append(new_edge)
        #self.edges.append(new_edge)
        #self.edges.sort()
        return

    def __getitem__(self, obj):
        """ Get an item from the list of edges """
        for a_edge in self.edges:
            if obj == a_edge:
                return a_edge
        return None
        
            

if __name__ == "__main__":
    v1 = vertex('1word!')
    v2 = vertex('2word!')
    v3 = vertex('3word!')
    v4 = vertex('4word!')
    v5 = vertex('5word!')

    e1 = edge(v1)
    e2 = edge(v2)
    e3 = edge(v3)
    e4 = edge(v4)
    e5 = edge(v5)

    v1.add_edge(e1)
    v1.add_edge(e2)
    v1.add_edge(e3)
    v1.add_edge(e4)
    v1.add_edge(e5)

    for edge in v1:
        print(edge)

