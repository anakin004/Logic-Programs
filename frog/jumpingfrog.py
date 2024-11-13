import sys


def baseCases(p):

    dp = []
    dp.append(1)

    #1, 2 ... p-1, p
    for i in range(1,p+1):
        totalProb = 0

        #calculating current position from all the previous positions in the dp array
        for j in range(i):
            totalProb += 1/p * dp[j]
        
        dp.append(totalProb)


    return dp


def frogJump(x,p,dp):

    if x <= p:
        return dp[x]
    
    # if p = 3 and x = 6
    # i will be 4, 5, 6
    # we will calculate dp[4] , d[5] , dp[6] then return d[6]
    for i in range(p+1,x+1):
        totalProb = 0

        #calculating prob of the current position i
        #from p positions behind i to i-1
        for j in range(i-p, i):
            totalProb += dp[j]*1/p
        
        dp.append(totalProb)
    
    #returning out desired probability
    return dp[x]




def main():

    # using sys.stdin.read() to read all input at once from standard input
    input_data = sys.stdin.read().strip()
    
    # split the input into lines
    lines = input_data.splitlines()

    n = int(lines[0].strip())

    index = 1

    for _ in range(n):

        x,p = map(int,lines[index].split(" "))
        index += 1

        dp = baseCases(p)
        prob = frogJump(x,p,dp)

        print(f'{prob:.9f}')

main()