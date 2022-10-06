
from overlay import fpga
from features import extract_features
from activity_detect import activity
import pandas as pd
import numpy as np

classifier = fpga( "/home/xilinx/model_v0.1.bit",432 )

reading_buffer = activity()

sim_data = pd.read_csv("/home/xilinx/x_sim.csv").to_numpy(dtype=np.float32)

#Simulates loop for input of data at 20 Hz
for i in range(len(sim_data)):
    #Adds single reading to sliding window of 60 readings, returns None if activity is not detected and the sliding window if it is
    data = reading_buffer.update(sim_data[i])
    if data is not None:
        #Extract features
        data = extract_features(data)
        action = classifier.classify(data)
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



