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
        mag_array.append( sqrt(data[i][0]**2 + data[i][1]**2 + data[i][2]**2) )
    return mag_array

def extract_acc_median(data):
    transpose = np.array(data).transpose()
    median_array = [np.median(transpose[0]), np.median(transpose[1]), np.median(transpose[2])]
    return median_array

def extract_gyro_median(data):
    transpose = np.array(data).transpose()
    median_array = [np.median(transpose[0]), np.median(transpose[1]), np.median(transpose[2])]
    return median_array


def extract_acc_mean(data):
    transpose = np.array(data).transpose()
    mean_array = [Mean(transpose[0]), Mean(transpose[1]), Mean(transpose[2])]
    return mean_array


def extract_gyro_mean(data):
    transpose = np.array(data).transpose()
    mean_array = [Mean(transpose[0]), Mean(transpose[1]), Mean(transpose[2])]
    return mean_array


def merge_feature_array(raw, mean_a, mean_g, median_a, median_g, mag):
    out = []
    raw = np.array(raw)
    transpose = raw.transpose()
    arr1 = np.concatenate((transpose.flatten(), mean_a))
    arr2 = np.concatenate((arr1, mean_g))
    arr3 = np.concatenate((arr2, median_a))
    arr4 = np.concatenate((arr3, median_g))
    arr5 = np.concatenate((arr4,mag))
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