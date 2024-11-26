from PIL import Image
from color import Color
from octree_quantizer import octree_quantizer

def main():
    images = Image.open('rainbow.png')
    image2 = Image.open('beach.png')
    image3 = Image.open('random.png')


    for image in images:
        pixels = image.load()
        width, height = image.size

        octree = OctreeQuantizer()

        # add colors to the octree
        for j in range(height):
            for i in range(width):
                octree.add_color(Color(*pixels[i, j]))

        palette = octree.make_palette(256)
        palette_image = Image.new('RGB', (16, 16))
        palette_pixels = palette_image.load()
        for i, color in enumerate(palette):
            palette_pixels[i % 16, i / 16] = (int(color.red), int(color.green), int(color.blue))
        palette_image.save('rainbow_palette.png')

        out_image = Image.new('RGB', (width, height))
        out_pixels = out_image.load()
        for j in range(height):
            for i in range(width):
                index = octree.get_palette_index(Color(*pixels[i, j]))
                color = palette[index]
            
                out_pixels[i, j] = (int(color.red), int(color.green), int(color.blue))
        out_image.save('rainbow_out.png')


if __name__ == '__main__':
    main()
