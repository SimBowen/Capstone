/*
----------------------------------------------------------------------------------
--	(c) Rajesh C Panicker, NUS,
--  Description : Self-checking testbench for AXI Stream Coprocessor (HLS) implementing the sum of 4 numbers
--	License terms :
--	You are free to use this code as long as you
--		(i) DO NOT post a modified version of this on any public repository;
--		(ii) use it only for educational purposes;
--		(iii) accept the responsibility to ensure that your implementation does not violate any intellectual property of any entity.
--		(iv) accept that the program is provided "as is" without warranty of any kind or assurance regarding its suitability for any particular purpose;
--		(v) send an email to rajesh.panicker@ieee.org briefly mentioning its use (except when used for the course EE4218 at the National University of Singapore);
--		(vi) retain this notice in this file or any files derived from this.
----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include "hls_stream.h"

/***************** AXIS with TLAST structure declaration *********************/

struct AXIS_wLAST {
	float data;
	bool last;
};

/***************** Coprocessor function declaration *********************/

void mlp(hls::stream<AXIS_wLAST>& S_AXIS, hls::stream<AXIS_wLAST>& M_AXIS);

/***************** Macros *********************/

#define INPUT_LAYER 432
#define NO_OF_TESTCASE 4

/************************** Variable Definitions *****************************/

