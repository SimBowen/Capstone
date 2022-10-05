
from queue import Queue

class activity:
    def __init__(self, overlay, input_shape):
        self.window = Queue()
        self.activity_level = 0
        self.counter = 0
  
    def put(self, data):
        if self.window.qsize()== 60:
            self.window.get()
        self.window.put(data)
        if self.counter == 59:
            self.counter = 0
        elif self.counter > 0:
            self.counter += 1


    def activity_check(self, data):
        a_x = data[0]
        a_y = data[1]
        a_z = data[2]

        #Threshold for move 0
        x_0 = 23
        y_0 = 23
        z_0 = 23
        #Threshold for move 1
        x_1 = 23
        y_1 = 23
        z_1 = 23

        #analyse data, if acceleration not > threshold for # values, reset counter

        if a_x > x_0 and a_y > y_0 and a_z > z_0:
            self.activity_level += 1

    def extract_window(self):
        if self.window.qsize<60:
            return
        if self.counter !=0:
            return
        #Activity threshold
        activity_threshold = 30
        #If current tracked activity level is greater than threshold, trigger classification
        if self.activity_level > activity_threshold:
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
 
        output = acc_x + acc_y + acc_z + gyro_x + gyro_y + gyro_z
        return output


    #If not ready and not threshold, return null. Else return flat array
    def update(self, data):
        self.activity_check(data)
        return self.extract_window()

    
            

                


    




