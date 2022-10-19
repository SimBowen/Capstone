
from overlay import fpga
from activity_detect import activity
import pandas as pd
import numpy as np

classifier = fpga( "/home/xilinx/model_v1.0.bit",432 )

reading_buffer_1 = activity()
reading_buffer_2 = activity()

sim_data = pd.read_csv("/home/xilinx/x_sim.csv").to_numpy(dtype=np.float32)

#Simulates loop for input of data at 20 Hz
for i in range(len(sim_data)):
    #Adds single reading to sliding window of 60 readings, returns None if activity is not detected and the sliding window if it is
    #temp = reading_buffer_1.a_level()
    data_1 = reading_buffer_1.update(sim_data[i])
    #data_2 = reading_buffer_2.update(sim_data[i]) 
    #sim_data[i] is the recieved imu reading from the respective player
    #reading_buffer_1.a_level()
    if data_1 is not None:
        print("Extracted line:" + str(i))
        #print(temp)
        action = classifier.classify(data_1)
        out = ""
        if action == 0:
            out ="Grenade"
        elif action == 1:
            out = "Quit"
        elif action == 2:
            out = "Reload"
        elif action == 3:
            out = "Shield"
        print("Predictedaction is : " +out+"-"+ str(action))



