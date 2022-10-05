
from queue import Queue
import numpy as np

class activity:
    def __init__(self, overlay, input_shape):
        self.window = Queue()
        self.activity_level = 0
        self.counter = 0
        self.activity_threshold = 35
  
    def put(self, data):
        if self.window.qsize()== 60:
            removed = self.window.get()
            if removed[1] > -0.2:
                self.activity_level-=1

        if data[1]>-0.2:
            self.activity_level+=1

        self.window.put(data)
        
        if self.counter == 60:
            self.counter = 0
        elif self.counter > 0:
            self.counter += 1


    def extract_window(self):
        if self.window.qsize<60:
            return
        if self.counter !=0:
            return

        #If current tracked activity level is greater than threshold, trigger classification
        if self.activity_level > self.activity_threshold:
            self.counter += 1
            
            acc_x = []
            acc_y = []
            acc_z = []
            gyro_x = []
            gyro_y = []
            gyro_z = []

            for i in range(60):
                temp_data = self.window.get()
                acc_x.append(temp_data[0])
                acc_y.append(temp_data[1])
                acc_z.append(temp_data[2])
                gyro_x.append(temp_data[3])
                gyro_y.append(temp_data[4])
                gyro_z.append(temp_data[5])
            self.activity_level = 0


        output = [np.array(acc_x) + np.array(acc_y) + np.array(acc_z) + np.array(gyro_x) + np.array(gyro_y) + np.array(gyro_z)]
        return output


    #If not ready and not threshold, return null. Else return flat array
    def update(self, data):
        return self.extract_window()

    
            

                


    




