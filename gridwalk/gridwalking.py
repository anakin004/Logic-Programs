MAX = 201
MOD = 1000000007

# setting up Pascal's Triangle.
tri = []
for i in range(MAX):
    newlist = []
    for j in range(i+1):
        newlist.append(0)
    tri.append(newlist)

# filling in entries
for i in range(MAX):
    tri[i][0] = 1;
    tri[i][i] = 1;
    for j in range(1,i):
        tri[i][j] = (tri[i-1][j-1] + tri[i-1][j])%MOD

def main():

    #dst position
    toks = input().split()
    x = int(toks[0])
    y = int(toks[1])

    #number of queries
    numQ = int(input())

    for _ in range(numQ):

        # Get which type of query.
        cmd = int(input())

        # visiting certain locations
        if cmd == 1:
            
            #getting locs
            numL = int(input())
            locs = []

            for i in range(numL):
                item = [int(x) for x in input().split()]
                locs.append(item)

            print(solve(x,y,locs))

        # avoiding case
        else:

            # getting locs.
            numL = int(input())
            locs = []

            for i in range(numL):
                item = [int(x) for x in input().split()]
                locs.append(item)

            if numL == 1:
                print( (tri[x+y][x] - solve(x,y,locs) + MOD)%MOD)

            else:

                # Count paths through both locs to avoid
                sub1 = solve(x, y, [locs[0]])
                sub2 = solve(x, y, [locs[1]])

                # Paths through both.
                addback = solve(x, y, locs)

                # Do full calculation via I/E. add 2*MOD to ensure non negative mod result
                tot = (tri[x+y][x] - sub1 - sub2 + addback + 2*MOD)%MOD
                print(tot)

# Returns the number of walking paths to (x,y) from (0,0) that go through
# The locations listed in locs (sorted by x already).
def solve(x,y,locs):

    # Initialize variables.
    res = 1
    curX = 0
    curY = 0

    # loop through locations to visit.
    for i in range(len(locs)):

        # cant go backwards in y 
        if i > 0 and locs[i-1][1] > locs[i][1]:
            return 0

        # updating result, easier to get change in x,y first
        dx = locs[i][0]-curX
        dy = locs[i][1]-curY
        res = (res*tri[dx+dy][dx])%MOD

        # updating current location.
        curX = locs[i][0]
        curY = locs[i][1]

    # last movement
    dx = x-locs[-1][0]
    dy = y-locs[-1][1]
    
    # multiplying by last path.
    res = (res*tri[dx+dy][dx])%MOD
    return res

main()
        

