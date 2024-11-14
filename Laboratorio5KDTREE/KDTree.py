
class Node:
    def __init__(self, data):
        self.L = none # puntero 
        self.R = none # puntero 
        self.P = none # puntero 
        self.data = data # coordenadas


class KDTree:
    def __init__(self):
        self.root = none

    def insert(self, data):
        if self.root is none:
            self.root = Node(data)
        else:
            self.insertCord(data, 0)

    def insertCord(self, data, cord):
        if cord < data.size():



        

    def search(self):