float test_input[INPUT_LAYER*NO_OF_TESTCASE] = {-1.01,-1.06,-1.03,-1.08,-1.04,-0.93,-0.86,-0.89,-0.83,-0.93,-0.84,-0.82,-0.44,0.05,0.04,0.15,0.24,0.27,0.55,1.01,1.49,1.81,1.88,1.04,0.81,0.93,1.06,1.05,1.09,1.16,1.33,1.41,1.4,1.21,1.16,0.61,0.51,0.28,-0.01,-0.37,-0.9,-1.12,-0.87,-0.77,-0.68,-0.67,-0.6,-0.55,-0.47,-0.47,-0.5,-0.5,-0.53,-0.54,-0.53,-0.53,-0.51,-0.53,-0.73,-1.12,-0.77,-0.73,-0.59,-0.42,-0.35,-0.25,-0.24,-0.16,-0.13,-0.04,-0.01,0.06,0.25,0.31,0.41,0.38,0.29,0.16,-0.01,-0.2,-0.38,-0.74,-0.67,-0.21,0.0,-0.07,-0.13,-0.14,-0.15,-0.21,-0.39,-0.32,-0.37,-0.21,-0.06,0.01,0.12,0.08,-0.04,-0.24,0.3,0.69,0.6,0.62,0.56,0.56,0.52,0.51,0.5,0.52,0.52,0.53,-0.74,-0.75,-0.76,-0.75,-0.75,-0.78,-0.76,-0.58,0.33,0.45,0.47,0.71,0.95,1.09,1.2,1.21,1.13,0.98,0.89,0.51,0.09,0.12,0.11,0.22,0.16,-0.05,0.05,-0.12,0.03,0.62,0.78,0.55,0.42,0.37,0.48,0.37,0.47,0.45,0.49,0.55,0.59,0.49,0.59,0.4,0.32,0.09,-0.18,-0.52,-1.16,-1.01,-0.73,-1.03,-0.86,-0.83,-0.64,-0.63,-0.54,-0.54,-0.55,-0.53,0.28,0.3,0.29,0.29,0.25,0.29,0.41,0.42,35.94,92.26,87.71,53.74,38.93,44.7,55.42,91.29,79.9,99.89,97.07,107.04,128.76,34.25,15.9,31.08,43.03,26.48,-10.76,14.57,-85.75,-97.2,-49.74,0.28,26.51,8.41,5.62,-3.08,-5.96,-3.0,-12.54,39.02,25.39,41.03,72.65,75.58,156.99,172.84,227.62,250.69,250.31,45.33,16.51,36.09,17.69,-5.36,-15.88,-1.59,-13.79,-2.13,-12.77,-1.43,-13.59,-10.25,-5.77,-3.84,-10.27,-11.76,1.34,37.3,-80.05,-163.2,-172.76,-87.88,-97.05,-7.97,15.34,32.74,88.21,49.32,62.82,41.51,98.26,-57.08,84.4,6.09,41.95,53.21,37.31,69.18,104.56,36.57,11.15,-14.44,20.23,13.73,-2.09,3.98,-7.15,0.82,-29.76,31.81,9.41,58.51,70.93,-5.71,40.6,105.4,20.89,185.76,-54.22,100.35,-90.99,20.43,-29.15,-8.77,-15.43,2.5,-17.67,-1.31,-14.86,-0.55,-14.22,-7.32,-1.91,1.84,-4.18,8.34,-11.26,-39.15,66.29,166.62,172.25,167.27,188.55,190.35,161.72,157.75,179.14,187.31,215.1,223.99,250.92,245.22,189.87,192.52,211.68,242.53,227.86,216.42,250.92,191.23,36.94,-109.82,-43.52,22.97,14.02,2.58,-11.82,-20.87,-46.26,-97.0,-141.61,-180.16,-208.84,-249.35,-240.01,-208.63,-214.58,-246.01,-180.19,-191.97,-61.35,-9.06,-18.04,-11.81,-3.92,4.06,7.74,4.71,-2.68,-2.75,3.91,0.83,-4.74,-3.43,-8.16,-14.03,-5.61,29.77,-0.04533333333333334,-0.09333333333333332,0.18899999999999997,38.47833333333334,8.200333333333335,31.447,-0.485,-0.13,0.31,25.935000000000002,3.24,3.245,1.3122118731363468,1.363451502621197,1.2766753698571927,1.3590069904161641,1.4514131045295133,1.454475850607359,1.4957272478630586,1.510562809021856,1.4080838043241601,1.3516286472252652,1.2238463955905576,0.9675226095549395,0.5140038910358559,0.3361547262794322,0.4263801121065568,0.4640043103248072,0.4090232267243512,0.3178049716414141,0.5523585791856591,1.0365809182114052,1.537985695642193,2.051365398947735,2.1428252378577213,1.1950732195141853,0.912414379544733,1.0033444074693396,1.1708543888972702,1.122051692213866,1.1964530914331746,1.2618240764861004,1.4700680256369092,1.5469324484281788,1.563649577111189,1.3222329598070077,1.3028046668629951,0.7295203903935791,0.6139218191268331,0.3047950130825634,0.18466185312619388,0.6818357573492314,1.4985326155943353,1.658493292117879,1.284445405612866,1.42765542061101,1.2310970717209915,1.2047406359876802,1.019803902718557,0.9795407086997456,0.873212459828649,0.8848163651289459,0.9071383576941281,0.9009994450608725,0.9523129737644027,0.9716480844420988,0.9708758932015976,0.9630680142129111,0.9407975340103736,0.986610358753647,1.130751962191532,1.3293607486307093,0.68,0.91,1.19,0.99,0.98,1.0,0.89,0.78,1.05,1.1,1.04,1.19,1.02,1.05,0.93,1.06,0.95,0.99,0.9,0.84,0.87,0.83,0.78,0.63,0.56,0.41,0.33,0.23,0.17,0.17,-0.07,-0.17,-0.2,-0.23,-0.33,-0.24,-0.24,-0.27,-0.25,-0.27,-0.3,-0.24,-0.28,-0.26,-0.28,-0.27,-0.25,-0.28,-0.26,-0.26,-0.26,0.75,0.74,0.8,0.89,0.74,0.75,0.7,0.91,0.98,0.6,0.63,0.72,0.71,0.68,0.67,0.57,0.68,0.53,0.61,0.61,0.62,0.61,0.56,0.5,0.35,0.29,0.17,0.16,0.06,0.01,-0.05,-0.06,-0.11,-0.17,-0.19,-0.26,-0.29,-0.32,-0.43,-0.37,-0.41,-0.4,-0.44,-0.36,-0.43,-0.44,-0.44,-0.46,-0.44,-0.43,-0.46,-0.44,-0.45,-0.44,-0.45,-0.47,-0.46,-0.45,-0.46,-0.47,0.78,0.76,0.7,0.79,0.73,0.76,0.76,0.73,0.73,0.43,0.46,0.42,0.59,0.63,0.69,0.65,0.46,0.38,0.23,0.24,0.04,0.02,-0.05,-0.09,-0.14,-0.16,-0.31,-0.3,-0.42,-0.51,-0.45,-0.7,-0.63,-0.68,-0.78,-0.64,-0.83,-0.68,-0.71,-0.73,-0.7,-0.63,-0.68,-0.78,-0.73,-0.82,-0.7,-0.82,-0.76,-0.77,-0.76,-0.81,-0.78,-0.81,-0.72,-0.74,-0.79,-0.76,-0.78,-0.78,0.24,0.31,0.2,0.33,0.06,0.27,0.16,0.21,-0.05,18.86,14.04,0.23,79.12,35.47,58.12,34.19,4.69,6.93,53.9,-7.3,59.94,35.67,54.78,77.54,53.97,57.77,18.14,28.81,16.36,24.36,7.29,19.37,21.67,26.15,16.28,25.35,18.13,28.29,16.4,28.48,13.16,21.39,6.58,0.12,1.42,3.61,8.96,-7.33,5.64,-8.85,-4.42,-7.15,3.41,2.98,7.38,-2.52,-1.63,-2.76,1.48,-3.8,-0.74,58.38,12.49,-45.85,31.93,5.72,-9.26,16.86,56.77,43.93,0.42,-153.91,-75.56,-162.4,-146.21,-70.01,-130.14,-123.98,-46.12,-87.31,-11.98,-83.57,-69.54,-20.65,-88.22,-45.11,-93.46,-71.47,-95.16,-101.92,-116.57,-98.85,-100.12,-79.77,-97.41,-63.37,-70.56,-61.42,-56.94,-44.63,-61.34,-33.47,-38.31,-50.32,-25.94,-31.68,-5.66,-10.56,-3.78,-22.79,-8.81,-9.29,-3.37,-11.87,2.15,-5.34,-7.47,-6.74,-1.06,-3.93,34.23,67.61,10.9,74.18,14.94,9.75,9.52,71.68,104.21,76.68,28.41,25.48,39.49,20.77,59.57,70.66,12.31,-34.34,17.96,-15.3,29.82,44.65,70.03,83.24,78.68,78.49,63.55,68.87,53.62,42.45,41.76,60.98,56.34,62.82,67.25,60.78,63.54,48.22,66.55,61.53,57.47,45.52,41.64,15.85,10.55,10.42,9.42,7.91,10.32,1.48,-2.16,0.82,2.49,1.64,3.26,0.26,1.16,-1.75,0.04,0.21,5.61,20.85,-17.61,-11.86,38.74,9.74,-14.02,7.09,6.75,0.44283333333333336,0.10049999999999999,-0.2826666666666667,18.282833333333333,-39.40950000000001,29.444999999999997,0.72,-0.02,-0.48,15.16,-35.89,23.165,1.0036433629531958,1.19858249611781,1.4528936643815336,1.3536247633668645,1.348962564343429,1.3874436925511608,1.2407658925034972,1.1324310133513653,1.2360420704814217,1.2786711852544421,1.2293494214420895,1.3424231821597838,1.1886547017532048,1.1910499569707393,1.0597169433391165,1.125033332839521,1.006081507632458,1.0512373661547614,0.9620810776644555,0.9410632284814873,1.0085137579626766,0.9454628496138808,1.0497618777608568,0.8977193325310534,0.8971621926942754,0.901443287178955,0.7655716818169283,0.9087904048789247,0.7705193054038296,0.8472897969408105,0.8214012417813841,0.828854631404084,0.772593036468748,0.841961994391671,0.9202716990106781,0.8805679985100525,0.961041102138717,0.8697700845625814,0.9728823155962903,0.9187491496594705,0.9315578350268973,0.9202173656261873,0.9633794683301072,0.9372833082905083,0.9633794683301072,0.8909545442950499,0.9115920140062659,0.9560857702110204,0.9207062506576134,0.9421252570651102,0.9470480452437459,1.1083771921146701,1.1051244273836318,1.0816653826391969,1.2349493916756267,1.0412012293500232,1.1013627921806692,1.0455620498086184,1.18536914081648,1.2230290266383703,0.04,0.06,0.08,0.09,0.11,0.08,0.07,0.06,0.1,0.11,0.11,0.11,0.11,0.12,0.11,0.11,0.12,0.12,0.12,0.12,0.13,0.11,-0.52,-0.49,-0.5,-0.49,-0.45,-0.5,-0.51,-0.93,-1.04,-0.89,-0.9,-0.92,-0.82,-0.33,-0.13,-0.08,0.02,-0.03,0.01,0.01,0.02,0.03,0.04,0.08,0.11,0.13,0.07,0.01,-0.04,-0.09,-0.07,0.09,0.1,0.05,0.06,0.0,0.02,0.04,0.09,0.05,0.03,0.05,0.07,0.07,0.06,0.06,0.04,0.05,0.06,0.05,0.04,0.05,0.03,0.03,0.03,0.04,0.03,0.04,0.04,0.05,-0.81,-0.83,-0.82,-0.82,-0.83,-0.77,-0.81,-0.71,-0.76,-0.74,-0.76,-0.69,-0.69,-0.55,-0.34,-0.12,-0.02,0.04,0.04,0.04,0.04,0.04,0.04,0.01,-0.04,-0.09,-0.08,-0.01,0.01,0.1,0.14,0.31,0.06,0.12,0.11,0.12,0.12,0.09,1.05,1.1,1.15,1.12,1.08,1.08,1.08,1.06,1.08,1.09,1.09,1.08,1.09,1.07,1.09,1.09,1.1,1.08,1.08,1.09,1.11,1.06,0.2,0.2,0.22,0.18,0.2,0.26,0.26,0.44,0.57,0.65,0.55,0.27,1.06,0.83,0.34,0.44,0.67,0.82,1.0,1.01,1.06,1.1,1.16,1.25,1.45,1.35,1.1,1.03,0.95,0.89,0.93,0.4,1.06,1.09,1.1,1.07,1.08,1.1,0.87,-8.22,-3.16,-1.1,3.34,-2.09,-2.0,-2.25,-6.57,-3.39,-3.29,-2.96,-3.36,0.69,-3.97,-2.33,-3.04,-4.68,-2.14,-3.96,-0.1,-1.23,1.54,-4.91,-13.83,-18.89,-1.33,1.37,4.62,-3.16,-4.68,47.34,81.4,117.58,33.44,179.12,90.13,38.0,-2.91,-5.64,-10.03,-10.08,-5.84,-22.49,-32.4,-40.94,-40.19,23.71,53.83,67.93,45.61,34.63,9.5,-48.31,-6.31,-7.53,-20.71,-4.0,-4.88,2.91,2.75,-7.2,-10.76,-6.85,-5.42,-1.89,-4.27,-4.44,-11.08,-6.95,-10.76,-11.18,-8.58,-1.92,-6.23,-3.2,-3.31,-6.6,-5.92,-5.34,-3.9,1.81,-1.07,-13.9,-43.36,-48.56,-14.77,-8.53,-3.05,-41.24,-135.18,-87.35,-98.89,-252.14,-252.14,-252.14,-170.3,-78.66,-37.58,2.65,9.84,-13.06,12.2,-0.98,-1.52,11.96,2.89,-17.88,-8.19,-5.49,-11.97,-19.53,-42.91,81.89,-16.24,7.15,-4.97,-3.11,-5.94,4.54,2.84,2.12,1.6,-4.07,-5.96,-3.37,-0.68,1.1,-0.86,0.45,-2.11,-1.45,-2.45,0.73,-1.08,0.1,0.56,2.38,0.77,1.48,-0.55,1.7,0.29,-0.3,-4.94,7.02,3.61,-0.1,2.16,21.92,88.74,126.35,157.59,192.03,168.01,91.84,54.36,-1.15,10.33,1.64,7.91,-0.97,2.05,2.54,0.71,2.35,-0.77,-33.27,-28.19,-26.36,-17.87,-30.46,-11.36,4.67,-2.13,2.48,-2.79,3.23,4.54,8.55,-0.11083333333333334,-0.14666666666666667,0.8876666666666666,7.811000000000001,-27.979499999999998,13.291833333333333,0.04,0.04,1.065,-2.935,-6.725,0.75,1.0546089322587782,1.102769241500687,1.15316954521007,1.1247221879201994,1.087841900277793,1.0852188719332152,1.0839280418920807,1.0633908030446757,1.0853570840972109,1.0966767983321248,1.0971781988355402,1.0867382389517726,1.0962663909835055,1.0778682665335315,1.0959470790143109,1.0959470790143109,1.106932698947863,1.087382177525455,1.0870602559196063,1.0973149046650192,1.1183022847155415,1.0668645649753299,0.9831073186585482,0.984377976185977,0.985291834940288,0.9720596689504198,0.965090669315583,0.95420123663722,0.9918669265581952,1.2500399993600206,1.408580846100074,1.3274788133902553,1.3000384609695206,1.1812705024675763,1.507348665704123,1.048951857808546,0.4980963762164909,0.463033476111609,0.6705967491719595,0.8215229759416348,1.0008496390567367,1.0108412338245805,1.0609429767899876,1.101135777277262,1.161378491276638,1.2525973016097391,1.4547164672196435,1.3592277219068187,1.1051244273836318,1.0300970828033638,0.9508943158942533,0.9001111042532471,0.9430800602281866,0.514003891035856,1.0663957989414625,1.0977249200050074,1.1071133636624573,1.0767079455451232,1.086830253535482,1.1044002897500527,0.14,0.11,0.15,0.12,0.15,0.13,0.14,0.13,0.14,0.14,0.15,0.14,0.13,0.13,0.14,0.15,-0.44,-0.46,-0.46,-0.44,-0.45,-0.47,-0.5,-0.7,-0.85,-0.81,-0.78,-0.79,-0.94,-0.95,-1.03,-1.01,-0.99,-0.91,-0.89,-0.79,-0.66,-0.58,-0.38,-0.36,-0.23,-0.18,-0.06,-0.09,0.03,0.06,0.19,0.32,0.35,0.33,0.29,0.29,0.23,0.16,0.2,0.2,0.2,0.19,0.17,0.17,1.0,1.0,1.0,1.0,1.0,0.99,1.0,1.01,1.0,0.99,0.99,1.0,1.0,1.01,1.0,1.0,-0.87,-0.86,-0.85,-0.86,-0.85,-0.83,-0.84,-0.78,-0.72,-0.7,-0.59,-0.58,-0.51,-0.5,-0.4,-0.31,-0.16,-0.05,0.09,0.21,0.35,0.46,0.54,0.65,0.7,0.74,0.83,0.88,0.91,0.92,0.94,0.93,0.93,0.94,0.98,1.0,0.98,1.02,1.0,1.01,0.99,0.99,0.97,0.98,-0.03,-0.03,-0.02,-0.04,-0.03,-0.01,-0.02,-0.03,-0.04,-0.04,-0.02,0.0,-0.04,0.0,-0.01,-0.01,0.15,0.16,0.17,0.17,0.18,0.17,0.19,0.24,0.32,0.33,0.41,0.54,0.55,0.58,0.56,0.57,0.58,0.5,0.49,0.47,0.42,0.36,0.31,0.33,0.26,0.13,0.1,0.11,0.06,0.02,-0.04,-0.07,-0.17,-0.15,-0.07,-0.02,-0.09,-0.04,0.01,-0.02,-0.01,-0.05,-0.1,-0.09,-0.45,-1.94,-3.26,-3.1,-2.26,-1.91,-0.52,-2.17,0.9,-0.91,-0.86,-2.7,-5.13,-2.5,-0.39,-0.93,-0.33,0.45,-1.88,-2.49,-2.48,2.49,7.11,14.07,19.41,35.38,46.12,57.73,90.04,98.84,100.38,97.76,91.16,94.87,69.04,82.64,61.9,60.7,49.29,53.76,62.83,58.01,38.67,40.65,31.16,31.93,23.73,19.28,23.18,-3.84,-4.15,-8.1,4.14,-10.77,-2.78,3.2,7.13,6.65,2.85,-2.75,-16.78,-2.3,-9.79,-10.6,-2.15,-5.03,-3.78,-5.83,-6.85,-4.56,-5.77,-5.98,-8.83,-2.73,-4.51,-9.28,-12.52,3.61,-4.51,-2.15,-5.03,-0.38,-7.22,-14.48,-45.74,-52.27,-31.02,-24.43,0.87,-12.05,-14.95,-17.11,-20.48,3.1,-6.31,11.44,-30.21,4.88,-9.44,-13.53,-8.74,-15.02,9.74,38.61,20.66,47.45,49.5,33.42,39.1,9.47,21.43,-11.34,-3.65,4.76,-5.85,-4.66,-8.76,-1.16,-17.46,3.78,-0.02,-0.22,0.34,0.7,-0.9,1.87,-1.6,-0.8,0.58,1.6,0.59,-1.06,0.13,0.84,0.07,1.22,-1.75,-4.19,5.28,5.84,3.03,11.97,9.55,52.76,87.38,116.01,95.13,87.07,90.66,101.97,116.1,127.64,137.52,123.93,133.79,118.48,130.56,101.71,114.37,114.19,88.32,89.15,73.08,66.03,66.45,61.37,65.64,44.52,14.26,10.69,-1.06,-1.59,-8.03,-2.61,-1.1,-1.13,-3.61,-6.95,-7.48,-2.87,-0.19383333333333336,0.42783333333333323,0.1358333333333333,23.647499999999997,-3.3903333333333334,40.42366666666667,0.08499999999999999,0.925,0.015,3.67,-5.4,5.5600000000000005,1.010198000393982,1.0064790112068904,1.0113851887386922,1.0079682534683323,1.011632344283238,0.9985489472229191,1.0099504938362078,1.0187737727287642,1.0105444077327825,1.000649788887201,1.0014988766843425,1.009752444909147,1.0092076099594176,1.0183319694480772,1.00980196078241,1.011236866416568,0.9864076236526155,0.9883319280484669,0.9813256340277675,0.9808669634563089,0.9784681905918046,0.9688653157173086,0.9958413528268446,1.075174404457249,1.1590081966923271,1.1202678251204041,1.0604715932074749,1.1189727431890377,1.202580558632144,1.2202049008260867,1.2387493693237548,1.2004582458378135,1.1584903970253704,1.0395191195932858,1.0199509792141974,0.9429209935090003,0.8570297544426332,0.8231646250902671,0.7294518489934754,0.8130190649671138,0.7813449942247022,0.7725930364687479,0.8381527307120105,0.891403387922662,0.9124691775616315,0.9221713506718803,0.9598437372822725,0.9860020283954796,1.0081170566953026,1.0074720839804943,1.0244022647378324,1.0413932974625868,1.010643359449811,1.0332473082471592,1.0198529305738155,1.029805806936434,1.0100495037373167,1.0093066927351666,0.9898484732523458,0.9986991538997116};
int expected_result[NO_OF_TESTCASE] = {0,1,2,3};

