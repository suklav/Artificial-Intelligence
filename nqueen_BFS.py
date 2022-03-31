
from queue import Queue


class solve_nqn:

    def __init__(self, n):
        self.n = n

    def solve_bfs(self):
                if self.n < 1:
                       return []
                solutions = []
                queue = Queue()
                queue.put([])
                while not queue.empty():
                            solution = queue.get()
                            if self.conflict(solution): #chacking if there is any attacking condition
                                    continue
                            row = len(solution)
                            if row == self.n:
                                    solutions.append(solution)
                                    continue
                            for col in range(self.n):
                                    elem = (row, col) #elem is a queen itself
                                    Arrray = solution.copy()
                                    Arrray.append(elem) #the dynamic array stores the queen positions
                                    queue.put(Arrray)
                return solutions

    def conflict(self, Arrray):
        #print(Arrray)
        for i in range(1, len(Arrray)):
               for j in range(0, i):
                        e1, e2 = Arrray[i]
                        e3, e4 = Arrray[j]
                         #chacking if there is any attacking condition
                        if (e1 == e3) or (e2 == e4) or abs(e1 - e3) == abs(e2 - e4):
                                        return True
        return False


def main():
    n = int(input('Enter the N for the NxN board:'))
    sol_holder = solve_nqn(n)
    all_sols = sol_holder.solve_bfs()
    print('Total No. of solutions: ', len(all_sols))
    

if __name__ == '__main__':
    main()
    
    
    
