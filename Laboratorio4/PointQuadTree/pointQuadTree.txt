import pygame
import random

class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, screen, color=(255,251, 80)): 
        pygame.draw.circle(screen, color, (self.x, self.y), 4) 

class QuadTree():
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.width = w
        self.height = h
        self.points = []
        self.dividido = False
        self.capacity = 4
        self.NW = None
        self.NE = None
        self.SW = None
        self.SE = None

    def contiene(self, punto):
        return self.x <= punto.x <= self.x + self.width and self.y <= punto.y <= self.y + self.height

    def dividir(self):
        x,y, w, h = self.x, self.y, self.width, self.height

        self.NW = QuadTree(x, y, w/2, h/2)
        self.NE = QuadTree(x + w/2, y, w/2, h/2)
        self.SW = QuadTree(x, y + h/2, w/2, h/2)
        self.SE = QuadTree(x + w/2, y + h/2, w/2, h/2)

        self.dividido = True

        for point in self.points[:]:
            if not self.insertar(point):
                printd("Error al insertar el punto en el nodo dividido")

        self.points.clear()

    def insertar(self, punto):
        if not self.contiene(punto):
            return False
        if len(self.points) <= self.capacity-1  and not self.dividido:
            self.points.append(punto)
            return True
        
        if not self.dividido:
            self.dividir()

        if self.NW.insertar(punto):
            return True
        if self.NE.insertar(punto):
            return True
        if self.SW.insertar(punto):
            return True
        if self.SE.insertar(punto):
            return True

    def search_rango(self, x, y, w, h):
        puntos = []
        if self.x >= x + w or self.x + self.width <= x or self.y >= y + h or self.y + self.height <= y:
            return puntos

        for point in self.points:
            if x <= point.x <= x + w and y <= point.y <= y + h:
                puntos.append(point)

        if self.dividido:
            puntos.extend(self.NW.search_rango(x, y, w, h))
            puntos.extend(self.NE.search_rango(x, y, w, h))
            puntos.extend(self.SW.search_rango(x, y, w, h))
            puntos.extend(self.SE.search_rango(x, y, w, h))

        return puntos

    def draw(self, screen):
        pygame.draw.rect(screen, (255, 255, 255), (self.x, self.y, self.width, self.height), 1)
        if self.dividido:
            self.NW.draw(screen)
            self.NE.draw(screen)
            self.SW.draw(screen)
            self.SE.draw(screen)

        for punto in self.points:
            punto.draw(screen)

pygame.init()

width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("QuadTree RUSHH! ")

background = (39, 154, 241)
screen.fill(background)

qtree = QuadTree(0, 0, width, height)
drawing_rect = False
rect_start = (0, 0)
rect_end = (0, 0)

x, y, w, h = 0, 0, 0, 0

points = []

def random_points(n):
    print("Generando e insertando %d puntos aleatorios" % n)
    for i in range(n):
        x = random.randint(0, width)
        y = random.randint(0, height)
        point = Point(x, y)
        print("Insertando punto x = %d, y = %d" % (x, y))
        qtree.insertar(point)

random_points(50)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                print("Insertando punto x = %d, y = %d" % (event.pos[0], event.pos[1]))
                point = Point(event.pos[0], event.pos[1])
                if not qtree.insertar(point):
                    print("Error al insertar el punto")
            elif event.button == 3:
                rect_start = event.pos
                drawing_rect = True
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 3 and drawing_rect:
                rect_end = event.pos
                drawing_rect = False
                x = min(rect_start[0], rect_end[0])
                y = min(rect_start[1], rect_end[1])
                w = abs(rect_end[0] - rect_start[0])
                h = abs(rect_end[1] - rect_start[1])
                puntos_encontrados = qtree.search_rango(x, y, w, h)
                print("Puntos encontrados:", [(p.x, p.y) for p in puntos_encontrados])
        elif event.type == pygame.MOUSEMOTION and drawing_rect:
            rect_end = event.pos


    screen.fill(background)
    qtree.draw(screen)

    #if drawing_rect:
    x = min(rect_start[0], rect_end[0])
    y = min(rect_start[1], rect_end[1])
    w = abs(rect_end[0] - rect_start[0])
    h = abs(rect_end[1] - rect_start[1])
    pygame.draw.rect(screen, (16, 20, 25), (x, y, w, h), 1)

    for p in qtree.search_rango(x, y, w, h):
        p.draw(screen, color=(16, 20, 25))

    pygame.display.flip()

pygame.quit()
