from numpy import mean, median, std, percentile, fft, abs, argmax
from math import sqrt
import numpy as np


def Mean(data):
    """Returns the mean of a time series"""
    return data.mean()


def Median(data):
    """Returns the median of a time series"""
    return data.median()

def extract_mean(data):
  mean_x = Mean(data[0])
  mean_y = Mean(data[1])
  mean_z = Mean(data[2])

  return [mean_x,mean_y,mean_z]

def extract_median(data):
  median_x = Median(data[0])
  median_y = Median(data[1])
  median_z = Median(data[2])

  return [median_x,median_y,median_z]

def extract_magnitude(data):
    mag_array = []
    for t in range(len(data[0])): 
        mag_array.append(sqrt( data[0][t]**2 + data[1][t]**2 + data[2][t]**2) )

    return mag_array


def merge_feature_array(raw, a_mean, a_median, a_mag, g_mean, g_median, g_mag):
    arr1 = raw
    arr1 = np.concatenate(arr1, a_mean)
    arr1 = np.concatenate(arr1, a_median)
    arr1 = np.concatenate(arr1, a_mag)
    arr1 = np.concatenate(arr1, g_mean)
    arr1 = np.concatenate(arr1, g_median)
    arr1 = np.concatenate(arr1, g_mag)


    return arr1

def extract_features(data):
    #By right recieved data should be Accel x, y, z, Gyro x, y, z
    a_mean = extract_mean(data[:180])
    g_mean = extract_mean(data[180:360])
    a_mag = extract_magnitude(data[:180])
    g_mag = extract_magnitude(data[180:360])
    a_median = extract_median(data[:180])
    g_median = extract_median(data[180:360])

    #Output should be accel x for 60 readings, accel y for 60 readings, accel z for 60 readings,
    #  gyro x for 60 readings, gyro y for 60 readings, gyro z for 60 readings,
    #  120 readings for both mag,  3 for mean 3 for median. 486
    return merge_feature_array(data, a_mean, a_median, a_mag, g_mean, g_median, g_mag)