/*****************************************************************************
* Main function
******************************************************************************/

int main()
{
	AXIS_wLAST write_input, read_output;
	hls::stream<AXIS_wLAST> S_AXIS;
	hls::stream<AXIS_wLAST> M_AXIS;

	int test_case_cnt = 0;
	int predicted_result[NO_OF_TESTCASE];

	for (test_case_cnt = 0; test_case_cnt < NO_OF_TESTCASE; test_case_cnt++) {

		/******************** Input to Coprocessor : Transmit the Data Stream ***********************/

		printf(" Transmitting Data for test case %d ... \r\n", test_case_cnt);
		for (int i = 0 ; i < INPUT_LAYER ; i++) {
			write_input.data = test_input[i + test_case_cnt * INPUT_LAYER];
			write_input.last = 0;
			if (i==INPUT_LAYER-1) {
				write_input.last = 1;
			}
			S_AXIS.write(write_input);
		}

		/********************* Call the hardware function (invoke the co-processor / ip) ***************/

		mlp(S_AXIS, M_AXIS);

		/******************** Output from Coprocessor : Receive the Data Stream ***********************/

		printf(" Receiving data for test case %d ... \r\n", test_case_cnt);
		read_output = M_AXIS.read();
		predicted_result[test_case_cnt] = read_output.data;

	}

	/************************** Checking correctness of results *****************************/

	bool success;

	printf(" Comparing data ...\r\n");
	for (int i = 0; i < NO_OF_TESTCASE; i++) {
		success = (expected_result[i] == predicted_result[i]);
		printf("Expected: %d   Predicted: %d  \r\n", expected_result[i], predicted_result[i]);
	}

	if (success) {
		printf("Test Success\r\n");
		return 0;
	} else {
		printf("Test Failed\r\n");
		return 1;
	}
}
