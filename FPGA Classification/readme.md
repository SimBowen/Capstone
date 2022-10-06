To use the run python scripts that utilize PYNQ Overlays run the following code:

```
sudo -s
export XILINX_XRT=/usr
```

Run the python script using python [script name].py

Files:
activity_detect.py - Action detection & fifo sliding window script
features.py - Feature extraction script
main_simulated.py - Simulated action sequence implementing FPGA classificationa and action detection
main.py - FPGA classificationa and action detection test script
overlay.py - PYNQ overlay functions script
predict.py - Classification & benchmarking test based on WISDM dataset
simple_bench.py - Classification & benchmarking test based on Chester dataset
