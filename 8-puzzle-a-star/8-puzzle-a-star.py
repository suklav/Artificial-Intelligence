#python program to solve 8 puzzle problem using A-star algorithm
#Please note that I have not used manhatten distance

import numpy as np

import time

import math

#8 puzzle is a 3x3 board
N=3

#The gap/blank position is represented by zero 
#this is the initial state
initial_state=[1,2,3,4,5,6,0,7,8]

#initial_state=[1,2,3,4,5,6,7,0,8]
#initial_state=[1,2,3,0,4,6,7,5,8]


#this is our goal state
goal_state=[1,2,3,4,5,6,7,8,0]

# Now reshaping the initial state array
#the outermost dimension will have N arrays, each with N elements
start = np.array(initial_state).reshape(N,N)

# Now reshaping the goal state array
#he outermost dimension will have N arrays, each with N elements
goal = np.array(goal_state).reshape(N,N)


#returns array of arrays which contains the arrays after performing certain move
def movement_func(array):
	notun_arrays = {}
	goal = np.array(goal_state).reshape(N,N)
	
#NOTE THAT : UP,DOWN,RIGHT,LEFT indicates the movement of the blank tile or the zero position
#Although other tile also gets changed but the operation is written wrt the blank tile

	for i in range(len(array)):
		for j in range(len(array)):
			if array[i][j] == 0:

				#To move UP
				if i > 0:
					up_array = array.copy()
					up_array[i][j], up_array[i-1][j] = up_array[i-1][j], up_array[i][j] #swap with UP position 
					if not np.array_equal(up_array, start):
						notun_arrays["OPERATION: UP "] = up_array 


				#To move DOWN
				if i < len(array) - 1:
					down_array = array.copy()
					down_array[i][j], down_array[i+1][j] = down_array[i+1][j], down_array[i][j] #swap with DOWN position 
					if not np.array_equal(down_array, start):
						notun_arrays["OPERATION: DOWN"] = down_array


				#To move RIGHT
				if j < len(array) - 1:
					right_array = array.copy()
					right_array[i][j], right_array[i][j+1] = right_array[i][j+1], right_array[i][j] #swap with RIGHT position 
					if not np.array_equal(right_array, start):
						notun_arrays["OPERATION: RIGHT"] = right_array


				#To move LEFT
				if j > 0 :
					left_array = array.copy()
					left_array[i][j], left_array[i][j-1] = left_array[i][j-1], left_array[i][j] #swap with LEFT position 
					if not np.array_equal(left_array, start):
						notun_arrays["OPERATION: LEFT"] = left_array


	return notun_arrays



#H value by calculating number of misplaced tiles
def calculate_h_value(array):
	
	s = sum(abs((val-1)%3 - i%3) + abs((val-1)//3 - i//3)
        for i, val in enumerate(array.reshape(1,9)[0]) if val)

	return s


def main():
    #flag to detect if the goal state is achieved
	flag = True
	#array to keep track of previous steps
	earlier_step = []
	#copying initial state array defined globally
	array = start.copy()
	ola = None
	#count is a flag that counts the no of steps
	count = 0
    
    #to calculate the time elapsed in search
	#tic = time.time()
	#it=0
	while flag:
		#it=it+1
		#print(it)
		#the h values
		h={} #calculated later by counting no of misplaced tiles
		
		if ola is not None:
			array = ola

        #returns array of arrays which contains the arrays after performing certain move
		act = movement_func(array)

        #h value which is calculated by counting no of misplaced tiles
		for keys, values in act.items():
			h[keys]=calculate_h_value(values)
			

		#searching for the smallest h value and its key in the dict (used lambda fn)
		new_dic =  dict(sorted(h.items(), key=lambda item: item[1]))
		resultant = list(new_dic.items())[0]
		r, v = resultant[0], resultant[1]

		if not earlier_step:
			earlier_step.append(['Initial State: ', array])

		else:
			for iterator in range(len(earlier_step)):
					if np.array_equal(act[r], earlier_step[iterator][1]):
					#check if the 2nd value in dic is equal to the lowest or not
					#taking only the top two smallest 
						new_h = list(new_dic.items())[1]
						r, v = new_h[0], new_h[1]


		if np.array_equal(act[r], goal):
			print("\n")
			print("Solution Found! \n The step are as follows : \n")

			earlier_step.append([resultant[0], act[r]])
			for iterator in earlier_step:
				print(iterator[0])
				print(iterator[1])
				print("\n")
			flag = False
			#toc = time.time()
			print("Total number of steps is: " + str(count) +" step(s)")
			#print("Total amount of time in the search: " + str(toc - tic) + " second(s)")

		else:
			earlier_step.append([r, act[r]])
			ola = act[r]
			# earlier_step[resultant[0]] = act[resultant[0]]
			count+=1

		

#calling the main function
main()


