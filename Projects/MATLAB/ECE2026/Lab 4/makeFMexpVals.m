function [xx, tt] = makeFMexpVals(sigFMexp, dt)
%makeFMexpVals Creates an exponential FM signal

tt = sigFMexp.t1 : dt : sigFMexp.t2;
xx = sigFMexp.Amp * cos(2 * pi * (sigFMexp.fc .* tt + sigFMexp.gamma / sigFMexp.beta * exp(sigFMexp.beta .* tt)));

end