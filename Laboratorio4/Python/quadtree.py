import os
import pygame
import random

class Point:
    def __init__(self, x, y, value, width=800, height=600):
        self.direction = ""
        self.x = x
        self.y = y
        self.value = value
        self.width = width
        self.height = height
        self.NW = None
        self.NE = None
        self.SW = None
        self.SE = None 
        self.parent = None

    def draw(self, screen, radius):
        pygame.draw.circle(screen, (0,0,255), (self.x, self.y), radius)
        if self.parent is None:
            base_x = 0
            base_y = 0
        else:
            base_x = self.parent.x
            base_y = self.parent.y

        pygame.draw.line(screen, (255, 255, 255), (self.x, base_x), (self.x, self.height), 1)  # Línea vertical
        pygame.draw.line(screen, (255, 255, 255), (base_y, self.y), (self.width, self.y), 1)    

        if self.NW:
            self.NW.draw(screen, radius)
        if self.NE:
            self.NE.draw(screen, radius)
        if self.SW:
            self.SW.draw(screen, radius)
        if self.SE:
            self.SE.draw(screen, radius)

class QuadTree:
    def __init__(self, width, height):
        self.root = None
        self.width = width
        self.height = height

    def _kill(self, node = None):
        if self.NW:
            self._kill(self.NW)
            del self.NW
        if self.NE:
            self._kill(self.NE)
            del self.NE
        if self.SW:
            self._kill(self.SW)
            del self.SW
        if self.SE:
            self._kill(self.SE)
        if(node):
            del node

    def compare(self, P, x, y):
        if x < P.x:
            return 'SW' if y < P.y else 'NW'
        return 'SE' if y < P.y else 'NE'

    def equal_cor(self, x, y, _x, _y):
        return x == _x and y == _y

    def insert(self, mouse_x, mouse_y, label, actual = None, anterior = None):
        if not self.root:
            self.root = Point(mouse_x, mouse_y, label, self.width, self.height)
            self.root.parent = None
            self.root.direction = "root"
            return True
        if actual is None:
            new_width = self.width 
            new_height = self.height 
            directionTO = self.compare(anterior, mouse_x, mouse_y)
            if(directionTO == "NW"):
                new_width = anterior.width - anterior.x 
                new_height = anterior.height - anterior.y
            elif(directionTO == "NE"):
                new_width = anterior.x
                new_height = anterior.height - anterior.y
            elif(directionTO == "SW"):
                new_width = anterior.width - anterior.xd 
                new_height = anterior.y
            elif(directionTO == "SE"):
                new_width = anterior.x
                new_height = anterior.y

            punto = Point(mouse_x, mouse_y,label,new_width,new_height)
            print(new_width, new_height)
            actual = punto
            actual.parent = anterior
            actual.direction = directionTO
            setattr(anterior, directionTO, actual)
            return True

        if self.equal_cor(mouse_x, mouse_y, actual.x, actual.y):
            return False

        target_direction = self.compare(actual, mouse_x, mouse_y)
        return self.insert(mouse_x, mouse_y, label , getattr(actual, target_direction), actual)

    def draw(self, screen):
        if self.root:
            self.root.draw(screen, 5)


    # def graph(self, file_path):
    #     with open(file_path, 'w') as f:
    #         f.write("graph T {\n")
    #         for point in points:
    #             f.write(f"{point.value};\n")
    #         self._graph_node(f, none)
    #         f.write("}\n")
    #     output_file = os.path.splitext(file_path)[0] + ".png"
    #     os.system(f"dot {file_path} -o {output_file} -Tpng")
    #     os.system(f"xdg-open {output_file}")
    #
    # def _graph_node(self, f, N = none, prefix=""):
    #     #f.write(f"{prefix}{N.value};\n")
    #     for point in points:
    #         f.write(f"{prefix}{N.value} -- {point.value};\n")
    #
    #     if(N.divided):
    #         for direction, child in [("NW", N.NW), ("NE", N.NE), ("SW", N.SW), ("SE", N.SE)]:
    #             if child:
    #                 f.write(f"{prefix}{N.value} -- {direction}_{child.value};\n")
    #                 self._graph_node(f, child, f"{direction}_")
    #
    # #
    # def post_order(self):
    #     self._post_order(self.root)
    #     print()
    #
    # def _post_order(self, N):
    #     if not N:
    #         return
    #     self._post_order(N.NW)
    #     self._post_order(N.NE)
    #     self._post_order(N.SW)
    #     self._post_order(N.SE)
    #     print(N.value, end=" ")


