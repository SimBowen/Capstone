import pynq.lib.dma
import pandas as pd
from pynq import allocate
from pynq import Overlay
import numpy as np



class fpga:
  def __init__(self, overlay, input_shape):
    self.ol = Overlay(overlay)
    self.dma = self.ol.axi_dma_0
    self.input_buffer = allocate(shape=(input_shape,), dtype=np.float32)
    self.output_buffer = allocate(shape=(1,), dtype=np.float32)

  def classify(self, data):
    self.input_buffer[:] = data.flatten()
    self.dma.sendchannel.transfer(self.input_buffer)
    self.dma.recvchannel.transfer(self.output_buffer)
    self.dma.sendchannel.wait()
    self.dma.recvchannel.wait()

    return self.output_buffer[0]



#sensors second set ready
#AI implement own algo with actual data, see if algo actual makes sense

