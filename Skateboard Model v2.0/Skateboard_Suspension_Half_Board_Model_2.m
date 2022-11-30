% Skateboard Suspension - Half-Board Model 2.0
% Victoria Rea Vastis
% 2022-09-27
%--------------------------------------------------------------------------

% Variables
md = 0;  % Mass of deck and rider (kg)
mtt = 0; % Mass of skateboard truck top (kg)
mbt = 0; % Mass of skateboard truck bottom (kg)
kbt = 0; % Top bushing spring rate (N/m)
cbt = 0; % Top bushing damping coefficient (Ns/m)
kbb = 0; % Bottom bushing spring rate (N/m)
cbb = 0; % Bottom bushing damping coefficient (Ns/m)
kw = 0;  % Wheel spring rate (N/m)
cw = 0;  % Wheel damping coefficient (Ns/m)

%--------------------------------------------------------------------------

% Main Code
kF1 = (kbt*kbb)/(kbt + kbb);
cF2 = (cbt*cbb)/(cbt + cbb);
