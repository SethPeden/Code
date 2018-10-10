function sigBeatSum = sum2BeatStruct(sigBeatIn)
%
%--- Assume the five basic fields are present, plus the starting and ending times
%--- Add the four fields for the parameters in Equation (4)
%
% 
sigBeatSum.f1 = sigBeatIn.fDelt - sigBeatIn.fc;
sigBeatSum.f2 = sigBeatIn.fDelt + sigBeatIn.fc;
sigBeatSum.X1 = sigBeatIn.Amp / 2 * exp(1j * (sigBeatIn.phiDelt - sigBeatIn.phic));
sigBeatSum.X2 = sigBeatIn.Amp / 2 * exp(1j * (sigBeatIn.phiDelt + sigBeatIn.phic));

sigBeatSum.times = sigBeatIn.times;
sigBeatSum.values = real(sigBeatSum.X1 * exp(1j * 2 * pi * sigBeatSum.f1 * sigBeatSum.times) + sigBeatSum.X2 * exp(1j * 2 * pi * sigBeatSum.f2 * sigBeatSum.times));