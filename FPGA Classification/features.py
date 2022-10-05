from numpy import mean, median, std, percentile, fft, abs, argmax
import numpy as np

def Mean(data):
    """Returns the mean of a time series"""
    return data.mean()

def Median(data):
    """Returns the median of a time series"""
    return data.median()


from math import sqrt

def extract_acc_magnitude(data):
  mag_array = []
  for i in range(len(data)):
    mags = []
    for t in range(len(data[i][0])): 
     mags.append( sqrt( data[i][0][t]**2 + data[i][1][t]**2 + data[i][2][t]**2) )
    mag_array.append(mags)
  return mag_array

def extract_acc_median(data):
  median_array = []

  for i in range(len(data)):
    median_array.append([np.median(data[i][0]), np.median(data[i][1]), np.median(data[i][2])])
  return median_array

def extract_gyro_median(data):
  median_array = []
  for i in range(len(data)):
    median_array.append([np.median(data[i][3]), np.median(data[i][4]), np.median(data[i][5])])
  return median_array


def extract_acc_mean(data):
  mean_array = []

  for i in range(len(data)):
    mean_array.append([Mean(data[i][0]),Mean(data[i][1]),Mean(data[i][2])])
  return mean_array

def extract_gyro_mean(data):
  mean_array = []

  for i in range(len(data)):
    mean_array.append([Mean(data[i][3]),Mean(data[i][4]),Mean(data[i][5])])
  return mean_array


def merge_feature_array(raw, mean_a, mean_g, median_a, median_g, mag):
  out = []
  raw = np.array(raw)
  for i in range(len(raw)):
    arr1 = np.concatenate((raw[i].flatten(), mean_a[i]))
    arr2 = np.concatenate((arr1, mean_g[i]))
    arr3 = np.concatenate((arr2, median_a[i]))
    arr4 = np.concatenate((arr3, median_g[i]))
    arr5 = np.concatenate((arr4,mag[i]))
    out.append(arr5)

  return out

def extract_features(data):
  raw = data
  mean_a = extract_acc_mean(data)
  mean_g = extract_gyro_mean(data)
  median_a = extract_acc_median(data)
  median_g = extract_gyro_median(data)
  mag = extract_acc_magnitude(data)
  return np.array(merge_feature_array(raw,mean_a,mean_g,median_a,median_g,mag))