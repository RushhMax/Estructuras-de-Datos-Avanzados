#include <bits/stdc++.h>

struct Rectangle {
    double x1, y1;  // Esquina inferior izquierda
    double x2, y2;  // Esquina superior derecha

    Rectangle(double x1, double y1, double x2, double y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}

    bool intersects(const Rectangle& other) const {
        return !(x2 < other.x1 || x1 > other.x2 || y2 < other.y1 || y1 > other.y2);
    }

    bool contains(const Rectangle& other) const {
        return x1 <= other.x1 && y1 <= other.y1 && x2 >= other.x2 && y2 >= other.y2;
    }
};


struct Node {
    bool isLeaf;
    std::vector<Rectangle> rectangles;
    std::vector<Node*> children;  // Solo en nodos internos

    Node(bool isLeaf = true) : isLeaf(isLeaf) {}
};


class RTree {
public:
    Node* root;
    int maxEntriesPerNode;

    RTree(int maxEntries = 4) : maxEntriesPerNode(maxEntries) {
        root = new Node(true);  // La raíz es inicialmente una hoja
    }

    void insert(const Rectangle& rect) {
        insert(root, rect);
    }

    void insert(Node* node, const Rectangle& rect) {
        if (node->isLeaf) {
            node->rectangles.push_back(rect);
            if (node->rectangles.size() > maxEntriesPerNode) {
                split(node);
            }
        } else {
            // Si el nodo no es hoja, se inserta en el nodo adecuado
            Node* bestChild = chooseSubtree(node, rect);
            insert(bestChild, rect);
        }
    }

    Node* chooseSubtree(Node* node, const Rectangle& rect) {
        Node* bestChild = nullptr;
        double minIncrease = std::numeric_limits<double>::max();

        for (Node* child : node->children) {
            double increase = calculateBoundingBoxIncrease(child, rect);
            if (increase < minIncrease) {
                minIncrease = increase;
                bestChild = child;
            }
        }
        return bestChild;
    }

    double calculateBoundingBoxIncrease(Node* node, const Rectangle& rect) {
        // Lógica para calcular cuánto aumentaría el área del nodo
        double areaBefore = calculateArea(node);
        node->rectangles.push_back(rect);
        double areaAfter = calculateArea(node);
        node->rectangles.pop_back();
        return areaAfter - areaBefore;
    }

    double calculateArea(Node* node) {
        double minX = node->rectangles[0].x1;
        double minY = node->rectangles[0].y1;
        double maxX = node->rectangles[0].x2;
        double maxY = node->rectangles[0].y2;

        for (const Rectangle& rect : node->rectangles) {
            minX = std::min(minX, rect.x1);
            minY = std::min(minY, rect.y1);
            maxX = std::max(maxX, rect.x2);
            maxY = std::max(maxY, rect.y2);
        }

        return (maxX - minX) * (maxY - minY);
    }

    void split(Node* node) {
        // Implementar la lógica para dividir un nodo cuando se supera el número máximo de entradas
        std::cout << "Split node logic needed" << std::endl;
    }
    std::vector<Rectangle> search(Node* node, const Rectangle& query) {
        std::vector<Rectangle> result;
        if (node->isLeaf) {
            for (const Rectangle& rect : node->rectangles) {
                if (rect.intersects(query)) {
                    result.push_back(rect);
                }
            }
        } else {
            for (Node* child : node->children) {
                if (child->rectangles.empty() || child->rectangles[0].intersects(query)) {
                    std::vector<Rectangle> childResults = search(child, query);
                    result.insert(result.end(), childResults.begin(), childResults.end());
                }
            }
        }
        return result;
    }



};



int main() {
    RTree tree;

    // Insertar rectángulos
    tree.insert(Rectangle(1.0, 1.0, 3.0, 3.0));
    tree.insert(Rectangle(2.0, 2.0, 4.0, 4.0));
    tree.insert(Rectangle(5.0, 5.0, 7.0, 7.0));

    // Realizar una búsqueda de rango
    Rectangle query(1.5, 1.5, 5.5, 5.5);
    auto result = tree.search(tree.root, query);

    std::cout << "Found " << result.size() << " rectangles" << std::endl;

    return 0;
}
