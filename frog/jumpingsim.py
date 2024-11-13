import random

def main():

    n = int(input("Please enter the distance of the position from the starting point\n"))
    p = int(input("Please enter the jumping distance of the frog\n"))

    res = [0]*(n+1)
    for _ in range(10_000):
        x = 0
        while x<=10:
            res[x] += 1
            choice = random.randint(1,p)
            x+=choice

    for i in range(len(res)):
        spaces = 4 - len(str(i))
        print(i, f'{' '*spaces}{res[i]/10_000}')


main()