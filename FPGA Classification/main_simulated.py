
from overlay import fpga
from features import extract_features
from activity_detect import activity
import pandas as pd
import numpy as np

classifier = fpga( "/home/xilinx/mlp_v0.1.bit",432 )

reading_buffer = activity()

sim_data = pd.read_csv("/home/xilinx/x_sim.csv").to_numpy(dtype=np.float32)

for i in range(len(sim_data)):
    data = activity.update(sim_data[i])
    if data != None:
        data = extract_features(data)
        action = classifier.classify(data)
        print(action)



