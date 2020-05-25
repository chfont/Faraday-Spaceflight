
% Initial Data For E-12 Engine - From https://www.nar.org/SandT/pdf/Estes/E12.pdf

x = [0.000 0.002 0.050 0.100 0.200 0.274 0.292 0.310 0.320 0.330 0.340 0.350 0.360 0.380 0.390 0.400 0.450 0.500 0.550 0.600 0.650 0.700 0.800 0.900 1.000 1.310 1.316 1.330 2.380 2.400 2.420 2.440];
y = [0.000 1.678 4.459 10.431 24.152 31.959 32.702 27.957 25.957 22.857 19.128 16.455 15.314 13.853 13.436 13.271 12.070 11.522 11.266 10.736 10.777 10.276 10.105 9.920 9.693 9.759 10.696 9.628 9.870 6.442 3.674 0.000];

% Breakup X and Y into segments that follow similar trends, for use in fitting

xA = x(1:7);
xB = x(7:25);
xC = x(25:29);
xD = x(29:32);

yA = y(1:7);
yB = y(7:25);
yC = y(25:29);
yD = y(29:32);

% Get best fit curve for each segment
f1 = polyfit(xA,yA,1);
f2 = polyfit(xB,yB,2);
f3 = polyfit(xC,yC,1);
f4 = polyfit(xD,yD,1);

% Displays the coefficients of the curve fitting the segments
fprintf("Function 1 is: ")
disp(f1)
fprintf("\nFunction 2 is: ")
disp(f2)
fprintf("\nFunction 3 is: ")
disp(f3)
fprintf("\nFunction 4 is: ")
disp(f4)