def main():
    pygame.init()

    width, height = 800, 600
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("QuadTree Rushh :D!")

    background = (0, 0, 0)
    screen.fill(background)

    # points = []
    # radio = 5

    # def drawPoints():
    #     for point in points:
    #         point.draw(screen, radio)
    #
    
    quadTree = QuadTree(width, height)

    text_input = ""
    input_active = False
    
    running = True
    while running:
        for event in pygame.event.get():
           # Check if the left mouse button is pressed
            # if event.type == pygame.MOUSEBUTTONDOWN:
            #     if event.button == 1:  # Left-click
            #         mouse_x, mouse_y = event.pos
            #         input_active = True
            #         text_input = ""  # Clear previous input
            #
            # # Capture text input if active
            # elif event.type == pygame.KEYDOWN and input_active:
            #     if event.key == pygame.K_RETURN:  # Press Enter to confirm input
            #         input_active = False
            #         # Create and insert the point with user-defined text
            #         point = Point(mouse_x, mouse_y, text_input)
            #         points.append(point)
            #         quadTree.insert(point)
            #         print(f"Inserted point with label '{text_input}' at ({mouse_x}, {mouse_y})")
            #
            #     elif event.key == pygame.K_BACKSPACE:  
            #         text_input = text_input[:-1]
            #
            #     else:
            #         text_input += event.unicode  # Add character to input
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_x, mouse_y = pygame.mouse.get_pos()

                if(event.button == 1):
                    #label = input("Enter a label for the point: ")
                    #points.append(Point(mouse_x, mouse_y, "", 0 ,0))
                    quadTree.insert(mouse_x, mouse_y , "", quadTree.root, None)
                    print(f"Inserted point at ({mouse_x}, {mouse_y})") 
                elif event.button == 3:
                    for point in points:
                        if point.x == mouse_x and point.y == mouse_y:
                            points.remove(point)
                            break

        screen.fill(background)
        #drawPoints()
        quadTree.draw(screen)
        pygame.display.flip()

    pygame.quit()

    # tree = QuadTree()
    # tree.insert(35, 40, "chicago")
    # tree.insert(50, 10, "mobile")
    # tree.insert(60, 75, "toronto")
    # tree.insert(80, 65, "buffalo")
    # tree.insert(5, 45, "denver")
    # tree.insert(25, 35, "omaha")
    # tree.insert(85, 15, "atlanta")
    # tree.insert(90, 5, "miami")
    #  
    # print("BUSQUEDA POST ORDEN")
    # tree.post_order()
    # tree.graph("quadtree.dot")
    #
    # print("BUSQUEDA 1")
    # tree.search(50, 80, 90, 60)
    # print("BUSQUEDA 2")
    # tree.search(0, 100, 100, 0)
    # print("BUSQUEDA 3")
    # tree.search(20, 75, 60, 5)
    # print("BUSQUEDA 4")
    # tree.search(20, 75, 60, 75)
    # print("BUSQUEDA 5")
    # tree.search(5, 100, 5, 45)
    # print("BUSQUEDA 6")
    # tree.search(20, 50, 95, 5)
    #
    # # Pygame visualization
    # # Constants
    # WIDTH, HEIGHT = 800, 600
    # BACKGROUND_COLOR = (255, 255, 255)
    #
    # # Pygame initialization
    # pygame.init()
    # screen = pygame.display.set_mode((WIDTH, HEIGHT))
    # pygame.display.set_caption('QuadTree Visualization')
    #
    # # Main loop
    # running = True
    # while running:
    #     for event in pygame.event.get():
    #         if event.type == pygame.QUIT:
    #             running = False
    #
    #     screen.fill(BACKGROUND_COLOR)
    #     tree.draw(screen)  # Draw the QuadTree
    #     pygame.display.flip()
    #
    # pygame.quit()

if __name__ == "__main__":
    main()
