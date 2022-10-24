#get input from user
num1 = int(input("Please enter your first number: "))
num2 = int(input("Please enter your second number: "))

#define sum, difference, product and quotient methods that return appropriate values
def sum(x, y):
  return x + y

def difference(x, y):
  return x - y

def product(x, y):
  return x * y

def quotient(x, y):
  return x / y
  
#Extra functions
def remainder(x, y):
  return x % y

def power(n, k):
  result = 1
  for i in range(k):
    result = result*n

  return result

def factorial(x):
  result = 1
  for i in range(1, x + 1):
    result = result * i
    
  return result

def sum_list(list):
  total = 0
  for num in list:
    total += num

  return total

def product_list(list):
  prod = 1
  for num in list:
    prod *= num

  return prod

#optional function you can make to run function
def runProgram(num1, num2):
  dictionary = {
    'addition': sum(num1, num2), 
    'subtraction': difference(num1,num2), 
    'multiplication': product(num1, num2), 
    'division': quotient(num1, num2), 
    'remainder' : remainder(num1, num2), 
    'power' : power(num1, num2), 
    'factorial' : factorial(num1)
  }
  
  inputFunction = (input("Please enter addition, subtraction, multiplication, division, remainder, power, or factorial: "))
  
  print(dictionary.get(inputFunction))

#call runProgram method
print("Starting calculator app...")
runProgram(num1, num2)