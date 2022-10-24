
"""
Facilitator Note: This is a decent way to learn about dictionaries, but with the 
introduction to switch statements this is not "programming best practices"
"""
from cmath import pi

# Triangle area function
def triangle():
    base = int(input("Input base value for triangle "))
    height = int(input("Input height value for triangle "))

    area = base * height * 0.5
    print("Area of a triangle with base ", base, "and height", height, "is", area)

# Circle area function
def circle():
    radius = int(input("Input radius value for circle "))
    area = pi * radius * radius

    print("Area of circle with radius", radius, "is", area)

# Square area function
def square():
    length = int(input("Input length value for square "))
    area = length * length

    print("Area of a square with length", length, "is", area)

# Rectangle area function
def rectangle():
    length = int(input("Input length value for rectangle "))
    width = int(input("Input width value for rectangle "))

    area = length * width
    print("Area of a rectangle with length ", length, "and width", width, "is", area)

# Note the syntax for this dictionary -- we do not put the () because otherwise the function will execute
# on initialization
def input_shape():
    shapes_dict = {
        "triangle" : triangle,
        "circle" : circle,
        "square" : square,
        "rectangle" : rectangle
    }

    input_shape = input("Pick a shape ")

    # Call the function
    shapes_dict[input_shape]()

input_shape()
    


